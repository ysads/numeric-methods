import math

def f(x):
    return 2 * math.cosh(x / 4.0) - x

def df(x):
    return 0.5 * math.sinh(x / 4.0) - 1

def newton(fun, dfun, start_x, tol):
    curr_x = start_x

    while True:
        fx = fun(curr_x)
        dfx = dfun(curr_x)

        if (math.fabs(fx) <= tol):
            break;

        curr_x = curr_x - (fx / dfx)

    return curr_x

tol = 1e-8

root_1 = newton(f, df, 2, tol) # ~ 2.357551
root_2 = newton(f, df, 8, tol) # ~ 8.507199

print("root_1: ", root_1)
print("root_2: ", root_2)
