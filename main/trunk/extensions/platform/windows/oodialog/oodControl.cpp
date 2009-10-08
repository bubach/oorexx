/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2009 Rexx Language Association. All rights reserved.    */
/*                                                                            */
/* This program and the accompanying materials are made available under       */
/* the terms of the Common Public License v1.0 which accompanies this         */
/* distribution. A copy is also available at the following address:           */
/* http://www.oorexx.org/license.html                                         */
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

/**
 * oodControl.cpp
 *
 * Contains the base classes used for an object that represents a Windows
 * Control.
 */
#include "ooDialog.hpp"     // Must be first, includes windows.h and oorexxapi.h

#include <stdio.h>
#include <commctrl.h>
#include <shlwapi.h>
#include "APICommon.hpp"
#include "oodCommon.hpp"
#include "oodMessaging.hpp"
#include "oodText.hpp"
#include "oodData.hpp"
#include "oodControl.hpp"

uint32_t listViewStyle(CSTRING opts, uint32_t style)
{
    if ( StrStrI(opts, "VSCROLL"      ) != NULL ) style |= WS_VSCROLL;
    if ( StrStrI(opts, "HSCROLL"      ) != NULL ) style |= WS_HSCROLL;
    if ( StrStrI(opts, "EDIT"         ) != NULL ) style |= LVS_EDITLABELS;
    if ( StrStrI(opts, "SHOWSELALWAYS") != NULL ) style |= LVS_SHOWSELALWAYS;
    if ( StrStrI(opts, "ALIGNLEFT"    ) != NULL ) style |= LVS_ALIGNLEFT;
    if ( StrStrI(opts, "ALIGNTOP"     ) != NULL ) style |= LVS_ALIGNTOP;
    if ( StrStrI(opts, "AUTOARRANGE"  ) != NULL ) style |= LVS_AUTOARRANGE;
    if ( StrStrI(opts, "ICON"         ) != NULL ) style |= LVS_ICON;
    if ( StrStrI(opts, "SMALLICON"    ) != NULL ) style |= LVS_SMALLICON;
    if ( StrStrI(opts, "LIST"         ) != NULL ) style |= LVS_LIST;
    if ( StrStrI(opts, "REPORT"       ) != NULL ) style |= LVS_REPORT;
    if ( StrStrI(opts, "NOHEADER"     ) != NULL ) style |= LVS_NOCOLUMNHEADER;
    if ( StrStrI(opts, "NOWRAP"       ) != NULL ) style |= LVS_NOLABELWRAP;
    if ( StrStrI(opts, "NOSCROLL"     ) != NULL ) style |= LVS_NOSCROLL;
    if ( StrStrI(opts, "NOSORTHEADER" ) != NULL ) style |= LVS_NOSORTHEADER;
    if ( StrStrI(opts, "SHAREIMAGES"  ) != NULL ) style |= LVS_SHAREIMAGELISTS;
    if ( StrStrI(opts, "SINGLESEL"    ) != NULL ) style |= LVS_SINGLESEL;
    if ( StrStrI(opts, "ASCENDING"    ) != NULL ) style |= LVS_SORTASCENDING;
    if ( StrStrI(opts, "DESCENDING"   ) != NULL ) style |= LVS_SORTDESCENDING;
    return style;
}


const char *controlType2winName(oodControl_t control)
{
    switch ( control )
    {
        case winStatic :               return WC_STATIC;
        case winPushButton :           return WC_BUTTON;
        case winRadioButton :          return WC_BUTTON;
        case winCheckBox :             return WC_BUTTON;
        case winGroupBox :             return WC_BUTTON;
        case winEdit :                 return WC_EDIT;
        case winListBox :              return WC_LISTBOX;
        case winComboBox :             return WC_COMBOBOX;
        case winScrollBar :            return WC_SCROLLBAR;
        case winTreeView :             return WC_TREEVIEW;
        case winListView :             return WC_LISTVIEW;
        case winTab :                  return WC_TABCONTROL;
        case winProgressBar :          return PROGRESS_CLASS;
        case winTrackBar :             return TRACKBAR_CLASS;
        case winMonthCalendar :        return MONTHCAL_CLASS;
        case winDateTimePicker :       return DATETIMEPICK_CLASS;
        default :                      return "";
    }
}


