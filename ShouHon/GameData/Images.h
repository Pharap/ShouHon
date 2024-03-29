#pragma once

uint8_t const Images16x16[] PROGMEM =
{
	16, 16,
	
	// Frame 0 - Hellbook
	0x00, 0x00, 0xFE, 0x02, 0x72, 0x4A, 0xCA, 0xFA, 0xCA, 0x4A, 0x72, 0x02, 0x02, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x37, 0x34, 0x04, 0x74, 0x75, 0x04, 0x35, 0x34, 0x34, 0x34, 0x34, 0x0F, 0x00, 0x00,
	
	// Frame 1 - Potion
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xF0, 0x18, 0x18, 0xF0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x3E, 0x7D, 0x7C, 0x7C, 0x7C, 0x5C, 0x6D, 0x3E, 0x1C, 0x00, 0x00, 0x00,
	
};

uint8_t const Images24x24[] PROGMEM =
{
	24, 24,
	
	// Frame 0 - Octoid
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0x38, 0x38, 0xF8, 0xF8, 0x98, 0x98, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40, 0x80, 0x47, 0x2F, 0x9F, 0x5F, 0xFF, 0xF3, 0x5D, 0xA2, 0x22, 0x63, 0x9C, 0x40, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x43, 0x50, 0x28, 0x07, 0x07, 0x28, 0x50, 0x43, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	
	// Frame 1 - Skel
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xCC, 0x86, 0x86, 0xFE, 0xFE, 0x86, 0x86, 0xCC, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x20, 0xE1, 0x0F, 0x43, 0xEE, 0xEE, 0x43, 0x0F, 0xE1, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0xD0, 0x10, 0x25, 0x0F, 0x0F, 0x25, 0x10, 0xD0, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

uint8_t const Images32x32[] PROGMEM =
{
	32, 32,
};

uint8_t const * const Images[] PROGMEM =
{
	Images16x16,
	Images24x24,
	Images32x32,
};
