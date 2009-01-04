/*
 * UTF-8 stream functions
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

#include <common.h>
#include <notify.h>
#include <types.h>

#include "libuca_definitions.h"
#include "libuca_unicode_character.h"
#include "libuca_utf8_stream.h"

/* Copies an UTF-8 stream byte order mark (BOM)
 * Returns 1 if successful or -1 on error
 */
int libuca_utf8_stream_copy_byte_order_mark(
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     size_t *utf8_stream_index )
{
	static char *function = "libuca_utf8_stream_copy_byte_order_mark";

	if( utf8_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream.\n",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf8_stream_index == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream index.\n",
		 function );

		return( -1 );
	}
	if( ( *utf8_stream_index + 2 ) >= utf8_stream_size )
	{
		notify_warning_printf( "%s: UTF-8 stream too small.\n",
		 function );

		return( -1 );
	}
	utf8_stream[ *utf8_stream_index     ] = 0xef;
	utf8_stream[ *utf8_stream_index + 1 ] = 0xbb;
	utf8_stream[ *utf8_stream_index + 2 ] = 0xbf;

	*utf8_stream_index += 3;

	return( 1 );
}

/* Determines the size of a UTF-8 stream from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuca_utf8_stream_size_from_utf8(
         libuca_utf8_character_t *utf8_string,
         size_t utf8_string_size,
         uint8_t strict_mode )
{
	static char *function    = "libuca_utf8_stream_size_from_utf8";
	ssize_t utf8_stream_size = 0;

	if( utf8_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	utf8_stream_size = 3 + utf8_string_size;

	return( utf8_stream_size );
}

/* Copies an UTF-8 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuca_utf8_stream_copy_from_utf8(
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     libuca_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     uint8_t strict_mode )
{
	static char *function       = "libuca_utf8_stream_copy_from_utf8";
	size_t utf8_string_iterator = 0;
	size_t utf8_stream_iterator = 0;

	if( utf8_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream.\n",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( libuca_utf8_stream_copy_byte_order_mark(
	     utf8_stream,
	     utf8_stream_size,
	     &utf8_stream_iterator ) != 1 )
	{
		notify_warning_printf( "%s: unable to copy UTF-8 byte order mark.\n",
		 function );

		return( -1 );
	}
	while( utf8_string_iterator < utf8_string_size )
	{
                /* TODO add strict test ?
		 */
		utf8_stream[ utf8_stream_iterator++ ] = utf8_string[ utf8_string_iterator++ ];
	}
	return( 1 );
}

/* Determines the size of a UTF-8 stream from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuca_utf8_stream_size_from_utf16(
         libuca_utf16_character_t *utf16_string,
         size_t utf16_string_size,
         uint8_t strict_mode )
{
	static char *function                        = "libuca_utf8_stream_size_from_utf16";
	size_t utf16_string_iterator                 = 0;
	ssize_t utf8_stream_size                     = 0;
	libuca_unicode_character_t unicode_character = 0;

	if( utf16_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	utf8_stream_size = 3;

	while( utf16_string_iterator < utf16_string_size )
	{
		/* Convert the UTF-16 character bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator,
		     strict_mode ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-16.\n",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-32 character bytes are required
		 */
		utf8_stream_size += libuca_unicode_character_size_to_utf32(
		                      unicode_character,
		                      strict_mode );
	}
	return( utf8_stream_size );
}

/* Copies an UTF-8 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuca_utf8_stream_copy_from_utf16(
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     libuca_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     uint8_t strict_mode )
{
	static char *function                        = "libuca_utf8_stream_copy_from_utf16";
	size_t utf16_string_iterator                 = 0;
	size_t utf8_stream_iterator                  = 0;
	libuca_unicode_character_t unicode_character = 0;

	if( utf8_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream.\n",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( libuca_utf8_stream_copy_byte_order_mark(
	     utf8_stream,
	     utf8_stream_size,
	     &utf8_stream_iterator ) != 1 )
	{
		notify_warning_printf( "%s: unable to copy UTF-8 byte order mark.\n",
		 function );

		return( -1 );
	}
	while( utf16_string_iterator < utf16_string_size )
	{
		/* Convert the UTF-16 string bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf16(
		     &unicode_character,
		     utf16_string,
		     utf16_string_size,
		     &utf16_string_iterator,
		     strict_mode ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-16 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-8 stream bytes
		 */
		if( libuca_unicode_character_copy_to_utf8(
		     unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_iterator,
		     strict_mode ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to UTF-8 stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a UTF-8 stream from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
ssize_t libuca_utf8_stream_size_from_utf32(
         libuca_utf32_character_t *utf32_string,
         size_t utf32_string_size,
         uint8_t strict_mode )
{
	static char *function                        = "libuca_utf8_stream_size_from_utf32";
	size_t utf32_string_iterator                 = 0;
	ssize_t utf8_stream_size                     = 0;
	libuca_unicode_character_t unicode_character = 0;

	if( utf32_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	utf8_stream_size = 3;

	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
		     strict_mode ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-32.\n",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-32 character bytes are required
		 */
		utf8_stream_size += libuca_unicode_character_size_to_utf32(
		                      unicode_character,
		                      strict_mode );
	}
	return( utf8_stream_size );
}

/* Copies an UTF-8 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuca_utf8_stream_copy_from_utf32(
     uint8_t *utf8_stream,
     size_t utf8_stream_size,
     libuca_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     uint8_t strict_mode )
{
	static char *function                        = "libuca_utf8_stream_copy_from_utf32";
	size_t utf32_string_iterator                 = 0;
	size_t utf8_stream_iterator                  = 0;
	libuca_unicode_character_t unicode_character = 0;

	if( utf8_stream == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream.\n",
		 function );

		return( -1 );
	}
	if( utf8_stream_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-8 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		notify_warning_printf( "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuca_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
		     strict_mode ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character from UTF-32.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-8 character bytes
		 */
		if( libuca_unicode_character_copy_to_utf8(
		     unicode_character,
		     utf8_stream,
		     utf8_stream_size,
		     &utf8_stream_iterator,
		     strict_mode ) != 1 )
		{
			notify_warning_printf( "%s: unable to copy Unicode character to UTF-8 stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}