const char *controlType2className(oodControl_t control)
{
    switch ( control )
    {
        case winStatic :               return "STATICCONTROL";
        case winPushButton :           return "BUTTONCONTROL";
        case winRadioButton :          return "RADIOBUTTON";
        case winCheckBox :             return "CHECKBOX";
        case winGroupBox :             return "GROUPBOX";
        case winEdit :                 return "EDITCONTROL";
        case winListBox :              return "LISTBOX";
        case winComboBox :             return "COMBOBOX";
        case winScrollBar :            return "SCROLLBAR";
        case winTreeView :             return "TREECONTROL";
        case winListView :             return "LISTCONTROL";
        case winTab :                  return "TABCONTROL";
        case winProgressBar :          return "PROGRESSBAR";
        case winTrackBar :             return "SLIDERCONTROL";
        case winMonthCalendar :        return "MONTHCALENDAR";
        case winDateTimePicker :       return "DATETIMEPICKER";
        default :                      return "";
    }
}


oodControl_t winName2controlType(const char *className)
{
    if (      strcmp(className, WC_STATIC         ) == 0 ) return winStatic;
    else if ( strcmp(className, WC_BUTTON         ) == 0 ) return winPushButton;
    else if ( strcmp(className, WC_EDIT           ) == 0 ) return winEdit;
    else if ( strcmp(className, WC_LISTBOX        ) == 0 ) return winListBox;
    else if ( strcmp(className, WC_COMBOBOX       ) == 0 ) return winComboBox;
    else if ( strcmp(className, WC_SCROLLBAR      ) == 0 ) return winScrollBar;
    else if ( strcmp(className, WC_TREEVIEW       ) == 0 ) return winTreeView;
    else if ( strcmp(className, WC_LISTVIEW       ) == 0 ) return winListView;
    else if ( strcmp(className, WC_TABCONTROL     ) == 0 ) return winTab;
    else if ( strcmp(className, PROGRESS_CLASS    ) == 0 ) return winProgressBar;
    else if ( strcmp(className, TRACKBAR_CLASS    ) == 0 ) return winTrackBar;
    else if ( strcmp(className, MONTHCAL_CLASS    ) == 0 ) return winMonthCalendar;
    else if ( strcmp(className, DATETIMEPICK_CLASS) == 0 ) return winDateTimePicker;
    else
    {
        return winUnknown;
    }
}

oodControl_t control2controlType(HWND hControl)
{
    oodControl_t type = winUnknown;

    TCHAR buf[64];
    if ( RealGetWindowClass(hControl, buf, sizeof(buf)) )
    {
        type = winName2controlType(buf);
        if ( type == winPushButton )
        {
            BUTTONTYPE buttonType = getButtonInfo(hControl, NULL, NULL);
            if ( buttonType == check )
            {
                type = winCheckBox;
            }
            else if ( buttonType == radio )
            {
                type = winRadioButton;
            }
            else if ( buttonType == group )
            {
                type = winGroupBox;
            }
        }
    }

    return type;
}

/**
 * Determine if a dialog control belongs to the specified dialog control class.
 *
 * @param hControl   Handle to the control.
 * @param control    One of the oodControl types specifying the class to check
 *                   for.
 *
 * @return True if the dialog control is the type specified, otherwise false.
 */
bool isControlMatch(HWND hControl, oodControl_t control)
{
    char buf[64];
    const char *pClass = controlType2winName(control);

    if ( ! RealGetWindowClass(hControl, buf, sizeof(buf)) || strcmp(buf, pClass) != 0 )
    {
        return false;
    }

    if ( control == winCheckBox || control == winRadioButton || control == winGroupBox )
    {
        BUTTONTYPE type = getButtonInfo(hControl, NULL, NULL);
        switch ( control )
        {
            case winCheckBox :
                if ( type != check )
                {
                    return false;
                }
                break;
            case winRadioButton :
                if ( type != radio )
                {
                    return false;
                }
                break;
            case winGroupBox :
                if ( type != group )
                {
                    return false;
                }
                break;
        }
    }
    return true;
}

/**
 * Resolves a string to the type of windows control it is.  The function only
 * compares enough letters to determine unequivocally if it matches one of the
 * supported dialog controls.
 *
 * Example:
 *
 * CSTRING msgName = "CONNECTEDITDATA";
 * oodControl_t ctrl = oodName2controlType(msgName + 7);
 *
 * @param name   The name to resolve.
 *
 * @return The windows control type.  winUnknown is returned for no match and
 *         the name "separator" is special cased to winNotAControl.  (Separator
 *         is used along with the data table stuff.)
 *
 * @remarks  There are some generic message names such as getControlDataPage
 *           that need to match to winUnknown.  CO is not sufficient to
 *           distinguish between comboBox and control.
 */
