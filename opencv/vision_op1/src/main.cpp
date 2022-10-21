// ENcontrar documentacion docs.opencv.org
// En este archivo es donde se programarà la pràctica


#include <iostream>     // cout
#include <opencv2/opencv.hpp>   // cv:mat
        // argc #params, argv ?params

void imagen_piramidal(cv::Mat &src, cv::Mat &dst);
void imagen_big(cv::Mat &src, cv::Mat &dst);


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
    
    cv::Mat image_small;
    cv::Mat image_big;

    imagen_piramidal(image, image_small);


    imagen_big(image_small, image_big);

    imwrite("Original.jpg", image);   // (nombre de la imagen a guardar, imagen a guardar)
    imwrite("big.jpg", image_big);   // (nombre de la imagen a guardar, imagen a guardar)
    imwrite("small.jpg", image_small);   // (nombre de la imagen a guardar, imagen a guardar)
    namedWindow("Original", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    namedWindow("Image_small", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    namedWindow("Image_big", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio

    imshow("Original", image); // (identificador, imagen a mostrar)
    imshow("Image_small", image_small); // (identificador, imagen a mostrar)
    imshow("Image_big", image_big); // (identificador, imagen a mostrar)

   
    cv::waitKey(0);     // Se espera 1/t milisegundos; Si se ingresa un 0 espera hasta que el usuario cierre la ventana manualmente

    
    return 0;
}




// imagen rgb, imagen donde se guardara en gris

void imagen_piramidal(cv::Mat &src, cv::Mat &dst)
{
    int rows = src.rows;
    int cols = src.cols;
    int channels = src.channels();
    int step=2;
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
    for (int id_level=0; id_level<level; id_level++){
        if(id_level>0){
            rows_dummy = img_new.rows;
            cols_dummy = img_new.cols;
            rows_new=(rows_dummy%2==0) ? rows_dummy/step:(rows_dummy+1)/step;
            cols_new=(cols_dummy%2==0) ? cols_dummy/step:(cols_dummy+1)/step;
            img_dummy.create(rows_dummy, cols_dummy, CV_8UC3);
            img_dummy=img_new;
            img_new.create(rows_new, cols_new, CV_8UC3);

            pixelPtr_img_new=(uchar*)img_new.data;
            pixelPtr=(uchar*)img_dummy.data;
        }
       
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
    }
    dst = img_new;
    if (level==0){
        std::cout<< "Nivel invalido, favor de ingresar un nivel arriba de 0 \n\r";
        dst = src;
    }

   }




void imagen_big(cv::Mat &src, cv::Mat &dst)
{
    int rows = src.rows;
    int cols = src.cols;
    int channels = src.channels();
    int step=2;
    int id_cols=0;
    int id_rows=0;
    int rows_new=rows*step;
    int cols_new=cols*step;
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
    
       for (int id_level=0; id_level<level; id_level++){
        if(id_level>0){
            rows_dummy = img_new.rows;
            cols_dummy = img_new.cols;
            rows_new=rows_dummy*step;
            cols_new=cols_dummy*step;
            img_dummy.create(rows_dummy, cols_dummy, CV_8UC3);
            img_dummy=img_new;
            img_new.create(rows_new, cols_new, CV_8UC3);

            pixelPtr_img_new=(uchar*)img_new.data;
            pixelPtr=(uchar*)img_dummy.data;
        }

        for (int id_cols_new=0; id_cols_new<cols_new; id_cols_new++){
            
            id_cols=(id_cols_new!=0)? ((id_cols_new %2 ==0) ? id_cols+1:id_cols) :0;
            for(int id_rows_new=0; id_rows_new<rows_new; id_rows_new++){

                id_rows=(id_rows_new!=0)? ((id_rows_new %2 ==0) ? id_rows+1:id_rows) :0;

                uchar blue= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 0];
                uchar green= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 1];
                uchar red= pixelPtr[id_rows*cols_dummy*channels + id_cols*channels + 2];
                
                pixelPtr_img_new[(id_rows_new)*cols_new*channels + ((id_cols_new)*channels) + 0]=blue;
                pixelPtr_img_new[(id_rows_new)*cols_new*channels + ((id_cols_new)*channels) + 1]=green;
                pixelPtr_img_new[(id_rows_new)*cols_new*channels + ((id_cols_new)*channels) + 2]=red;           
            }

        }
       }
    dst = img_new;
    if (level==0){
        std::cout<< "Nivel invalido, favor de ingresar un nivel arriba de 0 \n\r";
        dst = src;
    }

}