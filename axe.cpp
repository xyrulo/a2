/*Jonah Hedlund cssc  , Maximilian Nock cssc2602, Fusheng Jia cssc */
#include <stdio.h>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <bitset>

using namespace std;

string progName;
vector<string> code;
map<string, string> REG;
unordered_map<string, string> mnemonics;
vector<string> format1 = {};
vector<string> format2 = {"ADDR", "CLEAR", "COMPR", "TIXR"};
map<string, string> SYMTAB;
map<string, string> OPTAB;
map<int, string> intermediate;
map<int, string> listing;
string assembler_dir[] = {"BASE","BYTE","WORD","RESW","RESB","EQU"};
set<string> assembler_dirc; 
int LOCCTR = 0, progLength, start = 0, pc = 0, base = 0, index = 0;

void create_mnemonics() {
    mnemonics[(string)"ADD"] = (string)"18";
    mnemonics[(string)"ADDR"] = (string)"58";
    mnemonics[(string)"AND"] = (string)"40";
    mnemonics[(string)"CLEAR"] = (string)"B4";
    mnemonics[(string)"COMP"] = (string)"28";
    mnemonics[(string)"COMPR"] = (string)"A0";
    mnemonics[(string)"J"] = (string)"3C";
    mnemonics[(string)"JEQ"] = (string)"30";
    mnemonics[(string)"JGT"] = (string)"34";
    mnemonics[(string)"JLT"] = (string)"38";
    mnemonics[(string)"JSUB"] = (string)"48";
    mnemonics[(string)"LDA"] = (string)"00";
    mnemonics[(string)"LDB"] = (string)"68";
    mnemonics[(string)"LDCH"] = (string)"50";
    mnemonics[(string)"LDL"] = (string)"8";
    mnemonics[(string)"LDT"] = (string)"74";
    mnemonics[(string)"MUL"] = (string)"20";
    mnemonics[(string)"OR"] = (string)"44";
    mnemonics[(string)"RD"] = (string)"D8";
    mnemonics[(string)"RSUB"] = (string)"4C";
    mnemonics[(string)"STA"] = (string)"0C";
    mnemonics[(string)"STCH"] = (string)"54";
    mnemonics[(string)"STL"] = (string)"14";
    mnemonics[(string)"STSW"] = (string)"E8";
    mnemonics[(string)"STX"] = (string)"10";
    mnemonics[(string)"SUB"] = (string)"1C";
    mnemonics[(string)"TD"] = (string)"E0";
    mnemonics[(string)"TIXR"] = (string)"B8";
    mnemonics[(string)"WD"] = (string)"DC";
    mnemonics[(string)"A"] = (string)"0";
    mnemonics[(string)"X"] = (string)"1";
    mnemonics[(string)"S"] = (string)"2";
    mnemonics[(string)"T"] = (string)"5";
}

