**Info**

Written by Jonah Hedlund (823867220), Maximilian Nock, (824823292), Fusheng Jia ()l, CS 530, Fall 2023

Assigment 2, Two Pass Assembler for SIC/XE machine

Files: axe.cpp, MakeFile, README, sdd, test files

Made to be compiled by G++.

We have created a two pass assembler that will open the source files, if unable it will throw and error. "axe" reads each source file, scans the files, and processes each assembler directive using the two pass assembler logic. The program then reads the file for each instruction. Then the program will generate a listing file and SYMTAB according to SIC/XE standards.

Listing Files will be named the same as source files with '.l' filename extension
SYMTAB files will use the same name as the source files with '.st' filename extension.

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

6. **Pass Functions (`pass1()` and `pass2()`):**
   - **`pass1()`:** Invokes functions to generate the opcode table and symbol table. Assigns addresses to labels.
   - **`pass2()`:** Yet to be implemented. It would handle the second pass of the assembler.

7. **Main Function (`main()`):**
   - Calls `create_mnemonics()`, `pass1()`, and `pass2()` in sequence.