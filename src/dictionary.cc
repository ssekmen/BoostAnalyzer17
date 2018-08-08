// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIdictionary

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/tnm.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *itreestream_Dictionary();
   static void itreestream_TClassManip(TClass*);
   static void *new_itreestream(void *p = 0);
   static void *newArray_itreestream(Long_t size, void *p);
   static void delete_itreestream(void *p);
   static void deleteArray_itreestream(void *p);
   static void destruct_itreestream(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::itreestream*)
   {
      ::itreestream *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::itreestream));
      static ::ROOT::TGenericClassInfo 
         instance("itreestream", "treestream.h", 155,
                  typeid(::itreestream), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &itreestream_Dictionary, isa_proxy, 0,
                  sizeof(::itreestream) );
      instance.SetNew(&new_itreestream);
      instance.SetNewArray(&newArray_itreestream);
      instance.SetDelete(&delete_itreestream);
      instance.SetDeleteArray(&deleteArray_itreestream);
      instance.SetDestructor(&destruct_itreestream);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::itreestream*)
   {
      return GenerateInitInstanceLocal((::itreestream*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::itreestream*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *itreestream_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::itreestream*)0x0)->GetClass();
      itreestream_TClassManip(theClass);
   return theClass;
   }

   static void itreestream_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *otreestream_Dictionary();
   static void otreestream_TClassManip(TClass*);
   static void *new_otreestream(void *p = 0);
   static void *newArray_otreestream(Long_t size, void *p);
   static void delete_otreestream(void *p);
   static void deleteArray_otreestream(void *p);
   static void destruct_otreestream(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::otreestream*)
   {
      ::otreestream *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::otreestream));
      static ::ROOT::TGenericClassInfo 
         instance("otreestream", "treestream.h", 370,
                  typeid(::otreestream), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &otreestream_Dictionary, isa_proxy, 0,
                  sizeof(::otreestream) );
      instance.SetNew(&new_otreestream);
      instance.SetNewArray(&newArray_otreestream);
      instance.SetDelete(&delete_otreestream);
      instance.SetDeleteArray(&deleteArray_otreestream);
      instance.SetDestructor(&destruct_otreestream);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::otreestream*)
   {
      return GenerateInitInstanceLocal((::otreestream*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::otreestream*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *otreestream_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::otreestream*)0x0)->GetClass();
      otreestream_TClassManip(theClass);
   return theClass;
   }

   static void otreestream_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffer_Dictionary();
   static void eventBuffer_TClassManip(TClass*);
   static void *new_eventBuffer(void *p = 0);
   static void *newArray_eventBuffer(Long_t size, void *p);
   static void delete_eventBuffer(void *p);
   static void deleteArray_eventBuffer(void *p);
   static void destruct_eventBuffer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer*)
   {
      ::eventBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer", "eventBuffer.h", 22,
                  typeid(::eventBuffer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffer_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer) );
      instance.SetNew(&new_eventBuffer);
      instance.SetNewArray(&newArray_eventBuffer);
      instance.SetDelete(&delete_eventBuffer);
      instance.SetDeleteArray(&deleteArray_eventBuffer);
      instance.SetDestructor(&destruct_eventBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer*)
   {
      return GenerateInitInstanceLocal((::eventBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffer_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer*)0x0)->GetClass();
      eventBuffer_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffer_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLElectron_s_Dictionary();
   static void eventBuffercLcLElectron_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLElectron_s(void *p = 0);
   static void *newArray_eventBuffercLcLElectron_s(Long_t size, void *p);
   static void delete_eventBuffercLcLElectron_s(void *p);
   static void deleteArray_eventBuffercLcLElectron_s(void *p);
   static void destruct_eventBuffercLcLElectron_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::Electron_s*)
   {
      ::eventBuffer::Electron_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::Electron_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::Electron_s", "eventBuffer.h", 1013,
                  typeid(::eventBuffer::Electron_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLElectron_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::Electron_s) );
      instance.SetNew(&new_eventBuffercLcLElectron_s);
      instance.SetNewArray(&newArray_eventBuffercLcLElectron_s);
      instance.SetDelete(&delete_eventBuffercLcLElectron_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLElectron_s);
      instance.SetDestructor(&destruct_eventBuffercLcLElectron_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::Electron_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::Electron_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::Electron_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLElectron_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::Electron_s*)0x0)->GetClass();
      eventBuffercLcLElectron_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLElectron_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLFatJet_s_Dictionary();
   static void eventBuffercLcLFatJet_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLFatJet_s(void *p = 0);
   static void *newArray_eventBuffercLcLFatJet_s(Long_t size, void *p);
   static void delete_eventBuffercLcLFatJet_s(void *p);
   static void deleteArray_eventBuffercLcLFatJet_s(void *p);
   static void destruct_eventBuffercLcLFatJet_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::FatJet_s*)
   {
      ::eventBuffer::FatJet_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::FatJet_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::FatJet_s", "eventBuffer.h", 1118,
                  typeid(::eventBuffer::FatJet_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLFatJet_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::FatJet_s) );
      instance.SetNew(&new_eventBuffercLcLFatJet_s);
      instance.SetNewArray(&newArray_eventBuffercLcLFatJet_s);
      instance.SetDelete(&delete_eventBuffercLcLFatJet_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLFatJet_s);
      instance.SetDestructor(&destruct_eventBuffercLcLFatJet_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::FatJet_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::FatJet_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::FatJet_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLFatJet_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::FatJet_s*)0x0)->GetClass();
      eventBuffercLcLFatJet_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLFatJet_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLGenJet_s_Dictionary();
   static void eventBuffercLcLGenJet_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLGenJet_s(void *p = 0);
   static void *newArray_eventBuffercLcLGenJet_s(Long_t size, void *p);
   static void delete_eventBuffercLcLGenJet_s(void *p);
   static void deleteArray_eventBuffercLcLGenJet_s(void *p);
   static void destruct_eventBuffercLcLGenJet_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::GenJet_s*)
   {
      ::eventBuffer::GenJet_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::GenJet_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::GenJet_s", "eventBuffer.h", 1167,
                  typeid(::eventBuffer::GenJet_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLGenJet_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::GenJet_s) );
      instance.SetNew(&new_eventBuffercLcLGenJet_s);
      instance.SetNewArray(&newArray_eventBuffercLcLGenJet_s);
      instance.SetDelete(&delete_eventBuffercLcLGenJet_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLGenJet_s);
      instance.SetDestructor(&destruct_eventBuffercLcLGenJet_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::GenJet_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::GenJet_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::GenJet_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLGenJet_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::GenJet_s*)0x0)->GetClass();
      eventBuffercLcLGenJet_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLGenJet_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLGenJetAK8_s_Dictionary();
   static void eventBuffercLcLGenJetAK8_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLGenJetAK8_s(void *p = 0);
   static void *newArray_eventBuffercLcLGenJetAK8_s(Long_t size, void *p);
   static void delete_eventBuffercLcLGenJetAK8_s(void *p);
   static void deleteArray_eventBuffercLcLGenJetAK8_s(void *p);
   static void destruct_eventBuffercLcLGenJetAK8_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::GenJetAK8_s*)
   {
      ::eventBuffer::GenJetAK8_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::GenJetAK8_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::GenJetAK8_s", "eventBuffer.h", 1190,
                  typeid(::eventBuffer::GenJetAK8_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLGenJetAK8_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::GenJetAK8_s) );
      instance.SetNew(&new_eventBuffercLcLGenJetAK8_s);
      instance.SetNewArray(&newArray_eventBuffercLcLGenJetAK8_s);
      instance.SetDelete(&delete_eventBuffercLcLGenJetAK8_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLGenJetAK8_s);
      instance.SetDestructor(&destruct_eventBuffercLcLGenJetAK8_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::GenJetAK8_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::GenJetAK8_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::GenJetAK8_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLGenJetAK8_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::GenJetAK8_s*)0x0)->GetClass();
      eventBuffercLcLGenJetAK8_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLGenJetAK8_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLGenPart_s_Dictionary();
   static void eventBuffercLcLGenPart_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLGenPart_s(void *p = 0);
   static void *newArray_eventBuffercLcLGenPart_s(Long_t size, void *p);
   static void delete_eventBuffercLcLGenPart_s(void *p);
   static void deleteArray_eventBuffercLcLGenPart_s(void *p);
   static void destruct_eventBuffercLcLGenPart_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::GenPart_s*)
   {
      ::eventBuffer::GenPart_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::GenPart_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::GenPart_s", "eventBuffer.h", 1213,
                  typeid(::eventBuffer::GenPart_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLGenPart_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::GenPart_s) );
      instance.SetNew(&new_eventBuffercLcLGenPart_s);
      instance.SetNewArray(&newArray_eventBuffercLcLGenPart_s);
      instance.SetDelete(&delete_eventBuffercLcLGenPart_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLGenPart_s);
      instance.SetDestructor(&destruct_eventBuffercLcLGenPart_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::GenPart_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::GenPart_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::GenPart_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLGenPart_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::GenPart_s*)0x0)->GetClass();
      eventBuffercLcLGenPart_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLGenPart_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLGenVisTau_s_Dictionary();
   static void eventBuffercLcLGenVisTau_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLGenVisTau_s(void *p = 0);
   static void *newArray_eventBuffercLcLGenVisTau_s(Long_t size, void *p);
   static void delete_eventBuffercLcLGenVisTau_s(void *p);
   static void deleteArray_eventBuffercLcLGenVisTau_s(void *p);
   static void destruct_eventBuffercLcLGenVisTau_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::GenVisTau_s*)
   {
      ::eventBuffer::GenVisTau_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::GenVisTau_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::GenVisTau_s", "eventBuffer.h", 1240,
                  typeid(::eventBuffer::GenVisTau_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLGenVisTau_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::GenVisTau_s) );
      instance.SetNew(&new_eventBuffercLcLGenVisTau_s);
      instance.SetNewArray(&newArray_eventBuffercLcLGenVisTau_s);
      instance.SetDelete(&delete_eventBuffercLcLGenVisTau_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLGenVisTau_s);
      instance.SetDestructor(&destruct_eventBuffercLcLGenVisTau_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::GenVisTau_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::GenVisTau_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::GenVisTau_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLGenVisTau_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::GenVisTau_s*)0x0)->GetClass();
      eventBuffercLcLGenVisTau_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLGenVisTau_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLIsoTrack_s_Dictionary();
   static void eventBuffercLcLIsoTrack_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLIsoTrack_s(void *p = 0);
   static void *newArray_eventBuffercLcLIsoTrack_s(Long_t size, void *p);
   static void delete_eventBuffercLcLIsoTrack_s(void *p);
   static void deleteArray_eventBuffercLcLIsoTrack_s(void *p);
   static void destruct_eventBuffercLcLIsoTrack_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::IsoTrack_s*)
   {
      ::eventBuffer::IsoTrack_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::IsoTrack_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::IsoTrack_s", "eventBuffer.h", 1265,
                  typeid(::eventBuffer::IsoTrack_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLIsoTrack_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::IsoTrack_s) );
      instance.SetNew(&new_eventBuffercLcLIsoTrack_s);
      instance.SetNewArray(&newArray_eventBuffercLcLIsoTrack_s);
      instance.SetDelete(&delete_eventBuffercLcLIsoTrack_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLIsoTrack_s);
      instance.SetDestructor(&destruct_eventBuffercLcLIsoTrack_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::IsoTrack_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::IsoTrack_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::IsoTrack_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLIsoTrack_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::IsoTrack_s*)0x0)->GetClass();
      eventBuffercLcLIsoTrack_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLIsoTrack_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLJet_s_Dictionary();
   static void eventBuffercLcLJet_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLJet_s(void *p = 0);
   static void *newArray_eventBuffercLcLJet_s(Long_t size, void *p);
   static void delete_eventBuffercLcLJet_s(void *p);
   static void deleteArray_eventBuffercLcLJet_s(void *p);
   static void destruct_eventBuffercLcLJet_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::Jet_s*)
   {
      ::eventBuffer::Jet_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::Jet_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::Jet_s", "eventBuffer.h", 1300,
                  typeid(::eventBuffer::Jet_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLJet_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::Jet_s) );
      instance.SetNew(&new_eventBuffercLcLJet_s);
      instance.SetNewArray(&newArray_eventBuffercLcLJet_s);
      instance.SetDelete(&delete_eventBuffercLcLJet_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLJet_s);
      instance.SetDestructor(&destruct_eventBuffercLcLJet_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::Jet_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::Jet_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::Jet_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLJet_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::Jet_s*)0x0)->GetClass();
      eventBuffercLcLJet_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLJet_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLLHEPart_s_Dictionary();
   static void eventBuffercLcLLHEPart_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLLHEPart_s(void *p = 0);
   static void *newArray_eventBuffercLcLLHEPart_s(Long_t size, void *p);
   static void delete_eventBuffercLcLLHEPart_s(void *p);
   static void deleteArray_eventBuffercLcLLHEPart_s(void *p);
   static void destruct_eventBuffercLcLLHEPart_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::LHEPart_s*)
   {
      ::eventBuffer::LHEPart_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::LHEPart_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::LHEPart_s", "eventBuffer.h", 1371,
                  typeid(::eventBuffer::LHEPart_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLLHEPart_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::LHEPart_s) );
      instance.SetNew(&new_eventBuffercLcLLHEPart_s);
      instance.SetNewArray(&newArray_eventBuffercLcLLHEPart_s);
      instance.SetDelete(&delete_eventBuffercLcLLHEPart_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLLHEPart_s);
      instance.SetDestructor(&destruct_eventBuffercLcLLHEPart_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::LHEPart_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::LHEPart_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::LHEPart_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLLHEPart_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::LHEPart_s*)0x0)->GetClass();
      eventBuffercLcLLHEPart_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLLHEPart_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLMuon_s_Dictionary();
   static void eventBuffercLcLMuon_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLMuon_s(void *p = 0);
   static void *newArray_eventBuffercLcLMuon_s(Long_t size, void *p);
   static void delete_eventBuffercLcLMuon_s(void *p);
   static void deleteArray_eventBuffercLcLMuon_s(void *p);
   static void destruct_eventBuffercLcLMuon_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::Muon_s*)
   {
      ::eventBuffer::Muon_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::Muon_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::Muon_s", "eventBuffer.h", 1392,
                  typeid(::eventBuffer::Muon_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLMuon_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::Muon_s) );
      instance.SetNew(&new_eventBuffercLcLMuon_s);
      instance.SetNewArray(&newArray_eventBuffercLcLMuon_s);
      instance.SetDelete(&delete_eventBuffercLcLMuon_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLMuon_s);
      instance.SetDestructor(&destruct_eventBuffercLcLMuon_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::Muon_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::Muon_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::Muon_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLMuon_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::Muon_s*)0x0)->GetClass();
      eventBuffercLcLMuon_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLMuon_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLPhoton_s_Dictionary();
   static void eventBuffercLcLPhoton_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLPhoton_s(void *p = 0);
   static void *newArray_eventBuffercLcLPhoton_s(Long_t size, void *p);
   static void delete_eventBuffercLcLPhoton_s(void *p);
   static void deleteArray_eventBuffercLcLPhoton_s(void *p);
   static void destruct_eventBuffercLcLPhoton_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::Photon_s*)
   {
      ::eventBuffer::Photon_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::Photon_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::Photon_s", "eventBuffer.h", 1467,
                  typeid(::eventBuffer::Photon_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLPhoton_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::Photon_s) );
      instance.SetNew(&new_eventBuffercLcLPhoton_s);
      instance.SetNewArray(&newArray_eventBuffercLcLPhoton_s);
      instance.SetDelete(&delete_eventBuffercLcLPhoton_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLPhoton_s);
      instance.SetDestructor(&destruct_eventBuffercLcLPhoton_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::Photon_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::Photon_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::Photon_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLPhoton_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::Photon_s*)0x0)->GetClass();
      eventBuffercLcLPhoton_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLPhoton_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLSV_s_Dictionary();
   static void eventBuffercLcLSV_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLSV_s(void *p = 0);
   static void *newArray_eventBuffercLcLSV_s(Long_t size, void *p);
   static void delete_eventBuffercLcLSV_s(void *p);
   static void deleteArray_eventBuffercLcLSV_s(void *p);
   static void destruct_eventBuffercLcLSV_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::SV_s*)
   {
      ::eventBuffer::SV_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::SV_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::SV_s", "eventBuffer.h", 1532,
                  typeid(::eventBuffer::SV_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLSV_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::SV_s) );
      instance.SetNew(&new_eventBuffercLcLSV_s);
      instance.SetNewArray(&newArray_eventBuffercLcLSV_s);
      instance.SetDelete(&delete_eventBuffercLcLSV_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLSV_s);
      instance.SetDestructor(&destruct_eventBuffercLcLSV_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::SV_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::SV_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::SV_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLSV_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::SV_s*)0x0)->GetClass();
      eventBuffercLcLSV_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLSV_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLSoftActivityJet_s_Dictionary();
   static void eventBuffercLcLSoftActivityJet_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLSoftActivityJet_s(void *p = 0);
   static void *newArray_eventBuffercLcLSoftActivityJet_s(Long_t size, void *p);
   static void delete_eventBuffercLcLSoftActivityJet_s(void *p);
   static void deleteArray_eventBuffercLcLSoftActivityJet_s(void *p);
   static void destruct_eventBuffercLcLSoftActivityJet_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::SoftActivityJet_s*)
   {
      ::eventBuffer::SoftActivityJet_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::SoftActivityJet_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::SoftActivityJet_s", "eventBuffer.h", 1567,
                  typeid(::eventBuffer::SoftActivityJet_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLSoftActivityJet_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::SoftActivityJet_s) );
      instance.SetNew(&new_eventBuffercLcLSoftActivityJet_s);
      instance.SetNewArray(&newArray_eventBuffercLcLSoftActivityJet_s);
      instance.SetDelete(&delete_eventBuffercLcLSoftActivityJet_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLSoftActivityJet_s);
      instance.SetDestructor(&destruct_eventBuffercLcLSoftActivityJet_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::SoftActivityJet_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::SoftActivityJet_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::SoftActivityJet_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLSoftActivityJet_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::SoftActivityJet_s*)0x0)->GetClass();
      eventBuffercLcLSoftActivityJet_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLSoftActivityJet_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLSubGenJetAK8_s_Dictionary();
   static void eventBuffercLcLSubGenJetAK8_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLSubGenJetAK8_s(void *p = 0);
   static void *newArray_eventBuffercLcLSubGenJetAK8_s(Long_t size, void *p);
   static void delete_eventBuffercLcLSubGenJetAK8_s(void *p);
   static void deleteArray_eventBuffercLcLSubGenJetAK8_s(void *p);
   static void destruct_eventBuffercLcLSubGenJetAK8_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::SubGenJetAK8_s*)
   {
      ::eventBuffer::SubGenJetAK8_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::SubGenJetAK8_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::SubGenJetAK8_s", "eventBuffer.h", 1584,
                  typeid(::eventBuffer::SubGenJetAK8_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLSubGenJetAK8_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::SubGenJetAK8_s) );
      instance.SetNew(&new_eventBuffercLcLSubGenJetAK8_s);
      instance.SetNewArray(&newArray_eventBuffercLcLSubGenJetAK8_s);
      instance.SetDelete(&delete_eventBuffercLcLSubGenJetAK8_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLSubGenJetAK8_s);
      instance.SetDestructor(&destruct_eventBuffercLcLSubGenJetAK8_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::SubGenJetAK8_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::SubGenJetAK8_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::SubGenJetAK8_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLSubGenJetAK8_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::SubGenJetAK8_s*)0x0)->GetClass();
      eventBuffercLcLSubGenJetAK8_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLSubGenJetAK8_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLSubJet_s_Dictionary();
   static void eventBuffercLcLSubJet_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLSubJet_s(void *p = 0);
   static void *newArray_eventBuffercLcLSubJet_s(Long_t size, void *p);
   static void delete_eventBuffercLcLSubJet_s(void *p);
   static void deleteArray_eventBuffercLcLSubJet_s(void *p);
   static void destruct_eventBuffercLcLSubJet_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::SubJet_s*)
   {
      ::eventBuffer::SubJet_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::SubJet_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::SubJet_s", "eventBuffer.h", 1603,
                  typeid(::eventBuffer::SubJet_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLSubJet_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::SubJet_s) );
      instance.SetNew(&new_eventBuffercLcLSubJet_s);
      instance.SetNewArray(&newArray_eventBuffercLcLSubJet_s);
      instance.SetDelete(&delete_eventBuffercLcLSubJet_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLSubJet_s);
      instance.SetDestructor(&destruct_eventBuffercLcLSubJet_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::SubJet_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::SubJet_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::SubJet_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLSubJet_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::SubJet_s*)0x0)->GetClass();
      eventBuffercLcLSubJet_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLSubJet_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLTau_s_Dictionary();
   static void eventBuffercLcLTau_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLTau_s(void *p = 0);
   static void *newArray_eventBuffercLcLTau_s(Long_t size, void *p);
   static void delete_eventBuffercLcLTau_s(void *p);
   static void deleteArray_eventBuffercLcLTau_s(void *p);
   static void destruct_eventBuffercLcLTau_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::Tau_s*)
   {
      ::eventBuffer::Tau_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::Tau_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::Tau_s", "eventBuffer.h", 1640,
                  typeid(::eventBuffer::Tau_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLTau_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::Tau_s) );
      instance.SetNew(&new_eventBuffercLcLTau_s);
      instance.SetNewArray(&newArray_eventBuffercLcLTau_s);
      instance.SetDelete(&delete_eventBuffercLcLTau_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLTau_s);
      instance.SetDestructor(&destruct_eventBuffercLcLTau_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::Tau_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::Tau_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::Tau_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLTau_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::Tau_s*)0x0)->GetClass();
      eventBuffercLcLTau_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLTau_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *eventBuffercLcLTrigObj_s_Dictionary();
   static void eventBuffercLcLTrigObj_s_TClassManip(TClass*);
   static void *new_eventBuffercLcLTrigObj_s(void *p = 0);
   static void *newArray_eventBuffercLcLTrigObj_s(Long_t size, void *p);
   static void delete_eventBuffercLcLTrigObj_s(void *p);
   static void deleteArray_eventBuffercLcLTrigObj_s(void *p);
   static void destruct_eventBuffercLcLTrigObj_s(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::eventBuffer::TrigObj_s*)
   {
      ::eventBuffer::TrigObj_s *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::eventBuffer::TrigObj_s));
      static ::ROOT::TGenericClassInfo 
         instance("eventBuffer::TrigObj_s", "eventBuffer.h", 1725,
                  typeid(::eventBuffer::TrigObj_s), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &eventBuffercLcLTrigObj_s_Dictionary, isa_proxy, 0,
                  sizeof(::eventBuffer::TrigObj_s) );
      instance.SetNew(&new_eventBuffercLcLTrigObj_s);
      instance.SetNewArray(&newArray_eventBuffercLcLTrigObj_s);
      instance.SetDelete(&delete_eventBuffercLcLTrigObj_s);
      instance.SetDeleteArray(&deleteArray_eventBuffercLcLTrigObj_s);
      instance.SetDestructor(&destruct_eventBuffercLcLTrigObj_s);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::eventBuffer::TrigObj_s*)
   {
      return GenerateInitInstanceLocal((::eventBuffer::TrigObj_s*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::eventBuffer::TrigObj_s*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *eventBuffercLcLTrigObj_s_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::eventBuffer::TrigObj_s*)0x0)->GetClass();
      eventBuffercLcLTrigObj_s_TClassManip(theClass);
   return theClass;
   }

   static void eventBuffercLcLTrigObj_s_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *outputFile_Dictionary();
   static void outputFile_TClassManip(TClass*);
   static void delete_outputFile(void *p);
   static void deleteArray_outputFile(void *p);
   static void destruct_outputFile(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::outputFile*)
   {
      ::outputFile *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::outputFile));
      static ::ROOT::TGenericClassInfo 
         instance("outputFile", "tnm.h", 33,
                  typeid(::outputFile), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &outputFile_Dictionary, isa_proxy, 0,
                  sizeof(::outputFile) );
      instance.SetDelete(&delete_outputFile);
      instance.SetDeleteArray(&deleteArray_outputFile);
      instance.SetDestructor(&destruct_outputFile);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::outputFile*)
   {
      return GenerateInitInstanceLocal((::outputFile*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::outputFile*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *outputFile_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::outputFile*)0x0)->GetClass();
      outputFile_TClassManip(theClass);
   return theClass;
   }

   static void outputFile_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *commandLine_Dictionary();
   static void commandLine_TClassManip(TClass*);
   static void *new_commandLine(void *p = 0);
   static void *newArray_commandLine(Long_t size, void *p);
   static void delete_commandLine(void *p);
   static void deleteArray_commandLine(void *p);
   static void destruct_commandLine(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::commandLine*)
   {
      ::commandLine *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::commandLine));
      static ::ROOT::TGenericClassInfo 
         instance("commandLine", "tnm.h", 52,
                  typeid(::commandLine), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &commandLine_Dictionary, isa_proxy, 0,
                  sizeof(::commandLine) );
      instance.SetNew(&new_commandLine);
      instance.SetNewArray(&newArray_commandLine);
      instance.SetDelete(&delete_commandLine);
      instance.SetDeleteArray(&deleteArray_commandLine);
      instance.SetDestructor(&destruct_commandLine);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::commandLine*)
   {
      return GenerateInitInstanceLocal((::commandLine*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::commandLine*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *commandLine_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::commandLine*)0x0)->GetClass();
      commandLine_TClassManip(theClass);
   return theClass;
   }

   static void commandLine_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *matchedPair_Dictionary();
   static void matchedPair_TClassManip(TClass*);
   static void *new_matchedPair(void *p = 0);
   static void *newArray_matchedPair(Long_t size, void *p);
   static void delete_matchedPair(void *p);
   static void deleteArray_matchedPair(void *p);
   static void destruct_matchedPair(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::matchedPair*)
   {
      ::matchedPair *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::matchedPair));
      static ::ROOT::TGenericClassInfo 
         instance("matchedPair", "tnm.h", 76,
                  typeid(::matchedPair), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &matchedPair_Dictionary, isa_proxy, 0,
                  sizeof(::matchedPair) );
      instance.SetNew(&new_matchedPair);
      instance.SetNewArray(&newArray_matchedPair);
      instance.SetDelete(&delete_matchedPair);
      instance.SetDeleteArray(&deleteArray_matchedPair);
      instance.SetDestructor(&destruct_matchedPair);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::matchedPair*)
   {
      return GenerateInitInstanceLocal((::matchedPair*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::matchedPair*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *matchedPair_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::matchedPair*)0x0)->GetClass();
      matchedPair_TClassManip(theClass);
   return theClass;
   }

   static void matchedPair_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ptThing_Dictionary();
   static void ptThing_TClassManip(TClass*);
   static void *new_ptThing(void *p = 0);
   static void *newArray_ptThing(Long_t size, void *p);
   static void delete_ptThing(void *p);
   static void deleteArray_ptThing(void *p);
   static void destruct_ptThing(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ptThing*)
   {
      ::ptThing *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ptThing));
      static ::ROOT::TGenericClassInfo 
         instance("ptThing", "tnm.h", 86,
                  typeid(::ptThing), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ptThing_Dictionary, isa_proxy, 0,
                  sizeof(::ptThing) );
      instance.SetNew(&new_ptThing);
      instance.SetNewArray(&newArray_ptThing);
      instance.SetDelete(&delete_ptThing);
      instance.SetDeleteArray(&deleteArray_ptThing);
      instance.SetDestructor(&destruct_ptThing);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ptThing*)
   {
      return GenerateInitInstanceLocal((::ptThing*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ptThing*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ptThing_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ptThing*)0x0)->GetClass();
      ptThing_TClassManip(theClass);
   return theClass;
   }

   static void ptThing_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_itreestream(void *p) {
      return  p ? new(p) ::itreestream : new ::itreestream;
   }
   static void *newArray_itreestream(Long_t nElements, void *p) {
      return p ? new(p) ::itreestream[nElements] : new ::itreestream[nElements];
   }
   // Wrapper around operator delete
   static void delete_itreestream(void *p) {
      delete ((::itreestream*)p);
   }
   static void deleteArray_itreestream(void *p) {
      delete [] ((::itreestream*)p);
   }
   static void destruct_itreestream(void *p) {
      typedef ::itreestream current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::itreestream

namespace ROOT {
   // Wrappers around operator new
   static void *new_otreestream(void *p) {
      return  p ? new(p) ::otreestream : new ::otreestream;
   }
   static void *newArray_otreestream(Long_t nElements, void *p) {
      return p ? new(p) ::otreestream[nElements] : new ::otreestream[nElements];
   }
   // Wrapper around operator delete
   static void delete_otreestream(void *p) {
      delete ((::otreestream*)p);
   }
   static void deleteArray_otreestream(void *p) {
      delete [] ((::otreestream*)p);
   }
   static void destruct_otreestream(void *p) {
      typedef ::otreestream current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::otreestream

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffer(void *p) {
      return  p ? new(p) ::eventBuffer : new ::eventBuffer;
   }
   static void *newArray_eventBuffer(Long_t nElements, void *p) {
      return p ? new(p) ::eventBuffer[nElements] : new ::eventBuffer[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffer(void *p) {
      delete ((::eventBuffer*)p);
   }
   static void deleteArray_eventBuffer(void *p) {
      delete [] ((::eventBuffer*)p);
   }
   static void destruct_eventBuffer(void *p) {
      typedef ::eventBuffer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLElectron_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Electron_s : new ::eventBuffer::Electron_s;
   }
   static void *newArray_eventBuffercLcLElectron_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Electron_s[nElements] : new ::eventBuffer::Electron_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLElectron_s(void *p) {
      delete ((::eventBuffer::Electron_s*)p);
   }
   static void deleteArray_eventBuffercLcLElectron_s(void *p) {
      delete [] ((::eventBuffer::Electron_s*)p);
   }
   static void destruct_eventBuffercLcLElectron_s(void *p) {
      typedef ::eventBuffer::Electron_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::Electron_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLFatJet_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::FatJet_s : new ::eventBuffer::FatJet_s;
   }
   static void *newArray_eventBuffercLcLFatJet_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::FatJet_s[nElements] : new ::eventBuffer::FatJet_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLFatJet_s(void *p) {
      delete ((::eventBuffer::FatJet_s*)p);
   }
   static void deleteArray_eventBuffercLcLFatJet_s(void *p) {
      delete [] ((::eventBuffer::FatJet_s*)p);
   }
   static void destruct_eventBuffercLcLFatJet_s(void *p) {
      typedef ::eventBuffer::FatJet_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::FatJet_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLGenJet_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenJet_s : new ::eventBuffer::GenJet_s;
   }
   static void *newArray_eventBuffercLcLGenJet_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenJet_s[nElements] : new ::eventBuffer::GenJet_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLGenJet_s(void *p) {
      delete ((::eventBuffer::GenJet_s*)p);
   }
   static void deleteArray_eventBuffercLcLGenJet_s(void *p) {
      delete [] ((::eventBuffer::GenJet_s*)p);
   }
   static void destruct_eventBuffercLcLGenJet_s(void *p) {
      typedef ::eventBuffer::GenJet_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::GenJet_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLGenJetAK8_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenJetAK8_s : new ::eventBuffer::GenJetAK8_s;
   }
   static void *newArray_eventBuffercLcLGenJetAK8_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenJetAK8_s[nElements] : new ::eventBuffer::GenJetAK8_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLGenJetAK8_s(void *p) {
      delete ((::eventBuffer::GenJetAK8_s*)p);
   }
   static void deleteArray_eventBuffercLcLGenJetAK8_s(void *p) {
      delete [] ((::eventBuffer::GenJetAK8_s*)p);
   }
   static void destruct_eventBuffercLcLGenJetAK8_s(void *p) {
      typedef ::eventBuffer::GenJetAK8_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::GenJetAK8_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLGenPart_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenPart_s : new ::eventBuffer::GenPart_s;
   }
   static void *newArray_eventBuffercLcLGenPart_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenPart_s[nElements] : new ::eventBuffer::GenPart_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLGenPart_s(void *p) {
      delete ((::eventBuffer::GenPart_s*)p);
   }
   static void deleteArray_eventBuffercLcLGenPart_s(void *p) {
      delete [] ((::eventBuffer::GenPart_s*)p);
   }
   static void destruct_eventBuffercLcLGenPart_s(void *p) {
      typedef ::eventBuffer::GenPart_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::GenPart_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLGenVisTau_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenVisTau_s : new ::eventBuffer::GenVisTau_s;
   }
   static void *newArray_eventBuffercLcLGenVisTau_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::GenVisTau_s[nElements] : new ::eventBuffer::GenVisTau_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLGenVisTau_s(void *p) {
      delete ((::eventBuffer::GenVisTau_s*)p);
   }
   static void deleteArray_eventBuffercLcLGenVisTau_s(void *p) {
      delete [] ((::eventBuffer::GenVisTau_s*)p);
   }
   static void destruct_eventBuffercLcLGenVisTau_s(void *p) {
      typedef ::eventBuffer::GenVisTau_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::GenVisTau_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLIsoTrack_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::IsoTrack_s : new ::eventBuffer::IsoTrack_s;
   }
   static void *newArray_eventBuffercLcLIsoTrack_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::IsoTrack_s[nElements] : new ::eventBuffer::IsoTrack_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLIsoTrack_s(void *p) {
      delete ((::eventBuffer::IsoTrack_s*)p);
   }
   static void deleteArray_eventBuffercLcLIsoTrack_s(void *p) {
      delete [] ((::eventBuffer::IsoTrack_s*)p);
   }
   static void destruct_eventBuffercLcLIsoTrack_s(void *p) {
      typedef ::eventBuffer::IsoTrack_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::IsoTrack_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLJet_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Jet_s : new ::eventBuffer::Jet_s;
   }
   static void *newArray_eventBuffercLcLJet_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Jet_s[nElements] : new ::eventBuffer::Jet_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLJet_s(void *p) {
      delete ((::eventBuffer::Jet_s*)p);
   }
   static void deleteArray_eventBuffercLcLJet_s(void *p) {
      delete [] ((::eventBuffer::Jet_s*)p);
   }
   static void destruct_eventBuffercLcLJet_s(void *p) {
      typedef ::eventBuffer::Jet_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::Jet_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLLHEPart_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::LHEPart_s : new ::eventBuffer::LHEPart_s;
   }
   static void *newArray_eventBuffercLcLLHEPart_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::LHEPart_s[nElements] : new ::eventBuffer::LHEPart_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLLHEPart_s(void *p) {
      delete ((::eventBuffer::LHEPart_s*)p);
   }
   static void deleteArray_eventBuffercLcLLHEPart_s(void *p) {
      delete [] ((::eventBuffer::LHEPart_s*)p);
   }
   static void destruct_eventBuffercLcLLHEPart_s(void *p) {
      typedef ::eventBuffer::LHEPart_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::LHEPart_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLMuon_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Muon_s : new ::eventBuffer::Muon_s;
   }
   static void *newArray_eventBuffercLcLMuon_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Muon_s[nElements] : new ::eventBuffer::Muon_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLMuon_s(void *p) {
      delete ((::eventBuffer::Muon_s*)p);
   }
   static void deleteArray_eventBuffercLcLMuon_s(void *p) {
      delete [] ((::eventBuffer::Muon_s*)p);
   }
   static void destruct_eventBuffercLcLMuon_s(void *p) {
      typedef ::eventBuffer::Muon_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::Muon_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLPhoton_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Photon_s : new ::eventBuffer::Photon_s;
   }
   static void *newArray_eventBuffercLcLPhoton_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Photon_s[nElements] : new ::eventBuffer::Photon_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLPhoton_s(void *p) {
      delete ((::eventBuffer::Photon_s*)p);
   }
   static void deleteArray_eventBuffercLcLPhoton_s(void *p) {
      delete [] ((::eventBuffer::Photon_s*)p);
   }
   static void destruct_eventBuffercLcLPhoton_s(void *p) {
      typedef ::eventBuffer::Photon_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::Photon_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLSV_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SV_s : new ::eventBuffer::SV_s;
   }
   static void *newArray_eventBuffercLcLSV_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SV_s[nElements] : new ::eventBuffer::SV_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLSV_s(void *p) {
      delete ((::eventBuffer::SV_s*)p);
   }
   static void deleteArray_eventBuffercLcLSV_s(void *p) {
      delete [] ((::eventBuffer::SV_s*)p);
   }
   static void destruct_eventBuffercLcLSV_s(void *p) {
      typedef ::eventBuffer::SV_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::SV_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLSoftActivityJet_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SoftActivityJet_s : new ::eventBuffer::SoftActivityJet_s;
   }
   static void *newArray_eventBuffercLcLSoftActivityJet_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SoftActivityJet_s[nElements] : new ::eventBuffer::SoftActivityJet_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLSoftActivityJet_s(void *p) {
      delete ((::eventBuffer::SoftActivityJet_s*)p);
   }
   static void deleteArray_eventBuffercLcLSoftActivityJet_s(void *p) {
      delete [] ((::eventBuffer::SoftActivityJet_s*)p);
   }
   static void destruct_eventBuffercLcLSoftActivityJet_s(void *p) {
      typedef ::eventBuffer::SoftActivityJet_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::SoftActivityJet_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLSubGenJetAK8_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SubGenJetAK8_s : new ::eventBuffer::SubGenJetAK8_s;
   }
   static void *newArray_eventBuffercLcLSubGenJetAK8_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SubGenJetAK8_s[nElements] : new ::eventBuffer::SubGenJetAK8_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLSubGenJetAK8_s(void *p) {
      delete ((::eventBuffer::SubGenJetAK8_s*)p);
   }
   static void deleteArray_eventBuffercLcLSubGenJetAK8_s(void *p) {
      delete [] ((::eventBuffer::SubGenJetAK8_s*)p);
   }
   static void destruct_eventBuffercLcLSubGenJetAK8_s(void *p) {
      typedef ::eventBuffer::SubGenJetAK8_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::SubGenJetAK8_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLSubJet_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SubJet_s : new ::eventBuffer::SubJet_s;
   }
   static void *newArray_eventBuffercLcLSubJet_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::SubJet_s[nElements] : new ::eventBuffer::SubJet_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLSubJet_s(void *p) {
      delete ((::eventBuffer::SubJet_s*)p);
   }
   static void deleteArray_eventBuffercLcLSubJet_s(void *p) {
      delete [] ((::eventBuffer::SubJet_s*)p);
   }
   static void destruct_eventBuffercLcLSubJet_s(void *p) {
      typedef ::eventBuffer::SubJet_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::SubJet_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLTau_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Tau_s : new ::eventBuffer::Tau_s;
   }
   static void *newArray_eventBuffercLcLTau_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::Tau_s[nElements] : new ::eventBuffer::Tau_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLTau_s(void *p) {
      delete ((::eventBuffer::Tau_s*)p);
   }
   static void deleteArray_eventBuffercLcLTau_s(void *p) {
      delete [] ((::eventBuffer::Tau_s*)p);
   }
   static void destruct_eventBuffercLcLTau_s(void *p) {
      typedef ::eventBuffer::Tau_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::Tau_s

namespace ROOT {
   // Wrappers around operator new
   static void *new_eventBuffercLcLTrigObj_s(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::TrigObj_s : new ::eventBuffer::TrigObj_s;
   }
   static void *newArray_eventBuffercLcLTrigObj_s(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::eventBuffer::TrigObj_s[nElements] : new ::eventBuffer::TrigObj_s[nElements];
   }
   // Wrapper around operator delete
   static void delete_eventBuffercLcLTrigObj_s(void *p) {
      delete ((::eventBuffer::TrigObj_s*)p);
   }
   static void deleteArray_eventBuffercLcLTrigObj_s(void *p) {
      delete [] ((::eventBuffer::TrigObj_s*)p);
   }
   static void destruct_eventBuffercLcLTrigObj_s(void *p) {
      typedef ::eventBuffer::TrigObj_s current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::eventBuffer::TrigObj_s

namespace ROOT {
   // Wrapper around operator delete
   static void delete_outputFile(void *p) {
      delete ((::outputFile*)p);
   }
   static void deleteArray_outputFile(void *p) {
      delete [] ((::outputFile*)p);
   }
   static void destruct_outputFile(void *p) {
      typedef ::outputFile current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::outputFile

namespace ROOT {
   // Wrappers around operator new
   static void *new_commandLine(void *p) {
      return  p ? new(p) ::commandLine : new ::commandLine;
   }
   static void *newArray_commandLine(Long_t nElements, void *p) {
      return p ? new(p) ::commandLine[nElements] : new ::commandLine[nElements];
   }
   // Wrapper around operator delete
   static void delete_commandLine(void *p) {
      delete ((::commandLine*)p);
   }
   static void deleteArray_commandLine(void *p) {
      delete [] ((::commandLine*)p);
   }
   static void destruct_commandLine(void *p) {
      typedef ::commandLine current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::commandLine

namespace ROOT {
   // Wrappers around operator new
   static void *new_matchedPair(void *p) {
      return  p ? new(p) ::matchedPair : new ::matchedPair;
   }
   static void *newArray_matchedPair(Long_t nElements, void *p) {
      return p ? new(p) ::matchedPair[nElements] : new ::matchedPair[nElements];
   }
   // Wrapper around operator delete
   static void delete_matchedPair(void *p) {
      delete ((::matchedPair*)p);
   }
   static void deleteArray_matchedPair(void *p) {
      delete [] ((::matchedPair*)p);
   }
   static void destruct_matchedPair(void *p) {
      typedef ::matchedPair current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::matchedPair

namespace ROOT {
   // Wrappers around operator new
   static void *new_ptThing(void *p) {
      return  p ? new(p) ::ptThing : new ::ptThing;
   }
   static void *newArray_ptThing(Long_t nElements, void *p) {
      return p ? new(p) ::ptThing[nElements] : new ::ptThing[nElements];
   }
   // Wrapper around operator delete
   static void delete_ptThing(void *p) {
      delete ((::ptThing*)p);
   }
   static void deleteArray_ptThing(void *p) {
      delete [] ((::ptThing*)p);
   }
   static void destruct_ptThing(void *p) {
      typedef ::ptThing current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ptThing

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLTrigObj_sgR_Dictionary();
   static void vectorlEeventBuffercLcLTrigObj_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLTrigObj_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLTrigObj_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLTrigObj_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLTrigObj_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLTrigObj_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::TrigObj_s>*)
   {
      vector<eventBuffer::TrigObj_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::TrigObj_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::TrigObj_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::TrigObj_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLTrigObj_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::TrigObj_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLTrigObj_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLTrigObj_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLTrigObj_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLTrigObj_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLTrigObj_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::TrigObj_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::TrigObj_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLTrigObj_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::TrigObj_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLTrigObj_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLTrigObj_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLTrigObj_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::TrigObj_s> : new vector<eventBuffer::TrigObj_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLTrigObj_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::TrigObj_s>[nElements] : new vector<eventBuffer::TrigObj_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLTrigObj_sgR(void *p) {
      delete ((vector<eventBuffer::TrigObj_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLTrigObj_sgR(void *p) {
      delete [] ((vector<eventBuffer::TrigObj_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLTrigObj_sgR(void *p) {
      typedef vector<eventBuffer::TrigObj_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::TrigObj_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLTau_sgR_Dictionary();
   static void vectorlEeventBuffercLcLTau_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLTau_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLTau_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLTau_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLTau_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLTau_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::Tau_s>*)
   {
      vector<eventBuffer::Tau_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::Tau_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::Tau_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::Tau_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLTau_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::Tau_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLTau_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLTau_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLTau_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLTau_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLTau_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::Tau_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::Tau_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLTau_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::Tau_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLTau_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLTau_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLTau_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Tau_s> : new vector<eventBuffer::Tau_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLTau_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Tau_s>[nElements] : new vector<eventBuffer::Tau_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLTau_sgR(void *p) {
      delete ((vector<eventBuffer::Tau_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLTau_sgR(void *p) {
      delete [] ((vector<eventBuffer::Tau_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLTau_sgR(void *p) {
      typedef vector<eventBuffer::Tau_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::Tau_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLSubJet_sgR_Dictionary();
   static void vectorlEeventBuffercLcLSubJet_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLSubJet_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLSubJet_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLSubJet_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLSubJet_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLSubJet_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::SubJet_s>*)
   {
      vector<eventBuffer::SubJet_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::SubJet_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::SubJet_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::SubJet_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLSubJet_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::SubJet_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLSubJet_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLSubJet_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLSubJet_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLSubJet_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLSubJet_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::SubJet_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::SubJet_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLSubJet_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::SubJet_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLSubJet_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLSubJet_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLSubJet_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SubJet_s> : new vector<eventBuffer::SubJet_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLSubJet_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SubJet_s>[nElements] : new vector<eventBuffer::SubJet_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLSubJet_sgR(void *p) {
      delete ((vector<eventBuffer::SubJet_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLSubJet_sgR(void *p) {
      delete [] ((vector<eventBuffer::SubJet_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLSubJet_sgR(void *p) {
      typedef vector<eventBuffer::SubJet_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::SubJet_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLSubGenJetAK8_sgR_Dictionary();
   static void vectorlEeventBuffercLcLSubGenJetAK8_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLSubGenJetAK8_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::SubGenJetAK8_s>*)
   {
      vector<eventBuffer::SubGenJetAK8_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::SubGenJetAK8_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::SubGenJetAK8_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::SubGenJetAK8_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLSubGenJetAK8_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::SubGenJetAK8_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLSubGenJetAK8_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLSubGenJetAK8_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLSubGenJetAK8_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLSubGenJetAK8_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLSubGenJetAK8_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::SubGenJetAK8_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::SubGenJetAK8_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLSubGenJetAK8_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::SubGenJetAK8_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLSubGenJetAK8_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLSubGenJetAK8_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SubGenJetAK8_s> : new vector<eventBuffer::SubGenJetAK8_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLSubGenJetAK8_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SubGenJetAK8_s>[nElements] : new vector<eventBuffer::SubGenJetAK8_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p) {
      delete ((vector<eventBuffer::SubGenJetAK8_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p) {
      delete [] ((vector<eventBuffer::SubGenJetAK8_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLSubGenJetAK8_sgR(void *p) {
      typedef vector<eventBuffer::SubGenJetAK8_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::SubGenJetAK8_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLSoftActivityJet_sgR_Dictionary();
   static void vectorlEeventBuffercLcLSoftActivityJet_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLSoftActivityJet_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::SoftActivityJet_s>*)
   {
      vector<eventBuffer::SoftActivityJet_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::SoftActivityJet_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::SoftActivityJet_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::SoftActivityJet_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLSoftActivityJet_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::SoftActivityJet_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLSoftActivityJet_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLSoftActivityJet_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLSoftActivityJet_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLSoftActivityJet_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLSoftActivityJet_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::SoftActivityJet_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::SoftActivityJet_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLSoftActivityJet_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::SoftActivityJet_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLSoftActivityJet_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLSoftActivityJet_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SoftActivityJet_s> : new vector<eventBuffer::SoftActivityJet_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLSoftActivityJet_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SoftActivityJet_s>[nElements] : new vector<eventBuffer::SoftActivityJet_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p) {
      delete ((vector<eventBuffer::SoftActivityJet_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p) {
      delete [] ((vector<eventBuffer::SoftActivityJet_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLSoftActivityJet_sgR(void *p) {
      typedef vector<eventBuffer::SoftActivityJet_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::SoftActivityJet_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLSV_sgR_Dictionary();
   static void vectorlEeventBuffercLcLSV_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLSV_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLSV_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLSV_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLSV_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLSV_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::SV_s>*)
   {
      vector<eventBuffer::SV_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::SV_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::SV_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::SV_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLSV_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::SV_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLSV_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLSV_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLSV_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLSV_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLSV_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::SV_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::SV_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLSV_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::SV_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLSV_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLSV_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLSV_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SV_s> : new vector<eventBuffer::SV_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLSV_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::SV_s>[nElements] : new vector<eventBuffer::SV_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLSV_sgR(void *p) {
      delete ((vector<eventBuffer::SV_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLSV_sgR(void *p) {
      delete [] ((vector<eventBuffer::SV_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLSV_sgR(void *p) {
      typedef vector<eventBuffer::SV_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::SV_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLPhoton_sgR_Dictionary();
   static void vectorlEeventBuffercLcLPhoton_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLPhoton_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLPhoton_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLPhoton_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLPhoton_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLPhoton_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::Photon_s>*)
   {
      vector<eventBuffer::Photon_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::Photon_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::Photon_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::Photon_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLPhoton_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::Photon_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLPhoton_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLPhoton_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLPhoton_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLPhoton_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLPhoton_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::Photon_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::Photon_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLPhoton_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::Photon_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLPhoton_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLPhoton_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLPhoton_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Photon_s> : new vector<eventBuffer::Photon_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLPhoton_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Photon_s>[nElements] : new vector<eventBuffer::Photon_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLPhoton_sgR(void *p) {
      delete ((vector<eventBuffer::Photon_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLPhoton_sgR(void *p) {
      delete [] ((vector<eventBuffer::Photon_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLPhoton_sgR(void *p) {
      typedef vector<eventBuffer::Photon_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::Photon_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLMuon_sgR_Dictionary();
   static void vectorlEeventBuffercLcLMuon_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLMuon_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLMuon_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLMuon_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLMuon_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLMuon_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::Muon_s>*)
   {
      vector<eventBuffer::Muon_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::Muon_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::Muon_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::Muon_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLMuon_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::Muon_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLMuon_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLMuon_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLMuon_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLMuon_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLMuon_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::Muon_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::Muon_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLMuon_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::Muon_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLMuon_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLMuon_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLMuon_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Muon_s> : new vector<eventBuffer::Muon_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLMuon_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Muon_s>[nElements] : new vector<eventBuffer::Muon_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLMuon_sgR(void *p) {
      delete ((vector<eventBuffer::Muon_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLMuon_sgR(void *p) {
      delete [] ((vector<eventBuffer::Muon_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLMuon_sgR(void *p) {
      typedef vector<eventBuffer::Muon_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::Muon_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLLHEPart_sgR_Dictionary();
   static void vectorlEeventBuffercLcLLHEPart_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLLHEPart_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLLHEPart_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLLHEPart_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLLHEPart_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLLHEPart_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::LHEPart_s>*)
   {
      vector<eventBuffer::LHEPart_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::LHEPart_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::LHEPart_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::LHEPart_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLLHEPart_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::LHEPart_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLLHEPart_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLLHEPart_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLLHEPart_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLLHEPart_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLLHEPart_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::LHEPart_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::LHEPart_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLLHEPart_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::LHEPart_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLLHEPart_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLLHEPart_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLLHEPart_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::LHEPart_s> : new vector<eventBuffer::LHEPart_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLLHEPart_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::LHEPart_s>[nElements] : new vector<eventBuffer::LHEPart_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLLHEPart_sgR(void *p) {
      delete ((vector<eventBuffer::LHEPart_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLLHEPart_sgR(void *p) {
      delete [] ((vector<eventBuffer::LHEPart_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLLHEPart_sgR(void *p) {
      typedef vector<eventBuffer::LHEPart_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::LHEPart_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLJet_sgR_Dictionary();
   static void vectorlEeventBuffercLcLJet_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLJet_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLJet_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLJet_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLJet_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLJet_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::Jet_s>*)
   {
      vector<eventBuffer::Jet_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::Jet_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::Jet_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::Jet_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLJet_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::Jet_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLJet_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLJet_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLJet_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLJet_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLJet_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::Jet_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::Jet_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLJet_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::Jet_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLJet_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLJet_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLJet_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Jet_s> : new vector<eventBuffer::Jet_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLJet_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Jet_s>[nElements] : new vector<eventBuffer::Jet_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLJet_sgR(void *p) {
      delete ((vector<eventBuffer::Jet_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLJet_sgR(void *p) {
      delete [] ((vector<eventBuffer::Jet_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLJet_sgR(void *p) {
      typedef vector<eventBuffer::Jet_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::Jet_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLIsoTrack_sgR_Dictionary();
   static void vectorlEeventBuffercLcLIsoTrack_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLIsoTrack_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLIsoTrack_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLIsoTrack_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLIsoTrack_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLIsoTrack_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::IsoTrack_s>*)
   {
      vector<eventBuffer::IsoTrack_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::IsoTrack_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::IsoTrack_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::IsoTrack_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLIsoTrack_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::IsoTrack_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLIsoTrack_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLIsoTrack_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLIsoTrack_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLIsoTrack_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLIsoTrack_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::IsoTrack_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::IsoTrack_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLIsoTrack_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::IsoTrack_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLIsoTrack_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLIsoTrack_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLIsoTrack_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::IsoTrack_s> : new vector<eventBuffer::IsoTrack_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLIsoTrack_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::IsoTrack_s>[nElements] : new vector<eventBuffer::IsoTrack_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLIsoTrack_sgR(void *p) {
      delete ((vector<eventBuffer::IsoTrack_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLIsoTrack_sgR(void *p) {
      delete [] ((vector<eventBuffer::IsoTrack_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLIsoTrack_sgR(void *p) {
      typedef vector<eventBuffer::IsoTrack_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::IsoTrack_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLGenVisTau_sgR_Dictionary();
   static void vectorlEeventBuffercLcLGenVisTau_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLGenVisTau_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLGenVisTau_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLGenVisTau_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLGenVisTau_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLGenVisTau_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::GenVisTau_s>*)
   {
      vector<eventBuffer::GenVisTau_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::GenVisTau_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::GenVisTau_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::GenVisTau_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLGenVisTau_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::GenVisTau_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLGenVisTau_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLGenVisTau_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLGenVisTau_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLGenVisTau_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLGenVisTau_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::GenVisTau_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::GenVisTau_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLGenVisTau_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::GenVisTau_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLGenVisTau_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLGenVisTau_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLGenVisTau_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenVisTau_s> : new vector<eventBuffer::GenVisTau_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLGenVisTau_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenVisTau_s>[nElements] : new vector<eventBuffer::GenVisTau_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLGenVisTau_sgR(void *p) {
      delete ((vector<eventBuffer::GenVisTau_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLGenVisTau_sgR(void *p) {
      delete [] ((vector<eventBuffer::GenVisTau_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLGenVisTau_sgR(void *p) {
      typedef vector<eventBuffer::GenVisTau_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::GenVisTau_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLGenPart_sgR_Dictionary();
   static void vectorlEeventBuffercLcLGenPart_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLGenPart_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLGenPart_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLGenPart_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLGenPart_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLGenPart_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::GenPart_s>*)
   {
      vector<eventBuffer::GenPart_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::GenPart_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::GenPart_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::GenPart_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLGenPart_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::GenPart_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLGenPart_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLGenPart_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLGenPart_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLGenPart_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLGenPart_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::GenPart_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::GenPart_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLGenPart_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::GenPart_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLGenPart_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLGenPart_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLGenPart_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenPart_s> : new vector<eventBuffer::GenPart_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLGenPart_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenPart_s>[nElements] : new vector<eventBuffer::GenPart_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLGenPart_sgR(void *p) {
      delete ((vector<eventBuffer::GenPart_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLGenPart_sgR(void *p) {
      delete [] ((vector<eventBuffer::GenPart_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLGenPart_sgR(void *p) {
      typedef vector<eventBuffer::GenPart_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::GenPart_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLGenJet_sgR_Dictionary();
   static void vectorlEeventBuffercLcLGenJet_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLGenJet_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLGenJet_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLGenJet_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLGenJet_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLGenJet_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::GenJet_s>*)
   {
      vector<eventBuffer::GenJet_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::GenJet_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::GenJet_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::GenJet_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLGenJet_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::GenJet_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLGenJet_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLGenJet_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLGenJet_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLGenJet_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLGenJet_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::GenJet_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::GenJet_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLGenJet_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::GenJet_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLGenJet_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLGenJet_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLGenJet_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenJet_s> : new vector<eventBuffer::GenJet_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLGenJet_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenJet_s>[nElements] : new vector<eventBuffer::GenJet_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLGenJet_sgR(void *p) {
      delete ((vector<eventBuffer::GenJet_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLGenJet_sgR(void *p) {
      delete [] ((vector<eventBuffer::GenJet_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLGenJet_sgR(void *p) {
      typedef vector<eventBuffer::GenJet_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::GenJet_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLGenJetAK8_sgR_Dictionary();
   static void vectorlEeventBuffercLcLGenJetAK8_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLGenJetAK8_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::GenJetAK8_s>*)
   {
      vector<eventBuffer::GenJetAK8_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::GenJetAK8_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::GenJetAK8_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::GenJetAK8_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLGenJetAK8_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::GenJetAK8_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLGenJetAK8_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLGenJetAK8_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLGenJetAK8_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLGenJetAK8_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLGenJetAK8_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::GenJetAK8_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::GenJetAK8_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLGenJetAK8_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::GenJetAK8_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLGenJetAK8_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLGenJetAK8_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenJetAK8_s> : new vector<eventBuffer::GenJetAK8_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLGenJetAK8_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::GenJetAK8_s>[nElements] : new vector<eventBuffer::GenJetAK8_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p) {
      delete ((vector<eventBuffer::GenJetAK8_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p) {
      delete [] ((vector<eventBuffer::GenJetAK8_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLGenJetAK8_sgR(void *p) {
      typedef vector<eventBuffer::GenJetAK8_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::GenJetAK8_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLFatJet_sgR_Dictionary();
   static void vectorlEeventBuffercLcLFatJet_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLFatJet_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLFatJet_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLFatJet_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLFatJet_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLFatJet_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::FatJet_s>*)
   {
      vector<eventBuffer::FatJet_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::FatJet_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::FatJet_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::FatJet_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLFatJet_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::FatJet_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLFatJet_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLFatJet_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLFatJet_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLFatJet_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLFatJet_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::FatJet_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::FatJet_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLFatJet_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::FatJet_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLFatJet_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLFatJet_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLFatJet_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::FatJet_s> : new vector<eventBuffer::FatJet_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLFatJet_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::FatJet_s>[nElements] : new vector<eventBuffer::FatJet_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLFatJet_sgR(void *p) {
      delete ((vector<eventBuffer::FatJet_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLFatJet_sgR(void *p) {
      delete [] ((vector<eventBuffer::FatJet_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLFatJet_sgR(void *p) {
      typedef vector<eventBuffer::FatJet_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::FatJet_s>

namespace ROOT {
   static TClass *vectorlEeventBuffercLcLElectron_sgR_Dictionary();
   static void vectorlEeventBuffercLcLElectron_sgR_TClassManip(TClass*);
   static void *new_vectorlEeventBuffercLcLElectron_sgR(void *p = 0);
   static void *newArray_vectorlEeventBuffercLcLElectron_sgR(Long_t size, void *p);
   static void delete_vectorlEeventBuffercLcLElectron_sgR(void *p);
   static void deleteArray_vectorlEeventBuffercLcLElectron_sgR(void *p);
   static void destruct_vectorlEeventBuffercLcLElectron_sgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<eventBuffer::Electron_s>*)
   {
      vector<eventBuffer::Electron_s> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<eventBuffer::Electron_s>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<eventBuffer::Electron_s>", -2, "vector", 214,
                  typeid(vector<eventBuffer::Electron_s>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEeventBuffercLcLElectron_sgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<eventBuffer::Electron_s>) );
      instance.SetNew(&new_vectorlEeventBuffercLcLElectron_sgR);
      instance.SetNewArray(&newArray_vectorlEeventBuffercLcLElectron_sgR);
      instance.SetDelete(&delete_vectorlEeventBuffercLcLElectron_sgR);
      instance.SetDeleteArray(&deleteArray_vectorlEeventBuffercLcLElectron_sgR);
      instance.SetDestructor(&destruct_vectorlEeventBuffercLcLElectron_sgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<eventBuffer::Electron_s> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<eventBuffer::Electron_s>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEeventBuffercLcLElectron_sgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<eventBuffer::Electron_s>*)0x0)->GetClass();
      vectorlEeventBuffercLcLElectron_sgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEeventBuffercLcLElectron_sgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEeventBuffercLcLElectron_sgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Electron_s> : new vector<eventBuffer::Electron_s>;
   }
   static void *newArray_vectorlEeventBuffercLcLElectron_sgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<eventBuffer::Electron_s>[nElements] : new vector<eventBuffer::Electron_s>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEeventBuffercLcLElectron_sgR(void *p) {
      delete ((vector<eventBuffer::Electron_s>*)p);
   }
   static void deleteArray_vectorlEeventBuffercLcLElectron_sgR(void *p) {
      delete [] ((vector<eventBuffer::Electron_s>*)p);
   }
   static void destruct_vectorlEeventBuffercLcLElectron_sgR(void *p) {
      typedef vector<eventBuffer::Electron_s> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<eventBuffer::Electron_s>

namespace {
  void TriggerDictionaryInitialization_dictionary_Impl() {
    static const char* headers[] = {
"include/tnm.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc6_amd64_gcc630/lcg/root/6.10.08-elfike2//include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc630/lcg/root/6.10.08-elfike2/include",
"/d3/scratch/cghuh3811/CMSSW_9_4_9/src/BoostAnalyzer17/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "dictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$treestream.h")))  __attribute__((annotate("$clingAutoload$include/tnm.h")))  itreestream;
class __attribute__((annotate("$clingAutoload$treestream.h")))  __attribute__((annotate("$clingAutoload$include/tnm.h")))  otreestream;
struct __attribute__((annotate("$clingAutoload$eventBuffer.h")))  __attribute__((annotate("$clingAutoload$include/tnm.h")))  eventBuffer;
struct __attribute__((annotate("$clingAutoload$include/tnm.h")))  outputFile;
struct __attribute__((annotate("$clingAutoload$include/tnm.h")))  commandLine;
struct __attribute__((annotate("$clingAutoload$include/tnm.h")))  matchedPair;
struct __attribute__((annotate("$clingAutoload$include/tnm.h")))  ptThing;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "dictionary dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/tnm.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"change", payloadCode, "@",
"commandLine", payloadCode, "@",
"deltaPhi", payloadCode, "@",
"deltaR", payloadCode, "@",
"error", payloadCode, "@",
"eventBuffer", payloadCode, "@",
"eventBuffer::Electron_s", payloadCode, "@",
"eventBuffer::FatJet_s", payloadCode, "@",
"eventBuffer::GenJetAK8_s", payloadCode, "@",
"eventBuffer::GenJet_s", payloadCode, "@",
"eventBuffer::GenPart_s", payloadCode, "@",
"eventBuffer::GenVisTau_s", payloadCode, "@",
"eventBuffer::IsoTrack_s", payloadCode, "@",
"eventBuffer::Jet_s", payloadCode, "@",
"eventBuffer::LHEPart_s", payloadCode, "@",
"eventBuffer::Muon_s", payloadCode, "@",
"eventBuffer::Photon_s", payloadCode, "@",
"eventBuffer::SV_s", payloadCode, "@",
"eventBuffer::SoftActivityJet_s", payloadCode, "@",
"eventBuffer::SubGenJetAK8_s", payloadCode, "@",
"eventBuffer::SubJet_s", payloadCode, "@",
"eventBuffer::Tau_s", payloadCode, "@",
"eventBuffer::TrigObj_s", payloadCode, "@",
"itreestream", payloadCode, "@",
"matchedPair", payloadCode, "@",
"nameonly", payloadCode, "@",
"otreestream", payloadCode, "@",
"outputFile", payloadCode, "@",
"particleName", payloadCode, "@",
"ptThing", payloadCode, "@",
"setStyle", payloadCode, "@",
"shell", payloadCode, "@",
"split", payloadCode, "@",
"strip", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dictionary_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dictionary() {
  TriggerDictionaryInitialization_dictionary_Impl();
}
