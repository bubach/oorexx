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
/* REXX AIX/LINUX Support                                         lrxutil.c   */
/*                                                                            */
/* AIX  system utility functions                                              */
/*                                                                            */
/******************************************************************************/
/**********************************************************************
*   LRXUTIL.C                                                         *
*                                                                     *
*   This program extends the REXX language by providing many          *
*   REXX external functions.                                          *
*   These functions are:                                              *
*       SysCls              -- Clear the screen in an OS/2 fullscreen *
*                              or windowed command prompt session.    *
*       SysCurPos           -- Set and/or Query the cursor position   *
*                              in an OS/2 fullscreen or windowed      *
*                              command prompt session.                *
*       SysCurState         -- Make the cursor visible or invisible   *
*                              in an OS/2 fullscreen or windowed      *
*                              command prompt session.                *
*       SysDriveInfo        -- Returns information about a specific   *
*                              drive.                                 *
*       SysDriveMap         -- Returns a list of the drives on the    *
*                              machine                                *
*       SysDropFuncs        -- Makes all functions in this package    *
*                              unknown to REXX.                       *
*       SysFileDelete       -- Deletes a file                         *
*       SysFileSearch       -- Searches for a file matching a given   *
*                              filespec.                              *
*       SysFileTree         -- Searches for files matching a given    *
*                              filespec, including files in           *
*                              subdirectories.                        *
*       SysGetKey           -- Returns one by of data indicating the  *
*                              key which was pressed,                 *
*                              in an OS/2 fullscreen or windowed      *
*                              command prompt session.                *
*       SysGetMessage       -- Retrieves a message text from an OS/2  *
*                              message file, substituting values      *
*                              provided.                              *
*       SysIni              -- Reads and/or updates entries in .INI   *
*                              files.                                 *
*       SysLoadFuncs        -- Makes all functions in this package    *
*                              known to REXX so REXX programs may     *
*                              call them.                             *
*       SysMkDir            -- Creates a directory                    *
*       SysVersion          -- Returns the AIX  Version number        *
*       SysLinVer           -- Returns the OS/2 Version number        *
*       SysRmDir            -- Removes a directory                    *
*       SysSearchPath       -- Searches throught a specified path     *
*                              for a file.                            *
*       SysSleep            -- Suspends execution for a number of     *
*                              seconds.                               *
*       SysTempFilename     -- Creates a unique filename              *
*       SysTextScreenRead   -- Reads characters from the screen,      *
*                              in an OS/2 fullscreen or windowed      *
*                              command prompt session.                *
*       SysTextScreenSize   -- Returns the size of the window in      *
*                              rows and columns,                      *
*                              in an OS/2 fullscreen or windowed      *
*                              command prompt session.                *
*EX     SysGetEA            -- Reads an extended attribute            *
*                              for a file.                            *
*EX     SysPutEA            -- Writes an extended attribute           *
*                              for a file.                            *
*EX     SysWaitNamedPipe    -- Wait on a named pipe.                  *
*EX     SysSetIcon          -- Set a file icon                        *
*EX     SysRegisterObjectClass -- Register a new object class         *
*EX     SysDeregisterObjectClass -- Remove class registration         *
*EX     SysQueryClassList   -- Get list of registered classes         *
*EX     SysCreateObject     -- Create an object instance              *
*EX     SysDestroyObject    -- Delete an object instance              *
*EX     SysSetObjectData    -- Change object settings data            *
*EX     SysElapsedTime      -- Return the OS/2 elapsed time count     *
*EX     SysBootDrive        -- Return the OS/2 boot drive             *
*EX     SysQueryEAList      -- Return list of file EA names           *
*EX     SysWildCard         -- Perform file wild card editting        *
*EX     SysFileSystemType   -- Return drive file system type          *
*EX     SysAddFileHandle    -- Add file handles to a process          *
*EX     SysSetFileHandle    -- Set file handles for a process         *
*       SysCreateMutexSem   -- Create a Mutex semaphore               *
*       SysOpenMutexSem     -- Open a Mutex semaphore                 *
*       SysCloseMutexSem    -- Close a Mutex semaphore                *
*       SysRequestMutexSem  -- Request a Mutex semaphore              *
*       SysReleaseMutexSem  -- Release a Mutex semaphore              *
*       SysCreateEventSem   -- Create an Event semaphore              *
*       SysOpenEventSem     -- Open an Event semaphore                *
*       SysCloseEventSem    -- Close an Event semaphore               *
*       SysPostEventSem     -- Post an Event semaphore                *
*       SysResetEventSem    -- Reset an Event semaphore               *
*       SysWaitEventSem     -- Wait on an Event semaphore             *
*EX     SysProcessType      -- Return type of process                 *
*EX     SysSetPriority      -- Set current thread priority            *
*EX     SysGetCollate       -- Get country/codepage collating sequence*
*EX     SysNationalLanguageCompare -- NLS strict compare              *
*EX     SysMapCase          -- NLS uppercasing                        *
*EX     SysSetProcessCodePage -- Set current code page                *
*EX     SysQueryProcessCodePage -- Get current code page              *
*       SysAddRexxMacro     -- Load program into macro space          *
*       SysDropRexxMacro    -- Drop program from macro space          *
*       SysReorderRexxMacro -- Reorder program in macro space         *
*       SysQueryRexxMacro   -- Query ordering of macro space program  *
*       SysClearRexxMacroSpace -- Remove all programs from macro space*
*       SysLoadRexxMacroSpace  -- Load a Rexx macro space             *
*       SysSaveRexxMacroSpace  -- Save a Rexx macro space             *
*EX     SysShutDownSystem   -- Shutdown the system                    *
*EX     SysSwitchSession    -- Switch to a named session              *
*EX     SysLoadLibrary      -- Load a function package                *
*EX     SysDropLibrary      -- Drop a function package                *
*  EX   SysPi               -- Return Pi to given precision           *
*  EX   SysSqrt             -- Calculate a square root                *
*  EX   SysExp              -- Calculate an exponent                  *
*  EX   SysLog              -- Return natural log of a number         *
*  EX   SysLog10            -- Return log base 10 of a number         *
*  EX   SysSinh             -- Hyperbolic sine function               *
*  EX   SysCosh             -- Hyperbolic cosine function             *
*  EX   SysTanh             -- Hyperbolic tangent function            *
*  EX   SysPower            -- raise number to non-integer power      *
*  EX   SysSin              -- Sine function                          *
*  EX   SysCos              -- Cosine function                        *
*  EX   SysTan              -- Tangent function                       *
*  EX   SysCotan            -- Cotangent function                     *
*  EX   SysArcSin           -- ArcSine function                       *
*  EX   SysArcCos           -- ArcCosine function                     *
*  EX   SysArcTan           -- ArcTangent function                    *
*EX     SysSaveObject       -- Save an object either Async or Sync    *
*EX     SysOpenObject       -- Open a view of an object               *
*EX     SysMoveObject       -- Move an object from the existing folder*
*                              to the destination folder              *
*EX     SysCopyObject       -- Copy an object from the existing folder*
*                              to the destination folder              *
*EX     SysCreateShadow     -- Create a shadow of an object           *
*EX     SysWaitForShell     -- Wait for WPS initialization            *
*                              (Merlin only).                         *
*EX     SysQuerySwitchList  -- query the entries of the switch list   *
*                              (for SysSwitchSession)                 *
*       SysDumpVariables    -- Dump current variables to a file       *
*       SysSetFileDateTime  -- Set the last modified date of a file   *
*       SysGetFileDateTime  -- Get the last modified date of a file   *
*       SysStemSort         -- sort a stem array                      *
*       SysStemDelete       -- delete items in a stem array           *
*       SysStemInsert       -- insert items into a stem array         *
*       SysStemCopy         -- copy items from one stem array to other*
*       SysGetErrortext     -- Retrieve textual desc. of error number *
*       SysQueryProcess     -- Get information on current proc/thread *
*       SysUtilVersion      -- query version of REXXUTIL.DLL          *
*                                                                     *
*       SysAddFuncPkg       -- CREXX for AIX function support         *
*       SysAddCmdPkg        -- CREXX for AIX function support         *
*       SysDropFuncPkg      -- CREXX for AIX function support         *
*       SysDropCmdPkg       -- CREXX for AIX function support         *
*       SysGetpid           -- CREXX for AIX function support         *
*       SysFork             -- CREXX for AIX function support         *
*       SysWait             -- CREXX for AIX function support         *
*       SysCreatePipe       -- CREXX for AIX function support         *
*                                                                     *
*       SysIsFile           -- does file exist?                       *
*       SysIsFileDirectory  -- is file a subdirectory?                *
*       SysIsFileLink       -- is file a link?                        *
*                                                                     *
**********************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/* Include files */

#define  INCL_WPCLASS
#define  INCL_WINWORKPLACE
#define  INCL_WINSHELLDATA
#define  INCL_WINSWITCHLIST
#define  INCL_WINPROGRAMLIST
#define  INCL_WINPOINTERS
#define  INCL_SHLERRORS
#define  INCL_DOS
#define  INCL_DOSFILEMGR
#define  INCL_DOSMEMMGR
#define  INCL_DOSFILEMGR
#define  INCL_DOSNMPIPES
#define  INCL_DOSNLS
#define  INCL_ERRORS
#define  INCL_REXXSAA
#define  INCL_RXMACRO
#define  INCL_KBD
#define  INCL_VIO

#include "PlatformDefinitions.h"
#if defined( HAVE_LOCALE_H )
# include <locale.h>
#endif

#include SYSREXXSAA
#include "RexxAPIManager.h"
#include "APIUtilities.h"

#if defined( HAVE_SYS_WAIT_H )
# include <sys/wait.h>
#endif
#include "SystemSemaphores.h"

#include <sys/ipc.h>
#include <memory.h>

#if defined( HAVE_MALLOC_H )
# include <malloc.h>
#endif

#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <limits.h>
#include <sys/stat.h>                  /* mkdir() function           */
#include <errno.h>                     /* get the errno variable     */
#include <stddef.h>
#include <sys/types.h>
#include <sys/ipc.h>

#if defined( HAVE_SYS_SEM_H )
# include <sys/sem.h>
#endif

#include <dirent.h>                    /* directory functions        */
#include <sys/time.h>                  /* needed for the select func */

#include <time.h>                 /* needed for the select func          */

#if defined( HAVE_SYS_SELECT_H )
# include <sys/select.h>           /* needed for the select func          */
#endif

#if defined( HAVE_SYS_LDR_H )
# include <sys/ldr.h>              /* needed for the load   func          */
#endif

#if defined( HAVE_STRINGS_H )
# include <strings.h>
#endif

#include <utime.h>                /* moved, used by AIX & Linux          */

#if defined( HAVE_SYS_UTSNAME_H )
# include <sys/utsname.h>               /* get the uname() function   */
#endif

#include <signal.h>

#if defined( HAVE_SYS_RESOURCE_H )
# include <sys/resource.h>              /* get the getpriority() func */
#endif

#if defined( HAVE_FEATURES_H )
# include <features.h>                 /* catopen()                  */
#endif

#if defined( HAVE_NL_TYPES_H )
# include <nl_types.h>                  /* catopen()                  */
#endif

#include <termios.h>                   /* needed for SysGetKey       */
#include "ThreadSupport.hpp"           /* for the SysGetKey semaphore*/
#include <fnmatch.h>                   /* fnmatch()                  */
#include "RexxLibrary.h"

#if !defined( HAVE_UNION_SEMUN )
union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};
#endif

extern REXXAPIDATA  *apidata;          /* Global state data          */
extern INT opencnt[][2];               /* open count array for sems  */
//extern BOOL WAITANDRESET;              /* for creating sems  */
extern PCHAR resolve_tilde(PCHAR);
extern BOOL rexxutil_call;             /* internal call flag         */
extern RexxMutex rexxutil_call_sem;
/*extern INT rxstrnicmp(PSZ, PSZ, INT);  */

#define INVALID_ROUTINE 40
#define  MAX_DIGITS     9
#define  NO_UTIL_ERROR    "0"          /* No error whatsoever        */
#define  VALID_ROUTINE    0            /* Successful completion      */
//#define  MAX_LINE_LEN   2048         /* max line length */
#define  MAX_LINE_LEN   4096           /* max line length */
#define  MAX_READ       0x10000        /* full segment of buffer     */
#define  CH_EOF         0x1A           /* end of file marker         */
#define  CH_CR          '\r'           /* carriage return character  */
#define  CH_NL          '\n'           /* new line character         */
#define  MAX            256            /* temporary buffer length    */
#define  IBUF_LEN       4096           /* Input buffer length        */
#define CURRENT_DIR_FIRST 0            /* search flag 'C'            */
#define ENVIRONMENT_ONLY  1            /* search flag 'N'            */
#define OFFSET          1000           /* needed to prevent collision*/
                                       /* with the return codes      */
#define MAXUSECOUNT     65535          /* max semaphore usecount     */


/*********************************************************************/
/*  Various definitions used by the math functions                   */
/*********************************************************************/
#define SINE        0                  /* trig function defines...   */
#define COSINE      3                  /* the ordering is important, */
#define TANGENT     1                  /* as these get transformed   */
#define COTANGENT   2                  /* depending on the angle     */
#define MAXTRIG     3                  /* value                      */
#define ARCSINE     0                  /* defines for arc trig       */
#define ARCCOSINE   1                  /* functions.  Ordering is    */
#define ARCTANGENT  2                  /* not as important here      */


#define pi  3.14159265358979323846l    /* pi value                   */

#define DEGREES    'D'                 /* degrees option             */
#define RADIANS    'R'                 /* radians option             */
#define GRADES     'G'                 /* grades option              */

#define DEFAULT_PRECISION  9           /* default precision to use   */
#define MAX_PRECISION     16           /* maximum available precision*/



/*********************************************************************/
/* Numeric Error Return Strings                                      */
/*********************************************************************/

#define  NO_UTIL_ERROR    "0"          /* No error whatsoever        */
#define  ERROR_NOMEM      "2"          /* Insufficient memory        */
#define  ERROR_FILEOPEN   "3"          /* Error opening text file    */

/*********************************************************************/
/* Alpha Numeric Return Strings                                      */
/*********************************************************************/

#define  ERROR_RETSTR   "ERROR:"

/*********************************************************************/
/* Numeric Return calls                                              */
/*********************************************************************/

#define  INVALID_ROUTINE 40            /* Raise Rexx error           */
#define  VALID_ROUTINE    0            /* Successful completion      */

/*********************************************************************/
/* Defines used by SysStemSort                                       */
/*********************************************************************/
#define SORT_CASESENSITIVE 0
#define SORT_CASEIGNORE    1


#define SORT_ASCENDING 0
#define SORT_DECENDING 1

#define SORT_NUMERIC       3

#define SORT_DEF_AVG_SIZE  20

/*********************************************************************/
/* Some useful macros                                                */
/*********************************************************************/

#define BUILDRXSTRING(t, s) { \
  strcpy((t)->strptr,(s));\
  (t)->strlength = strlen((s)); \
}


#if defined(AIX) || defined(LINUX)
#define RETVAL(retc) { \
  _ltoa((long)retc, retstr->strptr,10); \
  retstr->strlength = strlen(retstr->strptr); \
  return VALID_ROUTINE; \
}
#endif


/*********************************************************************/
/* Defines uses by SysTree                                           */
/*********************************************************************/

#define  RECURSE        0x0002
#define  DO_DIRS        0x0004
#define  DO_FILES       0x0008
#define  NAME_ONLY      0x0010
#define  EDITABLE_TIME  0x0020
#define  LONG_TIME      0x0040
#define  IGNORE         2              /* Ignore attributes entirely */


/******************************************************************************/
/* Defines used by SysGetKey                                                  */
/******************************************************************************/

#define stty(a,b)         (void)tcsetattr(a,TCSANOW,b) /* simple set attr.    */
#define gtty(a,b)         (void)tcgetattr(a,b)         /* simple get attr.    */
#define discard_input(a)  tcflush(a,TCIFLUSH)          /* simple flush        */
#define restore_tty(a)    stty(ttyfd,a)                /* new settings STDIN  */


/* semaphore to prevent mulitple SysGetKey calls                              */
static RexxMutex SysGetKeySemaphore;
/* original terminal settings                                                 */
struct termios in_orig;                /* original settings (important!!)     */

extern void SysInitialize(void);


/*********************************************************************/
/* RxTree Structure used by SysTree.                                 */
/*********************************************************************/

typedef struct RxTreeData {
    ULONG count;                       /* Number of lines processed  */
    SHVBLOCK shvb;                     /* Request block for RxVar    */
    ULONG stemlen;                     /* Length of stem             */
    ULONG vlen;                        /* Length of variable value   */
    CHAR TargetSpec[MAX+1];            /* Target filespec            */
    CHAR truefile[MAX+1];              /* expanded file name         */
    CHAR Temp[MAX+80];                 /* buffer for returned values */
    CHAR varname[MAX];                 /* Buffer for variable name   */
    ULONG nattrib;                     /* New attrib, diff for each  */
} RXTREEDATA;


/*********************************************************************/
/* RxTree Structure used by GetLine, OpenFile and CloseFile          */
/*********************************************************************/

typedef struct _GetFileData {
  PCHAR        buffer;                 /* file read buffer           */
  ULONG        size;                   /* file size                  */
  ULONG        data;                   /* data left in buffer        */
  ULONG        residual;               /* size left to read          */
  PCHAR        scan;                   /* current scan position      */
  FILE         *handle;                /* file handle                */
} GetFileData;

/*********************************************************************/
/* RxStemData                                                        */
/*   Structure which describes as generic                            */
/*   stem variable.                                                  */
/*********************************************************************/

typedef struct RxStemData {
    SHVBLOCK shvb;                     /* Request block for RxVar    */
    CHAR ibuf[IBUF_LEN];               /* Input buffer               */
    CHAR varname[MAX];                 /* Buffer for the variable    */
                                       /* name                       */
    CHAR stemname[MAX];                /* Buffer for the variable    */
                                       /* name                       */
    ULONG stemlen;                     /* Length of stem.            */
    ULONG vlen;                        /* Length of variable value   */
    ULONG j;                           /* Temp counter               */
    ULONG tlong;                       /* Temp counter               */
    ULONG count;                       /* Number of elements         */
                                       /* processed                  */
} RXSTEMDATA;

/*********************************************************************/
/* SORTMEM used by SysStemSort                                       */
/*********************************************************************/
typedef struct _SORT_MEM {
  ULONG                 ulSize;
  ULONG                 ulRemaining;
  ULONG                 ulItems;
  PCHAR                 pNextBlock;
  struct _SORT_MEM      *pNext;
  CHAR                  pData;
} SORTMEM, *PSORTMEM;

/*********************************************************************/
/* Sorting column delimiters for SysStemSort                         */
/*********************************************************************/
static   ULONG ulStartCol = 0;
static   ULONG ulCompLength = 0;

/*********************************************************************/
/* RxFncTable                                                        */
/*   Array of names of the REXXUTIL functions.                       */
/*   This list is used for registration and deregistration.          */
/*********************************************************************/

static PSZ  RxFncTable[] =
   {
//      "SysBootDrive",
//      "SysElapsedTime",
//      "SysQueryEAList",
//      "SysWildCard",
//      "SysFileSystemType",
//      "SysAddFileHandle",
//      "SysSetFileHandle",
      "SysCreateMutexSem",
      "SysOpenMutexSem",
      "SysCloseMutexSem",
      "SysRequestMutexSem",
      "SysReleaseMutexSem",
      "SysCreateEventSem",
      "SysOpenEventSem",
      "SysCloseEventSem",
      "SysResetEventSem",
      "SysPostEventSem",
      "SysWaitEventSem",
      "SysSetPriority",
//      "SysProcessType",
//      "SysGetCollate",
//      "SysNationalLanguageCompare",
//      "SysMapCase",
//      "SysSetProcessCodePage",
//      "SysQueryProcessCodePage",
      "SysAddRexxMacro",
      "SysDropRexxMacro",
      "SysReorderRexxMacro",
      "SysQueryRexxMacro",
      "SysClearRexxMacroSpace",
      "SysLoadRexxMacroSpace",
      "SysSaveRexxMacroSpace",
//      "SysShutDownSystem",
//      "SysSwitchSession",
//      "SysLoadLibrary",
//      "SysDropLibrary",
#if defined(AIX)
      "SysAddFuncPkg",
      "SysAddCmdPkg",
      "SysDropFuncPkg",
      "SysDropCmdPkg",
      "SysGetpid",
#endif
      "SysFork",
      "SysWait",
      "SysCreatePipe",
      "SysCls",
//      "SysCurPos",
//      "SysCurState",
//      "SysDriveInfo",
//      "SysDriveMap",
      "SysDropFuncs",
      "SysFileDelete",
      "SysFileSearch",
      "SysFileTree",
//      "SysGetEA",
      "SysGetKey",
      "SysGetMessage",
      "SysGetMessageX",
//      "SysIni",
      "SysLoadFuncs",
      "SysMkDir",
#ifdef LINUX
      "SysLinVer",
#endif
      "SysVersion",
      "SysRmDir",
      "SysSearchPath",
      "SysSleep",
      "SysTempFileName",
      "SysDumpVariables",
      "SysSetFileDateTime",
      "SysGetFileDateTime",
      "SysStemSort",
      "SysStemDelete",
      "SysStemInsert",
      "SysStemCopy",
      "SysQueryProcess",
      "SysGetErrortext",
      "SysUtilVersion",
      "SysIsFile",
      "SysIsFileDirectory",
      "SysIsFileLink",
//      "SysTextScreenRead",
//      "SysTextScreenSize",
//      "SysGetEA",
//      "SysPutEA",
//      "SysWaitNamedPipe",
//      "SysSetIcon",
//      "SysRegisterObjectClass",
//      "SysDeregisterObjectClass",
//      "SysCreateObject",
//      "SysQueryClassList",
//      "SysDestroyObject",
//      "SysSetObjectData",
//      "SysSaveObject",
//      "SysOpenObject",
//      "SysMoveObject",
//      "SysCopyObject",
//      "SysCreateShadow",
//      "SysWaitForShell",
//      "SysQuerySwitchList"
   };

