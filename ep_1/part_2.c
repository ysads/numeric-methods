/**
 * Ygor Sad Machado
 * NUSP: 8910368
 *
 * EP 1 - Part 2
 * This part intends to implement the Newton Basins for
 * a given function f
 */
#include <complex.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

#define MAX_ITERATIONS 100
#define TOLERANCE 1E-8

/**
   Simple helper function that converts a complex double result
   coming from newton method into a discrete integer, easier to plot.

   @parameters
   - z: a result of newton method applied to any arbitrary point.

   @returns a constant ranging 1 to N - in which N is the number of
            distinct roots of f - represeting either a root on the
            lack of convergence.
 */
int output_for (double complex z) {
  int output;
  double complex values[6] = { -1,
                               1,
                               -0.80902 - 0.58779 * I,
                               -0.80902 + 0.58779 * I,
                               0.30902 - 0.95106 * I,
                               0.30902 + 0.95106 * I };

  /**
   * Note that the value at index 0 is not valid. This happens because gnuplot
   * does not allow assigning 0 to a valid color. Thus having this output could
   * cause issues.
   */
  for (output = 1; output < 4; output++) {
    /**
     * Due to floating-point precision issues, we can not use ==
     * operator here. Hence we evaluate proximity between two values
     * using absolute value
     */
    if (cabs(z - values[output]) < 1E-2) {
      return output;
    }
  }
  return 4;
}


/**
  Evaluates the f function at a given point in complex plane

  @parameters
  - z: the point in which the function will be evaluated.

  @returns the value of f(z).
 */
double complex eval_f (double complex z) {
  return cpow(z, 5) - 1;
}


/**
  Evaluates the derivative of f in a given point in complex plane.

  @parameters
  - z: the point in which the derivative will be evaluated.

  @returns the value of df(z).
 */
double complex eval_df (double complex z) {
  return 5 * cpow(z, 4);
}


/**
  Executes the newton method using the given z as the start point.

  @parameters
  - z: the starting point for newton method.

  @returns the result of newton method applied to z, being either a valid root
           of function f or DBL_MIN, if the method does not converge.
 */
double complex newton (double complex z) {
  int elapsed_iterations;
  complex double curr_z;
  complex double f_z, df_z;

  /**
   * We start the process using the given z.
   */
  curr_z = z;
  elapsed_iterations = 0;

  while (elapsed_iterations < MAX_ITERATIONS) {
    f_z = eval_f(curr_z);
    df_z = eval_df(curr_z);

    /**
     * In case the current f(z) value is already within our tolerance
     * range from the origin, we have can safely return the current z
     * value, since it fits as a valid root.
     */
    if (cabs(f_z) <= TOLERANCE) {
      return curr_z;
    }

    /**
     * Otherwise, we evaluate the next value for z using the values
     * of f(z) and df(z). Also, we increase the iterations counter.
     */
    curr_z = curr_z - (f_z / df_z);
    elapsed_iterations++;
  }

  /**
   * If this return is reach, then the newton's method does not
   * converge for this z. To differentiate this from a valid root,
   * we return the infinity constant.
   */
  return (double complex) DBL_MIN;
}


/**
   Generates the newton basins by iterating over an area of the complex
   plane and applying the newton method for each point in this section.

   @parameters:
   - l: the lowermost boundary on the complex plane (for real and imaginary axis).
   - u: the highermost boundary on the complex plane (for real and imaginary axis).
   - p: the number of points in which every axis will be split.

   @returns nothing.
 */
void newton_basins (int l, int u, int p) {
  FILE *output;
  double re_z, im_z;
  double step;
  double complex z;

  output = fopen("output.txt", "w");

  /**
   * The step states how much we increment the coordinates on each
   * iteration on the complex plane
   */
  step = 1.0 * (u - l) / p;

  /**
   * We iterate over the given section of the complex plane using
   * step value we have just evaluated
   */
  for (re_z = l; re_z <= u; re_z += step) {
    for (im_z = l; im_z <= u; im_z += step) {
      z = re_z + I * im_z;

      /**
       * Outputs the discretization of the newton method into the output
       * file. This process helps choosing colors to plot the basins later
       */
      fprintf(output, "%lf\t%lf\t%d\n", re_z, im_z, output_for(newton(z)));
    }
  }

  fclose(output);
}

int main () {
  newton_basins(-2, 2, 200);

  return 0;
}
