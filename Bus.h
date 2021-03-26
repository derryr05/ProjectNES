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
	std::array<uint8_t, 64 * 1024> ram;

// Write to address space and read from address
	void write(uint16_t addrLocation, uint8_t data);
	uint8_t read(uint16_t addrLocation, bool readOnly = false);
};