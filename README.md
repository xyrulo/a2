README
Jonah Hedlund,
Maximilian Nock, 824823292
Fusheng Jia, 
CS 530, Fall 2023
Assigment 2, Two Pass Assembler for SIC/XE machine
Files: axe.cpp, MakeFile, README, sdd, Test Files, source files
Has been made to be compiled by gcc and g++
We have created a two pass assembler that will open the source files, if unable it will throw and error. "axe" reads each source file, scans the files, and processes each assembler directive using the two pass assembler logic. The program then reads the file for each instruction. Then the program will generate a listing file and SYMTAB according to SIC/XE standards.
Listing Files will be named the same as source files with '.l' filename extension
SYMTAB files will use the same name as the source files with '.st' filename extension.