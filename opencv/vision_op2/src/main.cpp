#include <iostream>     // cout
#include <opencv2/opencv.hpp>   // cv:mat



int main(int argc, char** argv)
{
    
    if(argc != 2)
    {
        std::cout <<"usage: ./img_gray <Image_Path>\n";
        return 1;
    }

    cv::Mat image;

    image = imread(argv[1], cv::IMREAD_COLOR);
    if(image.data == 0)
    {
        std::cout <<"No valid data\n";
        return 1;
    }
    
   

    piramid imagen_1(image,3);
    imagen_1.piramidal_small();
    piramid imagen_2(image,2);
    imagen_2.piramidal_big();
    imagen_1.show_original();
    imagen_1.show_new();
    imagen_2.show_new();

   
   

    
    return 0;
}

