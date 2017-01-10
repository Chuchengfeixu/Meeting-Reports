%Name:Histogram_Equalization
%Author:Hao Ding
%Student ID:21160211113

clear all;
close all;
clc;                                  %Initialization

src = imread('einstein.jpg');                %import the image
fig = rgb2gray(src);

%histogram
outputimage = histeq(fig);

%AHE
J = adapthisteq(fig);

%CLAHE
A = adapthisteq(fig,'clipLimit',0.02,'Distribution','rayleigh');

%outputing

figure
subplot(4,2,1);imshow(fig);title('origin');
subplot(4,2,2);imhist(fig,64);title('origin-histogram');

subplot(4,2,3);imshow(outputimage);title('HE');
subplot(4,2,4);imhist(outputimage,64);title('HE-histogram');

subplot(4,2,5);imshow(J);title('AHE');
subplot(4,2,6);imhist(J,64);title('AHE-histogram');

subplot(4,2,7);imshow(A);title('CLAHE');
subplot(4,2,8);imhist(A,64);title('CLAHE-histogram');
