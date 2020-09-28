#include "framework.h"

#include <stdio.h>

const char * strcatdup(const char * psz1, const char * psz2)
{
   
   if(::is_null(psz1))
   {
      
      if(::is_null(psz2))
      {
         
         return nullptr;
         
      }
      else
      {
         
         return strdup(psz2);
      
      }
      
   }
   else if(::is_null(psz2))
   {
      
      return strdup(psz1);
      
   }
   else
   {

      char * pszNew = (char *) malloc(strlen(psz1) + strlen(psz2) + 1);

      strcpy(pszNew, psz1);
   
      strcat(pszNew, psz2);
   
      return pszNew;

   }
   
}




#if defined(APPLE_IOS)

bool exception::exception::s_bDoStackTrace = false;

#elif defined(ANDROID)

bool exception::exception::s_bDoStackTrace = true;

#elif defined(MACOS)

bool exception::exception::s_bDoStackTrace = false;

#else

bool exception::exception::s_bDoStackTrace = true;

#endif

namespace exception
{


   exception::exception(const char * pszMessage, const ::estatus & estatus, i32 iSkip, void * caller_address)
   {

#if !defined(__SANITIZE_ADDRESS__)

      if (s_bDoStackTrace && iSkip != SKIP_callstack)
      {

         if (iSkip == callstack_DEFAULT_SKIP_TRIGGER)
         {

            iSkip = callstack_DEFAULT_SKIP;

         }

         m_pcallstack = new callstack(callstack::default_format(), iSkip, caller_address);

      }

#endif

      //debug_print("log:exception");

      //if (pszMessage == nullptr)
      //{

      //   debug_print(":(nullptr)");

      //}
      //else
      //{

      //   debug_print(":(\"%s\")", pszMessage);

      //}


      m_bDumpBackTrace = true;

      defer_failed(m_estatus, error_exception);

      m_estatus = estatus;

      m_bHandled = false;

      m_bContinue = true;
      
      if(::is_set(pszMessage))
      {

         m_pszMessage = strdup(pszMessage);
         
      }
      else
      {
         
         m_pszMessage = nullptr;
         
      }

      m_pszException = nullptr;

      m_pszFile = nullptr;


   }


   exception::~exception()
   {

      if (m_pszException != nullptr)
      {

         free((void *)m_pszException);

      }

      if (m_pszMessage != nullptr)
      {

         free((void *)m_pszMessage);

      }

      if (m_pszFile != nullptr)
      {

         free((void *)m_pszFile);

      }

   }


   const char * exception::cat_message(const char * pszMessage)
   {
      
      auto pszNew = strcatdup(m_pszMessage, pszMessage);
      
      free((void *) m_pszMessage);

      m_pszMessage = pszNew;

      return m_pszMessage;

   }

   const char * exception::set_file(const char * pszFile)
   {

      if (m_pszFile != nullptr)
      {

         free((void *) m_pszFile);

      }
      
      if(pszFile == nullptr)
      {
         
         m_pszFile = nullptr;
         
      }
      else
      {

         m_pszFile = strdup(pszFile);
         
      }

      return m_pszFile;

   }

   const char * exception::cat_exception(const char * pszException)
   {

      auto pszNew = strcatdup(m_pszException, pszException);
      
      free((void *) m_pszException);

      m_pszException = pszNew;

      return m_pszException;

   }


   void exception::exception_enable_stack_trace(bool bEnable)
   {

      s_bDoStackTrace = bEnable;

   }



   string exception::get_message() const
   {

      string strMessage;

      strMessage = string("exception: ") + typeid(*this).name();

      if(::is_set(m_pszMessage))
      {

         strMessage += ", ";

         strMessage += m_pszMessage;

      }

      return strMessage;

   }


} // namespace exception


#ifdef APPLE_IOS



#else


// thread_object < string > t_strNote;


//string __get_thread_note()
//{
//   
//   return thread_value("strNote");
//
//}
//
//
//void __set_thread_note(const char * pszNote)
//{
//   
//   thread_value("strNote") = pszNote;
//
//}


#endif






errno_t c_runtime_error_check(errno_t error)
{
   switch(error)
   {
   case ENOMEM:
      __throw(memory_exception());
      break;
   case EINVAL:
   case ERANGE:
      __throw(invalid_argument_exception());
      break;
#if defined(WINDOWS)
   case STRUNCATE:
#endif
   case 0:
      break;
   default:
      __throw(invalid_argument_exception());
      break;
   }
   return error;
}

