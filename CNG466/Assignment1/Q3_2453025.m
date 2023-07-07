% I read the image in the current directory
Image3 = imread('Image3.png');

% I created a new matrix with zeros
[Row, Column, Layer] = size(Image3);
D = zeros(Row, Column);

% I filtered the image by using thresholding
% I decided the thresold value as 150, so
% every pixel greater than 150 is set as '1'
% otherwise '0'
      
for i = 1:Row
    for j = 1:Column
        if(Image3(i, j) >= 150)
            D(i, j) = 1;
        else
            D(i, j) = 0;
        end
    end
end

% After this operation the brightest star can seen easily

figure, subplot(1,2,1), imshow(Image3); title('Image3.png');
subplot(1,2,2), imshow(D); title('Image3Output.png');


