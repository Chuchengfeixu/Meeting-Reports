%read the image
image = imread('1.tif');
figure(1);
imshow(image);

%fourier transform
fourier = fft2(image);
dst = abs(fourier);
figure(2);
imshow(dst,[]);

%move to centre
centre = fftshift(dst);
figure(3);
imshow(abs(centre),[]);

%reinform
%amplitude
amplitude_ima = log(1 + abs(centre));
figure(4);
imshow(amplitude_ima,[]);

%phase
phase_ima = atan2(imag(fourier),real(fourier));
figure(5);
imshow(phase_ima,[]);

%idft
f = real(ifft2(fourier));
figure(6);
imshow(f,[]);


%threeD_mod_ima_log = log2(mod_ima)+1;
%[x1,y1] = size(threeD_mod_ima_log);
%[a1,b1]=meshgrid(1:x1,1:y1);  
%figure,subplot(1,2,1),mesh(a1,b1,threeD_mod_ima_log);   
%shading interp;         

%[x2,y2] = size(phase_ima);
%[a2,b2] = meshgrid(1:x2,1:y2);
%subplot(1,2,2),mesh(a2,b2,phase_ima); 
%shading interp; 
