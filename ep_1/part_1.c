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
   An auxiliary struct that holds the result of a single execution
   of the fixed-point method.
*/
struct iteration_result {
  double root;
  int iterations_count;
  int has_converged;
};


/**
   Definition of the main function whose roots we want
   to determine.

   @parameters
   - x: the x which we want to evaluate f.

   @returns the value of f on that point.
**/
double f (double x) {
  return exp(x) - 2 * pow(x, 2);
}


/**
   Definition of the derivative of f. This is an auxiliary
   function used by g.

   @parameters
   -x: the x to evaluate the derivative at.

   @returns the value of df(x).
**/
double df (double x) {
  return exp(x) - 4 * x;
}


/**
  Definition of our auxiliary function g(x).

  @parameters
  - x: the current x_k for which we have to evaluate g.

  @returns the next value for x, ie, x_{k+1}.
**/
double g (double x) {
  return x - f(x) / df(x);
}


/**
   This function performs the fixed-method iterative method on top of a
   given initial guess for x. It is capable of determining whether the
   iteration converged or not. Also it is limited to a maximun number of
   iterations until it safely infers the convergence failed.

   @parameters
   - start_x: a number representing an initial guess to our desired root.
   - precision: a number saying how close f(x) should be of zero.
   - max_iterations: the maximum amount of iterations the method can take.

   @returns an iteration_result struct containing the probable located root,
            the number of iterations if took to find it, and a flag saying
            whether the iteration converged or not.
**/
struct iteration_result fixed_point_method (double start_x, double precision, int max_iterations) {
  struct iteration_result result;
  double current_x = start_x;
  int iterations = 0;

  /**
    We keep on iterating until f(current_x) gets really close to zero or
    our allowed iterations are exhausted
  */
  while ((iterations <= max_iterations) && (fabs(f(current_x)) > precision)) {
    current_x = g(current_x);
    iterations++;
  }

  result.root = current_x;
  result.iterations_count = iterations;
  result.has_converged = (!isnan(current_x) && (iterations <= max_iterations));

  return result;
}


/**
   Function that encapsulates the process of finding a single root,
   using the fixed-point method, and outputting it.

   @parameters:
   - guess: an initial x that we know is close to one of our roots.
   - precision: the current precision to use with the method.
   - max_iterations: the maximum allowed number of iterations to use.

   @returns nothing.
**/
void find_root_around (double guess, double precision, int max_iterations) {
  struct iteration_result result;

  printf("=> initial x: %.10lf\n", guess);

  result = fixed_point_method(guess, precision, max_iterations);

  if (result.has_converged) {
    printf("=> root: %.10lf\n", result.root);
    printf("=> elapsed iterations: %d\n\n", result.iterations_count);
  } else {
    printf("=> the method has not converged\n");
    printf("=> elapsed iterations: %d\n\n", result.iterations_count);
  }
}


/**
   Helper functionthat simply prints a header within blocks of tests.

   @parameters
   - precision: the current precision to display.
   - max_iterations: the maximum allowed number of iterations to display.

   @returns nothing.
*/
void print_header (double precision, int max_iterations) {
  printf("==========================\n\n");
  printf(" Assuming precision %.10lf and at most %d iterations: \n\n", precision, max_iterations);
}


int main() {
  double precision = 10E-10;
  int max_iterations;

  /**
    Success iterations starting close to the roots
  */
  max_iterations = 100;

  print_header(precision, max_iterations);
  find_root_around(0.0, precision, max_iterations);
  find_root_around(1.0, precision, max_iterations);
  find_root_around(3.0, precision, max_iterations);

  /**
    Sucess iterations starting far from the roots
  */
  max_iterations = 100;

  print_header(precision, max_iterations);
  find_root_around(35.0, precision, max_iterations);
  find_root_around(-2777.0, precision, max_iterations);
  find_root_around(-100320524.0, precision, max_iterations);
  find_root_around(-55555555555.0, precision, max_iterations);

  max_iterations = 1000;

  print_header(precision, max_iterations);
  find_root_around(99.0, precision, max_iterations);
  find_root_around(467.0, precision, max_iterations);

  /**
    Failed iterations
  */
  max_iterations = 100;

  print_header(precision, max_iterations);
  find_root_around(99.0, precision, max_iterations);
  find_root_around(467.0, precision, max_iterations);

  max_iterations = 10E6;

  print_header(precision, max_iterations);
  find_root_around(3751.0, precision, max_iterations);
  find_root_around(5400.0, precision, max_iterations);

  return 0;
}
