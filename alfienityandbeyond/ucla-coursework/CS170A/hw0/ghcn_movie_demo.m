%%%%%%  This script only works in Matlab -- it uses the 'getframe' command and movie() function.

GHCN = csvread('ghcn.csv');

%  the data was artificially shifted to [0, 4500]; its range should be [-2500, +2000]/100, in degrees Centigrade

rescaled_GHCN = max(-5, (GHCN(:,3:74) - 2500)/100);   %  we skip the year and month in the first two columns
temperature_anomaly = reshape( rescaled_GHCN, [36, 12, 137, 72] );

month = { 'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December' };

year_month_anomaly = @(Y,M) reshape( temperature_anomaly(:, M, Y-1880+1, :), [36 72])

colormap(hot)

i = 1;
for y=1880:2016
   m = 7;   % display result for July (m=7) only
   % for m=1:12
      image(uint8((year_month_anomaly(y,m)+5)/25 * 265));
      colorbar
      title(sprintf('%s %4d', month{m},y), 'FontSize', 28);
      M(i) = getframe;
      i = i + 1;
   % end
end

movie(M)

