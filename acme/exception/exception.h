#pragma once


namespace exception
{


   class CLASS_DECL_ACME exception 
   {
   public:


      ::e_status              m_estatus;

      //enum_exception        m_eexception;
      bool                    m_bDumpBackTrace;
      __pointer(callstack)    m_pcallstack;
      bool                    m_bHandled;
      bool                    m_bContinue;
      string                  m_strMessage;
      string                  m_strException;

      // A exception class is meant to be a small utility/tool class.
      // m_bLog -> too much managing (micro-managing and also big-managing)
      // from utility/tool small class of the Logging get_system()->
      // General-ever Log can be done by final handlers at Main Loop and crash handlers
      // Log can be supressed or translated at optional middle-stack handlers.
      // bool        m_bLog;
      string                  m_strLink;
      string                  m_strFile;
      int                     m_iLine;
      int                     m_iErrNo;
#ifdef WINDOWS
      HRESULT                 m_hresult;
      ::u32                   m_uLastError;
#endif


      static bool             s_bDoStackTrace;


      exception();
      exception(const ::e_status& estatus, const char * pszMessage = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr);
      virtual ~exception();



      //virtual const char * what () const noexcept;
      static void exception_enable_stack_trace(bool bEnable);


      //virtual bool get_message(string & str, P::u32 pnHelpContext = nullptr);
      //virtual string get_message(P::u32 pnHelpContext = nullptr);

      virtual string get_message() const;
      
      
      inline ::e_status estatus() const { return m_estatus; }


      void defer_dump_back_trace();
      void dump_back_trace();

   };


   //class CLASS_DECL_ACME array:
   //   virtual public __pointer_array(exception)
   //{
   //public:


   //   array() {}
   //   array(const ::exception::exception & e) : __pointer_array(exception)({ pexception }) {}
   //   array(const std::initializer_list < ::exception::exception * > & list) : __pointer_array(exception)(list) {}


      string get_all_messages(const __pointer_array(exception) & a);


   //};


   //using exception_pointer = __pointer(exception);


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



//#include "result.h"




template < typename EXCEPTION >
inline __pointer(EXCEPTION) __move_throw_exception(EXCEPTION * pexceptionNew)
{

   ERR(pexceptionNew->get_message());

   return ::__move_transfer(pexceptionNew);

}


//class CLASS_DECL_ACME status_exception :
//   public ::exception::exception
//{
//public:
//
//
//   status_exception(const ::e_status & estatus, const char * pszStatus = nullptr) :
//      ::exception::exception(pszStatus, estatus)
//   {
//
//   }
//   virtual ~status_exception(){}
//
//
//};
//



#ifdef WINDOWS


class CLASS_DECL_ACME win32_exception :
   public ::exception::exception
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
   public ::exception::exception
{
public:


   assert_exception(const char* pszFileName, int iLine) :
      ::exception::exception(error_failed)
   {

      m_strMessage.Format("Assert Exception at file \"%s\", line %d", pszFileName, iLine);

   }


};



class CLASS_DECL_ACME what_exclamation_exclamation :
   public ::exception::exception
{
public:


   what_exclamation_exclamation(const char* pszMessage) :
      ::exception::exception(error_what_exclamation_exclamation, pszMessage)
   {

   }


};
//
//#ifdef WINDOWS
//class CLASS_DECL_ACME hresult_exception :
//   public ::exception::exception
//{
//public:
//
//
//   hresult_exception(HRESULT hresult, const char* pszMessage = nullptr)
//   {
//
//      if (hresult == S_OK)
//      {
//
//         m_estatus = success;
//
//      } 
//      else if (FAILED(hresult))
//      {
//
//         m_estatus = error_hresult;
//
//      }
//      else if(SUCCEEDED(hresult))
//      {
//
//         m_estatus = success_hresult;
//
//      }
//
//      m_hresult = hresult;
//
//      m_strMessage = pszMessage;
//
//   }
//
//
//};
//
//#endif


class CLASS_DECL_ACME error_number :
   public exception::exception
{
public:
   
   
   int m_iErrNo;

   error_number(::e_status estatus, int iError, const char * pszMessage = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr ) :
   ::exception::exception(
                          estatus, pszMessage, iSkip, caller_address),
   m_iErrNo(iError)
   {
   }
   
   ~error_number()
   {
      
   }
   
};
