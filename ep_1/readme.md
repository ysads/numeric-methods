# EP1

## Part 2 - Newton Basins

#### How to run

To compile this part, run:

```shell
make part_2 && ./part_2.o
```

This will generate an `output.txt` file, which contains the results of newton basins applied to given arguments. Each row in this file has the shape:

```csv
real(z) | imag(z) | output(z)
```

This `output(z)` is the result of the discretization applied to each result of newton method. It is simply an incremental (1, 2, 3...) value which is assigned to each possible result of the newton method - including when the method does not converge.

To plot the result coming from the dataset, just run

```shell
gnuplot plot.gpi
```

This will open a window with the basins plotted.

#### Functions index

These were the functions used while compiling the images:
1. `x^3 - 3x + 1 (u: -10, l: 10, p: 500)`
2. `2 * cosh(x / 4) - x (u: -50, l: 50, p: 800)`
3. `x^5 - 1 (u: -2, l: 2, p: 200)`
4. `2x^4 - x^3 + 5x (u: -2, l: 2, p: 200)`
5. `x^7 - 1 (u: -2, l: 2, p: 200)`
