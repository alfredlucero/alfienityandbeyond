
% coding: utf-8

% % CS170A -- HW#1 -- assignment and solution form -- Octave

% Your name:  ______________________
% 
% Your UID:  _________
% 
% <b>Please upload only this notebook to CCLE by the deadline.</b>
% 
% <b>Policy for late submission of solutions:</b>  We will use Paul Eggert's Late
% Policy: $N$ days late $\Leftrightarrow$ $2^N$ points deducted}
% The number of days late is $N=0$
% for the first 24 hrs, $N=1$ for the next 24 hrs, etc., and if you submit
% an assignment $H$ hours late, $2^{\lfloor H/24\rfloor}$ points are
% deducted.

% %% NOTE:  In this assignment we provide pseudocode to get you started.
% 
% In later assignments we will not do this.

% % Problem 1:  SVD k-th order approximations (30 points)

% If $A$ is a matrix that has SVD $A = U\,S\,V'$,
% the <b>rank-k approximation of $A$</b>
% keeping only the first $k$ columns of the SVD.
% 
% Specifically, given a $n \times p$ matrix $A$ with SVD $A = U\,S\,V'$,
% then if $k \leq n$ and $k \leq p$, the rank-$k$ approximation of $A$ is
% $$
% A^{(k)} ~~=~~ U ~ S^{(k)} ~ V'
% $$
% where $S^{(k)}$ is the result of setting all diagonal elements to zero after the first $k$ entries
% $(1 \leq k \leq p)$.
% If $U^{(k)}$ and $V^{(k)}$ are like $U$ and $V$ but with all columns zero after the first $k$, then
% $$
% A^{(k)} ~~=~~ U ~ S^{(k)} ~ V' ~~=~~ U^{(k)} ~ S^{(k)} ~ V^{(k)'} .
% $$
% 

% In class, we saw a demo of the attached Matlab script <tt>imagesvdgui.m</tt>
% --- and the effectiveness of this approximation in retaining information about an image.
% 
% The goal of this problem is to implement this approximation
% for black-and-white (grayscale) images.

% In[1]:

load mandrill
Mandrill = ind2rgb(X, map);

A = mean( Mandrill, 3 );  % grayscale image -- size 480 x 500.
size(A)

imwrite(A, 'GrayMandrill.bmp')  % Write the Mandrill to a bitmap image file

get_ipython().magic('The matrix A now contains the Mandrill image (in grayscale)')


% Display the bitmap image file using an HTML img tag:
% 
% <img src="GrayMandrill.bmp">
% 
% &lt;img src="GrayMandrill.bmp"&gt;

