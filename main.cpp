#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
int main(int argc, char **argv) {
   map <string, function<double(vector<double>)> > lab1;

    lab1["add"] = [](vector<double> arg) {return arg.at(0) + arg.at(1);};
    lab1["sin"] = [](vector<double> arg) {return sin(arg.at(0));};
    lab1["mod"] = [](vector<double> arg) {int a = arg.at(0),b = arg.at(1);return a % b;};



    return 0;
}
