#include <stdio.h>
#include <stdlib.h>
#include <enet/enet.h>
#include <allegro5/allegro5.h>

#include "enet_common.h"

static ENetHost  *create_client(void);
static ENetPeer  *connect_client(ENetHost *, int);
static void       disconnect_client(ENetHost *, ENetPeer *);

static void   disp_init(void);
static void   disp_deinit(void);
static void   disp_pre_draw(void);
static void   disp_post_draw(void);

static void   keyboard_init(void);
static void   keyboard_update(ALLEGRO_EVENT *);

static void   send_receive(ENetHost *);
static void   main_loop(ALLEGRO_EVENT_QUEUE *, ENetHost *, ENetPeer *);


static ENetHost *create_client(void) {
  ENetHost *client;

  client = enet_host_create(NULL /* create a client host */,
                            1    /* only allow 1 outgoing connection */,
                            2    /* allow up to 2 channels to be used, 0 and 1 */,
                            0    /* assume any amount of incoming bandwidth */,
                            0    /* assume any amount of outgoing bandwidth */);
  // 57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
  // 14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);

  if (client == NULL) {
    fprintf(stderr, "An error occurred while trying to create an ENet client host\n");
    exit(EXIT_FAILURE);
  }

  return client;
}

static ENetPeer *connect_client(ENetHost *client, int port) {
  ENetAddress address;
  ENetEvent event;
  ENetPeer *server;

  enet_address_set_host(&address, "localhost");
  address.port = port;

  /* Initiate the connection, allocating the two channels 0 and 1. */
  server = enet_host_connect(client, &address, 2, 0);
  if (server == NULL) {
    fprintf(stderr, "Client: no available peers for initiating an ENet connection\n");
    exit(EXIT_FAILURE);
  }

  /* Wait up to 5 seconds for the connection attempt to succeed. */
  if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
    printf("Client: connected to %x:%u\n", event.peer->address.host, event.peer->address.port);
  } else {
    /* Either the 5 seconds are up or a disconnect event was */
    /* received.  Reset the peer in the event the 5 seconds  */
    /* had run out without any significant event.            */
    enet_peer_reset(server);
    fprintf(stderr, "Client: connection to server failed\n");
    exit(EXIT_FAILURE);
  }

  return server;
}

static void disconnect_client(ENetHost *client, ENetPeer *server) {
  ENetEvent event;

  enet_peer_disconnect(server, 0);

  while (enet_host_service(client, &event, 3000) > 0) {
    switch (event.type) {
    case ENET_EVENT_TYPE_RECEIVE:
      enet_packet_destroy(event.packet);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      printf("Client: disconnection from server succeeded\n");
      return;
    }
  }

  // failed to disconnect gracefully, force the connection closed
  enet_peer_reset(server);
}


// Display stuff

#define BUFFER_W 400
#define BUFFER_H 300

#define DISP_W 640
#define DISP_H 480

static ALLEGRO_DISPLAY* disp;
static ALLEGRO_BITMAP* buffer;

static void disp_init(void) {
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  disp = al_create_display(DISP_W, DISP_H);
  if (disp == NULL) {
    fprintf(stderr, "Unable to create an Allegro display.\n");
    exit(EXIT_FAILURE);
  }

  buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  if (buffer == NULL) {
    fprintf(stderr, "Unable to create an Allegro bitmap buffer.\n");
    exit(EXIT_FAILURE);
  }
}

static void disp_deinit(void) {
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

static void disp_pre_draw(void) {
  al_set_target_bitmap(buffer);
}

static void disp_post_draw(void) {
  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

  al_flip_display();
}


// Keyboard stuff

#define KEY_SEEN     1
#define KEY_RELEASED 2
static unsigned char key[ALLEGRO_KEY_MAX];

static void keyboard_init(void) {
  memset(key, 0, sizeof(key));
}

static void keyboard_update(ALLEGRO_EVENT* event) {
  switch(event->type) {
  case ALLEGRO_EVENT_TIMER:
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
      key[i] &= KEY_SEEN;
    break;
  case ALLEGRO_EVENT_KEY_DOWN:
    key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
    break;
  case ALLEGRO_EVENT_KEY_UP:
    key[event->keyboard.keycode] &= KEY_RELEASED;
    break;
  }
}


static void send_receive(ENetHost *client) {
  ENetEvent event;
  ServerMessage *msg;
  bool redraw = false;
  int i;

  while (enet_host_service(client, &event, 0) > 0) {
    if (event.type == ENET_EVENT_TYPE_RECEIVE) {
      msg = (ServerMessage*)event.packet->data;

      for (i = 0; i < MAX_PLAYER_COUNT; i++) {
        players[i].button = msg->button[i];
      }
      redraw = true;

      enet_packet_destroy(event.packet);
    }

    if (redraw) {
      for (i = 0; i < MAX_PLAYER_COUNT; i++) {
        printf("Player %d button: %u\n", i, players[i].button);
      }

      redraw = false;
    }
  }
}

static void main_loop(ALLEGRO_EVENT_QUEUE* queue, ENetHost *client, ENetPeer *server) {
  ALLEGRO_EVENT event;
  bool done = false;
  static unsigned short tick = 0;

  while (!done) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:
      if(key[ALLEGRO_KEY_ESCAPE]) {
        done = true;
      }

      ClientMessage msg = { tick++ };
      ENetPacket *packet = enet_packet_create(&msg, sizeof(msg), ENET_PACKET_FLAG_RELIABLE);
      enet_peer_send(server, 0, packet);

      send_receive(client);

      break;
    }

    keyboard_update(&event);

  }
}

int main(int argc, char **argv) {
  ENetHost *client;
  ENetPeer *server;
  int port = DEFAULT_PORT;
  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE *queue;

  if (enet_initialize() != 0) {
    fprintf(stderr, "An error occurred while initializing ENet.\n");
    return EXIT_FAILURE;
  }
  atexit(enet_deinitialize);

  client = create_client();
  server = connect_client(client, port);

  if (!al_init()) {
    fprintf(stderr, "An error occurred while initializing Allegro.\n");
    return EXIT_FAILURE;
  }

  if (!al_install_keyboard()) {
    fprintf(stderr, "Unable to install an Allegro keyboard driver.\n");
    return EXIT_FAILURE;
  }

  timer = al_create_timer(1.0 / 60);
  if (timer == NULL) {
    fprintf(stderr, "Unable to create an Allegro timer.\n");
    return EXIT_FAILURE;
  }

  queue = al_create_event_queue();
  if (queue == NULL) {
    fprintf(stderr, "Unable to create an Allegro queue.\n");
    return EXIT_FAILURE;
  }

  disp_init();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  keyboard_init();

  al_start_timer(timer);
  main_loop(queue, client, server);

  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  disconnect_client(client, server);
  enet_host_destroy(client);

  return EXIT_SUCCESS;
}
