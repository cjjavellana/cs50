#define _BSD_SOURCE

#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    struct timespec tim;
    tim.tv_sec  = 0;
    tim.tv_nsec = 500000000L;

    while(s->head_coord.x < game->world_width) 
    {
        int x = s->head_coord.x;
        int y = s->head_coord.y;
        int direction = s->direction;

        // draw border - x axis
        for(int i = 0; i <= game->world_width; i++)
        {
           move(2,i);
           addch(ACS_HLINE);
           
           move(game->world_height - 1, i);
           addch(ACS_HLINE);
        }

        for(int i = 2; i <= game->world_height - 1; i++)
        {
           move(i, 0);
           addch(ACS_VLINE);

           move(i, game->world_width - 1);
           addch(ACS_VLINE);
        }

        mvprintw(0, 0, "Max rows: %d; Max Cols: %d\n", game->world_height, game->world_width);
        mvprintw(1, 0, "Current row: %d; Current Col: %d\n", y, x);    

        for(int i = 0; i < s->body_length + 1; i++)
        {
            move(y,x);
            addch(ACS_CKBOARD);

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
                    if(i == s->body_length)
                    {
                        mvprintw(2, 0, "Deleting: %d, %d;", pp->coord.x, pp->coord.y);
                        if(pp->previous != NULL && pp->next != NULL)
                        {
                            pp->previous->next = pp->next;
                            pivot_point *tmp = pp->next;
                            free(pp);
                            pp = tmp;
                        }
                        else if (pp->previous == NULL && pp->next != NULL)
                        {
                           game->pivot = pp->next;

                           pivot_point *tmp = pp->next;
                           free(pp);
                           pp = tmp;
                        }
                        else if(pp->previous != NULL && pp->next == NULL)
                        {
                            pp->previous->next = NULL;

                            pivot_point *tmp = pp->previous;
                            free(pp);
                            pp = tmp;
                        }

                        break;
                    }
                }

                pp = pp->next;
            }

            update_coordinates(direction, &x, &y);
        }
        refresh();
        nanosleep(&tim, NULL);

        snake_move_head(s);
        clear();
    }

    // set game over bit
    game->gameover = 0x1; 
    return NULL;
}

