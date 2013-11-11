/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2006 Rexx Language Association. All rights reserved.    */
/*                                                                            */
/* This program and the accompanying materials are made available under       */
/* the terms of the Common Public License v1.0 which accompanies this         */
/* distribution. A copy is also available at the following address:           */
/* http://www.oorexx.org/license.html                          */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or                 */
/* without modification, are permitted provided that the following            */
/* conditions are met:                                                        */
/*                                                                            */
/* Redistributions of source code must retain the above copyright             */
/* notice, this list of conditions and the following disclaimer.              */
/* Redistributions in binary form must reproduce the above copyright          */
/* notice, this list of conditions and the following disclaimer in            */
/* the documentation and/or other materials provided with the distribution.   */
/*                                                                            */
/* Neither the name of Rexx Language Association nor the names                */
/* of its contributors may be used to endorse or promote products             */
/* derived from this software without specific prior written permission.      */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          */
/* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,      */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,        */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY     */
/* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING    */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS         */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*  wininit.c - dllentrypoint for oryxk.dll                                   */
/*                                                                            */
/******************************************************************************/
#include <stdio.h>                          /* Get printf, FILE type, etc.    */
#include <string.h>                         /* Get strcpy, strcat, etc.       */
#include <stdlib.h>                         /* Get system, max_path etc...    */
#define INCL_REXXSAA
#include "rexx.h"
#include "RexxCore.h"
#include "RexxAPIManager.h"
#include "APIServiceMessages.h"
#include "RexxAPIService.h"

/* definition of RexxinitExports */

CRITICAL_SECTION waitProtect = { 0 } ;

#ifdef JAPANESE
int sharedOpen = 0;
#endif

HINSTANCE horyxkDll;
HANDLE apiProtect;
/*
 */
/********************************************************************/
/*                                                                  */
/* Function name:      DllMain                                      */
/*                                                                  */
/* Description:        EntryPoint for REXX.DLL                      */
/*                                                                  */
/* Function:           Called by O/S whenever a process attaches    */
/*                     or detaches from the DLL.                    */
/*                     This entry point is used to initialize the   */
/*                     memory manager, and check to make sure       */
/*                     it is functioning.                           */
/*                                                                  */
/* Inputs:             Defined by DllEntryPoint function of Windows */
/*                                                                  */
/* Outputs:            TRUE if successful, FALSE if failure.        */
/*                                                                  */
/* Notes:                                                           */
/*                                                                  */
/*                                                                  */
/********************************************************************/
BOOL WINAPI DllMain(
  HINSTANCE hinstDll,
  DWORD fdwReason,
  LPVOID lpvReserved)
{
  BOOL  fSuccess = true;
  ULONG dwSize = sizeof(ULONG);
  char  szMessage[256] = "Open Object Rexx: Not cleanly installed!";

   if (fdwReason == DLL_PROCESS_ATTACH) {
//      RxAPIStartUp();
     InitializeCriticalSection(&waitProtect);  // another critical section is needed...
/* create critical section at DLL load-time (more secure) */
#ifdef THREADS
     SysThreadInit();
#else
     OryxThreadInit();
#endif
     if (fSuccess) {
       RxInterProcessInit(TRUE);
       horyxkDll = hinstDll;            /* keep handle around */
       MTXNCR(apiProtect, "!REXX_API_PROTECT_MTX.0");
     } else
       MessageBox(NULL, szMessage, "Startup Error!", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
   } else if (fdwReason == DLL_PROCESS_DETACH)
   {
      /* Clean up semaphores before terminating process so that we */
      /* don't run out of system handles.                          */
      MTXCL(memoryObject.flattenMutex);
      MTXCL(memoryObject.unflattenMutex);
      MTXCL(memoryObject.envelopeMutex);
      DeleteCriticalSection(&waitProtect);
      RexxDeregisterFunction(NULL); // Send PROCESS_GONE to RXAPI
      MTXCL(apiProtect);
   }

   return(fSuccess);
}
