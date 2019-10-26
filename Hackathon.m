clear
clf
%%
clf;
A = readmatrix( 'xy_points.csv');
% A = [A(:,2) A(:,1)];
I = rgb2gray(imread('overhead1.jpg'));
imshow(ones(size(I)));
hold on;
r = 1;

for r = 1:2:size(A,1)
    pointA = A(r,:);
    pointB = A(r+1,:);
    x1 = pointA(1);
    y1 = pointA(2);
    x2 = pointB(1);
    y2 = pointB(2);

    line([x1 x2],[y1 y2],'LineWidth',3,'Color','k');
    
    %plot([x1 x2],[y1 y2],'*k')

end
%plot(A(:,1),A(:,2),'*k')
saveas(gcf,'ov_mask_sized.jpg');
imshow(imread('overhead1.jpg'));
saveas(gcf,'ov1_sized.jpg');
I_changedCar = imshow(imread('overhead2.jpg'));
saveas(gcf,'ov2_sized.jpg');

%% 
spotLinesBinary = imread('ov_mask_sized.jpg');
RGB =  imread('ov1_sized.jpg');
[height, width, numberOfColorChannels] = size(spotLinesBinary);

I = im2bw(spotLinesBinary(:,:,1)); % Convert to binary image 

I = double(I); % Convert image to double
disp('G')
% Apply an averaging filter to the image to create an image of local means.
I2 = imfilter(I, fspecial('average', width));
Idiff = I - I2; % Subtract the local average image from the original.
disp('E')
% Segment white blobs
W = Idiff>0;  

% creates structuring element, a disk of radius 1 and 0
Sopen = strel('disk', 0);
Sclose = strel('disk', 1);
disp('C')

%opening 
openI = imopen(W, Sopen);

%closing
closeI = imclose(openI, Sclose);
%imshow(closeI);
disp('A')
%IFlip = imcomplement(closeI);

% find white blobs (L) and number of blobs (n)
[L, n] = bwlabel(closeI);

Q = label2rgb(L);
disp('B')
imshow(Q);

% find black blobs (LFlip) and number of blobs (nFlip)
%[LFlip, nFlip] = bwlabel(IFlip);

carBlobs = regionprops(L, 'Area', 'BoundingBox', 'Centroid', 'Perimeter');
hold on;

%%
clf;
clc;
imshow(Q);
prev_img = imread('ov2_sized.jpg');

%imshow(prev_img - RGB);
%pause;

% Exclude based on Area

spotsChanged = zeros(length(carBlobs),1);
for i = 1:length(carBlobs)
    disp('X')
    myBlob = carBlobs(i);
    myBlobCentroid = myBlob.Centroid;
    if myBlob.Area < 100000
        %plot(myBlobCentroid(1),myBlobCentroid(2),'*k')
        text(myBlobCentroid(1)-12,myBlobCentroid(2),sprintf('%d',i-1))
        
        %parkingSpotMask = (L == i);
        %imshow(parkingSpotMask);
       
        maskedRGB_latest =RGB.* repmat(uint8((L == i)),1,1,3);
        maskedRGB_previous =prev_img.* repmat(uint8((L == i)),1,1,3);
        subplot(1,3,1);
        imshow(maskedRGB_latest - maskedRGB_previous);
        subplot(1,3,2);
        imshow(maskedRGB_latest);
        subplot(1,3,3);
        imshow(maskedRGB_previous);
        drawnow;

        naiveDiff = sum(sum(sum(maskedRGB_latest - maskedRGB_previous)));
        if  naiveDiff > 500
            fprintf('Spot %d has changed state by %d\n',i,naiveDiff)
            spotsChanged(i) = naiveDiff;
        end
        
  
        %imshow(maskedRGB);
        %pause(10);
    end
end





