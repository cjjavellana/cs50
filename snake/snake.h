#include <stdio.h>

#include "point.h"

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4

#define INITIAL_LENGTH 3

typedef struct {
    point coord;
} food;

typedef struct {
   point head_coord;
   int body_length;
   int direction;
} snake;

typedef struct {
  int min_y;
  int max_x;
  int max_y;
} world;

typedef struct {
    snake *s;
    struct pivot_point *pivot;
    short world_width;
    short world_height;
    float speed;
} gameplay;

/**
 * Returns true (1) if the head of the snake is 
 * on the same coordinates as the food. 
 *
 * False if otherwise.
 */
int snake_is_eating(const snake *s, food *food);

/**
 * Moves the snake 1px in the direction indicated by s->direction.
 */
void snake_move_head(snake *s);

/**
 * A function that coordinates the snake's movements
 */
void *snake_main(void *args);

