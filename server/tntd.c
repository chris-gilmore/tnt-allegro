#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <enet/enet.h>

#include "enet_common.h"

static ENetHost  *create_server(int);

static int    init_player(void);
static void   deinit_player(int);

static void   broadcast(ENetHost *);
static void   send_receive(ENetHost *);


static ENetHost *create_server(int port) {
  ENetAddress address;
  ENetHost *server;

  /* Bind the server to the default localhost.    */
  /* A specific host address can be specified by  */
  /* enet_address_set_host (&address, "x.x.x.x"); */
  address.host = ENET_HOST_ANY;
  address.port = port;

  server = enet_host_create(&address /* the address to bind the server host to */, 
                            MAX_PLAYER_COUNT /* allow up to MAX_PLAYER_COUNT clients and/or outgoing connections */,
                            2        /* allow up to 2 channels to be used, 0 and 1 */,
                            0        /* assume any amount of incoming bandwidth */,
                            0        /* assume any amount of outgoing bandwidth */);
  if (server == NULL) {
    fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
    exit(EXIT_FAILURE);
  }

  return server;
}

static int init_player(void) {
  // find the first open player slot
  for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
    if (!players[i].active) {
      players[i].active = true;
      players[i].button = 0;
      players[i].set = false;
      players[i].expected_seq_no = 1;
      return i;
    }
  }

  fprintf(stderr, "Server: oops, max of %d players still active\n", MAX_PLAYER_COUNT);
  return -1;
}

static void deinit_player(int i) {
  players[i].active = false;
}

static void broadcast(ENetHost *server) {
  ServerMessage msg;
  ENetPacket *packet;

  for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
    msg.button[i] = players[i].button;

    players[i].set = false;
    players[i].expected_seq_no++;
  }

  packet = enet_packet_create(&msg, sizeof(ServerMessage), ENET_PACKET_FLAG_RELIABLE);
  enet_host_broadcast(server, 0, packet);
}

static void send_receive(ENetHost *server) {
  ENetEvent event;
  int player_id;
  ClientMessage *msg_in;

  while (enet_host_service(server, &event, 1000) > 0) {
    switch (event.type) {

    case ENET_EVENT_TYPE_RECEIVE:
      if (event.peer->data == NULL) {
        fprintf(stderr, "Server: oops, client's data is NULL\n");
        break;
      }

      player_id = *(int*)event.peer->data;

      if (players[player_id].set) {
        broadcast(server);
      }

      msg_in = (ClientMessage*)event.packet->data;

      players[player_id].button = msg_in->button;

      if (msg_in->seq_no == players[player_id].expected_seq_no) {
        players[player_id].set = true;
      }

      enet_packet_destroy(event.packet);
      break;

    case ENET_EVENT_TYPE_CONNECT:
      printf("Server: a new client connected from %x:%u\n", event.peer->address.host, event.peer->address.port);

      player_id = init_player();
      if (player_id < 0) break;

      event.peer->data = malloc(sizeof(int));
      *(int*)event.peer->data = player_id;

      printf("Server: created Player %d\n", player_id);

      break;

    case ENET_EVENT_TYPE_DISCONNECT:
      if (event.peer->data == NULL) {
        fprintf(stderr, "Server: oops, client's data is NULL\n");
        break;
      }

      player_id = *(int*)event.peer->data;
      printf("Server: Player %d disconnected\n", player_id);

      free(event.peer->data);
      event.peer->data = NULL;
      deinit_player(player_id);
      break;
    }
  }
}

int main(int argc, char **argv) {
  ENetHost *server;
  int port = DEFAULT_PORT;

  if (enet_initialize() != 0) {
    fprintf(stderr, "An error occurred while initializing ENet.\n");
    return EXIT_FAILURE;
  }
  atexit(enet_deinitialize);

  server = create_server(port);

  for (;;) {
    send_receive(server);
  }

  enet_host_destroy(server);

  return EXIT_SUCCESS;
}
