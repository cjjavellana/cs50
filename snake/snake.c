#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>

#include "snake.h"
#include "pivot_point.h"

static void update_coordinates(const int direction, int *x, int *y)
{
    switch(direction)
    {
        case DIRECTION_RIGHT:
            *x = *x - 1;
            break;
        case DIRECTION_LEFT:
            *x = *x + 1;;
            break;
        case DIRECTION_UP:
            *y = *y + 1;
            break;
        case DIRECTION_DOWN:
            *y = *y - 1;
            break;
    }
}

/**
 * Returns true (1) if the head of the snake is 
 * on the same coordinates as the food. 
 *
 * False if otherwise.
 */
int snake_is_eating(const snake *s, food *food)
{
    if(s->head_coord.x == food->coord.x
            && s->head_coord.y == food->coord.y)
    {
        return 1;
    }

    return 0;
}

void snake_move_head(snake *s)
{
    switch(s->direction)
    {
        case DIRECTION_UP:
            s->head_coord.y = s->head_coord.y - 1;
            break;
        case DIRECTION_DOWN:
            s->head_coord.y = s->head_coord.y + 1;
            break;
        case DIRECTION_LEFT:
            s->head_coord.x = s->head_coord.x - 1;
            break;
        case DIRECTION_RIGHT:
            s->head_coord.x = s->head_coord.x + 1;
            break;
    }
}

/**
 * Manages snake's gameplay. i.e. Drawing borders, advancing snake movement, etc
 */
void *snake_main(void *args)
{
    gameplay *game = (gameplay *) args;
    snake *s = game->s;

    while(s->head_coord.x < game->world_width) 
    {
        int x = s->head_coord.x;
        int y = s->head_coord.y;
        int direction = s->direction;

        mvprintw(0, 0, "Max rows: %d; Max Cols: %d\n", game->world_height, game->world_width);
        mvprintw(1, 0, "Current row: %d; Current Col: %d\n", y, x);    
        mvprintw(2, 0, "Current direction: %d;", direction);

        for(int i = 0; i < s->body_length + 1; i++)
        {
            if(i == 0) mvprintw(y, x, "%s", "Q");
            else  mvprintw(y, x, "%s", "X");

            pivot_point *pp = game->pivot;
            while(pp != NULL)
            {
                if(x == pp->coord.x && 
                        y == pp->coord.y)
                {
                    s->direction = pp->pivot_direction;
                    switch(pp->previous_direction)
                    {
                        case DIRECTION_RIGHT:
                            direction = DIRECTION_LEFT;
                            break;
                        case DIRECTION_LEFT:
                            direction = DIRECTION_RIGHT;
                            break;
                        case DIRECTION_UP:
                            direction = DIRECTION_DOWN;
                            break;
                        case DIRECTION_DOWN:
                            direction = DIRECTION_UP;
                            break;
                    }
                    
                    //delete the pivot point if the tail has passed
                    //through it
                    if(i == (s->body_length))
                    {
                        if(pp->previous != NULL)
                        {
                        //    pp->previous->next = NULL;
                        }

                        //free(pp);
                        break;
                    }
                }

                pp = pp->next;
            }

            update_coordinates(direction, &x, &y);
        }
        refresh();
        sleep(1);

        snake_move_head(s);
        clear();
    }

    return NULL;
}

