#include <piramid.h>



piramid::piramid(){
    rows_ = 0;
    cols_ = 0;
    channels_ = 0;
    step_=2;
    level_=0;
    check_level_=true;
   
    //src_=src;
    
}
piramid::piramid(cv::Mat &src, int level){
    src_=src;
    rows_ = src_.rows;
    cols_ = src_.cols;
    channels_ = src_.channels();
    level_=level;
    step_=2;
    check_level_=true;
    dst_=src_;
}

piramid::~piramid()
{

}

//Getters

int piramid::getrows(void) const{
    return rows_;
}
int piramid::getcols(void) const{
    return cols_;
}
int piramid::getchannels(void) const{
    return channels_;
}
int piramid::getlevel(void) const{
    return level_;
}


//Setter

void piramid::setlevel(int level){
    level_=level;
}

//Muestra imagen nueva
void piramid::show_new(void){
    imwrite("NEW.jpg", dst_);   // (nombre de la imagen a guardar, imagen a guardar)
    namedWindow("NEW", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    imshow("NEW", dst_); // (identificador, imagen a mostrar)
    cv::waitKey(0);
}
//Muestra imagen original
void piramid::show_original(void){
    namedWindow("Original", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio
    imshow("Original", src_); // (identificador, imagen a mostrar)
     cv::waitKey(0);

}

void piramid::piramidal_small(void){
    
    piramid::check_level();

    if(check_level_){
        int id_cols_new=0;
        int id_rows_new=0;
        int rows_new=rows_/step_;
        int cols_new=cols_/step_;
        int rows_dummy = rows_;
        int cols_dummy = cols_;

        cv::Mat img_new(rows_new, cols_new, CV_8UC3);
        cv::Mat img_dummy(rows_, cols_, CV_8UC3);
        img_dummy=src_;

        uchar* pixelPtr=(uchar*)img_dummy.data;
        uchar* pixelPtr_img_new=(uchar*)img_new.data;
        
        //FAST!!!!
        for (int id_level_=0; id_level_<level_; id_level_++){
            if(id_level_>0){
                rows_dummy = img_new.rows;
                cols_dummy = img_new.cols;
                rows_new=(rows_dummy%2==0) ? rows_dummy/step_:(rows_dummy+1)/step_;
                cols_new=(cols_dummy%2==0) ? cols_dummy/step_:(cols_dummy+1)/step_;
                img_dummy.create(rows_dummy, cols_dummy, CV_8UC3);
                img_dummy=img_new;
                img_new.create(rows_new, cols_new, CV_8UC3);

                pixelPtr_img_new=(uchar*)img_new.data;
                pixelPtr=(uchar*)img_dummy.data;
            }
        
            for (int id_cols=0; id_cols<cols_dummy; id_cols+=step_){
                
                id_cols_new=(id_cols!=0)? (id_cols/step_):0;
                for(int id_rows=0; id_rows<rows_dummy; id_rows+=step_){

                    id_rows_new=(id_rows!=0)? (id_rows/step_):0;

                    uchar blue= pixelPtr[id_rows*cols_dummy*channels_ + id_cols*channels_ + BLUE];
                    uchar green= pixelPtr[id_rows*cols_dummy*channels_ + id_cols*channels_ + GREEN];
                    uchar red= pixelPtr[id_rows*cols_dummy*channels_ + id_cols*channels_ + RED];
                

                    pixelPtr_img_new[id_rows_new*cols_new*channels_ + (id_cols_new*channels_) + BLUE]=blue;
                    pixelPtr_img_new[id_rows_new*cols_new*channels_ + (id_cols_new*channels_) + GREEN]=green;
                    pixelPtr_img_new[id_rows_new*cols_new*channels_ + (id_cols_new*channels_) + RED]=red;
                }

            }
        }
        dst_=img_new;
    }
   }
        
void piramid::piramidal_big(void){
    
    piramid::check_level();
    if(check_level_){

   
    int step=2;
    int id_cols=0;
    int id_rows=0;
    int rows_new=rows_*step_;
    int cols_new=cols_*step_;
    int rows_dummy = rows_;
    int cols_dummy = cols_;


    cv::Mat img_new(rows_new, cols_new, CV_8UC3);
    cv::Mat img_dummy(rows_, cols_, CV_8UC3);
    img_dummy=src_;
   
    uchar* pixelPtr=(uchar*)img_dummy.data;
    uchar* pixelPtr_img_new=(uchar*)img_new.data;

   

    
    //FAST!!!!
    
       for (int id_level=0; id_level<level_; id_level++){
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

                uchar blue= pixelPtr[id_rows*cols_dummy*channels_ + id_cols*channels_ + 0];
                uchar green= pixelPtr[id_rows*cols_dummy*channels_ + id_cols*channels_ + 1];
                uchar red= pixelPtr[id_rows*cols_dummy*channels_ + id_cols*channels_ + 2];
                
                pixelPtr_img_new[(id_rows_new)*cols_new*channels_ + ((id_cols_new)*channels_) + 0]=blue;
                pixelPtr_img_new[(id_rows_new)*cols_new*channels_ + ((id_cols_new)*channels_) + 1]=green;
                pixelPtr_img_new[(id_rows_new)*cols_new*channels_ + ((id_cols_new)*channels_) + 2]=red;           
            }

        }
       }
    dst_ = img_new;
    }

}


void piramid::check_level(void){
    if (level_==0){
        std::cout<< "Nivel invalido, favor de ingresar un nivel arriba de 0 \n\r";
        check_level_=false;
    }
    else{check_level_=true;}
}