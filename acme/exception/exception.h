#pragma once


#include "acme/operating_system/error_code.h"

//#include "acme/prototype/collection/array.h"

#include "acme/prototype/string/scoped_string_base.h"


enum enum_consequence
{

   e_consequence_none,
   e_consequence_fatal,
   e_consequence_blocking,
   e_consequence_workaroundable,
   e_consequence_too_generic_and_context_dependant,

};


class CLASS_DECL_ACME exception :
   virtual public ::particle
{
public:


   ::e_status                 m_estatus;

   bool                       m_bDumpCallStackTrace;
   string                     m_strCallStackTrace;
   bool                       m_bHandled;
   bool                       m_bContinue;
   enum_consequence           m_econsequenceUserDefault;
   string                     m_strTitle;
   string                     m_strMessage; // Message for the user
   string                     m_strDetails; // Details about exception (if available/applicable)
   //string                   m_strException;

   // A exception class is meant to be a small utility/tool class.
   // m_bLog -> too much managing (micro-managing and also big-managing)
   // from utility/tool small class of the Logging system()->
   // General-ever Log can be done by final handlers at Main Loop and crash handlers
   // Log can be supressed or translated at optional middle-stack handlers.
   // bool                    m_bLog;
   string                                    m_strLink;
   string                                    m_strFile;
   int                                       m_iLine;
   array_non_particle < error_code >         m_errorcodea;
   static bool                               s_bEnableCallStackBackTrace;


   exception();
//#ifdef __ANDROID__
//   exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrDetails = nullptr, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER);
//#else
   exception(const ::e_status& estatus, const ::scoped_string& scopedstrMessage = {}, const ::scoped_string& scopedstrDetails = {}, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr);
//#endif
   exception(const ::e_status& estatus, const ::array_non_particle < error_code >& errorcodea, const ::scoped_string& scopedstrMessage = {}, const ::scoped_string& scopedstrDetails = {}, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr);
   exception(const ::exception& exception);
   ~exception() override;


   ::pointer < ::subparticle > clone() override;


   static void enable_call_stack_back_trace(bool bEnable);


   virtual string get_message() const;

   virtual string get_title() const;
   
   virtual string get_consolidated_details(::particle * pparticle) const;
      
      
   inline ::e_status estatus() const { return m_estatus; }


};


#define RETURN_OR_THROW(bReturn, ppexception, EXCEPTION, ...) \
   if(bReturn) \
   { \
      if(ppexception) *ppexception = __allocate EXCEPTION(__VA_ARGS__); \
      return; \
   } \
   throw EXCEPTION(__VA_ARGS__)



CLASS_DECL_ACME write_text_stream & operator <<(write_text_stream & stream, const ::exception & exception);

