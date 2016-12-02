#----------------------------------------------------------------------------
# Matrix operations
#----------------------------------------------------------------------------
import numpy as np

x = np.array([ 1, 3+2j ])      #  a vector
y = np.array([[1],[3+2j]])     #  explicitly: a column vector

x.shape                        #  obtain the dimensions of x
y.shape                        #  obtain the dimensions of y

A = np.array([[1,2+2j],[3,4]]) #  a 2x2 matrix -- whose rows are [1 2+2i] and [3 4]

A.size                         #  obtain the dimensions of A

B = A.T                        #  the ordinary transpose of A
A.dot(B)                       #  product of A and B  (a matrix)
A.dot(x.T)                     #  product of A and x  (a vector)

A.T.conj()                     #  the conjugate transpose (Hermitian transpose) of A
A.conj().T                     #  the conjugate transpose (Hermitian transpose) of A
A.T - A.T.conj()               #  the difference between A's transpose and A's conjugate transpose
np.imag(A+A.conj())            #  imag(z) is the imaginary part of z; so imag(A + A.conj()) should be zero

z = np.array([[1+2j],[0-3j]])  #  a column vector of complex values
z.T.conj()                     #  the corresponding complex conjugate row vector

x = np.array([1, 0])           #  a real row vector (1x2 matrix)
x.transpose()                  #  a column vector   (2x1 matrix)
x.T                            #  a column vector   (2x1 matrix)

np.arange(5)                   #  the row vector of values from 0 to 4
np.arange(5).T                 #  the column vector of values from 0 to 4

np.arange(0,5)                 #  the row vector of values from 0 to 4
np.arange(0, 5, 2)             #  the row vector of values from 0 to 4, with steps of size 2
np.array([1,3,5])              #  the same thing
np.array([[1],[3],[5]]).T      #  the same thing

np.arange(1.3, 4.3)            #  the row vector [ 1.3  2.3  3.3 ]

np.linspace(1.3, 3.8, 6)       #  row vector of length 6 with equispaced values from 1.3 to 3.8
np.arange(1.3, 4.8, 0.5)       #  the same thing (using steps of size 0.5)

x = np.array([[1],[0]])        #  a column vector (2x1 matrix)
x**2                           #  the column vector of squares of elements in x

#  x.dot(x)                    #  ERROR
x.T.dot(x)                     #  dot product of x with itself

A = np.array([[1,2],[3,4]])    #  a 2x2 matrix -- whose rows are [1 2] and [3 4]
np.reshape(A,(4,1))            #  the 4x1 matrix obtained by inserting the elements of A column-wise

A + A                          #  sum of A with itself

A.dot(x)                       #  the product of A with x

A.dot(A)                       #  product of A with itself
A**2                           #  a matrix whose elements are squares of corresponding elements in A
A*A                            #  a matrix whose elements are squares of corresponding elements in A

A.dot(A.dot(A))                #  cube of A
A.dot(A).dot(A)                #  cube of A

np.trace(A)                    #  trace of A
np.linalg.det(A)               #  determinant of A
np.linalg.inv(A)               #  inverse of A
np.matrix(A).I.A               #  inverse of A

np.linalg.det(A) * np.linalg.inv(A)  #  product of the scalar det(A) with the inverse of A
A.dot(np.linalg.inv(A))        #  product of A with its inverse
np.linalg.inv(A).dot(A)        #  product of the inverse of A with A
np.linalg.pinv(A) .dot(A)      #  product of the pseudo-inverse of A with A

B = np.hstack((A,A))           #  the 2x4 matrix with 2 horizontal copies of A
AAA = np.hstack((A,A,A))       #  the 2x6 matrix with 3 horizontal copies of A
C = np.vstack((AAA,AAA))       #  the 4x6 matrix with 2x3 stacked copies of A

B[0:2, 0:2]                    #  the upper left  2x2 submatrix of B (which equals A)
C[2:4, 2:6]                    #  the lower right 2x4 submatrix of B (which equals B)
B - C[0:2][:,0:4]

np.eye(2)                      #  the 2x2 identity matrix (terrible pun)
np.eye(8)                      #  the 8x8 identity matrix

np.zeros(3)                    #  a 1x3 matrix of zeros
np.zeros((3,2))                #  a 3x2 matrix of zeros

np.ones((3,2))                 #  a 3x2 matrix of ones

np.random.rand(3,2)            #  a 3x2 matrix of uniform random values
np.random.rand(3)              #  a 1x3 matrix of uniform random values

