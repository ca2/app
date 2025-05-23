// Created by camilo on 2023-06-29 09:20 <3ThomasBorregaardSorensen!!
#pragma once


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
   //string                   m_strException;

   // A exception class is meant to be a small utility/tool class.
   // m_bLog -> too much managing (micro-managing and also big-managing)
   // from utility/tool small class of the Logging system()->
   // General-ever Log can be done by final handlers at Main Loop and crash handlers
   // Log can be supressed or translated at optional middle-stack handlers.
   // bool                    m_bLog;
   string                     m_strLink;
   string                     m_strFile;
   int                        m_iLine;
   array < error_code >       m_errorcodea;
   static bool                s_bEnableCallStackBackTrace;


   exception();
   //#ifdef __ANDROID__
   //   exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrDetails = nullptr, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER);
   //#else
   exception(const ::e_status & estatus, const char * pszMessage = nullptr, const char * pszDetails = nullptr, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr);
   //#endif
   exception(const ::e_status & estatus, const ::array < error_code > & errorcodea, const char * pszMessage = nullptr, const char * pszDetails = nullptr, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr);
   virtual ~exception();


   static void enable_call_stack_back_trace(bool bEnable);


   virtual string get_message() const;

   virtual string get_title() const;

   virtual string get_consolidated_details() const;


   inline ::e_status estatus() const { return m_estatus; }


};


