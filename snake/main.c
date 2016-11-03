#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

#include "snake.h"
#include "pivot_point.h"

static void update_coordinates(const int direction, int *x, int *y);

int main(void)
{
    //int delay_msec = 1000; // 1 sec delay
    
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    int row, col;
    getmaxyx(stdscr, row, col);

    snake *s = malloc(sizeof(snake));
    s->head_coord.x = col - 10;
    s->head_coord.y = 3;
    s->body_length = 5;
    s->direction = DIRECTION_RIGHT;

    pivot_point *pivot1 = malloc(sizeof(pivot_point));
    pivot1->coord.x = col - 1;
    pivot1->coord.y = 3;
    pivot1->pivot_direction = DIRECTION_DOWN;
    pivot1->previous_direction = DIRECTION_LEFT;

    pivot_point *pivot2 = malloc(sizeof(pivot_point));
    pivot2->coord.x = col - 1;
    pivot2->coord.y = row - 1;
    pivot2->pivot_direction = DIRECTION_LEFT;
    pivot2->previous_direction = DIRECTION_UP;
    pivot2->previous = pivot1;

    pivot_point *pivot3 = malloc(sizeof(pivot_point));
    pivot3->coord.x = 1;
    pivot3->coord.y = row - 1;
    pivot3->pivot_direction = DIRECTION_UP;
    pivot3->previous_direction = DIRECTION_RIGHT;
    pivot3->previous = pivot2;
    
    pivot_point *pivot4 = malloc(sizeof(pivot_point));
    pivot4->coord.x = 1;
    pivot4->coord.y = 3;
    pivot4->pivot_direction = DIRECTION_RIGHT;
    pivot4->previous_direction = DIRECTION_DOWN;
    pivot4->previous = pivot3;

    pivot1->next = pivot2;
    pivot2->next = pivot3;
    pivot3->next = pivot4;

    while(s->head_coord.x < col)
    {
        int x = s->head_coord.x;
        int y = s->head_coord.y;
        int direction = s->direction;

        mvprintw(0, 0, "Max rows: %d; Max Cols: %d\n", row, col);    
        mvprintw(1, 0, "Current row: %d; Current Col: %d\n", y, x);    
        mvprintw(2, 0, "Current direction: %d;", direction);    

        for(int i = 0; i < s->body_length + 1; i++)
        {
            if(i == 0) mvprintw(y, x, "%s", "Q");
            else  mvprintw(y, x, "%s", "X");

            pivot_point *pp = pivot1;
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
                    if(i == (s->body_length - 1))
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

        switch(s->direction)
        {
            case DIRECTION_RIGHT:
                s->head_coord.x = s->head_coord.x + 1;
                break;
            case DIRECTION_LEFT:
                s->head_coord.x = s->head_coord.x - 1;
                break;
            case DIRECTION_UP:
                s->head_coord.y = s->head_coord.y - 1;
                break;
            case DIRECTION_DOWN:
                s->head_coord.y = s->head_coord.y + 1;
                break;
        }

        clear();
    }

    int c;
    while((c = getch()) != 'q')
    {
        switch(c)
        {
            case KEY_UP:
                printw("Up\n");
                break;
            case KEY_DOWN:
                printw("Down\n");
                break;
            case KEY_RIGHT:
                printw("Right\n");
                break;
            case KEY_LEFT:
                printw("Left\n");
                break;
       }
    }

    free(s);

    while(pivot1 != NULL)
    {
        pivot_point *tmp = pivot1->next;
        free(pivot1);
        pivot1 = tmp;
    }

    endwin();

    return 0;
}

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
