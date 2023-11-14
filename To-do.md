To do:

Need to figure out first: How are we storing the address and object code? Can we use `intermediate` to store the object code after done calculating, as in overwrite the line of code it stores? My current thought process is:
- pass 1 (address assigned to LOCCTR, put in `intermediate`?) 
- pass 2 (create obj code, overwrite code in intermediate with obj code) 
- write address << line of code from input << object code << endl
- write SYMTAB

**Core work**
- Add more instructions to mnemonics
- Add assembly directives list 
- generate_objcode()
    - separate by format
    - create objcode generation method
- generate_symbtab()
    - LITTAB too?
- pass1()
    - create iteration method to go through each line
    - swap pseudocode with appropriate methods and variables
    - ensure addresses are properly calculated
    - **Process assembler directives**
- pass2()
    - swap pseudocode with appropriate methods and variables
    - store lines as necessary for writing
- main()
    - combine intermediate and SYMTAB for full listing contents (if necessary)
    - replace pseudocode as necessary
- Make file

**Testing**
- Test formatting
- Check address, obj code calculations
- Check first/last instructions, make sure they are there/correct
- Check missing instructions/assembly directives

**Finishing touches**
- Clean up variables at the top
- Appropriate comments and documentation
- test on edoras