oodControl_t oodName2controlType(CSTRING name)
{
    if      ( StrCmpN(name, "CHECKBOX", 3      ) == 0 ) return winCheckBox;
    else if ( StrCmpN(name, "COMBOBOX", 3      ) == 0 ) return winComboBox;
    else if ( StrCmpN(name, "DATETIMEPICKER", 1) == 0 ) return winDateTimePicker;
    else if ( StrCmpN(name, "EDIT", 1          ) == 0 ) return winEdit;
    else if ( StrCmpN(name, "GROUPBOX", 1      ) == 0 ) return winGroupBox;
    else if ( StrCmpN(name, "LISTBOX", 5       ) == 0 ) return winListBox;
    else if ( StrCmpN(name, "LISTVIEW", 5      ) == 0 ) return winListView;
    else if ( StrCmpN(name, "MONTHCALENDAR", 1 ) == 0 ) return winMonthCalendar;
    else if ( StrCmpN(name, "PROGRESSBAR", 2   ) == 0 ) return winProgressBar;
    else if ( StrCmpN(name, "PUSHBUTTON", 2    ) == 0 ) return winPushButton;
    else if ( StrCmpN(name, "RADIOBUTTON", 1   ) == 0 ) return winRadioButton;
    else if ( StrCmpN(name, "SCROLLBAR", 2     ) == 0 ) return winScrollBar;
    else if ( StrCmpN(name, "SEPARATOR", 2     ) == 0 ) return winNotAControl;
    else if ( StrCmpN(name, "STATIC", 2        ) == 0 ) return winStatic;
    else if ( StrCmpN(name, "TAB", 3           ) == 0 ) return winTab;
    else if ( StrCmpN(name, "TRACKBAR", 3      ) == 0 ) return winTrackBar;
    else if ( StrCmpN(name, "TREEVIEW", 3      ) == 0 ) return winTreeView;
    else return winUnknown;
}

RexxClassObject oodClass4controlType(RexxMethodContext *c, oodControl_t controlType)
{
    RexxClassObject controlClass = NULLOBJECT;
    const char *className = controlType2className(controlType);

    controlClass = rxGetContextClass(c, className);
    if ( controlClass == NULLOBJECT )
    {
        // An exception has been raised, which we don't want.  So, clear it.
        c->ClearCondition();
    }
    return controlClass;
}


/**
 *  Methods for the .DialogControl class.
 */
#define DIALOGCONTROL_CLASS        "DialogControl"


/**
 * If there is subclass data, free it.
 */
static void freeSubclassData(SUBCLASSDATA * pData)
{
    if ( pData )
    {
        freeKeyPressData(pData->pKeyPressData);
        LocalFree((void *)pData);
    }
}


/**
 * Subclass procedure for any dialog control.  Reports key press events to
 * ooDialog for those key presses connected to an ooDialog method by the user.
 *
 * All messages are passed on unchanged to the control.
 *
 * processKeyPress() is used to actually decipher the key press data and set
 * up the ooDialog method invocation.  That function documents what is sent on
 * to the ooDialog method.
 */
