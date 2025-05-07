/*
 * WASM IO support code
 *
 * Based on the Return to Castle Wolfenstein GPL Source Code
 * Copyright (C) 1999–2010 id Software LLC, a ZeniMax Media company.
 *
 * Additional modifications Copyright (C) 2025 Gregory Maynard-Hoare
 *
 * For license details, see the COPYING.txt file included with this project.
 */

#include "wasm_io.h"

#include <emscripten.h>

void wasm_init_fs(void)
{
	// Fetch from IDBFS in the background
	EM_ASM(
		Module.restore_busy = 1;
		FS.mkdir("/wwasm");

		// We must autoPersist data because QVM programs can handle saves
		FS.mount(IDBFS, {autoPersist: true}, "/wwasm");

		console.info("Loading data...");
		FS.syncfs(true, function(err) {
			if (err)
				console.warn("Failed to load data:", err);
			else
				console.info("Data loaded.");

			Module.restore_busy = 0;
		});
	);
}

int wasm_restore_busy(void)
{
	// Verify whether IDBFS restore is complete
	return EM_ASM_INT(
		return Module.restore_busy;
	);
}

void wasm_hide_console(void)
{
	// Hide the game console and show the canvas
	EM_ASM(
		if (typeof Module.hideConsole === 'function')
			Module.hideConsole();
	);
}

void wasm_show_console(void)
{
	// Show the game console and hide the canvas
	EM_ASM(
		if (typeof Module.showConsole === 'function')
			Module.showConsole();
	);
}
