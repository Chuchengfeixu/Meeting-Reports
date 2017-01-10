%Name:Histogram_Equalization
%Author:Hao Ding
%Student ID:21160211113

clear all;
close all;
clc;                                  %Initialization

src = imread('einstein.jpg');                %import the image
fig = rgb2gray(src);

%AHE
J = adapthisteq(fig,'NumTiles',[2 2],'ClipLimit',0.2,'Distribution','exponential');
J1 = adapthisteq(fig,'NumTiles',[4 4],'ClipLimit',0.2,'Distribution','exponential');
J2 = adapthisteq(fig,'NumTiles',[8 8],'ClipLimit',0.2,'Distribution','exponential');
J3 = adapthisteq(fig,'NumTiles',[12 12],'ClipLimit',0.2,'Distribution','exponential');

%outputing

figure
subplot(5,2,1);imshow(fig);title('src');
subplot(5,2,2);imhist(fig,64);title('src-histogram');

subplot(5,2,3);imshow(J);title('2*2');
subplot(5,2,4);imhist(J,64);title('2*2-histogram');

subplot(5,2,5);imshow(J1);title('4*4');
subplot(5,2,6);imhist(J1,64);title('4*4-histogram');

subplot(5,2,7);imshow(J2);title('8*8');
subplot(5,2,8);imhist(J2,64);title('8*8-histogram');

subplot(5,2,9);imshow(J3);title('12*12');
subplot(5,2,10);imhist(J3,64);title('12*12-histogram');