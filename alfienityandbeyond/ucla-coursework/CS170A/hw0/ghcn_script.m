%  
%   GHCN is a large matrix of global historical temperature data, from 1880 to the present
%   We downloaded it from ftp://ftp.ncdc.noaa.gov/pub/data/ghcn/v3/grid/
%   The paper describing the dataset is at http://onlinelibrary.wiley.com/doi/10.1029/2011JD016187/pdf
%
%   The data stores values for the whole globe using a grid, which has a resolution of  5 x 5 degrees.
%   In other words, the grid has 36 rows (for latitude) and 72 columns (for longitude).
%   Although the earth is spherical and a  36 x 72  rectangular grid introduces distortion,
%   for this problem we will follow this approach.
%   
%   The GHCN dataset covers  2016 - 1880 + 1 = 137  years, with 12 months per year.
%   So the data set contains  137 x 12 grids.
%   The ghcn.csv file storing the data is basically a (36 x 12 x 137) x 72  matrix of temperature values.
%   It is stored as a 2D matrix of size (36 x 12 x 137) x 72, along with two initial columns giving the year and month.
%   The script ghcn_script.py reads in the data file and reshapes it for you into a 4D matrix of size  36 x 12 x 137 x 72.
%   
%   Actually, the GHCN data gives "anomaly" values instead of temperature values.
%   That is, it gives values of how far the temperature was from normal in that grid square in that month.
%   Positive values are above normal; all values are in Celsius.
%   (Why does it give anomaly values only? The paper explains why computing actual temperatures is much harder.)
%   
%   The point of this dataset in the assignment is that it permits us to use "slices" to do a lot of work.
%   For example, it turns out the coordinates of most of the continental U.S. are the rectangle with
%   rows 9:12 and columns 14:20 [in Python these are 8:11 and 13:19].
%  
%   -- D.S. Parker, Fall 2016.

GHCN = csvread('ghcn.csv');

%   The data was artificially shifted to [0, 4500];
%     its range should be [-2500, +2000]/100 = [-25,+20], in degrees Centigrade.
%     Since our focus here is on warming, we ignore temperatures below -5.
%   We omit the year and month in columns 1:2 before scaling:

GHCN_in_centigrade  = (GHCN(:,3:74) - 2500) / 100;


temperature_anomaly = reshape( GHCN_in_centigrade, [36, 12, 137, 72] );   % convert to a 4D matrix, so we can use slices
size( temperature_anomaly )
number_of_all_GHCN_values = prod(size( temperature_anomaly ));


missing_values = (temperature_anomaly == -25);
number_of_missing_values = sum(sum(sum(sum( missing_values ))));

maximum_anomaly_value = max(max(max(max( temperature_anomaly ))));
minimum_anomaly_value = min(min(min(min( temperature_anomaly .*  (~ missing_values) ))));  %  '~' is 'not' in MATLAB

US_latitude  = 9:12
US_longitude = 15:20

my_years = 1916:2015
my_slice = temperature_anomaly( US_latitude, :, my_years - 1880 + 1, US_longitude );

total_number_of_grid_squares = length(US_latitude) * length(US_longitude) * 12;
N = total_number_of_grid_squares;

average_US_anomaly_by_year = reshape( sum(sum(sum( my_slice, 4),2),1), [length(my_years) 1] ) / N


plot( my_years, average_US_anomaly_by_year )
xlabel('year')
ylabel('temperature anomaly -- Celsius')
title('average US temperature anomaly by year')

