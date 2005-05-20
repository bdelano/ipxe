#include "registers.h"
#include "main.h"
#include "hooks.h"

/*
 * This file provides the basic entry points from assembly code.  See
 * README.i386 for a description of the entry code path.
 *
 */

/*
 * arch_main() : call main() and then exit via whatever exit mechanism
 * the prefix requested.
 *
 */
void arch_main ( struct i386_all_regs *ix86 ) {
	void (*exit_path) ( struct i386_all_regs *ix86 );

	/* Determine exit path requested by prefix */
	exit_path = ( typeof ( exit_path ) ) ix86->regs.eax;

	/* Call to main() */
	ix86->regs.eax = main();

	if ( exit_path ) {
		/* Prefix requested that we use a particular function
		 * as the exit path, so we call this function, which
		 * must not return.
		 */
		exit_path ( ix86 );
	}
}
