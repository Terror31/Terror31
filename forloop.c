#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define GRID_SIZE 8
#define MINE_COUNT 10

// Define the grid structure
typedef struct {
    int8_t grid[GRID_SIZE][GRID_SIZE];
    bool game_over;
    bool game_won;
    uint8_t mines_left;
} MinesweeperGame;

// Function to initialize a new game
void minesweeper_init(MinesweeperGame *game, int8_t mine_locations[MINE_COUNT][2]) {
    // Initialize the game state
    game->game_over = false;
    game->game_won = false;
    game->mines_left = MINE_COUNT;

    // Initialize the grid with asterisks (*) to represent hidden squares
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            game->grid[i][j] = -2;  // -2 represents hidden squares
        }
    }

    // Place mines in the grid based on mine_locations
    for (int i = 0; i < MINE_COUNT; i++) {
        int x = mine_locations[i][0];
        int y = mine_locations[i][1];
        game->grid[x][y] = -1; // -1 represents mines
    }
}

// Function to reveal a square
void minesweeper_reveal_square(MinesweeperGame *game, uint8_t x, uint8_t y) {
    if (game->game_over || x >= GRID_SIZE || y >= GRID_SIZE || game->grid[x][y] != -2) {
        return;
    }

    // Calculate the number of adjacent mines
    int8_t adjacent_mines = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                if (game->grid[nx][ny] == -1) {
                    adjacent_mines++;
                }
            }
        }
    }

    game->grid[x][y] = adjacent_mines;

    // Check if the game is won
    game->mines_left--;

    if (adjacent_mines == 0) {
        // If the revealed square has no adjacent mines, recursively reveal its neighbors
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                    minesweeper_reveal_square(game, nx, ny);
                }
            }
        }
    }

    // Check if the game is won
    if (game->mines_left == 0) {
        game->game_over = true;
        game->game_won = true;
    }
}

// Function to check if the game is over
bool minesweeper_is_game_over(MinesweeperGame *game) {
    return game->game_over;
}

// Function to check if the game is won
bool minesweeper_is_game_won(MinesweeperGame *game) {
    return game->game_won;
}

// Function to get the game grid
int8_t minesweeper_get_square(MinesweeperGame *game, uint8_t x, uint8_t y) {
    return game->grid[x][y];
}

// Function to get the remaining mines count
uint8_t minesweeper_get_mines_left(MinesweeperGame *game) {
    return game->mines_left;
}

// Function to display the game grid
void minesweeper_display_grid(MinesweeperGame *game) {
    printf("Minesweeper Grid:\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (game->grid[i][j] == -2) {
                printf("* ");
            } else if (game->grid[i][j] == -1) {
                printf(". ");
            } else if (game->grid[i][j] == 0) {
                printf("  "); // Empty square
            } else {
                printf("%d ", game->grid[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int8_t mine_locations[MINE_COUNT][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 1}, {0, 0}, {2, 7}, {4, 3}, {6, 5}, {3, 0}, {7, 7}};
    MinesweeperGame game;

    minesweeper_init(&game, mine_locations);

    while (!minesweeper_is_game_over(&game) && !minesweeper_is_game_won(&game)) {
        minesweeper_display_grid(&game);

        printf("Enter the coordinates to reveal (row column): ");
        uint8_t x, y;
        scanf("%hhu %hhu", &x, &y);

        if (x < GRID_SIZE && y < GRID_SIZE) {
            minesweeper_reveal_square(&game, x, y);
        }
    }

    minesweeper_display_grid(&game);

    if (minesweeper_is_game_won(&game)) {
        printf("Congratulations! You won!\n");
    } else {
        printf("Game Over. You hit a mine!\n");
    }

    return 0;
}