#ifdef __cplusplus
extern "C" {
#endif

#if defined(AIX) || defined(LINUX)
LONG APIENTRY SysLoadFuncs(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr );                  /* Return RXSTRING            */

/********************************************************************
* Function:  string2ulong(string, number)                           *
*                                                                   *
* Purpose:   Validates and converts an ASCII-Z string from string   *
*            form to an unsigned long.  Returns FALSE if the number *
*            is not valid, TRUE if the number was successfully      *
*            converted.                                             *
*                                                                   *
* RC:        TRUE - Good number converted                           *
*            FALSE - Invalid number supplied.                       *
*********************************************************************/
BOOL string2ulong(
  PSZ    string,                       /* string to convert          */
  PULONG number)                       /* converted number           */
{
  ULONG    accumulator;                /* converted number           */
  INT      length;                     /* length of number           */

  length = strlen(string);             /* get length of string       */
  if (length == 0 ||                   /* if null string             */
      length > MAX_DIGITS + 1)         /* or too long                */
    return FALSE;                      /* not valid                  */

  accumulator = 0;                     /* start with zero            */

  while (length) {                     /* while more digits          */
    if (!isdigit(*string))             /* not a digit?               */
      return FALSE;                    /* tell caller                */
                                       /* add to accumulator         */
    accumulator = accumulator * 10 + (*string - '0');
    length--;                          /* reduce length              */
    string++;                          /* step pointer               */
  }
  *number = accumulator;               /* return the value           */
  return TRUE;                         /* good number                */
}

#endif

/*********************************************************************/
/****************  REXXUTIL Supporting Functions  ********************/
/****************  REXXUTIL Supporting Functions  ********************/
/****************  REXXUTIL Supporting Functions  ********************/
/*********************************************************************/

/********************************************************************
* Function:  ReadNextBuffer(filedata)                               *
*                                                                   *
* Purpose:   Reads the next buffer of data.                         *
*                                                                   *
* RC:        0       buffer was read                                *
*            1     - error occurred reading buffer                  *
*********************************************************************/
INT ReadNextBuffer(
   GetFileData  *filedata )            /* global file information    */
{
  ULONG     size;                      /* size to read               */
  PCHAR     endptr;                    /* end of file pointer        */
                                       /* get size of this read      */
  if(filedata->residual >= MAX_READ)
    size = MAX_READ;                   /* read as much as possible   */
  else
    size = filedata->residual;         /* take the rest              */
                                       /* read the file in           */
  filedata->data = fread(filedata->buffer, 1, size, filedata->handle);
  if(!filedata->data)                  /* problems ?                 */
    return (1);                        /* get out                    */
  if (filedata->data != size)          /* not get all of it?         */
    filedata->residual = 0;            /* no residual                */
  else                                 /* residual is remainder      */
    filedata->residual = filedata->residual - size;
                                       /* look for a EOF mark        */
  endptr = (PCHAR)memchr(filedata->buffer, CH_EOF, filedata->data);

  if (endptr) {                        /* found an EOF mark          */
                                       /* set new length             */
    filedata->data = (ULONG)(endptr - filedata->buffer);
    filedata->residual = 0;            /* no residual                */
  }
  filedata->scan = filedata->buffer;   /* set position to beginning  */
  return 0;
}

/***********************************************************************/
/* Function: strupr(string)                                            */
/* Purpose:  Uppercas the given string                                 */
/***********************************************************************/
void strupr(PCHAR string){

  for(;*string != '\0';string++){        /* while not at the end       */
    *string = toupper(*string);
  }
}

/********************************************************************
* Function:  OpenFile(file, filedata)                               *
*                                                                   *
* Purpose:   Prepares a file for reading.                           *
*                                                                   *
* RC:        0     - file was opened successfully                   *
*            1     - file open error occurred                       *
*********************************************************************/

INT OpenFile(
   PSZ          file,                  /* file name                  */
   GetFileData *filedata )             /* global file information    */
{
   struct stat finfo;                  /* file information           */
   PCHAR       endptr = NULL;          /* end of buffer pointer      */

                                       /* try to open the file       */
  if((filedata->handle = fopen(file,"r")) == NULL)
    return (1);                        /* return failure             */
                                       /* retrieve the file size     */
  if((stat(file,&finfo) == -1)||(!finfo.st_size)){
    fclose(filedata->handle);          /* close the file             */
    return (1);                        /* and quit                   */
  }
  if (finfo.st_size <= MAX_READ) {     /* less than a single buffer  */
                                       /* allocate buffer for file   */
    if((filedata->buffer = (PCHAR)malloc(finfo.st_size)) == NULL ){
      fclose(filedata->handle);        /* close the file             */
      return (1);                      /* and quit                   */
    }
    filedata->size = finfo.st_size;    /* save file size             */
    filedata->residual = 0;            /* no left over information   */
                                       /* read the file in           */
    filedata->data = fread(filedata->buffer, 1,
                                      finfo.st_size, filedata->handle);
    if(filedata->data != finfo.st_size){/*  problems ?               */
      free(filedata->buffer);          /* free the buffer            */
      fclose(filedata->handle);        /* close the file             */
      return (1);                      /* and quit                   */
    }                                  /* look for a EOF mark        */
    endptr = (PCHAR)memchr(filedata->buffer, CH_EOF, filedata->data);
    if (endptr)                        /* found an EOF mark          */
                                       /* set new length             */
      filedata->data = (ULONG)(endptr - filedata->buffer);
    filedata->scan = filedata->buffer; /* set position to beginning  */
  }
  else {                               /* need to read partial       */
                                       /* allocate buffer for read   */
    if((filedata->buffer = (PCHAR)malloc(MAX_READ)) == NULL ){
      fclose(filedata->handle);        /* close the file             */
      return (1);                      /* and quit                   */
    }
    filedata->size = finfo.st_size;    /* save file size             */
                                       /* and set remainder          */
    filedata->residual = filedata->size;
                                       /* read the file in           */
    if (ReadNextBuffer(filedata)) {
      free(filedata->buffer);          /* free the buffer            */
      fclose(filedata->handle);        /* close the file             */
      return 1;
    }
  }
  return 0;                            /* file is opened             */
}

/********************************************************************
* Function:  CloseFile(filedata)                                    *
*                                                                   *
* Purpose:   Close a file                                           *
*********************************************************************/
void CloseFile(
   GetFileData *filedata )             /* global file information    */
{
  fclose(filedata->handle);            /* close the file             */
  free(filedata->buffer);              /* release the file buffer    */
}

/*********************************************************************
* Function:  GetLine(line, size, filedata)                          *
*                                                                   *
* Purpose:   Reads a line of data using buffered reads.  At end of  *
*            file, zero is returned to indicate nothing left.       *
*                                                                   *
* RC:        TRUE -  line was read successfully                     *
*            FALSE - end of file was reached                        *
*********************************************************************/

INT GetLine(
   PSZ          line,                  /* returned line              */
   ULONG        size,                  /* size of line buffer        */
   GetFileData *filedata )             /* file handle                */
{
   PCHAR        scan;                  /* current scan pointer       */
   ULONG        length;                /* line length                */
   ULONG        copylength;            /* copied length              */


  if (!(filedata->data)) {             /* if out of current buffer   */
    if (filedata->residual) {          /* may be another buffer      */
      ReadNextBuffer(filedata);        /* try to read one            */
      if (!filedata->data)             /* nothing more?              */
        return 1;                      /* all done                   */
    }
    else
      return (1);                      /* return EOF condition       */
  }
                                       /* look for a line feed       */
  scan = (PCHAR)memchr(filedata->scan, CH_NL, filedata->data);
  if (scan) {                          /* found one                  */
                                       /* calculate the length       */
    length = (ULONG)(scan - filedata->scan);
    copylength = min(length, size);    /* get length to copy         */
                                       /* copy over the data         */
    memcpy(line, filedata->scan, copylength);
    line[copylength] = '\0';           /* make into ASCIIZ string    */

    /* we don't want the CR character in the result string*/
    if ( line[copylength - 1] == CH_CR ) {
      line[copylength - 1] = '\0';
    } /* endif */

    filedata->data -= length + 1;      /* reduce the length          */
    filedata->scan = scan + 1;         /* set new scan point         */

    if (!filedata->data) {             /* all used up                */
      if (filedata->residual)          /* more to read               */
        ReadNextBuffer(filedata);      /* read the next buffer       */

//      if (filedata->data &&            /* if more to read            */
//        *filedata->scan == CH_NL) {    /* may need to skip a char    */
//        filedata->scan++;              /* step past new line         */
//        filedata->data--;              /* reduce size by one         */
//      }
    }
                                       /* may need to skip a char    */
//    else if (*filedata->scan == CH_NL) {
//      filedata->scan++;                /* step past new line       */
//      filedata->data--;                /* reduce size by one       */
//    }
    return 0;                            /* this worked ok           */
  }
  else                                   /* ran off the end          */
  {
/* now we have scanned the whole buffer, but didn't find LF.         */
/* we have two situation that can appear:                            */
/* 1.) size > filedata->data ==> there is still room in the working  */
/*     buffer, we can see whether we have scanned the whole file     */
/*     --> ReadNextBuffer, or this was it, and we return             */
/* 2.) size < filedata->buffer ==> we have scanned to the end of the */
/*     buffer, more than what would fit into it, but still we        */
/*     haven't had a hit. So copy all elements into the buffer       */
/*     read the next buffer, GetLine to get the next LF              */
/*     and return what was put into buffer. Be ALWAYS AWARE that     */
/*     that buffer limits to 2047 bytes, and that we only return up  */
/*     to 2047 bytes of a line. The rest of the line is not returned */
/*     and not checked for search argument. Nevertheless, this       */
/*     garantees, that the line counter (argument 'N') corresponds   */
/*     with the input file                                           */

                                       /* get length to copy         */
    if (size > filedata->data)
    {
       copylength = filedata->data;    /* copy the rest into linebuffer */
                                       /* copy over the data         */
       memcpy(line, filedata->scan, copylength);
       line[copylength] = '\0';           /* make into ASCIIZ string    */

    /* we don't want the CR character in the result string*/
    /* we have not found LF, so why look for CR                      */
//     if ( line[copylength - 1] == CH_CR )
//     {
//       line[copylength - 1] = '\0';
//     } /* endif */

     /* all data should be read, filedata->data must be zero          */
       filedata->data -= copylength;
     /* scan should be at the end                                     */
       filedata->scan += copylength;    /* set new scan point         */

    /* if no more data to read in the file, return OK     */
//       if (!filedata->residual && !filedata->data)
       if (!filedata->residual)
          return 0;
       else
          return GetLine(line + copylength, size - copylength, filedata);
    }
    else        /* the line is full, scan until LF found but no copy */
    {
       copylength = min(size, filedata->data);
                                      /* copy over the data         */
       memcpy(line, filedata->scan, copylength);
       line[copylength] = '\0';           /* make into ASCIIZ string    */

    /* we don't want the CR character in the result string*/
//     if ( line[copylength - 1] == CH_CR )
//     {
//       line[copylength - 1] = '\0';
//     } /* endif */

       filedata->data  = 0;             /* no data in buffer          */
       filedata->scan += filedata->data;     /* set scan point to end */

       if (filedata->residual)          /* more to read               */
       {
           ReadNextBuffer(filedata);    /* read the next buffer       */
           return GetLine(line + copylength, 0, filedata);
       }
       else
          return 0;
    }
  }

//    /* if line didn't fit into buffer, then we look at it */
//    /* as multiple lines                                             */
//    if ( size > copylength) {
//      /* buffer was not full, read additional data from file */
//    } else {
//      filedata->scan += copylength;    /* set new scan point         */
//
//      if (!filedata->data) {           /* all used up                */
//        if (filedata->residual)        /* more to read               */
//          ReadNextBuffer(filedata);    /* read the next buffer       */
//      }
//
//      return 0;
//    } /* endif */
}

/********************************************************************
* Function:  GetLine(line, size, filedata)                          *
*                                                                   *
* Purpose:   Reads a line of data using buffered reads.  At end of  *
*            file, zero is returned to indicate nothing left.       *
*                                                                   *
* RC:        TRUE -  line was read successfully                     *
*            FALSE - end of file was reached                        *
*********************************************************************/

//INT GetLine(
//   PSZ          line,                  /* returned line              */
//   ULONG        size,                  /* size of line buffer        */
//   GetFileData *filedata )             /* file handle                */
//{
//   PCHAR        scan;                  /* current scan pointer       */
//   ULONG        length;                /* line length                */
//   ULONG        copylength;            /* copied length              */
//
//  if (!(filedata->data)) {             /* if out of current buffer   */
//    if (filedata->residual) {          /* may be another buffer      */
//      ReadNextBuffer(filedata);        /* try to read one            */
//      if (!filedata->data)             /* nothing more?              */
//        return 1;                      /* all done                   */
//    }
//    else
//      return (1);                      /* return EOF condition       */
//  }
//                                       /* look for a line feed        */
//  scan = (PCHAR)memchr(filedata->scan, CH_NL, filedata->data);
//  if (scan) {                          /* found one                  */
//                                       /* calculate the length       */
//    length = (ULONG)(scan - filedata->scan);
//                                       /* get the length to copy     */
//    if(size <= length)
//      copylength = size;               /* copy as much as possible   */
//    else
//      copylength = length;             /* take the whole line        */
//    if(*(scan-1) == CH_CR)
//      --copylength;                    /* do not copy CH_CR          */
//                                       /* copy over the data         */
//    memcpy(line, filedata->scan, copylength);
//    line[copylength] = '\0';           /* make into ASCIIZ string    */
//    filedata->data -= length + 1;      /* reduce the length          */
//    filedata->scan = scan + 1;         /* set new scan point         */
//    if (!filedata->data) {             /* all used up                */
//      if (filedata->residual)          /* more to read               */
//        ReadNextBuffer(filedata);      /* read the next buffer       */
//      if (filedata->data &&            /* if more to read            */
//        *filedata->scan == CH_NL) {    /* may need to skip a char    */
//        filedata->scan++;              /* step past new line         */
//        filedata->data--;              /* reduce size by one         */
//      }
//    }
//                                       /* may need to skip a char    */
//    else if (*filedata->scan == CH_NL) {
//      filedata->scan++;                /* step past new line         */
//      filedata->data--;                /* reduce size by one         */
//    }
//    return 0;                          /* this worked ok             */
//  }
//  else {                               /* ran off the end            */
//                                       /* get the length to copy     */
//    if(filedata->data <= size)
//      copylength = filedata->data;     /* copy as much as possible   */
//    else
//      copylength = size;               /* take the whole line        */
//                                       /* copy over the data         */
//    memcpy(line, filedata->scan, copylength);
//    line[copylength] = '\0';           /* make into ASCIIZ string    */
//
//    filedata->data -= copylength;
//
//    if (!filedata->residual)           /* all used up?               */
//      return 0;                        /* finished reading           */
//                                       /* line split over buffer     */
//                                       /* recursively call function  */
//
//    /* if line didn't fit into buffer, then we look at it */
//    /* as multiple lines                                             */
//    if ( size > copylength) {
//      return GetLine(line + copylength, size - copylength, filedata);
//    } else {
//      filedata->scan += copylength;    /* set new scan point         */
//
//      if (!filedata->data) {           /* all used up                */
//        if (filedata->residual)        /* more to read               */
//          ReadNextBuffer(filedata);    /* read the next buffer       */
//      }
//
//      return 1;
//    } /* endif */
//  }
//}


/********************************************************************
* Function:  mystrstr(haystack, needle, hlen, nlen, sensitive)      *
*                                                                   *
* Purpose:   Determines if the string 'needle' is in the            *
*            string 'haystack' by returning it's position or        *
*            a NULL if not found.  The length of haystack and       *
*            needle are given by 'hlen' and 'nlen' respectively.    *
*                                                                   *
*            If 'sensitive' is true, then the search is case        *
*            sensitive, else it is case insensitive.                *
*                                                                   *
* RC:        num  - The pos where needle was found.                 *
*            NULL - needle not found.                               *
*                                                                   *
* Used By:   SysFileSearch()                                        *
*********************************************************************/

ULONG mystrstr(
  CHAR   *haystack,
  CHAR   *needle,
  ULONG   hlen,
  ULONG   nlen,
  BOOL    sensitive)

{
  CHAR line[MAX_LINE_LEN];
  CHAR target[MAX_LINE_LEN];
  ULONG p;

 /* Copy line  - Change nulls to spaces and uppercase if needed      */

  for (p = 0; p < hlen; p++) {

    if (haystack[p] == '\0')
      line[p] = ' ';
    else if (sensitive)
      line[p] = haystack[p];
    else line[p] = (CHAR)toupper(haystack[p]);
  }
  line[p] = '\0';
 /* Copy target  - Change nulls to spaces and uppercase if needed    */

  for (p = 0; p < nlen; p++) {

    if (needle[p] == '\0')
      target[p] = ' ';
    else if (sensitive)
      target[p] = needle[p];
    else target[p] = (CHAR)toupper(needle[p]);
  }
  target[p] = '\0';
  return ((ULONG)strstr(line, target));
}

/*************************************************************************
* Function:  get_next_path                                               *
*                                                                        *
* Purpose:   Read one path out of an environment value pointed to by     *
*            ppenv.                                                      *
*            Used by the 'SearchPath' func.                              *
* Return:    0 - read successful                                         *
*            1 - end of environment entry                                *
*************************************************************************/
INT get_next_path(
  PCHAR *ppenv,                      /* environment pointer              */
  PCHAR path_buf)                    /* path buffer                      */
{
  INT i;                             /* counter                          */

  if(*ppenv == NULL)                 /* environment entry available ?    */
    return (1);                      /* return end of envrionment        */
  if(**ppenv == ':')                 /* if we point to the seperator     */
    (*ppenv)++;                      /* jump over                        */
  if(**ppenv == '\0')                /* if end of environment entry      */
    return (1);                      /* return so                        */
                                     /* copy the path out of the         */
                                     /* environment entry                */
  for(i=0;(**ppenv != ':')&&(**ppenv != '\0');(*ppenv)++){
    if(i>MAX_LINE_LEN)               /* if buffer to short               */
      return (1);                    /* get out                          */
    path_buf[i++] = **ppenv;         /* copy this character              */
  }
  path_buf[i] = '\0';                /* terminate the string             */
  return (0);                        /* found another path               */
}

/*************************************************************************
* Function:  SearchPath                                                  *
*                                                                        *
* Purpose:   Search a file along the given environment entry and return  *
*            the full filespec if found.                                 *
*                                                                        *
* Return:    0 - found the file(=>buf is modified)                       *
*            1 - not found                                               *
*************************************************************************/
INT SearchPath(
  INT   SearchFlag,                    /* search curr dir first ?    */
  PCHAR path,                          /* environment variable name  */
  PCHAR filename,                      /* searched file              */
  PCHAR buf,                           /* returned filespec if found */
  INT   buf_size)                      /* size of the return buffer  */
{

  INT   rc = 1;                        /* init rc to not found       */
  DIR   *dp;                           /* directory pointer          */
  struct dirent *ep;                   /* directory entry pointer    */
  INT   length;                        /* path length                */
  CHAR  path_buf[IBUF_LEN];            /* current search path        */
  PCHAR penv;                          /* ptr to the environment     */

  if(!SearchFlag){                     /* search curr dir first ?    */
    dp = opendir("./");                /* open current directory     */
    if(dp != NULL){                    /* worked well ?              */
      while(ep = readdir(dp)){         /* while entries in the dir   */
                                       /* if we have a match         */
        if(!strcmp(ep->d_name,filename)){
          if(!getcwd(buf,buf_size))    /* copy the cwd to return buf */
            return rc;                 /* failed, get out            */
          length = strlen(buf);        /* get the length of the path */
          if((length+2+strlen(filename))>buf_size)/* check buf space */
            return rc;                 /* not enough, get out        */
          buf[length] = '/';           /* add a slash                */
          buf[length+1] = '\0';        /* and update the terminater  */
          strcat(buf,filename);        /* now complete the filespec  */
          rc = NULL;                   /* Yep,found !                */
        }
      }
      (void)closedir(dp);              /* close the directory        */
    }
  }
  if(!rc)                              /* if we already found it     */
   return rc;                          /* return to caller           */

  /* Now search along the environment entry                          */
  penv = getenv(path);                 /* get the environment entry  */
  if(!penv)                            /* if couldn't get the env    */
    return rc;                         /* get out                    */
                                       /* while we have another path */
                                       /* to search for the file     */
  while(!get_next_path(&penv,path_buf)){
    dp = opendir(path_buf);            /* open the directory         */
    if(dp != NULL){                    /* worked well ?              */
      while(ep = readdir(dp)){         /* while entries in the dir   */
                                       /* if we have a match         */
        if(!strcmp(ep->d_name,filename)){
          if(strlen(path_buf)>buf_size)/* check the size             */
            return rc;                 /* get out                    */
          strcpy(buf,path_buf);        /* copy path to the return buf*/
          length = strlen(buf);        /* get the length of the path */
          if((length+2+strlen(filename))>buf_size)/* check buf space */
            return rc;                 /* not enough, get out        */
          buf[length] = '/';           /* add a slash                */
          buf[length+1] = '\0';        /* and update the terminater  */
          strcat(buf,filename);        /* now complete the filespec  */
          (void)closedir(dp);          /* close the directory        */
          return (NULL);               /* Yep,found !                */
        }
      }
      (void)closedir(dp);              /* close the directory        */
    }
  }
  return rc;                           /* return not found           */
}
/*************************************************************************
* Function:  initUtilSems                                                *
*                                                                        *
* Purpose:  get a semaphore set form the system if neccessary.           *
*                                                                        *
* Return:   0 - semaphore set is aviable                                 *
*           1 - system limit reached                                     *
*************************************************************************/
int initUtilSems()
{
  INT rc=NULL;
  INT semId;

  if(!apidata->rexxutilsems){          /* if no semaphore set aviable    */
                                       /* greate one                     */
    rc = createsem(&semId, IPC_PRIVATE, MAXUTILSEM);
    if(rc){                            /* if system limit reached        */
      APICLEANUP(MACROCHAIN);
      return rc;
    }
    apidata->rexxutilsems = semId;     /* remember the ID                */
    /* reset the semaphore control array                                 */
    for(int i=0;i<MAXUTILSEM;i++){     /* for the whole array            */
                                       /* clear the name array           */
      memset((apidata->utilsemfree[i]).name,NULL,MAXNAME);
      (apidata->utilsemfree[i]).usecount = NULL;/* reset usecount        */
    }
  }
  return rc;
}

/*************************************************************************
* Function:  dead                                                        *
*                                                                        *
* Purpose:   signal handling routine for the tout function. Kills the    *
*            timeout thread.                                             *
*                                                                        *
* Return:   none                                                         *
*************************************************************************/
void dead(int sig)
{
  PVOID status=NULL;

  pthread_exit(status);                 /* exit timeout thread           */
}

/*************************************************************************
* Function:  tout (timeout)                                              *
*                                                                        *
* Purpose:   timer thread for the semaphore functions                    *
*                                                                        *
* Return:   none                                                         *
*************************************************************************/
void* tout(void * brk){
  struct timeval tv;                 /* time for the select func   */
  INT * bk;

//#ifdef LINUX
//  pthread_signal(SIGUSR1,dead);
//#else
  signal(SIGUSR1,dead);
//pthread_signal_to_cancel_np((sigset_t*)SIGUSR1,
//                            (pthread_t*)dead);
//#endif

  bk = (INT *)brk;
  bk[1] = bk[1] * 1000;              /* convert to mircoseconds    */
  if(bk[1]<1000000){                 /* less than one second ?     */
    tv.tv_sec = 0;                   /* set seconds to NULL        */
    tv.tv_usec = bk[1];              /* set the microseconds       */
  }
  else {
    tv.tv_usec = bk[1]%1000000;      /* set the microsecs and      */
    bk[1] = bk[1]-tv.tv_usec;        /* substract them             */
    tv.tv_sec = bk[1]/1000000;       /* now set the seconds        */
  }
  select(0,(fd_set*)0,(fd_set*)0,(fd_set*)0,&tv);/* do the sleep   */
  bk[0] = 1;                         /* break                      */
  sleep(10);                         /* wait for death             */
  return((void *) NULL);
}


/*****************************************************************
* Function:  getpath(string, path, filename)                     *
*                                                                *
* Purpose:  This function gets the PATH and FILENAME of the file *
*           target contained in STRING.  The path will end with  *
*           the '/' char if a path is supplied.                  *
*                                                                *
*****************************************************************/

VOID getpath(
             CHAR *string,
             CHAR *path,
             CHAR *filename )
{
  INT    iLen;                         /* length of filespec         */
  INT    LastSlashPos;                 /* position of last slash     */
  CHAR   szSavePath[IBUF_LEN];         /* Keep path to get back to   */

  if (!strcmp(string, "."))            /* period case?               */
    strcpy(string, "./*");             /* make it a * request        */
  else if (!strcmp(string, ".."))      /* double period case?        */
    strcpy(string, "../*");            /* make it a ../ * request    */
  iLen = strlen(string);               /* Get length of full file    */
                                       /* spec                       */
  LastSlashPos = iLen-1;               /* Get max pos of last '/'    */

  /* Step back through string until it begins or at last '/' char    */
  do
    LastSlashPos--;
  while((string[LastSlashPos] != '/') && (LastSlashPos>=0));

  if (string[LastSlashPos] == '/'){    /* if we have a slash         */
    /* Get file name from filespec (just after last '/')             */
    if (string[LastSlashPos+1])        /* have a real name?          */
                                       /* copy it over               */
      strcpy(filename, &string[LastSlashPos+1]);
    else
      strcpy(filename, "*");           /* just use wildcards         */
  }
  else {                               /* no '/' just filename       */
      strcpy(filename, &string[LastSlashPos+1]);
  }

  /* Now resolve to fully qualified path ---------------------------- */
  iLen = strlen(filename);             /* Get file name length        */
  if (string[LastSlashPos] != '/')     /* if we have no slash         */
  {                                    /* resolve current dir         */
    if (!getcwd(path, (IBUF_LEN - iLen - 2)))
       strcpy(path, "./");             /* if no cwd set current dir  */
    else
       strcat(path, "/");
  }
  else {                               /* there is path info         */
    strncpy(path, string, LastSlashPos+1);/* copy the path out       */
    *(path+LastSlashPos+1) = '\0';     /* make ASCII-Z string        */
    if (getcwd(szSavePath, (IBUF_LEN - 1 )))
    {
      if (!chdir(path))                /* If successful get           */
      {                                /*   reolved path name         */
        if ((getcwd(path, (IBUF_LEN - iLen - 2 ))) &&
            ( LastSlashPos > 0 ))
           strcat(path, "/");          /* Add if not root dir         */
        chdir(szSavePath);             /* Back to current dir         */
      }
    }
  }
}


/*****************************************************************
* Function:  LinFindNextFile(path, dir_handle, finfo, d_name)    *
*                                                                *
* Purpose:  This function finds the next file in the directory   *
*           PATH pointed by DIR_HANDLE which matchs the filespec.*
*           All needed info is returned via the FINFO struct     *
*           and the D_NAME pointer.                              *
*                                                                *
* Note:  '?' is currently not supported. Add the impletmentation *
*        here !                                                  *
*****************************************************************/
int LinFindNextFile(
  PCHAR filespec,                      /* filespec to search for     */
  PCHAR path,                          /* current path               */
  DIR *dir_handle,                     /* directory handle           */
  struct stat *finfo,                  /* return buf for the finfo   */
  PCHAR *d_name)                       /* name of the file found     */
{
  struct dirent *dir_entry;            /* Directory entry            */
  CHAR full_path[IBUF_LEN+1];
  CHAR filespec_t[IBUF_LEN+3];         /* copy of filespec for the   */
                                       /* strtok routine             */
  PCHAR token;                         /* ptr to current token       */
  PCHAR start_ptr;                     /* ptr to begin of filename   */
  PCHAR found;                         /* ptr to substring found     */
  PCHAR last_token;
  PCHAR last_found;
  INT bad,no_delimiter,found_flag;


 if(!(dir_entry = readdir(dir_handle)))/* get first entry           */
   return 0;                           /* no entry or EOF            */

 do{

                                       /* make full spec             */
    sprintf(full_path, "%s%s", path, dir_entry->d_name);
    lstat(full_path, finfo);           /* read the info about it     */

  if(S_ISREG(finfo->st_mode) ||        /* if it is a file            */
     S_ISCHR(finfo->st_mode) ||        /* or a device special        */
     S_ISBLK(finfo->st_mode) ||        /* file                       */
     S_ISSOCK(finfo->st_mode) ||       /* or a socket                */
     S_ISLNK(finfo->st_mode) ||        /* or a symbolic link         */
     S_ISFIFO(finfo->st_mode)){        /* or a FIFO                  */

     if(fnmatch(filespec,dir_entry->d_name,FNM_NOESCAPE|FNM_PATHNAME|FNM_PERIOD)==0){
       *d_name = dir_entry->d_name;    /* retptr to the name location*/
       return 1;                       /* return success             */
     }
  }
   }
 while(dir_entry = readdir(dir_handle));/* while have entries       */
 return 0;                            /* no file found or EOF       */


//#ifdef 0
//  if(!(dir_entry = readdir(dir_handle)))/* get first entry           */
//    return 0;                          /* no entry or EOF            */
//
//  do{
//                                       /* make full spec             */
//    sprintf(full_path, "%s%s", path, dir_entry->d_name);
//    lstat(full_path, finfo);           /* read the info about it     */
//
//  if(S_ISREG(finfo->st_mode) ||        /* if it is a file            */
//     S_ISCHR(finfo->st_mode) ||        /* or a device special        */
//     S_ISBLK(finfo->st_mode) ||        /* file                       */
//     S_ISSOCK(finfo->st_mode) ||       /* or a socket                */
//     S_ISLNK(finfo->st_mode) ||        /* or a symbolic link         */
//     S_ISFIFO(finfo->st_mode)){        /* or a FIFO                  */
//
//    if(!strcmp(filespec,"*")){         /*want all files              */
//      *d_name = dir_entry->d_name;     /* retptr to the name location*/
//      return 1;                        /* return success             */
//    }
//    else if(strstr(filespec,"*")){     /* substring search ?         */
//       strcpy(filespec_t,filespec);    /* copy the filespec          */
//       start_ptr = filespec_t;         /* get ptr to first char      */
//       if(filespec_t[0] == '*')        /* if filespec begins with '*'*/
//         start_ptr = filespec_t+1;     /* jump over                  */
//
//       found_flag = 0;                 /* init found flag            */
//       bad = 0;                        /* init no match flag         */
//       found =  last_found = dir_entry->d_name;/* init found ptrs    */
//       token = strtok(start_ptr,"*\0");/* get the first token        */
//
//       /* if filespec doesn't begin with a '*'                       */
//       if(filespec[0] != '*'){
//         /* first token must match the begining of the filename      */
//         if(strncmp(dir_entry->d_name, token, strlen(token)))
//           bad = 1;
//       }
//
//       do {
//         last_token = token;           /* remember the last token    */
//         if(found_flag)                /* first found ?              */
//           if((found = strstr(dir_entry->d_name,token)) &&/*found      */
//                (strlen(found) < strlen(last_found)))/* not before => ok  */
//              last_found = found;        /* remember the last found ptr*/
//             else
//               bad = 1;                    /* not a possible name      */
//         else
//           if((found = strstr(dir_entry->d_name,token)) &&/*found      */
//                (strlen(found) <= strlen(last_found))){/* not before => ok */
//              last_found = found;        /* remember the last found ptr*/
//              found_flag = 1;            /* and set the found flag     */
//           }
//             else
//               bad = 1;                    /* not a possible name      */
//       }
//       while(token = strtok(NULL,"*\0"));/* get next token           */
//
//       /* if filespec doesn't end in a '*'                           */
//       if(filespec[strlen(filespec)-1] != '*'){
//         /* check if last_token matchs the end of the filename       */
//         if(strcmp(dir_entry->d_name+(strlen(dir_entry->d_name)-
//                                strlen(last_token)),last_token))
//           bad = 1;
//       }
//
//       if(!bad){
//         *d_name = dir_entry->d_name;  /* retptr to the name location*/
//         return 1;                     /* return success             */
//       }
//    }
//    else{                              /* we need a full match       */
//      if(!strcmp(dir_entry->d_name,filespec)){ /* have a full match ?*/
//        *d_name = dir_entry->d_name;   /* retptr to the name location*/
//        return 1;                      /* return success             */
//      }
//    }
//  }
//  }
//  while(dir_entry = readdir(dir_handle));/* while have entries       */
//  return 0;                            /* no file found or EOF       */
//#endif
}

/*****************************************************************
* Function:  LinFindNextDir(path, dir_handle, finfo, d_name)     *
*                                                                *
* Purpose:  This function finds the next dir in the directory    *
*           PATH pointed by DIR_HANDLE. All needed info is       *
*           returned via the FINFO struct and the D_NAME pointer.*
*                                                                *
* Note:  '?' is currently not supported. Add the impletmentation *
*        here !                                                  *
*****************************************************************/
int LinFindNextDir(
  PCHAR filespec,                      /* filespec to search for     */
  PCHAR path,                          /* current path               */
  DIR *dir_handle,                     /* directory handle           */
  struct stat *finfo,                  /* return buf for the finfo   */
  PCHAR *d_name)                       /* name of the file found     */
{
  struct dirent *dir_entry;            /* Directory entry            */
  CHAR full_path[IBUF_LEN+1];
  CHAR filespec_t[IBUF_LEN+3];         /* copy of filespec for the   */
                                       /* strtok routine             */
  PCHAR token;                         /* ptr to current token       */
  PCHAR start_ptr;                     /* ptr to begin of filename   */
  PCHAR found;                         /* ptr to substring found     */
  PCHAR last_token;
  PCHAR last_found;
  INT bad,no_delimiter,found_flag;




 if(!(dir_entry = readdir(dir_handle)))/* get first entry           */
   return 0;                           /* no entry or EOF            */

 do{

                                       /* make full spec             */
    sprintf(full_path, "%s%s", path, dir_entry->d_name);
    lstat(full_path, finfo);           /* read the info about it     */

    if(S_ISDIR(finfo->st_mode)){       /* if it is a directory       */

     if(fnmatch(filespec,dir_entry->d_name,FNM_NOESCAPE|FNM_PATHNAME|FNM_PERIOD)==0){
       *d_name = dir_entry->d_name;    /* retptr to the name location*/
       return 1;                       /* return success             */
     }
    }
   }
 while(dir_entry = readdir(dir_handle));/* while have entries       */
 return 0;                            /* no file found or EOF       */




//#ifdef 0
//
//  if(!(dir_entry = readdir(dir_handle)))/* get first entry           */
//    return 0;                          /* no entry or EOF            */
//                                       /* and its full spec          */
//
//  do{
//                                       /* make full spec             */
//    sprintf(full_path, "%s%s", path, dir_entry->d_name);
//    lstat(full_path, finfo);           /* read the info about it     */
//
//    if(S_ISDIR(finfo->st_mode)){       /* if it is a directory       */
//    if(!strcmp(filespec,"*")){         /*want all dirs               */
//      *d_name = dir_entry->d_name;     /* retptr to the name location*/
//      return 1;                        /* return success             */
//    }
//    else if(strstr(filespec,"*")){     /* substring search ?         */
//       strcpy(filespec_t,filespec);    /* copy the filespec          */
//       start_ptr = filespec_t;         /* get ptr to first char      */
//       if(filespec_t[0] == '*')        /* if filespec begins with '*'*/
//         start_ptr = filespec_t+1;     /* jump over                  */
//
//       found_flag = 0;                 /* init found flag            */
//       bad = 0;                        /* init no match flag         */
//       found =  last_found = dir_entry->d_name;/* init found ptrs    */
//       token = strtok(start_ptr,"*\0");/* get the first token        */
//
//       /* if filespec doesn't begin with a '*'                       */
//       if(filespec[0] != '*'){
//         /* first token must match the begining of the filename      */
//         if(strncmp(dir_entry->d_name, token, strlen(token)))
//           bad = 1;
//       }
//
//       do {
//         last_token = token;           /* remember the last token    */
//         if(found_flag)                /* first found ?              */
//           if((found = strstr(dir_entry->d_name,token)) &&/*found      */
//                (strlen(found) < strlen(last_found)))/* not before => ok  */
//              last_found = found;        /* remember the last found ptr*/
//             else
//               bad = 1;                    /* not a possible name      */
//         else
//           if((found = strstr(dir_entry->d_name,token)) &&/*found      */
//                (strlen(found) <= strlen(last_found))){/* not before => ok */
//              last_found = found;        /* remember the last found ptr*/
//              found_flag = 1;            /* and set the found flag     */
//           }
//             else
//               bad = 1;                    /* not a possible name      */
//       }
//       while(token = strtok(NULL,"*\0"));/* get next token           */
//
//       /* if filespec doesn't end in a '*'                           */
//       if(filespec[strlen(filespec)-1] != '*'){
//         /* check if last_token matchs the end of the filename       */
//         if(strcmp(dir_entry->d_name+(strlen(dir_entry->d_name)-
//                                strlen(last_token)),last_token))
//           bad = 1;
//       }
//
//       if(!bad){
//         *d_name = dir_entry->d_name;  /* retptr to the name location*/
//         return 1;                     /* return success             */
//       }
//    }
//    else{                              /* we need a full match       */
//      if(!strcmp(dir_entry->d_name,filespec)){ /* have a full match ?*/
//        *d_name = dir_entry->d_name;   /* retptr to the name location*/
//        return 1;                      /* return success             */
//      }
//    }
//  }
//  }
//  while(dir_entry = readdir(dir_handle));/* while have entries       */
//
//  return 0;                            /* no file found or EOF       */
//#endif
}

/*********************************************************************/
/* Function: ULONG FormatFile(                                       */
/*                                                                   */
/* Purpose:  Returns the new file attribute, given the mask of       */
/*           attributes to be cleared/set and the current attribute  */
/*           settings.                                               */
/*                                                                   */
/*********************************************************************/

ULONG FormatFile(
  RXTREEDATA   *ldp,                   /* Pointer to local data      */
  INT          *smask,                 /* Mask of attributes to      */
                                       /* search for                 */
  INT          *dmask,                 /* Mask of attributes to set  */
  ULONG         options,               /* Search and output format   */
  struct stat  *finfo )                /* File info sturcture        */
{
  USHORT rc;
  struct tm *timestamp;                /* Time info about the file   */
  struct tm stTimestamp;               /* Time info about the file   */
  CHAR tp;                             /* type of the entry          */

  if (options&NAME_ONLY)               /* name only?                 */
    strcpy(ldp->Temp, ldp->truefile);  /* just copy it over          */
  else {
#ifdef AIX
    timestamp = localtime_r(&(finfo->st_mtime),&stTimestamp); /* get the time info */
#else
    timestamp = localtime(&(finfo->st_mtime));/* get the time info   */
#endif
    /* add long time format */
    if (options&LONG_TIME)             /* need the long time format? */
                                       /* format as such             */
      sprintf(ldp->Temp, "%4d-%02d-%02d %02d:%02d:%02d  %10lu  ",
        timestamp->tm_year+1900,
        timestamp->tm_mon+1,
        timestamp->tm_mday,
        timestamp->tm_hour,
        timestamp->tm_min,
        timestamp->tm_sec,
        finfo->st_size);
    else
    {
      if (options&EDITABLE_TIME)       /* need the "smushed" form?   */
                                       /* format as such             */
        sprintf(ldp->Temp, "%02d/%02d/%02d/%02d/%02d  %10lu  ",
          (timestamp->tm_year)%100,
          timestamp->tm_mon+1,
          timestamp->tm_mday,
          timestamp->tm_hour,
          timestamp->tm_min,
          finfo->st_size);
      else                             /* give the pretty form       */
        sprintf(ldp->Temp, "%2d/%02d/%02d  %2d:%02d%c  %10lu  ",
          timestamp->tm_mon+1,
          timestamp->tm_mday,
          (timestamp->tm_year)%100,
          (timestamp->tm_hour < 13?
          timestamp->tm_hour:
          (timestamp->tm_hour-(SHORT)12)),
          timestamp->tm_min,
          ((timestamp->tm_hour < 12 ||
          timestamp->tm_hour == 24)?'a':'p'),
          finfo->st_size);
    }

    /* find the type of the entry                                    */
    if(S_ISLNK(finfo->st_mode))
      tp = 'l';                        /* symbolic link              */
    else if(S_ISBLK(finfo->st_mode))
      tp = 'b';                        /* block device               */
    else if(S_ISCHR(finfo->st_mode))
      tp = 'c';                        /* character device           */
    else if(S_ISDIR(finfo->st_mode))
      tp = 'd';                        /* directory                  */
    else if(S_ISFIFO(finfo->st_mode))
      tp = 'p';                        /* FIFO                       */
    else if(S_ISSOCK(finfo->st_mode))
      tp = 's';                        /* socket                     */
    else
      tp = '-';                        /* regular file               */

                                       /* format the attributes now  */
    sprintf(ldp->Temp, "%s%c%c%c%c%c%c%c%c%c%c  %s", ldp->Temp,
      tp,
      (((finfo->st_mode)&S_IREAD)?'r':'-'),
      (((finfo->st_mode)&S_IWRITE)?'w':'-'),
      (((finfo->st_mode)&S_IEXEC)?'x':'-'),
      (((finfo->st_mode)&S_IRGRP)?'r':'-'),
      (((finfo->st_mode)&S_IWGRP)?'w':'-'),
      (((finfo->st_mode)&S_IXGRP)?'x':'-'),
      (((finfo->st_mode)&S_IROTH)?'r':'-'),
      (((finfo->st_mode)&S_IWOTH)?'w':'-'),
      (((finfo->st_mode)&S_IXOTH)?'x':'-'),
      ldp->truefile);
  }
                                       /* Place new string in Stem   */
  ldp->vlen = strlen(ldp->Temp);
  ldp->count++;
  sprintf(ldp->varname+ldp->stemlen, "%d\0", ldp->count);
  ldp->shvb.shvnext = NULL;
  ldp->shvb.shvname.strptr = ldp->varname;
  ldp->shvb.shvname.strlength = strlen(ldp->varname);
  ldp->shvb.shvvalue.strptr = ldp->Temp;
  ldp->shvb.shvvalue.strlength = ldp->vlen;
  ldp->shvb.shvnamelen = ldp->shvb.shvname.strlength;
  ldp->shvb.shvvaluelen = ldp->vlen;
  ldp->shvb.shvcode = RXSHV_SET;
  ldp->shvb.shvret = 0;

  rc = RexxVariablePool(&ldp->shvb);
  if (rc & (RXSHV_BADN | RXSHV_MEMFL))
  {
    return INVALID_ROUTINE;
  }
  return 0;                            /* good return                */
}

/*****************************************************************************
* Function: RecursiveFindFile( FileSpec, path, lpd, smask, dmask, options )  *
*                                                                            *
* Purpose:  Finds all files starting with FileSpec, and will look down the   *
*           directory tree if required.                                      *
*                                                                            *
* Params:   FileSpec - ASCIIZ string which designates filespec to search     *
*                       for.                                                 *
*           path     - ASCIIZ string for current path                        *
*                                                                            *
*           ldp      - Pointer to local data structure.                      *
*                                                                            *
*           smask    - Array of integers which describe the source attribute *
*                       mask.  Only files with attributes matching this mask *
*                       will be found.                                       *
*                                                                            *
*           dmask    - Array of integers which describe the target attribute *
*                       mask.  Attributes of all found files will be set     *
*                       using this mask.                                     *
*                                                                            *
*             Note:  Both source and targets mask are really arrays of       *
*                    integers.  Each index of the mask corresponds           *
*                    to a different file attribute.  Each indexe and         *
*                    its associated attribute follows:                       *
*                                                                            *
*                         mask[0] = FILE_ARCHIVED                            *
*                         mask[1] = FILE_DIRECTORY                           *
*                         mask[2] = FILE_HIDDEN                              *
*                         mask[3] = FILE_READONLY                            *
*                         mask[4] = FILE_SYSTEM                              *
*                                                                            *
*                    A negative value at a given index indicates that        *
*                    the attribute bit of the file is not set.  A positive   *
*                    number indicates that the attribute should be set.      *
*                    A value of 0 indicates a "Don't Care" setting.          *
*                                                                            *
*           options  - The search/output options.  The following options     *
*                       may be ORed together when calling this function:     *
*                                                                            *
*                    RECURSE     - Indicates that function should search     *
*                                   all child subdirectories recursively.    *
*                    DO_DIRS     - Indicates that directories should be      *
*                                   included in the search.                  *
*                    DO_FILES    - Indicates that files should be included   *
*                                   in the search.                           *
*                    NAME_ONLY   - Indicates that the output should be       *
*                                   restricted to filespecs only.            *
*                    EDITABLE_TIME - Indicates time and date fields should   *
*                                   be output as one timestamp.              *
*                    LONG_TIME   - Indicates time and date fields should     *
*                                   be output as one long formatted timestamp*
*                                                                            *
*****************************************************************************/

LONG RecursiveFindFile(
  PSZ         FileSpec,                /* Filespecs to search for    */
  PSZ         path,                    /* current directory          */
  RXTREEDATA *ldp,                     /* Pointer to local data      */
  INT        *smask,                   /* Mask of attributes to      */
                                       /* search for                 */
  INT        *dmask,                   /* Mask of attributes to set  */
  ULONG       options )                /* Search and output format   */
                                       /* options                    */
{
  CHAR  tempfile[MAX+1];               /* Used to hold temp file name*/
  DIR *dir_handle;                     /* Directory handle           */
  struct stat finfo;                   /* file information           */
  PCHAR filename;

  /********************************************************************
  * First, process all of the normal files, saving directories for    *
  * last.                                                             *
  ********************************************************************/

  if(!(dir_handle = opendir(path))){   /* get the directory handle   */
    return VALID_ROUTINE;              /* return  on non-zero        */
  }

  if (options&DO_FILES &&              /* if processing files        */
                                       /* and have some              */
      (LinFindNextFile(ldp->TargetSpec,path ,dir_handle,&finfo, &filename))) {
                                       /* Get the rest of the files  */
    do {
                                       /* build the full name        */
      sprintf(ldp->truefile, "%s%s", path, filename);
                                       /* passed back ok?            */
      if (FormatFile(ldp, smask, dmask, options, &finfo)) {
        closedir(dir_handle);          /* close the search           */
        return INVALID_ROUTINE;        /* error on non-zero          */
      }
    } while (LinFindNextFile(ldp->TargetSpec,path, dir_handle, &finfo, &filename));
  }
  closedir(dir_handle);                /* reset the                  */
  dir_handle = opendir(path);          /* directory handle (rewinddir*/
                                       /* doesn't work!)             */
  if (options&DO_DIRS  &&              /* need directories?          */
                                       /* and have some              */
      (LinFindNextDir(ldp->TargetSpec,path,dir_handle,&finfo,&filename))) {

    do {
                                       /* dot directory?             */
      if (!strcmp(filename, ".") || !strcmp(filename, ".."))
        continue;                      /* skip this one              */
                                       /* build the full name        */
        sprintf(ldp->truefile, "%s%s", path, filename);
                                       /* passed back ok?            */
        if (FormatFile(ldp, smask, dmask, options, &finfo)) {
          closedir(dir_handle);        /* close the search           */
          return INVALID_ROUTINE;      /* error on non-zero          */
      }
   } while (LinFindNextDir(ldp->TargetSpec,path, dir_handle, &finfo, &filename));
  }
  closedir(dir_handle);                /* reset the                  */
  dir_handle = opendir(path);          /* directory handle (rewinddir*/
                                       /* doesn't work!)             */
  if (options&RECURSE) {               /* need to recurse?           */
                                       /* and have some              */
    if (LinFindNextDir("*",path,dir_handle,&finfo,&filename)) {
      do {
                                       /* dot directory?             */
        if (!strcmp(filename, ".") ||
            !strcmp(filename, ".."))
          continue;                    /* skip this one              */
                                       /* build the new directory    */
        sprintf(tempfile, "%s%s/", path, filename);
                                       /* search the next level      */
        if (RecursiveFindFile(ldp->TargetSpec, tempfile, ldp,
            smask, dmask, options)) {
          closedir(dir_handle);        /* close the search           */
          return INVALID_ROUTINE;      /* error on non-zero          */
        }
      } while (LinFindNextDir("*",path,dir_handle,&finfo,&filename));
    }
  }
  closedir(dir_handle);
  return VALID_ROUTINE;                /* finished                   */
}



/********************************************************************
* Function:  string2long(string, number)                            *
*                                                                   *
* Purpose:   Validates and converts an ASCII-Z string from string   *
*            form to an unsigned long.  Returns FALSE if the number *
*            is not valid, TRUE if the number was successfully      *
*            converted.                                             *
*                                                                   *
* RC:        TRUE - Good number converted                           *
*            FALSE - Invalid number supplied.                       *
*********************************************************************/

BOOL string2long(
  PSZ string,
  LONG *number)
{
  ULONG    accumulator;                /* converted number           */
  INT      length;                     /* length of number           */
  INT      sign;                       /* sign of number             */

  sign = 1;                            /* set default sign           */
  if (*string == '-') {                /* negative?                  */
    sign = -1;                         /* change sign                */
    string++;                          /* step past sign             */
  }

  length = strlen(string);             /* get length of string       */
  if (length == 0 ||                   /* if null string             */
      length > MAX_DIGITS)             /* or too long                */
    return FALSE;                      /* not valid                  */

  accumulator = 0;                     /* start with zero            */

  while (length) {                     /* while more digits          */
    if (!isdigit(*string))             /* not a digit?               */
      return FALSE;                    /* tell caller                */
                                       /* add to accumulator         */
    accumulator = accumulator * 10 + (*string - '0');
    length--;                          /* reduce length              */
    string++;                          /* step pointer               */
  }
  *number = accumulator * sign;        /* return the value           */
  return TRUE;                         /* good number                */
}



void restore_terminal(INT signal){

  stty(STDIN_FILENO,&in_orig);          /* restore the terminal settings        */
  SysInitialize();                      /* restore all signal handler           */
  raise(signal);                        /* propagate signal                     */
}

/******************************************************************************/
/* getkey                                                                     */
/******************************************************************************/
/* echo == FALSE => no echo                                                   */
/* echo == TRUE  => echo                                                      */
/******************************************************************************/
int getkey(char *ret, BOOL echo){
  /* restore original TTY settings on exit */

INT ttyfd = STDIN_FILENO;              /* standard tty filedescriptor        */
int tty_mode = -1;                     /* 1: raw, 0: cooked, -1: initial     */
int need_tty_reset = 0;                /* do we need a reset                 */
/* Set the cleanup handler for unconditional process termination              */
struct sigaction new_action;


/* Set up the structure to specify the new action                             */
new_action.sa_handler = restore_terminal;
sigfillset(&new_action.sa_mask);
new_action.sa_flags = SA_RESTART;

/* Termination signals                                                        */
sigaction(SIGINT, &new_action, NULL);  /* exitClear on SIGINT signal          */
sigaction(SIGTERM, &new_action, NULL); /* exitClear on SIGTERM signal         */
sigaction(SIGQUIT, &new_action, NULL); /* exitClear on SIGQUIT signal         */
sigaction(SIGHUP, &new_action, NULL);  /* exitClear on SIGHUP signal          */
sigaction(SIGTSTP, &new_action, NULL); /* exitClear on SIGTSTP signal         */
sigaction(SIGTTIN, &new_action, NULL); /* exitClear on SIGTTIN signal         */
sigaction(SIGTTOU, &new_action, NULL); /* exitClear on SIGTTOU signal         */
/* Error signals                                                              */
sigaction(SIGSEGV, &new_action, NULL); /* exitClear on SIGSEGV signal         */
sigaction(SIGFPE, &new_action, NULL);  /* exitClear on SIGFPE signal          */
sigaction(SIGILL, &new_action, NULL);  /* exitClear on SIGILL signal          */
sigaction(SIGBUS, &new_action, NULL);  /* exitClear on SIGBUS signal          */
sigaction(SIGPIPE, &new_action, NULL); /* exitClear on broken pipe            */


  if( !isatty(ttyfd) ){                 /* connected to a terminal ?          */
    ret[0] = '\0';
    return 0;
  }
  ttyfd = STDIN_FILENO;                 /* STDIN_FILENO is out default fd     */

                                        /* open tty                           */
  ttyfd = open("/dev/tty", O_RDONLY);   /* get filedescriptor (fd) for tty    */

  struct termios in_raw;                /* global for save reset after SIGNAL */

  gtty(ttyfd, &in_orig);                /* determine existing tty settings */

  /* restore original TTY settings on exit */

  /* change STDIN settings to raw */
  gtty(ttyfd, &in_raw);                 /* save old settings                  */

  in_raw.c_lflag &= ~ICANON;            /* no canonical mode                  */
  if (!echo)                            /* no echo flag set                   */
    in_raw.c_lflag &= ~ECHO;            /* no echo                            */
  in_raw.c_cc[VMIN] = 1;                /* read 1 byte before returning       */
  in_raw.c_cc[VTIME] = 0;               /* return immediatly (no timeout)     */
  stty(ttyfd, &in_raw);                 /* execute settings now!              */


  ret[0] = getchar();                   /* read the char                      */

  ret[1] = '\0';                        /* terminate string                   */

  restore_tty(&in_orig);                /* for standard I/O behavior          */
  close(ttyfd);                         /* close the terminal                 */
  SysInitialize();                      /* restore all signal handlers        */
  return 0;                             /* everything is fine                 */
}





/*************************************************************************
* Function:  SysSleep                                                    *
*                                                                        *
* Syntax:    call SysSleep secs                                          *
*                                                                        *
* Params:    secs - Number of seconds to sleep.                          *
*                                                                        *
* Return:    NO_UTIL_ERROR                                               *
*************************************************************************/

LONG APIENTRY SysSleep(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG  secs;                          /* Time to sleep in secs      */
  LONG  length;                        /* length of the count        */
  PCHAR string;                        /* input sleep time           */
  LONG  nanoseconds;                   /* decimals value             */
  LONG  digits;                        /* number of decimal digits   */
  struct timeval tv;                   /* time for the select func   */
#if defined( HAVE_NANOSLEEP )
  struct timespec    Rqtp, Rmtp;
#elif defined( HAVE_NSLEEP )
  struct timestruc_t Rqtp, Rmtp;
#endif
  LONG nano;
  if (numargs != 1)                    /* Must have one argument     */
    return INVALID_ROUTINE;

  string = args[0].strptr;             /* point to the string        */
  length = args[0].strlength;          /* get length of string       */
  if (length == 0 ||                   /* if null string             */
      length > MAX_DIGITS)             /* or too long                */
    return INVALID_ROUTINE;            /* not valid                  */

  secs = 0;                            /* start with zero            */

  while (length) {                     /* while more digits          */
    if (!isdigit(*string))             /* not a digit?               */
      break;                           /* get out of this loop       */
    secs = secs * 10 + (*string - '0');/* add to accumulator         */
    length--;                          /* reduce length              */
    string++;                          /* step pointer               */
  }
  if (*string == '.') {                /* have a decimal number?     */
    string++;                          /* step over the decimal      */
    length--;                          /* reduce the length          */
    nanoseconds = 0;                   /* no nanoseconds yet         */
    digits = 0;                        /* and no digits              */
    nano = 9;

    while(nano)
    {
      while (length)
      {                   /* while more digits          */
        if (!isdigit(*string))           /* not a digit?               */
          return INVALID_ROUTINE;        /* not a valid number         */
                                       /* add to accumulator         */
        nanoseconds = nanoseconds * 10 + (*string - '0');
        length--;                        /* reduce length              */
        string++;                        /* step pointer               */
        nano--;
      }
      while(nano)
      {
        nanoseconds = nanoseconds * 10;
        nano--;
      }
    }
  }
  else if (length != 0)                /* invalid character found?   */
    return INVALID_ROUTINE;            /* this is invalid            */
#if defined( HAVE_NANOSLEEP )
  Rqtp.tv_sec = secs;
  Rqtp.tv_nsec = nanoseconds;
  nanosleep(&Rqtp, &Rmtp);
#elif defined( HAVE_NSLEEP )
  Rqtp.tv_sec = secs;
  Rqtp.tv_nsec = nanoseconds;
  nsleep(&Rqtp, &Rmtp);
#else
  sleep( secs );
#endif
  BUILDRXSTRING(retstr, NO_UTIL_ERROR);/* return no error            */
  return VALID_ROUTINE;                /* this worked ok             */
}

/*************************************************************************
* Function:  SysLoadFuncs                                                *
*                                                                        *
* Syntax:    call SysLoadFuncs [option]                                  *
*                                                                        *
* Params:    none                                                        *
*                                                                        *
* Return:    null string                                                 *
*************************************************************************/
/* Entry for upper case function name                                */
LONG APIENTRY SYSLOADFUNCS(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
   return( SysLoadFuncs( name, numargs, args, queuename,  retstr ) );
}

LONG APIENTRY SysLoadFuncs(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT    entries;                      /* Num of entries             */
  INT    j;                            /* Counter                    */

  retstr->strlength = 0;               /* set return value           */
                                       /* check arguments            */
  if (numargs > 0)
    return INVALID_ROUTINE;

  entries = sizeof(RxFncTable)/sizeof(PSZ);

  for (j = 0; j < entries; j++) {
    RexxRegisterFunctionDll(RxFncTable[j],
          "rexxutil", RxFncTable[j]);
  }
  return VALID_ROUTINE;
}


/*************************************************************************
* Function:  SysDropFuncs                                                *
*                                                                        *
* Syntax:    call SysDropFuncs                                           *
*                                                                        *
* Return:    NO_UTIL_ERROR - Successful.                                 *
*************************************************************************/

LONG APIENTRY SysDropFuncs(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT     entries;                     /* Num of entries             */
  INT     j;                           /* Counter                    */

  if (numargs != 0)                    /* no arguments for this      */
    return INVALID_ROUTINE;            /* raise an error             */

  retstr->strlength = 0;               /* return a null string result*/

  entries = sizeof(RxFncTable)/sizeof(PSZ);

  for (j = 0; j < entries; j++)
    RexxDeregisterFunction(RxFncTable[j]);

  return VALID_ROUTINE;                /* no error on call           */
}


/**********************************************************************
* Function:  SysCls                                                   *
*                                                                     *
* Syntax:    call SysCls                                              *
*                                                                     *
* Return:    NO_UTIL_ERROR - Successful.                              *
**********************************************************************/

LONG APIENTRY SysCls(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  if (numargs)                         /* arguments specified?       */
    return INVALID_ROUTINE;            /* raise the error            */
  system("clear");                     /* do the clear               */             // think about the use of 'execve', Weigold
  BUILDRXSTRING(retstr, NO_UTIL_ERROR);/* pass back result           */
  return VALID_ROUTINE;                /* no error on call           */
}

/*************************************************************************
* Function:  SysAddRexxMacro                                             *
*                                                                        *
* Syntax:    result = SysAddRexxMacro(name, file, <order>)               *
*                                                                        *
* Params:    name   - loaded name of the macro file                      *
*            file   - file containing the loaded macro                   *
*            order  - Either 'B'efore or 'A'fter.  The default is 'B'    *
*                                                                        *
* Return:    return code from RexxAddMacro                               *
*************************************************************************/

LONG APIENTRY SysAddRexxMacro(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  APIRET      rc;                      /* creation return code       */
  ULONG       position;                /* added position             */

  if (numargs < 2 || numargs > 3 ||    /* wrong number?              */
      !RXVALIDSTRING(args[0]) ||       /* first is omitted           */
      !RXVALIDSTRING(args[1]))         /* second is omitted          */
    return INVALID_ROUTINE;            /* raise error condition      */

  position = RXMACRO_SEARCH_BEFORE;    /* set default search position*/
  if (numargs == 3) {                  /* have an option?            */
    if (RXZEROLENSTRING(args[2]))      /* null string?               */
      return INVALID_ROUTINE;          /* this is an error           */
                                       /* 'B'efore?                  */
    else if (toupper(args[2].strptr[0]) == 'B')
      position = RXMACRO_SEARCH_BEFORE;/* place before               */
                                       /* 'A'fter?                   */
    else if (toupper(args[2].strptr[0]) == 'A')
      position = RXMACRO_SEARCH_AFTER; /* place after                */
    else                               /* parm given was bad         */
      return INVALID_ROUTINE;          /* raise an error             */
  }
  rexxutil_call_sem.request();
  rexxutil_call = TRUE;                /* no RexxInitialize !        */
                                       /* try to add the macro       */
  rc = RexxAddMacro(args[0].strptr, args[1].strptr, position);
  if(rc)
    rexxutil_call_sem.release();
  sprintf(retstr->strptr, "%d", rc);   /* format the return code     */
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;                /* good completion            */
}


/*************************************************************************
* Function:  SysDropRexxMacro                                            *
*                                                                        *
* Syntax:    result = SysDropRexxMacro(name)                             *
*                                                                        *
* Params:    name   - name of the macro space function                   *
*                                                                        *
* Return:    return code from RexxDropMacro                              *
*************************************************************************/

LONG APIENTRY SysDropRexxMacro(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  APIRET      rc;                      /* creation return code       */

  if (numargs != 1)                    /* wrong number?              */
    return INVALID_ROUTINE;            /* raise error condition      */

  rc = RexxDropMacro(args[0].strptr);  /* try to drop the macro      */
  sprintf(retstr->strptr, "%d", rc);   /* format the return code     */
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;                /* good completion            */
}



/*************************************************************************
* Function:  SysClearRexxMacroSpace                                      *
*                                                                        *
* Syntax:    result = SysClearRexxMacroSpace()                           *
*                                                                        *
* Params:    none                                                        *
*                                                                        *
* Return:    return code from RexxClearMacroSpace()                      *
*************************************************************************/

LONG APIENTRY SysClearRexxMacroSpace(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  APIRET      rc;                      /* creation return code       */

  if (numargs)                         /* wrong number?              */
    return INVALID_ROUTINE;            /* raise error condition      */
  rc = RexxClearMacroSpace();          /* clear the macro space      */
  sprintf(retstr->strptr, "%d", rc);   /* format the return code     */
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;                /* good completion            */
}


/*************************************************************************
* Function:  SysSaveRexxMacroSpace                                       *
*                                                                        *
* Syntax:    result = SysSaveRexxMacroSpace(file)                        *
*                                                                        *
* Params:    file   - name of the saved macro space file                 *
*                                                                        *
* Return:    return code from RexxSaveMacroSpace()                       *
*************************************************************************/
LONG APIENTRY SysSaveRexxMacroSpace(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  APIRET      rc;                      /* creation return code       */

  if (numargs != 1)                    /* wrong number?              */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* clear the macro space      */
  rc = RexxSaveMacroSpace(0, NULL, args[0].strptr);
  sprintf(retstr->strptr, "%d", rc);   /* format the return code     */
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysLoadRexxMacroSpace                                       *
*                                                                        *
* Syntax:    result = SysLoadRexxMacroSpace(file)                        *
*                                                                        *
* Params:    file   - name of the saved macro space file                 *

*                                                                        *
* Return:    return code from RexxLoadMacroSpace()                       *
*************************************************************************/

LONG APIENTRY SysLoadRexxMacroSpace(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  APIRET      rc;                      /* creation return code       */

  if (numargs != 1)                    /* wrong number?              */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* clear the macro space      */
  rc = RexxLoadMacroSpace(0, NULL, args[0].strptr);
  sprintf(retstr->strptr, "%d", rc);   /* format the return code     */
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;                /* good completion            */
}


/*************************************************************************
* Function:  SysQueryRexxMacro                                           *
*                                                                        *
* Syntax:    result = SysQueryRexxMacro(name)                            *
*                                                                        *
* Params:    name   - name of the macro space function                   *
*                                                                        *
* Return:    position of the macro ('B' or 'A'), returns null for errors.*
*************************************************************************/
LONG APIENTRY SysQueryRexxMacro(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  APIRET      rc;                      /* creation return code       */
  USHORT      position;                /* returned position          */

  if (numargs != 1)                    /* wrong number?              */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* query the macro position   */
  if (RexxQueryMacro(args[0].strptr, &position))
    retstr->strlength = 0;             /* return a null string       */
  else {
                                       /* before?                    */
    if (position == RXMACRO_SEARCH_BEFORE)
      retstr->strptr[0] = 'B';         /* return a 'B'               */
    else
      retstr->strptr[0] = 'A';         /* must be 'A'fter            */
    retstr->strlength = 1;             /* returning one character    */
  }
  return VALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysReorderRexxMacro                                         *
*                                                                        *
* Syntax:    result = SysReorderRexxMacro(name, order)                   *
*                                                                        *
* Params:    name   - loaded name of the macro file                      *
*            order  - Either 'B'efore or 'A'fter.                        *
*                                                                        *
* Return:    return code from RexxReorderMacro                           *
*************************************************************************/
LONG APIENTRY SysReorderRexxMacro(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  APIRET      rc;                      /* creation return code       */
  ULONG       position;                /* added position             */

  if (numargs != 2 ||                  /* wrong number?              */
      !RXVALIDSTRING(args[0]) ||       /* first is omitted           */
      RXZEROLENSTRING(args[1]))        /* null string?               */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* 'B'efore?                  */
  if (toupper(args[1].strptr[0]) == 'B')
    position = RXMACRO_SEARCH_BEFORE;  /* place before               */
                                       /* 'A'fter?                   */
  else if (toupper(args[1].strptr[0]) == 'A')
    position = RXMACRO_SEARCH_AFTER;   /* place after                */
  else                                 /* parm given was bad         */
    return INVALID_ROUTINE;            /* raise an error             */
                                       /* try to add the macro       */
  rc = RexxReorderMacro(args[0].strptr, position);
  sprintf(retstr->strptr, "%d", rc);   /* format the return code     */
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;                /* good completion            */
}


/*************************************************************************
* Function:  SysMkDir                                                    *
*                                                                        *
* Syntax:    call SysMkDir dir                                           *
*                                                                        *
* Params:    dir - Directory to be created.                              *
*                                                                        *
* Return:    NO_UTIL_ERROR                                               *
*                                                                        *
*************************************************************************/

LONG APIENTRY SysMkDir(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  ULONG  rc;                           /* Ret code of func           */
  PCHAR  path;                         /* given path                 */
  PCHAR  home_dir = NULL;              /* home directory path        */
  PCHAR  dir_buf = NULL;               /* full directory path        */

  if (numargs != 1)
                                       /* If no args, then its an    */
                                       /* incorrect call             */
    return INVALID_ROUTINE;
  path = args[0].strptr;               /* directory to make          */
                                       /* check for using '~/'       */
  if(*(path) == '~'){
    dir_buf = resolve_tilde(path);     /* get absolut path           */
    path = dir_buf;                    /* directory to make          */
  }
  /* Make the dir; standard permissions are rwxr-xr-x                */
  /* we do not restrict permission, this is done by root in the file */
  /* /etc/security/user. We allow anything. System restricts         */
  /* according to the user settings --> smitty/user                  */
//rc = mkdir(path, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
  rc = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
  if(!rc){                             /* if worked well             */
    sprintf(retstr->strptr, "%d", rc); /* result is return code      */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  else{                                /* if there was an error      */
    switch (errno) {

      case EACCES: {
        sprintf(retstr->strptr, "%d", 5); /* result: Access denied   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case EEXIST: {
        sprintf(retstr->strptr, "%d", 87);/*result: already exists   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case EMLINK: {
        sprintf(retstr->strptr, "%d", 206);/* result: exceeds range  */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case ENOSPC: {
        sprintf(retstr->strptr, "%d", 206);/* result: exceeds range  */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case EROFS: {
        sprintf(retstr->strptr, "%d", 108);/* result:read only system*/
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      default:
        sprintf(retstr->strptr, "%d", 2);  /* result: file not found */
        retstr->strlength = strlen(retstr->strptr);
        break;
    }
  }
  if(dir_buf)                              /* did we allocate ?       */
    free(dir_buf);                         /* free the buffer memory  */
  return VALID_ROUTINE;
}


/*************************************************************************
* Function:  SysRmDir                                                    *
*                                                                        *
* Syntax:    call SysRmDir dir                                           *
*                                                                        *
* Params:    dir - Directory to be removed.                              *
*                                                                        *
* Return:    NO_UTIL_ERROR                                               *
*                                                                        *
*************************************************************************/

LONG APIENTRY SysRmDir(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  ULONG  rc;                           /* Ret code of func           */
  PCHAR  path;                         /* given path                 */
  PCHAR  home_dir = NULL;              /* home directory path        */
  PCHAR  dir_buf = NULL;               /* full directory path        */

  if (numargs != 1)
                                       /* If no args, then its an    */
                                       /* incorrect call             */
    return INVALID_ROUTINE;
  path = args[0].strptr;               /* directory to remove        */
                                       /* check for using '~/'       */
  if(*(path) == '~'){
    dir_buf = resolve_tilde(path);     /* get absolut path           */
    path = dir_buf;                    /* directory to remove        */
  }

  rc = rmdir(path);                    /* Remove the directory       */
  if(!rc){                             /* if worked well             */
    sprintf(retstr->strptr, "%d", rc); /* result is return code      */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  else{                                /* if there was an error      */
    switch (errno) {

      case EACCES: {
        sprintf(retstr->strptr, "%d", 5); /* result: Access denied   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
#if defined( ENOTEMPTY ) && defined( EEXIST )
      case EEXIST: {
        sprintf(retstr->strptr, "%d", 87);/*result: already exists   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
#elif defined( ENOTEMPTY )
      case ENOTEMPTY: {                 /* sometimes used for EEXITST */
        sprintf(retstr->strptr, "%d", 87);/*result: already exists   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
#elif defined( EEXIST )
      case EEXIST: {
        sprintf(retstr->strptr, "%d", 87);/*result: already exists   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
#endif
      case EBUSY: {
        sprintf(retstr->strptr, "%d", 5);/* result: currently in use */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case ENOENT: {
        sprintf(retstr->strptr, "%d", 87);/* result: doesn't exitst  */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case EROFS: {
        sprintf(retstr->strptr, "%d", 108);/* result:read only system*/
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
   default:
        sprintf(retstr->strptr, "%d", 2);  /* result: dir not found  */
        retstr->strlength = strlen(retstr->strptr);
        break;
    }
  }
  if(dir_buf)                              /* did we allocate ?       */
    free(dir_buf);                         /* free the buffer memory  */
  return VALID_ROUTINE;
}

/*************************************************************************
* Function:  SysFileDelete                                               *
*                                                                        *
* Syntax:    call SysFileDelete file                                     *
*                                                                        *
* Params:    file - file to be deleted.                                  *
*                                                                        *
* Return:    Return code from DosDelete() function.                      *
*************************************************************************/

LONG APIENTRY SysFileDelete(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  ULONG  rc;                           /* Ret code of func           */
  PCHAR  path;                         /* given path                 */
  PCHAR  home_dir = NULL;              /* home directory path        */
  PCHAR  dir_buf = NULL;               /* full directory path        */

  if (numargs != 1)
                                       /* If no args, then its an    */
                                       /* incorrect call             */
    return INVALID_ROUTINE;
  path = args[0].strptr;               /* file to remove             */
                                       /* check for using '~/'       */
  if(*(path) == '~'){
    dir_buf = resolve_tilde(path);     /* get absolut path           */
    path = dir_buf;                    /* file to remove             */
  }

  rc = remove(path);                   /* Remove the file            */
  if(!rc){                             /* if worked well             */
    sprintf(retstr->strptr, "%d", rc); /* result is return code      */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  else{                                /* if there was an error      */
    switch (errno) {

      case EACCES: {
        sprintf(retstr->strptr, "%d", 5); /* result: Access denied   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case EBUSY: {
        sprintf(retstr->strptr, "%d", 5);/* result: currently in use */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case ENOENT: {
        sprintf(retstr->strptr, "%d", 87);/* result: doesn't exist   */
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      case EROFS: {
        sprintf(retstr->strptr, "%d", 108);/* result:read only system*/
        retstr->strlength = strlen(retstr->strptr);
        break;
      }
      default:
        sprintf(retstr->strptr, "%d", 2);  /* result: file not found */
        retstr->strlength = strlen(retstr->strptr);
        break;
    }
  }
  if(dir_buf)                              /* did we allocate ?       */
    free(dir_buf);                         /* free the buffer memory  */
  return VALID_ROUTINE;
}

/*************************************************************************
* Function:  SysFileSearch                                               *
*                                                                        *
* Syntax:    call SysFileSearch target, file, stem [, options]           *
*                                                                        *
* Params:    target  - String to search for.                             *
*            file    - Filespec to search.                               *
*            stem    - Stem variable name to place results in.           *
*            options - Any combo of the following:                       *
*                       'C' - Case sensitive search (non-default).       *
*                       'N' - Preceed each found string in result stem   *
*                              with it line number in file (non-default).*
*                                                                        *
* Return:    NO_UTIL_ERROR   - Successful.                               *
*            ERROR_NOMEM     - Out of memory.                            *
*************************************************************************/

LONG APIENTRY SysFileSearch(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  PSZ         target;                  /* search string              */
  PSZ         file;                    /* search file                */
  PSZ         opts;                    /* option string              */
//  CHAR        line[MAX_LINE_LEN];      /* Line read from file      */
  ULONG       ptr;                     /* Pointer to char str found  */
  ULONG       num = 0;                 /* Line number                */
  ULONG       len;                     /* Length of string           */
  ULONG       len2;                    /* Length of string           */
  BOOL        linenums = FALSE;        /* Set TRUE for linenums in   */
                                       /* output                     */
  BOOL        sensitive = FALSE;       /* Set TRUE for case-sens     */
                                       /* search                     */
  RXSTEMDATA  ldp;                     /* stem data                  */
  GetFileData filedata;                /* file read information      */
  PCHAR       home_dir;                /* ptr to the environment     */
  PCHAR       dir_buf = NULL;          /* directory buffer           */
  PCHAR       line = NULL;             /* Line read from file        */

  BUILDRXSTRING(retstr, NO_UTIL_ERROR);/* pass back result           */
                                       /* validate arguments         */
  if (numargs < 3 || numargs > 4 ||
      !RXVALIDSTRING(args[0]) ||
      !RXVALIDSTRING(args[1]) ||
      !RXVALIDSTRING(args[2]))
    return INVALID_ROUTINE;            /* raise an error             */

  target = args[0].strptr;             /* get target pointer         */
  file = args[1].strptr;               /* get file name              */

  if(*(file) == '~'){                  /* check for using '~/'       */
    dir_buf = resolve_tilde(file);     /* get absolut path           */
    file = dir_buf;                    /* full path to the file      */
  }
  if (numargs == 4) {                  /* process options            */
    opts = args[3].strptr;             /* point to the options       */
    if (strstr(opts, "N") || strstr(opts, "n"))
      linenums = TRUE;

    if (strstr(opts, "C") || strstr(opts, "c"))
      sensitive = TRUE;
  }
                                       /* Initialize data area       */
  ldp.count = 0;
  strcpy(ldp.varname, args[2].strptr);
  ldp.stemlen = args[2].strlength;
  strupr(ldp.varname);                 /* uppercase the name         */
  if (ldp.varname[ldp.stemlen-1] != '.')
    ldp.varname[ldp.stemlen++] = '.';
  if (OpenFile(file, &filedata)) {     /* open the file              */
    BUILDRXSTRING(retstr, ERROR_FILEOPEN);
    if(dir_buf)                        /* did we allocate ?          */
      free(dir_buf);                   /* free it                    */
    return VALID_ROUTINE;              /* finished                   */
  }

  line = (CHAR *) malloc(4096 * sizeof(CHAR));
                                       /* do the search...found lines*/
                                       /* are saved in stem vars     */
  while (!GetLine(line, MAX_LINE_LEN - 1, &filedata)) {
    len = strlen(line);
    num++;

    ptr = mystrstr(line, target, len, args[0].strlength, sensitive);
    if (ptr != '\0') {
      if (linenums) {
        sprintf(ldp.ibuf, "%d ", num);
        len2 = strlen(ldp.ibuf);
//      memcpy(ldp.ibuf+len2, line, len);
        memcpy(ldp.ibuf+len2, line, min(len, IBUF_LEN-len2));
//        ldp.vlen = len+len2;
        ldp.vlen = min(IBUF_LEN, len+len2);
      }
      else {
        memcpy(ldp.ibuf, line, len);
        ldp.vlen = len;
      }
      ldp.count++;
      sprintf(ldp.varname+ldp.stemlen, "%d\0", ldp.count);
      if (ldp.ibuf[ldp.vlen-1] == '\n')
        ldp.vlen--;
      ldp.shvb.shvnext = NULL;
      ldp.shvb.shvname.strptr = ldp.varname;
      ldp.shvb.shvname.strlength = strlen(ldp.varname);
      ldp.shvb.shvnamelen = ldp.shvb.shvname.strlength;
      ldp.shvb.shvvalue.strptr = ldp.ibuf;
      ldp.shvb.shvvalue.strlength = ldp.vlen;
      ldp.shvb.shvvaluelen = ldp.vlen;
      ldp.shvb.shvcode = RXSHV_SET;
      ldp.shvb.shvret = 0;
      if (RexxVariablePool(&ldp.shvb) == RXSHV_BADN) {
        CloseFile(&filedata);          /* close the file             */
        if(dir_buf)                    /* did we allocate ?          */
          free(dir_buf);               /* free it                    */
        free(line);
        return INVALID_ROUTINE;        /* error on non-zero          */
      }
    }
  }
  free(line);
  CloseFile(&filedata);                /* Close that file            */
                                       /* set stem.0 to lines read   */
  sprintf(ldp.ibuf, "%d\0", ldp.count);
  ldp.varname[ldp.stemlen] = '0';
  ldp.varname[ldp.stemlen+1] = 0;
  ldp.shvb.shvnext = NULL;
  ldp.shvb.shvname.strptr = ldp.varname;
  ldp.shvb.shvname.strlength = ldp.stemlen+1;
  ldp.shvb.shvnamelen = ldp.stemlen+1;
  ldp.shvb.shvvalue.strptr = ldp.ibuf;
  ldp.shvb.shvvalue.strlength = strlen(ldp.ibuf);
  ldp.shvb.shvvaluelen = ldp.shvb.shvvalue.strlength;
  ldp.shvb.shvcode = RXSHV_SET;
  ldp.shvb.shvret = 0;
  if (RexxVariablePool(&ldp.shvb) == RXSHV_BADN){
    if(dir_buf)                        /* did we allocate ?          */
      free(dir_buf);                   /* free it                    */
    return INVALID_ROUTINE;            /* error on non-zero          */
  }
  if(dir_buf)                          /* did we allocate ?          */
    free(dir_buf);                     /* free it                    */
  return VALID_ROUTINE;                /* no error on call           */
}

/*************************************************************************
* Function:  SysSearchPath                                               *
*                                                                        *
* Syntax:    call SysSearchPath path, file [, options]                   *
*                                                                        *
* Params:    path - Environment variable name which specifies a path     *
*                    to be searched (ie 'PATH', 'DPATH', etc).           *
*            file - The file to search for.                              *
*            options -  'C' - Current directory search first (default).  *
*                       'N' - No Current directory search. Only searches *
*                             the path as specified.                     *
*                                                                        *
* Return:    other  - Full path and filespec of found file.              *
*            ''     - Specified file not found along path.               *
*************************************************************************/

LONG APIENTRY SysSearchPath(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  CHAR     buf[IBUF_LEN]={0};          /* returned file name         */
  PSZ      opts;                       /* option string              */
  INT      SearchFlag;                 /* Search control variable    */
                                       /* default=search current 1st */
  INT      ulRc;                       /* return value of SearchPath */


  SearchFlag = CURRENT_DIR_FIRST;      /* set default search flag    */
                                       /* validate arguments         */
  if (numargs < 2 || numargs > 3 ||
      !RXVALIDSTRING(args[0]) ||
      !RXVALIDSTRING(args[1]))
    return INVALID_ROUTINE;

  if (numargs == 3) {                  /* process options            */

    opts = args[2].strptr;             /* point to the options       */
    if ((*opts == 'N') || (*opts == 'n'))
      SearchFlag = ENVIRONMENT_ONLY ;
                                       /* do not search current dir  */

    else if ((*opts == 'C') || (*opts == 'c'))
      SearchFlag = CURRENT_DIR_FIRST;
                                       /* search current 1st(default)*/
    else
      return INVALID_ROUTINE;          /* Invalid option             */
  }

  ulRc = SearchPath(SearchFlag, args[0].strptr, args[1].strptr,
                       (PCHAR)buf, sizeof(buf));

  /* if environment variable could not be found, try again with      */
  /* uppercase name.                                                 */
  if (ulRc)
  {
    strupr( args[0].strptr );
    ulRc = SearchPath(SearchFlag, args[0].strptr, args[1].strptr,
                         (PCHAR)buf, sizeof(buf));
  } /* endif */

  BUILDRXSTRING(retstr, (const char *)buf);          /* pass back result           */
  return VALID_ROUTINE;
}
#ifdef LINUX
/*************************************************************************
* Function:  SysLinVer                                                   *
*                                                                        *
* Syntax:    call SysLinVer                                              *
*                                                                        *
* Return:    Linux Version                                               *
*************************************************************************/

LONG APIENTRY SysLinVer(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{

  struct utsname info;                 /* info structur              */

  if (numargs != 0)                    /* validate arg count         */
    return INVALID_ROUTINE;

  if(uname(&info)<NULL)                /* if no info stored          */
    return INVALID_ROUTINE;            /* get out                    */

  sprintf(retstr->strptr, "%s %s",info.sysname,info.release);
  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;
}
#endif

/*************************************************************************
* Function:  SysVersion                                                  *
*                                                                        *
* Syntax:    call SysVersion                                             *
*                                                                        *
* Return:    Operating System name (LINUX/AIX/WINDOWS) and Version       *
*************************************************************************/

LONG APIENTRY SysVersion(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{

  struct utsname info;                 /* info structur              */

  if (numargs != 0)                    /* validate arg count         */
    return INVALID_ROUTINE;

  if(uname(&info)<NULL)                /* if no info stored          */
    return INVALID_ROUTINE;            /* get out                    */

  sprintf(retstr->strptr, "%s %s.%s",info.sysname, info.version, info.release);

  retstr->strlength = strlen(retstr->strptr);
  return VALID_ROUTINE;
}



/*************************************************************************
* Function:  SysCreateEventSem                                           *
*                                                                        *
* Syntax:    handle = SysCreateEventSem(<name>)                          *
*                                                                        *
* Params:    name  - optional name for a event semaphore                 *
*                                                                        *
* Return:    handle - token used as a event sem handle for               *
*                     SysPostEventSem, SysClearEventSem,                 *
*                     SysCloseEventSem, and SysOpenEventSem              *
*            '' - Empty string in case of any error                      *
*************************************************************************/
LONG APIENTRY SysCreateEventSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT handle;                          /* semaphore handle           */
  INT i;                               /* counter                    */
  BOOL bwaitreset = FALSE;
  int val = 1;
  union semun semopts;               /* for semaphore control      */
/*  if (numargs > 1)                    Too many arguments?          */
  if (numargs > 2)                     /* Too many arguments?        */
      return INVALID_ROUTINE;          /* raise error too many       */

  APISTARTUP(MACROCHAIN);
  if(initUtilSems()) {                 /* if system limit reached    */
    retstr->strlength = 0;             /* return null string         */
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }

  if (!args[1].strlength)
  {
    bwaitreset = TRUE;
  }

  if ((numargs) && (args[0].strlength))
  {
                                       /* if name to long or zero    */
    if(args[0].strlength>MAXNAME-1) {
      printf("\nSemaphore name to long !  \nName: %s\n",args[0].strptr);
      retstr->strlength = 0;           /* return null string         */
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
    }
    /* check wheather semaphore exists                               */
    handle = -1;                       /* reset handle               */
    for(i=0;i<MAXUTILSEM;i++){         /* for all semaphores         */
      if(((apidata->utilsemfree[i]).usecount > NULL) &&/* a used     */
             ((apidata->utilsemfree[i]).type == EVENT)){/*event sem ?*/
                                       /* if we have a match         */
        if(!strcmp((apidata->utilsemfree[i]).name,args[0].strptr)){
          handle = i;                  /* remember the handle        */
          break;                       /* for max sem        */
        }
      }
    }
    if(handle != -1){                  /* if semaphore exists        */
      (apidata->utilsemfree[handle]).usecount++;/* increment usecount*/
      (opencnt[handle][0])++;          /* and privat open count      */
                                       /* format the result          */
      sprintf(retstr->strptr, "%d", (handle+OFFSET));
      retstr->strlength = strlen(retstr->strptr);
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
    }
    else {                             /* semaphore doesn't exists   */
      handle = -1;                     /* reset the handle           */
      /*looking for a unused semaphore                               */
      for(i=0;i<MAXUTILSEM;i++){       /* for all semaphores         */
                                       /* found a unused one ?       */
        if((apidata->utilsemfree[i]).usecount == 0 )
        {                              /* for max sem        */
          handle = i;                  /* remember the handle        */
          break;                       /* for max sem        */
        }                              /* for max sem        */
      }
      if(handle == -1){                /* all semaphores used        */
        retstr->strlength = 0;         /* return null string         */
        APICLEANUP(MACROCHAIN);
        return VALID_ROUTINE;
      }
                                       /* copy the name over         */
      strcpy((apidata->utilsemfree[handle]).name,args[0].strptr);
      (apidata->utilsemfree[handle]).usecount++;/*increment usecount */
      (opencnt[handle][0])++;          /* and privat open count      */
      (apidata->utilsemfree[handle]).type = EVENT;/* set the type    */
      (apidata->utilsemfree[handle]).waitandreset = bwaitreset;/* set the type */
      /* reset the semaphore                                         */
      semopts.val = 1;                 /* initial value                  */
                                       /* do the initialisation          */
      semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
/*semctl is fine, now everyone can catch the semaphore               */

/* Thats not fine, creation should open but not lock                 */

/*      locksem(apidata->rexxutilsems, handle); lock the semaphore */
                                       /* format the result          */
      sprintf(retstr->strptr, "%d", (handle+OFFSET));
      retstr->strlength = strlen(retstr->strptr);
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
    }
  }
  else {                               /* unnamed semaphore          */
      handle = -1;                     /* reset the handle           */
      /*looking for a unused semaphore                               */
      for(i=0;i<MAXUTILSEM;i++){       /* for all semaphores         */
                                       /* found a unused one ?       */
        if((apidata->utilsemfree[i]).usecount == 0 )
        {                              /* for max sem        */
          handle = i;                  /* remember the handle        */
          break;                       /* for max sem        */
        }                              /* for max sem        */
      }
      if(handle == -1){                /* all semaphores used        */
        retstr->strlength = 0;         /* return null string         */
        APICLEANUP(MACROCHAIN);
        return VALID_ROUTINE;
      }
      (apidata->utilsemfree[handle]).usecount++;/*increment usecount */
      (opencnt[handle][0])++;          /* and privat open count      */
      (apidata->utilsemfree[handle]).type = EVENT;/* set the type    */
      (apidata->utilsemfree[handle]).waitandreset = bwaitreset;/* set the type */
      /* reset the semaphore                                         */
      semopts.val = 1;                 /* initial value                  */
                                       /* do the initialisation          */
      semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
/*semctl is fine, now everyone can catch the semaphore               */

/* Thats not fine, creation should open but not lock                 */

/*      locksem(apidata->rexxutilsems, handle); lock the semaphore   */
                                       /* format the result          */
      sprintf(retstr->strptr, "%d", (handle+OFFSET));
      retstr->strlength = strlen(retstr->strptr);
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
  }
}

/*************************************************************************
* Function:  SysOpenEventSem                                             *
*                                                                        *
* Syntax:    result = SysOpenEventSem(handle)                            *
*                                                                        *
* Params:    handle - token returned from SysCreateEventSem              *
*                                                                        *
* Return:    result - return code from DosOpenEventSem                   *
*************************************************************************/

LONG APIENTRY SysOpenEventSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  PCHAR     character;
  CHAR      c[2]= {'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))      /* if it is no number         */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a event semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != EVENT)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if((apidata->utilsemfree[handle]).usecount < MAXUSECOUNT){
    (apidata->utilsemfree[handle]).usecount++;/* increment usecount  */
    (opencnt[handle][0])++;            /* and privat open count      */
    sprintf(retstr->strptr, "%d", 0);  /* no errors                  */
  }
  else
    sprintf(retstr->strptr, "%d", 291);/* to many opens              */
  retstr->strlength = strlen(retstr->strptr);
  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysResetEventSem                                            *
*                                                                        *
* Syntax:    result = SysResetEventSem(handle)                           *
*                                                                        *
* Params:    handle - token returned from SysCreateEventSem              *
*                                                                        *
* Return:    result - return code from DosResetEventSem                  *
*************************************************************************/

LONG APIENTRY SysResetEventSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  union semun semopts;               /* for semaphore control        */
  PCHAR     character;
  int val = 1;
  CHAR      c[2]={'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number        */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a event semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != EVENT)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!(opencnt[handle][0])){           /* if I haven't open the sem  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!getval(apidata->rexxutilsems, handle)){/* already reset        */
    sprintf(retstr->strptr, "%d", 300);/* say so                     */
  }
  else {
    semopts.val = 1;             /* initial value                      */
                                 /* do the initialisation              */
    semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
    locksem(apidata->rexxutilsems, handle);/* lock the semaphore     */
    sprintf(retstr->strptr, "%d", 0);    /* no errors                */
  }
  retstr->strlength = strlen(retstr->strptr);
  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysPostEventSem                                             *
*                                                                        *
* Syntax:    result = SysPostEventSem(handle)                            *
*                                                                        *
* Params:    handle - token returned from SysCreateEventSem              *
*                                                                        *
* Return:    result - return code from DosPostEventSem                   *
*************************************************************************/

LONG APIENTRY SysPostEventSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number        */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a event semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != EVENT)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!(opencnt[handle][0])){           /* if I haven't open the sem  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!getval(apidata->rexxutilsems, handle)){/* if sem is locked     */
  /* unlock the sem to wake the one who waits                        */
  unlocksem(apidata->rexxutilsems, handle);
  sprintf(retstr->strptr, "%d", 0);    /* no errors                  */
  }
  else
    sprintf(retstr->strptr, "%d", 299);/* already posted             */
  retstr->strlength = strlen(retstr->strptr);
  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}
/*************************************************************************
* Function:  SysCloseEventSem                                            *
*                                                                        *
* Syntax:    result = SysCloseEventSem(handle)                           *
*                                                                        *
* Params:    handle - token returned from SysCreateEventSem              *
*                                                                        *
* Return:    result - return code from DosCloseEventSem                  *
*************************************************************************/

LONG APIENTRY SysCloseEventSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  union semun semopts;               /* for semaphore control          */
  INT i;                               /* counter                    */
  int val = 1;
  INT used = NULL;
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number        */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a event semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != EVENT)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if this will be the final close */
  if((apidata->utilsemfree[handle]).usecount == 1){
    /* if another thread in the process is waiting on the sem        */
    if(semgetnumberwaiting(apidata->rexxutilsems,handle))
      sprintf(retstr->strptr, "%d", 301);/* error sem busy           */
    else {                            /* we can close                */
      if((opencnt[handle][0])){       /* if I have it open           */
        --((apidata->utilsemfree[handle]).usecount);/* decrement usecount*/
        --(opencnt[handle][0]);            /* and privat open count  */
        sprintf(retstr->strptr, "%d", 0);  /* no errors              */
      }
      else
        sprintf(retstr->strptr, "%d", 6);  /* invalid handle         */
    }
  }
  else {
      if((opencnt[handle][0])){       /* if I have it open           */
        --((apidata->utilsemfree[handle]).usecount);/* decrement usecount*/
        --(opencnt[handle][0]);            /* and privat open count  */
        sprintf(retstr->strptr, "%d", 0);  /* no errors              */
      }
      else
        sprintf(retstr->strptr, "%d", 6);  /* invalid handle         */
  }
  if(!(apidata->utilsemfree[handle]).usecount){/*sem now unused ?    */
                                       /* clear the name array       */
    memset((apidata->utilsemfree[handle]).name,NULL,MAXNAME);
    /* make sure the sem  is in a clear state                        */
    semopts.val = 1;                   /* initial value                  */
                                       /* do the initialisation          */
    semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
  }
  /* Possibly this was the last used sem. So we can remove the       */
  /* semaphore set. Check this possibility.                          */
  for(i=0;i<MAXUTILSEM;i++){           /* for all semaphores         */
    if((apidata->utilsemfree[i]).usecount != 0 )/* a used one ?      */
      used = 1;                        /* remember it                */
  }
  if(!used){                           /* if all sems are unused     */
    removesem(apidata->rexxutilsems);  /* remove the semaphore set   */
    apidata->rexxutilsems = NULL;      /* delete the old ID          */
  }
  retstr->strlength = strlen(retstr->strptr);
  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysWaitEventSem                                             *
*                                                                        *
* Syntax:    result = SysWaitEventSem(handle, <timeout>)                 *
*                                                                        *
* Params:    handle - token returned from SysWaitEventSem                *
*                                                                        *
* Return:    result - return code from DosWaitEventSem                   *
*************************************************************************/

LONG APIENTRY SysWaitEventSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  INT       timeout;                   /* time for timeout           */
  pid_t     pid;                       /* id of the child process    */
  struct sigaction timer;              /* action for the signal      */
  sigset_t block_mask;                 /* signals to block           */
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};
  pthread_t  thread;                   /* timeout thread             */
  BOOL bwaitandreset = FALSE;
//INT     *brk;                        /* timeout and timeout flag   */

  if (numargs < 1 ||                   /* too few, or                */
      numargs > 2 ||                   /* too many, or               */
      !RXVALIDSTRING(args[0]))         /* first is omitted           */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* get a binary handle        */
  if (numargs == 2) {                  /* have a timeout value?      */
                                       /*for each char of the timeout*/
    for(character=args[1].strptr;*character != '\0';character++){
      c[0] = *character;
      if(!strpbrk(c,"1234567890"))     /* if it is no number         */
        return INVALID_ROUTINE;        /* get out                    */
    }
                                       /* get number of seconds      */
    timeout = strtol(args[1].strptr,NULL,NULL);
  }
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number        */
      return INVALID_ROUTINE;          /* get out                    */
  }
  handle = strtoul(args[0].strptr,NULL,NULL);/* get binary handle    */
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a event semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != EVENT)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!(opencnt[handle][0])){           /* if I haven't open the sem  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  bwaitandreset = apidata->utilsemfree[handle].waitandreset;
  if(numargs == 1){                    /* indefinit wait             */
    APICLEANUP(MACROCHAIN);            /* release the shared resouces*/
    /* try to lock the sem to do the wait                            */
    locksem(apidata->rexxutilsems, handle);

    /* take care, if WAITANDRESET == TRUE don't unlock               */

    if(!bwaitandreset)
    {
      unlocksem(apidata->rexxutilsems, handle);
    }
    sprintf(retstr->strptr, "%d", 0);  /* no errors                  */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;              /* good completion            */
  }
  else {                               /* need timeout               */
    INT brk[2];                        /* timeout flag and value     */
    struct sembuf sem_lock = {handle, -1,IPC_NOWAIT};

    if((!timeout) || (timeout > INT_MAX/1000)){/* if zero timeout    */
      sprintf(retstr->strptr, "%d", 640);/* error timeout            */
      APICLEANUP(MACROCHAIN);          /* release the shared resouces*/
      retstr->strlength = strlen(retstr->strptr);
      return VALID_ROUTINE;            /* good completion            */
    }
    brk[0]=0;                          /* reset the timeout flag     */
    brk[1]=timeout;                    /* set the requested timeout  */
                                       /* start the timeout thread   */
    if(pthread_create(&thread,NULL,tout,(void*)brk)){
      sprintf(retstr->strptr, "%d", 95);/* error not enough memory   */
      APICLEANUP(MACROCHAIN);          /* release the shared resouces*/
      retstr->strlength = strlen(retstr->strptr);
      return VALID_ROUTINE;
    }
    APICLEANUP(MACROCHAIN);            /* release the shared resouces*/
//#ifdef AIX
//    pthread_yield();                 /* must give the timeout thrd           */
//    pthread_yield();                 /* some time to register sig            */
//#else
//    sched_yield();                   /* must give the timeout thrd          */
//    sched_yield();                   /* some time to register sig           */
    SysThreadYield();                  /* some time to register sig           */
    SysThreadYield();                  /* some time to register sig           */
//#endif                               /* try to lock the semaphore           */
                                       /* while no success           */
    while(semop(apidata->rexxutilsems,&sem_lock,1) != 0 ){
      if((errno) && (errno != EAGAIN)){/* if there was a real error  */
       sprintf(retstr->strptr, "%d", 95);/* error not enough memory  */
       retstr->strlength = strlen(retstr->strptr);
       return VALID_ROUTINE;
      }
      else {
//#ifdef AIX
//        pthread_yield();           /* free the processor           */
//#else
//      sched_yield();
        SysThreadYield();            /* free the processor           */
//#endif
        if(brk[0])                   /* if time out                  */
          break;                     /*no longer tying to get the sem*/
      }
    }
    pthread_kill(thread,SIGUSR1);    /* kill the timer thread        */
    if(brk[0]){
      sprintf(retstr->strptr, "%d", 640);/* error timeout            */
    }
    else {/* immediatly release the sem                              */
    /* take care, if WAITANDRESET == TRUE don't unlock               */
      if(!bwaitandreset)
      {
        unlocksem(apidata->rexxutilsems, handle);
      }
      sprintf(retstr->strptr, "%d", 0);/* no error                   */
    }
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;              /* good completion            */
  }
}

/*************************************************************************
* Function:  SysCreateMutexSem                                           *
*                                                                        *
* Syntax:    handle = SysCreateMutexSem(<name>)                          *
*                                                                        *
* Params:    name  - optional name for a event semaphore                 *
*                                                                        *
* Return:    handle - token used as a event sem handle for               *
*                     SysPostEventSem, SysClearEventSem,                 *
*                     SysCloseEventSem, and SysOpenEventSem              *
*            '' - Empty string in case of any error                      *
*************************************************************************/
LONG APIENTRY SysCreateMutexSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT handle;                          /* semaphore handle           */
  INT i;                               /* counter                    */
  int val = 1;
  union semun semopts;               /* for semaphore control          */

  if (numargs > 1)                     /* Too many arguments?        */
      return INVALID_ROUTINE;          /* raise error too many       */

  APISTARTUP(MACROCHAIN);
  if(initUtilSems()) {                 /* if system limit reached    */
    retstr->strlength = 0;             /* return null string         */
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }


  if (numargs == 1) {                  /* request for named sem      */
                                       /* if name to long or zero    */
    if((args[0].strlength>MAXNAME-1) || !(args[0].strlength)){
      printf("\nSemaphore name to long or no name provided !\nName: %s\n",args[0].strptr);
      retstr->strlength = 0;           /* return null string         */
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
    }
    /* check wheather semaphore exists                               */
    handle = -1;                       /* reset handle               */
    for(i=0;i<MAXUTILSEM;i++){         /* for all semaphores         */
      if(((apidata->utilsemfree[i]).usecount > NULL) &&/* a used     */
             ((apidata->utilsemfree[i]).type == MUTEX)){/*mutex sem ?*/
                                       /* if we have a match         */
        if(!strcmp((apidata->utilsemfree[i]).name,args[0].strptr)){
          handle = i;                  /* remember the handle        */
          break;                       /*         for max sem        */
        }
      }
    }
    if(handle != -1){                  /* if semaphore exists        */
      (apidata->utilsemfree[handle]).usecount++;/* increment usecount*/
      (opencnt[handle][0])++;          /* and privat open count      */
                                       /* format the result          */
      sprintf(retstr->strptr, "%d", (handle+OFFSET));
      retstr->strlength = strlen(retstr->strptr);
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
    }
    else {                             /* semaphore doesn't exists   */
      handle = -1;                     /* reset the handle           */
      /*looking for a unused semaphore                               */
      for(i=0;i<MAXUTILSEM;i++){       /* for all semaphores         */
                                       /* found a unused one ?       */
        if((apidata->utilsemfree[i]).usecount == 0 )
        {                              /* for max sem        */
          handle = i;                  /* remember the handle        */
          break;                       /* for max sem        */
        }                              /* for max sem        */
      }
      if(handle == -1){                /* all semaphores used        */
        retstr->strlength = 0;         /* return null string         */
        APICLEANUP(MACROCHAIN);
        return VALID_ROUTINE;
      }
                                       /* copy the name over         */
      strcpy((apidata->utilsemfree[handle]).name,args[0].strptr);
      (apidata->utilsemfree[handle]).usecount++;/*increment usecount */
      (opencnt[handle][0])++;          /* and privat open count      */
      (apidata->utilsemfree[handle]).type = MUTEX;/* set the type    */
      /* reset the semaphore                                         */
      semopts.val = 1;                 /* initial value                  */
                                       /* do the initialisation          */
      semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
                                       /* format the result          */
      sprintf(retstr->strptr, "%d", (handle+OFFSET));
      retstr->strlength = strlen(retstr->strptr);
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
    }
  }
  else {                               /* unnamed semaphore          */
      handle = -1;                     /* reset the handle           */
      /*looking for a unused semaphore                               */
      for(i=0;i<MAXUTILSEM;i++){       /* for all semaphores         */
                                       /* found a unused one ?       */
        if((apidata->utilsemfree[i]).usecount == 0 )
        {
          handle = i;                  /* remember the handle        */
          break;                       /*         for max sem        */
        }
      }
      if(handle == -1){                /* all semaphores used        */
        retstr->strlength = 0;         /* return null string         */
        APICLEANUP(MACROCHAIN);
        return VALID_ROUTINE;
      }
      (apidata->utilsemfree[handle]).usecount++;/*increment usecount */
      (opencnt[handle][0])++;          /* and privat open count      */
      (apidata->utilsemfree[handle]).type = MUTEX;/* set the type    */
      /* reset the semaphore                                         */
      semopts.val = 1;                 /* initial value                  */
                                       /* do the initialisation          */
      semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
                                       /* format the result          */
      sprintf(retstr->strptr, "%d", (handle+OFFSET));
      retstr->strlength = strlen(retstr->strptr);
      APICLEANUP(MACROCHAIN);
      return VALID_ROUTINE;
  }
}

/*************************************************************************
* Function:  SysOpenMutexSem                                             *
*                                                                        *
* Syntax:    result = SysOpenMutexSem(handle)                            *
*                                                                        *
* Params:    handle - token returned from SysCreateMutexSem              *
*                                                                        *
* Return:    result - return code from DosOpenEventSem                   *
*************************************************************************/

LONG APIENTRY SysOpenMutexSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number         */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a mutex semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != MUTEX)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if((apidata->utilsemfree[handle]).usecount < MAXUSECOUNT){
    (apidata->utilsemfree[handle]).usecount++;/* increment usecount  */
    (opencnt[handle][0])++;            /* and privat open count      */
    sprintf(retstr->strptr, "%d", 0);    /* no errors                */
  }
  else
    sprintf(retstr->strptr, "%d", 291);  /* to many opens            */
  retstr->strlength = strlen(retstr->strptr);
  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysRequestMutexSem                                          *
*                                                                        *
* Syntax:    result = SysRequestMutexSem(handle, <timeout>)              *
*                                                                        *
* Params:    handle - token returned from SysRequestMutexSem             *
*                                                                        *
* Return:    result - return code from DosWaitEventSem                   *
*************************************************************************/

LONG APIENTRY SysRequestMutexSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  INT       timeout;                   /* time for timeout           */
  pid_t     pid;                       /* id of the child process    */
  struct sigaction timer;              /* action for the signal      */
  pthread_t thread;                    /* timeout thread             */
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};

  if (numargs < 1 ||                   /* too few, or                */
      numargs > 2 ||                   /* too many, or               */
      !RXVALIDSTRING(args[0]))         /* first is omitted           */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* get a binary handle        */
  if (numargs == 2) {                  /* have a timeout value?      */
                                       /*for each char of the timeout*/
    for(character=args[1].strptr;*character != '\0';character++){
      c[0] = *character;
      if(!strpbrk(c,"1234567890"))     /* if it is no number         */
        return INVALID_ROUTINE;        /* get out                    */
    }
                                       /* get number of seconds      */
    timeout = strtol(args[1].strptr,NULL,NULL);
  }
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number        */
      return INVALID_ROUTINE;          /* get out                    */
  }
  handle = strtoul(args[0].strptr,NULL,NULL);/* get binary handle    */
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
//  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
//    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a mutex semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != MUTEX)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
//    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!(opencnt[handle][0])){           /* if I haven't open the sem  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
//    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(numargs == 1){                    /* indefinit wait             */

    if(!getval(apidata->rexxutilsems, handle)){/* if sem is locked     */
                                               /* and I'm the owner    */
      if((opencnt[handle][1])== SysQueryThreadID()){
//        APICLEANUP(MACROCHAIN);          /* release the shared resouces*/
        sprintf(retstr->strptr, "%d", 0);    /* no errors              */
      }
      else {                             /* wait for it                */
//        APICLEANUP(MACROCHAIN);          /* release the shared resouces*/
        /* try to lock the sem                                         */
        locksem(apidata->rexxutilsems, handle);
        (opencnt[handle][1])= SysQueryThreadID();/* TID of the owner   */
        sprintf(retstr->strptr, "%d", 0);  /* no errors                */
      }
    }
    else {                               /* sem unlocked               */
      /*        lock the sem                                           */
      locksem(apidata->rexxutilsems, handle);
      (opencnt[handle][1])= SysQueryThreadID();/* TID of the owner     */
//      APICLEANUP(MACROCHAIN);            /* release the shared resouces*/
      sprintf(retstr->strptr, "%d", 0);  /* no errors                  */
    }
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* good completion            */
  }
  else {                                 /* need timeout porcess       */
      if(!getval(apidata->rexxutilsems, handle)){/* if sem is locked   */
                                                 /* and I'm the owner  */
        if((opencnt[handle][1])== SysQueryThreadID()){
//          APICLEANUP(MACROCHAIN);        /* release the shared resouces*/
          sprintf(retstr->strptr, "%d", 0);/* no errors                */
        }
        else {                           /* wait for it                */
          INT brk[2];
          struct sembuf sem_lock = {handle, -1,IPC_NOWAIT};
          if((!timeout) || (timeout > INT_MAX/1000)){/* if zero timeout*/
            sprintf(retstr->strptr, "%d", 640);/* error timeout        */
//            APICLEANUP(MACROCHAIN);      /* release the shared resouces*/
            retstr->strlength = strlen(retstr->strptr);
            return VALID_ROUTINE;        /* good completion            */
          }
          brk[0]=0;                      /* reset the timeout flag     */
          brk[1]=timeout;                /* set the requested timeout  */
                                         /* start the timeout thread   */
          if(pthread_create(&thread,NULL,tout,(void*)brk)){
            sprintf(retstr->strptr, "%d", 95);/*error not enough memory*/
//            APICLEANUP(MACROCHAIN);      /* release the shared resouces*/
            retstr->strlength = strlen(retstr->strptr);
            return VALID_ROUTINE;
          }
//          APICLEANUP(MACROCHAIN);        /* release the shared resouces*/
//#ifdef AIX
//          pthread_yield();             /* must give the timeout thrd */
//          pthread_yield();             /* some time to register sig  */
//#else
//          sched_yield();               /* must give the timeout thrd          */
//          sched_yield();               /* some time to register sig           */
          SysThreadYield();              /* free the processor           */
          SysThreadYield();              /* free the processor           */
//#endif                                 /* try to lock the semaphore           */
                                         /* while no success           */
          while(semop(apidata->rexxutilsems,&sem_lock,1) != 0 ){
            if((errno) && (errno != EAGAIN)){/* if there was a real error  */
             sprintf(retstr->strptr, "%d", 95);/* error not enough memory  */
             retstr->strlength = strlen(retstr->strptr);
             return VALID_ROUTINE;
            }
            else {
//#ifdef AIX
//              pthread_yield();       /* free the processor           */
//#else
//              sched_yield();         /* free the processor           */
              SysThreadYield();        /* free the processor           */
//#endif
              if(brk[0])               /* if time out                  */
                break;                 /*no longer tying to get the sem*/
            }
          }
          pthread_kill(thread,SIGUSR1);/* kill the timer thread        */
          if(brk[0]){
            sprintf(retstr->strptr, "%d", 640);/* error timeout        */
          }
          else {/* got it                                              */
            (opencnt[handle][1])= SysQueryThreadID();/*TID of the owner*/
            sprintf(retstr->strptr, "%d", 0);/* no error               */
          }
          retstr->strlength = strlen(retstr->strptr);
          return VALID_ROUTINE;          /* good completion            */
        }
      }
      else {                             /* sem unlocked               */

        /*        lock the sem                                         */
        locksem(apidata->rexxutilsems, handle);
        (opencnt[handle][1])= SysQueryThreadID();/* TID of the owner   */
//        APICLEANUP(MACROCHAIN);        /* release the shared resouces  */
        sprintf(retstr->strptr, "%d", 0);/* no errors                  */
      }
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;              /* good completion              */
  }
}


/*************************************************************************
* Function:  SysReleaseMutexSem                                          *
*                                                                        *
* Syntax:    result = SysReleaseMutexSem(handle)                         *
*                                                                        *
* Params:    handle - token returned from SysCreateMutexSem              *
*                                                                        *
* Return:    result - return code from DosCloseEventSem                  *
*************************************************************************/

LONG APIENTRY SysReleaseMutexSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
//  union semun semopts;             /* for semaphore control          */
  INT i;                               /* counter                    */
  INT used = NULL;
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number        */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
//  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
//    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a mutex semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != MUTEX)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
//    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!(opencnt[handle][0])){           /* if I haven't open the sem  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
//    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  if(!getval(apidata->rexxutilsems, handle)){/* if sem is locked     */
                                             /* and I'm the owner    */
    if((opencnt[handle][1])== SysQueryThreadID()){
      /* unlock the sem                                              */
      unlocksem(apidata->rexxutilsems, handle);
      (opencnt[handle][1])= 0;         /* reset the owner TID        */
      sprintf(retstr->strptr, "%d", 0);    /* no errors              */
    }
    else
      sprintf(retstr->strptr, "%d", 288);/* error not owner          */
  }
  else
    sprintf(retstr->strptr, "%d", 288);/* error not owner            */
  retstr->strlength = strlen(retstr->strptr);
