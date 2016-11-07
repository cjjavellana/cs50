#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

#include "snake.h"
#include "pivot_point.h"

int main(int argc, char *argv[])
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

    gameplay *g = malloc(sizeof(gameplay));
    g->s = s;
    g->pivot = pivot1;
    g->world_width = (short) col;
    g->world_height = (short) row;
    g->speed = 1.0f;

    pthread_t pth;
    pthread_create(&pth, NULL, *snake_main, g);

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
    
    // set the condition to exit thread loop
    g->s->head_coord.x = 255;

    pthread_join(pth, NULL);

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
