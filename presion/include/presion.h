#ifndef PRESION_H_
#define PRESION_H_

class Presion
{    private:
        double deep_;
        double superficialp_;
        double densityf_;
        double gravity_;

    public:
        Presion();
        Presion(double deep, double superficialp, double densityf, double gravity);
        ~Presion();

        //Getters
        double getDeep(void) const;
        double getSuperficialp(void) const;
        double getDensityf(void) const;
        double getGravity(void) const;

        //Setters
        void setDeep(double deep);
        void setSuperficialp(double superficialp);
        void setDensityf(double densityf);
        void setGravity(double gravity);

        //Setter Todos los miembros
        void setVariables(double deep, double superficialp, double densityf, double gravity);

        //Imprime todos los miembros
        void print(void) const;

        //Calcula la presión absoluta
        double getAbsolutePressure(void) const;
        //Calcula la presión manométrica
        double getManometricPressure(void) const;
};

#endif