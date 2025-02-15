#ifndef _ENET_COMMON_H_
#define _ENET_COMMON_H_

#define MAX_PLAYER_COUNT 4
#define DEFAULT_PORT 2000

// message sent from client to server
typedef struct {
  unsigned short   button;
} ClientMessage;

// message sent from server to client
typedef struct {
  unsigned short   button[MAX_PLAYER_COUNT];
} ServerMessage;

// storage for all players
struct {
  bool             active;
  unsigned short   button;
  bool             set;
} players[MAX_PLAYER_COUNT];

#endif /* !_ENET_COMMON_H_ */
