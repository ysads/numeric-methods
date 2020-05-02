1;

% 8910368 - Ygor Sad Machado
% Exercício 3.13

% Probes a given function by determining in which points f
% changes its sign
%
% f: the function to probe
% points: a set of points to test f's sign
function [xs_start, xs_end] = probe(f, points)
  points_length = length(points) - 1;

  for x = 1:points_length
    f_curr = feval(f, points(x));
    f_next = feval(f, points(x + 1));

    % If the function changes signal within two consecutive abscissae,
    % then we must add them to our resulting sets
    if f_curr * f_next < 0
      xs_start(end + 1) = points(x);
      xs_end(end + 1) = points(x + 1);
    endif
  endfor
endfunction


% Apply the bisection method a given number of times, considering
% 
% num: number of times to apply bisection
% f: the function to apply the method to
% x_start: start of the interval
% x_end: end of the interval
function [x_start, x_end] = bisection(num, f, x_start, x_end)
  for i = 1 : num
    x_mean = (x_start + x_end) / 2;

    % If f changes sign from the mean of the interval onwards then
    % we set the start of the interval to be the current mean
    if f(x_mean) * f(x_end) < 0
      x_start = x_mean;
    else
      x_end = x_mean;
    endif
  endfor
endfunction


% Checks whether a given value of x is within our required tolerance
% by both evaluting how close x is from is antecessor and how close
% f(x) is from zero
%
% f: the function to evaluate
% curr_x: the x we would like to assess to tolerance to
% last_x: the last value for x
% tol: the required tolerance
function [result] = is_within_tolerance(f, curr_x, last_x, tol)
  within_x_tol = abs(curr_x - last_x) / (1 + abs(curr_x)) < tol;
  within_f_tol = abs(f(curr_x)) <= tol;

  result = within_x_tol && within_f_tol;
endfunction


% Apply our custom version of Newton's  method to find a single root
%
% f: the function whose root is being searched
% df: the derivative of f
% x_start: the end of the interval in which the root is
% x_end: the end of the interval in which the root is
% tol: the tolerance for our root value
function [root] = custom_newton(f, df, x_start, x_end, tol)
  curr_x = x_start;

  % Some constants to guide both Newton and bisection methods
  x_tol = 0.5;
  num_bisections = 3;

  % We will repeat this process until we finally have a value for x
  % which satifies our tolerance requirements
  do
    % Evaluates the next value of x using standard Newton's method
    last_x = curr_x;
    curr_x = curr_x - f(curr_x) / df(curr_x);

    % If the value of x hasn't seen a significant decrease, we apply
    % the bisection method a fixed number of times and recursively
    % apply our custom Newton's method to the new interval
    if abs(f(curr_x) >= x_tol * abs(f(last_x)))
      [x_start, x_end] = bisection(num_bisections, f, x_start, x_end);
      root = custom_newton(f, df, x_start, x_end, tol);
      return;
    endif
  until (is_within_tolerance(f, curr_x, last_x, tol))

  % If we got out of the loop, it's safe to assume curr_x is the
  % root we've been looking for
  root = curr_x;
endfunction


% A function that find all roots of f using the probed intervals
%
% f: function whose roots we want
% df: the derivative of f
% xs_start: the starting points of interval we know contain roots
% xs_end: the ending points of interval we know contain roots
% tol: the tolerance to use when finding the roots
function roots = find_roots(f, df, xs_start, xs_end, tol)
  for i = 1:length(xs_start)
    roots(end + 1) = custom_newton(f, df, xs_start(i), xs_end(i), tol);
  endfor
endfunction


% Initial parameters
%
a = -10;
b = 10;
n_probe = 50;
tol = 1.e-8;

% The function and its derivative to which we will apply our
% custom root-finding method
f = inline("2 * cosh(x / 4) - x");
df = inline("(sinh(x / 4) - 2) / 2");

% step represents the distance between two consectutive probing points
step = (b - a) / (n_probe - 1);
probing_points = a : step : b;

% x_start and x_end are vectors with the edges of intervals which
% contain roots of function f
[xs_start, xs_end] = probe(f, probing_points);

% Finds all roots of f in the probed intervals
roots = find_roots(f, df, xs_start, xs_end, tol);

printf("The roots are:\n")
for i = 1:length(roots)
  printf("=> %.15f\n", roots(i))
endfor