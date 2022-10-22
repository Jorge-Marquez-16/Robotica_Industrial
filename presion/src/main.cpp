#include <presion.h>
#include <iostream>

int main()
{
    Presion Tanque_vacio;
    Presion Tanque_lleno(12, 101325,997,9.81);

    Tanque_vacio.print();
    Tanque_lleno.print();

    //Presiones tanque vacio
    std::cout<< "\n"<<"Presion Absoluta Tanque vacio: ";
    std::cout<<Tanque_vacio.getAbsolutePressure()<<"Pa"<<"\n";

    std::cout <<"\n"<<"Presion Manometrica Tanque vacio: ";
    std::cout<<Tanque_vacio.getManometricPressure()<<"Pa"<<"\n";

    //Presiones tanque del problema
    std::cout<<"\n"<<"Presion Absoluta Tanque lleno: ";
    std::cout<<Tanque_lleno.getAbsolutePressure()<<"Pa"<<"\n";

    std::cout <<"\n"<<"Presion Manometrica Tanque lleno: ";
    std::cout<<Tanque_lleno.getManometricPressure()<<"Pa"<<"\n";

    return 0;
}