/*
 * Date and time functions
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
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
#include <memory.h>
#include <types.h>

#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "date_time.h"
#include "notify.h"

#if !defined( HAVE_CTIME_R )

/* Sets ctime in the string
 * The string must be at least 32 characters of size
 * Returns the pointer to the string if successful or NULL on error
 */
char *date_time_ctime(
       const time_t *timestamp,
       char *string,
       size_t size )
{
	char *ctime_string    = NULL;
	static char *function = "date_time_ctime";

	if( timestamp == NULL )
	{
		notify_warning_printf( "%s: invalid timestamp.\n",
		 function );

		return( NULL );
	}
	if( string == NULL )
	{
		notify_warning_printf( "%s: invalid string.\n",
		 function );

		return( NULL );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		notify_warning_printf( "%s: invalid size.\n",
		 function );

		return( NULL );
	}
	if( size < 32 )
	{
		notify_warning_printf( "%s: string too small.\n",
		 function );

		return( NULL );
	}
	ctime_string = ctime(
	                timestamp );

	if( ctime_string == NULL )
	{
		notify_warning_printf( "%s: unable to create ctime string.\n",
		 function );

		return( NULL );
	}
	if( strncpy(
             string,
             ctime_string,
             strlen(
	      ctime_string ) ) == NULL )
	{
		notify_warning_printf( "%s: unable to set time string.\n",
		 function );

		return( NULL );
	}
	return( string );
}
#endif

#if defined( date_time_gmtime_r ) || defined( HAVE_GMTIME )
/* Returns a structured representation of a time using UTC (GMT), or NULL on error
 */
struct tm *date_time_gmtime(
            const time_t *timestamp )
{
#if !defined( date_time_gmtime_r ) && defined( HAVE_GMTIME )
	struct tm *static_time_elements = NULL;
#endif
	struct tm *time_elements        = NULL;
	static char *function           = "date_time_gmtime";

	if( timestamp == NULL )
	{
		notify_warning_printf( "%s: invalid time stamp.\n",
		 function );

		return( NULL );
	}
	time_elements = (struct tm *) memory_allocate(
	                               sizeof( struct tm ) );

	if( time_elements == NULL )
	{
		notify_warning_printf( "%s: unable to create time elements.\n",
		 function );

		return( NULL );
	}
#if defined( date_time_gmtime_r )
#if defined( WINAPI )
	if( date_time_gmtime_r(
	     timestamp,
	     time_elements ) != 0 )
#else
	if( date_time_gmtime_r(
	     timestamp,
	     time_elements ) == NULL )
#endif
	{
		notify_warning_printf( "%s: unable to set time elements.\n",
		 function );

		memory_free(
		 time_elements );

		return( NULL );
	}
#elif defined( HAVE_GMTIME )
	static_time_elements = gmtime(
	                        timestamp );

	if( static_time_elements == NULL )
	{
		notify_warning_printf( "%s: unable to create static time elements.\n",
		 function );

		memory_free(
		 time_elements );

		return( NULL );
	}
	if( memory_copy(
	     time_elements,
	     static_time_elements,
	     sizeof( struct tm ) ) == NULL )
	{
		notify_warning_printf( "%s: unable to set time elements.\n",
		 function );

		memory_free(
		 time_elements );

		return( NULL );
	}
#endif
	return( time_elements );
}
#endif

