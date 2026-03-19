#include <stdio.h>

typedef struct Room {
    char *description;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;

} Room;

int main(void) {
    printf("Zork Text Based Game\n");
    return 0;
}