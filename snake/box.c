#include <ncurses.h>
#include <stdio.h>

int main(void) {

    initscr();

    int row, col;
    getmaxyx(stdscr, row, col);

    WINDOW *win = newwin(row - 5, col - 5, 1, 1);

    box(win, '|', '-');
    touchwin(win);
    wrefresh(win);
    getchar();

    endwin();
    return 0;
}
