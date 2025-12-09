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

static const bool verbose = true;

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

struct RollPos {
    string s;
    int x;
    int y;
    RollPos(string a, int b, int c) : s(a), x(b), y(c) {}
};

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

    vector<RollPos*> allRollPos;
    vector<vector<RollPos*>*> rollGrid;
    vector<vector<string>*> resGrid;
    for (int i = 0; i < allLines.size(); i++) {
        vector<RollPos*>* v = new vector<RollPos*>();
        vector<string>* sres = new vector<string>();
        rollGrid.push_back(v);
        resGrid.push_back(sres);
        for (int j = 0; j < allLines.at(i).length(); j++) {
            RollPos* r = new RollPos(getCharAt(allLines, i, j), i, j);
            v->push_back(r);
            allRollPos.push_back(r);
            sres->push_back(r->s);
        }
    }

    string ar = "@";
    int nbLines = allLines.size();
    int nbCol = allLines.at(0).length();

    if (verbose) {
        for (int i = 0; i < rollGrid.at(0)->size(); i++) {
            for (int j = 0; j < rollGrid.size(); j++) {
                cout << rollGrid.at(j)->at(i)->s;
            }
            cout << endl;
        }

        cout << endl;
        cout << endl;
    }

    long long iteration = 0;
    bool loop = true;
    while (loop) {

        loop = false;
        int nbRollRemoved = 0;

        for (RollPos* r : allRollPos) {
            if (r->s == "@") {
                int cptRollNei = 0;
                if (r->x > 0) {
                    if (rollGrid.at(r->x - 1)->at(r->y)->s == ar) cptRollNei++;
                    if (r->y > 0) {
                        if (rollGrid.at(r->x - 1)->at(r->y - 1)->s == ar) cptRollNei++;
                    }
                    if (r->y < nbLines - 1) {
                        if (rollGrid.at(r->x - 1)->at(r->y + 1)->s == ar) cptRollNei++;
                    }
                }
                if (r->y > 0) {
                    if (rollGrid.at(r->x)->at(r->y - 1)->s == ar) cptRollNei++;
                }
                if (r->y < nbLines - 1) {
                    if (rollGrid.at(r->x)->at(r->y + 1)->s == ar) cptRollNei++;
                }
                if (r->x < nbCol - 1) {
                    if (rollGrid.at(r->x + 1)->at(r->y)->s == ar) cptRollNei++;
                    if (r->y > 0) {
                        if (rollGrid.at(r->x + 1)->at(r->y - 1)->s == ar) cptRollNei++;
                    }
                    if (r->y < nbLines - 1) {
                        if (rollGrid.at(r->x + 1)->at(r->y + 1)->s == ar) cptRollNei++;
                    }
                }
                if (cptRollNei < 4) {
                    nbRollRemoved++;
                    resGrid.at(r->x)->at(r->y) = "X";
                }
            }
        }
        if (iteration == 0) result1 = nbRollRemoved;

        result2 += nbRollRemoved;
        iteration++;

        loop = nbRollRemoved > 0;

        for (int i = 0; i < rollGrid.at(0)->size(); i++) {
            for (int j = 0; j < rollGrid.size(); j++) {
                if (resGrid.at(j)->at(i) == "X") {
                    resGrid.at(j)->at(i) = ".";
                    rollGrid.at(j)->at(i)->s = ".";
                }
            }
        }

        if (verbose) cout << "iteration " << iteration << endl;

    }

    if (verbose) {
        for (int i = 0; i < rollGrid.at(0)->size(); i++) {
            for (int j = 0; j < rollGrid.size(); j++) {
                cout << resGrid.at(j)->at(i);
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl;

    cout << "Bye World !" << endl;

    return 0;
}