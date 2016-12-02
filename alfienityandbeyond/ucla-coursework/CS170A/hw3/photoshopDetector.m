function photoshopped = photoshopDetector(photo)
% Save photo as m x n RGB image and obtain dimensions
PhotoRGB = imread(photo);
sizePhoto = size(PhotoRGB);
m = sizePhoto(1);
n = sizePhoto(2);

% Reshape image into (m*n) x 3
ReshapedPhoto = reshape(PhotoRGB, m*n, 3);

% Find the covariance of the reshaped image with its principal components
CovReshapedPhoto = cov(double(ReshapedPhoto));
[U,S,V] = svd(CovReshapedPhoto);
PCs = U(:, 1:3);
PCTwo = PCs(:,2);

% Project image into its second principal component and reshape to m x n
ReshapedBackPhoto = double(ReshapedPhoto)*double(PCTwo);
ReshapedBackPhoto = reshape(uint8(ReshapedBackPhoto), m, n);

% Show grayscale image to see bright spots for possible photoshop editing
imshow(ReshapedBackPhoto);

end