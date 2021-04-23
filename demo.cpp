#include "NumberWithUnits.hpp"
#include "sstream"

using namespace ariel;


int main(){
     ifstream unitFile{"units.txt"};
    NumberWithUnits::read_units(unitFile);
    
    return 0;
}