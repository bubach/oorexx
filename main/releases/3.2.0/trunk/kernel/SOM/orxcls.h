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

/*
 * This file was generated by the SOM Compiler.
 * FileName: orxcls.h.
 * Generated using:
 *     SOM Precompiler somipc: 2.29.1.3
 *     SOM Emitter emith: 2.41
 */

/*
 *
 *   Oryx Interface                                               orxcls.csc
 *
 *   SOM Class for Oryx Proxy Objects
 *
 *
 */


#ifndef SOM_OrxClass_h
#define SOM_OrxClass_h


/*
 * The SOM_STRICT_IDL macro means that we can ignore stars
 * in our declarations of objects.
 */
#define SOM_STRICT_IDL 1


#include <som.h>

/*
 * -- This emitter treats Method Tokens as Thunks by default.
 * -- Use the sc modifier "nothunks" to change this default
 */
#undef somresolve_
#define somresolve_(obj,mToken) ((somMethodProc*)((void)obj, mToken))

/*
 * Define the class name as an object type
 */
#ifndef OrxClass
#define OrxClass SOMObject
#endif
#include <somcls.h>

/*
 * Start of user-defined types:
 */
#ifndef SOMClass
    #define SOMClass SOMObject
#endif /* SOMClass */

/*
 * End of user-defined types.
 */

#define OrxClass_MajorVersion 0
#define OrxClass_MinorVersion 0

/*
 * External name shortening if required
 */
#ifdef SOM_USE_SHORT_EXTERNAL_NAMES
#define OrxClassNewClass c
#pragma linkage(c, system)
#define OrxClassClassData d
#define OrxClassCClassData x
#endif /* SOM_USE_SHORT_EXTERNAL_NAMES */
/*--------------Migration------------*/
#define OrxClass_classObj OrxClassClassData.classObject
#define _OrxClass OrxClass_classObj

/*
 * Declare the class creation procedure
 */
SOMEXTERN SOMClass  SOMLINK OrxClassNewClass(integer4 somtmajorVersion,
		integer4 somtminorVersion);
#pragma linkage(OrxClassNewClass, system)

/*
 * Declare the class data structure
 */
SOMEXTERN struct OrxClassClassDataStructure {
	SOMClass classObject;
} SOMDLINK OrxClassClassData;

/*
 * Declare the C specific class data structure
 */
SOMEXTERN struct OrxClassCClassDataStructure {
	somMethodTabs parentMtab;
	somDToken instanceDataToken;
} SOMDLINK OrxClassCClassData;

/*
 * New and Renew macros for OrxClass
 */
#define OrxClassNew() \
   (_somNew(_OrxClass ? _OrxClass : OrxClassNewClass(OrxClass_MajorVersion, OrxClass_MinorVersion)))
#define OrxClassRenew(buf) \
   (_somRenew(_OrxClass ? _OrxClass : OrxClassNewClass(OrxClass_MajorVersion, OrxClass_MinorVersion), buf))

/*
 * Override method: somClassReady
 */
#define OrxClass_somClassReady(somSelf) \
	SOMClass_somClassReady(somSelf)
