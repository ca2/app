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


//#if defined(APPLE_IOS)
//
//bool ::exception::s_bEnableCallStackBackTrace = false;
//
//#elif defined(ANDROID)
//
//bool ::exception::s_bEnableCallStackBackTrace = true;
//
//#elif defined(MACOS)
//
//bool ::exception::s_bEnableCallStackBackTrace = false;
//
//#else

bool ::exception::s_bEnableCallStackBackTrace = true;

//#endif

exception::exception()
{


}


exception::exception(const ::e_status & estatus, const char * pszMessage, const char * pszDetails, i32 iSkip, void * caller_address)
{

#if !defined(__SANITIZE_ADDRESS__)

   if (s_bEnableCallStackBackTrace && iSkip != SKIP_CALLSTACK)
   {

      if (iSkip == CALLSTACK_DEFAULT_SKIP_TRIGGER)
      {

         iSkip = CALLSTACK_DEFAULT_SKIP;

      }

      m_strCallstack = get_callstack(callstack_default_format(), iSkip, caller_address);

   }

#endif

   m_bDumpBackTrace = true;

   defer_failed(m_estatus, error_exception);

   m_estatus = estatus;

   m_bHandled = false;

   m_bContinue = true;

   m_strMessage = pszMessage;

   string strDetails;

   strDetails = pszDetails;

   if (strDetails.has_char())
   {

      strDetails += "\n\n";

   }

   strDetails += m_strCallstack;

   m_strDetails = strDetails;

}


exception::~exception()
{

}


void exception::enable_call_stack_back_trace(bool bEnable)
{

   s_bEnableCallStackBackTrace = bEnable;

}


string exception::get_message() const
{

   string strMessage;

   strMessage += get_status_message(m_estatus) + "\n";

   strMessage += m_strMessage;

   return strMessage;

}


errno_t c_runtime_error_check(errno_t error)
{

   switch(error)
   {
   case ENOMEM:
      throw ::exception(error_no_memory, nullptr, nullptr, CALLSTACK_DEFAULT_SKIP + 1);
      break;
   case EINVAL:
   case ERANGE:
      throw ::exception(error_bad_argument, nullptr, nullptr, CALLSTACK_DEFAULT_SKIP + 1);
      break;
#if defined(WINDOWS)
   case STRUNCATE:
#endif
   case 0:
      break;
   default:
      throw ::exception(error_bad_argument, nullptr, nullptr, CALLSTACK_DEFAULT_SKIP + 1);
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


//
//namespace exception
//{


   // CLASS_DECL_ACME void throw_interface_only(const char * pszMessage)
   // {

   //    throw ::exception(error_interface_only, pszMessage);

   // }


   // CLASS_DECL_ACME void throw_not_implemented(const char * pszMessage)
   // {

   //    throw ::exception(error_not_implemented, pszMessage);

   // }


   // string get_all_messages(const array < exception > & a)
   // {

   //    ::count c = a.get_count();

   //    if (c <= 0)
   //    {

   //       return "";

   //    }
   //    else if (c == 1)
   //    {

   //       return a[0].m_strMessage;

   //    }
   //    else
   //    {

   //       string str;

   //       index i = 0;

   //       a.predicate_each(

   //       [&](auto & e)
   //       {

   //          str += __string(++i);

   //          str += ". ";

   //          str += e.m_strMessage;

   //          str += ";";

   //          if (i < c)
   //          {

   //             str += " ";

   //          }

   //       }

   //       );

   //       return str;

   //    }

   // }


   //void exception_pointer::rethrow_exit()
   //{

   //   if (is_exit())
   //   {

   //      throw *this;

   //   }

   //}



//   i32 exception::report_error(::u32 nType /* = e_message_box_ok */, const char * pszMessageId /* = nullptr */)
//   {
//      string   strErrorMessage;
//      i32     nDisposition;
////      ::u32    nHelpContext;
//
//      // nHelpContext should come with the message "<helpcontext id=\"123\" />"
//      strErrorMessage = get_message();
//      //if (get_message(strErrorMessage, &nHelpContext))
//      //   nDisposition = message_box(nullptr, strErrorMessage, nType);
//      //else
//      //{
//      //   if (pszMessageId == 0)
//      //      //pszMessageId = __IDP_NO_ERROR_AVAILABLE;
//      //      pszMessageId = "Error message not available";
//      nDisposition = message_box(nullptr, pszMessageId, nType);
//      //}
//      return nDisposition;
//   }
//

   
   //void exception::defer_dump_back_trace()
   //{

   //   if (m_bDumpBackTrace)
   //   {

   //      dump_back_trace();

   //   }

   //}


//   void exception::dump_back_trace()
//   {
//
//      if (::is_set(m_pcallstack))
//      {
//
//#ifdef ANDROID
//
//         string_array stra;
//
//         stra.add_lines(m_pcallstack->m_pszCallStack);
//
//         for (auto& str : stra)
//         {
//
//            output_debug_string(str);
//
//         }
//
//#else
//
//         debug_print(m_pcallstack->m_pszCallStack);
//
//#endif
//
//      }
//
//   }
// 
// 
// 
//
//
//} // namespace exception



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


//CLASS_DECL_ACME __pointer(::exception) __trace_context_move_throw_exception(::matter * trace_context, ::exception * pexceptionNew)
//{
//
//   __trace_logger_level(trace_context, e_trace_level_error);
//
//   return ::__move_transfer(pexceptionNew);
//
//}


const char* status_short_description(const ::e_status & estatus)
{

   auto psz = ::file::status_short_description(estatus);

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

   case error_bad_file_format:

      return "Attempted to open file with an unsupported waveform-audio_mmsystem format.";

   case error_bad_data_format:

      return "Attempted to access data with an unsupported waveform-audio_mmsystem format.";

   default:

      break;

   }

   return "(Missing Error Text)";

}


// thread_local bool t_bAvoidBadStatusException = false;


// CLASS_DECL_ACME bool avoid_bad_status_exception()
// {

//    return t_bAvoidBadStatusException;

// }


// CLASS_DECL_ACME void set_avoid_bad_status_exception(bool bSet)
// {

//    t_bAvoidBadStatusException = bSet;

// }


string estatus_to_string(::e_status estatus)
{

   if (::succeeded(estatus))
   {
      
      return "success";

   }
   else
   {

      return "failed";

   }

}

//
//CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const char * pszMessage, const char * pszDetails, i32 iSkip, void * caller_address)
//{
//
//   throw ::exception(estatus, pszMessage, pszDetails, iSkip, caller_address);
//
//}


CLASS_DECL_ACME void exception_message_box(::object * pobject, ::exception & exception, const ::string & strMoreDetails)
{


   string strMessage;

   strMessage += "Failed to initialize application\n";
   strMessage += "\n";
   strMessage += exception.m_strMessage + "\n";
   strMessage += "(" + __string(exception.m_estatus) + ")";

   string strTitle;

   strTitle = "Exception during initialization";

   string strDetails;

   strDetails += strMessage + "\n";
   strDetails += exception.m_strDetails + "\n\n";
   strDetails += "\n";
   strDetails += "PID: " + __string(::get_current_process_id()) + "\n";
   //strDetails += "Working Directory: " + string(GetCurrentDirectory()) + "\n\n";
   
   if (strMoreDetails.has_char())
   {

      strDetails += strMoreDetails + "\n";

   }

   if (exception.m_strCallstack)
   {

      strDetails += "\n\n" + string(exception.m_strCallstack);

   }

   message_box_synchronous(pobject, strMessage, strTitle, e_message_box_ok | e_message_box_icon_exclamation, strDetails);

}



