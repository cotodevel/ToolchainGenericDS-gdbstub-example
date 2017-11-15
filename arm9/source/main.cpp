/*

			Copyright (C) 2017  Coto
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
USA

*/

#include "socket.h"
#include "in.h"
#include <netdb.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "main.h"
#include "InterruptsARMCores_h.h"
#include "specific_shared.h"
#include "ff.h"
#include "mem_handler_shared.h"
#include "reent.h"
#include "sys/types.h"
#include "dsregs.h"
#include "dsregs_asm.h"
#include "typedefs.h"
#include "console.h"
#include "toolchain_utils.h"

#include "devoptab_devices.h"
#include "fsfat_layer.h"
#include "usrsettings.h"

#include "video.h"
#include "keypad.h"
#include "gui.h"
#include "dma.h"

#include "dswnifi_lib.h"

int main(int _argc, sint8 **_argv) {
	
	IRQInit();
	
	bool project_specific_console = false;	//set default console or custom console: default console
	GUI_init(project_specific_console);
	GUI_clear();
	
	sint32 fwlanguage = (sint32)getLanguage();
	
	int ret=FS_init();
	if (ret == 0)
	{
		printf("FS Init ok.");
	}
	else if(ret == -1)
	{
		printf("FS Init error.");
	}
	
	printf("TCP GDBStub example. ");
	printf("write down the IP to GDB debugger.");
	printf("It should connect. Happy Debugging!");
	
	//single player:
	switch_dswnifi_mode(dswifi_idlemode);
	//udp nifi:
	//switch_dswnifi_mode(dswifi_udpnifimode);	//UDP NIFI: Check readme
	//local nifi: 
	//switch_dswnifi_mode(dswifi_localnifimode);	//LOCAL NIFI:
	
	//GDB Start must run after setting proper switch_dswnifi_mode(); mode
	if(gdbNdsStart() != true){
		printf("phailed connecting. Re-do your WIFI settings.");
		while(1==1){
			IRQVBlankWait();
		}
	}
	
	while (1)
	{
		if ((keysPressed() & KEY_A)){
			clrscr();
		}
		
		if ((keysPressed() & KEY_B)){
			printf("test!:%d",rand());
		}
		
		//GDB Stub Process must run here
		remoteStubMain();
		
		IRQVBlankWait();
	}

	return 0;
}