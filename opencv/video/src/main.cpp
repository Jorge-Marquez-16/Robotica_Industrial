#include <opencv2/core.hpp> // cv Mat
#include <iostream>
#include <opencv2/imgproc.hpp>//filtros
//#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>//video capture

#include <opencv2/opencv.hpp>   // cv:mat


const int cam_id =0;
const int width=640;
const int height=480;
const int fps=30;

const char* window_name = "Images Filters";
const char* trackbar_name = "Filter Type: \n 0. Default 1. Threshold 2. Log 3. Smoothing 4. Kernel 5. Edge 6. Color Segmentation";
const int trackbar_max_value = 6;
const char* threshold_name = "0. Binary 1. Binary Inverted 2. Truncate 3. To Zero 4. To Zero Inverted";
const int threshold_max_value = 4;
const int threshold_value_max_value = 255;
const char* threshold_value_name = "Threshold Value: ";

const char* smoothing_name = "0. Homogeneous 1. Gaussian 2. Median";
const int smoothing_max_value = 2;

void smoothing(cv::Mat& src, cv::Mat& dst, int type);


int main(){
    cv::VideoCapture input_video;
    int trackbar_value=0;
    int threshold_filter=0;
    int threshold_value=125;
    int smoothing_value=0;

    int high_H =179;
    int high_S =255;
    int high_V =255;


    int low_H =0;
    int low_S =0;
    int low_V =0;


    input_video.open(cam_id);

    if(!input_video.isOpened())
    {
        std::cout <<"Cam not opened..\n\r";
        return -1;
    }

    input_video.set(cv::CAP_PROP_FRAME_WIDTH, width);
    input_video.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    input_video.set(cv::CAP_PROP_FPS,fps);

    std::cout<< "camera fps:::  " << input_video.get(cv::CAP_PROP_FPS)<<"\n\r";
    cv::Mat input_frame;

    cv::Mat output_frame;

    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    //namedWindow("Original", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    cv:: createTrackbar(trackbar_name ,window_name, &trackbar_value,trackbar_max_value);
    //cv:: createTrackbar(threshold_name ,window_name, &threshold_filter,threshold_max_value);
    //cv:: createTrackbar(threshold_value_name ,window_name, &threshold_value,threshold_value_max_value);
    //cv:: createTrackbar(smoothing_name ,window_name, &smoothing_value,smoothing_max_value);

    cv:: createTrackbar("LowH" ,window_name, &low_H, 179);
    cv:: createTrackbar("LowS" ,window_name, &low_S, 255);
    cv:: createTrackbar("LowV" ,window_name, &low_V, 255);

    cv:: createTrackbar("HighH" ,window_name, &high_H, 179);
    cv:: createTrackbar("HighS" ,window_name, &high_S, 255);
    cv:: createTrackbar("HighV" ,window_name, &high_V, 255);




    while(1){
        input_video.read(input_frame);

        if(trackbar_value==0){
            output_frame=input_frame;
        }
        if(trackbar_value==1){
            cvtColor(input_frame, output_frame, cv::COLOR_BGR2GRAY);
            threshold(output_frame , output_frame , threshold_value , threshold_value_max_value , threshold_filter);
        }
        if(trackbar_value==2){
            input_frame.convertTo(output_frame, CV_32F);
            output_frame = output_frame + 1;
            cv::log(output_frame, output_frame);
            cv::convertScaleAbs(output_frame , output_frame);
            cv::normalize(output_frame , output_frame , 0 , 255 , cv::NORM_MINMAX);
        }

        if(trackbar_value==3){

            smoothing(input_frame , output_frame , smoothing_value);


        }

        if (trackbar_value==4){
            cv::Mat kernel=(cv::Mat_<char>(3,3)<<0, -1, 0,
                                                -1,  10, -1,
                                                 0, -1 ,0);
            filter2D(input_frame,output_frame, input_frame.depth(),kernel);
        }

        if (trackbar_value==5){
            cv::Mat dst;
            GaussianBlur(input_frame, dst, cv::Size(3,3),0 ,0);
            cvtColor(dst,dst, cv::COLOR_BGR2GRAY);
            Laplacian(dst, output_frame, CV_16S,3,1,0, cv::BORDER_DEFAULT);
            cv::convertScaleAbs(output_frame,output_frame);
        }

        if (trackbar_value==6){
            cv::Mat imgHSV;
            cvtColor(input_frame, imgHSV, cv::COLOR_BGR2HSV);
            inRange(imgHSV, cv::Scalar(low_H,low_S,low_V), cv::Scalar(high_H,high_S,high_V), output_frame);
        }


        cv::imshow(window_name, output_frame); // (identificador, imagen a mostrar)

        cv::waitKey(1);     // Se espera 1/t milisegundos; Si se ingresa un 0 espera hasta que el usuario cierre la ventana manualmente


    }
    input_video.release();
    return 0;

}



void smoothing(cv::Mat& src, cv::Mat& dst, int type){

    if (type==0){
        int kernel_size=7;
        blur(src, dst, cv::Size(kernel_size,kernel_size), cv::Point(-1,-1));
    }
    if (type==1){
        int kernel_size=7;
        GaussianBlur(src,dst, cv::Size(kernel_size,kernel_size),0,0);
    }
    if(type==2){
        int kernel_size=7*3;
        medianBlur(src,dst, kernel_size);
    }
}