#ifndef SOM_DONT_USE_INHERITED_MACROS
#define OrxClass__get_somDataAlignment SOMClass__get_somDataAlignment
#define OrxClass__get_somInstanceDataOffsets SOMClass__get_somInstanceDataOffsets
#define OrxClass__get_somDirectInitClasses SOMClass__get_somDirectInitClasses
#define OrxClass__set_somDirectInitClasses SOMClass__set_somDirectInitClasses
#define OrxClass_somNew SOMClass_somNew
#define OrxClass_somNewNoInit SOMClass_somNewNoInit
#define OrxClass_somRenew SOMClass_somRenew
#define OrxClass_somRenewNoInit SOMClass_somRenewNoInit
#define OrxClass_somRenewNoZero SOMClass_somRenewNoZero
#define OrxClass_somRenewNoInitNoZero SOMClass_somRenewNoInitNoZero
#define OrxClass_somAllocate SOMClass_somAllocate
#define OrxClass_somDeallocate SOMClass_somDeallocate
#define OrxClass__get_somClassAllocate SOMClass__get_somClassAllocate
#define OrxClass__get_somClassDeallocate SOMClass__get_somClassDeallocate
#define OrxClass_somGetInstanceInitMask SOMClass_somGetInstanceInitMask
#define OrxClass_somGetInstanceDestructionMask SOMClass_somGetInstanceDestructionMask
#define OrxClass_somGetInstanceAssignmentMask SOMClass_somGetInstanceAssignmentMask
#define OrxClass_somInitClass SOMClass_somInitClass
#define OrxClass_somInitMIClass SOMClass_somInitMIClass
#define OrxClass_somAddStaticMethod SOMClass_somAddStaticMethod
#define OrxClass_somAddDynamicMethod SOMClass_somAddDynamicMethod
#define OrxClass_somOverrideSMethod SOMClass_somOverrideSMethod
#define OrxClass_somGetApplyStub SOMClass_somGetApplyStub
#define OrxClass_somGetClassData SOMClass_somGetClassData
#define OrxClass_somSetClassData SOMClass_somSetClassData
#define OrxClass_somGetClassMtab SOMClass_somGetClassMtab
#define OrxClass_somGetInstanceOffset SOMClass_somGetInstanceOffset
#define OrxClass_somGetInstancePartSize SOMClass_somGetInstancePartSize
#define OrxClass_somGetInstanceSize SOMClass_somGetInstanceSize
#define OrxClass_somGetInstanceToken SOMClass_somGetInstanceToken
#define OrxClass_somGetMemberToken SOMClass_somGetMemberToken
#define OrxClass_somGetMethodData SOMClass_somGetMethodData
#define OrxClass_somGetRdStub SOMClass_somGetRdStub
#define OrxClass_somGetMethodDescriptor SOMClass_somGetMethodDescriptor
#define OrxClass_somGetMethodIndex SOMClass_somGetMethodIndex
#define OrxClass_somGetMethodToken SOMClass_somGetMethodToken
#define OrxClass_somGetName SOMClass_somGetName
#define OrxClass_somGetNthMethodData SOMClass_somGetNthMethodData
#define OrxClass_somGetNthMethodInfo SOMClass_somGetNthMethodInfo
#define OrxClass_somGetNumMethods SOMClass_somGetNumMethods
#define OrxClass_somGetNumStaticMethods SOMClass_somGetNumStaticMethods
#define OrxClass_somGetParent SOMClass_somGetParent
#define OrxClass_somGetParents SOMClass_somGetParents
#define OrxClass_somGetPClsMtab SOMClass_somGetPClsMtab
#define OrxClass_somGetPClsMtabs SOMClass_somGetPClsMtabs
#define OrxClass_somGetVersionNumbers SOMClass_somGetVersionNumbers
#define OrxClass_somSetMethodDescriptor SOMClass_somSetMethodDescriptor
#define OrxClass_somFindMethod SOMClass_somFindMethod
#define OrxClass_somFindMethodOk SOMClass_somFindMethodOk
#define OrxClass_somFindSMethod SOMClass_somFindSMethod
#define OrxClass_somFindSMethodOk SOMClass_somFindSMethodOk
#define OrxClass_somLookupMethod SOMClass_somLookupMethod
#define OrxClass_somCheckVersion SOMClass_somCheckVersion
#define OrxClass_somDescendedFrom SOMClass_somDescendedFrom
#define OrxClass_somSupportsMethod SOMClass_somSupportsMethod
#define OrxClass_somDefinedMethod SOMClass_somDefinedMethod
#define OrxClass_somOverrideMtab SOMClass_somOverrideMtab
#define OrxClass_somDefaultInit SOMObject_somDefaultInit
#define OrxClass_somDestruct SOMObject_somDestruct
#define OrxClass_somDefaultCopyInit SOMObject_somDefaultCopyInit
#define OrxClass_somDefaultAssign SOMObject_somDefaultAssign
#define OrxClass_somDefaultConstCopyInit SOMObject_somDefaultConstCopyInit
#define OrxClass_somDefaultVCopyInit SOMObject_somDefaultVCopyInit
#define OrxClass_somDefaultConstVCopyInit SOMObject_somDefaultConstVCopyInit
#define OrxClass_somDefaultConstAssign SOMObject_somDefaultConstAssign
#define OrxClass_somDefaultVAssign SOMObject_somDefaultVAssign
#define OrxClass_somDefaultConstVAssign SOMObject_somDefaultConstVAssign
#define OrxClass_somInit SOMObject_somInit
#define OrxClass_somFree SOMObject_somFree
#define OrxClass_somUninit SOMObject_somUninit
#define OrxClass_somGetClass SOMObject_somGetClass
#define OrxClass_somGetClassName SOMObject_somGetClassName
#define OrxClass_somGetSize SOMObject_somGetSize
#define OrxClass_somIsA SOMObject_somIsA
#define OrxClass_somIsInstanceOf SOMObject_somIsInstanceOf
#define OrxClass_somRespondsTo SOMObject_somRespondsTo
#define OrxClass_somDispatch SOMObject_somDispatch
#define OrxClass_somClassDispatch SOMObject_somClassDispatch
#define OrxClass_somCastObj SOMObject_somCastObj
#define OrxClass_somResetObj SOMObject_somResetObj
#define OrxClass_somDispatchV SOMObject_somDispatchV
#define OrxClass_somDispatchL SOMObject_somDispatchL
#define OrxClass_somDispatchA SOMObject_somDispatchA
#define OrxClass_somDispatchD SOMObject_somDispatchD
#define OrxClass_somPrintSelf SOMObject_somPrintSelf
#define OrxClass_somDumpSelf SOMObject_somDumpSelf
#define OrxClass_somDumpSelfInt SOMObject_somDumpSelfInt
#endif /* SOM_DONT_USE_INHERITED_MACROS */

#endif       /* SOM_OrxClass_h */