LRESULT CALLBACK KeyPressSubclassProc(HWND hwnd, UINT msg, WPARAM wParam,
  LPARAM lParam, UINT_PTR id, DWORD_PTR dwData)
{
    KEYPRESSDATA *pKeyData;
    SUBCLASSDATA *pData = (SUBCLASSDATA *)dwData;
    if ( ! pData ) return DefSubclassProc(hwnd, msg, wParam, lParam);

    pKeyData = pData->pKeyPressData;

    switch ( msg )
    {
        case WM_GETDLGCODE:
            /* Don't do anything for now. This message has some interesting
             * uses, perhaps a future enhancement.
             */
            break;

        case WM_SYSKEYDOWN :
            /* Sent when the alt key is down.  We need both WM_SYSKEYDOWN and
             * WM_KEYDOWN to catch everything that a keyboard hook catches.
             */
            if (  pKeyData->key[wParam] && !(lParam & KEY_REALEASE) && !(lParam & KEY_WASDOWN) )
            {
                processKeyPress(pKeyData, wParam, lParam, pData->pMessageQueue);
            }
            break;

        case WM_KEYDOWN:
            /* WM_KEYDOWN will never have KEY_RELEASE set. */
            if (  pKeyData->key[wParam] && !(lParam & KEY_WASDOWN) )
            {
                processKeyPress(pKeyData, wParam, lParam, pData->pMessageQueue);
            }
            break;

        case WM_NCDESTROY:
            /* The window is being destroyed, remove the subclass, clean up
             * memory.
             */
            RemoveWindowSubclass(hwnd, KeyPressSubclassProc, id);
            if ( pData )
            {
                freeSubclassData(pData);
            }
            break;
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

/**
 * Convenience function to remove the key press subclass procedure and free the
 * associated memory.
 *
 */
static BOOL removeKeyPressSubclass(SUBCLASSDATA *pData, HWND hDlg, INT id)
{
    BOOL success = SendMessage(hDlg, WM_USER_SUBCLASS_REMOVE, (WPARAM)&KeyPressSubclassProc, (LPARAM)id) != 0;
    if ( success )
    {
        freeSubclassData(pData);
    }
    return success;
}


static keyPressErr_t connectKeyPressSubclass(RexxMethodContext *c, CSTRING methodName, CSTRING keys, CSTRING filter,
                                             pCDialogControl pcdc)
{
    keyPressErr_t result = nameErr;
    if ( ! requiredComCtl32Version(c, c->GetMessageName(), COMCTL32_6_0) )
    {
        goto done_out;
    }
    if ( *methodName == '\0' )
    {
        c->RaiseException1(Rexx_Error_Invalid_argument_null, TheOneObj);
        goto done_out;
    }
    if ( *keys == '\0' )
    {
        c->RaiseException1(Rexx_Error_Invalid_argument_null, TheTwoObj);
        goto done_out;
    }

    SUBCLASSDATA *pData = NULL;
    BOOL success = GetWindowSubclass(pcdc->hCtrl, KeyPressSubclassProc, pcdc->id, (DWORD_PTR *)&pData);

    // If pData is null, the subclass is not installed.  The data block needs to
    // be allocated and then install the subclass.  Otherwise, just update the
    // data block.
    if ( pData == NULL )
    {
        pData = (SUBCLASSDATA *)LocalAlloc(LPTR, sizeof(SUBCLASSDATA));
        if ( pData == NULL )
        {
            result = memoryErr;
            goto done_out;
        }

        pData->pKeyPressData = (KEYPRESSDATA *)LocalAlloc(LPTR, sizeof(KEYPRESSDATA));
        if ( pData->pKeyPressData == NULL )
        {
            LocalFree(pData);
            result = memoryErr;
            goto done_out;
        }

        pCPlainBaseDialog pcpbd = dlgToCSelf(c, pcdc->oDlg);

        pData->hCtrl = pcdc->hCtrl;
        pData->uID = pcdc->id;
        pData->pMessageQueue = pcpbd->dlgAdm->pMessageQueue;

        result = setKeyPressData(pData->pKeyPressData, methodName, keys, filter);
        if ( result == noErr || result == badFilterErr || result == keyMapErr )
        {
            if ( SendMessage(pcdc->hDlg, WM_USER_SUBCLASS, (WPARAM)KeyPressSubclassProc, (LPARAM)pData) == 0 )
            {
                result = winAPIErr;
            }
        }
        else
        {
            LocalFree(pData);
        }
    }
    else
    {
        if ( success )
        {
            result = setKeyPressData(pData->pKeyPressData, methodName, keys, filter);
        }
        else
        {
            result = winAPIErr;
        }
    }

done_out:
    return result;
}


/** DialogControl::new()
 *
 *
 */
RexxMethod3(RexxObjectPtr, dlgctrl_new_cls, OPTIONAL_RexxObjectPtr, args, OSELF, self, SUPER, superClass)
{
    RexxMethodContext *c = context;
    RexxObjectPtr control = TheNilObj;

    if ( argumentOmitted(1) || ! c->IsPointer(args) )
    {
        goto done_out;
    }

    // Forwarding this message to the super class will also invoke the init()
    // method of the control instance object.
    control = c->ForwardMessage(NULLOBJECT, NULL, superClass, NULL);
    if ( control == NULLOBJECT )
    {
        control = TheNilObj;
    }

done_out:
    return control;
}

/** DialogControl::init()
 *
 *  The base init() for all dialog control objects.
 *
 *  Initializes the WindowBase and sets the 3 attributes: id, hDlg, and oDlg.
 *  These attributes are publicly 'get' only attributes and can not be changed.
 *
 *
 */
RexxMethod2(uint32_t, dlgctrl_init, OPTIONAL_POINTER, args, OSELF, self)
{
    RexxMethodContext *c = context;
    uint32_t result = 1;

    if ( argumentOmitted(1) || args == NULL )
    {
        goto done_out;
    }

    // Set up for the DialogControl CSelf.
    RexxBufferObject cdcBuf = c->NewBuffer(sizeof(CDialogControl));
    if ( cdcBuf == NULLOBJECT )
    {
        goto done_out;
    }

    // Do the WindowBase initialization.
    pCWindowBase wbCSelf;
    PNEWCONTROLPARAMS params = (PNEWCONTROLPARAMS)args;
    if ( ! initWindowBase(context, params->hwnd, self, &wbCSelf) )
    {
        goto done_out;
    }

    pCDialogControl cdcCSelf = (pCDialogControl)c->BufferData(cdcBuf);
    memset(cdcCSelf, 0, sizeof(CDialogControl));

    cdcCSelf->wndBase = wbCSelf;
    cdcCSelf->rexxSelf = self;
    cdcCSelf->hCtrl = params->hwnd;
    cdcCSelf->id = params->id;
    cdcCSelf->hDlg = params->hwndDlg;
    cdcCSelf->oDlg = params->parentDlg;

    context->SetObjectVariable("CSELF", cdcBuf);

    context->SetObjectVariable("ID", c->UnsignedInt32(params->id));
    context->SetObjectVariable("HDLG", pointer2string(context, params->hwndDlg));
    context->SetObjectVariable("ODLG", params->parentDlg);
    result = 0;

done_out:
    return result;
}

/** DialogControl::unInit()
 *
 *  Release the global reference for CWindowBase::rexxHwnd.
 *
 */
RexxMethod1(RexxObjectPtr, dlgctrl_unInit, CSELF, pCSelf)
{
    if ( pCSelf != NULLOBJECT )
    {
        pCWindowBase pcwb = ((pCDialogControl)pCSelf)->wndBase;
        if ( pcwb->rexxHwnd != TheZeroObj )
        {
            context->ReleaseGlobalReference(pcwb->rexxHwnd);
            pcwb->rexxHwnd = TheZeroObj;
        }
    } return NULLOBJECT;
}

RexxMethod4(int32_t, dlgctrl_connectKeyPress, CSTRING, methodName, CSTRING, keys, OPTIONAL_CSTRING, filter,
            CSELF, pCSelf)
{
    keyPressErr_t result = connectKeyPressSubclass(context, methodName, keys, filter, (pCDialogControl)pCSelf);
    if ( result == memoryErr )
    {
        outOfMemoryException(context->threadContext);
    }
    return -(int32_t)result;
}

RexxMethod2(int32_t, dlgctrl_connectFKeyPress, CSTRING, methodName, CSELF, pCSelf)
{
    keyPressErr_t result = connectKeyPressSubclass(context, methodName, "FKEYS", NULL, (pCDialogControl)pCSelf);
    if ( result == memoryErr )
    {
        outOfMemoryException(context->threadContext);
    }
    return -(int32_t)result;
}

RexxMethod2(int32_t, dlgctrl_disconnectKeyPress, OPTIONAL_CSTRING, methodName, CSELF, pCSelf)
{
    char *tmpName = NULL;
    keyPressErr_t result = winAPIErr;

    if ( ! requiredComCtl32Version(context, context->GetMessageName(), COMCTL32_6_0) )
    {
        goto done_out;
    }

    pCDialogControl pcdc = (pCDialogControl)pCSelf;

    SUBCLASSDATA *pData = NULL;
    BOOL success = GetWindowSubclass(pcdc->hCtrl, KeyPressSubclassProc, pcdc->id, (DWORD_PTR *)&pData);

    // If success, the subclass is still installed, otherwise the subclass has
    // already been removed, (or never existed.)
    if ( success )
    {
        // If no method name, remove the whole thing.
        if ( argumentOmitted(1) )
        {
            result = (removeKeyPressSubclass(pData, pcdc->hDlg, pcdc->id) ? noErr : winAPIErr);
            goto done_out;
        }

        // Have a method name, just remove that method from the mapping.
        tmpName = strdupupr(methodName);
        if ( tmpName == NULL )
        {
            result = memoryErr;
            goto done_out;
        }

        success = FALSE;  // Reuse the success variable.
        uint32_t index = seekKeyPressMethod(pData->pKeyPressData, tmpName);
        if ( index == 0 )
        {
            result = nameErr;
            goto done_out;
        }

        // If only 1 method left, remove the subclass entirely.  Otherwise,
        // remove the subclass, fix up the subclass data block, then reinstall
        // the subclass.
        if ( pData->pKeyPressData->usedMethods == 1 )
        {
            success = removeKeyPressSubclass(pData, pcdc->hDlg, pcdc->id);
        }
        else
        {
            if ( SendMessage(pcdc->hDlg, WM_USER_SUBCLASS_REMOVE, (WPARAM)KeyPressSubclassProc, (LPARAM)pcdc->id) )
            {
                removeKeyPressMethod(pData->pKeyPressData, index);
                success = (BOOL)SendMessage(pcdc->hDlg, WM_USER_SUBCLASS, (WPARAM)KeyPressSubclassProc, (LPARAM)pData);
            }
        }
        result = (success ? noErr : winAPIErr);
    }

done_out:
    return -(int32_t)result;
}

RexxMethod2(logical_t, dlgctrl_hasKeyPressConnection, OPTIONAL_CSTRING, methodName, CSELF, pCSelf)
{
    if ( ComCtl32Version <  COMCTL32_6_0 )
    {
        return FALSE;
    }

    pCDialogControl pcdc = (pCDialogControl)pCSelf;

    SUBCLASSDATA *pData = NULL;
    if ( ! GetWindowSubclass(pcdc->hCtrl, KeyPressSubclassProc, pcdc->id, (DWORD_PTR *)&pData) )
    {
        return FALSE;
    }
    if ( pData == NULL )
    {
        return FALSE;
    }
    if ( argumentOmitted(1) )
    {
        return TRUE;
    }

    char *tmpName = strdupupr(methodName);
    if ( tmpName == NULL )
    {
        outOfMemoryException(context->threadContext);
        return FALSE;
    }

    BOOL exists = (seekKeyPressMethod(pData->pKeyPressData, tmpName) > 0);
    free(tmpName);
    return exists;
}

/** DialogControl::tabstop()
 *  DialogControl::group()
 */
RexxMethod3(RexxObjectPtr, dlgctrl_tabGroup, OPTIONAL_logical_t, addStyle, NAME, method, CSELF, pCSelf)
{
    oodResetSysErrCode(context->threadContext);

    pCDialogControl pcdc = (pCDialogControl)pCSelf;
    if ( argumentOmitted(1) )
    {
        addStyle = TRUE;
    }
    uint32_t style = GetWindowLong(pcdc->hCtrl, GWL_STYLE);

    if ( *method == 'T' )
    {
        style = (addStyle ? (style | WS_TABSTOP) : (style & ~WS_TABSTOP));
    }
    else
    {
        style = (addStyle ? (style | WS_GROUP) : (style & ~WS_GROUP));
    }
    return setWindowStyle(context, pcdc->hCtrl, style);
}

/** DialogControl::getTextSizeDlg()
 *
 *  Gets the size (width and height) in dialog units for any given string.
 *
 *  Since dialog units only have meaning for a specific dialog, normally the
 *  dialog units are calculated using the font of the dialog.  Optionally, this
 *  method will calculate the dialog units using a specified font.
 *
 *  @param  text         The string whose size is needed.
 *
 *  @param  fontName     Optional. If specified, use this font to calculate the
 *                       size.  The default is to use the font of the owner
 *                       dialog of the dialog control.  This would be the normal
 *                       usage.
 *
 *  @param  fontSize     Optional. If specified, use this font size with
 *                       fontName to calculate the size.  The default if omitted
 *                       is 8.  This arg is ignored if fontName is omitted.
 *
 *  @param  hwndFontSrc  Optional. Use this window's font to calculate the size.
 *                       This arg is always ignored if fontName is specified.
 *
 *  @return  A .Size object representing the area (width and height,) in dialog
 *           units, needed for the specified string.
 *
 *  @note  This method, mapped to a dialog control object, does not really make
 *         sense.  It, and its convoluted optional arguments, are maintained
 *         only for backward compatibility.  Its use should be strongly
 *         discouraged.
 */
RexxMethod5(RexxObjectPtr, dlgctrl_getTextSizeDlg, CSTRING, text, OPTIONAL_CSTRING, fontName,
            OPTIONAL_uint32_t, fontSize, OPTIONAL_POINTERSTRING, hwndFontSrc, CSELF, pCSelf)
{
    HWND hwndSrc = NULL;
    if ( argumentExists(2) )
    {
        if ( argumentOmitted(3) )
        {
            fontSize = DEFAULT_FONTSIZE;
        }
    }
    else if ( argumentExists(4) )
    {
        hwndSrc = (HWND)hwndFontSrc;
        if ( hwndFontSrc == NULL )
        {
            nullObjectException(context->threadContext, "window handle", 4);
            return NULLOBJECT;
        }
    }

    SIZE textSize = {0};
    if ( getTextSize(context, text, fontName, fontSize, hwndSrc, ((pCDialogControl)pCSelf)->oDlg, &textSize) )
    {
        return rxNewSize(context, textSize.cx, textSize.cy);
    }
    return NULLOBJECT;
}


/**
 * Methods for the Edit class.
 */
#define EDIT_CLASS   "Edit"

#define BALLON_MAX_TITLE      99
#define BALLON_MAX_TEXT     1023
#define QUE_MAX_TEXT         255

/**
 * Take an edit control's window flags and construct a Rexx string that
 * represents the control's style.
 */
RexxObjectPtr editStyleToString(RexxMethodContext *c, uint32_t style)
{
    char buf[512];

    if ( style & WS_VISIBLE ) strcpy(buf, "VISIBLE");
    else strcpy(buf, "HIDDEN");

    if ( style & WS_TABSTOP ) strcat(buf, " TAB");
    else strcat(buf, " NOTAB");

    if ( style & WS_DISABLED ) strcat(buf, " DISABLED");
    else strcat(buf, " ENABLED");

    if ( style & WS_GROUP )       strcat(buf, " GROUP");
    if ( style & WS_HSCROLL )     strcat(buf, " HSCROLL");
    if ( style & WS_VSCROLL )     strcat(buf, " VSCROLL");
    if ( style & ES_PASSWORD )    strcat(buf, " PASSWORD");
    if ( style & ES_MULTILINE )   strcat(buf, " MULTILINE");
    if ( style & ES_AUTOHSCROLL ) strcat(buf, " AUTOSCROLLH");
    if ( style & ES_AUTOVSCROLL ) strcat(buf, " AUTOSCROLLV");
    if ( style & ES_READONLY )    strcat(buf, " READONLY");
    if ( style & ES_WANTRETURN )  strcat(buf, " WANTRETURN");
    if ( style & ES_NOHIDESEL )   strcat(buf, " KEEPSELECTION");
    if ( style & ES_UPPERCASE )   strcat(buf, " UPPER");
    if ( style & ES_LOWERCASE )   strcat(buf, " LOWER");
    if ( style & ES_NUMBER )      strcat(buf, " NUMBER");
    if ( style & ES_OEMCONVERT )  strcat(buf, " OEM");

    if ( style & ES_RIGHT ) strcat(buf, " RIGHT");
    else if ( style & ES_CENTER ) strcat(buf, " CENTER");
    else strcat(buf, " LEFT");

    return c->String(buf);
}

/**
 * Parse an edit control style string sent from ooDialog into the corresponding
 * style flags.
 *
 * Note that this is meant to only deal with the styles that can be changed
 * after the control is created through SetWindowLong.
 */
uint32_t parseEditStyle(CSTRING keyWords)
{
    uint32_t style = 0;

    if ( StrStrI(keyWords, "UPPER"     ) ) style |= ES_UPPERCASE;
    if ( StrStrI(keyWords, "LOWER"     ) ) style |= ES_LOWERCASE;
    if ( StrStrI(keyWords, "NUMBER"    ) ) style |= ES_NUMBER;
    if ( StrStrI(keyWords, "WANTRETURN") ) style |= ES_WANTRETURN;
    if ( StrStrI(keyWords, "OEM"       ) ) style |= ES_OEMCONVERT;

    /* Although these styles can be changed by individual ooDialog methods, as
     * a convenience, allow the programmer to include them when changing
     * multiple styles at once.
     */
    if ( StrStrI(keyWords, "TAB"  ) ) style |= WS_TABSTOP;
    if ( StrStrI(keyWords, "GROUP") ) style |= WS_GROUP;

    return style;
}

RexxMethod1(RexxObjectPtr, e_selection, CSELF, pCSelf)
{
    pCDialogControl pcdc = (pCDialogControl)pCSelf;

    uint32_t start, end;
    SendMessage(pcdc->hCtrl, EM_GETSEL, (WPARAM)&start, (LPARAM)&end);

    RexxDirectoryObject result = context->NewDirectory();
    context->DirectoryPut(result, context->UnsignedInt32(++start), "STARTCHAR");
    context->DirectoryPut(result, context->UnsignedInt32(++end), "ENDCHAR");
    return result;
}


RexxMethod1(RexxObjectPtr, e_hideBallon, CSELF, pCSelf)
{
    if ( ! requiredComCtl32Version(context, context->GetMessageName(), COMCTL32_6_0)  )
    {
        return TheOneObj;
    }
    pCDialogControl pcdc = (pCDialogControl)pCSelf;
    return (Edit_HideBalloonTip(pcdc->hCtrl) ? TheZeroObj : TheOneObj);
}


RexxMethod4(RexxObjectPtr, e_showBallon, CSTRING, title, CSTRING, text, OPTIONAL_CSTRING, icon, CSELF, pCSelf)
{
    if ( ! requiredComCtl32Version(context, context->GetMessageName(), COMCTL32_6_0)  )
    {
        return TheOneObj;
    }
    pCDialogControl pcdc = (pCDialogControl)pCSelf;

    EDITBALLOONTIP tip;
    WCHAR wszTitle[128];
    WCHAR wszText[BALLON_MAX_TEXT + 1];

    // The title string has a limit of 99 characters / text is limited to 1023.
    if ( strlen(title) > BALLON_MAX_TITLE )
    {
        stringTooLongException(context->threadContext, 1, BALLON_MAX_TITLE, strlen(title));
        return TheOneObj;
    }
    if ( strlen(text) > BALLON_MAX_TEXT )
    {
        stringTooLongException(context->threadContext, 2, BALLON_MAX_TEXT, strlen(title));
        return TheOneObj;
    }

    putUnicodeText((LPWORD)wszTitle, title);
    putUnicodeText((LPWORD)wszText, text);

    tip.cbStruct = sizeof(tip);
    tip.pszText = wszText;
    tip.pszTitle = wszTitle;
    tip.ttiIcon = TTI_INFO;

    if ( argumentExists(3) )
    {
        switch( toupper(*icon) )
        {
            case 'E' :
                tip.ttiIcon = TTI_ERROR;
                break;
            case 'N' :
                tip.ttiIcon = TTI_NONE;
                break;
            case 'W' :
                tip.ttiIcon = TTI_WARNING;
                break;
        }
    }
    return (Edit_ShowBalloonTip(pcdc->hCtrl, &tip) ? TheZeroObj : TheOneObj);
}

/* Note that the EM_GETCUEBANNER simply does not work.  At least on XP.  So
 * the code is removed.  But, it might be worth trying on Vista.
 */


RexxMethod2(RexxObjectPtr, e_setCue, CSTRING, text, CSELF, pCSelf)
{
    if ( ! requiredComCtl32Version(context, context->GetMessageName(), COMCTL32_6_0)  )
    {
        return TheOneObj;
    }
    pCDialogControl pcdc = (pCDialogControl)pCSelf;

    // The text is limited to 255.
    WCHAR wszCue[QUE_MAX_TEXT + 1];
    if ( strlen(text) > QUE_MAX_TEXT )
    {
        stringTooLongException(context->threadContext, 1, QUE_MAX_TEXT, strlen(text));
        return TheOneObj;
    }

    putUnicodeText((LPWORD)wszCue, text);
    return (Edit_SetCueBannerText(pcdc->hCtrl, wszCue) ? TheZeroObj : TheOneObj);
}


/** Edit::getStyle()
 *  Edit::replaceStyle()
 *  Edit::removeStyle()
 *  Edit::addStyle()
 *
 *  @param  _style1  Style to add for addStyle(), style to remove for
 *                   removeStyle() and replaceStyle().
 *  @param  _style2  Style to add for replaceStyle().
 */
RexxMethod4(RexxObjectPtr, e_style, OPTIONAL_CSTRING, _style1, OPTIONAL_CSTRING, _style2, NAME, method, CSELF, pCSelf)
{
    oodResetSysErrCode(context->threadContext);
    pCDialogControl pcdc = (pCDialogControl)pCSelf;

    uint32_t style = GetWindowLong(pcdc->hCtrl, GWL_STYLE);
    if ( *method == 'G' )
    {
        return editStyleToString(context, style);
    }

    if ( argumentOmitted(1) )
    {
        return missingArgException(context->threadContext, 1);
    }

    uint32_t style1 = parseEditStyle(_style1);
    if ( *method == 'A' )
    {
        style |= style1;
    }
    else if ( method[2] == 'M' )
    {
        style &= ~style1;
    }
    else
    {
        if ( argumentOmitted(2) )
        {
            return missingArgException(context->threadContext, 2);
        }

        uint32_t style2 = parseEditStyle(_style2);
        style = (style & ~style1) | style2;
    }
    return setWindowStyle(context, pcdc->hCtrl, style);
}


/**
 * Methods for the ListBox class.
 */
#define LISTBOX_CLASS   "ListBox"


/** ListBox::getText()
 *
 *  Return the text of the item at the specified index.
 *
 *  @param  index  The 1-based item index.  (The underlying list box uses
 *                 0-based indexes.)
 *
 *  @return  The item's text or the empty string on error.
 */
RexxMethod2(RexxObjectPtr, lb_getText, uint32_t, index, CSELF, pCSelf)
{
    pCDialogControl pcdc = (pCDialogControl)pCSelf;
    RexxStringObject result = context->NullString();

    if ( index-- > 0 )
    {
        LRESULT l = SendMessage(pcdc->hCtrl, LB_GETTEXTLEN, index, 0);
        if ( l > 0 )
        {
            char *buf = (char *)malloc(l + 1);
            if ( buf == NULL )
            {
                outOfMemoryException(context->threadContext);
                return result;
            }

            l = SendMessage(pcdc->hCtrl, LB_GETTEXT, (WPARAM)buf, 0);
            if ( l > 0 )
            {
                result = context->String(buf);
            }
            free(buf);
        }
    }
    return result;
}

