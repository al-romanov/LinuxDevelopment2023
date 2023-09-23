#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

void try_print_error(const char *msg) {
  int fputs_res = fputs(msg, stderr);
  if (fputs_res == EOF) {
    endwin();
    exit(2);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    try_print_error("Usage: Show FILE\n\tFILE -- file name to open\n");
    return 1;
  }
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    try_print_error("Show: couldn't open file ");
    try_print_error(argv[1]);
    try_print_error("\n");
    return 1;
  }

  WINDOW *win = NULL;
  initscr();
  noecho();
  cbreak();
  int WIN_HEIGHT = LINES - 2;
  int WIN_WIDTH = COLS - 2;
  win = newwin(WIN_HEIGHT, WIN_WIDTH, 1, 1);
  scrollok(win, true);
  wmove(win, 1, 1);
  box(win, 0, 0);
  printw("File: %.50s", argv[1]);
  refresh();
  int current_line_number = 1;
  int MAX_LINE_LENGTH = WIN_WIDTH - 8;
  char *current_line = (char *)calloc(MAX_LINE_LENGTH + 1, 1);
  int c;
  while ((c = wgetch(win)) != 27) {
    if (c != ' ') {
      continue;
    }
    char *line = fgets(current_line, MAX_LINE_LENGTH + 1, file);
    if (!line) {
      continue;
    }
    wprintw(win, "%4d: %.*s", current_line_number, MAX_LINE_LENGTH, line);
    size_t line_length = strlen(line);
    while (line_length == MAX_LINE_LENGTH && current_line[line_length - 1] != '\n') {
      wprintw(win, "\n");
      line = fgets(current_line, MAX_LINE_LENGTH + 1, file);
      if (!line) {
        break;
      }
      int cursor_pos_x, cursor_pos_y;
      getyx(win, cursor_pos_y, cursor_pos_x);
      wmove(win, cursor_pos_y, 1);
      wprintw(win, "      %.*s", MAX_LINE_LENGTH, line);
      line_length = strlen(line);
    }
    int cursor_pos_x, cursor_pos_y;
    getyx(win, cursor_pos_y, cursor_pos_x);
    wmove(win, cursor_pos_y, 1);
    box(win, 0, 0);
    ++current_line_number;
  }
  delwin(win);
  fclose(file);
  endwin();
  return 0;
}
