/*
 * The internal definitions
 *
 * Copyright (c) 2008, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBUCA_DEFINITIONS_H )
#define _LIBUCA_DEFINITIONS_H

#include <common.h>

/* Define HAVE_LOCAL_LIBUCA for local use of libuca
 */
#if !defined( HAVE_LOCAL_LIBUCA )
#include <libuca/definitions.h>

#else
#define LIBUCA_VERSION					20080903

/* The libuca version string
 */
#if defined( LIBUCA_WIDE_CHARACTER_TYPE )
#define LIBUCA_VERSION_STRING				L"20080903"
#else
#define LIBUCA_VERSION_STRING				"20080903"
#endif

/* The endian definitions
 */
#define LIBUCA_ENDIAN_BIG				(uint8_t) 'b'
#define LIBUCA_ENDIAN_LITTLE				(uint8_t) 'l'

/* The codepage definitions
 */
#define LIBUCA_CODEPAGE_ASCII				0x41
#define LIBUCA_CODEPAGE_WINDOWS_1250			1250
#define LIBUCA_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	1250
#define LIBUCA_CODEPAGE_WINDOWS_1251			1251
#define LIBUCA_CODEPAGE_WINDOWS_CYRILLIC		1251
#define LIBUCA_CODEPAGE_WINDOWS_1252			1252
#define LIBUCA_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	1252
#define LIBUCA_CODEPAGE_WINDOWS_1253			1253
#define LIBUCA_CODEPAGE_WINDOWS_GREEK			1253
#define LIBUCA_CODEPAGE_WINDOWS_1254			1254
#define LIBUCA_CODEPAGE_WINDOWS_TURKISH			1254
#define LIBUCA_CODEPAGE_WINDOWS_1255			1255
#define LIBUCA_CODEPAGE_WINDOWS_HEBREW			1255
#define LIBUCA_CODEPAGE_WINDOWS_1256			1256
#define LIBUCA_CODEPAGE_WINDOWS_ARABIC			1256
#define LIBUCA_CODEPAGE_WINDOWS_1257			1257
#define LIBUCA_CODEPAGE_WINDOWS_BALTIC			1257
#define LIBUCA_CODEPAGE_WINDOWS_1258			1258
#define LIBUCA_CODEPAGE_WINDOWS_VIETNAMESE		1258

#endif

/* Character definitions
 */
#define LIBUCA_UNICODE_REPLACEMENT_CHARACTER		0x0000fffd
#define LIBUCA_UNICODE_BASIC_MULTILINGUAL_PLANE_MAX	0x0000ffff
#define LIBUCA_UNICODE_SURROGATE_LOW_RANGE_START	0x0000dc00
#define LIBUCA_UNICODE_SURROGATE_LOW_RANGE_END		0x0000dfff
#define LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_START	0x0000d800
#define LIBUCA_UNICODE_SURROGATE_HIGH_RANGE_END		0x0000dbff
#define LIBUCA_UNICODE_CHARACTER_MAX			0x0010ffff

#define LIBUCA_UTF16_CHARACTER_MAX			0x0010ffff
#define LIBUCA_UTF32_CHARACTER_MAX			0x7fffffff

#define LIBUCA_ASCII_REPLACEMENT_CHARACTER		0x1a

#endif

