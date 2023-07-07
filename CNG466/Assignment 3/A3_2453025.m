clear all; clc;


% Read the image
image = imread('OrangesTestExample2.jpg');


% Call the segment_oranges function
segmented_image = segment_oranges(image);

% Call the count_oranges function
[num_small, num_big] = count_oranges(segmented_image);

% Get the variables to the caption, and display it to the title
caption = sprintf('%d Small oranges, %d Big oranges', num_small, num_big);
f2 = figure;
ax2 = axes(f2);
subplot(1,1,1),imshow(segmented_image),title(ax2,caption);



function segmented_image = segment_oranges(image)
  % Convert the image to grayscale image
  I = rgb2gray(image);
  
  % Segment the image I using thresholding-based segmentation with a 
  % threshold value of 250 and obtain the segmented_image
  segmented_image =  I;
  segmented_image(segmented_image<=250) = 0;
  segmented_image(segmented_image>250) = 255;
  
  figure;
  subplot(1,6,1), imshow(segmented_image),title('Segmented Image');
  segmented_image = ~segmented_image;
  subplot(1,6,2), imshow(segmented_image),title('Reversed Version'); 
end

function [num_small, num_big] = count_oranges(segmented_image)
  % Create Structuring Element S with 'disk' and size 4
  S = strel('disk', 4);
  
  % Applying Opening = Erosion and Dilation
    % Erode the image using imerode built-in function and Structuring 
    % element S and obtain image E1
  E1 = imerode(segmented_image, S);
  % Dilate image E1 using imdilate built-in function and Structuring 
    % element S and obtain image D1
  D1 = imdilate(E1, S);
  
  % Applying Closing = Dilation and Erosion
    % Dilate image D1 using imdilate built-in function and Structuring 
    % element S and obtain image D2
  D2 = imdilate(D1,S);
  
  % Erode image D2 using imerode built-in function and Structuring 
    % element S and obtain image E2
  E2 = imdilate(D2,S);
  
  % Find the number of objects in the image using
  % bwconncomp built-in function
  cc = bwconncomp(E2);
  
  % Get the are of oranges, and set it as threshold value
  stats = regionprops(cc, 'Area');
  small_threshold = stats.Area;
  num_small = 0;
  num_big = 0;
  
  % If the area values in the stats array, less than the threshold
  % value increse the small oranges
  % else increase the big oranges
  for i = 1:cc.NumObjects
      if stats(i).Area < small_threshold
          num_small = num_small + 1;
      else
          num_big = num_big + 1;
      end
  end
  
  % Display the steps
  subplot(1,6,3), imshow(E1),title('Opening 1 - Erode');
  subplot(1,6,4), imshow(D1),title('Opening 2 - Dilate');
  subplot(1,6,5), imshow(D2),title('Closing 1 - Dilate');
  subplot(1,6,6), imshow(E2),title('Closing 2 - Erode');
  
  
  
end
