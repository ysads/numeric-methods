1;

% 8910368 - Ygor Sad Machado
% Exercício 14.3

% Define a função f a ser usada pelo método
function y = f(x)
  y = exp(x) * sin(3 * x);
endfunction

% Define a função que avalia a segunda derivada de f
% usando o método construído
function fpp = estimate_fpp(x, h)
  fpp = 1/(90 * h^2) * f(x - 3 * h) ...
        - 3/(20 * h^2) * f(x - 2 * h) ...
        + 3/(2 * h^2) * f(x - h) ...
        - 49/(18 * h^2) * f(x) ...
        + 3/(2 * h^2) * f(x + h) ...
        - 3/(20 * h^2) * f(x + 2 * h) ...
        + 1/(90 * h^2) * f(x + 3 * h);
endfunction

% Parâmetros da simulação
h = [.1, .05, .025];
x0 = .4;

% Calcula a segunda derivada usando a fórmula exata para fins de comparação
exact_derivative = 2 * exp(x0) * (3 * cos(3 * x0) - 4 * sin(3 * x0));
printf("exact f'': %0.10f\n", exact_derivative);

% Estima a segunda derivada usando os diversos h exibindo os resultados
for h_i = h
  printf("h = %f => f''(x0) = %0.10f\n", h_i, estimate_fpp(x0, h_i))
endfor
