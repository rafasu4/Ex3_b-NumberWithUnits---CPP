#include "NumberWithUnits.hpp"
#include "sstream"

using namespace ariel;

 
int main(){
     ifstream unitFile{"units.txt"};
      NumberWithUnits::read_units(unitFile);
      NumberWithUnits n1 (1,"day");
      NumberWithUnits n2 (60*24,"min");
      bool a =  n1 != n2;
      cout <<a;
  
    return 0;
}