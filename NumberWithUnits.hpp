#include <iostream>
#include <fstream>
#include <map>
using namespace std;

namespace ariel
{
    /*This class represents a collection of units, gathers from a given file, and represents them
    as objects of NumberWithUnits class. Each object consist from a value, the amount, and unit, the type.
    This class has a set of logic operators, so one can operate on two objects with different types but from the same dimension.*/


    class NumberWithUnits
    {
        static map<string, map<string, double>> convertionMap;//holds all the units and the possible convertions from them
        double value;
        string unit;

    public:
        //constructor
        NumberWithUnits(double value, string unit) noexcept(false)
        {
            bool exist = false;
            //checks if the given unit exist within the keys of the map
            if (NumberWithUnits::convertionMap.count(unit))
            {
                exist = true;
            }
            //if the given unit doesn't exist within the units chart - throw an exception
            if (exist == false)
            {
                throw invalid_argument(unit + " is Not a valid unit!");
            }

            else
            {
                this->value = value;
                this->unit = unit;
            }
        }
        //copy constructor
        NumberWithUnits(const NumberWithUnits &other)
        {
            this->value = other.value;
            this->unit = other.unit;
        }

        double getValue()
        {
            return this->value;
        }

        string getUnit()
        {
            return this->unit;
        }
        //API
        static void read_units(ifstream &fileName);

        /***************************Mathematical operators***************************/
        NumberWithUnits operator+=(const NumberWithUnits &other);
        NumberWithUnits &operator++();
        NumberWithUnits operator++(int num);
        NumberWithUnits operator-=(const NumberWithUnits &other);
        NumberWithUnits &operator--();
        NumberWithUnits operator--(int num);
        friend NumberWithUnits operator+(const NumberWithUnits &n);
        friend NumberWithUnits operator-(const NumberWithUnits &n);
        friend NumberWithUnits operator*(const NumberWithUnits &n ,double num);
        friend NumberWithUnits operator*(double num, const NumberWithUnits &n);
        friend NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2);

        /***************************Comparison operators***************************/
        friend bool operator>(const NumberWithUnits &n1,const NumberWithUnits &n2);
        friend bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        /***************************Stream operators***************************/
        friend ostream &operator<<(ostream &os, const NumberWithUnits &n);
        friend istream &operator>>(istream &is, NumberWithUnits &n);

    private:
        static void convert(NumberWithUnits &, string unit);
        void setValue(double v)
        {
            this->value = v;
        }

        void setUnit(string u)
        {
            this->unit = u;
        }
    };

}
