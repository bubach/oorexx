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
/* REXX mathematical function support                             rxmath.c    */
/*                                                                            */
/* AIX  mathematical utility function package                                 */
/*                                                                            */
/******************************************************************************/

/**********************************************************************
*   RXMATH.C                                                          *
*                                                                     *
*   This program extends the REXX language by providing many          *
*   external mathematical functions                                   *
*   These functions are:                                              *
*       RxCalcPi               -- Return Pi to given precision        *
*       RxCalcSqrt             -- Calculate a square root             *
*       RxCalcExp              -- Calculate an exponent               *
*       RxCalcLog              -- Return natural log of a number      *
*       RxCalcLog10            -- Return log base 10 of a number      *
*       RxCalcSinh             -- Hyperbolic sine function            *
*       RxCalcCosh             -- Hyperbolic cosine function          *
*       RxCalcTanh             -- Hyperbolic tangent function         *
*       RxCalcPower            -- raise number to non-integer power   *
*       RxCalcSin              -- Sine function                       *
*       RxCalcCos              -- Cosine function                     *
*       RxCalcTan              -- Tangent function                    *
*       RxCalcCotan            -- Cotangent function                  *
*       RxCalcArcSin           -- ArcSine function                    *
*       RxCalcArcCos           -- ArcCosine function                  *
*       RxCalcArcTan           -- ArcTangent function                 *
*                                                                     *
**********************************************************************/

extern int errno;

/*------------------------------------------------------------------
 * program defines
 *------------------------------------------------------------------*/
#if defined(OPSYS_AIX) || defined(LINUX)
#define PROG_NAME "rxmath"
#else
#define PROG_NAME "RxMath"
#endif

#define PROG_DESC "REXX mathematical function package"
#define PROG_COPY "(c) Copyright RexxLanguage Association 2005-2006."
#define PROG_ALRR "All Rights Reserved."

/*------------------------------------------------------------------
 * standard includes
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <sys/types.h>

#include <math.h>
#include <fcntl.h>

/*------------------------------------------------------------------
 * rexx includes
 *------------------------------------------------------------------*/
#define INCL_REXXSAA

#if defined(OPSYS_AIX) || defined(LINUX)
#include "rexx.h"
#include "PlatformDefinitions.h"
#include "locale.h"
#else
#ifdef WIN32
#include <rexx.h>
#define NO_SYSTIMESLICEELAPSED
#include "PlatformDefinitions.h"
#else
#include <rexxsaa.h>
#endif
#endif
#include <sys/types.h>
#include <errno.h>
#include "RexxNativeAPI.h"
#include "RexxErrorCodes.h"
#include "RexxMessageNumbers.h"           /* include  definition of errorcodes */
#include "RexxMessageTable.h"             /* include actual table definition   */

#define MAX_DIGITS     9

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
#define MIN_PRECISION     1            /* minimum available precision*/

/*********************************************************************/
/* Numeric Return calls                                              */
/*********************************************************************/

#define  INVALID_ROUTINE 40            /* Raise Rexx error           */
#define  VALID_ROUTINE    0            /* Successful completion      */


BOOL bErrorFlag = FALSE;

/* Turn off optimization under Windows. If this is compiler under    */
/* Windows with the MS Visual C++ copiler and optimization is on     */
/* then the function _matherr is not called                          */
#ifdef WIN32
#pragma optimize( "", off )
#endif

/*********************************************************************/
/* MathFncTable                                                      */
/*   Array of names of the rxmath functions.                         */
/*   This list is used for registration and deregistration.          */
/*********************************************************************/

static PSZ  MathFncTable[] =
   {
      "MathLoadFuncs",
      "MATHLOADFUNCS",
      "MathDropFuncs",
      "RxCalcPi",
      "RxCalcSqrt",
      "RxCalcExp",
      "RxCalcLog",
      "RxCalcLog10",
      "RxCalcSinH",
      "RxCalcCosH",
      "RxCalcTanH",
      "RxCalcPower",
      "RxCalcSin",
      "RxCalcCos",
      "RxCalcTan",
      "RxCalcCotan",
      "RxCalcArcSin",
      "RxCalcArcCos",
      "RxCalcArcTan"
   };

