#include <stdio.h>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string progName;
vector<pair<int, string>> objcode;
vector<string> code;
map<string, string> REG;
unordered_map<string, string> mnemonics;
map<string, string> SYMTAB;
map<int, string> intermediate;
int LOCCTR = 0, progLength, start = 0, pc = 0, base = 0, index = 0;

void create_mnemonics(){
    mnemonics[(string)"ADD"] = (string)"18";
    mnemonics[(string)"ADDR"] = (string)"58";
    mnemonics[(string)"CLEAR"] = (string)"B4";
    mnemonics[(string)"COMP"] = (string)"28";
    mnemonics[(string)"COMPR"] = (string)"A0";
    mnemonics[(string)"J"] = (string)"3C";
    mnemonics[(string)"JEQ"] = (string)"30";
    mnemonics[(string)"JLT"] = (string)"38";
    mnemonics[(string)"JSUB"] = (string)"48";
    mnemonics[(string)"LDA"] = (string)"00";
    mnemonics[(string)"LDB"] = (string)"68";
    mnemonics[(string)"LDCH"] = (string)"50";
    mnemonics[(string)"LDT"] = (string)"74";
    mnemonics[(string)"RD"] = (string)"D8";
    mnemonics[(string)"RSUB"] = (string)"4C";
    mnemonics[(string)"STA"] = (string)"0C";
    mnemonics[(string)"STCH"] = (string)"54";
    mnemonics[(string)"STL"] = (string)"14";
    mnemonics[(string)"STX"] = (string)"10";
    mnemonics[(string)"TD"] = (string)"E0";
    mnemonics[(string)"TIXR"] = (string)"B8";
    mnemonics[(string)"WD"] = (string)"DC";
    mnemonics[(string)"A"] = (string)"0";
    mnemonics[(string)"X"] = (string)"1";
    mnemonics[(string)"S"] = (string)"2";
    mnemonics[(string)"T"] = (string)"5";
}

/* Generating OPCODE symbol */
void generate_opcode() {

}

string get_label(string line) {
    string label = "";
    for(int i = 0; i < line.size(); i++) {
        if(line[i] == ' ' || line[i] == '\t') {
            break;
        }
        label += line[i];
    }
    return label;
}

string get_operator(string line) {
    string opr = "";
    for(int i = 11; i < line.size(); i++) {
        if(line[i] == ' ' || line[i] == '\t') {
            break;
        }
        opr += line[i];
    }
    return opr;

}

string get_operand(string line) {
    string operand = "";
    for(int i = 20; i < line.size(); i++) {
        if(line[i] == ' ' || line[i] == '\t') {
            break;
        }
        operand += line[i];
    }
    return operand;

}

string int_to_hex(int a) {
    // convert integer to hex string
    string hex = "";
    while(a > 0) {
        int rem = a % 16;
        if(rem < 10) {
            hex += (char)(rem + '0');
        }
        else {
            hex += (char)(rem - 10 + 'A');
        }
        a /= 16;
    }
}

int hex_to_int(string hex) {
    // convert hex string to integer
    int a = 0;
    for(int i = 0; i < hex.size(); i++) {
        if(hex[i] >= '0' && hex[i] <= '9') {
            a = a * 16 + (hex[i] - '0');
        }
        else {
            a = a * 16 + (hex[i] - 'A' + 10);
        }
    }
    return a;
}

/* Generating Symbol Table */
void generate_symtab() {
    for(int i = 0; i < code.size(); i++){
        string label = get_label(code[i]);
        string opr = get_operator(code[i]);
        string operand = get_operand(code[i]);

        if (label != "" && opr == "EQU") {
            if (operand == "*")
                SYMTAB.insert(make_pair(label, intermediate[i]));
            else {
                string a = "", b = "";
                int flag = 0;
                for (int i = 0; i < operand.size(); ++i) {
                    if (operand[i] == '-') {
                        flag = 1; continue;
                    }
                    if (flag == 0) a += operand[i];
                    else b += operand[i];
                }
                SYMTAB.insert(make_pair(label, int_to_hex(hex_to_int(SYMTAB[a])-hex_to_int(SYMTAB[b]))));
            }
        }
        else if (label != "") {
            SYMTAB.insert(make_pair(label, intermediate[i]));
        }
    }
}

/* First pass of assembler */
void pass1() {
    // Assign addresses to all source code statements

    if get_opcode(firstline) = "START" {
        LOCCTR, start = get_operand(firstline);
    }
    // todo: Update currentLine
    // Assign addresses to labels
    while (get_operator(currentLine) != "END") {
        // Check if current line is assembler directive
        // Check for symbol in LABEL field, insert into SYMTAB if not already there
        if (get_operator is a LABEL) {
            	generate_symtab();
        }
        // WORD/RESW/RESB/BYTE LOCCTR changes
        if (get_operator is in OPTAB) {
            LOCCTR += 3;
        } else if (get_operator == "WORD") {
            LOCCTR += 3;
        } else if (get_operator == "RESW") {
            LOCCTR = LOCCTR + (3 * get_operand);
        } else if (get_operator == "RESB") {
            LOCCTR += (get_operand);
        } else if (get_operator == "BYTE") {
            LOCCTR += (get_operand length);
        } else {
            cout << "Error";
        }
        intermediate.insert(LOCCTR, get_operand);
        // todo: Update currentLine
    }
    progLength = LOCCTR;
    // todo: Process directives
}

/* Second pass of assembler */
void pass2() {
    // todo: Update currentLine to firstLine
    if (get_operator(currentLine) == "START") {
        // todo: write line to output file
        // todo: Update currentLine
    }
    while (get_operator(currentLine) != "END") {
        if (currentLine opcode is in optab) {
            // Check if symbol
            if (get_operand(currentLine) == symbol) {
                if (SYMTAB contains get_operand(currentLine)) {
                    // todo: store symbol value as operand address
                } else {
                    // todo: store 0 as operand address, set error flag
                } 
            } else {
                // todo: create objcode generation method
                generate_objcode();
            }
        } else {
            if (opcode == "BYTE" || "WORD") {
                // todo: convert constant to objcode
            }
        }
        // todo: write line to output file
    }
    // todo: write end line to output file
}

int main(int argc, char *argv[]) {
    // todo: Get cmd line args
    string inputFile;
    vector<string> fileNames;
    if (argc >= 2) { // Command line arguments
       	for (int i = 0; i < argc; i++) {
            string fileName = argv[i];
            // Check if arg is a .sic file
            if(fileName.substr(fileName.find_last_of(".") + 1) == "sic") {
                int pos = fileName.find(".");
                fileNames.push_back(fileName.substr(0, pos));
            } else {
                 cout << "Invalid File " << argv[i] << std::endl;
                 exit(2);
            }
        }
    } else {
       	cout << "Invalid syntax.\n";
       	return 1;
    }

    // Create mnemonics
    create_mnemonics();
    
    for (string fileName : fileNames) {
        // Open input file
        ifstream inputFile;
        string filePath = fileName.append(".sic");
        inputFile.open(filePath);

        // Create output files
        ofstream outputListing;
        outputListing.open(fileName.append(".l"),ios::out);
        ofstream outputSymtab;
        outputSymtab.open(fileName.append(".st"),ios::out);

        // Populate code vector with lines from input
        string line = "";
        while (getline(inputFile, line)) {
            code.push_back(line);
        }

        pass1();
        pass2();

        // Close files, clear code vector for next file
        inputFile.close();
        outputListing.close();
        outputSymtab.close();
        code.clear();
    }

    // todo: create output file
    
    return 0;

}
