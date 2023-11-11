#include <stdio.h>
#include <map>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

string progName;
vector<pair<int, string>> objcode;
map<string, string> REG;
map<string, pair<int, string>> OPTAB;
map<string, int> SYMTAB;
int LOCCTR = 0, pc = 0, base = 0, index = 0;

int main(int argc, char *argv[]) {
    // Get cmd line args
    fstream inputFile;
    string line, filePath;
    string argv1 = argv[1];

    if (argc == 2) { // Command line arguments
       	filePath = argv[1];
    } else {
       	cout << "Invalid syntax.\n";
       	return 1;
    }

    inputFile.open(filePath.c_str());
    
}

