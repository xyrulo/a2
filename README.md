**Info**

Written by Jonah Hedlund (823867220), Maximilian Nock, (824823292), Fusheng Jia (822109555), CS 530, Fall 2023

Assigment 2, Two Pass Assembler for SIC/XE machine

Files: 
- **axe.cpp**: The main file, containing all of the mentioned functions.
- **MakeFile**: Used to make axe from axe.cpp
- **SDD**: Document showcase the group's plan of action and any changes during the course of development
- **test files**: Files that axe was tested on, including
   - s.sic
- **README:** This file.

Made to be compiled by G++. Turned in on cssc2621

We have created a two pass assembler that will open the source files, if unable it will throw and error. "axe" reads each source file, scans the files, and processes each assembler directive using the two pass assembler logic. The program then reads the file for each instruction. Then the program will generate a listing file and SYMTAB according to SIC/XE standards.

Listing Files will be named the same as source files with '.l' filename extension
SYMTAB files will use the same name as the source files with '.st' filename extension.

To use, simply call the make file, then input `axe` followed by the .sic files you wish to assemble.

**Variables and Functions**
1. **Mnemonics Map (`mnemonics`):**
   - Stores the mnemonic instructions and their corresponding opcodes for the XE architecture.

2. **Code Vector (`code`):**
   - Stores the lines of code read from the input XE assembler source file(s).

3. **Symbol Table (`symtab`):**
   - Maps labels to their corresponding addresses. It is generated during the first pass.

4. **Intermediate Code Map (`intermediate`):**
   - Maps line numbers to their corresponding lines of code. This is used during symbol table generation.

5. **Functions:**
   - **`create_mnemonics()`:** Populates the mnemonic map with XE assembly language instructions and their opcodes.
   - **`get_label()`, `get_operator()`, `get_operand()`:** Extracts label, operator, and operand from a line of code.
   - **`int_to_hex()`, `hex_to_int()`:** Converts integers to hexadecimal strings and vice versa.
   - **`generate_symtab()`:** Generates the symbol table during the first pass. Handles EQU directives and assigns addresses to labels.
   - **`assign_addresses`
   - **`generate_objcode()`:** Generates object code in second pass.

6. **Pass Functions (`pass1()` and `pass2()`):**
   - **`pass1()`:** Invokes functions to generate the opcode table and symbol table. Assigns addresses to labels.
   - **`pass2()`:** Generates object code.

7. **Main Function (`main()`):**
   - Handles input file(s) and creates appropriate output files.
   - Calls `create_mnemonics()`, `pass1()`, and `pass2()` in sequence.

   There was a lot we were unable to finish. Those concerns have been address in the SDD, towards the bottom, stating what happened and what we have learned from this experience.