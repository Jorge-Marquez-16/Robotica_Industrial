#include <opencv2/core.hpp> //video capture
#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>   // cv:mat


const int cam_id =0;
const int width=640;
const int height=480;
const int fps=30;

int main(){
    cv::VideoCapture input_video;

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


    while(1){
        input_video.read(input_frame);
        imwrite("Original.jpg", input_frame);   // (nombre de la imagen a guardar, imagen a guardar)
        namedWindow("Original", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
        imshow("Original", input_frame); // (identificador, imagen a mostrar)

        cv::waitKey(1);     // Se espera 1/t milisegundos; Si se ingresa un 0 espera hasta que el usuario cierre la ventana manualmente


    }



    input_video.release();
    return 0;

}