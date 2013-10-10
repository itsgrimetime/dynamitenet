#include <glib.h>

typedef enum bomb_type {
    BLACK,
    RED,
    REMOTE
} BOMB_TYPE;

typedef enum player_state {
    ALIVE,
    DEAD
} PLAYER_STATE;

typedef struct player {

    int id;
    int x, y;
    int state;
    int kills;

    int firepower;
    int speed;

    int canThrow;
    int canKick;

    int bombCount;
    GSList *bombs;  // Player's bombs out on the field

} Player;

typedef struct bomb {

    int playerId;
    int type;

} Bomb;

// What the delta is
typedef enum delta_type {
    // Movement
    MOVE,
    // Bomb placement
    PLACE_BOMB,
    // Death
    DEATH
} DELTA_TYPE;

// What the delta is affecting
typedef enum delta_object {
    PLAYER,
    BOMB
} DELTA_OBJECT;

// Contains one bit of information changed since the last state 
typedef struct delta {
    DELTA_TYPE type;
    DELTA_OBJECT object;
    int id;
    // Not sure if we're going to need other info, but put it here!
    union information {
        // x, y
        int location[2];
        
    };
} Delta;

// The entire game state
typedef struct state {
    GList *players;
    GList *bombs;
} State;
