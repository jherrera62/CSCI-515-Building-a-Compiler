#include<iostream>
#include<vector>
#include "Date.h"
using namespace std;

int main()
{
  //Just a test here to show usage:
  Date dt(1,1,1);
  cout << dt << '\n' << "-----\n";

  vector<Date*> dates;
  dates.push_back(new Date(1,16,1720));
  dates.push_back(new Date(2,17,1820));
  dates.push_back(new Date(3,18,1920));
  dates.push_back(new Date(4,19,2020));

  //(1)
  //Write a line of code before the hash-line that prints out the last Date in the vector (4/19/2020)
  cout<<*dates.back()<<endl;
  
  cout << "---------\n";

  //(2)
  //Write a loop to iterate through the vector *backwards*
  //printing out each date. Do not hardcode
  //the number of items in the vector, 4, anywhere.
  for(int i=0; i<dates.size();i++)
  {
  }

  //(3)
  //Write a normal, forward loop to release each of the four items using delete

  return 0;
}
