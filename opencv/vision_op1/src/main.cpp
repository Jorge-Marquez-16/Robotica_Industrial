// ENcontrar documentacion docs.opencv.org
// En este archivo es donde se programarà la pràctica


#include <iostream>     // cout
#include <opencv2/opencv.hpp>   // cv:mat
        // argc #params, argv ?params

void fast_gray(cv::Mat &src, cv::Mat &dst);


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
    
    cv::Mat image_gray;
    fast_gray(image, image_gray);

    imwrite("result.jpg", image);   // (nombre de la imagen a guardar, imagen a guardar)
    imwrite("result_cust.jpg", image_gray);   // (nombre de la imagen a guardar, imagen a guardar)
    namedWindow("Gray", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    namedWindow("Gray_custom", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    imshow("Gray", image); // (identificador, imagen a mostrar)
    imshow("Gray_custom", image_gray); // (identificador, imagen a mostrar)

   
    cv::waitKey(0);     // Se espera 1/t milisegundos; Si se ingresa un 0 espera hasta que el usuario cierre la ventana manualmente

    
    return 0;
}




// imagen rgb, imagen donde se guardara en gris

void fast_gray(cv::Mat &src, cv::Mat &dst)
{
    int rows = src.rows;
    int cols = src.cols;
    int channels = src.channels();
    const int step=2;
    int id_cols_new=0;
    int id_rows_new=0;
    int rows_new=rows/step;
    int cols_new=cols/step;
    int level=0;
    int rows_dummy = rows;
    int cols_dummy = cols;


    cv::Mat img_new(rows_new, cols_new, CV_8UC3);
    cv::Mat img_dummy(rows, cols, CV_8UC3);
    img_dummy=src;
   
    uchar* pixelPtr=(uchar*)img_dummy.data;
    uchar* pixelPtr_img_new=(uchar*)img_new.data;

    std::cout<< "Ingrese un nivel :";
    std::cin >> level;

    
    //FAST!!!!

        for (int id_cols=0; id_cols<cols_dummy; id_cols+=step){
            
            id_cols_new=(id_cols!=0)? (id_cols/step):0;
            for(int id_rows=0; id_rows<rows_dummy; id_rows+=step){

                id_rows_new=(id_rows!=0)? (id_rows/step):0;

                uchar blue= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 0];
                uchar green= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 1];
                uchar red= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 2];
                
                pixelPtr_img_new[id_rows_new*cols_new*channels + (id_cols_new*channels) + 0]=blue;
                pixelPtr_img_new[id_rows_new*cols_new*channels + (id_cols_new*channels) + 1]=green;
                pixelPtr_img_new[id_rows_new*cols_new*channels + (id_cols_new*channels) + 2]=red;

            }

        }
   
        rows_dummy = img_new.rows;
        cols_dummy = img_new.cols;
        rows_new=rows_dummy/step;
        cols_new=cols_dummy/step;
        img_dummy.release();

        //cv::Mat img_new2(rows_new, cols_new, CV_8UC3,0.0);
        img_dummy.create(rows_new, cols_new, CV_8UC3);
        pixelPtr_img_new=(uchar*)img_dummy.data;
        pixelPtr=(uchar*)img_new.data;

        for (int id_cols=0; id_cols<cols_dummy; id_cols+=4){
            id_cols_new=(id_cols!=0)? (id_cols/4):0;
            for(int id_rows=0; id_rows<rows_dummy; id_rows+=4){

                id_rows_new=(id_rows!=0)? (id_rows/4):0;

                uchar blue= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 0];
                uchar green= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 1];
                uchar red= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 2];
                
                pixelPtr_img_new[id_rows_new*cols_new*channels + (id_cols_new*channels) + 0]=blue;
                pixelPtr_img_new[id_rows_new*cols_new*channels + (id_cols_new*channels) + 1]=green;
                pixelPtr_img_new[id_rows_new*cols_new*channels + (id_cols_new*channels) + 2]=red;

            }

        }



    dst = img_dummy;

   }




/*    for (int id_level=0; id_level<level; id_level++){
        if(id_level==0){
            rows_dummy = rows;
            cols_dummy = cols;
            rows_new=rows_dummy/step;
            cols_new=cols_dummy/step;           
            //pixelPtr=(uchar*)img_dummy.data;
            //pixelPtr_img_new=(uchar*)img_new.data;
        }
        else{
            rows_dummy = img_new.rows;
            cols_dummy = img_new.cols;
            rows_new=rows_dummy/step;
            cols_new=cols_dummy/step;
            img_dummy.release();
            img_dummy.create(rows_dummy, cols_dummy, CV_8UC3);
            img_dummy=img_new;
            img_new.release();
            img_new.create(rows_new, cols_new, CV_8UC3);


 if (level==0){
        std::cout<< "Nivel invalido, favor de ingresar un nivel arriba de 0 \n/r";
        dst = src;
    }
        }*/