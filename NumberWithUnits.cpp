#include "NumberWithUnits.hpp"
#include <sstream>

constexpr double EPS = 0.00001;

namespace ariel
{
    map<string, map<string, double>> NumberWithUnits::convertionMap = map<string, map<string, double>>();

    void NumberWithUnits::read_units(ifstream &fileName)
    {
        if (fileName.fail())
        {
            throw "Error at opening the file!";
        }

        string unitR = "";         //unit_r
        string unitL = "";        //unit_l
        string equalSign = ""; //will hold '=' in each line - no use for it
        string line;
        double value_r; // = 0;
        double value_l; // = 0;

        while (getline(fileName, line))
        {
            istringstream is(line);
            is >> value_l >> unitL >> equalSign >> value_r >> unitR; //inserting values by order
            //if end of file - exit
            if (!is)
            {
                break;
            }
            //insert values to the map
            else
            {
                NumberWithUnits::convertionMap[unitL][unitR] = value_r;
                NumberWithUnits::convertionMap[unitR][unitL] = 1 / value_r;
            }
        }
        //updating all the transitive relations to the map in three for-each loop
        //first loop - go over all the units(keys) in the map
        for (const auto &pair : convertionMap)
        {
            string currentUnit = pair.first;
            map<string, double> equivalentUnits = pair.second;
            //second loop - go over all the units that has relations with the current unit
            for (const auto &unit : equivalentUnits)
            {
                //in all the units that has relations with current unit - check if there is a transitive to be added
                for (const auto &innerUnits : convertionMap[unit.first])
                {
                    //if the inner unit doesn't have relation with the currnt unit - update the map
                    if (!equivalentUnits.count(innerUnits.first))
                    {
                        double equals = innerUnits.second;
                        convertionMap[currentUnit][innerUnits.first] = equals * equivalentUnits[unit.first];
                    }
                }
            }
        }
    }

    void NumberWithUnits::convert(NumberWithUnits &n, string unit)
    {
        //if there isn't a convertion between the two units - throw exception
        if (!convertionMap[n.getUnit()].count(unit))
        {
            __throw_bad_cast();
        }
        double value = convertionMap[n.getUnit()][unit] * n.getValue();//the new value according to the map relations
        n.setUnit(unit);
        n.setValue(value);
    }

    NumberWithUnits operator+(const NumberWithUnits &n1,  const NumberWithUnits &n2)
    {
        NumberWithUnits n(n2.value, n2.unit);
        if (n1.unit != n2.unit)
        {
            NumberWithUnits::convert(n, n1.unit);
        }
        n.setValue(n.value + n1.value);
        return n;
    }

    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2){
        NumberWithUnits n(n2.value, n2.unit);
        if (n1.unit != n2.unit)
        {
            NumberWithUnits::convert(n, n1.unit);
        }
        n.setValue(n1.value - n.value);
        return n;
    }

    NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        NumberWithUnits n(other);
        if (this->unit != other.unit)
        {
            NumberWithUnits::convert(n, this->unit);
        }
        this->value += n.value;
        return *this;
    }

    NumberWithUnits operator+(const NumberWithUnits &n)
    {
        return NumberWithUnits(n);
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->value++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int num)
    {
        NumberWithUnits temp(*this);
        this->value++;
        return temp;
    }

    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        NumberWithUnits n(other);
        if (this->unit != other.unit)
        {
            NumberWithUnits::convert(n, this->unit);
        }
        this->value -= n.value;
        return *this;
    }

    NumberWithUnits operator-(const NumberWithUnits &n)
    {
        return NumberWithUnits(-n.value, n.unit);
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->value--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int num)
    {
        NumberWithUnits temp(*this);
        this->value--;
        return temp;
    }

    NumberWithUnits operator*(const NumberWithUnits &n, double num)
    {
     return NumberWithUnits(n.value*num, n.unit);
    }

    NumberWithUnits operator*(double num, const NumberWithUnits &n)
    {
        return n * num;
    }

    bool operator>(const NumberWithUnits &n1,const NumberWithUnits &n2){
        return  n2 < n1;
    }

    bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        NumberWithUnits n(n2);
        if (n1.unit != n2.unit)
        {
            NumberWithUnits::convert(n, n1.unit);
        }
        bool ans = false;
        (n1.value < n.value) ? ans = true : ans;
        return ans;
    }

    bool operator<=(const NumberWithUnits &n1,const NumberWithUnits &n2)
    {
        return !(n1 > n2);
    }

    bool operator>=(const NumberWithUnits &n1,const NumberWithUnits &n2)
    {
        return !(n1 < n2);
    }

    bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        NumberWithUnits n(n2.value, n2.unit);
        if (n1.unit != n2.unit)
        {
            NumberWithUnits::convert(n, n1.unit);
        }
        bool ans = false;
        (abs(n1.value - n.value) < EPS) ? ans = true : ans;
        return ans;
    }

    bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        return !(n1 == n2);
    }

    ostream &operator<<(ostream &os, const NumberWithUnits &n)
    {
        os << n.value << "[" << n.unit <<"]";
        return os;
    }

    istream &operator>>(istream &is, NumberWithUnits &n)
    {
        char c = 0; //hold '[]'
        string u; // holds the unit
        double v = 0; // holds the value
        is >> v >> c >> u >> c;
        if (u[u.length() - 1] == ']')
        {
            u.pop_back();
        }
        if (c == '-')
        {
            is.putback('-');
        }
        //if the input unit doesn't exist in units file
        if(!NumberWithUnits::convertionMap.count(u)){
            throw invalid_argument(u + " is Not a valid unit!");
        }
        n.setUnit(u);
        n.setValue(v);
        return is;
    }
}