//  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}
/*************************************************************************
* Function:  SysCloseMutexSem                                            *
*                                                                        *
* Syntax:    result = SysCloseMutexSem(handle)                           *
*                                                                        *
* Params:    handle - token returned from SysCreateMutexSem              *
*                                                                        *
* Return:    result - return code from DosCloseEventSem                  *
*************************************************************************/

LONG APIENTRY SysCloseMutexSem(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  INT       handle;                    /* semaphore  handle          */
  union semun semopts;               /* for semaphore control          */
  INT i;                               /* counter                    */
  int val = 1;
  INT used = NULL;
  PCHAR     character;
  CHAR      c[2]={'\0','\0'};

  if (numargs != 1)                    /* Only one argument accepted */
    return INVALID_ROUTINE;            /* raise error condition      */
                                       /* for each char of the handle*/
  for(character=args[0].strptr;*character != '\0';character++){
    c[0] = *character;
    if(!strpbrk(c,"1234567890"))       /* if it is no number         */
      return INVALID_ROUTINE;          /* get out                    */
  }
                                       /* get a binary handle        */
  handle = strtoul(args[0].strptr,NULL,NULL);
  handle = handle - OFFSET;            /* make it real               */
  if (handle < NULL || handle >= MAXUTILSEM){/* if bad handle        */
    sprintf(retstr->strptr, "%d", 6);  /* say so                     */
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;
  }
  APISTARTUP(MACROCHAIN);
  if(!apidata->rexxutilsems){          /* no sems created until now  */
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if the semaphore is unused or isn't a mutex semaphore           */
  if(((apidata->utilsemfree[handle]).usecount == 0 ) ||
         ((apidata->utilsemfree[handle]).type != MUTEX)){
    sprintf(retstr->strptr, "%d", 6);  /* invalid handle             */
    retstr->strlength = strlen(retstr->strptr);
    APICLEANUP(MACROCHAIN);
    return VALID_ROUTINE;
  }
  /* if this will be the final close */
  if((apidata->utilsemfree[handle]).usecount == 1){
    /* if another thread in the process is the owner  (sem locked)   */
    if(!getval(apidata->rexxutilsems, handle))
      sprintf(retstr->strptr, "%d", 301);/* error sem busy           */
    else {                             /* we can close               */
      if((opencnt[handle][0])){        /* if I have it open          */
        --((apidata->utilsemfree[handle]).usecount);/* decrement usecount*/
        --(opencnt[handle][0]);          /* and privat open count    */
        sprintf(retstr->strptr, "%d", 0);  /* no errors              */
      }
      else
        sprintf(retstr->strptr, "%d", 6);  /* invalid handle         */
    }
  }
  else {
      if((opencnt[handle][0])){       /* if I have it open           */
        --((apidata->utilsemfree[handle]).usecount);/* decrement usecount*/
        --(opencnt[handle][0]);          /* and privat open count    */
        sprintf(retstr->strptr, "%d", 0);  /* no errors              */
      }
      else
        sprintf(retstr->strptr, "%d", 6);  /* invalid handle         */
  }
  if(!(apidata->utilsemfree[handle]).usecount){/*sem now unused ?    */
                                       /* clear the name array       */
    memset((apidata->utilsemfree[handle]).name,NULL,MAXNAME);
    /* make sure the sem  is in a clear state                        */
    semopts.val = 1;                   /* initial value                  */
                                       /* do the initialisation          */
    semctl(apidata->rexxutilsems, handle, SETVAL, semopts);
  }
  /* Possibly this was the last used sem. So we can remove the       */
  /* semaphore set. Check this possibility.                          */
  for(i=0;i<MAXUTILSEM;i++){           /* for all semaphores         */
    if((apidata->utilsemfree[i]).usecount != 0 ) /* a used one ?          */
    {                                  /* for max sem        */
      used = 1;                        /* remember it                */
      break;                           /* for max sem        */
    }                                  /* for max sem        */
  }
  if(!used){                           /* if all sems are unused     */
    removesem(apidata->rexxutilsems);  /* remove the semaphore set   */
    apidata->rexxutilsems = NULL;      /* delete the old ID          */
  }
  retstr->strlength = strlen(retstr->strptr);
  APICLEANUP(MACROCHAIN);
  return VALID_ROUTINE;                /* good completion            */
}


/*************************************************************************
* Function:  SysFileTree                                                 *
*                                                                        *
* Syntax:    call SysFileTree filespec, stem [, options]                 *
*                                                                        *
* Params:    filespec - Filespec to search for (may include * and ?).    *
*            stem     - Name of stem var to store results in.            *
*            options  - Any combo of the following:                      *
*                        'B' - Search for files and directories.         *
*                        'D' - Search for directories only.              *
*                        'F' - Search for files only.                    *
*                        'O' - Only output file names.                   *
*                        'S' - Recursively scan subdirectories.          *
*                        'T' - Combine time & date fields into one.      *
*                        'L' - Long time format                          *
*                                                                        *
* Return:    NO_UTIL_ERROR   - Successful.                               *
*            ERROR_NOMEM     - Out of memory.                            *
*************************************************************************/

LONG APIENTRY SysFileTree(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  CHAR        FileSpec[IBUF_LEN];      /* File spec to look for      */
  CHAR        path[IBUF_LEN];          /* path to search along       */
  PCHAR       optptr;                  /* option scan pointer        */
  ULONG       options;                 /* Mask of options            */
  ULONG       y;                       /* Temp counter (II)          */
  INT         smask[5];                /* Source attribute mask      */
  INT         dmask[5];                /* Target attribute mask      */
  RXTREEDATA  ldp;                     /* local data                 */
  PCHAR       temp;

  options = DO_FILES|DO_DIRS;          /* Clear if we should not     */
                                       /* display files              */
  smask[0] = IGNORE;                   /* No mask unless specified   */
  dmask[0] = IGNORE;                   /* No mask unless specified   */
  path[0] = '\0';                      /* no path yet                */
  BUILDRXSTRING(retstr, NO_UTIL_ERROR);/* pass back result           */

                                       /* validate arguments         */
  if (numargs < 2 || numargs > 3 ||
      !RXVALIDSTRING(args[0]) ||
      !RXVALIDSTRING(args[1]) ||
      args[0].strlength > 255)
    return INVALID_ROUTINE;            /* Invalid call to routine    */
                                       /* initialize data area       */
  ldp.count = 0;
  strcpy(ldp.varname, args[1].strptr);
  ldp.stemlen = args[1].strlength;
  /* uppercase the name  */
  temp = ldp.varname;
  for(int k=0;k<strlen(ldp.varname);k++) {/* loop through mem and    */
    *temp = toupper(*temp);            /* uppercase each char        */
    temp++;
  }

  if (ldp.varname[ldp.stemlen-1] != '.')
    ldp.varname[ldp.stemlen++] = '.';

  strcpy(FileSpec, args[0].strptr);    /* get file spec              */

  /* if filespec is '*' then use './ *'                               */
  if((strlen(FileSpec)==1)&&(FileSpec[0] == '*'))
    strcpy(FileSpec, "./*");

   /** If FileSpec ends in / then append  *                          */

  if (FileSpec[strlen(FileSpec)-1] == '/')
    strcat(FileSpec, "*");

  /* if filespec begins with '~' generate absolute path              */
  if(FileSpec[0] == '~'){
    if(!(temp = resolve_tilde(FileSpec)))/* get the absolute path    */
      return INVALID_ROUTINE;
    strcpy(FileSpec,temp);             /* work with the new one      */
    free(temp);                        /* free temp space            */
  }

  if (numargs >= 3 &&                  /* check third option         */
      !RXNULLSTRING(args[2])) {
    if (!args[2].strlength)            /* a zero length string isn't */
      return INVALID_ROUTINE;          /* valid                      */
    optptr = args[2].strptr;           /* copy the pointer           */
    while (*optptr) {                  /* while more characters      */
      switch(toupper(*optptr)) {       /* process each option        */
        case 'S':                      /* recurse on subdirectories  */
          options |= RECURSE;          /* Should we recurse          */
          break;

        case 'O':                      /* only return names          */
          options |= NAME_ONLY;        /* Should include names only  */
          break;

        case 'T':                      /* editable time?             */
          options |= EDITABLE_TIME;    /* create editable timestamp  */
          break;

        case 'L':                      /* long time format?          */
          options |= LONG_TIME;        /* create timestamp           */
          break;

        case 'F':                      /* include only files?        */
          options &= ~DO_DIRS;         /* Should not include dirs !  */
          options |= DO_FILES;         /* Should include files !     */
          break;

        case 'D':                      /* include only directories?  */
          options |= DO_DIRS;          /* Should include dirs !      */
          options &= ~DO_FILES;        /* Should not include files ! */
          break;

        case 'B':                      /* include both files and dirs*/
          options |= DO_DIRS;          /* Should include dirs !      */
          options |= DO_FILES;         /* Should include files !     */
          break;

        default:                       /* unknown option             */
          return INVALID_ROUTINE;      /* raise an error             */
      }
      optptr++;                        /* step the option pointer    */
    }
  }
                                       /* get path and name          */
  getpath(FileSpec, path, ldp.TargetSpec);
                                       /* recursively search         */
  if (RecursiveFindFile(FileSpec, path, &ldp, smask, dmask, options))
    return INVALID_ROUTINE;
                                       /* return lines read          */
  sprintf(ldp.Temp, "%d", ldp.count);
  ldp.varname[ldp.stemlen] = '0';
  ldp.varname[ldp.stemlen+1] = 0;
  ldp.shvb.shvnext = NULL;
  ldp.shvb.shvname.strptr = ldp.varname;
  ldp.shvb.shvname.strlength = ldp.stemlen+1;
  ldp.shvb.shvnamelen = ldp.stemlen+1;
  ldp.shvb.shvvalue.strptr = ldp.Temp;
  ldp.shvb.shvvalue.strlength = strlen(ldp.Temp);
  ldp.shvb.shvvaluelen = ldp.shvb.shvvalue.strlength;
  ldp.shvb.shvcode = RXSHV_SET;
  ldp.shvb.shvret = 0;
  if (RexxVariablePool(&ldp.shvb) == RXSHV_BADN)
    return INVALID_ROUTINE;            /* error on non-zero          */

  return VALID_ROUTINE;                /* no error on call           */
}



/*************************************************************************
* Function:  SysTempFileName                                             *
*                                                                        *
* Syntax:    call SysTempFileName template [,filler]                     *
*                                                                        *
* Params:    template - Description of filespec desired.  For example:   *
*                        C:\TEMP\FILE.???                                *
*            filler   - A character which when found in template will be *
*                        replaced with random digits until a unique file *
*                        or directory is found.  The default character   *
*                        is '?'.                                         *
*                                                                        *
* Return:    other - Unique file/directory name.                         *
*            ''    - No more files exist given specified template.       *
*************************************************************************/

LONG APIENTRY SysTempFileName(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  CHAR   filler;                       /* filler character           */
  CHAR numstr[6];
  ULONG  num, start, max;
  CHAR   *array;
  CHAR   *dir;                         /* the directory              */
  CHAR   *file;                        /* the file prefix            */
  CHAR *tmp;                           /* temporary                  */
  int x, j, i;
  j = 0;                                     /* get a copy of the argument */
  i = 0;
  max = 1;

  if (numargs < 1 ||                   /* validate arguments         */
      numargs > 2 ||
      !RXVALIDSTRING(args[0]) ||
      args[0].strlength > 512)
    return INVALID_ROUTINE;

  if (numargs == 2 &&                  /* get filler character       */
      !RXNULLSTRING(args[1])) {
    if (args[1].strlength != 1)        /* must be one character      */
      return INVALID_ROUTINE;
    filler = args[1].strptr[0];
  }
  else
    filler = '?';
                                       /* get the file id            */
  dir = (char*) malloc(args[0].strlength);
  if (dir == NULL){                    /* if something went wrong    */
    BUILDRXSTRING(retstr, ERROR_NOMEM);
    return VALID_ROUTINE;
  }

  strcpy(dir, args[0].strptr);        /* copy the string             */

  tmp = dir;                          /* set temporary               */

/* search for filter        *********/

  for (x = 0; tmp[x] != 0; x++)
  {
    if (tmp[x] == filler)
    {
      max = max *10;
      j++;
    }
  }

  if (j)
  {
    srand(time(0));
    num = rand();
    num = num % max;

    switch (j)
    {
       case 1:
              sprintf(numstr, "%01u", num);
              break;
       case 2:
              sprintf(numstr, "%02u", num);
              break;
       case 3:
              sprintf(numstr, "%03u", num);
              break;
       case 4:
              sprintf(numstr, "%04u", num);
              break;
       case 5:
              sprintf(numstr, "%05u", num);
              break;
       default:
              return INVALID_ROUTINE;            /* raise error condition */
    }                                            /* for compatibility     */

    for (x = 0; tmp[x] !=0; x++)
    {
      if (tmp[x] == filler)
      {
        tmp[x] = numstr[i++];
      }
    }
  }                                         /* if we need the filler */

  while(*tmp != 0 )                         /* lets start at the end */
  {
    tmp++;
  }

  while((*tmp != '/') && (*tmp != '\\') && (tmp > dir))
  {
    --tmp;
  }

  if(tmp == dir)
  {                                 /* directory string is '' or '/' */
    if(*dir == '\\'){
      file = dir+1;
      array = tempnam(NULL,file); /* call system routine    */
    }
    else if(*dir == '/'){
      file = dir+1;
      array = tempnam("/",file); /* call system routine     */
    }
    else{
      file = dir;
      array = tempnam(NULL,file);/* call system routine     */
    }
  }
  else
  {                                /* directory string exists    */
    file = tmp+1;                      /* set filename prefix        */
    *tmp = '\0';                       /* terminate directory string */
    array = tempnam(dir,file);/* call system routine        */
  }

  if(strlen(array) > 255)
  {
     free((char *)retstr->strptr);
     retstr->strptr = (char *) malloc(strlen(array) + 1);
  }

  strcpy(retstr->strptr, array);
                                       /* correct string length      */
  retstr->strlength = strlen(retstr->strptr);

  free (array);
  free(dir);                           /* free local string          */

  return VALID_ROUTINE;
}



/*************************************************************************
* Function:  SysSetPriority                                              *
*                                                                        *
* Syntax:    result = SysSetPriority(Class, Level)                       *
*                                                                        *
* Params:    Class  - The priority class (0-4)                           *
*            Level  - Amount to change (-31 to +31)                      *
*                     (lower to higher priority)                         *
* Return:    0    for correct execution                                  *
*            304  for ERROR_INVALID_PDELTA                               *
*            307  for ERROR_INVALID_PCLASS                               *
*            derived from:                                               *
*            result - return code from DosSetPriority                    *
*                                                                        *
*************************************************************************/

LONG APIENTRY SysSetPriority(
  PSZ       name,                      /* Function name                       */

  LONG      numargs,                   /* Number of arguments                 */

  RXSTRING  args[],                    /* Argument array                      */

  PSZ       queuename,                 /* Current queue                       */

  PRXSTRING retstr )                   /* Return RXSTRING                     */

{
  LONG      pclass;                    /* priority class                      */
  LONG      level;                     /* priority level                      */
  APIRET    rc;                        /* creation return code                */

  if (numargs != 2 ||                  /* must have two                       */
      !RXVALIDSTRING(args[0]))         /* first is omitted                    */
    return INVALID_ROUTINE;            /* raise error condition               */
                                       /* get class of change                 */

  if(!string2long(args[0].strptr,&pclass) || /* set the value for pclass      */
     !string2long(args[1].strptr,&level))    /* set the value for level       */
    return INVALID_ROUTINE;

  if ((ULONG)pclass == 0){              /* class 0 -> no change               */
    rc = 0;                             /* no error                           */
  }
                                        /* change the priority                */
                                        /* change according to delta          */
  else if (((ULONG)pclass > 0) && ((ULONG)pclass <= 4)){
    int pid;                            /* PID                                */
    pid = getpid();                     /* current PID                        */

    int priority;                       /* Priority                           */
                                        /* current priority                   */
    priority = getpriority(PRIO_PROCESS, getpid());

                                        /* Set new priority                   */
    setpriority(PRIO_PROCESS, getpid(),-level);
    rc = 0;
  }

  else{
    rc = 307;
    return INVALID_ROUTINE;             /* raise error condition              */
  }

  sprintf(retstr->strptr, "%d", rc);   /* format the return code              */
  retstr->strlength = strlen(retstr->strptr);

  return VALID_ROUTINE;                /* good completion                     */
}



/*************************************************************************
* Function:  SysGetMessage                                               *
*                                                                        *
* Syntax:    call SysGetMessage msgnum [,file] [,str1]...[,str9]         *
*                                                                        *
* Params:    file           - Name of message file to get message from.  *
*                              Default is OSO001.MSG.                    *
*            msgnum         - Number of message being queried.           *
*            str1 ... str9  - Insertion strings.  For messages which     *
*                              contain %1, %2, etc, the str1, str2, etc  *
*                              strings will be inserted (if given).      *
*                                                                        *
* Return:    The message with the inserted strings (if given).           *
* Note:      The set number ist always 1. Therefore the interface        *
*            remains the same as in OS/2 and Win.                        *
*            Reason: keep portability                                    *
*************************************************************************/

LONG APIENTRY SysGetMessage(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG msgnum;                         /* Message number to get      */
  INT setnum = 1;                      /* Set number (const 1)       */
#if defined( HAVE_CATOPEN )
  nl_catd catalog;                     /* catalog handle             */
#endif
                                       /* default error msg          */
  CHAR default_message[] = {"Error: Message catalog not open !\0"};
                                       /* msg not found  msg         */
  CHAR not_found_message[] = {"Error: Message not found !\0"};
                                       /* insertion error  msg       */
  CHAR error_insertions[] = {"Error: Unable to generate message \
                              (wrong insertions)\0"};
                                       /* cat not found  msg         */
  CHAR cat_not_found_message[] = {"Error: Message catalog not found !\0"};
                                       /* catopen not supported      */
  CHAR cat_not_supported_message[] = {"Error: Message catalog (catopen) not supported !\0"};

  PCHAR msg;                           /* msg retrieved from catalog */
  INT icount;                          /* number of insertions       */
  INT msg_length = 0;                  /* length of the return msg   */
  PCHAR msgfile;                       /* name of the message file   */
  PCHAR temp;
  INT count = 0;                       /* number of '%s' in the msg  */


  if (numargs < 1 || numargs > 11 ||   /* validate arguments         */
      !RXVALIDSTRING(args[0]))
    return INVALID_ROUTINE;            /* exit with error            */

                                       /* get message number         */
  if (!string2long(args[0].strptr, &msgnum) || msgnum < 0)
    return INVALID_ROUTINE;            /* exit with error            */

                                       /* Get message file name.     */
                                       /* Use "rexx.cat if not        */
                                       /* given                      */
  if (numargs >= 2 && RXVALIDSTRING(args[1]))
    msgfile = args[1].strptr;          /* use provided message file  */
  else
    msgfile = REXXMESSAGEFILE;

#if defined( HAVE_SETLOCALE )
  setlocale(LC_ALL, "en_US");
#endif

#if defined( HAVE_CATOPEN )
                                       /* open the catalog           */
  if((catalog = catopen(msgfile, NL_CAT_LOCALE)) == (nl_catd)-1){
    retstr->strptr = (PCHAR)malloc(strlen(cat_not_found_message)+1);
    strcpy(retstr->strptr, cat_not_found_message);
    retstr->strlength = strlen(cat_not_found_message);
    return VALID_ROUTINE;
  }

                                       /* retrieve msg from catalog  */
  msg = catgets(catalog, setnum, (INT)msgnum, default_message);

  if(*msg == '\0')                     /* if empty string returned   */
    msg = not_found_message;           /* it means msg not found     */

                                       /* set number of insertions   */
  if (numargs >= 2)
    icount = numargs-2;
  else
    icount = 0;

  /* calculate length of the return message */
  for(int j=2; j < icount+2; j++)
    msg_length += args[j].strlength;
  msg_length += strlen(msg);
  msg_length -= icount*2;

  /* alloc needed space for the return message (add 100 for default msgs)  */
  if(!(retstr->strptr = (PCHAR)malloc(msg_length+100))){
     BUILDRXSTRING(retstr, ERROR_NOMEM);
      catclose(catalog);
      return VALID_ROUTINE;
  }

  /* check for too much '%s' in the message                          */
  temp = msg;
  /* replace all &1..&9 with %s                                         */
  while(temp = strstr(temp, "&")){
    if(isdigit(*(temp+1))){             /* replace &1..&9 ?             */
      *(temp++) = '%';
      *(temp++) = 's';                  /* %s expected                  */
      //      count++;
    }
    else
      temp++;
  }
  /* now look for number of replacement variables                       */
  temp = msg;                            /* reset temp pointer          */
  while(temp = strstr(temp,"%s")){       /* search for the %s           */
    count ++;                            /* increment counter           */
    temp += 2;                           /* jump over %s                */
  }
  if(count > icount)
    icount = 10;                         /* go to error case         */

  /* generate full message with insertions                           */
  switch(icount){
    case(1):{
      if(sprintf(retstr->strptr, msg,args[2].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(2):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(3):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(4):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(5):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(6):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(7):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(8):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr,
                                     args[9].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(9):{
      if(sprintf(retstr->strptr, msg,args[2].strptr,
                                     args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr,
                                     args[9].strptr,
                                     args[10].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(10):{
      strcpy(retstr->strptr, error_insertions); /* error case        */
      break;
    }
    default:{
      strcpy(retstr->strptr, msg);
      break;
    }
  }
  retstr->strlength = strlen(retstr->strptr);/* insert the length    */

  catclose(catalog);                   /* close the catalog          */
  return VALID_ROUTINE;                /* no error on call           */
#else
  retstr->strptr = (PCHAR)malloc(strlen(cat_not_supported_message)+1);
  strcpy(retstr->strptr, cat_not_supported_message);
  retstr->strlength = strlen(cat_not_supported_message);
  return VALID_ROUTINE;
#endif
}



/*************************************************************************
* Function:  SysGetMessageX                                              *
*                                                                        *
* Syntax:    call SysGetMessageX setnum, msgnum [,file] [,str1]...[,str9]*
*                                                                        *
* Params:    file           - Name of message file to get message from.  *
*                              Default is OSO001.MSG.                    *
*            msgnum         - Number of message being queried.           *
*            str1 ... str9  - Insertion strings.  For messages which     *
*                              contain %1, %2, etc, the str1, str2, etc  *
*                              strings will be inserted (if given).      *
*            setnum         - set number in the catalog                  *
*                                                                        *
* Return:    The message with the inserted strings (if given).           *
* Note:      This is a special Unix only version of SysGetMessage which  *
*            supports the selection of a set in the msg catalog.         *
*************************************************************************/

LONG APIENTRY SysGetMessageX(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG msgnum;                         /* Message number to get      */
  LONG setnum;                         /* Set number                 */
#if defined( HAVE_CATOPEN )
  nl_catd catalog;                     /* catalog handle             */
#endif
                                       /* default error msg          */
  CHAR default_message[] = {"Error: Message catalog not open !\0"};
                                       /* msg not found  msg         */
  CHAR not_found_message[] = {"Error: Message not found !\0"};
                                       /* insertion error  msg       */
  CHAR error_insertions[] = {"Error: Unable to generate message \
                              (wrong insertions)\0"};
                                       /* cat not found  msg         */
  CHAR cat_not_found_message[] = {"Error: Message catalog not found !\0"};
                                       /* catopen not supported      */
  CHAR cat_not_supported_message[] = {"Error: Message catalog (catopen) not supported !\0"};

  PCHAR msg;                           /* msg retrieved from catalog */
  INT icount;                          /* number of insertions       */
  INT msg_length = 0;                  /* length of the return msg   */
  PCHAR msgfile;                       /* name of the message file   */
  PCHAR temp;
  INT count = 0;                       /* number of '%s' in the msg  */


  if (numargs < 1 || numargs > 12 ||   /* validate arguments         */
      !RXVALIDSTRING(args[0]) ||
      !RXVALIDSTRING(args[1]))
    return INVALID_ROUTINE;            /* exit with error            */

                                       /* get set number             */
  if (!string2long(args[0].strptr, &setnum) || setnum < 0)
    return INVALID_ROUTINE;            /* exit with error            */

                                       /* get message number         */
  if (!string2long(args[1].strptr, &msgnum) || msgnum < 0)
    return INVALID_ROUTINE;            /* exit with error            */

                                       /* Get message file name.     */
                                       /* Use "rexx.cat if not        */
                                       /* given                      */
  if (numargs >= 3 && RXVALIDSTRING(args[1]))
    msgfile = args[2].strptr;          /* use provided message file  */
  else
    msgfile = REXXMESSAGEFILE;

#if defined( HAVE_CATOPEN )
                                       /* open the catalog           */
  if((catalog = catopen(msgfile, NL_CAT_LOCALE)) == (nl_catd)-1){
    retstr->strptr = (PCHAR)malloc(strlen(cat_not_found_message)+1);
    strcpy(retstr->strptr, cat_not_found_message);
    retstr->strlength = strlen(cat_not_found_message);
    return VALID_ROUTINE;
  }

                                       /* retrieve msg from catalog  */
  msg = catgets(catalog, (INT)setnum, (INT)msgnum, default_message);

  if(*msg == '\0')                     /* if empty string returned   */
    msg = not_found_message;           /* it means msg not found     */

                                       /* set number of insertions   */
  if (numargs >= 3)
    icount = numargs-3;
  else
    icount = 0;

  /* calculate length of the return message */
  for(int j=3; j < icount+3; j++)
    msg_length += args[j].strlength;
  msg_length += strlen(msg);
  msg_length -= icount*2;

  /* alloc needed space for the return message (add 100 for default msgs)  */
  if(!(retstr->strptr = (PCHAR)malloc(msg_length+100))){
     BUILDRXSTRING(retstr, ERROR_NOMEM);
      catclose(catalog);
      return VALID_ROUTINE;
  }

  /* check for to much '%s' in the message                           */
  temp = msg;
  /* replace all &1..&9 with %s                                         */
  while(temp = strstr(temp, "&")){
    if(isdigit(*(temp+1))){             /* replace &1..&9 ?             */
      *(temp++) = '%';
      *(temp++) = 's';                  /* %s expected                  */
    }
    else
      temp++;
  }
  /* now look for number of replacement variables                       */
  temp = msg;                            /* reset temp pointer          */
  while(temp = strstr(temp,"%s")){       /* search for the %s           */
    count++;                             /* increment counter           */
    temp += 2;                           /* jump over %s                */
  }

  if(count > icount)
    icount = 10;                         /* go to error case         */

  /* generate full message with insertions                           */
  switch(icount){
    case(1):{
      if(sprintf(retstr->strptr, msg,args[3].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(2):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(3):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(4):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(5):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(6):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(7):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr,
                                     args[9].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(8):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr,
                                     args[9].strptr,
                                     args[10].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(9):{
      if(sprintf(retstr->strptr, msg,args[3].strptr,
                                     args[4].strptr,
                                     args[5].strptr,
                                     args[6].strptr,
                                     args[7].strptr,
                                     args[8].strptr,
                                     args[9].strptr,
                                     args[10].strptr,
                                     args[11].strptr) != msg_length)
        strcpy(retstr->strptr, error_insertions);
      break;
    }
    case(10):{
      strcpy(retstr->strptr, error_insertions); /* error case        */
      break;
    }
    default:{
      strcpy(retstr->strptr, msg);
      break;
    }
  }
  retstr->strlength = strlen(retstr->strptr);/* insert the length    */

  catclose(catalog);                   /* close the catalog          */
  return VALID_ROUTINE;                /* no error on call           */
#else
  retstr->strptr = (PCHAR)malloc(strlen(cat_not_supported_message)+1);
  strcpy(retstr->strptr, cat_not_supported_message);
  retstr->strlength = strlen(cat_not_supported_message);
  return VALID_ROUTINE;
#endif
}



/*************************************************************************
* Function:  SysGetKey                                                   *
*                                                                        *
* Syntax:    call SysGetKey [echo]                                       *
*                                                                        *
* Params:    echo - Either of the following:                             *
*                    'ECHO'   - Echo the inputted key (default).         *
*                    'NOECHO' - Do not echo the inputted key.            *
*                                                                        *
* Return:    The key striked.                                            *
*************************************************************************/

LONG APIENTRY SysGetKey(
 PSZ       name,                       /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  BOOL      echo = TRUE;               /* Set to FALSE if we         */
                                       /* shouldn't echo             */
  RexxMutex *mutex;                    /* serialization semaphore    */

  mutex = &SysGetKeySemaphore;
  mutex->request();                    /* request the seamphore      */

  if (numargs > 1)                     /* too many arguments         */
    return INVALID_ROUTINE;            /* raise an error             */

  if (numargs == 1) {                  /* validate arguments         */
    if (!rxstricmp(args[0].strptr, "NOECHO"))
      echo = FALSE;
    else if (rxstricmp(args[0].strptr, "ECHO"))
      return INVALID_ROUTINE;          /* Invalid option             */
  }

  getkey(retstr->strptr,echo);         /* call the complicated part  */
  mutex->release();                    /* release the seamphore      */
  retstr->strlength = strlen(retstr->strptr); /* format string       */

  return VALID_ROUTINE;                /* no error on call           */
}


#ifdef AIX
/*************************************************************************
* Function:  SysAddFuncPkg                                               *
*                                                                        *
* Description:   Function to enable load of old CREXX libraries for AIX. *
*                The Path must be fully qualified in REXX procedure,     *
*                it is used to select the old >load< function call.      *
*                                                                        *
* Syntax:    call SysAddFuncPkg ( /Fully_qualified_path/Package_name )   *
*                                                                        *
* Params:    none                                                        *
*                                                                        *
* Return:    null string                                                 *
*************************************************************************/

LONG APIENTRY SysAddFuncPkg(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG   rc = NULL;
  INT    j;                            /* Counter                    */
  LONG   arglength;                    /* length of the count        */
  PCHAR  argstring;                    /* input sleep time           */
  RXFUNCBLOCK *funcblock;              /* Base for function blocks   */
  PRXINITFUNCPKG InitFunc;             /* Pointer returned from load */

  retstr->strlength = 0;               /* set return value           */
                                       /* check arguments            */
  if (numargs != 1)                    /* Must have one argument     */
    return INVALID_ROUTINE;

  argstring = args[0].strptr;             /* point to the string        */
  arglength = args[0].strlength;          /* get length of string       */
  if ( (arglength == 0 ) ||               /* if null string             */
       (arglength >= MAXNAME) ||          /* or too long                */
       (!strchr( argstring, '/' )) )
    return INVALID_ROUTINE;               /* not valid                  */

  if (!(InitFunc = (PRXINITFUNCPKG)load(argstring,0,NULL)))
  {                                          /*  loadAndInit? for load  */
    if ( InitFunc == NULL ) {
      fprintf(stderr, " *** Unable to load library %s !\nError message: errno = %d;",\
               argstring, errno);
      perror(" REXXUTIL");
      rc = 1;
    }
  }
  if ( rc == NULL ) {
    /* Call the initialization routine for the library (which should */
    /* be the function pointer returned to us by load).              */
    rc = (*InitFunc)(&funcblock);
    if (rc) {                          /* If routine indicates error,*/
                                       /* tell the user.             */
      fprintf(stderr,"*** Library load routine gave error %d.\n",rc);
      return(rc);                      /* don't load anything        */
    } /* endif */

    /* Now run through the array of func blocks, adding them to the  */
    /* list of external functions or subcommand handlers.  Note that */
    /* we use the external function types in all cases, but since    */
    /* the only thing affected is the function pointers, there's no  */
    /* problem - the RXFUNCBLOCK and RXSUBCOMBLOCK types are         */
    /* otherwise identical.                                          */
    for (j=0; funcblock[j].name != NULL; j++) {
#ifdef ORXLD_DEBUG
        fprintf(stderr,"REXXUTIL: PKGFunction %s \n", funcblock[j].name);
#endif
        if ( funcblock[j].function && (rc == NULL) ) {
          RexxRegisterFunctionDll( funcblock[j].name,
                                   argstring, funcblock[j].name);
        }
    } /* endfor */
  }
  return VALID_ROUTINE;
}

/*************************************************************************
* Function:  SysAddCmdPkg    like SysAddFuncPkg                          *
*                                                                        *
*************************************************************************/
LONG APIENTRY SysAddCmdPkg(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
 LONG lRc;

 lRc = SysAddFuncPkg(
                        name,          /* Function name              */
                        numargs,       /* Number of arguments        */
                        args,          /* Argument array             */
                        queuename,     /* Current queue              */
                        retstr );      /* Return RXSTRING            */

  return lRc;
}

/*************************************************************************
* Function:  SysDropFuncPkg                                              *
*                                                                        *
* Description:   Function to enable load of old CREXX libraries for AIX. *
*                It is used for the old >load< function call for the     *
*                list of function to be dropped from REXX.               *
*                The Path must not be fully qualified in REXX procedure. *
*                                                                        *
* Syntax:    call SysDropFuncPkg                                         *
*                                                                        *
* Return:    NO_UTIL_ERROR - Successful.                                 *
*************************************************************************/

LONG APIENTRY SysDropFuncPkg(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG   rc = NULL;
  INT    j;                            /* Counter                    */
  LONG   arglength;                    /* length of the count        */
  PCHAR  argstring;                    /* input sleep time           */
  RXFUNCBLOCK *funcblock;              /* Base for function blocks   */
  PRXINITFUNCPKG InitFunc;             /* Pointer returned from load */

  retstr->strlength = 0;               /* set return value           */
                                       /* check arguments            */
  if (numargs != 1)                    /* Must have one argument     */
    return INVALID_ROUTINE;

  argstring = args[0].strptr;             /* point to the string        */
  arglength = args[0].strlength;          /* get length of string       */
  if ( (arglength == 0 ) ||               /* if null string             */
       (arglength >= MAXNAME) )           /* or too long                */
    return INVALID_ROUTINE;               /* not valid                  */

  if (!(InitFunc = (PRXINITFUNCPKG)load(argstring,0,NULL)))
  {                                       /*  loadAndInit? for load     */
    if ( InitFunc == NULL ) {
      fprintf(stderr, " *** Unable to drop library %s !\nError message: errno = %d;",\
               argstring, errno);
      perror(" REXXUTIL");
      rc = 1;
    }
  }
  if ( rc == NULL ) {
    /* Call the initialization routine for the library (which should */
    /* be the function pointer returned to us by load).              */
    rc = (*InitFunc)(&funcblock);
    if (rc) {                          /* If routine indicates error,*/
                                       /* tell the user.             */
      fprintf(stderr," *** Library drop routine gave error %d.\n",rc);
      return(rc);                      /* don't load anything        */
    } /* endif */

    /* Now run through the array of func blocks, adding them to the  */
    /* list of external functions or subcommand handlers.  Note that */
    /* we use the external function types in all cases, but since    */
    /* the only thing affected is the function pointers, there's no  */
    /* problem - the RXFUNCBLOCK and RXSUBCOMBLOCK types are         */
    /* otherwise identical.                                          */
    for (j=0; funcblock[j].name != NULL; j++) {
#ifdef ORXLD_DEBUG
        fprintf(stderr,"REXXUTIL: PKGFunction %s \n", funcblock[j].name);
#endif
        if ( funcblock[j].function && (rc == NULL) ) {
          RexxDeregisterFunction( funcblock[j].name );
        }
    } /* endfor */
  }
  return VALID_ROUTINE;                /* no error on call           */
}

/*************************************************************************
* Function:  SysDropCmdPkg    like SysDropFuncPkg                        *
*                                                                        *
*************************************************************************/
LONG APIENTRY SysDropCmdPkg(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
 LONG lRc;

 lRc = SysDropFuncPkg(
                        name,          /* Function name              */
                        numargs,       /* Number of arguments        */
                        args,          /* Argument array             */
                        queuename,     /* Current queue              */
                        retstr );      /* Return RXSTRING            */

  return lRc;
}

/*************************************************************************
* Function:  SysGetpid                                                   *
*                                                                        *
* Description:   Function to migrate CREXX for AIX procedures.           *
*                                                                        *
* Syntax:    call SysGetpid()                                            *
*                                                                        *
* Return:    Process_ID                                                  *
*************************************************************************/

LONG APIENTRY SysGetpid(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  retstr->strlength = 0;               /* set return value           */
                                       /* check arguments            */
  if (numargs != 0)                    /* Must have no  argument     */
    return INVALID_ROUTINE;
  else
  {
    sprintf(retstr->strptr, "%d", getpid());
    retstr->strlength = strlen(retstr->strptr);
  }
  return VALID_ROUTINE;                /* no error on call           */
}
#endif                                 /* CREXX funcs                */

/*************************************************************************
* Function:  SysFork                                                     *
*                                                                        *
* Description:   Function to migrate CREXX for AIX procedures.           *
*                                                                        *
* Syntax:    call SysFork()                                              *
*                                                                        *
* Return:    Process_ID   ( to parent child''s ID / to child the ID 0 )  *
*************************************************************************/

LONG APIENTRY SysFork(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  retstr->strlength = 0;               /* set return value           */
                                       /* check arguments            */
  if (numargs != 0)                    /* Must have no  argument     */
    return INVALID_ROUTINE;
  else
  {
    sprintf(retstr->strptr, "%d", fork());
    retstr->strlength = strlen(retstr->strptr);
  }
  return VALID_ROUTINE;                /* no error on call           */
}

/*************************************************************************
* Function:  SysWait                                                     *
*                                                                        *
* Description:   Function to migrate CREXX for AIX procedures.           *
*                                                                        *
* Syntax:    call SysWait()                                              *
*                                                                        *
* Return:    exit code of child                                          *
*************************************************************************/

LONG APIENTRY SysWait(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  int iStatus;
  retstr->strlength = 0;               /* set return value           */
                                       /* check arguments            */
  if (numargs != 0)                    /* Must have no  argument     */
    return INVALID_ROUTINE;
  else
  {
    wait( &iStatus );
    sprintf(retstr->strptr, "%d", iStatus);
    retstr->strlength = strlen(retstr->strptr);
  }
  return VALID_ROUTINE;                /* no error on call           */
}

/*************************************************************************
* Function:  SysCreatePipe                                               *
*                                                                        *
* Description:   Function to migrate CREXX for AIX procedures.           *
*                Function creates an unnamed pipe                        *
*                                                                        *
* Syntax:    call SysCreatePipe( Blocking | Nonblocking )                *
*                                                                        *
* Return:    'handle handle'     ( handle for read and handle for write )*
*************************************************************************/

LONG APIENTRY SysCreatePipe(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  int  iStatus;
  int  iaH[2];
  char cBlocking;
  retstr->strlength = 0;                     /* set return value           */
                                             /* check arguments ---------- */
  if (numargs > 1)                           /* More than one arg?         */
    return INVALID_ROUTINE;
  if (numargs == 0 )                         /* No arg?                    */
    cBlocking = 1;                           /* Default is blocking        */
  /* One arg, first char is 'b'?    */
  else if (args[0].strptr[0] == 'b' || args[0].strptr[0] == 'B')
    cBlocking = 1;                            /* Wants blocking             */
  /* One arg, first char is 'n'?    */
  else if (args[0].strptr[0] == 'n' || args[0].strptr[0] == 'N')
    cBlocking = 0;                            /* Wants non-blocking         */

  if (pipe(iaH))                             /* Create the pipe            */
  {
    perror("*** ERROR: Creating pipe");      /* pipe creation failed       */
    return VALID_ROUTINE;                    /* no error on call           */
  }
  if (!cBlocking)                            /* Non-blocking?              */
  {
    /* Get file status flags ---------- */
    iStatus = fcntl(iaH[0], F_GETFL, NULL);
    iStatus |= O_NONBLOCK;                   /* Turn on NONBLOCK flag      */
    /* Does set work? ----------------- */
    if (fcntl(iaH[0], F_SETFL, iStatus) == -1) {
      perror("*** ERROR: Setting NONBLOCK flag");  /* No, tell user        */
      close(iaH[0]); close(iaH[1]);                /* Close pipes          */
      return VALID_ROUTINE;                  /* no error on call           */
    }
  }
  sprintf(retstr->strptr, "%d %d", iaH[0], iaH[1]);/* Create return string */
  retstr->strlength = strlen(retstr->strptr);

  return VALID_ROUTINE;                      /* no error on call           */
}

//#endif



/*************************************************************************
* Function:  SysDumpVariables                                            *
*                                                                        *
* Syntax:    result = SysDumpVariables([filename])                       *
*                                                                        *
* Params:    filename - name of the file where variables are appended to *
*                       (dump is written to stdout if omitted)           *
*                                                                        *
* Return:    0 - dump completed OK                                       *
*            -1 - failure during dump                                     *
*************************************************************************/

LONG APIENTRY SysDumpVariables(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG      rc;                        /* Ret code                   */
  SHVBLOCK  shvb;
  int       handle;
  BOOL      fCloseFile = FALSE;

  if ( (numargs > 1) ||                /* wrong number of arguments? */
       ((numargs > 0) && !RXVALIDSTRING(args[0])) )
    return INVALID_ROUTINE;            /* raise error condition      */

  if (numargs > 0)
  {
    /* open output file for append */
    fCloseFile = TRUE;

    handle = open(args[0].strptr, O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH);
    if(handle < 0)
        return INVALID_ROUTINE;            /* raise error condition      */
  }
  else
      handle = STDOUT_FILENO;

  do
  {
    /* prepare request block */
    shvb.shvnext = NULL;
    shvb.shvname.strptr = NULL;      /* let REXX allocate the memory */
    shvb.shvname.strlength = 0;
    shvb.shvnamelen = 0;
    shvb.shvvalue.strptr = NULL;     /* let REXX allocate the memory */
    shvb.shvvalue.strlength = 0;
    shvb.shvvaluelen = 0;
    shvb.shvcode = RXSHV_NEXTV;
    shvb.shvret = 0;

    rc = RexxVariablePool(&shvb);

    if (rc == RXSHV_OK)
    {


      write(handle, "Name=", strlen("Name="));
      write(handle, shvb.shvname.strptr, shvb.shvname.strlength);
      write(handle, ", Value='", 9);
      write(handle, shvb.shvvalue.strptr,shvb.shvvalue.strlength);
      write(handle, "'\n", 2);

      /* free memory allocated by REXX */
      free(shvb.shvname.strptr);
      free(shvb.shvvalue.strptr);

      /* leave loop if this was the last var */
      if (shvb.shvret & RXSHV_LVAR)
        break;
    }
  } while (rc == RXSHV_OK);

  if (fCloseFile)
     close(handle);          /* close the file             */

/*if (rc != RXSHV_OK)       */
  if (rc != RXSHV_LVAR)
    RETVAL(-1)
  else
    RETVAL(0)
}

/*************************************************************************
* Function:  SysGetFileDateTime                                          *
*                                                                        *
* Syntax:    result = SysGetFileDateTime(filename [,timesel])            *
* Params:    filename - name of the file to query                        *
*            timesel  - What filetime to query: Access/Write             *
*                                                                        *
* Return:    -1 - file date/time query failed                            *
*            other - date and time as YYYY-MM-DD HH:MM:SS                *
*************************************************************************/

LONG APIENTRY SysGetFileDateTime(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG      rc;                        /* Ret code                   */
  struct    stat buf;
  struct    tm *newtime;
  PCHAR     dir_buf = NULL;            /* full directory path        */
  BOOL      fOk = TRUE;
  BOOL      alloc_Flag = FALSE;

  if ( (numargs < 1) || (numargs > 2) ||
       ((numargs == 2) && !RXVALIDSTRING(args[1])) )
    return INVALID_ROUTINE;            /* raise error condition      */

  if(*(args[0].strptr) == '~')
  {
    dir_buf = resolve_tilde(args[0].strptr);
    alloc_Flag = TRUE;
  }
  else
  {
    dir_buf = args[0].strptr;
  }

  if (stat(dir_buf, &buf) < 0)
  {
     fOk = FALSE;
  }

  if(fOk)
  {
     if (numargs > 1)
     {
       switch (args[1].strptr[0])
       {
         case 'a':
         case 'A':
           newtime = localtime(&(buf.st_atime));
           break;
         case 'w':
         case 'W':
           newtime = localtime(&(buf.st_mtime));

           break;
         default:
           return INVALID_ROUTINE;
       }
     }
     else
         newtime = localtime(&(buf.st_mtime));

     newtime->tm_year += 1900;
     newtime->tm_mon += 1;

     sprintf(retstr->strptr, "%4d-%02d-%02d %02d:%02d:%02d",
             newtime->tm_year,
             newtime->tm_mon,
             newtime->tm_mday,
             newtime->tm_hour,
             newtime->tm_min,
             newtime->tm_sec);
             retstr->strlength = strlen(retstr->strptr);
  }
  if( (dir_buf) && (alloc_Flag == TRUE) )
    free(dir_buf);                         /* free the buffer memory  */
  if (!fOk)
    RETVAL(-1)
  else
    return VALID_ROUTINE;
}

/*************************************************************************
* Function:  SysSetFileDateTime                                          *
*                                                                        *
* Syntax:    result = SysSetFileDateTime(filename [,newdate] [,newtime]) *
*                                                                        *
* Params:    filename - name of the file to update                       *
*            newdate  - new date to set in format YYYY-MM-DD (YYYY>1800) *
*            newtime  - new time to set in format HH:MM:SS               *
*                                                                        *
* Return:    0 - file date/time was updated correctly                    *
*            -1 - failure attribute update                               *
*************************************************************************/

LONG APIENTRY SysSetFileDateTime(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  LONG      rc;                        /* Ret code                   */
  BOOL      fOk = TRUE;
  BOOL      fCloseFile = FALSE;
  struct utimbuf timebuf;
  struct tm *newtime;
  time_t ltime;
  struct stat buf;
  PCHAR  dir_buf = NULL;
  BOOL      alloc_Flag = FALSE;

  /* we expect one to three parameters, if three parameters are      */
  /* specified then the second may be omitted to set only a new time,*/
  /* if only one is specified then the file is set to current time   */

  if ( (numargs < 1) || (numargs > 3) ||
       ((numargs == 2) && !RXVALIDSTRING(args[1])) ||
       ((numargs == 3) && !RXVALIDSTRING(args[2])) )
    return INVALID_ROUTINE;            /* raise error condition      */

  if(*(args[0].strptr) == '~')
  {
    dir_buf = resolve_tilde(args[0].strptr);
    alloc_Flag = TRUE;
  }
  else
  {
    dir_buf = args[0].strptr;
  }

  if (stat(dir_buf, &buf) < 0)
  {
     fOk =  FALSE;
  }

  if (numargs == 1)
  {
    time(&ltime);
    timebuf.modtime = ltime;
    if (utime(dir_buf, &timebuf) < 0)
    {
       fOk = FALSE;
    }
  }
  else
  {
    newtime = localtime(&(buf.st_mtime));
    if ((numargs >= 2) && RXVALIDSTRING(args[1]))
    {

       /* parse new date */
       if (sscanf(args[1].strptr, "%4d-%2d-%2d", &newtime->tm_year,
                  &newtime->tm_mon, &newtime->tm_mday) != 3)
       fOk = FALSE;
       newtime->tm_year -= 1900;
       newtime->tm_mon -= 1;
    }
    if ((numargs == 3) && RXVALIDSTRING(args[2]))
    {
       /* parse new time */
       if (sscanf(args[2].strptr, "%2d:%2d:%2d", &newtime->tm_hour,
                  &newtime->tm_min, &newtime->tm_sec) != 3)
            fOk = FALSE;
    }
    ltime = mktime(newtime);
    timebuf.modtime = ltime;
/*  if (utime(args[0].strptr, &timebuf) < 0)           */
    if (utime(dir_buf, &timebuf) < 0)
    {
       fOk = FALSE;
    }
  }

  if( (dir_buf) && (alloc_Flag == TRUE) )
    free(dir_buf);                         /* free the buffer memory  */
  if (fOk)
    RETVAL(0)
  else
    RETVAL(-1)
}


/*-------------------------------------------------------------------*/

/*********************************************************************/
/*                                                                   */
/*   Subroutine Name:   rxstrnicmp                                   */
/*                                                                   */
/*   Descriptive Name:  case insensitive string compare              */
/*                                                                   */
/*   Entry Point:       rxstrnicmp                                   */
/*                                                                   */
/*   Input:             pointers to two ASCII strings                */
/*                                                                   */
/*********************************************************************/
int rxstrnicmp(
  PSZ       s1,                        /* first string location      */
  PSZ       s2,                        /* second string location     */
  ULONG     count)
{

  int i = 0;

  while ( 1 ) {
    if ( ( tolower(*s1) != tolower(*s2) ) || !*s1 )
      break;
    ++s1;
    ++s2;
    i++;
    if (i > count)
       break;
  }
  return ( (INT)tolower(*s1) - (INT)tolower(*s2) );
}

int compare_asc(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  return (strcmp(rxArg1->strptr, rxArg2->strptr));
}

int compare_asc_cols(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  if ( (ulStartCol < rxArg1->strlength) && (ulStartCol < rxArg2->strlength) )
  {
    return (strncmp(rxArg1->strptr+ulStartCol,
                    rxArg2->strptr+ulStartCol, ulCompLength));
  }
  else
  {
    if (rxArg1->strlength == rxArg2->strlength)
      return 0;
    else
      return (rxArg1->strlength < rxArg2->strlength) ? -1 : 1;
  } /* endif */
}

int compare_asc_i(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  return (stricmp(rxArg1->strptr, rxArg2->strptr));
}

int compare_asc_i_cols(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  if ( (ulStartCol < rxArg1->strlength) && (ulStartCol < rxArg2->strlength) )
  {
  return (rxstrnicmp(rxArg1->strptr+ulStartCol,
                    rxArg2->strptr+ulStartCol, ulCompLength));

  }
  else
  {
    if (rxArg1->strlength == rxArg2->strlength)
      return 0;
    else
      return (rxArg1->strlength < rxArg2->strlength) ? -1 : 1;
  } /* endif */
}

int compare_asc_num(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  return (stricmp(rxArg1->strptr, rxArg2->strptr));
}

int compare_asc_num_cols(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  if ( (ulStartCol < rxArg1->strlength) && (ulStartCol < rxArg2->strlength) )
  {
    return (rxstrnicmp(rxArg1->strptr+ulStartCol,
                    rxArg2->strptr+ulStartCol, ulCompLength));
  }
  else
  {
    if (rxArg1->strlength == rxArg2->strlength)
      return 0;
    else
      return (rxArg1->strlength < rxArg2->strlength) ? -1 : 1;
  } /* endif */
}

int compare_desc(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  return (-strcmp(rxArg1->strptr, rxArg2->strptr));
}

int compare_desc_cols(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  if ( (ulStartCol < rxArg1->strlength) && (ulStartCol < rxArg2->strlength) )
  {
    return (-strncmp(rxArg1->strptr+ulStartCol,
                     rxArg2->strptr+ulStartCol, ulCompLength));
  }
  else
  {
    if (rxArg1->strlength == rxArg2->strlength)
      return 0;
    else
      return (rxArg1->strlength > rxArg2->strlength) ? -1 : 1;
  } /* endif */
}

int compare_desc_i(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  return (-stricmp(rxArg1->strptr, rxArg2->strptr));
}

int compare_desc_i_cols(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  if ( (ulStartCol < rxArg1->strlength) && (ulStartCol < rxArg2->strlength) )
  {
    return (-rxstrnicmp(rxArg1->strptr+ulStartCol,
                      rxArg2->strptr+ulStartCol, ulCompLength));
  }
  else
  {
    if (rxArg1->strlength == rxArg2->strlength)
      return 0;
    else
      return (rxArg1->strlength > rxArg2->strlength) ? -1 : 1;
  } /* endif */
}

int compare_desc_num(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  return (-stricmp(rxArg1->strptr, rxArg2->strptr));
}

int compare_desc_num_cols(const void *arg1, const void *arg2)
{
  PRXSTRING     rxArg1 = (PRXSTRING)arg1;
  PRXSTRING     rxArg2 = (PRXSTRING)arg2;

  if ( (ulStartCol < rxArg1->strlength) && (ulStartCol < rxArg2->strlength) )
  {
    return (-rxstrnicmp(rxArg1->strptr+ulStartCol,
                      rxArg2->strptr+ulStartCol, ulCompLength));
  }
  else
  {
    if (rxArg1->strlength == rxArg2->strlength)
      return 0;
    else
      return (rxArg1->strlength > rxArg2->strlength) ? -1 : 1;
  } /* endif */
}

APIRET APIENTRY RexxStemSort(PCHAR stemname, INT order, INT type,
    size_t start, size_t end, size_t firstcol, size_t lastcol);

/*************************************************************************
* Function:  SysStemSort                                                 *
*                                                                        *
* Syntax:    result = SysStemSort(stem, order, type, start, end,         *
*                                 firstcol, lastcol)                     *
*                                                                        *
* Params:    stem - name of stem to sort                                 *
*            order - 'A' or 'D' for sort order                           *
*            type - 'C', 'I', 'N' for comparision type                   *
*            start - first index to sort                                 *
*            end - last index to sort                                    *
*            firstcol - first column to use as sort key                  *
*            lastcol - last column to use as sort key                    *
*                                                                        *
* Return:    0 - sort was successful                                     *
*            -1 - sort failed                                            *
*************************************************************************/

LONG APIENTRY SysStemSort(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */

{
    CHAR          stemName[255];
    size_t        first = 1;
    size_t        last = ULONG_MAX;
    size_t        firstCol = 0;
    size_t        lastCol = ULONG_MAX;
    INT           sortType = SORT_CASESENSITIVE;
    INT           sortOrder = SORT_ASCENDING;

    if ( (numargs < 1) || (numargs > 7) || /* validate arguments       */
        !RXVALIDSTRING(args[0]))
      return INVALID_ROUTINE;

    /* remember stem name */
    memset(stemName, 0, sizeof(stemName));
    strcpy(stemName, args[0].strptr);
    if (stemName[args[0].strlength-1] != '.')
      stemName[args[0].strlength] = '.';

    /* check other parameters */
    if ((numargs >= 2) && RXVALIDSTRING(args[1])) /* sort order */
    {
      switch (args[1].strptr[0])
      {
        case 'A':
        case 'a':
          sortOrder = SORT_ASCENDING;
          break;
        case 'D':
        case 'd':
          sortOrder = SORT_DECENDING;
          break;
        default:
          return INVALID_ROUTINE;
      } /* endswitch */
    } /* endif */

    if ((numargs >= 3) && RXVALIDSTRING(args[2])) /* sort type */
    {
      switch (args[2].strptr[0])
      {
        case 'C':
        case 'c':
          sortType = SORT_CASESENSITIVE;
          break;
        case 'I':
        case 'i':
          sortType = SORT_CASEIGNORE;
          break;
        default:
          return INVALID_ROUTINE;
      } /* endswitch */
    } /* endif */

    if ((numargs >= 4) && RXVALIDSTRING(args[3])) /* first element to sort */
    {
      if (sscanf(args[3].strptr, "%ld", &first) != 1)
        return INVALID_ROUTINE;
      if (first == 0)
        return INVALID_ROUTINE;
    } /* endif */

    if ((numargs >= 5) && RXVALIDSTRING(args[4])) /* last element to sort */
    {
      if (sscanf(args[4].strptr, "%ld", &last) != 1)
        return INVALID_ROUTINE;
      if (last < first)
        return INVALID_ROUTINE;
    } /* endif */

    if ((numargs >= 6) && RXVALIDSTRING(args[5])) /* first column to sort */
    {
      if (sscanf(args[5].strptr, "%ld", &firstCol) != 1)
        return INVALID_ROUTINE;
      firstCol--;
    } /* endif */

    if ((numargs == 7) && RXVALIDSTRING(args[6])) /* last column to sort */
    {
      if (sscanf(args[6].strptr, "%ld", &lastCol) != 1)
        return INVALID_ROUTINE;
      lastCol--;
      if (lastCol < firstCol)
        return INVALID_ROUTINE;

    } /* endif */

    /* the sorting is done in the interpreter */
    if (!RexxStemSort(stemName, sortOrder, sortType, first, last, firstCol, lastCol)) {
        sprintf(retstr->strptr, "-1");
        retstr->strlength = 2;
        return INVALID_ROUTINE;
    }

    sprintf(retstr->strptr, "0");
    retstr->strlength = 1;
    return VALID_ROUTINE;
}


/*************************************************************************
* Function:  SysStemDelete                                               *
*                                                                        *
* Syntax:    result = SysStemDelete(stem, startitem [,itemcount])        *
*                                                                        *
* Params:    stem - name of stem where item will be deleted              *
*            startitem - index of item to delete                         *
*            itemcount - number of items to delete if more than 1        *
*                                                                        *
* Return:    0 - delete was successful                                   *
*            -1 - delete failed                                          *
*************************************************************************/

LONG APIENTRY SysStemDelete(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  APIRET        rc;
  CHAR          szStemName[255];
  PSZ           pszStemIdx;
  CHAR          szValue[255];
  SHVBLOCK      shvb;
  ULONG         ulIdx;
  ULONG         ulFirst;
  ULONG         ulItems = 1;
  ULONG         ulCount;
  BOOL          fOk = TRUE;

  if ( (numargs < 2) || (numargs > 3) || /* validate arguments       */
      !RXVALIDSTRING(args[0]) || !RXVALIDSTRING(args[1]) ||
      ((numargs == 3) && !RXVALIDSTRING(args[2])) )
    return INVALID_ROUTINE;

  /* remember stem name */
  memset(szStemName, 0, sizeof(szStemName));
  strcpy(szStemName, args[0].strptr);
  if (szStemName[args[0].strlength-1] != '.')
    szStemName[args[0].strlength] = '.';
  pszStemIdx = &(szStemName[strlen(szStemName)]);

  /* get item index to be deleted */
  if (sscanf(args[1].strptr, "%ld", &ulFirst) != 1)
    return INVALID_ROUTINE;

  /* get number of items to delete */
  if (numargs == 3)
  {
    if (sscanf(args[2].strptr, "%ld", &ulItems) != 1)
      return INVALID_ROUTINE;
    if (ulItems == 0)
      return INVALID_ROUTINE;
  } /* endif */

  /* retrieve the number of elements in stem */
  strcpy(pszStemIdx, "0");
  shvb.shvnext = NULL;
  shvb.shvname.strptr = szStemName;
  shvb.shvname.strlength = strlen((const char *)szStemName);
  shvb.shvvalue.strptr = szValue;
  shvb.shvvalue.strlength = sizeof(szValue);
  shvb.shvnamelen = shvb.shvname.strlength;
  shvb.shvvaluelen = shvb.shvvalue.strlength;
  shvb.shvcode = RXSHV_SYFET;
  shvb.shvret = 0;
  if (RexxVariablePool(&shvb) == RXSHV_OK)
  {
    /* index retrieved fine */
    if (sscanf(shvb.shvvalue.strptr, "%ld", &ulCount) != 1)
      return INVALID_ROUTINE;

    /* check wether supplied index and count is within limits */
    if (ulFirst + ulItems - 1 > ulCount)
      return INVALID_ROUTINE;

    /* now copy the remaining indices up front */
    for (ulIdx = ulFirst; ulIdx + ulItems <= ulCount; ulIdx++)
    {
      /* get element to relocate */
      sprintf(pszStemIdx, "%ld", ulIdx + ulItems);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szStemName;
      shvb.shvname.strlength = strlen((const char *)szStemName);
      shvb.shvvalue.strptr = NULL;
      shvb.shvvalue.strlength = 0;
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYFET;
      shvb.shvret = 0;

      if (RexxVariablePool(&shvb) == RXSHV_OK)
      {
        sprintf(pszStemIdx, "%ld", ulIdx);
        shvb.shvnext = NULL;
        shvb.shvname.strptr = szStemName;
        shvb.shvname.strlength = strlen((const char *)szStemName);
        shvb.shvnamelen = shvb.shvname.strlength;
        shvb.shvvaluelen = shvb.shvvalue.strlength;
        shvb.shvcode = RXSHV_SYSET;
        shvb.shvret = 0;
        rc = RexxVariablePool(&shvb);
        if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
          fOk = FALSE;

        /* free memory allocated by REXX */
        free(shvb.shvvalue.strptr);
      }
      else
        fOk = FALSE;

      if (!fOk)
        break;
    } /* endfor */

    if (fOk)
    {
      /* now delete the items at the end */
      for (ulIdx = ulCount - ulItems + 1; ulIdx <= ulCount; ulIdx++)
      {
        sprintf(pszStemIdx, "%ld", ulIdx);
        shvb.shvnext = NULL;
        shvb.shvname.strptr = szStemName;
        shvb.shvname.strlength = strlen((const char *)szStemName);
        shvb.shvvalue.strptr = NULL;
        shvb.shvvalue.strlength = 0;
        shvb.shvnamelen = shvb.shvname.strlength;
        shvb.shvvaluelen = shvb.shvvalue.strlength;
        shvb.shvcode = RXSHV_SYDRO;
        shvb.shvret = 0;
        if (RexxVariablePool(&shvb) != RXSHV_OK)
        {
          fOk = FALSE;
          break;
        } /* endif */
      } /* endfor */
    } /* endif */

    if (fOk)
    {
      /* set the new number of items in the stem array */
      strcpy(pszStemIdx, "0");
      sprintf(szValue, "%ld", ulCount - ulItems);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szStemName;
      shvb.shvname.strlength = strlen((const char *)szStemName);
      shvb.shvvalue.strptr = szValue;
      shvb.shvvalue.strlength = strlen(szValue);
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYSET;
      shvb.shvret = 0;
      rc = RexxVariablePool(&shvb);
      if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
        fOk = FALSE;
    } /* endif */
  }
  else
  {
    fOk = FALSE;
  } /* endif */

  if (fOk)
    RETVAL(0)
  else
    RETVAL(-1)
}


/*************************************************************************
* Function:  SysStemInsert                                               *
*                                                                        *
* Syntax:    result = SysStemInsert(stem, position, value)               *
*                                                                        *
* Params:    stem - name of stem where item will be inserted             *
*            position - index where new item will be inserted            *
*            value - new item value                                      *
*                                                                        *
* Return:    0 - insert was successful                                   *
*            -1 - insert failed                                          *
*************************************************************************/

LONG APIENTRY SysStemInsert(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  APIRET        rc;
  CHAR          szStemName[255];
  PSZ           pszStemIdx;
  CHAR          szValue[255];
  SHVBLOCK      shvb;
  ULONG         ulIdx;
  ULONG         ulPosition;
  ULONG         ulCount;
  BOOL          fOk = TRUE;

  if ( (numargs != 3) ||  /* validate arguments       */
      !RXVALIDSTRING(args[0]) || !RXVALIDSTRING(args[1]) ||
      RXNULLSTRING(args[2]) )
    return INVALID_ROUTINE;

  /* remember stem name */
  memset(szStemName, 0, sizeof(szStemName));
  strcpy(szStemName, args[0].strptr);
  if (szStemName[args[0].strlength-1] != '.')
    szStemName[args[0].strlength] = '.';
  pszStemIdx = &(szStemName[strlen(szStemName)]);

  /* get new item index */
  if (sscanf(args[1].strptr, "%ld", &ulPosition) != 1)
     return INVALID_ROUTINE;

  /* retrieve the number of elements in stem */
  strcpy(pszStemIdx, "0");
  shvb.shvnext = NULL;
  shvb.shvname.strptr = szStemName;
  shvb.shvname.strlength = strlen((const char *)szStemName);
  shvb.shvvalue.strptr = szValue;
  shvb.shvvalue.strlength = sizeof(szValue);
  shvb.shvnamelen = shvb.shvname.strlength;
  shvb.shvvaluelen = shvb.shvvalue.strlength;
  shvb.shvcode = RXSHV_SYFET;
  shvb.shvret = 0;
  if (RexxVariablePool(&shvb) == RXSHV_OK)
  {
    /* index retrieved fine */
    if (sscanf(shvb.shvvalue.strptr, "%ld", &ulCount) != 1)
      return INVALID_ROUTINE;

    /* check wether new position is within limits */
    if ((ulPosition == 0) || (ulPosition > ulCount + 1))
      return INVALID_ROUTINE;

    /* make room for new item by moving all items to the end */
    for (ulIdx = ulCount; ulIdx >= ulPosition; ulIdx--)
    {
      /* get element to relocate */
      sprintf(pszStemIdx, "%ld", ulIdx);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szStemName;
      shvb.shvname.strlength = strlen((const char *)szStemName);
      shvb.shvvalue.strptr = NULL;
      shvb.shvvalue.strlength = 0;
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYFET;
      shvb.shvret = 0;

      if (RexxVariablePool(&shvb) == RXSHV_OK)
      {
        sprintf(pszStemIdx, "%ld", ulIdx + 1);
        shvb.shvnext = NULL;
        shvb.shvname.strptr = szStemName;
        shvb.shvname.strlength = strlen((const char *)szStemName);
        shvb.shvnamelen = shvb.shvname.strlength;
        shvb.shvvaluelen = shvb.shvvalue.strlength;
        shvb.shvcode = RXSHV_SYSET;
        shvb.shvret = 0;
        rc = RexxVariablePool(&shvb);
        if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
          fOk = FALSE;

        /* free memory allocated by REXX */
        free(shvb.shvvalue.strptr);
      }
      else
        fOk = FALSE;

      if (!fOk)
        break;
    } /* endfor */

    if (fOk)
    {
      /* set the new item value */
      sprintf(pszStemIdx, "%ld", ulPosition);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szStemName;
      shvb.shvname.strlength = strlen((const char *)szStemName);
      shvb.shvvalue.strptr = args[2].strptr;
      shvb.shvvalue.strlength = args[2].strlength;
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYSET;
      shvb.shvret = 0;
      rc = RexxVariablePool(&shvb);
      if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
        fOk = FALSE;
    } /* endif */

    if (fOk)
    {
      /* set the new number of items in the stem array */
      strcpy(pszStemIdx, "0");
      sprintf(szValue, "%ld", ulCount + 1);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szStemName;
      shvb.shvname.strlength = strlen((const char *)szStemName);
      shvb.shvvalue.strptr = szValue;
      shvb.shvvalue.strlength = strlen(szValue);
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYSET;
      shvb.shvret = 0;
      rc = RexxVariablePool(&shvb);
      if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
        fOk = FALSE;
    } /* endif */
  }
  else
  {
    fOk = FALSE;
  } /* endif */

  if (fOk)
    RETVAL(0)
  else
    RETVAL(-1)
}


/*************************************************************************
* Function:  SysStemCopy                                                 *
*                                                                        *
* Syntax:    result = SysStemCopy(fromstem, tostem, from, to, count      *
*                                 [,insert])                             *
*                                                                        *
* Params:    fromstem - name of source stem                              *
*            tostem - - name of target stem                              *
*            from  - first index in source stem to copy                  *
*            to - position where items are copied/inserted in target stem*
*            count - number of items to copy/insert                      *
*            insert - 'I' to indicate insert instead of 'O' overwrite    *
*                                                                        *
* Return:    0 - stem copy was successful                                *
*            -1 - stem copy failed                                       *
*************************************************************************/

LONG APIENTRY SysStemCopy(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  APIRET        rc;
  CHAR          szFromStemName[255];
  CHAR          szToStemName[255];
  PSZ           pszFromStemIdx;
  PSZ           pszToStemIdx;
  CHAR          szValue[255];
  SHVBLOCK      shvb;
  ULONG         ulIdx;
  ULONG         ulToCount;
  ULONG         ulFromCount;
  ULONG         ulFrom = 1;
  ULONG         ulTo = 1;
  ULONG         ulCopyCount = 0;
  BOOL          fInsert = FALSE;
  BOOL          fOk = TRUE;

  if ( (numargs < 2) || (numargs > 6) ||  /* validate arguments       */
      !RXVALIDSTRING(args[0]) || !RXVALIDSTRING(args[1]) ||
      ((numargs == 6) && !RXVALIDSTRING(args[5])) )
    return INVALID_ROUTINE;

  /* remember stem names */
  memset(szFromStemName, 0, sizeof(szFromStemName));
  strcpy(szFromStemName, args[0].strptr);
  if (szFromStemName[args[0].strlength-1] != '.')
    szFromStemName[args[0].strlength] = '.';
  pszFromStemIdx = &(szFromStemName[strlen(szFromStemName)]);

  memset(szToStemName, 0, sizeof(szToStemName));
  strcpy(szToStemName, args[1].strptr);
  if (szToStemName[args[1].strlength-1] != '.')
    szToStemName[args[1].strlength] = '.';
  pszToStemIdx = &(szToStemName[strlen(szToStemName)]);

  /* get from item index */
  if ((numargs >= 3) && RXVALIDSTRING(args[2]))
    if (sscanf(args[2].strptr, "%ld", &ulFrom) != 1)
      return INVALID_ROUTINE;

  /* get to item index */
  if ((numargs >= 4) && RXVALIDSTRING(args[3]))
    if (sscanf(args[3].strptr, "%ld", &ulTo) != 1)
      return INVALID_ROUTINE;

  /* get copy count */
  if ((numargs >= 5) && RXVALIDSTRING(args[4]))
    if (sscanf(args[4].strptr, "%ld", &ulCopyCount) != 1)
      return INVALID_ROUTINE;

  /* get copy type */
  if (numargs >= 6)
  {
    switch (args[5].strptr[0])
    {
      case 'I':
      case 'i':
        fInsert = TRUE;
        break;
      case 'O':
      case 'o':
        fInsert = FALSE;
        break;
      default:
        return INVALID_ROUTINE;
    } /* endswitch */
  } /* endif */

  /* retrieve the number of elements in stems */
  strcpy(pszFromStemIdx, "0");
  shvb.shvnext = NULL;
  shvb.shvname.strptr = szFromStemName;
  shvb.shvname.strlength = strlen((const char *)szFromStemName);
  shvb.shvvalue.strptr = szValue;
  shvb.shvvalue.strlength = sizeof(szValue);
  shvb.shvnamelen = shvb.shvname.strlength;
  shvb.shvvaluelen = shvb.shvvalue.strlength;
  shvb.shvcode = RXSHV_SYFET;
  shvb.shvret = 0;
  if (RexxVariablePool(&shvb) == RXSHV_OK)
  {
    /* index retrieved fine */
    if (sscanf(shvb.shvvalue.strptr, "%ld", &ulFromCount) != 1)
      return INVALID_ROUTINE;

    if ((ulCopyCount > ulFromCount) || (ulFromCount == 0))
      return INVALID_ROUTINE;
  }
  else
    fOk = FALSE;

  if (fOk)
  {
    strcpy(pszToStemIdx, "0");
    shvb.shvnext = NULL;
    shvb.shvname.strptr = szToStemName;
    shvb.shvname.strlength = strlen((const char *)szToStemName);
    shvb.shvvalue.strptr = szValue;
    shvb.shvvalue.strlength = sizeof(szValue);
    shvb.shvnamelen = shvb.shvname.strlength;
    shvb.shvvaluelen = shvb.shvvalue.strlength;
    shvb.shvcode = RXSHV_SYFET;
    shvb.shvret = 0;
    rc = RexxVariablePool(&shvb);
    if (rc == RXSHV_OK)
    {
      /* index retrieved fine */
      if (sscanf(shvb.shvvalue.strptr, "%ld", &ulToCount) != 1)
        return INVALID_ROUTINE;
    }
    else
    {
      if (rc == RXSHV_NEWV)
      {
        /* tostem.0 is not set, we assume empty target stem */
        ulToCount = 0;
      }
      else
        fOk = FALSE;
    } /* endif */

    if (fOk)
    {
      if (ulTo > ulToCount + 1)
        return INVALID_ROUTINE;
    } /* endif */
  } /* endif */

  /* set copy count to number of items in source stem if not already set */
  if (ulCopyCount == 0)
    ulCopyCount = ulFromCount;

  if (fOk && fInsert)
  {
    /* if we are about to insert the items we have to make room */
    for (ulIdx = ulToCount; ulIdx >= ulTo; ulIdx--)
    {
      /* get element to relocate */
      sprintf(pszToStemIdx, "%ld", ulIdx);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szToStemName;
      shvb.shvname.strlength = strlen((const char *)szToStemName);
      shvb.shvvalue.strptr = NULL;
      shvb.shvvalue.strlength = 0;
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYFET;
      shvb.shvret = 0;

      if (RexxVariablePool(&shvb) == RXSHV_OK)
      {
        sprintf(pszToStemIdx, "%ld", ulIdx + ulCopyCount);
        shvb.shvnext = NULL;
        shvb.shvname.strptr = szToStemName;
        shvb.shvname.strlength = strlen((const char *)szToStemName);
        shvb.shvnamelen = shvb.shvname.strlength;
        shvb.shvvaluelen = shvb.shvvalue.strlength;
        shvb.shvcode = RXSHV_SYSET;
        shvb.shvret = 0;
        rc = RexxVariablePool(&shvb);
        if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
          fOk = FALSE;

        /* free memory allocated by REXX */
        free(shvb.shvvalue.strptr);
      }
      else
        fOk = FALSE;

      if (!fOk)
        break;
    } /* endfor */

    if (fOk)
    {
      /* set the new count for the target stem */
      strcpy(pszToStemIdx, "0");
      ulToCount += ulCopyCount;
      sprintf(szValue, "%ld", ulToCount);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szToStemName;
      shvb.shvname.strlength = strlen((const char *)szToStemName);
      shvb.shvvalue.strptr = szValue;
      shvb.shvvalue.strlength = strlen(szValue);
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYSET;
      shvb.shvret = 0;
      rc = RexxVariablePool(&shvb);
      if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
        fOk = FALSE;
    } /* endif */
  } /* endif */

  if (fOk)
  {
    /* now do the actual copying from the source to target */
    for (ulIdx = 0; ulIdx < ulCopyCount; ulIdx++)
    {
      /* get element to copy */
      sprintf(pszFromStemIdx, "%ld", ulFrom + ulIdx);
      shvb.shvnext = NULL;
      shvb.shvname.strptr = szFromStemName;
      shvb.shvname.strlength = strlen((const char *)szFromStemName);
      shvb.shvvalue.strptr = NULL;
      shvb.shvvalue.strlength = 0;
      shvb.shvnamelen = shvb.shvname.strlength;
      shvb.shvvaluelen = shvb.shvvalue.strlength;
      shvb.shvcode = RXSHV_SYFET;
      shvb.shvret = 0;

      if (RexxVariablePool(&shvb) == RXSHV_OK)
      {
        sprintf(pszToStemIdx, "%ld", ulTo + ulIdx);
        shvb.shvnext = NULL;
        shvb.shvname.strptr = szToStemName;
        shvb.shvname.strlength = strlen((const char *)szToStemName);
        shvb.shvnamelen = shvb.shvname.strlength;
        shvb.shvvaluelen = shvb.shvvalue.strlength;
        shvb.shvcode = RXSHV_SYSET;
        shvb.shvret = 0;
        rc = RexxVariablePool(&shvb);
        if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
          fOk = FALSE;

        /* free memory allocated by REXX */
        free(shvb.shvvalue.strptr);
      }
      else
        fOk = FALSE;

      if (!fOk)
        break;
    } /* endfor */
  } /* endif */

  if (fOk && (ulTo + ulCopyCount - 1 > ulToCount))
  {
    /* set the new count for the target stem */
    strcpy(pszToStemIdx, "0");
    ulToCount = ulTo + ulCopyCount - 1;
    sprintf(szValue, "%ld", ulToCount);
    shvb.shvnext = NULL;
    shvb.shvname.strptr = szToStemName;
    shvb.shvname.strlength = strlen((const char *)szToStemName);
    shvb.shvvalue.strptr = szValue;
    shvb.shvvalue.strlength = strlen(szValue);
    shvb.shvnamelen = shvb.shvname.strlength;
    shvb.shvvaluelen = shvb.shvvalue.strlength;
    shvb.shvcode = RXSHV_SYSET;
    shvb.shvret = 0;
    rc = RexxVariablePool(&shvb);
    if ((rc != RXSHV_OK) && (rc != RXSHV_NEWV))
      fOk = FALSE;
  } /* endif */

  if (fOk)
    RETVAL(0)
  else
    RETVAL(-1)
}

//#endif


/**************************************************************************
* Function:  SysQueryProcess                                              *
*                                                                         *
* Params:    "PID"       - (default) returns current process ID           *
*    NEW:    "PPID"      -  returns parent of current process ID          *
*    NEW:    "PGID"      -  returns group ID of current process           *
*    NO      "TID"       -  returns current thread ID                     *
*    YES     "PPRIO"     -  returns current process priority              *
*    NO      "TPRIO"     -  returns current thread priority               *
*    YES     "PTIME"     -  returns current process times                 *
*    NO      "TTIME"     -  returns current thread times                  *
*    NEW:    "PMEM"      -  returns current process max memory size RSS   *
*    NEW:    "PSWAPS"    -  returns current process number of swaps out   *
*    NEW:    "PRCVDSIG"  -  returns current process received signals      *
***************************************************************************/

LONG APIENTRY SysQueryProcess(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{

  unsigned int uiUsedCPUTime  = 0;
  unsigned int uiUsedCPUmsec  = 0;
  unsigned int uiUsedHours    = 0;
  unsigned int uiUsedMinutes  = 0;
  unsigned int uiUsedSeconds  = 0;
  char timebuf[40];
  int iRc = 0;
  struct rusage struResUse;
  retstr->strlength = 0;                 /* set return value           */

  if (numargs > 1)                    /* none or one argument accepted */
    return INVALID_ROUTINE;              /* raise error condition      */

  if ((numargs == 0) || (!stricmp(args[0].strptr, "PID")))
  {
    sprintf(retstr->strptr, "%d", getpid());
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }
  else
  if (!stricmp(args[0].strptr, "PPID"))
  {
    sprintf(retstr->strptr, "%d", getppid());
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }
  else
  if (!stricmp(args[0].strptr, "PGID"))
  {
    sprintf(retstr->strptr, "%d", getpgid(getpid()));
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }
  else
  if (!stricmp(args[0].strptr, "PPRIO"))
  {
    sprintf(retstr->strptr, "%d", getpriority(PRIO_PROCESS, 0));
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }

  /* ----------------------------------------------------------------- */
  /* Get process usage data and keep calls together at the end of      */
  /* the function SysQueryProcess.                                     */
  iRc = getrusage ( RUSAGE_SELF, &struResUse);
  if ( iRc )
  {
     sprintf(retstr->strptr, " System error; errno = %d", errno);
     retstr->strlength = strlen(retstr->strptr);
     return VALID_ROUTINE;               /* no error on call           */
  }
  if (!stricmp(args[0].strptr, "PTIME")) /* Calculate the used CPU time*/
  {
    uiUsedCPUmsec  = (unsigned int) struResUse.ru_utime.tv_usec/1000;
    uiUsedCPUmsec += (unsigned int) struResUse.ru_stime.tv_usec/1000;
    if (uiUsedCPUmsec >= 1000 )
    {
      uiUsedCPUTime = uiUsedCPUmsec / 1000;
      uiUsedCPUmsec = uiUsedCPUmsec % 1000;
    }
    uiUsedCPUTime += (unsigned int) struResUse.ru_utime.tv_sec;
    uiUsedCPUTime += (unsigned int) struResUse.ru_stime.tv_sec;
    uiUsedHours   = uiUsedCPUTime / 3600;
    uiUsedMinutes = uiUsedCPUTime / 60;
    if (uiUsedMinutes >= 60 ) uiUsedMinutes = uiUsedMinutes % 60;
    if (uiUsedCPUTime >= 60 ) uiUsedSeconds = uiUsedCPUTime % 60;
    else uiUsedSeconds = uiUsedCPUTime;

    sprintf(retstr->strptr, "CPU_Time Summary: %2d:%.2d:%.2d:%.3d  Kernel:",
                    uiUsedHours, uiUsedMinutes, uiUsedSeconds, uiUsedCPUmsec );

    uiUsedCPUmsec = (unsigned int) struResUse.ru_stime.tv_usec/1000;
    uiUsedCPUTime = (unsigned int) struResUse.ru_stime.tv_sec;
    uiUsedHours   = uiUsedCPUTime / 3600;
    uiUsedMinutes = uiUsedCPUTime / 60;
    if (uiUsedMinutes >= 60 ) uiUsedMinutes = uiUsedMinutes % 60;
    if (uiUsedCPUTime >= 60 ) uiUsedSeconds = uiUsedCPUTime % 60;
    else uiUsedSeconds = uiUsedCPUTime;

    sprintf(timebuf, " %2d:%.2d:%.2d:%.3d  User:", uiUsedHours,
                                 uiUsedMinutes, uiUsedSeconds, uiUsedCPUmsec );
    strcat(retstr->strptr, timebuf);

    uiUsedCPUmsec = (unsigned int) struResUse.ru_utime.tv_usec/1000;
    uiUsedCPUTime = (unsigned int) struResUse.ru_utime.tv_sec;
    uiUsedHours   = uiUsedCPUTime / 3600;
    uiUsedMinutes = uiUsedCPUTime / 60;
    if (uiUsedMinutes >= 60 ) uiUsedMinutes = uiUsedMinutes % 60;
    if (uiUsedCPUTime >= 60 ) uiUsedSeconds = uiUsedCPUTime % 60;
    else uiUsedSeconds = uiUsedCPUTime;

    sprintf(timebuf, " %2d:%.2d:%.2d:%.3d", uiUsedHours,
                                 uiUsedMinutes, uiUsedSeconds, uiUsedCPUmsec );
    strcat(retstr->strptr, timebuf);

    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }
  else
  if (!stricmp(args[0].strptr, "PMEM"))  /* Show max memory RSS used   */
  {
    sprintf(retstr->strptr, "Max_Memory_RSS: %d", struResUse.ru_maxrss);
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }
  else
  if (!stricmp(args[0].strptr, "PSWAPS")) /* Memory has been swapped   */
  {
    sprintf(retstr->strptr, "Memory_swaps: %d", struResUse.ru_nswap);
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }
  else
  if (!stricmp(args[0].strptr, "PRCVDSIG")) /* Process received signals*/
  {
    sprintf(retstr->strptr, "Received_signals: %d", struResUse.ru_nsignals);
    retstr->strlength = strlen(retstr->strptr);
    return VALID_ROUTINE;                /* no error on call           */
  }

  return INVALID_ROUTINE;                /* good completion            */
}

/*************************************************************************
* Function:  SysGetErrortext                                             *
*                                                                        *
* Syntax:    call SysGetErrortext errnumber                              *
*                                                                        *
* Params:    errnumber - error number to be described                    *
*                                                                        *
* Return:    Description or empty string                                 *
*************************************************************************/

LONG APIENTRY SysGetErrortext(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{

  int   errnum  = 0;
  char  *errmsg = NULL;

  if (numargs != 1)
                                       /* If no args, then its an    */
                                       /* incorrect call             */
    return INVALID_ROUTINE;

  errnum = atoi(args[0].strptr);
  errmsg = strerror( errnum );
  if (errmsg == NULL )
    retstr->strptr[0] = '\0';
  else
  {
    if (strlen(errmsg) >= retstr->strlength)
       retstr->strptr = (char *) malloc(strlen(errmsg + 1));
    strcpy(retstr->strptr,errmsg);
  }
  retstr->strlength = strlen(retstr->strptr);

  return VALID_ROUTINE;
}


/*************************************************************************
* Function:  SysUtilVersion                                              *
*                                                                        *
* Syntax:    Say SysUtilVersion                                          *
*                                                                        *
* Return:    REXXUTIL.DLL Version                                        *
*************************************************************************/

LONG APIENTRY SysUtilVersion(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  if (numargs != 0)                    /* validate arg count         */
    return INVALID_ROUTINE;
                                       /* format into the buffer            */
  sprintf(retstr->strptr, "%d.%d.%d", ORX_VER, ORX_REL, ORX_MOD);
  retstr->strlength = strlen(retstr->strptr);

  return VALID_ROUTINE;
}

/*************************************************************************
* Function:  SysIsFile                                                *
*                                                                        *
* Syntax:    call SysIsFile file                                      *
*                                                                        *
* Params:    file - file to check existance of.                          *
*                                                                        *
* Return:    Logical.                                                    *
*************************************************************************/

LONG APIENTRY SysIsFile(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
  struct stat finfo;                   /* return buf for the finfo   */

  if (numargs != 1)                    /* we need one argument       */
    return INVALID_ROUTINE;            /* raise an error             */

  stat(args[0].strptr, &finfo);        /* read the info about it     */

  if(S_ISREG(finfo.st_mode) ||         /* if it is a file            */
     S_ISBLK(finfo.st_mode)) {         /* file                       */
    RETVAL(1)                          /* True - Is a File           */
  }
  else {
    RETVAL(0)                          /* False - Is something else  */
  }
}

/*************************************************************************
* Function:  SysIsFileDirectory                                                 *
*                                                                        *
* Syntax:    call SysIsFileDirectory dir                                        *
*                                                                        *
* Params:    dir - dir to check existance of.                            *
*                                                                        *
* Return:    Logical.                                                    *
*************************************************************************/

LONG APIENTRY SysIsFileDirectory(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
    struct stat finfo;                 /* return buf for the finfo   */

    if (numargs != 1)                  /* we need one argument       */
      return INVALID_ROUTINE;          /* raise an error             */

    stat(args[0].strptr, &finfo);      /* read the info about it     */

    if(S_ISDIR(finfo.st_mode)) {       /* is a subdir?               */
      RETVAL(1)                        /* True - Is a File           */
    }
    else {
      RETVAL(0)                        /* False - Is something else  */
    }
}

/*************************************************************************
* Function:  SysIsFileLink                                               *
*                                                                        *
* Syntax:    call SysIsFileLink file                                     *
*                                                                        *
* Params:    file - file to check if it is a Link (Alias).               *
*                                                                        *
* Return:    Logical.                                                    *
*************************************************************************/

LONG APIENTRY SysIsFileLink(
  PSZ       name,                      /* Function name              */
  LONG      numargs,                   /* Number of arguments        */
  RXSTRING  args[],                    /* Argument array             */
  PSZ       queuename,                 /* Current queue              */
  PRXSTRING retstr )                   /* Return RXSTRING            */
{
    struct stat finfo;                 /* return buf for the finfo   */

    if (numargs != 1)                  /* we need one argument       */
      return INVALID_ROUTINE;          /* raise an error             */

    lstat(args[0].strptr, &finfo);     /* read the info about it     */

    if(S_ISLNK(finfo.st_mode)) {       /* or a symbolic link         */
      RETVAL(1)                        /* True - Is a File           */
    }
    else {
      RETVAL(0)                        /* False - Is something else  */
    }
}


#ifdef __cplusplus
}
#endif