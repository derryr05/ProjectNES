#pragma once
#include <cstdint>
#include <array>

#include "CPU.h"

class Bus
{
public:
// Constructor and destructor methods 
	Bus();
	~Bus();

// Devices on the bus
	CPU cpu;

// RAM as an array
	std::array<uint8_t, 64 * 1024> ram;

// Write to address space
	void Write(uint16_t addrLocation, uint8_t data);

// Read from address space
	uint8_t Read(uint16_t addrLocation, bool readOnly = false);
};