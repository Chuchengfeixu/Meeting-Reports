#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	Mat src;
	src = imread(argv[1], 0);
	
	int x, y, u, v;
	int M, N;
	
	double ang;
	double grayValue;
	double** R, **I;

	M = src.rows;
	N = src.cols;
	
	Mat real(M, N, CV_8UC1, Scalar::all(0));
	Mat imagin(M, N, CV_8UC1, Scalar::all(0));
	Mat dft_mag(M, N, CV_8UC1, Scalar::all(0));
    Mat dft_phase(M, N, CV_8UC1, Scalar::all(0));
    Mat idft(M, N, CV_8UC1, Scalar::all(0));

    //DFT
	R = new double*[M];
	I = new double*[M];
	for (x = 0; x<M; x++){
		R[x] = new double[N];
		I[x] = new double[N];
		for (y = 0; y<N; y++){
			R[x][y] = 0;
			I[x][y] = 0;
			src.at<uchar>(x, y) = pow(-1, x+y)*src.at<uchar>(x, y);  //shift
		}
	}
	for (u = 0; u<M; u++){
		for (v = 0; v<N; v++){
			R[u][v] = 0.0;
			I[u][v] = 0.0;
			for (x = 0; x<M; x++){
				for (y = 0; y<N; y++){
					grayValue = src.at<uchar>(x, y);
					ang = 2 * M_PI*((double)x*u / (double)M + (double)y*v / (double)N);
					R[u][v] += cos(ang)*grayValue;
					I[u][v] += -sin(ang)*grayValue;
				}
			}
            
                real.at<uchar>(u, v) = R[u][v];
                imagin.at<uchar>(u, v) = I[u][v];
		}
	}
   
    
	imwrite("dft_real.png", real);
	imwrite("dft_imagin.png", imagin);
    
    //phase map
    for (u = 0; u<M; u++){
        for (v = 0; v<N; v++){
            dft_phase.at<uchar>(u, v)=atan2(I[u][v],R[u][v])*180/M_PI;
        }
    }
    imwrite("dft_phase.png",dft_phase);
    
    //Amplitude map(normalization)
   	double max_dst = 0;
	for (u = 0; u<M; u++){
		for (v = 0; v<N; v++){
			dft_mag.at<uchar>(u, v) = (int)log(1 + sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v]));
			if (max_dst < dft_mag.at<uchar>(u, v))
				max_dst = dft_mag.at<uchar>(u, v);
		}
	}
        
	for (u = 0; u < M; u++){
		for (v = 0; v < N; v++)
		{
			dft_mag.at<uchar>(u, v) *= 255.0/max_dst;
		}
	}
    imwrite("dft_mag.png", dft_mag);
    
    //IDFT
	
 double phase;
    double** r, **i;
    r = new double*[M];
    i = new double*[M];
    for(x=0;x<M;x++){
        r[x]=new double[N];
        i[x]=new double[N];
    }
    for(u=0;u<M;u++){
        for(v=0;v<N;v++){
            R[u][v]=sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v])*cos(dft_phase.at<uchar>(u, v));
            I[u][v]=sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v])*sin(dft_phase.at<uchar>(u, v));
        }
    }
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
            r[x][y]=0.0;
            i[x][y]=0.0;
            for(u=0;u<M;u++){
                for(v=0;v<N;v++){
                    ang=2*M_PI*((double)x*u/(double)M+(double)y*v/(double)N);
                    r[x][y]+=R[u][v]*cos(ang)-I[u][v]*sin(ang);
                    i[x][y]+=I[u][v]*cos(ang)+R[u][v]*sin(ang);
                  /*phase=atan(I[u][v]/R[u][v])*180/M_PI;
                    r[x][y]+=sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v])*cos(phase+ang);
                    i[x][y]+=sqrt(R[u][v] * R[u][v] + I[u][v] * I[u][v])*sin(phase+ang);*/
                    
                }
            }
            real.at<uchar>(x,y)=r[x][y]/(M*N);
            imagin.at<uchar>(x,y)=i[x][y]/(M*N);
    
            
        }
    }
    imwrite("idft_real.png", real);
    imwrite("idft_imagin.png", imagin);
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
            idft.at<uchar>(x,y) =sqrt(r[x][y] * r[x][y]);
        }
    }
    imwrite("idft.bmp",idft);
    for(x=0;x<M;x++){
        for(y=0;y<N;y++){
           idft.at<uchar>(x, y) = pow(-1, x+y)*sqrt(r[x][y] * r[x][y] + i[x][y] * i[x][y])/(M*N);
        }
    }
    imwrite("idft_shift.png",idft);

	return 0;

}
