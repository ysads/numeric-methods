/**
 * Ygor Sad Machado
 * NUSP: 8910368
 *
 * EP 3 - Part 2
 * This part computes both uni- and multidimensional integrals using
 * Montecarlo's method. It computes integrals of several test functions
 * as long as estimate the value o pi using a bivariate function.
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


/**
    Helper function to display output in organized way, computing the
    associated error in the estimation.
**/
void output(double expected, double estimated) {
    printf("> estimated: %.10lf\n", estimated);
    printf("> expected:  %.10lf\n", expected);
    printf("> error:     %.10lf\n\n\n", fabs(estimated - expected));
}


/**
    Generates a number between 0 and 1 using an algorithm based on
    a uniform distribution.
**/
double generate_random() {
    return 1.0 * rand() / RAND_MAX;
}


/**
    Executes estimated method for a single-variable function. Please note this
    function generates a value in [0,1] interval and apply a series of arithmetic
    operations onto it to translate it into a value in [a,b] interval
**/
long double montecarlo_1d(long n, double a, double b, double (*f)(double)) {
    double x;
    double mean = 0;

    for (long i = 0; i < n; i++) {
        x = generate_random();
        mean += (b - a) * f(a + (b - a) * x);
    }

    return mean / n;
}


/**
    Equivalent to function above, but for bidimensional integrals. Note it relies
    on two additional parameters c and d. This function also applies the same
    correction as described above to translate a point (x,y) from [0,1]x[0,1]
    region to [a,b]x[c,d] region.
**/
long double montecarlo_2d(long n, double a, double b, double c, double d, double (*f)(double, double)) {
    double x, y;
    double mean = 0;

    for (long i = 0; i < n; i++) {
        x = generate_random();
        y = generate_random();
        mean += (b-a) * (d-c) * f(a + (b-a) * x, c + (d-c) * y);
    }

    return mean / n;
}

/**
    Functions whose integrals will be evaluated
**/

double f_1(double x) { return sin(x); }
double f_2(double x) { return pow(x, 3); }
double f_3(double x) { return exp(-x); }

double f_4(double x, double y) { return (pow(x, 2) + pow(y, 2) <= 1) ? 1 : 0; }


int main (int argc, char *argv[]) {
    double a, b, c, d;
    double integral;
    long n;

    /**
        Parse the number of iterations that should be used by montecarlo's
        method. Exit with error if none is given.
    **/
    if (argc != 2) {
        printf("Required number of iterations. Use: ./part_2.o <n>\n");
        return 1;
    }

    n = atoi(argv[1]);

    printf("---------------------------------------------------------\n");
    printf("---------- UNIDIMENSIONAL -------------------------------\n\n");
    
    /**
        Test 1
    **/
    a = 0.0;
    b = 1.0;
    printf("f(x) = sin(x)\n");
    output(0.4596976941, montecarlo_1d(n, a, b, f_1));

    /**
        Test 2
    **/
    a = 3.0;
    b = 7.0;
    printf("f(x) = x^3\n");
    output(580.0000000000, montecarlo_1d(n, a, b, f_2));

    /**
        Test 3 - Note that it is not required to use b=infinity, since
        a much smaller number already yields sufficient precision.
    **/
    a = 0.0;
    b = 50.0;
    printf("f(x) = exp(-x)\n");
    output(1.0000000000, montecarlo_1d(n, a, b, f_3));


    printf("---------------------------------------------------------\n");
    printf("---------- MULTIDIMENSIONAL -----------------------------\n\n");
    
    /**
        Test 4
    **/
    a = 0.0;
    b = 1.0;
    c = 0.0;
    d = 1.0;
    integral = montecarlo_2d(n, a, b, c, d, f_4);
    printf("f(x) = |  1,  x^2 + y^2 <= 1\n");
    printf("       |  0,  otherwise\n");
    output(0.7853981634, integral);

    printf("value of π\n");
    output(3.14159265359, 4 * integral);

    return 0;
}
