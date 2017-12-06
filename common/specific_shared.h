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

//inherits what is defined in: ipcfifo.h
#ifndef __specific_shared_h__
#define __specific_shared_h__

#include "dsregs.h"
#include "dsregs_asm.h"
#include "ipcfifo.h"
#include "dswnifi.h"
#include "mem_handler_shared.h"

//aligned struct, shared code works just fine from here
struct sAlignedIPCProy	//sAlignedIPC as in ipcfifo.h but project specific implementation
{
	uint32 frameCounter7;	//VBLANK counter7
	uint32 frameCounter9;	//VBLANK counter9
};

//---------------------------------------------------------------------------------
typedef struct sSpecificIPC {
//---------------------------------------------------------------------------------
	//the unaligned access here kills code. Must be word aligned, defined on ARM9 only
	uint32 stubSpecificIPC;
} tSpecificIPC __attribute__ ((aligned (4)));

//project specific IPC. tMyIPC is used by TGDS so don't overlap
#define SpecificIPCUnalign ((volatile tSpecificIPC*)(getUserIPCAddress()))
#define SpecificIPCAlign ((volatile struct sAlignedIPCProy*)(getUserIPCAddress()+(sizeof(tSpecificIPC))))

#endif

#ifdef __cplusplus
extern "C" {
#endif

//NOT weak symbols : the implementation of these is project-defined (here)
extern void HandleFifoNotEmptyWeakRef(uint32 cmd1,uint32 cmd2,uint32 cmd3,uint32 cmd4);
extern void HandleFifoEmptyWeakRef(uint32 cmd1,uint32 cmd2,uint32 cmd3,uint32 cmd4);


#ifdef __cplusplus
}
#endif