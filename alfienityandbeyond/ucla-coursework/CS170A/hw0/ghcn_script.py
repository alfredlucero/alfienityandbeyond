#   GHCN is a large matrix of global historical temperature data, from 1880 to the present
#   We downloaded it from ftp://ftp.ncdc.noaa.gov/pub/data/ghcn/v3/grid/
#   The paper describing the dataset is at http://onlinelibrary.wiley.com/doi/10.1029/2011JD016187/pdf
#
#  The data stores values for the whole globe using a grid, which has a resolution of  5 degrees x 5 degrees.
#  In other words, the grid has 36 rows (for latitude) and 72 columns (for longitude).
#  Although the earth is spherical and a  36 x 72  rectangular grid introduces distortion,
#  for this problem we will follow this approach.
#  
#  The GHCN dataset covers  2016 - 1880 + 1 = 137  years, with 12 months per year.
#  So the data set contains  137 x 12 grids.
#  The ghcn.csv file storing the data is basically a (36 x 12 x 137) x 72  matrix of temperature values.
#  It is stored as a 2D matrix of size (36 x 12 x 137) x 72, along with two initial columns giving the year and month.
#  The script ghcn_script.py reads in the data file and reshapes it for you into a 4D matrix of size  36 x 12 x 137 x 72.
#  
#  Actually, the GHCN data gives "anomaly" values instead of temperature values.
#  That is, it gives values of how far the temperature was from normal in that grid square in that month.
#  Positive values are above normal; all values are in Celsius.
#  (Why does it give anomaly values only? The paper explains why computing actual temperatures is much harder.)
#  
#  The point of this dataset in the assignment is that it permits us to use "slices" to do a lot of work.
#  For example, it turns out the coordinates of most of the continental U.S. are the rectangle with
#  rows 9:12 and columns 14:20 [in Python these are 8:11 and 13:19].

#   -- D.S. Parker, Fall 2016.

import numpy as np

import matplotlib.pyplot as plt
# %matplotlib inline

import pandas as pd


GHCN = pd.read_csv('ghcn.csv', header=None).fillna(0).as_matrix()

#   The data was artificially shifted to [0, 4500]
#     its range should be [-2500, +2000]/100 = [-25,+20], in degrees Centigrade.
#     Since our focus here is on warming, we ignore temperatures below -5.
#   We omit the year and month in columns 1:2 before scaling:

GHCN_in_centigrade  = (GHCN[:,2:74] - 2500.0) / 100.0      # omit the first two columns


temperature_anomaly = np.reshape( GHCN_in_centigrade, (36, 12, 137, 72), order="F" )
# convert to a 4D matrix, so we can use slices; use Fortran conventions, like Matlab
temperature_anomaly.shape
number_of_all_GHCN_values = np.prod( temperature_anomaly.shape )


missing_values     = (temperature_anomaly == -25)
non_missing_values = (temperature_anomaly != -25)
number_of_missing_values = missing_values.sum()

maximum_anomaly_value = temperature_anomaly.max()
minimum_anomaly_value = temperature_anomaly[non_missing_values].min()

US_latitude  = np.arange(8,12)
US_longitude = np.arange(14,20)

my_years = np.arange(1916,2016)
my_year_indices = np.arange(1916-1880,2016-1880)

my_slice = temperature_anomaly[ US_latitude ][ :, :, my_year_indices ][ :, :, :, US_longitude ]


total_number_of_grid_squares = len(US_latitude) * len(US_longitude) * 12
N = total_number_of_grid_squares

average_US_anomaly_by_year = np.reshape( my_slice.sum(axis=3).sum(axis=1).sum(axis=0), (len(my_years), 1) ) / N
# order="F" is not needed for this reshape since the result is a vector


# plt.rcParams['figure.figsize'] = (12.0, 8.0)
plt.plot( my_years, average_US_anomaly_by_year )
plt.xlabel('year')
plt.ylabel('temperature anomaly -- Celsius')
plt.title('average US temperature anomaly by year')
plt.show()

