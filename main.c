#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Declaration.h"

NPC *rat;
Player *player;
Room *basement, *hallway, *garage, *office, *bathroom, *bedroom, *stairs, *upstairs, *attic, *exitDoor;

int secretCode;
int codeboxOpened = 0;
Furniture *codebox;
char input[500];
char word1[100];
char word2[100];

int main(void) {
    CreateRooms();
    player = CreatePlayer("Player", basement);
    Play();
    return 0;
}