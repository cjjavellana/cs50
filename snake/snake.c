#include <stdio.h>
#include "snake.h"
/**
 * Returns true (1) if the head of the snake is 
 * on the same coordinates as the food. 
 *
 * False if otherwise.
 */
int is_eating(const snake *s, food *food)
{
    if(s->head_coord.x == food->coord.x
            && s->head_coord.y == food->coord.y)
    {
        return 1;
    }

    return 0;
}

void move_head(snake *s)
{
    switch(s->direction)
    {
        case DIRECTION_UP:
            s->head_coord.x = s->head_coord.x + 1;
            break;
        case DIRECTION_DOWN:
            s->head_coord.x = s->head_coord.x - 1;
            break;
        case DIRECTION_LEFT:
            s->head_coord.y = s->head_coord.y - 1;
            break;
        case DIRECTION_RIGHT:
            s->head_coord.y = s->head_coord.y + 1;
            break;
    }
}

