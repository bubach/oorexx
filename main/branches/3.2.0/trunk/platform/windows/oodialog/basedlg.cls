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
/*                                                                            */
/*       Windows Dialog Interface for Object REXX                             */
/* Basic Dialog Class                                                         */
/*                                                                            */
/******************************************************************************/


::requires "plbdlg.cls"
::requires "dlgext.cls"

/******************************************************************************/
/* The class WindowExtensions implements methods that are common to all windows, */
/* no matter whether they are dialogs or dialog items. It's an extension to   */
/* the WindowBase mixin-class                                                 */
/******************************************************************************/

::class 'WindowExtensions' public MIXINCLASS object

::method Init_WindowExtensions
   if RxFuncQuery("InstExtendedMMFuncs") \= 0 then do
      ret = Rxfuncadd("InstExtendedMMFuncs", "oodialog", "InstExtendedMMFuncs")
      if ret = 0 then ret = InstExtendedMMFuncs()
      if ret \= 0 then
      do
         say "Couldn't load function library -->" ret
         call RxFuncDrop("InstExtendedMMFuncs")
         self~InitCode = 1
         return 1
      end
   end
   return 0


::method HideFast unguarded
   return WndShow_Pos("S",self~hwnd, "HIDE FAST")

::method ShowFast unguarded
   return WndShow_Pos("S",self~hwnd, "NORMAL FAST")

::method Display unguarded
   use arg disptype = "NORMAL"
   if disptype = "" then disptype = "NORMAL"; else disptype = disptype~translate
   if self~isA(.DialogControl) & (disptype~wordpos("MIN") <> 0 | disptype~wordpos("MAX") <> 0) then do
     if self~oDlg~isA(.PlainBaseDialog) then
       forward to (self~oDlg)
     else
       return 1
   end
   return WndShow_Pos("S",self~hwnd, disptype)

::method SetFont unguarded
   use arg hFont, bRedraw     /* WM_SETFONT */
   if Arg(2, 'o') = 1 then bRedraw = 1
   return SendWinMsg("ANY",self~hwnd, "0x00000030", hFont, bRedraw)

::method GetRect unguarded
   return WindowRect("GET", self~Hwnd)

::method GetClientRect unguarded
   use arg hwnd
   if Arg(1,'o') = 1 then hwnd = self~hwnd
   return WindowRect("GET", hwnd, "CLIENT")

::method SetRect unguarded
   use arg x, y, width, high, showOptions
   if Arg(5,"o") = 1 then showOptions = ""; else showOptions = showOptions~translate
   return WndShow_Pos("P",self~hwnd, x, y, width, high, showOptions)

::method Update unguarded
   return WndShow_Pos("S",self~Hwnd, "UPDATE")

   /* This method draws the window */
::method Draw unguarded
   return WindowRect("RDW", self~hwnd, "")

::method Redraw unguarded
   return WndShow_Pos("S",self~hwnd, "REDRAW")

::method RedrawClient unguarded
   use arg erasebkg
   if Arg(1, 'o') = 1 then erasebkg = 0
   return WindowRect("RDW", self~Hwnd, erasebkg)

::method GetDC unguarded
   return HandleDC_Obj("G", self~hwnd)

::method FreeDC unguarded
   use arg dc
   return HandleDC_obj("F", self~hwnd, dc)

::method HScrollPos unguarded
    return WndShow_Pos("B", self~hwnd, 0)

::method SetHScrollPos unguarded
    use arg pos, redraw
    if Arg(2, 'o') = 1 then redraw = 1
    return WndShow_Pos("B", self~hwnd, 0, pos, redraw)

::method VScrollPos unguarded
    return WndShow_Pos("B", self~hwnd, 1)

::method SetVScrollPos unguarded
    use arg pos, redraw
    if Arg(2, 'o') = 1 then redraw = 1
    return WndShow_Pos("B", self~hwnd, 1, pos, redraw)

::method Scroll unguarded
    use arg x, y
    return WndShow_Pos("M", self~hwnd, x, y)

::method ScreenToClient unguarded
    use arg x,y
    return Wnd_Desktop("COORD", self~hwnd, x, y, "S2C")

::method ClientToScreen unguarded
    use arg x,y
    return Wnd_Desktop("COORD", self~hwnd, x, y, "C2S")

::method SetForegroundWindow unguarded
    use arg hwnd
    return Wnd_Desktop("TOP", hwnd)

::method ForegroundWindow unguarded
   return Wnd_Desktop("FG")

::method SetCursorPos unguarded
   use arg x, y
   return Wnd_Desktop("CURSOR", x, y)

::method CursorPos unguarded
   return Wnd_Desktop("CURSOR")

::method RestoreCursorShape unguarded
   use arg cursor
   return Wnd_Desktop("CURSOR", self~hwnd, "R", cursor)

::method Cursor_Arrow unguarded
   return Wnd_Desktop("CURSOR", self~hwnd, "R", 0)

::method Cursor_AppStarting unguarded
   return Wnd_Desktop("CURSOR", self~hwnd, "S", 32650)

::method Cursor_Cross unguarded
   return Wnd_Desktop("CURSOR", self~hwnd, "S", 32515)

::method Cursor_No unguarded
   return Wnd_Desktop("CURSOR", self~hwnd, "S", 32648)

::method Cursor_Wait unguarded
   return Wnd_Desktop("CURSOR", self~hwnd, "S", 32514)

::method CreateFont unguarded
   use arg fontName, fontSize, fontStyle, fontWidth
   if Arg(1, "o") = 1 then fontName = "System"
   if Arg(2, "o") = 1 then fontSize = 10
   if Arg(3, "o") = 1 then fontStyle = ""
   if Arg(4, "o") = 1 then fontWidth = fontSize
   return HandleFont("CREATE", fontName, fontSize, fontStyle, fontWidth)

   /* Deletes a font */
::method DeleteFont unguarded
   use arg hFont
   return self~DeleteObject(hFont)

   /* This method deletes a graphic object */
::method DeleteObject unguarded
   use arg obj
   return HandleDC_Obj("D", obj)

   /* This method loads a bitmap from file into memory */
   /* It returns a handle to the bitmap */

::method LoadBitmap unguarded
   use arg bmpFilename, option
   if Arg(2, 'o') = 1 then option = ""; else option = option~translate
   return LoadRemoveBitmap(0 /* NULL Adm */, bmpFilename, "LOAD" || option)

   /* This method will free a memory bitmap */

::method RemoveBitmap unguarded
   use arg hBitmap
   return LoadRemoveBitmap(0 /* NULL Adm */, hBitmap, "REMOVE")

::method CreateBrush unguarded
    use arg color, brushSpecifier
    if Arg() = 0 then return HandleDC_Obj("B")
    if Arg(1, "o") = 1 then color = 1
    if Arg(2, "o") = 1 then return HandleDC_Obj("B", color)
    brushSpecifier = brushSpecifier~translate
    if brushSpecifier = "UPDIAGONAL" | brushSpecifier = "DOWNDIAGONAL" | brushSpecifier = "CROSS" | brushSpecifier = "DIAGCROSS",
    | brushSpecifier = "HORIZONTAL" | brushSpecifier = "VERTICAL" then return HandleDC_Obj("B", color, brushSpecifier)
    else return HandleDC_Obj("B", 0 /* NULL ADM */, color, brushSpecifier)  /* brushSpecifier must be filename */

   /* This method allows you to write text to a window in the given font, in */
   /* the given size, and to the given position */
   /* argument 'fontStyle' can be one or more off: */
   /*    "THIN"            "UNDERLINE"    */
   /*    "EXTRALIGHT"      "ITALIC"       */
   /*    "LIGHT"           "STRIKEOUT"    */
   /*    "MEDIUM"                */
   /*    "SEMIBOLD"              */
   /*    "EXTRABOLD"             */
   /*    "BOLD"                  */
   /*    "HEAVY"                 */

::method Write unguarded
   argarr = Arg(1, "A")
   newarg = .array~new(argarr~Items+1)
   do i = 1 to Arg(); newarg[i+1] = argarr[i]; end
   newarg[1] = self~hwnd
   forward message (WriteToWindow) arguments (newarg)

   /* This method allows you to write text to a device context to a given */
   /* position */

::method WriteDirect unguarded
   use arg dc, xPos, yPos, text
   return WriteText(dc, xPos, yPos, text)               /* 4 arguments means don't use font */

   /* This method loads a graphic object into device context */

::method ObjectToDC unguarded
   use arg dc, obj
   return HandleDC_Obj("S", dc, obj)

   /* Loads font into device context of a window. */
   /* Use 'createFont' method to get a font handle */

::method FontToDC unguarded
   use arg dc, hFont
   return self~ObjectToDC(dc, hFont)

   /* Set the font color of a device context. */
   /* Use 'createFont' method to get a font handle */

::method FontColor unguarded
   use arg color, dc
   if Arg(1,'o') = 1 then color = 1
   return DrawGetSet("COL", dc, color)


   /* This method returns the text size from a device context */
::method GetStdTextSize unguarded
    use arg dc, text
    if Arg(1,'o') = 1 then do
      parse value GetStdTextSize(text) with width height
      width = width * self~FactorX
      height = height * self~FactorY
      return width height
    end
    else return HandleFont( "SIZE", dc, text )


   /* This method will create a pen in the given color and style */
   /* It returns a handle to a pen object */

