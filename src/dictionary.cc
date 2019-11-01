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
         instance("eventBuffer", "eventBuffer_small.h", 678,
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
         instance("eventBuffer::Electron_s", "eventBuffer_small.h", 961,
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
         instance("eventBuffer::FatJet_s", "eventBuffer_small.h", 1088,
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
         instance("eventBuffer::GenPart_s", "eventBuffer_small.h", 1165,
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
         instance("eventBuffer::Jet_s", "eventBuffer_small.h", 1192,
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
         instance("eventBuffer::Muon_s", "eventBuffer_small.h", 1267,
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
         instance("eventBuffer::Photon_s", "eventBuffer_small.h", 1366,
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
         instance("eventBuffer::SubJet_s", "eventBuffer_small.h", 1435,
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
         instance("eventBuffer::Tau_s", "eventBuffer_small.h", 1474,
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
         instance("outputFile", "tnm.h", 31,
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
         instance("commandLine", "tnm.h", 50,
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
         instance("matchedPair", "tnm.h", 74,
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
         instance("ptThing", "tnm.h", 84,
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
         instance("vector<eventBuffer::Tau_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::SubJet_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::Photon_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::Muon_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::Jet_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::GenPart_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::FatJet_s>", -2, "vector", 216,
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
         instance("vector<eventBuffer::Electron_s>", -2, "vector", 216,
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
"/cvmfs/cms.cern.ch/slc6_amd64_gcc700/lcg/root/6.12.07-gnimlf5//include",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc700/lcg/root/6.12.07-gnimlf5/include",
"/data/jkarancs/cernbox/nosync/work/CMSSW/SusyAnalysis/BoostAnalyzer17/CMSSW_10_2_16/src/BoostAnalyzer17/",
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
struct __attribute__((annotate("$clingAutoload$eventBuffer_small.h")))  __attribute__((annotate("$clingAutoload$include/tnm.h")))  eventBuffer;
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
"eventBuffer::GenPart_s", payloadCode, "@",
"eventBuffer::Jet_s", payloadCode, "@",
"eventBuffer::Muon_s", payloadCode, "@",
"eventBuffer::Photon_s", payloadCode, "@",
"eventBuffer::SubJet_s", payloadCode, "@",
"eventBuffer::Tau_s", payloadCode, "@",
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
