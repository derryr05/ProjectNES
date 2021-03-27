#pragma once

#include <vector>
#include <string>
#include <map>

class Bus;

class CPU
{
public:
	CPU();
	~CPU();

// 6502 Registers
	uint8_t accumulator		  = 0x00;
	uint8_t xReg              = 0x00;
	uint8_t yReg              = 0x00;
	uint8_t stackPtr          = 0x00;
	uint8_t statusReg         = 0x00;
	uint16_t programCounter   = 0x0000;
	
// Reset interrept - CPU enters initialisation 
	void Reset();

// IRQ - Maskable interrupt (Can be disabled)
	void IRQ();

// NMI - Non maskable interrupt (CPU cannot ignore)
	void NMI();

// CPU clock
	void Clock();

// Method to check whether an instruction has completed
	bool IsComplete();

// Link the CPU to Bus
	void ConnectBus(Bus *_bus) { busPtr = _bus; }

// Produce map of strings with keys to address start, for the specified address range
	std::map<uint16_t, std::string> disassemble(uint16_t addrStart, uint16_t addrStop);

// 6502 CPU Flags in enum for direct use
	enum FLAGS 
	{
		CARRY			= (1 << 0),			// Carry flag
		ZERO			= (1 << 1),			// Zero flag
		INTER_DISABLE	= (1 << 2),			// Interrupt disable flag
		DECIMAL			= (1 << 3),			// Decimal mode flag (NOT USED)
		BREAK			= (1 << 4),			// Break flag
		UNUSED			= (1 << 5),			// Unused flag (ALWAYS SET)
		OVERFL			= (1 << 6),			// Overflow flag
		NEGATIVE		= (1 << 7)			// Negative flag
	};

private:
// Flag functions to access the status register 
	uint8_t GetFlag(FLAGS flag);
	void SetFlag(FLAGS flag, bool isOverflow);

// Emulation variables
	uint8_t fetched		 = 0x00;   // Working input value
	uint16_t temp		 = 0x0000; 
	uint16_t addr_abs	 = 0x0000; // Used memory addresses stored here
	uint16_t addr_rel	 = 0x0000; // Absolote addresses following a branch
	uint8_t opcode		 = 0x00;   // The instruction byte
	uint8_t cycles		 = 0;	   // Holds the remaining cycle count of an instruction
	uint32_t clock_count = 0;	   // Accumulation of clocks

// Communication with the bus
	Bus *busPtr = nullptr;
	uint8_t Read(uint16_t addrLocation);
	void Write(uint16_t addrLocation, uint8_t data);

// INCLUDE COMMENT
	uint8_t Fetch();

// INCLUDE COMMENT
	struct Instruction {
		std::string name;
		uint8_t(CPU::* operate)(void) = nullptr;
		uint8_t(CPU::* addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};

	std::vector<Instruction> lookup;

// ------------- ADDRESSING MODES -------------- //

	uint8_t ABS();	uint8_t ABX();	uint8_t ABY();
	uint8_t IMM();	uint8_t IMP();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();	uint8_t REL();
	uint8_t ZP_();	uint8_t ZPX();	uint8_t ZPY();

// ----------------- OPCODES ------------------- //

	uint8_t ADC();	uint8_t AND();	uint8_t ASL();
	uint8_t BCC();	uint8_t BCS();	uint8_t BEQ();
	uint8_t BIT();	uint8_t BMI();	uint8_t BNE();
	uint8_t BPL();	uint8_t BRK();	uint8_t	BVC();
	uint8_t BVS();	uint8_t CLC();  uint8_t CLD();
	uint8_t CLI();	uint8_t CLV();	uint8_t CMP();
	uint8_t CPX();	uint8_t CPY();	uint8_t DEC();	
	uint8_t DEX();	uint8_t DEY();  uint8_t EOR();
	uint8_t INC();	uint8_t	INX();	uint8_t INY();
	uint8_t JMP();  uint8_t JSR();	uint8_t LDA();
	uint8_t LDX();  uint8_t LDY();	uint8_t LSR();	
	uint8_t NOP();  uint8_t ORA();	uint8_t PHA();	
	uint8_t PHP();  uint8_t PLA();	uint8_t PLP();	
	uint8_t	ROL();  uint8_t ROR();	uint8_t RTI();
	uint8_t RTS();	uint8_t SBC();	uint8_t SEC();
	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();
	uint8_t TAY();	uint8_t TSX();	uint8_t	TXA();
	uint8_t TXS();	uint8_t TYA();

	uint8_t XXX(); // Unofficial opcodes
};

