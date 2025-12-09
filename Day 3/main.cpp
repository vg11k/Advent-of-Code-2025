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

string getCharAt(vector<string> s, int x, int y, int z) {
    return s.at(y).substr(x, z);
}

string getCharAt(vector<string> s, int x, int y) {
    return getCharAt(s,x,y,1);
}

void loopDoStuff(vector<string> input) {
    for (string sinput : input) {
        istringstream iss(sinput);
        string s;
        while (getline(iss, s, ' ')) {
            int val = stoi(s);

        }
    }
}

struct Jolt {
    long digit;
    int pos;
    int nbNulls;
};

long long dojob(vector<string> allLines, int joltsMax) {
    long long result = 0;
    for(int i = 0; i < allLines.size(); i++) {

        map<int, vector<int>*> digitToPositionsMap;
        for(int j = 1; j < 10; j++) {
            vector<int> * monvec = new vector<int>();
            digitToPositionsMap.emplace(j, monvec);
        }

        int linelength = allLines.at(i).length();
        vector<Jolt*> jolts;
        for(int j = 0; j < linelength; j++) {
            int digit = stoi(getCharAt(allLines,  j,  i));
            digitToPositionsMap.at(digit)->push_back(j);
            jolts.push_back(NULL);
        }

        int nbJoltSet = 0;
        vector<Jolt*> validJolts;
        for(int f = 9; f > 0 && nbJoltSet < joltsMax; f--) {
            vector<int> * fvector = digitToPositionsMap.at(f);
            for(int j = fvector->size() - 1; j > -1 && nbJoltSet < joltsMax; j--) {
                int pos = fvector->at(j);
                bool keep = true;
                for(Jolt * jolt : validJolts) {
                    if(jolt->digit > f && jolt->pos > pos) {
                        if(jolt->nbNulls + nbJoltSet >= joltsMax - 1) keep = false;
                    }
                }

                if(keep) {
                    Jolt * jolt = new Jolt();
                    jolt->pos = pos;
                    jolt->digit = f;
                    jolt->nbNulls = linelength - 1 - pos;
                    nbJoltSet++;
                    validJolts.push_back(jolt);
                    for(Jolt * joltb : validJolts) {
                        if(pos > joltb->pos) joltb->nbNulls--;
                        else jolt->nbNulls--;
                    }
                    jolts[pos] = jolt;
                }
            }
        }

        long long res = 0;
        for(Jolt * j : jolts) {
            if(j != NULL) {
                res *= 10;
                res += j->digit;
                if(verbose) cout << j->digit;
            }
            else if(verbose)cout << "n";
        }
        if(verbose) {
            cout << endl;
            cout << res << endl;
        }
        result += res;
    }
    return result;
}

int main(char* args[]) {

    cout << "Hello World !" << endl;

    bool debug = false;

    clock_t start, end;

    ifstream infile(filename.c_str());
    string line;
    long long result1 = 0;
    long long result2 = 0;
    vector<string> allLines;

    start = clock();

    while (getline(infile, line)) {
        allLines.push_back(line);
    }

    result1 = dojob(allLines, 2);
    result2 = dojob(allLines, 12);

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl; 
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}