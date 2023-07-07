% I read the image in the current directory
A = imread('Image1.png');

% I created a figure by using subplot to show
% the original image and the histogram in the same figure
figure, subplot(1,2,1), imshow(A); title('Original Image');
subplot(1,2,2), imhist(A); title('Histogram of Image1');

% I used histeq function to enhance the image.
% Because the image is quite dark, the enhancement is visible enough.
Image1Output = histeq(A);

% I saved the image in the current directory bu using imwrite function
imwrite(Image1Output, 'Image1Output.png');

% I displayed the enhanced image and the histogram by using subplot
figure, subplot(1,2,1), imshow(Image1Output); title('Image1Output');
subplot(1,2,2), imhist(Image1Output); title('Histogram of Image1Output');