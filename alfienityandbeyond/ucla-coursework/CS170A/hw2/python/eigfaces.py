import os

import matplotlib.pyplot as plt   #  includes  imshow()
import matplotlib.image as img    #  includes  imread()

import numpy as np
from numpy.linalg import svd


Face = img.imread('face000.bmp')
plt.figure
plt.subplot(1,2,1)
plt.imshow(Face, cmap='gray')
plt.title('initial image -- no approximation')

X = np.array(Face, dtype='double');        # convert unit8 image to double so we can operate on it
U,sigma,V  = svd(X)

# find the index k such that sigma_k has percentage above 95 percent
sigma_percentage = np.cumsum( sigma / sum(sigma) )

k = len( sigma[ (sigma_percentage < 0.95) ] )

# k-th order approximation
S_k = np.diag( sigma[0:k] )
U_k = U[:, 0:k]
V_k = V[:, 0:k]

X_k = U_k .dot( S_k .dot( V_k.T ))

Face_k = np.array(X_k, dtype='uint8');     # convert matrix back to a uint8 image
plt.subplot(1,2,2)
plt.imshow(Face_k, cmap='gray')
plt.title(('k-th order approximation of image (k = %d)' % k))
plt.show()


def scree_plot( sigma, percent ):
   if (percent <= 0):  percent = 0.01
   if (percent >  1):  percent = 1.0   # percent should be a fraction between 0 and 1
   p = max(np.shape(sigma))
   sigma_total = sum(sigma)
   plt.plot( np.array(range(1,(p+1))), sigma, 'b.' , np.array([0,p]), np.array([percent * sigma_total, percent * sigma_total]), 'r-' )
   plt.title('a "scree plot":  singular values of the face matrix X')
   plt.xlabel('the red line is %d percent of the total of all singular values' % round( percent * 100 ))
   plt.show()

scree_plot( sigma, 0.01 )


def kthOrderApproximation(X, k):
   U,sigma,V = svd(X, full_matrices=0, compute_uv=1)
   U_k = U[:, 0:k]
   V_k = V[:, 0:k]
   S_k = np.diag(sigma[0:k])
   X_k = U_k .dot( S_k .dot( V_k.T ) )
   return (U_k,S_k,V_k,X_k)

Face_10 = uint8( kthOrderApproximation(X, 10) )
Face_5  = uint8( kthOrderApproximation(X, 5) )

plt.figure
plt.subplot(1,2,1)
plt.imshow(Face_10, cmap='gray')
plt.title('10-th order approximation of image')
plt.subplot(1,2,2)
plt.imshow(Face_5, cmap='gray')
plt.title('5-th order approximation of image')
plt.show()

#-------------------------------

 #----------------------------------------------------------------------------
 #       Useful functions for converting  images  <-->  vectors
 #----------------------------------------------------------------------------
 row = 64
 col = 64
 
 image_vector  = lambda(Bitmap) double(reshape(Bitmap,row*col,1))
 vector_image  = lambda(Vec) reshape( uint8( min(max(Vec,0),255) ), row, col)
 vector_render = lambda(Vec) plt.imshow(vector_image(Vec), cmap='gray')

filenames = os.dir('*.bmp')
n = len(filenames)
for i in range(n):
  Image_File = filenames[i]
  Face_Matrix = img.imread(Image_File)
  F[i,:] = image_vector(Face_Matrix)  # the i-th row of F is the i-th image
end

#-------------------------------

m = np.mean(F).T   # m is a vector containing the means of columns of F
vector_render(m)
plt.show()

image_vector  = lambda(Bitmap) double(reshape(Bitmap,row*col,1))
vector_image  = lambda(Vec) reshape( min(max(Vec,0),255), row, col)
vector_render = lambda(Vec) plt.imshow(vector_image(Vec), cmap='gray')

filenames = dir('*.bmp')
[row,col] = size(img.imread(filenames(1).name))
  ## row = 64
  ## col = 64

p = row*col
n = size(filenames,1)
F = zeros(n,p)

for i = 1:n
  Image_File = filenames(i).name
  Face_Matrix = img.imread(Image_File)
  F(i,:) = image_vector(Face_Matrix);  # the i-th row of F is the i-th image
end

M = np.ones(n,1) * np.mean(F);  #  rows of M = n replications of (the column means of F)

X = (F - M)

k = 30;                             #  arbitrarily choose k=30

#  k-th order approximation to cov(X)
U,sigma,V = svd(X, full_matrices=0, compute_uv=1)
U_k = U[:, 0:k]
V_k = V[:, 0:k]
S_k = np.diag( sigma[0:k] )

Eigenfaces = V_k;      # Eigenfaces = principal components of X = principal components of F

matrix_image = lambda(A) round( (A-min(A))/(max(A)-min(A)) * 255 )

plt.figure
plt.subplot(2,3,1)
scree_plot( sigma, 0.01 )
plt.subplot(2,3,2)
vector_render( matrix_image(Eigenfaces(:,1)) )
plt.xlabel('first Eigenface')
plt.subplot(2,3,3)
vector_render( matrix_image(Eigenfaces(:,2)) )
plt.xlabel('second Eigenface')
plt.subplot(2,3,4)
vector_render( matrix_image(Eigenfaces(:,3)) )
plt.xlabel('third Eigenface')
plt.subplot(2,3,5)
vector_render( matrix_image(Eigenfaces(:,4)) )
plt.xlabel('fourth Eigenface')
plt.subplot(2,3,6)
vector_render( matrix_image(Eigenfaces(:,5)) )
plt.xlabel('fifth Eigenface')
plt.show()

#-------------------------------

m = np.mean(F).T
f = image_vector(img.imread('face000.bmp'))
plt.x = f - m
c = V_k' * x

factors = [1 2 4 6]
nfactors = max(size(factors))
plt.figure
for i = 1:nfactors
  factor = factors(i)
  subplot(1,nfactors,i)
  cnew = c
  cnew(4) = c(4) * factor;   # perturb the 4th coefficient by multiplicative factor
  vector_render( m + V_k * cnew )
  xlabel(('factor = %d' % factor))
  if i*2==nfactors
     title('image with 4th Eigenface coefficient multiplied by a constant factor')
  end
end
plt.show()

