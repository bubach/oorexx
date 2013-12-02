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
#include <windows.h>
#define INCL_REXXSAA
#include <rexx.h>
#include <stdio.h>
#include <dlgs.h>
#include <malloc.h>
#ifdef __CTL3D
#include <ctl3d.h>
#endif
#include "oovutil.h"

extern WPARAM InterruptScroll = 0;
extern HWND ScrollingButton = NULL;
extern HWND RedrawScrollingButton = NULL;
HANDLE TimerEvent = NULL;
ULONG TimerCount = 0;
ULONG Timer = 0;

#define GETWEIGHT(opts, weight) \
      if (strstr(opts, "THIN")) weight = FW_THIN; else \
      if (strstr(opts, "EXTRALIGHT")) weight = FW_EXTRALIGHT; else \
      if (strstr(opts, "LIGHT")) weight = FW_LIGHT; else \
      if (strstr(opts, "MEDIUM")) weight = FW_MEDIUM; else \
      if (strstr(opts, "SEMIBOLD")) weight = FW_SEMIBOLD; else \
      if (strstr(opts, "EXTRABOLD")) weight = FW_EXTRABOLD; else \
      if (strstr(opts, "BOLD")) weight = FW_BOLD; else \
      if (strstr(opts, "HEAVY")) weight = FW_HEAVY; else \
      weight = FW_NORMAL;



void DrawFontToDC(HDC hDC, INT x, INT y, CHAR * text, INT size, CHAR * opts, CHAR * fontn, INT fgColor, INT bkColor)
{
   HFONT hFont, oldF;
   INT weight, oldMode=0;
   COLORREF oldFg, oldBk;

   GETWEIGHT(opts, weight)

   hFont = CreateFont(size, size, 0, 0, weight, (BOOL)strstr(opts, "ITALIC"), (BOOL)strstr(opts, "UNDERLINE"),
               (BOOL)strstr(opts, "STRIKEOUT"), DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, fontn);

   oldF = SelectObject(hDC, hFont);
   if (strstr(opts, "TRANSPARENT")) oldMode = SetBkMode(hDC, TRANSPARENT);
   else if (strstr(opts, "OPAQUE")) oldMode = SetBkMode(hDC, OPAQUE);
   if (fgColor != -1) oldFg = SetTextColor(hDC, PALETTEINDEX(fgColor));
   if (bkColor != -1) oldBk = SetBkColor(hDC, PALETTEINDEX(bkColor));


   TextOut(hDC, x, y, text, strlen(text));
   SelectObject(hDC, oldF);
   DeleteObject(hFont);
   if (oldMode) SetBkMode(hDC, oldMode);
   if (fgColor != -1) SetTextColor(hDC, oldFg);
   if (bkColor != -1) SetBkColor(hDC, oldBk);
}


ULONG APIENTRY WriteText(
  PUCHAR funcname,
  ULONG argc,
  RXSTRING argv[],
  PUCHAR qname,
  PRXSTRING retstr )
{
   HWND w;
   HDC hDC;

   if (argc >= 7)
   {
       INT bkC = -1, fgC = -1;
       w = (HWND)atol(argv[0].strptr);

       if (strstr(argv[6].strptr, "CLIENT"))
           hDC = GetDC(w);
       else
           hDC = GetWindowDC(w);

       if (argc >= 8) fgC = atoi(argv[7].strptr);
       if (argc >= 9) bkC = atoi(argv[8].strptr);

       if (hDC)
       {
                             /* x                     y                    text                size                options      fontname */
          DrawFontToDC(hDC, atoi(argv[1].strptr), atoi(argv[2].strptr), argv[3].strptr, atoi(argv[5].strptr), argv[6].strptr, argv[4].strptr, fgC, bkC);
          ReleaseDC(w, hDC);
          RETC(0)
       }
   }
   else
   {
       CHECKARG(4);

       if (NULL != (hDC = (HDC)atol(argv[0].strptr)))
       {
          TextOut(hDC, atoi(argv[1].strptr), atoi(argv[2].strptr), argv[3].strptr, argv[3].strlength);
          RETC(0)
       }
   }
   RETC(1)
}


VOID CALLBACK ScrollTimerProc(
    HWND  hwnd,    // handle of window for timer messages
    UINT  uMsg,    // WM_TIMER message
    UINT  idEvent,    // timer identifier
    DWORD  dwTime     // current system time
   )
{
    SetEvent(TimerEvent);
}



