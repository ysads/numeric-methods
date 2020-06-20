1;

% 8910368 - Ygor Sad Machado
% Exercício 14.12

% Determina os valores de h e de f ao longo do intervalo
% de modo a construir a iteração e avaliar o erro
k = 0:0.5:8;
h = 10.^(-k);

lower = 1.2 - h;
upper = 1.2 + h;

f_lower = sin(lower);
f_upper = sin(upper);

% Valor exato da segunda derivada de f em x = 1.2
fpp_exact = -sin(1.2);

% Fixa o valor de f_0 a ser usado durante a iteração
f_0 = sin(1.2);

% Itera pelo intervalo avaliando o erro em cada ponto
for i = 1:length(k)
  fpp(i) = (f_lower(i) - 2 * f_0 + f_upper(i)) / (h(i) ^ 2);
  error(i) = abs(fpp(i) - fpp_exact);
endfor

printf("O ponto ótimo de h ocorre aproximadamente em h = 1 * (10^-4)\n")

% Plota os valores de h e do erro em escala logarítmica
loglog(h, error);
hold on;
xlabel('h (log)');
ylabel('erro (log)');
