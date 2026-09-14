#include <Chip-8.h> // Preprocessor
#include <GUI.h>    // Contains interfaces for player
#include <cstdint>  // Fixed width integers
#include <fstream>  // File handling

// Core logic of Chip-8 belongs to this class
class Chip8Cpu
{
    public:
        uint8_t Registers[16] {};      // 16 8-bit registers
        uint8_t Memory[4096] {};       // 4096 bytes of memory
        uint16_t Index {};          // Stores address for use during operations
        uint16_t ProgramCounter {}; // Stores address of the next instruction

        uint16_t Stack[16] {};          // 16 level stack
        uint8_t StackPointer {};    // 8-bit stack pointer

        uint8_t DelayTimer{};       // 8-bit delay timer
        uint8_t SoundTimer{};       // 8-bit sound timer

        uint8_t Keyboard[16] {};    // 16-key keyboard
        // I used "uint32_t Display[64][32];" but tutorial suggested what I am using now
        uint32_t Display[64*32]{};  // 64x32 Monochrome display. 
    
};