/* Create directives */
void create_directives() {
		for(int i = 0; i < 6; i++)
			assembler_dirc.insert(assembler_dir[i]);
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
    return hex;
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

int string_to_int(string s) {
    int ans = 0;
		for(int i = 0;i < s.size(); i++){
			ans *= 10;
			ans += s[i]-'0';
		}
		return ans;
}

int checkIndexed(string str){
    if(str.substr(str.length() - 2 , str.length()) == ",X" || str.substr(str.length() - 2 , str.length()) == ",x")
        return 1;
    else
        return 0;
}

int checkPCRel(int num){
    if (num >= -2048 && num <= 2047)
        return 1;
    else
        return 0;
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

void assign_location() {
    int ctr = 0;
    int location_ctr = string_to_int(get_operand(code[0]));
    string loc = int_to_hex(location_ctr);
    intermediate.insert(make_pair(ctr,loc));
    intermediate.insert(make_pair(++ctr,loc));
    for(int i = 2; i < code.size(); i++){
        string current_operator = get_operator(code[i]);
        string previous_operator = get_operator(code[i-1]);
        if(assembler_dirc.find(previous_operator) != assembler_dirc.end()) {
            if(previous_operator == "RESW")
                location_ctr += 3;
            else if(previous_operator == "BYTE"){
                if(code[i-1][20] == 'C')
                    location_ctr += 3;
                else if(code[i-1][20] == 'X')
                    location_ctr++;
            }
            else if(previous_operator=="RESB")
                location_ctr+=string_to_int(get_operand(code[i-1]));
        }
        else if (code[i-1][10] == '+')
            location_ctr += 4;
        else if (previous_operator == "COMPR" || previous_operator == "CLEAR" || previous_operator == "TIXR")
            location_ctr += 2;
        else
            location_ctr += 3;

        if(current_operator=="BASE"){
            loc = "____";
        }
        else{
            loc = int_to_hex(location_ctr);
        }
        intermediate.insert(make_pair(i,loc));
    }
    
}

// Generating objcode
void generate_objcode() {
    bool nixbpe[6] = {0, 0, 0, 0, 0, 0};
    for(int 0 = 1; i < code.size(); i++){
        string label = get_label(code[i]);
        string opr = get_operator(code[i]);
        string operand = get_operand(code[i]);
        string address = intermediate[i];
        // Determine format
        // Todo: skip necessary assembler directives
        // Check for format 1 instructions
        if (opr == "ADDR" || "CLEAR" || "COMPR" || "TIXR") {
            // todo: Format 2
            
        } else { // Format 3/4
            nixbpe[0] = (operand[0] == '@');
            nixbpe[1] = (operand[0] == '#');
            // Check for indexed
            nixbpe[2] = (operand[operand.length() - 1] == 'X' && operand[operand.length() - 2] == ',') ? 1 : 0;
            nixbpe[3] = 0;
            nixbpe[4] = 0;
            // todo: add opr hex to nixbpe, convert to hex
            // Make format 3/4 adjustments
            if (operand[0] == '+') {
                //Format 4: just use direct
                nixbpe[5] = 1;
                // Convert operand to bitset, to add nixbpe
                // Maybe use bitmasking 
                bitset<4> bs(opr);
                if (nixbpe[1] && !nixbpe[0]) {
                    // todo: append disp to previous
                } else {
                    // todo: calculate disp
                }
            } else {
                //Format 3
                // Default PC relative, unless otherwise specified or needed
                // Convert operand to bitset, to add nixbpe
                bitset<4> bs(opr);
                if (nixbpe[1] && !nixbpe[0]) {
                    // todo: append disp to previous
                } else {
                    // todo: calculate disp
                }
            }
        }
}

/* First pass of assembler */
void pass1() {
    assign_location();
    generate_symtab(); // make sure absolute/relative is included
}
/*include bit masking*/
/* Second pass of assembler */
void pass2() {
    string currentLine = code[0];
    if (get_operator(currentLine) == "START") {
        // todo: write line to intermediate
        currentLine = code[1];
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
                generate_objcode();
            }
        } else {
            if (opcode == "BYTE" || "WORD") {
                // todo: convert constant to objcode
            }
        }
        // todo: write line to intermediate
    }
    // todo: write end line to intermediate
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

    // Create mnemonics OpCode Table
    create_mnemonics();
    
    for (string fileName : fileNames) {
        // Open input file
        ifstream inputFile;
        string filePath = fileName.append(".sic");
        inputFile.open(filePath);

        // Populate code vector with lines from input
        string line = "";
        while (getline(inputFile, line)) {
            code.push_back(line);
        }
        inputFile.close();

        pass1();
        pass2();

        // Create listing file
        ofstream outputListing;
        outputListing.open(fileName.append(".l"),ios::out););
        // Write addresses and obj code from intermediate
        for (int i = 0; i < code.size; i++) {
            outputListing << intermediate[i] << "\t" << code[i] << "\t" << listing[i];
        }
        outputListing.close();

        // Create SYMTAB file
        ofstream outputSymtab;
        outputSymtab.open(fileName.append(".st"),ios::out);
        map<string, string>::iterator it = SYMTAB.begin(); 
        outputListing << "Symbol  Value   Flags:" << endl << "-----------------------" << endl;
        for (auto i : SYMTAB) {
            outputListing << i.first << "\t" << i.second << "\t" <</* flags here <<*/ endl; 
        }

        // Add LITTAB
        cout << "Name    Literal   Address:" << endl << "-----------------------" << endl;
        for (auto i : LITTAB) {
            outputListing << i.first << "\t" << i.second << "\t" <</* address here <<*/ endl; 
        }
        outputSymtab.close();
        
        code.clear();
    }
    
    return 0;

}
