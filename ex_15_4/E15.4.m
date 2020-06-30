1;

% 8910368 - Ygor Sad Machado
% Exercício 15.4

% Define a função f e a sua derivada
f = @(x) exp(x);
df = @(x) exp(x);

% Função que estima a integral usando o método trapezoidal corrigido
function res = estimate_integral(f, df, a, b)
	res = (b - a) / 2 * (f(a)  + f(b)) + (b - a)^2 / 12 * (df(a) - df(b));
endfunction

% Executa o primeiro teste, integrando de 0 a 1
exact = e - 1;
estimative = estimate_integral(f, df, 0, 1);

printf("Integral of exp(x) from a=0 to b=1\n")
printf("Exact: \t\t %0.10f\n", exact);
printf("Estimated: \t %0.10f\n", estimative);
printf("Error: \t\t %0.10f\n\n\n", abs(exact - estimative));

% Segundo teste, integrando de 0.9 a 1
exact = e - e^.9;
estimative = estimate_integral(f, df, 0.9, 1);

printf("Integral of exp(x) from a=0.9 to b=1\n")
printf("Exact: \t\t%0.10f\n", exact);
printf("Estimated: \t%0.10f\n", estimative);
printf("Error: \t\t%0.10f\n", abs(exact - estimative));
