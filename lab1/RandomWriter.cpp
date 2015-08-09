/*
 * File: RandomWriter.cpp
 * ----------------------
 * The program will produce 2000 random characters based on markov model.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"
using namespace std;

const int REQUIRED_LEN = 2000; //required # of characters

class Transition  // records information about a seed, and can produce a character based on possibility
{
    private:
        map<char,int> stat;  //record about # of a character's occurence
        int total;           //# of the seed's occurence
    public:
        //constructor
        Transition():total(0){}
        //is the last one?
        bool isFinite()
        {
            return (total == 0);
        }
        //record a char after the seed
        void add(char c);
        //produce a char based on possibility
        char generate(); //should not be called on a finite state
        //getter of total
        int getTotal()
        {
            return total;
        }
};

void Transition::add(char c)
{
    ++stat[c];
    ++total;
}

char Transition::generate()
{
    int r = randomInteger(0, total - 1);
    int sum = 0;
    for(map<char, int>::iterator iter = stat.begin(); iter != stat.end(); ++iter){
        sum += iter->second;
        if (r < sum){  //random number falls in the interval
            return iter->first;
        }
    }
}

//Build a Markov model in model
void buildModel(istream & source, int order, map<string, Transition> & model)
{
    //read first ${order} chars
    int cnt = 0;
    string state = "";
    char c;
    while(source && (cnt < order)){
        source.get(c);
        state += c;
        ++cnt;
    }
    
    //insufficient chars
    if (cnt < order){
        throw runtime_error("input not big enough");
    }
    //work char by char
    while(source.get(c)){
        model[state].add(c);
        state += c;
        state = state.substr(1); //remove the first
    }
    //the last k char won't be recorded, because there is no more char
}

//output random chars to os
//using Markov model in model
void write(ostream & os, map<string, Transition> & model)
{
    //decide the initial seed
    string state;
    int max = 0;
    for(map<string, Transition>::iterator iter = model.begin(); iter != model.end(); ++iter){
        if(max < iter->second.getTotal()){
            max = iter->second.getTotal();
            state = iter->first;
        }
    }
    //output the initial seed
    os << state;
    //output the left char
    int cnt = state.size();
    while((cnt < REQUIRED_LEN) && model.count(state) && !model[state].isFinite()){
        char c = model[state].generate();
        os << c;
        ++cnt;
        //update seed
        state += c;
        state = state.substr(1); //remove the first
    }
}

//attempt to open a file, until success or fatal error happens
void open_file(ifstream & fin)
{
    while(true){
        string name = "";
        cout<<"Enter the source text: ";
        cin>>name;
        if (std::cin.eof()){
            throw std::runtime_error("Unexpected input end.");
        }
        if (std::cin.bad() || std::cin.fail()){
            throw std::runtime_error("input stream is not well.");
        }   
        fin.open(name.c_str());
        if (fin){
            break;
        }
        cout<<"Unable to open that file.  Try again."<<endl;
    }
}

//repeated input until get a int in range [l, h]
int read_int_checked(int l, int h)
{
    while(true){
        cout<<"Enter the Markov order ["<<l<<"-"<<h<<"]: ";
        try{
            string s;
            cin >> s;
            int ans = stringToInteger(s);//attempt to convert
            if ((ans >= l) && (ans <= h)){
                return ans;
            }
            cout<<"The value is out of range."<<endl;
        }catch(...){
            cout<<"Illegal integer format.  Try again"<<endl;//convert fails
        }
    }
}

int main() {
    map<string, Transition> model;
    ifstream fin;
    open_file(fin);
    int order = read_int_checked(0,10);
    buildModel(fin,order,model);
    write(cout,model);
    return 0;
}
