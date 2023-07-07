% ---------------- Q1 ---------------
clear all;clc;

noisy1 = imread('noisy1.png');

%take a block from the image
blockOfnoisy1 = noisy1(1060:1130,300:320);

% by looking to the histogram of the block image
% we can easily see that there is a uniform additive noise
% , so by using midpoint filter we can remove it.

% create a pad and copy noisy1 to the pad
[rows, columns] = size(noisy1);
pad = ones(rows + 2, columns + 2);
pad(1:rows, 1:columns) = noisy1;
% created an array to sort the values
arr = (1:9);
recovered1 = pad;

for i = 1:rows
    for j = 1:columns
        arr(1,1) = pad(i, j);
        arr(1,2) = pad(i, j + 1);
        arr(1,3) = pad(i, j + 2);
        arr(1,4) = pad(i + 1, j);
        arr(1,5) = pad(i + 1, j + 1);
        arr(1,6) = pad(i + 1, j + 2);
        arr(1,7) = pad(i + 2, j);
        arr(1,8) = pad(i + 2, j + 1);
        arr(1,9) = pad(i + 2, j + 2);
        %sort the array to get the max and min
        arr = sort(arr);
        recovered1(i, j) = (arr(1, 1) + arr(1,9))/2;
    end
end
recovered1 = uint8(recovered1);
recovered1 = recovered1(2:1310, 2:1921);
diff = noisy1 - recovered1;
figure, subplot(2,2,1), imshow(noisy1);title('noisy1.png');
subplot(2,2,2), imhist(blockOfnoisy1);title('Histogram of the noise');
subplot(2,2,3), imshow(recovered1);title('recovered1.png');
subplot(2,2,4), imshow(diff);title('Differences of edges');
% write the image
imwrite(recovered1, 'recovered1.png');

% ------------ Q2 -------------------

clear all;clc;

noisy2 = imread('noisy2.png');

% there is a periodic noise in this image
% , so it can be viewed in frequency domain

% computed DFT
F= fft2(noisy2);
F = fftshift(F);

% bandreject filter can be used to remove the noise
% I chose the gaussian type
[M,N] = size(noisy2);
D0 = 65; % cutoff value
n = 2; %order
W = 50; %width
for u = 1:M
    for v = 1:N
        D(u,v) = ((u-(M/2))^2 + (v-(N/2))^2 )^(1/2);
    end
end

%filter is created
Hbp = 1 - exp(-(((D.^2 - D0.^2)./(D .* W)).^2));
Hbr = 1 - Hbp;
%filter the image
G = F .* Hbp;
%compute inverse DFT
G2 = ifft2(G);
G2 = abs(G2);
G3= uint8(255 * mat2gray(G2));

% difference between noisy2 and recovered image
diff2 = noisy2 - G3;


figure, subplot(3,2,1), imshow(noisy2); title('noisy2.png');
subplot (3,2,2), imshow(log(abs(F)),[]); title('Frequency Domain');
subplot(3,2,3), imshow(Hbp, []); title('Gaussian BandReject Filter');
subplot(3,2,4), imshow(log(abs(G)), []); title('F(x) * G(x)');
subplot(3,2,5), imshow(G3); title('recovered2.png');
subplot(3,2,6), imshow(diff2); title('Difference between edges');
% write the image
imwrite(G3, 'recovered2.png');
% ---------------- Q3 ----------------
clear all;clc;

noisy3 = imread('noisy3.tif');

% there is a periodic noise in this image
% , so it can be viewed in frequency domain

% compute DFT
F= fft2(noisy3);
F = fftshift(F);

% notchreject filter can be used to remove the noise
% as we can see from the fourier spectrum there are 8 white spots, so
% we need 4 notch pairs
% I need to do same computation for each pair and multiply
% with notch reject filter(Hnr)
% at the end the white spots will be covered by black dots
% and the noise will be removed
[M,N] = size(noisy3);

% first pair
D0 = 9;
n = 4;
uk = 38;
vk = 30;

for u=1:M
    for v=1:N
        Dkp(u,v)=((u-(M/2)-uk)^2 + (v-(N/2)-vk)^2 )^(1/2);
        Dkn(u,v)=((u-(M/2)+uk)^2 + (v-(N/2)+vk)^2 )^(1/2);
    end
end

Hnr = (1./(1 + (D0./Dkp).^(2*n))) .* (1./(1 + (D0./Dkn).^(2*n)));

% update D0, uk, vk for the second pair
D0 = 9, uk = -42, vk = 27;
for u=1:M
    for v=1:N
        Dkp(u,v)=((u-(M/2)-uk)^2 + (v-(N/2)-vk)^2 )^(1/2);
        Dkn(u,v)=((u-(M/2)+uk)^2 + (v-(N/2)+vk)^2 )^(1/2);
    end
end

Hnr = Hnr .* (1./(1 + (D0./Dkp).^(2*n))) .* (1./(1 + (D0./Dkn).^(2*n)));

%update for the 3rd pair
D0 = 9, uk = 80, vk = 30;
for u=1:M
    for v=1:N
        Dkp(u,v)=((u-(M/2)-uk)^2 + (v-(N/2)-vk)^2 )^(1/2);
        Dkn(u,v)=((u-(M/2)+uk)^2 + (v-(N/2)+vk)^2 )^(1/2);
    end
end

Hnr = Hnr .* (1./(1 + (D0./Dkp).^(2*n))) .* (1./(1 + (D0./Dkn).^(2*n)));

% update for the 4th pair
D0 = 9, uk = -82, vk = 28;
for u=1:M
    for v=1:N
        Dkp(u,v)=((u-(M/2)-uk)^2 + (v-(N/2)-vk)^2 )^(1/2);
        Dkn(u,v)=((u-(M/2)+uk)^2 + (v-(N/2)+vk)^2 )^(1/2);
    end
end
Hnr = Hnr .* (1./(1 + (D0./Dkp).^(2*n))) .* (1./(1 + (D0./Dkn).^(2*n)));


% multiply the filter with fourier 
G = F .* Hnr;
% inverse DFT
G2 = ifft2(G);
G2 = abs(G2);
G3= uint8(255 * mat2gray(G2));

diff3 = noisy3 - G3;

figure, subplot(3,2,1), imshow(noisy3); title('noisy3.tif');
subplot(3,2,2), imshow(log(abs(F)),[]); title('DFT of noisy3.tif');
subplot(3,2,3), imshow(Hnr, []); title('Butterworth Notch Reject Filter');
subplot(3,2,4), imshow(log(abs(G)), []); title('F(x) * Hr');
subplot(3,2,5), imshow(G3), title('recovered3.png');
subplot(3,2,6), imshow(diff3), title('Difference of edges');
% write the image
imwrite(G3, 'recovered3.png');

