% I read the image in the current directory
Image2 = imread('Image2.png');

% I chose median filter method, so
% I need to get the size of the matrix because
% I need a pad to use median filter in order to
% remove the noise in the image
[rows, columns, layers] = size(Image2);
Pad = zeros(rows + 2, columns + 2);
b = 0;

% I copied the matrix to the pad
Pad(1:rows, 1:columns) = Image2;
% I created an array to sort the values
Window = (1:9);
% I need a key value to use insertion sort
key = 0;

% In the first two loop, the values are copied to the window array
for i = 1:rows
    for j = 1:columns
        Window(1,1) = Pad(i, j);
        Window(1,2) = Pad(i, j + 1);
        Window(1,3) = Pad(i, j + 2);
        Window(1,4) = Pad(i + 1, j);
        Window(1,5) = Pad(i + 1, j + 1);
        Window(1,6) = Pad(i + 1, j + 2);
        Window(1,7) = Pad(i + 2, j);
        Window(1,8) = Pad(i + 2, j + 1);
        Window(1,9) = Pad(i + 2, j + 2);
        
        % Insertion sort
        for a = 2:9
            key = Window(1,a);
            b = a - 1;
            while (b >= 1) && (Window(1,b) > key)
                Window(1, b+1) = Window(1,b);
                b = b - 1;
            end
            Window(b + 1) = key;
        end
        Pad(i, j) = Window(1, 5);
    end
end

% I converted the values to 0-255 range
Pad = uint8(Pad);

% I filtered the image, by using Sobel Operator
% I got the filter from the lecture notes
Hx = [-1 -2 -1; 0 0 0; 1 2 1];
Hy = [-1 0 1; -2 0 2; -1 0 1];

% I need to convert the values to double
Pad2 = double(Pad);
Edges = zeros(size(Pad2));

Image2_2 = double(Image2);
Edges2 = zeros(size(Image2_2));

% I used convolution
for a1 = 1:size(Pad2, 1) - 2
    for b1 = 1:size(Pad2, 2) - 2
  
        % Horizontal and Vertical Edges
        Gx = sum(sum(Hx.*Pad2(a1:a1+2, b1:b1+2)));
        Gy = sum(sum(Hy.*Pad2(a1:a1+2, b1:b1+2)));
                 
        % I calculated the edge vector
        Edges(a1+1, b1+1) = sqrt(Gx.^2 + Gy.^2);
         
    end
end

for a1 = 1:size(Image2_2, 1) - 2
    for b1 = 1:size(Image2_2, 2) - 2
  
        % Horizontal and Vertical Edges
        Gx = sum(sum(Hx.*Image2_2(a1:a1+2, b1:b1+2)));
        Gy = sum(sum(Hy.*Image2_2(a1:a1+2, b1:b1+2)));
                 
        % I calculated the edge
        Edges2(a1+1, b1+1) = sqrt(Gx.^2 + Gy.^2);
         
    end
end

% I converted the values to 0-255 range
Edges = uint8(Edges);
Edges2 = uint8(Edges2);

figure, subplot(1, 4, 1), imshow(Image2); title('Image2.png');
subplot(1, 4, 2), imshow(Pad); title('Image2Output.png');
subplot(1, 4, 3), imshow(Edges2); title('Edges of Image2.png');
subplot(1, 4, 4), imshow(Edges); title('Edges of Image2Output.png');

% It can be seen that this operation is very sensitive to noises


            
            
                
        
        


