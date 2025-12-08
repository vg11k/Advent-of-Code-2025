#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

static const string filename = "input.txt";
//static const string filename = "example.txt";

static const bool verbose = false;
static const bool verbosep2 = false;

struct Element {
    string a;
    string b;
};

int main(char* args[]) {

    cout << "Hello World !" << endl;

    bool debug = false;

    clock_t start, end;

    ifstream infile(filename.c_str());
    string line;
    long long result1 = 0;
    long long result2 = 0;
    string singleLine;
    vector<Element> allIds;

    start = clock();

    char commaSeparator = ',';
    char dashSeparator = '-';

    while (getline(infile, line)) {
        singleLine = line;
    }

    istringstream iss(singleLine);
    string s;

    while (getline(iss, s, commaSeparator)) {
        Element id;
        id.a = s.substr(0, s.find(dashSeparator));
        id.b = s.substr(s.find(dashSeparator) + 1);
        allIds.push_back(id);
        if(verbose) cout << id.a << " " << id.b << endl;
    }
    

    for(Element e : allIds) {
        long long ia = stoll(e.a);
        long long ib = stoll(e.b);
        for(long long i = ia; i < ib + 1; i++) {
            string is = to_string(i);
            if(is.length() % 2 == 0) {
                string isa = is.substr(0,is.length() / 2);
                string isb = is.substr(is.length() / 2);
                if(isa == isb) {
                    result1 += i;
                    if(verbose) cout << is << " ";
                }
            }
        }
        if(verbose) cout << endl;
    }

    //that's a bit messy but i hate regex so lets brut force dat thing
    for(Element e : allIds) {
        long long lla = stoll(e.a);
        long long llb = stoll(e.b);
        if(verbosep2) cout << lla << " " << llb << " : ";
        for(long long ll = lla; ll < llb + 1; ll++) {
            string lls = to_string(ll);
            int isHalfLength = lls.length() / 2; //lil opt
            bool keepSolution = false;

            for(int j = 1; j <= isHalfLength && !keepSolution; j++) {
                string llc = lls.substr(0,j);
                if(lls.length() % llc.length() == 0) {//lil opt
                    bool getout = false;
                    for(int k = j; k < lls.length() && !getout; k+= j) {
                        string lld = lls.substr(k, j);
                         if(llc != lld) {
                            getout = true;//not necessary to try further
                        }
                    }
                    //did we try everything and no combination was wrong ? so its right
                    if(!getout) keepSolution = true;
                }
            }

            if(keepSolution) {
                result2 += ll;
                if(verbosep2) cout << lls << " ";
            }
        }
        if(verbosep2) cout << endl << endl;
    }

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl; 
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}