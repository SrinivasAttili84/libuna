/*
 * Signal handling functions for the ucatools
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
#include <notify.h>

#include "ucasignal.h"

#if defined( HAVE_SIGNAL_H )

#if defined( HAVE_SYS_TYPES_H )
#include <sys/types.h>
#endif

#include <signal.h>

/* Attaches a signal handler for SIGINT
 * Returns 1 if successful or -1 on error
 */
int ucasignal_attach(
     void (*signal_handler)( ucasignal_t ) )
{
	static char *function = "ucasignal_attach";

	if( signal_handler == NULL )
	{
		notify_warning_printf( "%s: invalid signal handler.\n",
		 function );

		return( -1 );
	}
	if( signal(
	     SIGINT,
	     signal_handler ) == SIG_ERR )
	{
		notify_warning_printf( "%s: unable to attach signal handler.\n",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Detaches a signal handler for SIGINT
 * Returns 1 if successful or -1 on error
 */
int ucasignal_detach(
     void )
{
	static char *function = "ucasignal_detach";

	if( signal(
	     SIGINT,
	     SIG_DFL ) == SIG_ERR )
	{
		notify_warning_printf( "%s: unable to detach signal handler.\n",
		 function );

		return( -1 );
	}
	return( 1 );
}

#elif defined(HAVE_WINDOWS_API)

#include <windows.h>
#include <winnt.h>
#include <crtdbg.h>

void (*ucasignal_signal_handler)( ucasignal_t ) = NULL;

/* Signal handler for Ctrl+C or Ctrl+Break signals
 */
BOOL WINAPI ucasignal_handler(
             unsigned long signal )
{
	static char *function = "ucasignal_handler";

	switch( signal )
	{
		/* use Ctrl+C or Ctrl+Break to simulate SERVICE_CONTROL_STOP in debug mode
		 */
		case CTRL_BREAK_EVENT:
		case CTRL_C_EVENT:
			if( ucasignal_signal_handler != NULL )
			{
				ucasignal_signal_handler(
				 signal );
			}
			return( TRUE );

		default:
			break;
	}
	return( FALSE );
}

/* Initialize memory usage and leakage debugging
 */
void ucasignal_initialize_memory_debug(
      void )
{
	int flag = 0;

	/* Get the current state of the flag and store it in a temporary variable
	 */
	flag = _CrtSetDbgFlag(
	         _CRTDBG_REPORT_FLAG );

	/* Turn on client block identifiers and automatic leak detection
	 */
	flag |= ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	/* Set the new state for the flag
	 */
	_CrtSetDbgFlag(
	 flag );
}

/* Attaches a signal handler for Ctrl+C or Ctrl+Break signals
 * Returns 1 if successful or -1 on error
 */
int ucasignal_attach(
     void (*signal_handler)( ucasignal_t ) )
{
	static char *function = "ucasignal_attach";

	if( signal_handler == NULL )
	{
		notify_warning_printf( "%s: invalid signal handler.\n",
		 function );

		return( -1 );
	}
	ucasignal_signal_handler = signal_handler;

	if( SetConsoleCtrlHandler(
	     ucasignal_handler,
	     TRUE ) == 0 )
	{
		notify_warning_printf( "%s: unable to attach signal handler.\n",
		 function );

		return( -1 );
	}
	if( SetConsoleCtrlHandler(
	     NULL,
	     FALSE ) == 0 )
	{
		notify_warning_printf( "%s: unable to attach break signal.\n",
		 function );

		return( -1 );
	}
	ucasignal_initialize_memory_debug();

	SetErrorMode(
	 SEM_FAILCRITICALERRORS );

#if defined( LOCALE_SUPPORT )
	/* Allow subsequent threads to have their own locale.
	 * The current application is single threaded so this
	 * call has no practical effect here.
	 */
	_configthreadlocale(
	  _ENABLE_PER_THREAD_LOCALE );

	/* Set the current thread locale to the user default
	 * ANSI code page.
	 */
	setlocale(
	 LC_ALL,
	 "" );

	/* Set the the code page used by multibyte functions
	 * to use the same code page as the previous call to setlocale.
	 */
	_setmbcp(
	  _MB_CP_LOCALE );
#endif

	return( 1 );
}

/* Detaches a signal handler for Ctrl+C or Ctrl+Break signals
 * Returns 1 if successful or -1 on error
 */
int ucasignal_detach(
     void )
{
	static char *function = "ucasignal_detach";

	if( SetConsoleCtrlHandler(
	     ucasignal_handler,
	     FALSE ) == 0 )
	{
		notify_warning_printf( "%s: unable to detach signal handler.\n",
		 function );

		return( -1 );
	}
	ucasignal_signal_handler = NULL;

	return( 1 );
}

#endif

