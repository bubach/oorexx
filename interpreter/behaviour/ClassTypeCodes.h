

/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Copyright (c) 1995, 2004 IBM Corporation. All rights reserved.             */
/* Copyright (c) 2005-2018 Rexx Language Association. All rights reserved.    */
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
/******************************************************************************/
/* REXX  Support                                                              */
/*                                                                            */
/* Rexx primitive class id codes                                              */
/*                                                                            */
/*        -- DO NOT CHANGE THIS FILE, ALL CHANGES WILL BE LOST! --            */
/*                  -- FILE WAS GENERATED BY ClassTypeIds.xsl --              */
/******************************************************************************/

#ifndef ClassTypeCodes_Included
#define ClassTypeCodes_Included

typedef enum
{
    T_First_Primitive_Class = 0,
    T_First_Exported_Class = 0,

    T_Object = 0,
    T_ObjectClass = 1,
    T_Class = 2,
    T_ClassClass = 3,
    T_Array = 4,
    T_ArrayClass = 5,
    T_Directory = 6,
    T_DirectoryClass = 7,
    T_Integer = 8,
    T_IntegerClass = 9,
    T_List = 10,
    T_ListClass = 11,
    T_Message = 12,
    T_MessageClass = 13,
    T_Method = 14,
    T_MethodClass = 15,
    T_NumberString = 16,
    T_NumberStringClass = 17,
    T_Queue = 18,
    T_QueueClass = 19,
    T_Stem = 20,
    T_StemClass = 21,
    T_String = 22,
    T_StringClass = 23,
    T_Supplier = 24,
    T_SupplierClass = 25,
    T_Table = 26,
    T_TableClass = 27,
    T_StringTable = 28,
    T_StringTableClass = 29,
    T_Relation = 30,
    T_RelationClass = 31,
    T_MutableBuffer = 32,
    T_MutableBufferClass = 33,
    T_Pointer = 34,
    T_PointerClass = 35,
    T_Buffer = 36,
    T_BufferClass = 37,
    T_WeakReference = 38,
    T_WeakReferenceClass = 39,
    T_Routine = 40,
    T_RoutineClass = 41,
    T_Package = 42,
    T_PackageClass = 43,
    T_RexxContext = 44,
    T_RexxContextClass = 45,
    T_IdentityTable = 46,
    T_IdentityTableClass = 47,
    T_StackFrame = 48,
    T_StackFrameClass = 49,
    T_Set = 50,
    T_SetClass = 51,
    T_Bag = 52,
    T_BagClass = 53,
    T_RexxInfo = 54,
    T_RexxInfoClass = 55,
    T_VariableReference = 56,
    T_VariableReferenceClass = 57,

    T_Last_Exported_Class = 57,
    
    T_First_Internal_Class = 58,

    T_NilObject = 58,
    T_Behaviour = 59,
    T_MethodDictionary = 60,
    T_LibraryPackage = 61,
    T_RexxCode = 62,
    T_NativeMethod = 63,
    T_NativeRoutine = 64,
    T_RegisteredRoutine = 65,
    T_CPPCode = 66,
    T_AttributeGetterCode = 67,
    T_AttributeSetterCode = 68,
    T_ConstantGetterCode = 69,
    T_AbstractCode = 70,
    T_DelegateCode = 71,
    T_SmartBuffer = 72,
    T_IdentityHashContents = 73,
    T_EqualityHashContents = 74,
    T_MultiValueContents = 75,
    T_StringHashContents = 76,
    T_ListContents = 77,
    T_Variable = 78,
    T_VariableDictionary = 79,
    T_VariableTerm = 80,
    T_CompoundVariableTerm = 81,
    T_StemVariableTerm = 82,
    T_DotVariableTerm = 83,
    T_IndirectVariableTerm = 84,
    T_FunctionCallTerm = 85,
    T_MessageSendTerm = 86,
    T_UnaryOperatorTerm = 87,
    T_BinaryOperatorTerm = 88,
    T_LogicalTerm = 89,
    T_ListTerm = 90,
    T_Instruction = 91,
    T_AddressInstruction = 92,
    T_AssignmentInstruction = 93,
    T_CallInstruction = 94,
    T_DynamicCallInstruction = 95,
    T_QualifiedCallInstruction = 96,
    T_CallOnInstruction = 97,
    T_CommandInstruction = 98,
    T_SimpleDoInstruction = 99,
    T_DoForeverInstruction = 100,
    T_DoOverInstruction = 101,
    T_DoOverUntilInstruction = 102,
    T_DoOverWhileInstruction = 103,
    T_DoOverForInstruction = 104,
    T_DoOverForUntilInstruction = 105,
    T_DoOverForWhileInstruction = 106,
    T_ControlledDoInstruction = 107,
    T_ControlledDoUntilInstruction = 108,
    T_ControlledDoWhileInstruction = 109,
    T_DoWhileInstruction = 110,
    T_DoUntilInstruction = 111,
    T_DoCountInstruction = 112,
    T_DoCountUntilInstruction = 113,
    T_DoCountWhileInstruction = 114,
    T_DropInstruction = 115,
    T_ElseInstruction = 116,
    T_EndInstruction = 117,
    T_EndIfInstruction = 118,
    T_ExitInstruction = 119,
    T_ExposeInstruction = 120,
    T_ForwardInstruction = 121,
    T_GuardInstruction = 122,
    T_IfInstruction = 123,
    T_CaseWhenInstruction = 124,
    T_InterpretInstruction = 125,
    T_LabelInstruction = 126,
    T_LeaveInstruction = 127,
    T_MessageInstruction = 128,
    T_NopInstruction = 129,
    T_NumericInstruction = 130,
    T_OptionsInstruction = 131,
    T_OtherwiseInstruction = 132,
    T_ParseInstruction = 133,
    T_ProcedureInstruction = 134,
    T_QueueInstruction = 135,
    T_RaiseInstruction = 136,
    T_ReplyInstruction = 137,
    T_ReturnInstruction = 138,
    T_SayInstruction = 139,
    T_SelectInstruction = 140,
    T_SelectCaseInstruction = 141,
    T_SignalInstruction = 142,
    T_DynamicSignalInstruction = 143,
    T_SignalOnInstruction = 144,
    T_ThenInstruction = 145,
    T_TraceInstruction = 146,
    T_UseInstruction = 147,
    T_UseLocalInstruction = 148,
    T_DoWithInstruction = 149,
    T_DoWithUntilInstruction = 150,
    T_DoWithWhileInstruction = 151,
    T_DoWithForInstruction = 152,
    T_DoWithForUntilInstruction = 153,
    T_DoWithForWhileInstruction = 154,
    T_ClassDirective = 155,
    T_LibraryDirective = 156,
    T_RequiresDirective = 157,
    T_CompoundElement = 158,
    T_ParseTrigger = 159,
    T_ProgramSource = 160,
    T_ArrayProgramSource = 161,
    T_BufferProgramSource = 162,
    T_FileProgramSource = 163,
    T_NumberArray = 164,
    T_ClassResolver = 165,
    T_QualifiedFunction = 166,
    T_PointerBucket = 167,
    T_PointerTable = 168,
    T_SpecialDotVariableTerm = 169,
    T_VariableReferenceOp = 170,
    T_UseArgVariableRef = 171,

    T_Last_Internal_Class = 171,
    
    T_First_Transient_Class = 172,

    T_Memory = 172,
    T_InternalStack = 173,
    T_LiveStack = 174,
    T_PushThroughStack = 175,
    T_Activity = 176,
    T_Activation = 177,
    T_NativeActivation = 178,
    T_ActivationFrameBuffer = 179,
    T_Envelope = 180,
    T_LanguageParser = 181,
    T_Clause = 182,
    T_Token = 183,
    T_DoBlock = 184,
    T_InterpreterInstance = 185,
    T_SecurityManager = 186,
    T_CommandHandler = 187,
    T_MapBucket = 188,
    T_MapTable = 189,
    T_TrapHandler = 190,

    T_Last_Transient_Class = 190,
    T_Last_Primitive_Class = 190,
    T_Last_Class_Type = 190,
    
} ClassTypeCode;

/* -------------------------------------------------------------------------- */
/* --            ==================================================        -- */
/* --            DO NOT CHANGE THIS FILE, ALL CHANGES WILL BE LOST!        -- */
/* --            ==================================================        -- */
/* -------------------------------------------------------------------------- */
#endif