% %%%  1.(a):  Plot Singular Values of the Rank-$k$ Approximation of an Image
% 
% As in HW0, construct a grayscale version of the Mandrill image,
% and take one of the 3 color planes as a 500x480 matrix.
% This is our `black and white' image $A$.
% You are to analyze the rank-k approximation of the image.

% Compute the SVD of $A$, and plot the singular values $\sigma_1$, $\sigma_2$, ...

% In[2]:

[U S V] = svd(A);       % U, S, V are now the SVD of A

norm( A - U * S * V' )  %  A should match the product of U, S, V'


% %%%  1.(b):  Optimal Rank-$k$ Approximation of an Image
% 
% Find the value of $k$ that minimizes $\mid\mid{A \; - \; A^{(k)}}\mid\mid^2_{F} ~+~ k$.

% In[3]:

[n p] = size(A)
maximum_possible_k = min(n,p)

for k=1:maximum_possible_k
   do_something = 0; % ................
end


% %%%  1.(c):  The Rank-$k$ Approximation is a Good Approximation
% 
% In the chapter on the SVD, the course reader presents a derivation for $A \, - \, A^{(k)}$:
% $$\begin{eqnarray*}
% A \; - \; A^{(k)}
%  & = &
% U \; S \; V' ~ - ~ U^{(k)} ~ S^{(k)} ~ V^{(k)'}  \\
%  & = &
% U \; S \; V' ~ - ~ U \; S^{(k)} \; V' \\
%  & = &
% U \; (S ~ - ~ S^{(k)}) \; V ' \\
% \end{eqnarray*}$$
% 
% Prove the following:
% $$ \mid\mid{A \; - \; A^{(k)}}\mid\mid^2_{F} ~=~ \sum_{i>k} \sigma_i^2 . $$
% 

% %%%% Proof  (Enter your Proof here)
% Because
% $A \; - \; A^{(k)} ~ = ~ U \; (S ~ - ~ S^{(k)}) \; V '$,
% ..............
% 
% As a result, $\mid\mid{A \; - \; A^{(k)}}\mid\mid^2_{F} ~ = ~ ...$
% 
% Therefore
% $$ \mid\mid{A \; - \; A^{(k)}}\mid\mid^2_{F} ~=~ \sum_{i>k} \sigma_i^2 . $$

% % Problem 2:  Baseball Visualization (40 points)
% 
% For this dataset you are given a matrix of statistics for Baseball players.
% You are to perform two kinds of analysis on this matrix.

% %%% Read in the Baseball Statistics
% 
% Statistics of top players after the last regular season game,
% obtained from MLB.com, October 2016.

% In[4]:

get_ipython().run_cell_magic('', "Stats = csvread('Baseball_Players_Stats_2016.csv', 1, 0);  % skip the header (= row 0)", "%%% Names = csvread('Baseball_Players_Names_2016.csv', 1, 0);\n\nBaseball_Players_2016   %% execute Baseball_Players_2016.m  to load in the data needed here")


% In[5]:

StatNames{1:3}

size(StatNames)

StatNames{:}


% In[6]:

size(Stats)
Stats(1:3, :)


% In[7]:

size(PlayerNames)
PlayerNames{1:3}


% %%% Compute a "scaled" version of the Stats matrix
% 
% We scale each column of values ${\bf x}$ in Stats
% to be  ${\bf z} = ({\bf x}-\mu)/\sigma$ in ScaledStats,
% where $\mu$ is the mean of the ${\bf x}$ values, and $\sigma$ is their standard deviation.
% 
% In Octave/Matlab, the function <tt>mean()</tt> computes column means,
% and <tt>std()</tt> computes standard deviations.
% The function <tt>zscore()</tt> computes both,
% and uses them to "scale" each column in this way.
% 
% This scaling is also called __normalization__ and __standardization__.
% The __z-scores__ ${\bf z} = ({\bf x}-\mu)/\sigma$ are also called
% the standardized or normalized values for ${\bf x}$.

% In[8]:

ScaledStats  =  zscore(Stats);   %  z  =  (x-mu)/sigma

mean(ScaledStats)  %  the means of each column after normalization should be 0
std(ScaledStats)   %  the standard deviations of each column after normalization should be 1


% %%% 2 (a):  Random Projections
%  
% A fundamental problem in data science is that it is impossible to visualize a dataset that has many features.  Given an $n \times p$ dataset (matrix) $A$ in which the number of features $p$ is large, there is no obvious way to plot the data.
% 
% _Dimensionality reduction_ algorithms have been developed that attempt to find datasets that have lower values of $p$ but approximate $A$ in some way.  Although there are sophisticated algorithms, a competitive approach is to compute a ___random projection___ of $A$ into a few dimensions.  When the projection is into 2 or 3 dimensions, the result can be visualized.
% 
% A ___random $k$-D projection___ of a $n \times p$ dataset (matrix) $A$ is the result $(A \, P)$ of multiplying $A$ on the right by a $p \times k$ matrix $P$ of random values.
% 
% The result is a $n \times k$ matrix, assigning each row in $A$ a new pair of values $(x,y)$, and these can be interpreted as positions in a 2D plot.

% In[9]:

get_ipython().magic('plotting 2D values')
Iris = csvread('iris.csv', 1,0);  % skip over the header line
A = Iris(:, 1:4);  % just the measurement columns
[n p] = size(A);
P = rand(p,2);
disp('random projection weights:')
disp(P)
XY = A * P;
plot(XY(:,1), XY(:,2), 'b.')
title('random projection of the iris data')
species = {'  s', '  v', '  V'}
text(XY(:,1), XY(:,2), species(Iris(:,5)), 'fontsize', 10 )


% ___Problem:___ write a function <tt>random_projection(A,k)</tt> that, given an input matrix $A$ of size $n \times p$ and an integer $k>0$, produces a random $k$-D projection.
% 
% Please use uniform random values in the matrix $P$.
% 
% Then:  plot the result of 3 random 2D projections of the data. 

% In each plot, identify the ___greatest outlier___ -- the player with $(x,y)$ values that have the largest total $x+y$.  Print the row in the dataset whose projection is this outlier.

% In[10]:

random_projection = @(A,k) 0 % fill in using e.g.:   ... rand(size(A,1),k) ...

for i = 1:3
   XY = random_projection( ScaledStats, 2 )

   get_ipython().magic('plot ( something_involving_XY )')
   get_ipython().magic("% text( something_involving_XY, PlayerNames, 'fontsize', 10 )")
   get_ipython().magic("text ( something_involving_XY, PlayerRanks, 'fontsize', 10 )")
   XplusY = sum(XY,1)
   get_ipython().magic('greatest_outlier = something_involving_XplusY % ... (XplusY == max(XplusY)) ...')
end


% %%% 2 (b): Latent Semantic Analysis
% 
% The course reader describes __Latent Semantic Indexing__
% for a matrix of values measuring association between X terms vs. Y terms.
% 
% The classic example is a "term/document matrix" for Keywords vs. Books, shown below.
% The code shown produces an LSI plot for the data.
% 
% __Your job is to produce an analogous LSI plot for the table of Baseball players.__
% 
% Components are computed as in:
%   Berry, M. W., Dumais, S. T., and O'Brien, G. W. (1995).
%   "Using linear algebra for intelligent information retrieval."
%   SIAM Review, 37(4), 1995, 573-595.
% 
% Some LSI references:
% <a target="_blank"
% href="http://lsi.research.telcordia.com/lsi/LSIpapers.html">lsi.research.telcordia.com/lsi/LSIpapers.html</a>

% In[11]:

get_ipython().magic('X :  Keywords')

nX = 16;
Xtext = {
        'algorithms',
        'application',
        'delay',
        'differential',
        'equations',
        'implementation',
        'integral',
        'introduction',
        'methods',
        'nonlinear',
        'ordinary',
        'oscillation',
        'partial',
        'problem',
        'systems',
        'theory'
        };

get_ipython().magic('Y :  Books')

nY = 17;

get_ipython().magic('Book : 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17   % Keyword:')
get_ipython().magic('--------------------------------------------------------------------------')
coOccurrence =  [
        0  0  1  0  1  0  1  0  0  0  0  0  0  0  0  0  0;  % algorithms
        0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  1;  % application
        0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0  0;  % delay
        0  0  0  1  0  0  0  1  0  1  1  1  1  1  1  0  0;  % differential
        1  1  0  1  0  0  0  1  0  1  1  1  1  1  1  0  0;  % equations
        0  0  1  0  0  0  1  0  0  0  0  0  0  0  0  0  0;  % implementation
        1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1;  % integral
        0  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0;  % introduction
        0  0  0  0  0  0  0  1  0  0  0  0  0  1  0  0  0;  % methods
        0  0  0  0  0  0  0  0  1  0  0  0  1  0  0  0  0;  % nonlinear
        0  0  0  0  0  0  0  1  0  1  0  0  0  0  0  0  0;  % ordinary
        0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0  0;  % oscillation
        0  0  0  1  0  0  0  0  0  0  0  0  1  0  0  0  0;  % partial
        0  0  0  0  0  1  1  0  0  0  0  0  0  0  0  1  0;  % problem
        0  0  0  0  0  1  0  1  1  0  0  0  0  0  0  0  0;  % systems
        0  0  1  0  0  0  0  0  0  0  1  1  0  0  0  0  1;  % theory
];

[U,S,V] = svd(coOccurrence);

get_ipython().magic('We can look at a plot of the singular values (diagonal of S):')

plot( diag(S), 'b' )

Xfactor = U(:,1:2)
Yfactor = V(:,1:2)

get_ipython().magic('plot the 2D projection of the data')

text_offset = 0.01;
plot( Xfactor(:,1), Xfactor(:,2), 'r*' )
hold on
plot( Yfactor(:,1), Yfactor(:,2), 'b*' )

for i = (1:nX)
     text( Xfactor(i,1)+text_offset, Xfactor(i,2), Xtext(i))
end

for i = (1:nY)
     text( Yfactor(i,1)+text_offset, Yfactor(i,2), sprintf('B%d',i))
end

title( 'Latent Semantic Indexing:  X term vs. Y term ' )
xlabel( '1st component' )
ylabel( '2nd component' )

zoom on
hold off


% In[ ]:




% % Problem 3: Global Warming again  (30 points)

% In HW0, you plotted the average (non-missing-value) temperature anomaly over the entire grid,
% for every year from 1916 to 2015.
% 
% In this problem we want you to fit linear models through the data.

% In[12]:

get_ipython().magic('set up everything as in HW%0:')

GHCN = csvread('ghcn.csv');

get_ipython().magic('The data was artificially shifted to [0, 4500];')
get_ipython().magic('its range should be [-2500, +2000]/100 = [-25,+20], in degrees Centigrade.')
get_ipython().magic('Since our focus here is on warming, we ignore temperatures below -5.')
get_ipython().magic('We omit the year and month in columns 1:2 before scaling:')

GHCN_in_centigrade  = (GHCN(:,3:74) - 2500) / 100;

temperature_anomaly = reshape( GHCN_in_centigrade, [36, 12, 137, 72] );   % convert to a 4D matrix, so we can use slices

missing_values = (temperature_anomaly == -25);
number_of_missing_values = sum(sum(sum(sum( missing_values ))));

maximum_anomaly_value = max(max(max(max( temperature_anomaly ))))
minimum_anomaly_value = min(min(min(min( temperature_anomaly .*  (~ missing_values) ))))  %  '~' is 'not' in MATLAB

US_latitude  = 9:12
US_longitude = 15:20
my_years = 1916:2015;
my_slice = temperature_anomaly( US_latitude, :, my_years - 1880 + 1, US_longitude );

total_number_of_grid_squares = length(US_latitude) * length(US_longitude) * 12
N = total_number_of_grid_squares

average_US_anomaly_by_year = reshape( sum(sum(sum( my_slice, 4),2),1), [length(my_years) 1] ) / N;

plot( my_years, average_US_anomaly_by_year )
xlabel('year')
ylabel('avg anomaly (Centigrade) in the US')
title('average US temperature anomaly by year')


% %%% (a) Global Average Temperature Anomaly:  Linear Model (Least Squares)
% 
% ___Problem:___ fit a line through the data, using Least Squares.

% In[13]:

average_global_anomaly_by_year = 0 % fill in something % ..........

linear_model = 0 %  fit_curve( my_years, average_global_anomaly_by_year )  % ..........


% %%% (b) Global Average Temperature Anomaly:  Piecewise Linear Model (Least Squares)
% 
% ___Problem:___ fit a 2-segment piecewise linear model through the data, using Least Squares.
% 
% Specifically, find a pair of least squares models, one from 1916 up to year Y, and one from year Y+1 to 2015, such that the SSE (sum of squared errors) is minimized.
% 

% In[14]:

minimum_SSE = 0

for Y = 1917:2013
   linear_model_up_to_Y = 0; % fit_curve( years_up_to_Y, average_global_anomaly_by_year_up_to_Y )
   linear_model_after_Y = 0; % fit_curve( years_after_Y, average_global_anomaly_by_year_after_Y )
   total_SSE = 0; % SSE_up_to_Y + SSE_after_Y
   if (total_SSE < minimum_SSE)
      do_something = 0;
   end
end


% In[ ]:



