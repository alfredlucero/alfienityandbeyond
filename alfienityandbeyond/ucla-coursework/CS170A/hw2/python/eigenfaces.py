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
