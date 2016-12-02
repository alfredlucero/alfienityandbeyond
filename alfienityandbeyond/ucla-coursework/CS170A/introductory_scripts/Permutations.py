import numpy as np

n = 4

import itertools
perm_generator = itertools.permutations(range(n))

Perm = np.array([p for p in perm_generator])
# Perm is a  24 x 4  table of all permutations of size 4


Ident = np.eye(n)

P = np.zeros((n,n,n))

for i in range(n):
   P[:,:,i] = Ident[ :, Perm[i,:] ]
   #  P(:,:,i) is the i-th permutation matrix:
   #    the Identity matrix with columns permuted into Perm(i)

Perm[0:3, :]   # the first 3 permutations

P1 = P[:,:,0]  # the identity permutation
P2 = P[:,:,1]  # the permutation that interchanges 2 and 3
P3 = P[:,:,2]  # the permutation that interchanges 1 and 2

x = np.arange(4).T

P1.dot(x)

P2.dot(x)

P3.dot(x)

P2.dot(P3)

P2.dot(P3).dot(x)

P3.dot(P2)

P3.dot(P2).dot(x)
