#include <iostream>     // cout
#include <opencv2/opencv.hpp>   // cv:mat

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>


const int cam_id =0;
const int width=640;
const int height=480;
const int fps=30;

const int total_pix=width*height;

const char* window_name = "Otsu_binarization ";

double Proba(int idx, cv::Mat& hist, int total_pix);
double W1_cluster(int t_var, cv::Mat& hist, int total_pix);
double u1_cluster(int t_var, cv::Mat& hist, int total_pix);
double W2_cluster(int t_var, cv::Mat& hist, int total_pix);
double u2_cluster(int t_var, cv::Mat& hist, int total_pix);
double inter_class_variance(int t_var, cv::Mat& hist, int total_pix);
int SETUP(cv::VideoCapture& src);
void Otsu_binarization(cv::Mat& src, cv::Mat& dst);
void binarization(cv::Mat& src, cv::Mat& dst, int threshold);


const int threshold_value_max_value = 255;
const int histSize = 256;
float range[] = { 0, 256 }; //the upper boundary is exclusive
const float* histRange[] = { range };
bool uniform = true, accumulate = false;
cv::Mat image_gray; 
cv::Mat hist_GRAY;

int main(int argc, char** argv)
{
    cv::VideoCapture input_video;
    input_video.open(cam_id);

    SETUP(input_video);
    cv::Mat input_frame;
    cv::Mat output_frame;


    input_video.set(cv::CAP_PROP_FRAME_WIDTH, width);
    input_video.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    input_video.set(cv::CAP_PROP_FPS,fps);
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    //cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
  


    while(1){
        input_video.read(input_frame);
        cvtColor(input_frame, output_frame, cv::COLOR_BGR2GRAY);

        Otsu_binarization( output_frame, output_frame);
        cv::imshow(window_name, output_frame); // (identificador, imagen a mostrar)
        //cv::imshow("Original", input_frame); // (identificador, imagen a mostrar)

        cv::waitKey(1);     // Se espera 1/t milisegundos; Si se ingresa un 0 espera hasta que el usuario cierre la ventana manualmente

    }
    //threshold(image_gray , image_gray , threshold_value , threshold_value_max_value , threshold_filter);

  
    input_video.release();

    return EXIT_SUCCESS;
}


double Proba(int idx, cv::Mat& hist, int total_pix){
    return ((hist.at<float>(idx))/(total_pix));
}

double W1_cluster(int t_var, cv::Mat& hist, int total_pix){
    double sum=0;
    int idx=1;
    do{
        sum+=Proba(idx,hist,total_pix) ;
        idx++;
    }while(idx <= t_var);
    return sum;
}
double W2_cluster(int t_var, cv::Mat& hist, int total_pix){
    double sum=0;
    int idx=t_var+1;
    do{
        sum+=Proba(idx,hist,total_pix) ;
        idx++;
    }while(idx < histSize);
    return sum;
}

double u1_cluster(int t_var, cv::Mat& hist, int total_pix){
    double sum=0;

    int idx=1;
    do{
        sum+=(idx*Proba(idx, hist,  total_pix))/W1_cluster(t_var, hist, total_pix);
        idx++;
    }while( idx <= t_var);
    return sum;
}

double u2_cluster(int t_var, cv::Mat& hist, int total_pix){
    double sum=0;
    int idx=t_var+1;
    do{
        sum+=(idx*Proba(idx, hist,  total_pix))/W2_cluster(t_var, hist, total_pix);
        idx++;
    }while(idx < histSize);
    return sum;
}

double inter_class_variance(int t_var, cv::Mat& hist, int total_pix){
    return (W1_cluster(t_var, hist,  total_pix)*W2_cluster(t_var, hist, total_pix)*pow((u1_cluster(t_var,hist, total_pix)-u2_cluster(t_var, hist, total_pix)),2));
}


void Otsu_binarization(cv::Mat& src, cv::Mat& dst){
    float sum=0.0;
    double variant_max=0.0;
    double t_variant=0.0;
    int threshold_value=0;
    int threshold_filter=0;
    cv::calcHist( &src, 1, 0, cv::Mat(), hist_GRAY, 1, &histSize, histRange, uniform, accumulate );
    int t_var = 1;
    do{
        t_variant=inter_class_variance(t_var, hist_GRAY, total_pix);
        variant_max= (variant_max<t_variant) ? t_variant : variant_max;
        t_var++;
    }while(t_var < histSize);
    threshold_value=int (sqrt(variant_max));
    binarization(dst, dst, threshold_value);
}



void binarization(cv::Mat& src, cv::Mat& dst, int threshold){    
    int cols=src.cols;
    int rows=src.rows;

    uchar* pixelPtr=(uchar*)src.data;
    uchar* pixelPtr_img_new=(uchar*)dst.data;

    for (int id_rows=0; id_rows<rows; id_rows++){               
        for(int id_cols=0; id_cols<cols; id_cols++){

            uchar gray= pixelPtr[id_rows*cols + id_cols];
                
            pixelPtr_img_new[id_rows*cols + (id_cols)]=(gray<threshold)? 0 : 255;
        }

    }
}



int SETUP(cv::VideoCapture& src ){
    if(!src.isOpened())
    {
        std::cout <<"Cam not opened..\n\r";
        return -1;
    }
    return 0;
}