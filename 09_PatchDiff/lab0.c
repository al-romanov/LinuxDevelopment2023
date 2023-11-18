#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_lab_template() {
  enum { SIDE_LEN = 13 };
  char *lab = calloc(SIDE_LEN * SIDE_LEN, sizeof(*lab));
  for (size_t i = 0; i < SIDE_LEN; ++i) {
    for (size_t j = 0; j < SIDE_LEN; ++j) {
      if (i % 2 == 0 || j % 2 == 0) {
        lab[i * SIDE_LEN + j] = '#';
      } else {
        lab[i * SIDE_LEN + j] = '.';
      }
    }
  }
  return lab;
}

size_t get_neighbour(size_t cell, size_t n) {
  assert(n < 4 && "Expecting n to be less than 4");
  enum { LAB_SIZE = 6 };
  switch (n) {
  case 0:
    cell -= cell > LAB_SIZE ? LAB_SIZE : 0;
    break;
  case 1:
    cell += cell % LAB_SIZE + 1 != LAB_SIZE ? 1 : 0;
    break;
  case 2:
    cell += cell < LAB_SIZE * (LAB_SIZE - 1) ? LAB_SIZE : 0;
    break;
  case 3:
    cell -= cell % LAB_SIZE != 0 ? 1 : 0;
    break;
  }
  return cell;
}

void print_lab(char *lab) {
  enum { SIDE_LEN = 13 };
  for (size_t i = 0; i < SIDE_LEN; ++i) {
    printf("%.*s\n", SIDE_LEN, lab + i * SIDE_LEN);
  }
}

char *mutate_lab(char *lab_template) {
  enum { LAB_SIZE = 6 };
  size_t visited_size = 0;
  unsigned char visited[LAB_SIZE * LAB_SIZE];
  memset(visited, 0, sizeof(visited));
  size_t work_list_size = 0;
  size_t work_list[LAB_SIZE * LAB_SIZE];
  size_t current_cell = rand() % (LAB_SIZE * LAB_SIZE);
  visited[current_cell] = 1;
  ++visited_size;
  while (visited_size != LAB_SIZE * LAB_SIZE) {
    size_t neighbour_num = rand() % 4;
    size_t neighbour_cell;
    for (int i = 0; i < 4; ++i) {
      neighbour_cell = get_neighbour(current_cell, neighbour_num);
      if (!visited[neighbour_cell])
        break;
      neighbour_num = (neighbour_num + 1) % 4;
    }
    if (!visited[neighbour_cell]) {
      work_list[work_list_size++] = current_cell;
      int lab_wall_idx_diff;
      switch (neighbour_num) {
        case 0: lab_wall_idx_diff = -(2 * LAB_SIZE + 1); break;
        case 1: lab_wall_idx_diff = 1; break;
        case 2: lab_wall_idx_diff = 2 * LAB_SIZE + 1; break;
        case 3: lab_wall_idx_diff = -1; break;
      }
      size_t lab_row = current_cell / LAB_SIZE * 2 + 1;
      size_t lab_column = current_cell % LAB_SIZE * 2 + 1;
      lab_template[(2 * LAB_SIZE + 1) * lab_row + lab_column + lab_wall_idx_diff] = '.';
      current_cell = neighbour_cell;
      visited[neighbour_cell] = 1;
      ++visited_size;
    } else if (work_list_size != 0)
      current_cell = work_list[--work_list_size];
    else {
      size_t search_start = rand() % (LAB_SIZE * LAB_SIZE);
      current_cell = search_start;
      do {
        if (!visited[current_cell])
          break;
        current_cell = (current_cell + 1) % (LAB_SIZE * LAB_SIZE);
      } while (current_cell != search_start);
      assert(current_cell != search_start &&
             "There is no way we search for not visited!");
      visited[current_cell] = 1;
      ++visited_size;
    }
  }
  return lab_template;
}

int main() {
  enum { SIDE_LEN = 13 };
  char *lab = create_lab_template();
  lab = mutate_lab(lab);
  print_lab(lab);
  free(lab);
  return 0;
}