void __cdecl __clearerr_s(FILE *stream)
{
#ifdef WINDOWS
   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
#else
   clearerr(stream);
   C_RUNTIME_ERROR_CHECK(errno);
#endif
}


namespace exception
{


   CLASS_DECL_ACME void throw_interface_only(const char * pszMessage)
   {

      __throw(interface_only_exception(pszMessage));

   }


   CLASS_DECL_ACME void throw_not_implemented(const char * pszMessage)
   {

      __throw(not_implemented(pszMessage));

   }


   string get_all_messages(const __pointer_array(exception)& a)
   {

      ::count c = a.get_count();

      if (c <= 0)
      {

         return "";

      }
      else if (c == 1)
      {

         return a[0]->m_pszMessage;

      }
      else
      {

         string str;

         index i = 0;

         a.pred_each(

         [&](auto & pe)
         {

            str += __str(++i);

            str += ". ";

            str += pe->m_pszMessage;

            str += ";";

            if (i < c)
            {

               str += " ";

            }

         }

         );

         return str;

      }

   }


   //void exception_pointer::rethrow_exit()
   //{

   //   if (is_exit())
   //   {

   //      throw *this;

   //   }

   //}



//   i32 exception::report_error(UINT nType /* = MB_OK */, const char * pszMessageId /* = nullptr */)
//   {
//      string   strErrorMessage;
//      i32     nDisposition;
////      UINT    nHelpContext;
//
//      // nHelpContext should come with the message "<helpcontext id=\"123\" />"
//      strErrorMessage = get_message();
//      //if (get_message(strErrorMessage, &nHelpContext))
//      //   nDisposition = Application.message_box(nullptr, strErrorMessage, nType);
//      //else
//      //{
//      //   if (pszMessageId == 0)
//      //      //pszMessageId = __IDP_NO_ERROR_AVAILABLE;
//      //      pszMessageId = "Error message not available";
//      nDisposition = Application.message_box(nullptr, pszMessageId, nType);
//      //}
//      return nDisposition;
//   }
//

   void exception::defer_dump_back_trace()
   {

      if (m_bDumpBackTrace)
      {

         dump_back_trace();

      }

   }


   void exception::dump_back_trace()
   {

      if (m_pcallstack.is_set())
      {

#ifdef ANDROID

         string_array stra;

         stra.add_lines(m_pcallstack->m_pszCallStack);

         for (auto& str : stra)
         {

            output_debug_string(str);

         }

#else

         debug_print(m_pcallstack->m_pszCallStack);

#endif

      }

   }


} // namespace exception

//template < typename T >
//void __rethrow(T * pexception)
//{
//
////   throw ::esp(pexception);
//
//   throw pexception;
//
//}
//


namespace status
{


   i32 result::s_iSkipCallStack = SKIP_callstack;


   void result::set_skip_callstack(i32 iSkip)
   {

      s_iSkipCallStack = iSkip;

   }


} // namespace status





//CLASS_DECL_ACME __pointer(::exception::exception) __trace_context_move_throw_exception(::elemental * trace_context, ::exception::exception * pexceptionNew)
//{
//
//   __trace_logger_level(trace_context, trace_level_error);
//
//   return ::__move_transfer(pexceptionNew);
//
//}






const char* status_message(const ::estatus& estatus)
{

   auto psz = ::file::status_message(estatus);

   if (::is_set(psz))
   {

      return psz;

   }

   switch (estatus.m_estatus)
   {
   case error_already_allocated:

      return "Specified resource is already allocated.";

   case error_bad_device_id:

      return "Specified device identifier is out of range.";

   case error_bad_format:

      return "Attempted to open with an unsupported waveform-audio_mmsystem format.";

   default:

      break;

   }

   return "(Missing Error Text)";

}


thread_local bool t_bAvoidBadStatusException = false;


CLASS_DECL_ACME bool avoid_bad_status_exception()
{

   return t_bAvoidBadStatusException;

}


CLASS_DECL_ACME void set_avoid_bad_status_exception(bool bSet)
{

   t_bAvoidBadStatusException = bSet;

}



