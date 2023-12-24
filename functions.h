#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief Number of boats in the game.
 */

# define NUMBER_BOATS 5

/**
 * @brief Size of the game board.
 */

# define GAME_BOARD_SIZE 10

/**
 * @brief Maximum length of a boat.
 */

# define MAX_BOAT_LENGTH 4

/**
 * @brief Enumeration of states for a cell on the game board.
 */

enum{
    WATER,  /**< Untouched water. */
    WATER_SHOT, /**< Water hit. */
    BOAT,   /**< Part of a boat. */
    WRECK,  /**< Wreck of a sunk boat. */
};

/**
 * @brief Structure representing a boat.
 */

typedef struct{
    int length; /**< Length of the boat. */
    char direction; /**< 'H' for Horizontal, 'V' for Vertical. */
    int position_X; /**< X position of the top-left corner of the boat. */
    int position_Y; /**< Y position of the top-left corner of the boat. */
} Boat;

/**
 * @brief Structure representing a game board.
 */

typedef struct{
    char ** matrice;    /**< Matrix of the game board. */
    int side_size;  /**< Size of the game board's side. */
} Game_board;

/**
 * @brief Structure representing the overall state of the game.
 */

typedef struct{
    Game_board *game_board1;    /**< Game board for player 1. */
    Game_board *game_board2;    /**< Game board for player 2. */
    Boat *Boat_player1;         /**< Array of boats for player 1. */
    Boat *Boat_player2;       /**< Array of boats for player 2. */
} Game;

Game_board* Create_Game_Board (int side_size);
void Free_Game_Board(Game_board *game_board);
Boat* Create_Boat2(int length);
int Random_number(int min, int max);
Boat* Create_BoatsArray(int num_boats);
void Free_Boat(Boat *boat);
bool Boat_Alive(const Boat *boat);
int Valid_coordinates(int x, int y, int side_size);
int Selected_Box(const Game_board *game_board, int x, int y);
void Place_Boats(Game_board *game_board, Boat *boats, int player);
void Display_Game_Board(const Game_board *game_board, int player_view, bool game_started, const Boat *player_boats, const Boat *computer_boats);
void Player_Turn(Game_board *game_board, Boat *player_boats);
void Computer_Turn(Game_board *game_board, Boat *computer_boats);
int Number_Boats_Alive(const Boat *boats);
bool Winner_Player(const Boat *player_boats, const Boat *computer_boats);
bool Winner_Computer(const Boat *player_boats, const Boat *computer_boats);
void Play_Game();

#endif