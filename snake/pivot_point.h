
typedef struct pivot_point {
  point coord;
  struct pivot_point *next;
  struct pivot_point *previous;
  int pivot_direction;
  int previous_direction;
} pivot_point;

