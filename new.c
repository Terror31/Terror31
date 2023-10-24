#include <stdio.h>
#include <stdbool.h>

#define GRID_SIZE 8
#define NUM_MINES 10

typedef struct {
    bool is_mine;
    bool is_cleared;
} Cell;

typedef struct {
    Cell grid[GRID_SIZE][GRID_SIZE];
    bool is_game_over;
    bool is_won;
} MinesweeperGame;

void printGrid(MinesweeperGame *game) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (game->grid[i][j].is_cleared) {
                if (game->grid[i][j].is_mine) {
                    printf("X ");
                } else {
                    printf("  ");
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void initGame(MinesweeperGame *game, int mine_locations[NUM_MINES][2]) {
    game->is_game_over = false;
    game->is_won = false;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            game->grid[i][j].is_mine = false;
            game->grid[i][j].is_cleared = false;
        }
    }

    for (int i = 0; i < NUM_MINES; i++) {
        int row = mine_locations[i][0];
        int col = mine_locations[i][1];
        game->grid[row][col].is_mine = true;
    }
}

void clearCell(MinesweeperGame *game, int row, int col) {
    if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE || game->is_game_over) {
        return;
    }

    if (game->grid[row][col].is_cleared) {
        return;
    }

    game->grid[row][col].is_cleared = true;

    if (game->grid[row][col].is_mine) {
        game->is_game_over = true;
        game->is_won = false;
    } else {
        int cleared_cells = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (game->grid[i][j].is_cleared) {
                    cleared_cells++;
                }
            }
        }
        if (cleared_cells == GRID_SIZE * GRID_SIZE - NUM_MINES) {
            game->is_game_over = true;
            game->is_won = true;
        }
    }
}

int main() {
    MinesweeperGame game;
    int mine_locations[NUM_MINES][2] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {0, 7}, {7, 0}};

    initGame(&game, mine_locations);

    // Print the initial state
    printf("Initial state:\n");
    printGrid(&game);

    // Clear cells (example moves)
    clearCell(&game, 2, 3);
    clearCell(&game, 4, 4);

    // Print the updated state
    printf("Updated state:\n");
    printGrid(&game);

    // Check if the game is won or lost
    if (game.is_game_over) {
        if (game.is_won) {
            printf("Congratulations! You won!\n");
        } else {
            printf("Game over. You lost!\n");
        }
    }

    return 0;
}
