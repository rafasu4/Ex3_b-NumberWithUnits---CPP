#include "NumberWithUnits.hpp"
#include <sstream>

namespace ariel
{

    void NumberWithUnits::read_units(ifstream& fileName){
        string unit_r = "";
        string unit_l = "";
        string equalSign = " ";//will hold '=' in each line - no use for it
        string line;
        double value_r;// = 0;
        double value_l;// = 0;

        while(getline(fileName, line)){
            istringstream is(line);
            is >> value_l >> unit_l >> equalSign >> value_r >> unit_r;//inserting values by order
            //if end of file - exit
            if(!is){
                break;
            }
            //insert values to the map
            else{
                NumberWithUnits::convertionMap[unit_l] = {value_r, unit_r};
            }
            for(auto& t  : NumberWithUnits::convertionMap){
                cout << t.first << " " << t.second.first << " " << t.second.second << endl;
            }
            
        }

    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const
    {
        return NumberWithUnits(this->value + other.value, this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        this->value += other.value;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator+()
    {
        return *this;
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

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const
    {
        return NumberWithUnits(this->value - other.value, this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        this->value -= other.value;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-()
    {
        this->value *= -1;
        return *this;
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

    NumberWithUnits &NumberWithUnits::operator*(double num)
    {
        this->value *= num;
        return *this;
    }

    NumberWithUnits &operator*(double num, NumberWithUnits &n)
    {
        return n * num;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &other) const
    {
        bool ans = false;
        (this->value < other.value) ? ans = true : ans;
        return ans;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &other) const
    {
        bool ans = false;
        (this->value <= other.value) ? ans = true : ans;
        return ans;
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &other) const
    {
        bool ans = false;
        (this->value > other.value) ? ans = true : ans;
        return ans;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &other) const
    {
        bool ans = false;
        (this->value >= other.value) ? ans = true : ans;
        return ans;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &other) const
    {
        bool ans = false;
        (this->value == other.value) ? ans = true : ans;
        return ans;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const
    {
        bool ans = false;
        (this->value != other.value) ? ans = true : ans;
        return ans;
    }

    ostream &operator<<(ostream &os, const NumberWithUnits& n)
    {
        os << "value: " << n.value << " unit: " << n.unit;
        return os;
    }

    istream &operator>>(istream &is, NumberWithUnits& n)
    {
        is >> n.value;
        return is;
    }
}