#pragma once


#include "acme/operating_system/error_code.h"


class CLASS_DECL_ACME exception 
{
public:


   ::e_status                 m_estatus;

   bool                       m_bDumpBackTrace;
   string                     m_strCallstack;
   bool                       m_bHandled;
   bool                       m_bContinue;
   string                     m_strMessage; // Message for the user
   string                     m_strDetails; // Details about exception (if available/applicable)
   //string                     m_strException;

   // A exception class is meant to be a small utility/tool class.
   // m_bLog -> too much managing (micro-managing and also big-managing)
   // from utility/tool small class of the Logging get_system()->
   // General-ever Log can be done by final handlers at Main Loop and crash handlers
   // Log can be supressed or translated at optional middle-stack handlers.
   // bool        m_bLog;
   string                     m_strLink;
   string                     m_strFile;
   int                        m_iLine;
   array < error_code >       m_errorcodea;
//   int                        m_iErrNo;
//#ifdef WINDOWS
  // HRESULT                    m_hresult;
   //::u32                      m_uLastError;
//#endif


   static bool                s_bEnableCallStackBackTrace;


   exception();
#ifdef ANDROID
   exception(const ::e_status & estatus, const char * pszMessage = nullptr, const char * pszDetails = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER);
#else
   exception(const ::e_status & estatus, const char * pszMessage = nullptr, const char * pszDetails = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr);
#endif
   virtual ~exception();


   static void enable_call_stack_back_trace(bool bEnable);


   virtual string get_message() const;
      
      
   inline ::e_status estatus() const { return m_estatus; }


};



#if defined(__APPLE__)


class ns_exception :
   public ::exception
{
public:

   int m_iCode;

   ns_exception();
   ~ns_exception();

};


#endif


#ifdef WINDOWS


class CLASS_DECL_ACME win32_exception :
   public ::exception
{
public:


   win32_exception(::u32 uLastError) :
      exception(error_win32)
   {

      m_uLastError = uLastError;

   }


};


#endif


class CLASS_DECL_ACME assert_exception :
   public ::exception
{
public:


   assert_exception(const char* pszFileName, int iLine) :
      ::exception(error_failed)
   {

      m_strMessage.format("Assert Exception at file \"%s\", line %d", pszFileName, iLine);

   }


};



class CLASS_DECL_ACME what_exclamation_exclamation :
   public ::exception
{
public:


   what_exclamation_exclamation(const char* pszMessage) :
      ::exception(error_what_exclamation_exclamation, pszMessage)
   {

   }


};


class CLASS_DECL_ACME error_number :
   public ::exception
{
public:
   
   
   int m_iErrNo;


#ifdef ANDROID
   error_number(::e_status estatus, int iError, const char * pszMessage = nullptr, const char * pszDetails = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER) :
      ::exception(estatus, pszMessage, pszDetails, iSkip),
#else
      error_number(::e_status estatus, int iError, const char * pszMessage = nullptr, const char * pszDetails = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr ) :
   ::exception(estatus, pszMessage, pszDetails, iSkip, caller_address),
#endif
   m_iErrNo(iError)
   {

   }
   
   ~error_number()
   {
      
   }

   
};



