#ifndef STL_H
#define STL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
using namespace std;
#define SPACES " \t\r\n"
string trim_right (const string & s, const string & t = SPACES);
string trim_left (const string & s, const string & t = SPACES);
string trim (const string & s, const string & t = SPACES);
string tolower (const string & s);
string toupper (const string & s);
void StringToVector (const string s,
                     vector<string> & v,
                     const string delim = " ",
                     const bool trim_spaces = true);
string VectorToString (const vector<string> & v,
                       const string delim = " ");
float StrToFloat (string);
std::string FloatToStr(double);




#endif // STL_H
// disable warnings about long names




