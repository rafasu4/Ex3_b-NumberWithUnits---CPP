#include <iostream>
#include <fstream>
#include <map>
using namespace std;

namespace ariel
{
    class NumberWithUnits
    {
        double value;
        string unit;
        public:
            static map<string, pair<double,string>> convertionMap;

    public:
        //constructor
        NumberWithUnits(double value, string measure){
            this->value = value;    
            this->unit = measure;
        }
        //copy constructor
        NumberWithUnits(const NumberWithUnits& other){
            this->value = other.value;
            this->unit = other.unit;
        }
        double getValue(){
            return this->value;
        }

        string getUnit(){
            return this->unit;
        }
        //API
        static void read_units(ifstream& fileName);

        /***************************Mathematical operators***************************/
        NumberWithUnits operator+(const NumberWithUnits &other) const;
        NumberWithUnits &operator+=(const NumberWithUnits &other);
        NumberWithUnits& operator+();
        NumberWithUnits &operator++();
        NumberWithUnits operator++(int num);

        NumberWithUnits operator-(const NumberWithUnits &other) const;
        NumberWithUnits &operator-=(const NumberWithUnits &other);
        NumberWithUnits& operator-();
        NumberWithUnits &operator--();
        NumberWithUnits operator--(int num);
        NumberWithUnits &operator*(double num);
        friend NumberWithUnits& operator*(double num, NumberWithUnits& n);

        /***************************Comparison operators***************************/
        bool operator<(const NumberWithUnits &other) const;
        bool operator<=(const NumberWithUnits &other) const;
        bool operator>(const NumberWithUnits &other) const;
        bool operator>=(const NumberWithUnits &other) const;
        bool operator==(const NumberWithUnits &other) const;
        bool operator!=(const NumberWithUnits &other) const;

        /***************************Stream operators***************************/
        friend ostream &operator<<(ostream &os, const NumberWithUnits& n);
        friend istream &operator>>(istream &is, NumberWithUnits& n);
    };
    map<string, pair<double,string>> NumberWithUnits::convertionMap = map<string, pair<double,string>>();    
}
