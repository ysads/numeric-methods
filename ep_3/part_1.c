/**
 * Ygor Sad Machado
 * NUSP: 8910368
 *
 * EP 3 - Part 1
 * This part estimates the integral of F(x)cos(theta(x)) using both
 * Newton's and Simpson's methods after interpolating a polynomial
 * using a given dataset.
 */
#include <math.h>
#include <stdio.h>

#define N_POINTS 7
#define N_DIMENSIONS 2


/**
    Helper function to display output in organized way, computing the
    associated error in the estimation.
**/
void output(double expected, double estimated) {
    printf("> estimated: %.10lf\n", estimated);
    printf("> expected:  %.10lf\n", expected);
    printf("> error:     %.10lf\n\n", fabs(estimated - expected));
}


/**
    Find each coefficient c_i of the interpolant function. This
    coefficients are determined by iteratively calculating divided
    differences. This function assumes a coefficients array with
    enough space is already allocated and given as argument.
**/
void find_coefficients(double *xs, double *ys, double *coefficients) {
    for (int i = 0; i < N_POINTS; i++) {
        coefficients[i] = ys[i];
    }

    for (int j = 0; j < N_POINTS - 1; j++) {
        for (int i = N_POINTS - 1; i > j; i--) {
            coefficients[i] = (coefficients[i] - coefficients[i-1]) / (xs[i] - xs[i-j-1]);
        }
    }
}


/**
    Estimates the value of f at given abcissae using the interpolant
    polynomial whose coefficients have been computed earlier and given
    as argument to this function.
**/
double estimate_f(double *coefficients, double *xs, double x) {
    double product;
    double sum = 0;

    for (int i = N_POINTS - 1; i >= 0; i--) {
        product = 1;
        
        for (int j = 0; j < i; j++) {
            product *= (x - xs[j]);
        }
        sum += (product * coefficients[i]);
    }
    return sum;
} 


/**
    Evaluates the integral of f using composite-trapezoidal rule. It uses
    a simplified version of the general formula, which saves some computation
    by grouping the items in between two adjancent abcissae, which always
    appear doubled, and by only multiplying the area by h at the end of iteration.
**/
double composite_trapezoidal(double *coefficients, double *xs, double *ys, int n) {
    double a, b, h;
    double sum = 0;

    /**
        The length of each subinterval
    **/
    h = (xs[0] + xs[1]) / n;

    for (int i = 0; i < N_POINTS - 1; i++) {
        a = xs[i];
        b = xs[i + 1];

        /**
            Compute separately the parcels which appear doubled on the areas and thus
            don't need to be divided by 2.
        **/
        for (int j = 1; j < n; j++) {
            sum += estimate_f(coefficients, xs, a + j * h);
        }

        /**
            The boundary areas only appear once and thus must be divided by 2 normally
        **/
        sum += (estimate_f(coefficients, xs, a) + estimate_f(coefficients, xs, b)) / 2; 
    }
    sum *= h;

    return sum;
}


/**
    Just like the above implementation, this one tries to simplify evaluations
    by grouping parcels which get multiplied by common factors – in this case,
    inner odds and evens.
**/
double simpson(double *coefficients, double *xs, double *ys, int n) {
    double a, b, h;
    double sum = 0;
    double sum_odds, sum_evens;

    /**
        The length of each subinterval
    **/
    h = (xs[0] + xs[1]) / n;

    for (int i = 0; i < N_POINTS - 1; i++) {
        a = xs[i];
        b = xs[i + 1];

        sum_odds = 0;
        sum_evens = 0;

        /**
            Computes sum of the odd parcels. They always appear multiplied
            by 4; that's why we want to to compute it separated from the evens.
        **/
        for (int j = 1; j < n; j += 2) {
            sum_odds += estimate_f(coefficients, xs, a + j * h);
        }

        /**
            Computes sum of the inner even parcels. Since they are computed
            twice – two consecutive integrals always have a common sum parcel –,
            we would like to group them into a single sum that can be doubled later on.
        **/
        for (int j = 2; j < n; j += 2) {
            sum_evens += estimate_f(coefficients, xs, a + j * h);
        }

        /**
            After the partial sums have been computed, we can safely multiply
            them by their respective factors, and also add the two missing
            interval boundary areas.
        **/
        sum += 4 * sum_odds;
        sum += 2 * sum_evens;
        sum += estimate_f(coefficients, xs, a) + estimate_f(coefficients, xs, b);
    }
    sum *= h / 3;

    return sum;
}


int main() {
    double xs[N_POINTS] = { 0, 5, 10, 15, 20, 25, 30 };
    double ys[N_POINTS] = { 0.0000, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537 };
    double coefficients[N_POINTS] = { 0, 0, 0, 0, 0, 0, 0 };

    /**
        The expected exact value of the integral
    **/
    double expected = 117.266;

    find_coefficients(xs, ys, coefficients);

    for (int n = 2; n <= 256; n *= 2) {
        printf("---------- n = %d\n\n", n);

        printf("trapezoidal\n");
        output(expected, composite_trapezoidal(coefficients, xs, ys, n));

        printf("simpson\n");
        output(expected, simpson(coefficients, xs, ys, n));

        getchar();
    }

    return 0;
}