/*
 * Copyright (C) 2015 Motorola Mobility, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>

/* Polynomial is 0x8005 */
static const uint16_t crc16_lookup_tbl[256] = {
	0x0000, 0x0580, 0x0F80, 0x0A00, 0x1B80, 0x1E00, 0x1400, 0x1180,
	0x3380, 0x3600, 0x3C00, 0x3980, 0x2800, 0x2D80, 0x2780, 0x2200,
	0x6380, 0x6600, 0x6C00, 0x6980, 0x7800, 0x7D80, 0x7780, 0x7200,
	0x5000, 0x5580, 0x5F80, 0x5A00, 0x4B80, 0x4E00, 0x4400, 0x4180,
	0xC380, 0xC600, 0xCC00, 0xC980, 0xD800, 0xDD80, 0xD780, 0xD200,
	0xF000, 0xF580, 0xFF80, 0xFA00, 0xEB80, 0xEE00, 0xE400, 0xE180,
	0xA000, 0xA580, 0xAF80, 0xAA00, 0xBB80, 0xBE00, 0xB400, 0xB180,
	0x9380, 0x9600, 0x9C00, 0x9980, 0x8800, 0x8D80, 0x8780, 0x8200,
	0x8381, 0x8601, 0x8C01, 0x8981, 0x9801, 0x9D81, 0x9781, 0x9201,
	0xB001, 0xB581, 0xBF81, 0xBA01, 0xAB81, 0xAE01, 0xA401, 0xA181,
	0xE001, 0xE581, 0xEF81, 0xEA01, 0xFB81, 0xFE01, 0xF401, 0xF181,
	0xD381, 0xD601, 0xDC01, 0xD981, 0xC801, 0xCD81, 0xC781, 0xC201,
	0x4001, 0x4581, 0x4F81, 0x4A01, 0x5B81, 0x5E01, 0x5401, 0x5181,
	0x7381, 0x7601, 0x7C01, 0x7981, 0x6801, 0x6D81, 0x6781, 0x6201,
	0x2381, 0x2601, 0x2C01, 0x2981, 0x3801, 0x3D81, 0x3781, 0x3201,
	0x1001, 0x1581, 0x1F81, 0x1A01, 0x0B81, 0x0E01, 0x0401, 0x0181,
	0x0383, 0x0603, 0x0C03, 0x0983, 0x1803, 0x1D83, 0x1783, 0x1203,
	0x3003, 0x3583, 0x3F83, 0x3A03, 0x2B83, 0x2E03, 0x2403, 0x2183,
	0x6003, 0x6583, 0x6F83, 0x6A03, 0x7B83, 0x7E03, 0x7403, 0x7183,
	0x5383, 0x5603, 0x5C03, 0x5983, 0x4803, 0x4D83, 0x4783, 0x4203,
	0xC003, 0xC583, 0xCF83, 0xCA03, 0xDB83, 0xDE03, 0xD403, 0xD183,
	0xF383, 0xF603, 0xFC03, 0xF983, 0xE803, 0xED83, 0xE783, 0xE203,
	0xA383, 0xA603, 0xAC03, 0xA983, 0xB803, 0xBD83, 0xB783, 0xB203,
	0x9003, 0x9583, 0x9F83, 0x9A03, 0x8B83, 0x8E03, 0x8403, 0x8183,
	0x8002, 0x8582, 0x8F82, 0x8A02, 0x9B82, 0x9E02, 0x9402, 0x9182,
	0xB382, 0xB602, 0xBC02, 0xB982, 0xA802, 0xAD82, 0xA782, 0xA202,
	0xE382, 0xE602, 0xEC02, 0xE982, 0xF802, 0xFD82, 0xF782, 0xF202,
	0xD002, 0xD582, 0xDF82, 0xDA02, 0xCB82, 0xCE02, 0xC402, 0xC182,
	0x4382, 0x4602, 0x4C02, 0x4982, 0x5802, 0x5D82, 0x5782, 0x5202,
	0x7002, 0x7582, 0x7F82, 0x7A02, 0x6B82, 0x6E02, 0x6402, 0x6182,
	0x2002, 0x2582, 0x2F82, 0x2A02, 0x3B82, 0x3E02, 0x3402, 0x3182,
	0x1382, 0x1602, 0x1C02, 0x1982, 0x0802, 0x0D82, 0x0782, 0x0202,
};

static inline u16 crc16_one(u16 crc, const u8 data)
{
	return (crc >> 8) ^ crc16_lookup_tbl[(crc ^ data) & 0xff];
}

uint16_t crc16_calc(uint16_t crc, uint8_t const *buffer, size_t len)
{
	while (len--)
		crc = crc16_one(crc, *buffer++);
	return crc;
}