ULONG APIENTRY ScrollText(
  PUCHAR funcname,
  ULONG argc,
  RXSTRING argv[],
  PUCHAR qname,
  PRXSTRING retstr )
{
   INT disply;
   PCHAR opts;
   INT size;
   PCHAR text;
   INT col;

   CHAR * tp;
   HWND w;
   HDC hDC;
   HFONT hFont, oldF;
   HPEN hpen, oP;
   HBRUSH oB, hbr;
   RECT r, rs, rclip;
   SIZE s, sone;
   INT i, rc, sl, step, j, disp, weight;
   UINT sleep;
   DEF_ADM;

   CHECKARG(10);

   GET_ADM;

   if (!dlgAdm) RETERR

   text = argv[2].strptr;
   size = atoi(argv[4].strptr);
   opts = argv[5].strptr;
   disply = atoi(argv[6].strptr);
   col = atoi(argv[9].strptr);

   w = (HWND)atol(argv[1].strptr);
   step = atoi(argv[7].strptr);
   tp = text;

   if (NULL != (hDC = GetWindowDC(w)))
   {
      GetWindowRect(w, &r);

      GETWEIGHT(opts, weight)

      hFont = CreateFont(size, size, 0, 0, weight, (BOOL)strstr(opts, "ITALIC"), (BOOL)strstr(opts, "UNDERLINE"),
                 (BOOL)strstr(opts, "STRIKEOUT"), DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, FF_DONTCARE, argv[3].strptr);

      oldF = SelectObject(hDC, hFont);
      if (dlgAdm && dlgAdm->Use3DControls)
      {
         hpen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE));
         hbr = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
         SetBkColor(hDC, GetSysColor(COLOR_BTNFACE));
         oP = SelectObject(hDC, hpen);
         oB = SelectObject(hDC, hbr);
      } else
         oP = SelectObject(hDC, GetStockObject(WHITE_PEN));

      if (col > 0) SetTextColor(hDC, PALETTEINDEX(col));
      sl = strlen(text);
      rc = GetTextExtentPoint32(hDC, text, sl, &s);

      r.right = r.right - r.left;
      r.bottom = r.bottom - r.top + disply;
      r.top = disply;
      r.left = 0;

      j = 0;
      disp = 0;
      rc = GetTextExtentPoint32(hDC, tp, 1, &sone);
      rclip= r;
      rs.top = r.top;
      rs.bottom = r.top+s.cy+2;
      rs.right = r.right;
      rs.left = r.right;

      sleep = atoi(argv[8].strptr);
      if (sleep)
      {
          if (!TimerEvent)
          {
              TimerEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
              Timer = SetTimer(NULL,GetCurrentThreadId(), sleep, ScrollTimerProc);
              TimerCount++;
          }
          else TimerCount++;
      }
      else Timer = 0;

      ScrollingButton = w;
      for (i=step; i<=r.right+s.cx; i+=step)
      {
         if (i>=s.cx+step)
            Rectangle(hDC, r.right-i+s.cx, r.top, r.right -i+s.cx+step+step, r.top + s.cy + 2);

         if (j<sl)
         {
             if (RedrawScrollingButton == w)
                 rc = TextOut(hDC, r.right - i, r.top, text, sl);
             else rc = TextOut(hDC, r.right - i+disp, r.top, tp, 1);
         }
         if ((j<sl) && (!rc)) break;

         RedrawScrollingButton = NULL;

         if (i-disp>sone.cx)
         {
            tp++;
            j++;
            disp += sone.cx;
            rc = GetTextExtentPoint32(hDC, tp, 1, &sone);
         }

         rs.left -= step;
         rc = 0;

         if (dlgAdm->StopScroll == (WPARAM) w)
         {
            dlgAdm->StopScroll = 0;
            break;
         }

         if (!ScrollDC(hDC, -step, 0, &rs, &rclip, NULL, NULL)) break;

         if (Timer)
         {
             WaitForSingleObject(TimerEvent, (int)sleep*1.5);
             ResetEvent(TimerEvent);
         }

      }

      if (Timer)
      {
         if (TimerCount == 1)
         {
             KillTimer(NULL, Timer);
             if (TimerEvent) CloseHandle(TimerEvent);
             TimerEvent = NULL;
             TimerCount = 0;
             Timer = 0;
         } else TimerCount--;
      }

      ScrollingButton = NULL;

      if (!dlgAdm || (!IsWindow(dlgAdm->TheDlg))) RETC(1)

      Rectangle(hDC, r.left, r.top, r.right, r.bottom);

      SelectObject(hDC, oldF);
      SelectObject(hDC, oP);
      if (dlgAdm->Use3DControls)
      {
         SelectObject(hDC, oB);
         DeleteObject(hpen);
         DeleteObject(hbr);
      }

      DeleteObject(hFont);
      ReleaseDC(w, hDC);
      RETC(0)
   }
   RETC(1)
}



ULONG APIENTRY HandleFont(
  PUCHAR funcname,
      ULONG argc,
  RXSTRING argv[],
  PUCHAR qname,
  PRXSTRING retstr )
{
   CHECKARGL(3);

   if (!strcmp(argv[0].strptr, "CREATE"))
   {
       HFONT hFont;
       INT weight;
       CHECKARG(5);

       GETWEIGHT(argv[3].strptr, weight)

       hFont = CreateFont(atoi(argv[2].strptr), atoi(argv[4].strptr), 0, 0, weight, (BOOL)strstr(argv[3].strptr, "ITALIC"), (BOOL)strstr(argv[3].strptr, "UNDERLINE"),
                   (BOOL)strstr(argv[3].strptr, "STRIKEOUT"), DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, argv[1].strptr);

       if (hFont)
       {
           ultoa((ULONG)hFont, retstr->strptr, 10);
           retstr->strlength = strlen(retstr->strptr);
           return 0;
       }
       RETC(0)
   }
   else
   if (!strcmp(argv[0].strptr, "SIZE"))
   {
       HDC hDC;
       SIZE s;

       hDC = (HDC)atol(argv[1].strptr);
       if (hDC)
       {
         if (GetTextExtentPoint32(hDC, argv[2].strptr, argv[2].strlength, &s))
         {
             sprintf(retstr->strptr, "%ld %ld", s.cx, s.cy);
             retstr->strlength = strlen(retstr->strptr);
             return 0;
         }
       }
       RETC(0)
   }
   RETC(1)
}