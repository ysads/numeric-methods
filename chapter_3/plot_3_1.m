t = 0:.1:4*pi;
tt = sin(t);
ax = zeros(1,length(t));
xrt = 0:pi:4*pi;
yrt = zeros(1,5);
subplot(3,1,1)
plot(t, tt, 'b', t, ax, 'k', xrt, yrt, 'rx');
xlabel('x')
ylabel('f(x)')
