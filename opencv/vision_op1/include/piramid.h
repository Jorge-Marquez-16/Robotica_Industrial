#ifndef PIRAMID_H_
#define PIRAMID_H_

#include <iostream>     // cout
#include <opencv2/opencv.hpp>   // cv:mat

#define BLUE 0
#define GREEN 1
#define RED 2

class piramid
{
    private:
        int rows_;
        int cols_;
        int channels_;
        int step_;
        
        int level_;
        
        bool check_level_;
        cv::Mat src_;
        cv::Mat dst_;        
        

    public:
        piramid();
        //piramid(cv::Mat &src);
        piramid(cv::Mat &src, int level);
        ~piramid();


        //Getters

        int getrows(void) const;
        int getcols(void) const;
        int getchannels(void) const;
        int getlevel(void) const;

        //Setters

        void setlevel(int level);


        //Muestra imagen nueva
        void show_new(void);
        //Muestra imagen original
        void show_original(void);

        //Reduce imagen
        void piramidal_small(void);
        
        void piramidal_big(void);

        void check_level(void);
};










#endif