import matplotlib.pyplot as plt
import numpy as np

def scree_plot( sigma, percent ):
   if (percent <= 0):  percent = 0.01
   if (percent >  1):  percent = 1.0   # percent should be a fraction between 0 and 1
   p = max(np.shape(sigma))
   sigma_total = sum(sigma)
   plt.plot( np.array(range(1,(p+1))), sigma, 'b.' , np.array([0,p]), np.array([percent * sigma_total, percent * sigma_total]), 'r-' )
   plt.title('a "scree plot":  singular values of the face matrix X')
   plt.xlabel('the red line is %d percent of the total of all singular values' % round( percent * 100 ))
   plt.show()
