%Name:Histogram_Equalization
%Author:Hao Ding
%Student ID:21160211113

clear all;
close all;
clc;                                  %Initialization

src = imread('einstein.jpg');                %import the image
fig = rgb2gray(src);

%AHE
J = adapthisteq(fig,'NumTiles',[8 8],'ClipLimit',0.2,'Distribution','uniform');
J1 = adapthisteq(fig,'NumTiles',[8 8],'ClipLimit',0.2,'Distribution','rayleigh');
J2 = adapthisteq(fig,'NumTiles',[8 8],'ClipLimit',0.2,'Distribution','exponential');

%outputing

figure
subplot(4,2,1);imshow(fig);title('origin');
subplot(4,2,2);imhist(fig,64);title('origin-histogram');

subplot(4,2,3);imshow(J);title('uniform');
subplot(4,2,4);imhist(J,64);title('uniform-histogram');

subplot(4,2,5);imshow(J1);title('rayleigh');
subplot(4,2,6);imhist(J1,64);title('rayleigh-histogram');

subplot(4,2,7);imshow(J2);title('exponential');
subplot(4,2,8);imhist(J2,64);title('exponential-histogram');