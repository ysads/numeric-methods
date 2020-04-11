1;

% Evaluates an approximation for p such that |p - root| < atol, where root
% is a root of func. This function assumes func(a) * func(b) < 0.
function [p, n] = bisect(func, a, b, atol)
  fa = feval(func, a);
  fb = feval(func, b);

  if (a >= b) | (fa * fb >= 0) | (atol <= 0)
    disp('Input parameters incorrect. Try again')
    p = NaN;
    n = NaN;
    return;
  endif

  % This approach for bisect is absolutist. Instead of relying on how close fp
  % is from 0, we prefer to execute the for below a deterministic number of times.
  n = ceil(log2(b - a) - log2(2 * atol));

  for k = 1:n
    p = (a + b) / 2;
    fp = feval(func, p);

    % This handles the case in which `p` is the exact root of func. Take the
    % stance this generally does not occur naturally. To simulate it, call
    % `bisect(@sin, -1, 1, 1.e10) both with and without the if below to check
    % the difference.
    if (abs(fp) < eps)
      n = k;
      return;
    endif

    if (fa * fp < 0)
      b = p;
      fb = fp;
    else
      a = p;
      fa = fp;
    endif
  endfor
  p = (a + b) / 2;
endfunction


% Ex. 3.3 - Function 1
function f = fex3_1(x)
  f = x.^3 - 30 * x.^2 + 2552;
endfunction


% Ex. 3.2 - Function 2
function f = fex3_2(x)
  f = 2.5 * sinh(x / 4) - 1;
endfunction


bisect(@fex3_1, 11, 12, 1.e-10)  % n = 33 & p ~ 11.862
bisect(@fex3_2, -10, 10, 1.e-10) % n = 37 & p ~ 1.5601
