Created folder for project
Made 3 cpp files (and its header files) - Seems more sensible based on past experiences making a game, main is the loop, chip-8 is the tool/logic and GUI is the adjustable interface using other libraries
Install Raylib through Github
 - Extracted zip folder 
 - Moved contents of lib and include folder into project folder

Compile : 
Avoiding extension from VSC and other tools as it might complicate things when I don't already know anything
Using code from Google Gemini :
Open CMD
cd "Reese\4 - Programming\1 - Local projects"
g++ Main.cpp Chip-8.cpp GUI.cpp -L. -o "Build\Chip-8.exe" -lraylib -lopengl32 -lgdi32 -lwinmm

---

# Introduction : 
Emulators fully simulate the behaviours of intended hardware, they read the original machine code instructions and replicate it
Compared to virtual machine which do not fully simulate so have worse compatibility but better performance as they provide a a layer that is closely built to the hardware it runs on

Chip-8 is not a actual hardware but a specification for 1. Kinda like how C is portable because it's behaviour is basic and shared across various systems which can be compiled to intermediate code

Using this guide : https://austinmorlan.com/posts/chip8_emulator/#16-8-bit-registers

# Creating specification : 
Core logic stored in Chip-8 object
To match fixed bit length data types, use cstdint

Chip-8 has 35 opcodes meaning theyre are 2 bytes long
Aparrently operands are built into the opcodes hence why its possible to have the statement above which was confusing
It is RISC because it has fixed length commands (always 8-bits) but the operand may take up a nibble or 2

Tutorial seems to use modern value-initialisation which disallows narrowing conversions (int cannot store 4.5)

16 8-bit registers : 
Labelled V0-VF (not sure how to reference later, probably a mapping or casting hex to dec?)
Holds values 0x00-0xFF
Register VF is special, it's used as a flag to hold information about result of operations

4KB memory : 
4096 bytes of memory
Address space ranges 0x000-0xFFF
 - 0x000-0x1FF - Reserved for interpreter, however will not be used except for built in characters
 - 0x050-0x0A0 - 16 built-in characters 0-F, loaded into Chip-8 space of memory
 - 0x200-0xFFF - General RAM space for ROM instructions and free space after that

16-bit index register : 
Store memory addresses for use during operations

16-bit program counter : 
Store memory address of the next instruction
"An instruction is two bytes but memory is addressed as a single byte, so when we fetch an instruction from memory we need to fetch a byte from PC and a byte from PC+1 and connect them into a single value. We then increment the PC by 2 because We have to increment the PC before we execute any instructions because some instructions will manipulate the PC to control program flow. Some will add to the PC, some will subtract from it, and some will change it completely."
=>  
Basically, a instruction is 2 bytes, each part of memory is 8 bits/1 byte so to access the instruction : Fetch contents of PC and PC + 1, then concatenate them to get the full instruction. Then increment PC by 2 (some instructions manipulate PC by add/subtract/change like jump or calls) 
This took a bit to get my head around

16-level stack :
Stack contains PC value when CALL was executed
RET returns PC value to PC and removes 
 - CALL - CPU will execute other instructions first
 - RET - Return to the point where CALL was made

8-bit stack pointer : 
In this implementation, stack pointer points to the current free space (if there are 16 items, it is fine because its labeled from 0-15)

8-bit delay timer :
If timer is 0, stay 0
Else, decrement at 60Hz (Apparently use whatever rate cycle clock is set to)

8-bit sound timer :
Same behaviour, however a single buzz will go while its non-zero

16 input keys : 
0-F, either pressed or not pressed
Guide leads to another guide which stats that the recommended layout is the keyboard layout so I will use that (kinda looks nicer) : 
|1|2|3|4|
+-+-+-+-+
|Q|W|E|R|
+-+-+-+-+
|A|S|D|F|
+-+-+-+-+
|Z|X|C|V|

64x32 monochrome display memory : 
Array size - 64x32
Contents are monochrome
Basically, use sprites to toggle display. To update sprite position, draw at the same position (unsets display at local region back to black), then draw at new region (sets black parts to white). Use XOR table to demonstrate.


To do : 
Set PC to 0x200
Set stack pointer, delay timer and sound timer to 0
Keyboard - Initialise
Display - Initialise display as blank (0x00000000)

# Loading ROM
I thought I needed to convert it to hex but turns out memory stores it raw so wasted some time.

Considerations : 
Loading need to check if successful, if not then cancel program
TEST - Print inputs

Attempt to load file
 - If fail - Quit program and output message
Extract each byte and insert it into memory, starting at 0x200
Set PC to 0x200

# Redesign compile structure and process
I put all the library files back into their folders as its much cleaner and learnt some of the compile command to fit this change.
cd "Reese\4 - Programming\2 - Cloned projects"
g++ * -Llib -Iinclude -o "Build\Chip-8.exe" -lraylib -lopengl32 -lgdi32 -lwinmm


---

# Questions/things I want to change and improve at later date 


# Final thoughts



---

# Notes : 
Sections to learn :
 - 1 and 2 - learn structure and basics of operating the language
 - O - Bit manipulation
 - 12 - References and pointers
 - 14/15 - Classes
 - 17 - Arrays
 - 28 - IO streams

 1,2, 28



---

# CPP
## RAND
Best way to initialise variables is to declare the signature and then list initialise it

## Compile
#include must use quotes for header files in folder of the compiled file, using angle brackets means it checks system files

Either you have to specify every file to compile (including extension) or use *

Library packages can come in .h (so your program can compile), .a (historically a archive format and used today to contain multiple object files for static linking or import tool for dll (not required but dll has to be manually imported for with verbose code which is only done so for modding or plugins)) and .dll (dynamic library)

-I... Include search path - Used for header files
-L... Library search path - Usef for compiled binary libraries
-l... File finder - Used to name the library binary file in the library search path

If you nest the header files in further folders, compile command or include command will need to demonstrate it
Subfolders in libraries file however will require this path to be passed into the compile command, since this is used for multiple libraries, each folder needs to be specified individually since the compiler only looks at the level of the folder provided and not above or below

## IO
#include <iostream>
'''std::cout <<''' - Can output strings and numbers. Multiple things can be outputted by repeating the insertion operator, this concatenates the different items but does not pad (manually have to add space)

'''std:endl''' - Acts as a carriage character return, is not its own procedure but a variable so must be added to std::cout. However this flushes the buffer so an alternative is "\n" 

'''std::cin >> x''' - Takes input from console, you can take multiple inputs like cout however it should be taken with spaces/newlines/tabs separating it

Literals - Fixed/constant values inserted in the source code

Side effect - Changes state or value in progarm apart from return values





Do section 2 to understand basics
Search about list initialisation and arrays and how to pass them
Do section 28 for file handling







