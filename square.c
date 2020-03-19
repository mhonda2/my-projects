#include <stdio.h>
#include <stdlib.h>


//------ POINT ----------------------------------------------------------------
typedef struct point point;
struct point { double x, y; };
//------ SQUARE -----------------------------------------------------------------
typedef struct square square;
struct square { point ul; size_t side; };
square* square_init(double ulx, double uly, double side) // TODO
{
  square* square = malloc(sizeof (square));
  square->ul.x = ulx;
  square->ul.y = uly;
  square->side = side;

  return square;
}
void square_delete(square* sq) // TODO
{
  free(sq);
}
void square_move(square* sq, double x, double y) // TODO
{
  sq->ul.x = x;
  sq->ul.y = y;
}
void square_expandby(square* sq, double expandby) // TODO
{
  sq->ul.x -= (expandby / 2);
  sq->ul.y += (expandby / 2);
  sq->side += expandby;
}
double square_area(square* sq) // TODO
{
  return sq->side * sq->side;
}
double square_perimeter(square* r) // TODO
{
  return 4.0 * r->side;
}
// print location, side, area and perimeter
void square_print(const char* msg, square* sq) // TODO
{
  printf("%s (%.2f, %.2f)\n", msg, sq->ul.x, sq->ul.y);
}
void test_square(double ulx, double uly, double side) {
 square* sq = square_init(ulx, uly, side);
 square_print("sq is: ", sq);
 square_move(sq, 2, 2);
 square_print("sq is now: ", sq);
 square_expandby(sq, 10);
 square_print("sq has expanded to: ", sq);
 printf("sq has area: %.2f\n", square_area(sq));
 square_delete(sq);
 printf("\n\n");
}
void tests_square() {
 test_square(0, 0, 10);
 test_square(1, 1, 5);
 // add other tests if you wish // TODO (optional)
}
int main(int argc, const char* argv[]) {
 tests_square();
 return 0;
}
