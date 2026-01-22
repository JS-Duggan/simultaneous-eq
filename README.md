# Simultaneous Equation Solver

A command-line tool that solves systems of linear equations using Gaussian elimination with exact rational arithmetic.

## Usage

```
clang++ -std=c++20 -o solver main.cpp
./solver
```

## Input Format

The program prompts for:

1. Number of variables (n)
2. Number of equations (m)
3. Coefficients for each equation

For a system like:
```
2x + 3y = 8
4x - y  = 2
```

Enter:
```
Enter number of variables, Xi: 2
Enter number of equations, Ej: 2
Enter coefficients for variable Xi
eq0:
   X0: 2
   X1: 3
   eq0 = 8
eq1:
   X0: 4
   X1: -1
   eq1 = 2
```

Coefficients can be entered as integers or fractions (e.g., `3/4`).

## Output

The program outputs:
1. The row echelon form of the coefficient matrix
2. The solution values for each variable (X0, X1, ..., Xn-1)

## Limitations

- Only works on systems with a unique solution
- Does not detect or handle inconsistent systems (no solution)
- Does not detect or handle underdetermined systems (infinite solutions)
- Number of equations should equal number of variables for reliable results