::method CreatePen unguarded
   use arg width, style, color
   if Arg(1, "o") = 1 then width = 1
   if Arg(2, "o") = 1 then style = "SOLID"; else style = style~translate
   if Arg(3, "o") = 1 then color = 0
   return HandleDC_Obj("P", width, style, color)

   /* This method will draw a rectangle to the given device context */
   /* Use one of the following methods to get a valid DC: */
   /* 'GetDC', 'GetWindowDC', 'GetButtonDC' */

::method Rectangle unguarded
   use arg dc, x, y, cx, cy, fill
   if Arg(6, "o") = 1 then fill = ''
   if fill~left(1)~translate = 'F' then
        return DCDraw("REC", dc, x, y, cx, cy)
   ret = DrawGetSet("SDP", dc, x, y)
   ret = DCDraw("LN", dc, cx, y)
   ret = DCDraw("LN", dc, cx, cy)
   ret = DCDraw("LN", dc, x, cy)
   return DCDraw("LN", dc, x, y)

   /* This method draws a line within the device context */

::method DrawLine unguarded
   use arg dc, fromX, fromY, toX, toY
   if Arg(2, 'o') = 0 | Arg(3, 'o') = 0 then ret = DrawGetSet("SDP",dc, fromX, fromY)
   return DCDraw("LN",dc, toX, toY)

   /* This method draws a pixel within the device context */

::method DrawPixel unguarded
   use arg dc, x, y, color
   return DCDraw("PT",dc, X, Y, color)

   /* This method gets the color of a pixel within the device context */

::method GetPixel unguarded
   use arg dc, x, y
   return DrawGetSet("GPT", dc, X, Y)

   /* fill with current brush, border determined by color */
::method FillDrawing unguarded
   use arg dc, x, y, color
   return DCDraw("FL", dc, X, Y, color)

::method TransparentText unguarded
   use arg dc
   return DrawGetSet("SBK", dc, "TRANSPARENT")

::method OpaqueText unguarded
   use arg dc
   return DrawGetSet("SBK", dc, "OPAQUE")

   /* This method draws an arc / circle  */

::method DrawArc unguarded
   use arg dc, left, top, right, bottom, startx, starty, endx, endy
   return DCDraw("ARC",dc, left, top, right, bottom, startx, starty, endx, endy)

   /* This method draws a pie shape */

::method DrawPie unguarded
   use arg dc, left, top, right, bottom, xrad1, yrad1, xrad2, yrad2
   return DCDraw("PIE",dc, left, top, right, bottom, xrad1, yrad1, xrad2, yrad2)

   /* This method draws an arc / circle using an angle */

::method DrawAngleArc unguarded
   use arg dc, movex, movey, x, y, radius, startangle, sweepangle
   if Arg(2, 'o') = 0 | Arg(3, 'o') = 0 then ret = DrawGetSet("SDP", dc, movex, movey)
   return DCDraw("ANG",dc, x, y, radius, startangle, sweepangle)

::method SetArcDirection unguarded
   use arg dc, direction
   return DrawGetSet("SAD", dc, (direction~translate~wordpos("CLOCKWISE") > 0))

::method GetArcDirection unguarded
   use arg dc
   ret = DrawGetSet("GAD",dc)
   if ret = 1 then return "CLOCKWISE"
   else return "COUNTERCLOCKWISE"

::method LogRect2AbsRect unguarded
   parse arg l, t, r, b
   ret.left = l*self~FactorX
   ret.right = r*self~FactorX
   ret.top = t*self~FactorY
   ret.bottom = b*self~FactorY
   return ret.

::method AbsRect2LogRect unguarded
   parse arg l, t, r, b
   ret.left = l/self~FactorX
   ret.right = r/self~FactorX
   ret.top = t/self~FactorY
   ret.bottom = b/self~FactorY
   return ret.

    /* create a COLORREF */
::method RGB   /* currently only color indexes are supported by functions using colors */
   use arg red, green, blue
   if Arg(1,'o') = 1 then red = 0
   if Arg(2,'o') = 1 then green = 0
   if Arg(3,'o') = 1 then blue = 0
   return (blue*256*256) + (green*256) + red



/******************************************************************************/
/* The class BaseDialog implements methods that are common to a dialog        */
/* by Resource Workshop (ResDialog) and to a dialog created by using Add...   */
/* methods (UserDialog).                                 */
/******************************************************************************/

::class 'BaseDialog' public subclass PlainBaseDialog inherit DialogExtensions WindowExtensions

::method ScrollNow attribute        /* Indicator whether or not scrolling is active */

::method Init
   forward class (super) continue
   if result <> 0 then return result

   self~ScrollNow = 0      /* a kind of semaphore to handle multiple text scrolling */
   self~InitCode = self~Init_WindowExtensions
   if self~InitCode \= 0 then return self~InitCode

   self~BkgBitmap = 0  /* no background bitmap */
   self~BkgBrushBmp = 0  /* no background bitmap */
   return 0