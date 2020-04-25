/**
 * Ygor Sad Machado
 * NUSP: 8910368
 *
 * EP 1 - Part 1
 * This part is responsible of finding the roots of a function
 * using an implementation of the fixed-point iteration method
 */
#include <float.h>
#include <math.h>
#include <stdio.h>

/**
   Definition of the main function whose roots we want
   to determine

   @parameters
   - x: the x which we want to evaluate f

   @returns the value of f on that point
**/
double f (double x) {
  return exp(x) - 2 * pow(x, 2);
}

/**
   Definition of the derivative of f. This is an auxiliary
   function used by g
**/
double df (double x) {
  return exp(x) - 4 * x;
}

/**
  Definition of our auxiliary function g(x)

  @parameters
  - x: the current x_k for which we have to evaluate g

  @returns the next value for x, ie, x_{k+1}
**/
double g (double x) {
  return x - f(x) / df(x);
}

/**
   Function that actually executes the fixed-point numeric method.
   It recursively evaluates f for a given x and check whether this
   value is close enough to zero - considering the precision received
   as argument. If so, returns the received x. Otherwise, calls itself
   again using the next x, which is evaluated using g.

   @parameters
   - current_x: the current x_k which we suspect might be the root of f
   - precision: the desired range of zero within which our root must be.

   @returns the value of root
**/
double fixed_point_method (double current_x, double precision) {
  if (fabs(f(current_x)) <= precision) {
    return current_x;
  }

  return fixed_point_method(g(current_x), precision);
}

/**
   Function that encapsulates the process of finding a single root,
   using the fixed-point method, and outputting it.

   @parameters:
   - guess: an initial x that we know is close to one of our roots.

   @returns nothing.
**/
void find_root_around (double guess) {
  double root;
  double precision = pow(10, -10);

  printf("==========================\n\n");
  printf("=> initial x: %lf\n", guess);
  printf("=> precision: %e\n", precision);
  printf("\n");

  root = fixed_point_method(guess, precision);

  printf("=> root: %lf\n\n", root);
}

int main() {
  find_root_around(0.0);
  find_root_around(1.0);
  find_root_around(3.0);

  return 0;
}
