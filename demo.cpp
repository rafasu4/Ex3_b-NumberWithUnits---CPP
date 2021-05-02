
#include "NumberWithUnits.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <exception>
using namespace std;
using namespace ariel;

NumberWithUnits operatorN(NumberWithUnits &n1, NumberWithUnits &n2, int op)
{
  if(op == 1){return n1 + n2;}
  if(op == 2){return n1 += n2;}
  if(op == 3){return n1 - n2;}
  if(op == 4){return n1 -= n2;}
  return NumberWithUnits();
}


bool operatorM(NumberWithUnits &n1, NumberWithUnits &n2,  int op)
{
  if(op == 5){return n1 < n2;}
  if(op == 6){return n1 > n2;}
  if(op == 7){return n1 <= n2;}
  if(op == 8){return n1 >= n2;}
  if(op == 9){return n1 == n2;}
  if(op == 10){return n1 != n2;}
  return false;

}

void checkValid(NumberWithUnits &n, double v, int index, string units[], bool flag)
{
  try
  {
     NumberWithUnits temp(v, units[index - 1]);
     n = temp;
  }
  catch (exception e)
  {
    cout << "try again!";
    flag = false;
  }
}

int main()
{
  ofstream myfile;
  myfile.open("myTestFile.txt");
  myfile << "1 km = 1000 m" << endl;
  myfile << "1 m = 100 cm" << endl;
  myfile << "1 kg = 1000 g" << endl;
  myfile << "1 ton = 1000 kg" << endl;
  myfile << "1 hour = 60 min" << endl;
  myfile << "1 min = 60 sec" << endl;
  myfile << "1 day = 24 hour" << endl;
  myfile << "1 month = 30 day" << endl;
  myfile << "1 year = 12 month" << endl;
  myfile.close();
  ifstream units_file{"myTestFile.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1;
  NumberWithUnits n2;

  string units[12] = {"km", "m", "cm", "kg", "g", "ton", "hour", "min", "sec", "day", "month", "year"};
  string operators[10] = {"+", "+=", "-", "-=", "<", ">", "<=", ">=", "==", "!="};
  int option = 0;
  bool flag = false;
  double value = 0;
  

  cout << "Hello! this program will compare between two units"<<endl;

  while (!flag)
  {
    //getting the first value
    while (!flag)
    {
      cout << "Choose the unit from the following(note: comparation must be between units in the same dimension): " << endl;
      cout << "1 - km\n2 - m\n3 - cm\n4 - kg\n5 - g\n6 - ton\n7 - hour\n";
      cout << "8 - min\n9 - sec\n10 - day\n11 - month\n12 - year\n";
      cin >> option;
      cout << "Enter a value of the first unit: " << endl;
      cin >> value;
      //if the given option isn't within the parameters
      if (option < 1 || option > 12)
      {
        cout << "Invalid input!" << endl;
      }
      else
      {
        flag = true;
        checkValid( n1, value, option, units, flag);
        cout << n1 << endl;
      }
    }

      flag = false;
      //getting the sec value
      while (!flag)
      {
        cout << "Choose the unit from the following(note: comparation must be between units in the same dimension): " << endl;
        cout << "1 - km\n2 - m\n3 - cm\n4 - kg\n5 - g\n6 - ton\n7 - hour\n8 - min\n9 - sec\n10 - day\n11 - month\n12 - year\n";
        cin >> option;
        cout << "Enter the value of the second unit: " << endl;
        cin >> value;
        //if the given option isn't within the parameters
        if (option < 1 || option > 12)
        {
          cout << "Invalid input!" << endl;
        }
        else
        {
          flag = true;
          checkValid(n2, value, option, units, flag);
          cout << n2 << endl;
        }
      }
    
      flag = false;
      while (!flag)
      {
        cout << "Choose the operator from the following: " << endl;
        cout << "1 - +\n2 - +=\n3 - -\n4 - -=\n5 - <g>\n6 - >\n7 - <=\n8 - >=\n9 - ==\n10 - !=\n";
        cin >> option;
        if (option < 1 || option > 10)
        {
          cout << "Invalid input!" << endl;
        }
        else{
          flag = true;
          if(option < 5){
            NumberWithUnits n = operatorN(n1, n2, option);
            cout << n1 << " " + operators[option - 1] << n2 <<" will give: " << n << endl;
          }
          else{
            bool ans = operatorM(n1, n2, option);
            cout << n1 << " " + operators[option - 1] << n2 <<" is: " << boolalpha<< ans << endl;
          }
        }
      }
    cout<<"For another run enter 0. For exit enter any number: ";
    cin >> flag;
    if(flag){
      cout<<"bye-bye!"<<endl;
    }
    
  }
  return 0;
}