# Escape It! - Text Adventure Game in C

A text based escape room game built in C. You wake up trapped in the basement of an abandoned house and must explore rooms, collect items, solve puzzles, and find the key to escape.

## How to Play

1. Clone the repo
2. Build with CMake or gcc:
```
gcc -o escape main.c Item.c Room.c Player.c Command.c game.c
```
3. Run: `./escape`

## Commands

- `go [direction]` - Move north, south, east, west, up, down
- `look` - Look around the current room
- `take [item]` - Pick up an item
- `drop [item]` - Drop an item
- `inventory` - Show what you are carrying
- `search [furniture]` - Search furniture for hidden items
- `interact [npc]` - Talk to an NPC
- `read [item]` - Read an item's description
- `open codebox` - Try to open the codebox with a 3-digit code
- `save` - Save your game
- `load` - Load a saved game
- `map` - Show the house map
- `help` - Show all commands
- `quit` - Quit the game

## Project Structure

- `Declaration.h` - All structs, extern globals, and function prototypes
- `Item.h / Item.c` - Item struct and creation
- `Room.c` - Room, furniture, and NPC creation
- `Player.c` - Player creation and inventory check
- `Command.c` - Command parser
- `Features.c` - All game logic
- `main.c` - Global variables and entry point

## Built With

- C (C11)
- CLion on Ubuntu
- gcc compiler