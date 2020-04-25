/**
 * Ygor Sad Machado
 * NUSP: 8910368
 *
 * EP 1 - Part 2
 * This part intends to implement the Newton Basins for
 * a given function f
 */
#include <complex.h>
#include <stdio.h>

#define MAX_ITERATIONS 20
#define TOLERANCE 0.0000001

double complex eval_f (double complex z) {
  // return 2 * cosh(z / 4) - z;
  return cpow(z, 4) - 1;
}

double complex eval_df (double complex z) {
  // return 0.5 * sinh(z / 4) - 1;
  return 4 * cpow(z, 3);
}

double complex newton (double complex z, double complex tol, int max_iter) {
  int elapsed_iterations;
  complex double curr_z;
  complex double f_z, df_z;

  /**
   * We start the process using the given z.
   */
  curr_z = z;
  elapsed_iterations = 0;

  while (elapsed_iterations <= max_iter) {
    f_z = eval_f(curr_z);
    df_z = eval_f(curr_z);

    /**
     * In case the current f(z) value is already within our tolerance
     * range from the origin, we have can safely return the current z
     * value, since it fits as a valid root.
     */
    if (cabs(f_z) <= tol) {
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
  return INFINITY;
}


double scaled(int coordinate, int total_dim) {
  return 1.0 * coordinate / total_dim;
}


void newton_basins (int l, int u) {
  FILE *output;
  double complex x, y;
  double complex z;
  double complex root;

  output = fopen("output.txt", "w+");

  /**
   * Iterates over
   */
  for (x = 0; x <= l; x++) {
    for (y = 0; y <= u; y++) {
      /**
       * We must scale our pixel (x, y) down to our domain on
       * complex plane. This is needed to make sure every point
       * is within our delimited area.
       */
      z = scaled(x, l) + I * scaled(y, u);

      root = newton(z, TOLERANCE, MAX_ITERATIONS);

      fprintf(output, "%3.8fi ", root);
    }
    fprintf(output, "\n");
  }

  fclose(output);
}

int main () {

  newton_basins(400, 400);
  
  return 0;
}