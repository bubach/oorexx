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
/* REXX Kernel                                                   ParseTrigger.hpp */
/*                                                                            */
/* Primitive PARSE instruction parsing trigger Class Definitions              */
/*                                                                            */
/******************************************************************************/
#ifndef Included_RexxInstructionTrigger
#define Included_RexxInstructionTrigger

#define TRIGGER_END      1
#define TRIGGER_PLUS     2
#define TRIGGER_MINUS    3
#define TRIGGER_ABSOLUTE 4
#define TRIGGER_STRING   5
#define TRIGGER_MIXED    6

class RexxTrigger : public RexxInternalObject {
 public:
  void       *operator new(size_t, LONG);
  inline void       *operator new(size_t size, void *ptr) {return ptr;};
  RexxTrigger(INT, RexxObject *, LONG, RexxQueue *);
  inline RexxTrigger(RESTORETYPE restoreType) { ; };
  long        integer(RexxObject *);
  void        parse(RexxActivation *, RexxExpressionStack *, RexxTarget *);
  void        live();
  void        liveGeneral();
  void        flatten(RexxEnvelope *);
  inline long        getType()     { return this->hashvalue; } ;
  inline void        setType(INT v) { this->hashvalue = (long) v; } ;

  LONG        variableCount;           /* type of trigger                   */
  RexxObject *value;                   /* value associated with trigger     */
  RexxVariableBase *variables[1];      /* list of variables to assign       */
};
#endif