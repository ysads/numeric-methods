% Recursive version of bisection method
%
% Evaluates an approximation for p such that |p - root| < atol, where root
% is a root of func. This function assumes func(a) * func(b) < 0.
function [p] = bisect_recursive(func, a, b, atol)
  p = (a + b) / 2;
  
  if (b - a) < atol
    return
  else
    fa = feval(func, a);
    fb = feval(func, b);
    fp = feval(func, p);

    if (fa * fp) < 0
      b = p;
    else
      a = p;
    endif
    
    p = bisect_recursive(func, a, b, atol);  
  endif
endfunction