#ifdef __cplusplus
extern "C" {
#endif

void SearchPrecision(PULONG);
void RxErrMsgSet(PSZ);
void RxErrMsgSet1(PSZ);

/*************************************************************************
* Function:  MathLoadFuncs                                               *
*                                                                        *
* Syntax:    call MathLoadFuncs                                          *
*                                                                        *
* Purpose:   load the function package                                   *
*                                                                        *
* Params:    none                                                        *
*                                                                        *
* Return:    null string                                                 *
*************************************************************************/
/*------------------------------------------------------------------
 * load the function package
 *------------------------------------------------------------------*/
#if defined(LINUX) || defined(OPSYS_AIX)
ULONG MATHLOADFUNCS(PUCHAR, ULONG, PRXSTRING, PSZ, PRXSTRING);
ULONG APIENTRY MathLoadFuncs (
   PUCHAR     name,
   ULONG      argc,
   PRXSTRING  argv,
   PSZ        qName,
   PRXSTRING  retStr
   )
{
   return( MATHLOADFUNCS( name, argc, argv, qName, retStr) );
}
#endif
ULONG APIENTRY MATHLOADFUNCS (
   PUCHAR     name,
   ULONG      argc,
   PRXSTRING  argv,
   PSZ        qName,
   PRXSTRING  retStr
   )
{
   INT    entries;                      /* Num of entries             */
   INT    j;                            /* Counter                    */

   retStr->strlength = 0;

   if (argc)
   {
      fprintf(stdout, "%s %d.%d.%d - %s\n",
              PROG_NAME, ORX_VER, ORX_REL, ORX_MOD, PROG_DESC);
      fprintf(stdout, "%s\n",PROG_COPY);
      fprintf(stdout, "%s\n",PROG_ALRR);
      fprintf(stdout, "\n");
   }

   entries = sizeof(MathFncTable)/sizeof(PSZ);

   for (j = 0; j < entries; j++) {
     RexxRegisterFunctionDll(MathFncTable[j],
           PROG_NAME, MathFncTable[j]);
   }
   return VALID_ROUTINE;
}

/*************************************************************************
* Function:  MathDropFuncs                                               *
*                                                                        *
* Syntax:    call MathDropFuncs                                          *
*                                                                        *
* Return:    NO_UTIL_ERROR - Successful.                                 *
*************************************************************************/

LONG APIENTRY MathDropFuncs(
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

  entries = sizeof(MathFncTable)/sizeof(PSZ);

  for (j = 0; j < entries; j++)
    RexxDeregisterFunction(MathFncTable[j]);

  return VALID_ROUTINE;                /* no error on call           */
}


/* Helper functions **************************************************/

/*************************************************************************
* Function:  matherr                                                     *
*                                                                        *
* Syntax:    matherr is called by the system if exist whenever  a mathe  *
*            matical function fails.                                     *
*                                                                        *
* Return:    NO_UTIL_ERROR - Successful.                                 *
*************************************************************************/
#ifdef WIN32
int _cdecl _matherr( struct _exception *x )
#elif OPSYS_SUN
int matherr(struct __math_exception *x)    /* return string            */
#elif OPSYS_AIX
int matherr(struct __exception *x)         /* return string            */
#endif
#if defined(WIN32) || defined(OPSYS_SUN) || defined(OPSYS_AIX)
{
  LONG rc;
  rc = errno;
  bErrorFlag = TRUE;

  if (x->type == DOMAIN)
  {
      RxErrMsgSet1("Argument domain error");
  }
  else if (x->type == OVERFLOW)
  {
      RxErrMsgSet1("Overflow range error");
  }
  else if (x->type == UNDERFLOW)
  {
      RxErrMsgSet1("Underflow range error");
  }
  else if (x->type == SING)
  {
      RxErrMsgSet1("Argument singularity");
  }
  else if (x->type == TLOSS)
  {
      RxErrMsgSet1("Total loss of significance");
  }
  else if (x->type == PLOSS)
  {
      RxErrMsgSet1("Total loss of significance");
  }
  else
  {
      RxErrMsgSet1("Mathematical error occured");
  }

  return(1);                            /* otherwhile system throws exception */

}
#endif

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

/*********************************************************************/
/* Function FormatFloat:  Common routine to format a floating point  */
/* result for the math functions                                     */
/*********************************************************************/
LONG MathFormatResult(
  double    result,                    /* formatted result           */
  ULONG     precision,                 /* required precision         */
  PRXSTRING retstr )                   /* return string              */
{

  LONG      rc;                        /* validation code            */
  rc = VALID_ROUTINE;                  /* set default completion     */

  if (bErrorFlag)                      /* error occured during       */
  {
    bErrorFlag = FALSE;
    strcpy(retstr->strptr, "ERROR");   /* matherr has set bErrorFlag */
    retstr->strlength = strlen(retstr->strptr);
    rc = VALID_ROUTINE;
    return rc;
  }
  else if (result == 0)                /* zero result?               */
    strcpy(retstr->strptr, "0");       /* make exactly 0             */
  else
    sprintf(retstr->strptr, "%.*g", precision, result);
                                       /* set the length             */
  retstr->strlength = strlen(retstr->strptr);
                                       /* end in a period?           */
  if (retstr->strptr[retstr->strlength - 1] == '.')
    retstr->strlength--;               /* remove the period          */
  return rc;
}

/*********************************************************************/
/* Function ValidateMath: Common validation routine for math         */
/* that are of the form fn(number, <precision>)                      */
/*********************************************************************/
LONG  ValidateMath(
  LONG      numargs,                   /* Number of arguments.       */
  RXSTRING  args[],                    /* Function arguments.        */
  double   *x,                         /* input number               */
  PULONG    precision )                /* returned precision         */
{
  LONG      rc;                        /* validation code            */

  rc = VALID_ROUTINE;                  /* set default completion     */

  RxErrMsgSet1("0");

  SearchPrecision(precision);

  if (numargs < 1 || numargs > 2)
  {
    RxErrMsgSet1("Invalid number of arguments");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (!RXVALIDSTRING(args[0]))         /* first is omitted           */
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
                                       /* convert input number       */
  else if (sscanf(args[0].strptr, " %lf", x) != 1)
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (numargs == 2 &&             /* have a precision, override activity precision */
      !string2ulong(args[1].strptr, precision))
  {
    RxErrMsgSet1("The second argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if ( (*precision > MAX_PRECISION)  || (*precision < MIN_PRECISION) )
  {
    RxErrMsgSet1("The precision is not in the valid range (1-16)");
    rc = INVALID_ROUTINE;
  }
  return rc;                           /* return success code        */
}

/*********************************************************************/
/* Function ValidateTrig: Common validation routine for math         */
/* that are of the form fn(number, <precision>, <unit>)              */
/*********************************************************************/
LONG  ValidateTrig(
  LONG      numargs,                   /* Number of arguments.       */
  RXSTRING  args[],                    /* Function arguments.        */
  PRXSTRING retstr,                    /* return string              */
  INT       function )                 /* function to perform        */
{
  LONG      rc;                        /* validation code            */
  INT       units;                     /* angle type                 */
  double    angle;                     /* working angle              */
  double    nsi;                       /* convertion factor          */
  double    nco;                       /* convertion factor          */
  ULONG     precision;                 /* returned precision         */
  double    result;                    /* result                     */

  rc = VALID_ROUTINE;                  /* set default completion     */
  units = DEGREES;                     /* default angle is degrees   */
  nsi = 1.;                            /* set default conversion     */
  nco = 1.;                            /* set default conversion     */


  RxErrMsgSet1("0");

/* give me the numeric digits settings of the current actitity       */

  SearchPrecision(&precision);

  if (numargs < 1 || numargs > 3)
  {
    RxErrMsgSet1("Invalid number of arguments");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (!RXVALIDSTRING(args[0]))         /* first is omitted           */
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
                                       /* convert input number       */
  else if (sscanf(args[0].strptr, " %lf", &angle) != 1)
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (numargs >= 2 &&             /* have a precision           */
      RXVALIDSTRING(args[1]) &&        /* and it is real string      */
      !string2ulong(args[1].strptr, &precision))
  {
    RxErrMsgSet1("The second argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if ( (precision > MAX_PRECISION)  | (precision < MIN_PRECISION) )
  {
    RxErrMsgSet1("The precision is not in the valid range (1-16)");
    rc = INVALID_ROUTINE;
  }
  else if (numargs == 3)
  {                                    /* have an option             */
    if (RXZEROLENSTRING(args[2]))      /* null string?               */
    {
      RxErrMsgSet1("The third argument is invalid");
      rc = INVALID_ROUTINE;            /* this is invalid            */
    }
    else
    {                                  /* process the options        */
                                       /* get the option character   */
      units = toupper(args[2].strptr[0]);
                                       /* was it a good option?      */
      if (units != DEGREES && units != RADIANS && units != GRADES)
      {
        rc = INVALID_ROUTINE;          /* bad option is error        */
        RxErrMsgSet1("The third argument is invalid");
        rc = INVALID_ROUTINE;            /* this is invalid            */
      }
    }
  }
  if (!rc)
  {                                    /* everything went well?      */
    if (units == DEGREES) {            /* need to convert degrees    */
      nsi = (angle < 0.) ? -1. : 1.;   /* get the direction          */
      angle = fmod(fabs(angle), 360.); /* make modulo 360            */
      if (angle <= 45.)                /* less than 45?              */
        angle = angle * pi / 180.;
      else if (angle < 135.) {         /* over on the other side?    */
        angle = (90. - angle) * pi / 180.;
        function = MAXTRIG - function; /* change the function        */
        nco = nsi;                     /* swap around the conversions*/
        nsi = 1.;
      }
      else if (angle <= 225.) {        /* around the other way?      */
        angle = (180. - angle) * pi / 180.;
        nco = -1.;
      }
      else if (angle < 315.) {         /* close to the origin?       */
        angle = (angle - 270.) * pi / 180.;
        function = MAXTRIG - function; /* change the function        */
        nco = -nsi;
        nsi = 1.;
      }
      else
        angle = (angle - 360.) * pi / 180.;
    }
    else if (units == GRADES) {        /* need to convert degrees    */
      nsi = (angle < 0.) ? -1. : 1.;   /* get the direction          */
      angle = fmod(fabs(angle), 400.); /* make modulo 400            */
      if (angle <= 50.)
        angle = angle * pi / 200.;
      else if (angle < 150.) {
        angle = (100. - angle) * pi / 200.;
        function = MAXTRIG - function; /* change the function        */
        nco = nsi;                     /* swap the conversions       */
        nsi = 1.;
      }
      else if (angle <= 250.) {
        angle = (200. - angle) * pi / 200.;
        nco = -1.;
      }
      else if (angle < 350.) {
        angle = (angle - 300.) * pi / 200.;
        function = MAXTRIG - function; /* change the function        */
        nco = -nsi;
        nsi = 1.;
      }
      else
        angle = (angle - 400.) * pi / 200.;
    }
    switch (function) {                /* process the function       */
      case SINE:                       /* Sine function              */
        result = nsi * sin(angle);
        break;
      case COSINE:                     /* Cosine function            */
        result = nco * cos(angle);
        break;
      case TANGENT:                    /* Tangent function           */
        result = nsi * nco * tan(angle);
        break;
      case COTANGENT:                  /* cotangent function         */
                                       /* overflow?                  */
        if ((result = tan(angle)) == 0.0)
        {
           RxErrMsgSet1("Unable to calculate value. Overflow occured");
           rc = INVALID_ROUTINE;              /* this is invalid            */
        }
        else
          result = nsi * nco / result; /* real result                */
        break;
    }
    if (!rc)                           /* good result?               */
                                       /* format the result          */
      rc = MathFormatResult(result, precision, retstr);
  }
  return rc;                           /* return success code        */
}

/*********************************************************************/
/* Function ValidateATrig: Common validation routine for math        */
/* that are of the form fn(number, <precision>, <units>)             */
/*********************************************************************/
LONG  ValidateArcTrig(
  LONG       numargs,                  /* Number of arguments.       */
  RXSTRING   args[],                   /* Function arguments.        */
  PRXSTRING  retstr,                   /* return string              */
  INT        function )                /* function to perform        */
{
  LONG      rc;                        /* validation code            */
  INT       units;                     /* angle type                 */
  double    angle;                     /* working angle              */
  double    nsi;                       /* convertion factor          */
  double    nco;                       /* convertion factor          */
  ULONG     precision;                 /* returned precision         */
  double    x;                         /* input number               */

  rc = VALID_ROUTINE;                  /* set default completion     */
  units = DEGREES;                     /* default angle is degrees   */
  nsi = 1.;                            /* set default conversion     */
  nco = 1.;                            /* set default conversion     */

  RxErrMsgSet1("0");
  SearchPrecision(&precision);

  if (numargs < 1 || numargs > 3)
  {
    RxErrMsgSet1("Invalid number of arguments");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else  if (!RXVALIDSTRING(args[0]))         /* first is omitted           */
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
                                       /* convert input number       */
  else if (sscanf(args[0].strptr, " %lf", &x) != 1)
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (numargs >= 2 &&             /* have a precision           */
      RXVALIDSTRING(args[1]) &&        /* and it is real string      */
      !string2ulong(args[1].strptr, &precision))
  {
    RxErrMsgSet1("The second argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if ( (precision > MAX_PRECISION)  || (precision < MIN_PRECISION) )
  {
    RxErrMsgSet1("The precision is not in the valid range (1-16)");
    rc = INVALID_ROUTINE;
  }
  else if (numargs == 3)
  {                                    /* have an option             */
    if (RXZEROLENSTRING(args[2]))      /* null string?               */
    {
      RxErrMsgSet1("The third argument is invalid");
      rc = INVALID_ROUTINE;            /* this is invalid            */
    }
    else
    {                                  /* process the options        */
                                       /* get the option character   */
      units = toupper(args[2].strptr[0]);
                                       /* was it a good option?      */
      if (units != DEGREES && units != RADIANS && units != GRADES)
      {
        rc = INVALID_ROUTINE;          /* bad option is error        */
        RxErrMsgSet1("The third argument is invalid");
        rc = INVALID_ROUTINE;            /* this is invalid            */
      }
    }
  }

  if (!rc) {                           /* everything went well?      */
                                       /* truncate to maximum        */
//    precision = min(precision, MAX_PRECISION);
    switch (function) {                /* process the function       */
      case ARCSINE:                    /* ArcSine function           */
        angle = asin(x);
        break;
      case ARCCOSINE:                  /* ArcCosine function         */
        angle = acos(x);
        break;
      case ARCTANGENT:                 /* ArcTangent function        */
        angle = atan(x);
        break;
    }
    if (units == DEGREES)              /* have to convert the result?*/
      angle = angle * 180. / pi;       /* make into degrees          */
    else if (units == GRADES)          /* need it in grades?         */
      angle = angle * 200. / pi;       /* convert to base 400        */
                                       /* format the result          */
    rc = MathFormatResult(angle, precision, retstr);
  }
  return rc;                           /* return success code        */
}

/* Mathematical function package *************************************/

/********************************************************************/
/* Functions:           RxCalcSqrt(), RxCalcExp(), RxCalcLog(), RxCalcLog10, */
/* Functions:           RxCalcSinH(), RxCalcCosH(), RxCalcTanH()    */
/* Description:         Returns function value of argument.         */
/* Input:               One number.                                 */
/* Output:              Value of the function requested for arg.    */
/*                      Returns 0 if the function executed OK,      */
/*                      40 otherwise.  The interpreter will fail    */
/*                      if the function returns a negative result.  */
/* Notes:                                                           */
/*   These routines take one to two parameters.                     */
/*   The form of the call is:                                       */
/*   result = func_name(x <, prec>)                                 */
/*                                                                  */
/********************************************************************/
LONG  APIENTRY RxCalcSqrt(             /* Square root function.      */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */
  LONG      rc;                        /* function return code       */

  errno = 0;                                     /* validate the inputs        */
                                       /* validate the inputs        */
  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(sqrt(x), precision, retstr);
  return rc;                           /* return error code          */
}

/*==================================================================*/
LONG  APIENTRY RxCalcExp(              /* Exponential function.      */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation return code     */

  errno = 0;                                     /* validate the inputs        */

  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(exp(x), precision, retstr);
  return rc;                           /* return error code          */
}

/*==================================================================*/
LONG  APIENTRY RxCalcLog(              /* Logarithm function.        */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation return code     */

  errno = 0;                                     /* validate the inputs        */
                                       /* validate the inputs        */
  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(log(x), precision, retstr);
  return rc;                           /* return error code          */
}


/*==================================================================*/
LONG  APIENTRY RxCalcLog10(            /* Log base 10 function.      */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation return code     */

  errno = 0;                                     /* validate the inputs        */
                                       /* validate the inputs        */
  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(log10(x), precision, retstr);
  return rc;                           /* return error code          */
}

/*==================================================================*/
LONG  APIENTRY RxCalcSinH(             /* Hyperbolic sine function.  */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation return code     */

  errno = 0;                                     /* validate the inputs        */
                                       /* validate the inputs        */
  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(sinh(x), precision, retstr);
  return rc;                           /* return error code          */
}

/*==================================================================*/
LONG  APIENTRY RxCalcCosH(             /* Hyperbolic cosine funct.   */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation return code     */

  errno = 0;                                     /* validate the inputs        */
                                       /* validate the inputs        */
  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(cosh(x), precision, retstr);
  return rc;                           /* return error code          */
}

/*==================================================================*/
LONG  APIENTRY RxCalcTanH(             /* Hyperbolic tangent funct.  */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation return code     */

  errno = 0;                                     /* validate the inputs        */
                                       /* validate the inputs        */
  rc = ValidateMath(numargs, args, &x, &precision);
  if (!rc)                             /* good function call         */
                                       /* format the result          */
    rc = MathFormatResult(tanh(x), precision, retstr);
  return rc;                           /* return error code          */
}

/********************************************************************/
/* Functions:           RxCalcPower()                               */
/* Description:         Returns function value of arguments.        */
/* Input:               Two numbers.                                */
/* Output:              Value of the x to the power y.              */
/*                      Returns 0 if the function executed OK,      */
/*                      -1 otherwise.  The interpreter will fail    */
/*                      if the function returns a negative result.  */
/* Notes:                                                           */
/*   This routine takes two to three parameters.                    */
/*   The form of the call is:                                       */
/*   result = func_name(x, y <, prec>)                              */
/*                                                                  */
/********************************************************************/
LONG  APIENTRY RxCalcPower(            /* Power function.           */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  double    x;                         /* input number               */
  double    y;                         /* second input number        */
  ULONG     precision;                 /* precision used             */

  LONG      rc;                        /* validation code            */

  errno = 0;                                     /* validate the inputs        */

  rc = VALID_ROUTINE;                  /* set default completion     */

  RxErrMsgSet1("0");

  SearchPrecision(&precision);

  if (numargs < 2 || numargs > 3)
  {
    RxErrMsgSet1("Invalid number of arguments");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
                                       /* convert input number       */
  else if (!RXVALIDSTRING(args[0]) )   /* first is omitted           */
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (sscanf(args[0].strptr, " %lf", &x) != 1)
  {
    RxErrMsgSet1("The first argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (!RXVALIDSTRING(args[1]) )        /* first is omitted           */
  {
    RxErrMsgSet1("The second argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
                                       /* convert second input       */
  else if (sscanf(args[1].strptr, " %lf", &y) != 1)
  {
    RxErrMsgSet1("The second argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if (numargs == 3 &&             /* have a precision           */
      !string2ulong(args[2].strptr, &precision))
  {
    RxErrMsgSet1("The third argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }

  else if ( (precision > MAX_PRECISION)  || (precision < MIN_PRECISION) )
  {
    RxErrMsgSet1("The precision is not in the valid range (1-16)");
    rc = INVALID_ROUTINE;
  }
                                       /* format the result          */
  if (!rc)
  {
    rc = MathFormatResult(pow(x,y), precision, retstr);
  }
  return rc;                           /* return error code          */
}

/********************************************************************/
/* Functions:           RxCalcSin(), RxCalcCos(), RxCalcTan(), RxCalcCotan() */
/* Description:         Returns trigonometric angle value.          */
/* Input:               Angle in radian or degree or grade          */
/* Output:              Trigonometric function value for Angle.     */
/*                      Returns 0 if the function executed OK,      */
/*                      -1 otherwise.  The interpreter will fail    */
/*                      if the function returns a negative result.  */
/* Notes:                                                           */
/*   These routines take one to three parameters.                   */
/*   The form of the call is:                                       */
/*   x = func_name(angle <, prec> <, [R | D | G]>)                  */
/*                                                                  */
/********************************************************************/
LONG  APIENTRY RxCalcSin(              /* Sine function.             */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateTrig(numargs, args, retstr, SINE);
}

/*==================================================================*/
LONG  APIENTRY RxCalcCos(              /* Cosine function.           */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateTrig(numargs, args, retstr, COSINE);
}

/*==================================================================*/
LONG  APIENTRY RxCalcTan(              /* Tangent function.          */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateTrig(numargs, args, retstr, TANGENT);
}

/*==================================================================*/
LONG  APIENTRY RxCalcCotan(            /* Cotangent function.        */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateTrig(numargs, args, retstr, COTANGENT);
}

/********************************************************************/
/* Functions:           RxCalcPi()                                  */
/* Description:         Returns value of pi for given precision     */
/* Input:               Precision.   Default is 9                   */
/* Output:              Value of the pi to given precision          */
/* Notes:                                                           */
/*   This routine takes one parameters.                             */
/*   The form of the call is:                                       */
/*   result = RxCalcpi(<precision>)                                    */
/*                                                                  */
/********************************************************************/
LONG  APIENTRY RxCalcPi(               /* Pi function                */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
  ULONG     precision;                 /* required precision         */
  LONG rc;
  errno = 0;                                     /* validate the inputs        */
  rc = VALID_ROUTINE;
  SearchPrecision(&precision);

  RxErrMsgSet1("0");               /* setting MATHERROR to 0     */

  if (numargs > 1)
  {
    RxErrMsgSet1("Invalid number of arguments");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
  else if ( (numargs == 1) &&  (!string2ulong(args[0].strptr, &precision)) )
  {
    RxErrMsgSet1("The argument is invalid");
    rc = INVALID_ROUTINE;              /* this is invalid            */
  }
                                       /* keep to maximum            */
  else if ( (precision > MAX_PRECISION)  || (precision < MIN_PRECISION) )
  {
    RxErrMsgSet1("The precision is not in the valid range (1-16)");
    rc = INVALID_ROUTINE;
  }
                                       /* format the result          */
  if (!rc)
  {                           /* good function call         */
     rc = MathFormatResult(pi, precision, retstr); /* format the result */
  }
  return rc;                           /* good result                */
}

/********************************************************************/
/* Functions:           RxCalcArcSin(), RxCalcArcCos(), RxCalcArcTan()*/
/* Description:         Returns angle from trigonometric value.     */
/* Input:               Angle in radian or degree or grade          */
/* Output:              Angle for matching trigonometric value.     */
/*                      Returns 0 if the function executed OK,      */
/*                      -1 otherwise.  The interpreter will fail    */
/*                      if the function returns a negative result.  */
/* Notes:                                                           */
/*   These routines take one to three parameters.                   */
/*   The form of the call is:                                       */
/*   a = func_name(arg <, prec> <, [R | D | G]>)                    */
/*                                                                  */
/********************************************************************/
LONG  APIENTRY RxCalcArcSin(           /* Arc Sine function.         */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateArcTrig(numargs, args, retstr, ARCSINE);
}

/*==================================================================*/
LONG  APIENTRY RxCalcArcCos(           /* Arc Cosine function.       */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateArcTrig(numargs, args, retstr, ARCCOSINE);
}

/*==================================================================*/
LONG  APIENTRY RxCalcArcTan(           /* Arc Tangent function.      */
  PSZ       name,                      /* Function name              */

  LONG      numargs,                   /* Number of arguments        */

  RXSTRING  args[],                    /* Argument array             */

  PSZ       queuename,                 /* Current queue              */

  PRXSTRING retstr )                   /* Return RXSTRING            */

{
                                       /* call common routine        */
  errno = 0;                                     /* validate the inputs        */
  return ValidateArcTrig(numargs, args, retstr, ARCTANGENT);

}

void RxErrMsgSet1(
   PSZ name)
{
   SHVBLOCK shv;
   PSZ  pszVariable;
   PSZ  pszValue;

   pszVariable = (char *)malloc((strlen("MATHERRNO"))+1);
   strcpy(pszVariable,"MATHERRNO");
   pszValue = (char *)malloc((strlen(name)+1));
   strcpy(pszValue, name);

   /*---------------------------------------------------------------
    * set variable pool
    *---------------------------------------------------------------*/
   shv.shvcode            = RXSHV_SYSET;
   shv.shvnext            = NULL;
   shv.shvname.strptr     = pszVariable;
   shv.shvname.strlength  = strlen(pszVariable);
   shv.shvvalue.strptr    = pszValue;
   shv.shvvalue.strlength = strlen(pszValue);

   RexxVariablePool(&shv);
   free(pszVariable);
   free(pszValue);
}

#ifdef __cplusplus
}
#endif

#ifdef WIN32
#pragma optimize( "", on )
#endif