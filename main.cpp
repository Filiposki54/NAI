#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <math.h>

int main(int argc, char** argv) {
    using namespace std;

    map <string, function<string(vector<string>)> > lab1;


    lab1["add"] = [](vector<string>arg){
        return to_string(stof(arg.at(2))+ stof(arg.at(3)));
    };
    lab1["mod"] = [](vector<string>arg){
        return to_string(stoi(arg.at(2))% stoi(arg.at(3)));
    };
    lab1["sin"] = [](vector<string>arg){
        return to_string(sin(stod(arg.at(2))));
    };
    lab1[""] = [](vector<string>arg){
        return "Podaj parametry \n"
               "[add][a][b]\n"
               "[mod][a][b]\n"
               "[sin][a]";
    };
    try{
        vector<string> argumenty(argv, argv + argc);
        function f = lab1.at(argumenty.at(1));
        cout<<f(argumenty);
    }catch (exception &e){
        cout<<"Nie podano argumentów";
    }
    return 0;
}
