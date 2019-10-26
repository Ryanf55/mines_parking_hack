clf;
A = readmatrix( 'xy_points.csv');
% A = [A(:,2) A(:,1)];
I = rgb2gray(imread('../overhead1.jpg'));
imshow(ones(size(I)));
hold on;
r = 1;

for r = 1:2:size(A,1)
    pointA = A(r,:)
    pointB = A(r+1,:)
    x1 = pointA(1);
    y1 = pointA(2);
    x2 = pointB(1);
    y2 = pointB(2)

    line([x1 x2],[y1 y2],'LineWidth',3,'Color','k')
    %plot([x1 x2],[y1 y2],'*k')

end
%plot(A(:,1),A(:,2),'*k')

gcf
