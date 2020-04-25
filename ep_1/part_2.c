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
 * Simple helper function that converts a complex double result
 * coming from newton method into a discrete integer, easier to plot
 */
int output_for (double complex z) {
  int output;
  double values[3] = {-1.879385, 0.347296, 1.532089};

  for (output = 0; output < 3; output++) {
    /**
     * Due to floating-point precision issues, we can not use ==
     * operator here. Hence we evaluate proximity between two values
     * using absolute value
     */
    if (fabs(creal(z) - values[output]) < 1E-2) {
      return output;
    }
  }
  return 3;
}


/**
 * Evaluates the f function at a given point in complex plane
 */
double complex eval_f (double complex z) {
  return cpow(z, 3) - 3 * z + 1;
}


/**
 * Evaluates the derivative of f in a given point in complex plane
 */
double complex eval_df (double complex z) {
  return 3 * cpow(z, 2) - 3;
}


/**
 * Executes the newton method using the given z as the start point
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
 * Generates the newton basins by iterating over an area of the complex
 * plane and applying the newton method for each point in this section.
 */
void newton_basins (int l, int u, int p) {
  FILE *output;
  double complex z;
  double re_z, im_z;
  double step;
  double complex result;

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

      result = newton(z);

      /**
       * Outputs the discretization of the newton method into the output
       * file. This process helps choosing colors to plot the basins later
       */
      fprintf(output, "%lf\t%lf\t%d\n", re_z, im_z, output_for(result));
    }
  }

  fclose(output);
}

int main () {
  newton_basins(-100, 100, 1000);

  return 0;
}
