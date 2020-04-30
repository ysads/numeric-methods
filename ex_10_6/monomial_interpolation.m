1;

% This function received 4 points in the format [X Y]
% and interpolates it using monomial basis.
function c = interpolate_monomial(point_0, point_1, point_2, point_3)
	A = [point_0(1)^0  point_0(1)^1  point_0(1)^2  point_0(1)^3;
			 point_1(1)^0  point_1(1)^1  point_1(1)^2  point_1(1)^3;
			 point_2(1)^0  point_2(1)^1  point_2(1)^2  point_2(1)^3;
			 point_3(1)^0  point_3(1)^1  point_3(1)^2  point_3(1)^3];

  y = [point_0(2)
			 point_1(2)
			 point_2(2)
			 point_3(2)];

	c = A \ y;
end

% Initialize the data points
p1 = [-1 1];
p2 = [0 1];
p3 = [1 2];
p4 = [2 0];

% Evaluates coefficients using each method
res_monomial = interpolate_monomial(p1, p2, p3, p4)
