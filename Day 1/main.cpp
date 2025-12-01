#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
using namespace std;


static const bool verbose = true;
static const string filename = "input1.txt";
//static const string filename = "example1.txt";

static const int startingPosition = 50;

struct CircularResult {
    int rotationCount;
    int position;
};

CircularResult getCircularValue(int value) {
    CircularResult result;
    result.position = value;
    result.rotationCount = 0;
    while(result.position > 99 || result.position < 0) {
        if(result.position > 99) {
            result.position -=100;
        }
        else if(result.position < 0){
            result.position +=100;
        }
        result.rotationCount++; //each complete rotation we click !
    }
    return result;
}


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

    int rotationPosition = startingPosition;
    result1 = 0;

    for(int lineIndex = 0; lineIndex < allLines.size(); lineIndex++) {
        string output = "";
        string rotate = getCharAt(allLines, 0, lineIndex);
        int rotation = stoi(getCharAt(allLines, 1, lineIndex, allLines.at(lineIndex).length() - 1));
        if(rotate == "L") {
            output += std::to_string(rotationPosition) + " - " + std::to_string(rotation) + " ";
        }
        else {
            output += std::to_string(rotationPosition) + " + " + std::to_string(rotation) + " ";
        }


        int positiveRotation = rotation;
        if(rotate == "L") rotation *= -1;

        int originalPos = rotationPosition;
        rotationPosition += rotation;
        int prevPosition = rotationPosition;
        CircularResult circular = getCircularValue(rotationPosition);
        rotationPosition = circular.position;
        if(rotationPosition == 0) result1++;

        if(circular.rotationCount > 0) {
            int click = circular.rotationCount;
            //starting on 0 while rotate L cause a click auto, already counted prev instruction
            if(rotate == "L" && originalPos == 0) click--; 
            //rotating L and ending on a 0 without a last click (revert of last else)
            if(rotate == "L" && rotationPosition == 0) click++;
            result2+=click;
            output += " click += " + std::to_string(click) + " ";
        }
        else if(rotationPosition == 0) {
            output += " click0 += 1 ";
            result2++; //no rotation but ending on a 0 (suppose it was L)
        }

        output += "current position : " + std::to_string(rotationPosition);
        if(verbose) cout << output << endl;
    }

    end = clock();

    cout << "result1 : " << result1 << endl;
    cout << "result2 : " << result2 << endl;
    cout << end - start << " ms to compute." << endl; 

    cout << "Bye World !" << endl;

    return 0;
}