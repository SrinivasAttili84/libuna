/*
 * Windows 1254 codepage (Turkish) functions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#include "libuna_codepage_windows_1254.h"

/* Extended ASCII to Unicode character lookup table for Windows 1254 codepage
 * Unknown are filled with the Unicode replacement character 0xfffd
 */
const uint16_t libuna_codepage_windows_1254_byte_stream_to_unicode_base_0x80[ 32 ] = {
	0x20ac, 0xfffd, 0x201a, 0x0192, 0x201e, 0x2026, 0x2020, 0x2021,
	0x02c6, 0x2030, 0x0160, 0x2039, 0x0152, 0xfffd, 0xfffd, 0xfffd,
	0xfffd, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013, 0x2014,
	0x02dc, 0x2122, 0x0161, 0x203a, 0x0153, 0xfffd, 0xfffd, 0x0178,
};

const uint16_t libuna_codepage_windows_1254_byte_stream_to_unicode_base_0xd0[ 16 ] = {
	0x011e, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7,
	0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x0130, 0x015e, 0x00df,
};

const uint16_t libuna_codepage_windows_1254_byte_stream_to_unicode_base_0xf0[ 16 ] = {
	0x011f, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7,
	0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x0131, 0x015f, 0x00ff,
};

/* Unicode to ASCII character lookup table for Windows 1254 codepage
 * Unknown are filled with the ASCII replacement character 0x1a
 */
const uint8_t libuna_codepage_windows_1254_unicode_to_byte_stream_base_0x00d0[ 48 ] = {
	0x1a, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
	0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0x1a, 0x1a, 0xdf,
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
	0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0x1a, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0x1a, 0x1a, 0xff,
};

const uint8_t libuna_codepage_windows_1254_unicode_to_byte_stream_base_0x2010[ 24 ] = {
	0x1a, 0x1a, 0x1a, 0x96, 0x97, 0x1a, 0x1a, 0x1a,
	0x91, 0x92, 0x82, 0x1a, 0x93, 0x94, 0x84, 0x1a,
	0x86, 0x87, 0x95, 0x1a, 0x1a, 0x1a, 0x85, 0x1a,
};

