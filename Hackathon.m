RGB = imread('parking1.png');
[height, width, numberOfColorChannels] = size(RGB);

I = im2bw(RGB); % Convert to binary image 

I = double(I); % Convert image to double

% Apply an averaging filter to the image to create an image of local means.
I2 = imfilter(I, fspecial('average', width));
Idiff = I - I2; % Subtract the local average image from the original.

% Segment white blobs
W = Idiff>0;  

% creates structuring element, a disk of radius 1 and 0
Sopen = strel('disk', 0);
Sclose = strel('disk', 2);

%opening 
openI = imopen(W, Sopen);

%closing
closeI = imclose(openI, Sclose);
%imshow(closeI);

%IFlip = imcomplement(closeI);

% find white blobs (L) and number of blobs (n)
[L, n] = bwlabel(closeI);

Q = label2rgb(L);

imshow(Q);

% find black blobs (LFlip) and number of blobs (nFlip)
%[LFlip, nFlip] = bwlabel(IFlip);

carBlobs = regionprops(L, 'Area', 'BoundingBox', 'Centroid', 'Perimeter');




