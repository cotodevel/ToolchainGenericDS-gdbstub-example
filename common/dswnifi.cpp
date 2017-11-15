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

//DSWNIFI Library revision: 1.2
#include "specific_shared.h"
#include "wifi_shared.h"
#include "clock.h"
#include "ipcfifo.h"

#ifdef ARM9
#include "dswnifi_lib.h"

#include "dswnifi.h"
#include "wifi_arm9.h"
#include "dswifi9.h"
#include "wifi_shared.h"
#include "toolchain_utils.h"
#include <netdb.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <socket.h>
#include <in.h>
#include <assert.h>

#include "dswnifi.h"
#include "dswnifi_lib.h"

#endif

#ifdef ARM9

//These methods are template you must override (as defined below), to have an easy DS - DS framework running.

//Example Sender Code
//extern struct frameBlock * HandleSendUserspace(uint32 * databuf_src, int bufsize);
//example: 
//if(!FrameSenderUser){
//				FrameSenderUser = HandleSendUserspace((uint8*)nfdata,sizeof(nfdata));
//}

//Example Receiver Code
__attribute__((section(".itcm")))
void HandleRecvUserspace(struct frameBlock * frameBlockRecv){
	//frameBlockRecv->framebuffer	//Pointer to received Frame
	//frameBlockRecv->frameSize		//Size of received Frame
	do_multi(frameBlockRecv);		
}

//Multiplayer key binding/buffer shared code. For DS-DS multiplayer.
__attribute__((section(".itcm")))
bool do_multi(struct frameBlock * frameBlockRecv)
{
	//frameBlockRecv->framebuffer	//Pointer to received Frame
	//frameBlockRecv->frameSize		//Size of received Frame
	
	switch(getMULTIMode()){
		//single player, has no access to shared buffers.
		case(dswifi_idlemode):{
			//DSWNIFIStatus:SinglePlayer
			return false;
		}
		break;
		
		//NIFI local
		case(dswifi_localnifimode):{	//detect nifi_stat here if nifi_stat = 0 for disconnect when nifi was issued
			clrscr();
			printf("DSWNIFIStatus:LocalNifi!");
			printf("%s",(char*)frameBlockRecv->framebuffer);
			printf("FrameSize:%d!",frameBlockRecv->frameSize);
			return true;
		}
		break;
		
		//UDP NIFI
		case(dswifi_udpnifimode):{	//detect nifi_stat here if nifi_stat = 0 for disconnect when nifi was issued
			clrscr();
			printf("DSWNIFIStatus:UDPNifi!");
			printf("%s",(char*)frameBlockRecv->framebuffer);
			printf("FrameSize:%d!",frameBlockRecv->frameSize);
			return true;
		}
		break;
		
	}
	
	
	return false;
}


#endif
