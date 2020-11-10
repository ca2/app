#pragma once


namespace exception
{


   class CLASS_DECL_ACME exception :
      public matter
   {
   public:


      static bool    s_bDoStackTrace;


      bool              m_bDumpBackTrace;
      __pointer(callstack)     m_pcallstack;
      bool              m_bHandled;
      bool              m_bContinue;
      const char *      m_pszMessage;
      const char *      m_pszException;

      // A exception class is meant to be a small utility/tool class.
      // m_bLog -> too much managing (micro-managing and also big-managing)
      // from utility/tool small class of the Logging System.
      // General-ever Log can be done by final handlers at Main Loop and crash handlers
      // Log can be supressed or translated at optional middle-stack handlers.
      // bool        m_bLog;

      const char *         m_pszFile;
      int                  m_iLine;
      ::estatus                 m_estatus;


      exception(const ::estatus & estatus = error_exception, i32 iSkip = callstack_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr) :
         exception(nullptr, estatus, iSkip, caller_address)
      {

      }

      exception(const char * pszMessage, const ::estatus & estatus = error_exception, i32 iSkip = callstack_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr);
      virtual ~exception();


      const char * cat_message(const char * pszMessage);
      const char * cat_exception(const char * pszException);
      const char * set_file(const char * pszFile);

      //virtual const char * what () const noexcept;
      static void exception_enable_stack_trace(bool bEnable);


      //virtual bool get_message(string & str, P::u32 pnHelpContext = nullptr);
      //virtual string get_message(P::u32 pnHelpContext = nullptr);

      virtual string get_message() const;


      void defer_dump_back_trace();
      void dump_back_trace();

   };


   //class CLASS_DECL_ACME array:
   //   virtual public __pointer_array(exception)
   //{
   //public:


   //   array() {}
   //   array(::exception::exception * pexception) : __pointer_array(exception)({ pexception }) {}
   //   array(const std::initializer_list < ::exception::exception * > & list) : __pointer_array(exception)(list) {}


      string get_all_messages(const __pointer_array(exception) & a);


   //};


   using exception_pointer = __pointer(exception);


} // namespace exception


#if defined(__APPLE__)


class ns_exception :
   public ::exception::exception
{
public:

   int m_iCode;

   ns_exception();
   ~ns_exception();

};

#endif



#include "result.h"




template < typename EXCEPTION >
inline __pointer(EXCEPTION) __move_throw_exception(EXCEPTION * pexceptionNew)
{

   ERR(pexceptionNew->get_message());

   return ::__move_transfer(pexceptionNew);

}