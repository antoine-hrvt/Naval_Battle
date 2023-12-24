#include "functions.h"


/**
 * @brief Function to create a game board.
 * 
 * @param side_size Size of the game board's side.
 * @return A pointer to the dynamically allocated Game_board structure.
 */

Game_board* Create_Game_Board (int side_size){
    Game_board *game_board = (Game_board*)malloc(sizeof(Game_board));
    if (game_board == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    game_board->side_size = side_size;
    game_board->matrice = (char**)malloc(side_size * sizeof(char*)); 
    if (game_board->matrice == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < side_size; i++){
        game_board->matrice[i] = (char*)malloc(side_size * sizeof(char));
        if (game_board->matrice == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
            for (int j = 0; j < side_size; j++){
                game_board->matrice[i][j] = ' ';
            }
        }
    } 
    return game_board;
}

/**
 * @brief Function to free the memory allocated for a game board.
 * 
 * @param game_board Pointer to the Game_board structure to free.
 */

void Free_Game_Board(Game_board *game_board){
    for (int i = 0; i < game_board->side_size; i++){
    free(game_board->matrice[i]);
    }
    free(game_board->matrice);
    free(game_board);
}

/**
 * @brief Function to create a boat with a random size and orientation.
 * 
 * @param length Length of the boat.
 * @return A pointer to the dynamically allocated Boat structure.
 */

Boat* Create_Boat2(int length) {
    Boat *boat= (Boat*)malloc(sizeof(Boat));
    if (boat == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le bateau\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    boat->direction = (rand() % 2 == 0) ? 'H' : 'V';
    boat->length = length;
    boat->position_X = -1;
    boat->position_Y = -1;
    return boat;
}


/**
 * @brief Function to generate a random number between min and max.
 * 
 * @param min Minimum value.
 * @param max Maximum value.
 * @return A random number between min and max.
 */

int Random_number(int min, int max){
    return rand() % (max - min + 1) + min;
}

/**
 * @brief Function to create an array of boats with random sizes.
 * 
 * @param num_boats Number of boats to create.
 * @return A pointer to the dynamically allocated array of Boat structures.
 */

Boat* Create_BoatsArray(int num_boats) {
    Boat *boats = (Boat*)malloc(num_boats * sizeof(Boat));
    if (boats == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau de bateaux\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_boats; ++i) {
        boats[i] = *Create_Boat2(Random_number(2, MAX_BOAT_LENGTH)); // Taille aléatoire entre 2 et MAX_BOAT_LENGTH
    }

    return boats;
}

/**
 * @brief Function to free the memory allocated for a boat.
 * 
 * @param boat Pointer to the Boat structure to free.
 */

void Free_Boat(Boat *boat){
    free(boat);
}

/**
 * @brief Function to check if a boat is still alive.
 * 
 * @param boat Pointer to the Boat structure.
 * @return True if the boat is alive, false otherwise.
 */

bool Boat_Alive(const Boat *boat){
    return (boat->length > 0);
}

/**
 * @brief Function to check if coordinates are valid.
 * 
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @param side_size Size of the game board's side.
 * @return True if coordinates are valid, false otherwise.
 */

int Valid_coordinates(int x, int y, int side_size) {
    return (x >= 0 && x < side_size && y >= 0 && y < side_size);
}

/**
 * @brief Function to check if a box has already been selected.
 * 
 * @param game_board Pointer to the Game_board structure.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return True if the box has been selected, false otherwise.
 */

int Selected_Box(const Game_board *game_board, int x, int y){
    return (game_board->matrice[x][y] == 'X' || game_board->matrice[x][y] == '0');
}

/**
 * @brief Function to randomly place boats on a game board without overlapping.
 * 
 * @param game_board Pointer to the Game_board structure.
 * @param boats Array of boats to be placed.
 * @param player 1 if placing boats for player 1, 0 for player 2.
 */

void Place_Boats(Game_board *game_board, Boat *boats, int player) {
    srand(time(NULL));
    for (int k = 0; k < NUMBER_BOATS; ++k) {
        int length = boats[k].length;
        char direction = boats[k].direction;
        // As long as the boat is not positioned, try new positions
        while (1) {
            int x, y;

            // Generate random coordinates
            x = Random_number(0, game_board->side_size - 1);
            y = Random_number(0, game_board->side_size - 1);

            // Check that the boxes required to place the boat are empty
            int valid = 1;

            if (direction == 'H') {
                for (int j = 0; j < length; ++j) {
                    if (!Valid_coordinates(x, y + j, game_board->side_size) ||
                        game_board->matrice[x][y + j] != ' ') {
                        valid = 0;
                        break;
                    }
                }
            } else if (direction == 'V') {
                for (int j = 0; j < length; ++j) {
                    if (!Valid_coordinates(x + j, y, game_board->side_size) ||
                        game_board->matrice[x + j][y] != ' ') {
                        valid = 0;
                        break;
                    }
                }
            }
            // If the required boxes are empty, place the boat and exit the loop.
            if (valid) {
                if (direction == 'H') {
                    for (int j = 0; j < length; ++j) {
                        game_board->matrice[x][y + j] = (player) ? 'B' : ' ';
                        boats[k].position_X = x;
                        boats[k].position_Y = y + j;
                    }
                } else if (direction == 'V') {
                    for (int j = 0; j < length; ++j) {
                        game_board->matrice[x + j][y] = (player) ? 'B' : ' ';
                        boats[k].position_X = x + j;
                        boats[k].position_Y = y;
                    }
                }
                break;
            }
        }
    }
}

/**
 * @brief Function to display the game board.
 * 
 * @param game_board Pointer to the Game_board structure.
 * @param player_view 1 to display player's own board, 0 to hide computer's boats.
 * @param game_started True if the game has started, false otherwise.
 * @param player_boats Array of boats for the player.
 * @param computer_boats Array of boats for the computer.
 */


void Display_Game_Board(const Game_board *game_board, int player_view, bool game_started, const Boat *player_boats, const Boat *computer_boats){
    printf("  ");
    for(int i = 0; i < game_board->side_size; ++i){
        printf("%d ", i);
    }
    printf("\n");

    for(int i = 0; i < game_board->side_size; ++i){
        printf("%c ", 'A' + i);
        for(int j = 0; j < game_board->side_size; ++j){
            char symbol = game_board->matrice[i][j];

            if (player_view) {
                // Display the player's boats on his own board
                if (symbol == 'B' && game_started && computer_boats[i].length > 0) {
                    printf("%c ", 'B');
                } else {
                    printf("%c ", symbol);
                }
            } else {
                // Hide the computer's boats on the player's board
                if (symbol == 'B' && game_started && player_boats[i].length > 0) {
                    printf("  ");
                } else {
                    printf("%c ", symbol);
                }
            }
        }
        printf("\n");
    }
}

/**
 * @brief Function to sequence a player's turn.
 * 
 * @param game_board Pointer to the Game_board structure.
 * @param player_boats Array of boats for the player.
 */

void Player_Turn(Game_board *game_board, Boat *player_boats){
    int x,y;
    printf("Please enter the (x,y) coordinates for a shot: ");
    // Check that scanf has successfully read two integers
    while (scanf("%d %d", &x, &y) != 2 || !Valid_coordinates(x, y, game_board->side_size) || Selected_Box(game_board, x, y)) {
        // Clear input buffer on error
        while (getchar() != '\n');
        // Request contact details again
        printf("Invalid details or box already checked. Please try again: ");
    }
    if(game_board->matrice[x][y] == 'B'){ // Check shooting result
        printf("HIT !\n");
        game_board->matrice[x][y] = 'X'; // Mark as touched
        for(int i = 0; i < NUMBER_BOATS; ++i){
            if(x == player_boats[i].position_X && y == player_boats[i].position_Y){ // Find the affected boat and reduce its size
                player_boats[i].length--;
                break;
            }
        }
    }
    else{
        printf("MISSED !\n");
        game_board->matrice[x][y] = '0'; // Marked as missed shot
    }
    Display_Game_Board(game_board, 1, true, player_boats, NULL); // Show tray after shooting
}

/**
 * @brief Function to sequence the computer's turn.
 * 
 * @param game_board Pointer to the Game_board structure.
 * @param computer_boats Array of boats for the computer.
 */

void Computer_Turn(Game_board *game_board, Boat *computer_boats){
    int x,y;
    srand(time(NULL)); 
    do{ // Randomly select a square where the computer has not yet drawn
        x = rand() % game_board->side_size;
        y = rand() % game_board->side_size;
    }
    while (Selected_Box(game_board, x, y));
    printf("The computer pulls in (%d,%d) : ", x, y); // Displays computer shot
    if(game_board->matrice[x][y] == 'B'){ // Check shooting result
        printf("HIT !\n");
        game_board->matrice[x][y] = 'X'; // Marked as touched
        for(int i = 0; i < NUMBER_BOATS; ++i){
            if(x == computer_boats[i].position_X && y == computer_boats[i].position_Y){ // Trouver le bateau touché et diminuer sa taille
                computer_boats[i].length--;
                break;
            }
        }
    }
    else{
        printf("MISSED !\n");
        game_board->matrice[x][y] = '0'; // Mark as missed shot
    }
    Display_Game_Board(game_board, 0, true, NULL, computer_boats); // Afficher le plateau après le tir
}

/**
 * @brief Function to get the number of boats still alive.
 * 
 * @param boats Array of boats.
 * @return Number of boats still alive.
 */

int Number_Boats_Alive(const Boat *boats) {
    int count = 0;
    for (int i = 0; i < NUMBER_BOATS; ++i) {
        if (Boat_Alive(&boats[i])) {
            count++;
        }
    }
    return count;
}

/**
 * @brief Function to check if the player has won.
 * 
 * @param player_boats Array of boats for the player.
 * @param computer_boats Array of boats for the computer.
 * @return True if the player has won, false otherwise.
 */

bool Winner_Player(const Boat *player_boats, const Boat *computer_boats) {
    bool ennemis_coules = true;  // Set to true, if an enemy boat is still alive, it will become false
    for (int i = 0; i < NUMBER_BOATS; ++i) {
        if (Boat_Alive(&computer_boats[i])) {
            ennemis_coules = false;  // An unsunken enemy ship remains
            break;  // No need to check the other enemy boats, as we already know there's at least one left.
        }
    }
    // The player wins if all enemy boats are sunk and if he has any boats left.
    return ennemis_coules && (Number_Boats_Alive(player_boats) > 0);
}

/**
 * @brief Function to check if the computer has won.
 * 
 * @param player_boats Array of boats for the player.
 * @param computer_boats Array of boats for the computer.
 * @return True if the computer has won, false otherwise.
 */

bool Winner_Computer(const Boat *player_boats, const Boat *computer_boats) {
    bool ennemis_coules = true; 
    for (int i = 0; i < NUMBER_BOATS; ++i) {
        if (Boat_Alive(&player_boats[i])) {
            ennemis_coules = false;  
            break; 
        }
    }
    return ennemis_coules && (Number_Boats_Alive(computer_boats) > 0);
}

/**
 * @brief Main function to sequence the entire game.
 */

void Play_Game(){
    Game_board *player_game_board = Create_Game_Board(GAME_BOARD_SIZE);
    Game_board *computer_game_board = Create_Game_Board(GAME_BOARD_SIZE);
    Boat *player_boats = Create_BoatsArray(NUMBER_BOATS);
    Boat *computer_boats = Create_BoatsArray(NUMBER_BOATS);
    Place_Boats(player_game_board, player_boats, 1);
    Place_Boats(computer_game_board, computer_boats, 0);
    // Display initial trays
    printf("Player's board :\n");
    Display_Game_Board(player_game_board, 1, true, player_boats, computer_boats);
    printf("\nComputer board :\n");
    Display_Game_Board(computer_game_board, 0, true, player_boats, computer_boats);
    // Main game loop
    while(1){
        Player_Turn(computer_game_board, player_boats);
        if (Winner_Player(player_boats, computer_boats)) {
            printf("Congratulations! You've won!\n");
            break;
        }
        Computer_Turn(player_game_board, computer_boats);
        if (Winner_Computer(computer_boats, player_boats)) {
            printf("Sorry, the computer won. Please try again.\n");
            break;
        }
        printf("\nPlayer's board :\n");
        Display_Game_Board(player_game_board, 1, true, player_boats, computer_boats);
        printf("\nComputer board :\n");
        Display_Game_Board(computer_game_board, 0, true, player_boats, computer_boats);
    }
    Free_Game_Board(player_game_board);
    Free_Game_Board(computer_game_board);
    Free_Boat(player_boats);
    Free_Boat(computer_boats);
}
