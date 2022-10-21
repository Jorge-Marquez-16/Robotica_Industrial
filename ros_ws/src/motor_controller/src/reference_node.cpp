#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>

void menu(int &opc);


int main(int argc, char** argv)
{
    int opc = 0;
    int rate = 250;
    ros::init(argc, argv, "reference_node");
    ros::NodeHandle node_comms;

    ros::Publisher point_pub = node_comms.advertise<geometry_msgs::PointStamped>("reference_signal", 1);

    menu(opc);

    if (opc == 2 || opc == 3)
    {
        rate = 10;
    }
    
    ros::Rate loopRate(rate);

    double counter = 0;
    int aux_count = 0;
    int cycle = 0;
    int square_wave = 0;
    int triangular_wave = 0;  

    while(ros::ok() && opc < 5)
    {
        geometry_msgs::PointStamped msg_point;

        switch(opc){
        case 1: msg_point.point.x = 180 * std::sin(counter);
            msg_point.header.stamp=ros::Time::now();
            counter+=0.001;
            break;
        case 2: if (counter <= 180 && cycle == 1)
            {
                counter -= 18;
                aux_count += 18;
            }
            else if (counter <= 180)
            {
                counter +=18;
            }
            if (counter == 180)
            {
                cycle = 1;
            }
            if(aux_count == 360)
            {
                cycle = 0;
                aux_count = 0;
            }
            triangular_wave = counter;
            msg_point.point.x = triangular_wave; 
            msg_point.header.stamp=ros::Time::now();

            break;
        case 3: if (int(counter) % 40 == 0)
            {
                square_wave = 180;
            }
            if (counter == 80)
            {
                square_wave = -180;
                counter = 0;
            }
            msg_point.point.x = square_wave;
            msg_point.header.stamp=ros::Time::now();

            counter++;
            break;
        case 4: msg_point.point.x = 180 * std::cos(counter);
            msg_point.header.stamp=ros::Time::now();
            counter+=0.001;
            break;
        }
        
        point_pub.publish(msg_point);

        loopRate.sleep();
    }
    
    return 0;
}

void menu(int &opc)
{
    std::cout << "\t.:MENU DE REFERENCIAS:.\n";
    std::cout << "\n1. Referencia Senoidal.\n";
    std::cout << "2. Referencia Triangular.\n";
    std::cout << "3. Referencia Cuadratica.\n";
    std::cout << "4. Referencia Cosenoidal.\n";
    std::cout << "5. Salir.\n";
    std::cout << "Digite una opcion: ";
    std::cin >> opc;
}