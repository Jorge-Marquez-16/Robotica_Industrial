#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/PointStamped.h>
#include <std_msgs/Int16.h>
#include <math.h>

void callback_point(const geometry_msgs::PointStamped &msg);
void callback(const std_msgs::Float32 &msg);
std_msgs::Int16 control;

const int POSITIVO=1;
const int NEGATIVO=-1;
const double t_muestreo=0.001;

//Variables control
double e_der; //derivada del error
double e_var; // error
double e_pass; // error pasado

double alpha_var=0.95;//0.95; //constante alpha super twisting
double c_var=5; //constante c
double beta_var=10; // constante beta

double reference=0;

double s_var; //superficie deslizante
double u_var; //señal de control

double w_der; //derivada de w
double w_var; 

int sign; //signo 


int main(int argc, char** argv){
    ros::init(argc,argv,"controler_node");

    ros::NodeHandle node_comms;
    ros::NodeHandle nodeHandle;

    ros::Subscriber subscriber_reference = nodeHandle.subscribe("reference_signal",1,callback_point);
    ros::Subscriber subscriber_encoder = nodeHandle.subscribe("encoder_signal",1,callback);


    ros::Publisher topic_pub= node_comms.advertise<std_msgs::Int16>("control_signal", 1);




    ros::Rate loopRate(250);

    int counter=0;

    while (ros::ok())
    {    
        topic_pub.publish(control);


        ros::spinOnce();
        loopRate.sleep();
    }
    

}


void callback_point(const geometry_msgs::PointStamped &msg_point){
    reference=msg_point.point.x;

}

void callback(const std_msgs::Float32 &encoder){
    //Control
    
    e_var=(reference-encoder.data);
    e_der=(e_var-e_pass)/t_muestreo;
    s_var=e_der+c_var*e_var;
    sign=(s_var >= 0) ? POSITIVO :NEGATIVO;
    w_der=beta_var*sign;
    w_var=w_var + t_muestreo*w_der;

    u_var=alpha_var*sqrt(fabs(s_var))*sign+w_var;


    
    
               


    if(u_var>255) u_var=255;  
    if(u_var<-255)u_var=-255;
    

    control.data=u_var;


}