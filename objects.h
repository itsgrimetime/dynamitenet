#include <glib.h>

typedef struct Player {

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

} player;

typedef struct Bomb {

    int playerId;
    int type;

} bomb;

