#include <presion.h>
#include <math.h>
#include <iostream>


Presion::Presion()
{
    deep_=0.0;
    superficialp_=101325;
    densityf_=0.0;
    gravity_=9.81;
}

Presion::Presion(double deep, double superficialp, double densityf, double gravity)
{
    deep_=deep;
    superficialp_=superficialp;
    densityf_=densityf;
    gravity_=gravity;
}

Presion::~Presion()
{

}
//Getters
double Presion::getDeep(void) const
{
    return deep_;
}

double Presion::getSuperficialp(void) const
{
    return superficialp_;
}


double Presion::getDensityf(void) const
{
    return densityf_;
}

double Presion::getGravity(void) const
{
    return gravity_;
}

//Setters
void Presion::setDeep(double deep)
{
    deep_=deep;
}

void Presion::setSuperficialp(double superficialp)
{
    superficialp_=superficialp;
}

void Presion::setDensityf(double densityf)
{
    densityf_=densityf;
}

void Presion::setGravity(double gravity)
{
    gravity_=gravity_;
}

//Setter Todos los miembros
void Presion::setVariables(double deep, double superficialp, double densityf, double gravity)
{
    deep_=deep;
    superficialp_=superficialp;
    densityf_=densityf;
    gravity_=gravity;
}

//Imprime todos los miembros
void Presion::print(void) const
{
    std::cout<<"\n"<<"Profundidad: "<< deep_<< "m"<<"  Presión Superficial: "<<superficialp_<<"Pa";
    std::cout<<" Densidad del fluido: "<< densityf_<<"kg/m³"<<"  Gravedad: "<<gravity_ <<"m/s²"<<"\n";

}

//Calcula la presión absoluta
double Presion::getAbsolutePressure(void) const
{

    return (Presion::getManometricPressure()+ superficialp_);
}
//Calcula la presión manométrica
double Presion::getManometricPressure(void) const
{
    return (densityf_*gravity_*deep_);
}

