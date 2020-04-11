function f = func(x)
  f = 2 * cosh(x / 4) - x;
endfunction

function f = dfunc(x)
  f = 0.5 * sinh(x / 4) - 1;
endfunction

function [root] = newton_recursive(fn, dfn, x, tol)
  fx = feval(fn, x);
  dfx = feval(dfn, x);

  if (abs(fx) <= tol)
    root = x;
    return;
  endif

  next = x - (fx / dfx);

  root = newton_recursive(fn, dfn, next, tol);
endfunction

newton_recursive(@func, @dfunc, 4, 1.e-10)  # ~ 2.3576
newton_recursive(@func, @dfunc, 10, 1.e-10) # ~ 8.5072
