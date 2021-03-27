/*
	Bus.cpp emulates the data communication between components.
*/

#include "Bus.h"

Bus::Bus()
{
	cpu.ConnectBus(this);

	// Clear RAM
	for (auto &i : ram) 
		i = 0x00;
}

Bus::~Bus() 
{

}

void Bus::Write(uint16_t addrLocation, uint8_t data)
{
	// Write at specified RAM location with data (0 to 65535)
	if (addrLocation >= 0x0000 && addrLocation <= 0xFFFF) 
		ram[addrLocation] = data;
}

uint8_t Bus::Read(uint16_t addrLocation, bool readOnly)
{
	// Read at specified RAM location with data (0 to 65535)
	if (addrLocation >= 0x0000 && addrLocation <= 0xFFFF)
		return ram[addrLocation];

	// If somehow outside the range
	return 0x00;
}