#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NUM_PAWNS = 5;
const int NUM_COLORS = 8;
const int NUM_ATTEMPTS = 10;

enum color_t { RED, GREEN, BLUE, YELLOW, BLACK, WHITE, GRAY, PURPLE };

void read_proposed_combination(enum color_t board[]) {
    printf("Enter your proposed combination (use numbers 0 to 7 for colors):\n");
    for (int i = 0; i < NUM_PAWNS; ++i) {
        int pawn;
        printf("Pawn %d: ", i + 1);
        scanf("%d", &pawn);
        board[i] = (enum color_t)pawn;
    }
}

void evaluate_proposed_combination(
    enum color_t hidden_combination[],
    enum color_t proposed_combination[],
    int* num_well_placed_pawns,
    int* num_misplaced_pawns) {
    *num_well_placed_pawns = 0;
    *num_misplaced_pawns = 0;

    int hidden_used[NUM_PAWNS];
    int proposed_used[NUM_PAWNS];

    for (int i = 0; i < NUM_PAWNS; ++i) {
        hidden_used[i] = 0;
        proposed_used[i] = 0;
    }

    for (int i = 0; i < NUM_PAWNS; ++i) {
        if (proposed_combination[i] == hidden_combination[i]) {
            (*num_well_placed_pawns)++;
            hidden_used[i] = 1;
            proposed_used[i] = 1;
        }
    }

    for (int i = 0; i < NUM_PAWNS; ++i) {
        for (int j = 0; j < NUM_PAWNS; ++j) {
            if (!hidden_used[i] && !proposed_used[j] && proposed_combination[j] == hidden_combination[i]) {
                (*num_misplaced_pawns)++;
                hidden_used[i] = 1;
                proposed_used[j] = 1;
                break;
            }
        }
    }
}

void generate_hidden_combination(enum color_t hidden_combination[]) {
    srand(time(NULL));
    for (int i = 0; i < NUM_PAWNS; ++i) {
        hidden_combination[i] = (enum color_t)(rand() % NUM_COLORS);
    }
}

void game() {
    enum color_t hidden_combination[NUM_PAWNS];
    enum color_t proposed_combination[NUM_PAWNS];
    int num_well_placed_pawns, num_misplaced_pawns;
    int attempts = 0;

    generate_hidden_combination(hidden_combination);

    while (attempts < NUM_ATTEMPTS) {
        read_proposed_combination(proposed_combination);
        evaluate_proposed_combination(hidden_combination, proposed_combination, &num_well_placed_pawns, &num_misplaced_pawns);

        printf("Well-placed pawns: %d\n", num_well_placed_pawns);
        printf("Misplaced pawns: %d\n", num_misplaced_pawns);

        if (num_well_placed_pawns == NUM_PAWNS) {
            printf("Congratulations! You guessed the combination!\n");
            break;
        }

        attempts++;
        printf("Attempts left: %d\n", NUM_ATTEMPTS - attempts);
    }

    if (attempts == NUM_ATTEMPTS) {
        printf("Game over. The hidden combination was:");
        for (int i = 0; i < NUM_PAWNS; ++i) {
            printf(" %d", hidden_combination[i]);
        }
        printf("\n");
    }
}

int main() {
    game();
    return 0;
}
