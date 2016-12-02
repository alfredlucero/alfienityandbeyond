%----------------------------------------------------------------------------
% Matrix operations
%----------------------------------------------------------------------------

echo on

x = [ 1 3+2i ]         %  a vector
y = [ 1 ; 3+2i ]       %  explicitly: a column vector

size(x)                %  obtain the dimensions of x
size(y)                %  obtain the dimensions of y

A = [ 1 2+2i ; 3 4 ]   %  a 2x2 matrix -- whose rows are [1 2+2i] and [3 4]

size(A)                %  obtain the dimensions of A

B = A'                 %  the 'transpose' of A
A * B                  %  product of A and B  (a matrix)
A * x'                 %  product of A and x  (a vector)

A.'                    %  .' is the ordinary transpose of A
A'                     %  ' is actually the Hermitian transpose (conjugate transpose)
A - A'                 %  the difference between A's transpose and A's conjugate transpose
imag(A+A')             %  imag(z) is the imaginary part of z; so imag(A + A') should be zero

z = [ 1+2i ; 0-3i ]    %  a column vector of complex values
z'                     %  the corresponding complex conjugate row vector

x = [ 1   0 ]          %  a real row vector (1x2 matrix)
x'                     %  a column vector   (2x1 matrix)

1:5                    %  the row vector of values from 1 to 5
(1:5)'                 %  the column vector of values from 1 to 5

1 : 2 : 5              %  the row vector of values from 1 to 5, with steps of size 2
[ 1 3 5 ]              %  the same thing
[ 1;3;5 ]'             %  the same thing

1.3 : 3.3              %  the row vector [ 1.3  2.3  3.3 ]

linspace(1.3, 3.8, 6)  %  row vector of length 6 with equispaced values from 1.3 to 3.8
1.3 : 0.5 : 3.8        %  the same thing (using steps of size 0.5)

x = [ 1 ; 0 ]          %  a column vector (2x1 matrix)

x.^2                   %  the column vector of squares of elements in x

% x^2                  %  ERROR

x' * x                 %  dot product of x with itself

A = [ 1 2 ; 3 4 ]      %  a 2x2 matrix -- whose rows are [1 2] and [3 4]
reshape(A,4,1)         %  the 4x1 matrix obtained by inserting the elements of A column-wise

A + A                  %  sum of A with itself

A * x                  %  the product of A with x

A * A                  %  product of A with itself
A^2                    %  product of A with itself
A.^2                   %  a matrix whose elements are squares of corresponding elements in A

A * A * A              %  cube of A
A^3                    %  cube of A

det(A)                 %  determinant of A
trace(A)               %  trace of A

inv(A)                 %  inverse of A
det(A) * inv(A)        %  product of the scalar det(A) with the inverse of A
A * inv(A)             %  product of A with its inverse
inv(A) * A             %  product of the inverse of A with A
A \ A                  %  product of the pseudoinverse of A with A  (backslash = "divide on left")

B = [ A   A ]          %  the 2x4 matrix with 2 horizontal copies of A
C = [ A A A ; A A A ]  %  the 4x6 matrix with 2x3 stacked copies of A

B(1:2, 1:2)            %  the upper left  2x2 submatrix of B (which equals A)
C(3:4, 3:6)            %  the lower right 2x4 submatrix of B (which equals B)
B - C(1:2, 1:4)

eye(2)                 %  the 2x2 identity matrix (terrible pun)
eye(8)                 %  the 8x8 identity matrix

zeros(3)               %  a 3x3 matrix of zeros
zeros(3,2)             %  a 3x2 matrix of zeros

ones(3,2)              %  a 3x2 matrix of ones

rand(3,2)              %  a 3x2 matrix of uniform random values
rand(3)                %  a 3x3 matrix of uniform random values

echo off

