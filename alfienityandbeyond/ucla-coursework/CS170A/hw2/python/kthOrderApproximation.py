import numpy as np
from numpy.linalg import svd

def kthOrderApproximation(X, k):
   U,S,V = svd(X, full_matrices=0, compute_uv=1)
   U_k = U[:, 0:k]
   V_k = V[:, 0:k]
   S_k = np.diag( S[0:k] )
   X_k = U_k .dot( np.diag(S_k) .dot( V_k.T ) )
   return (U_k,S_k,V_k,X_k)
