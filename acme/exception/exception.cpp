// added error_code::get_string by camilo on 2022-09-29 22:10 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "exception.h"
//#include "callstack.h"
//#include "acme/prototype/string/as_string.h"
#include "acme/filesystem/file/exception.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/atom.h"
//#include "_api.h"
#include <stdio.h>

string get_status_message(const ::e_status & estatus);

bool ::exception::s_bEnableCallStackBackTrace = true;


exception::exception()
{


}


//#ifdef __ANDROID__
exception::exception(const ::e_status & estatus, const ::scoped_string& scopedstrMessage, const ::scoped_string& scopedstrDetails, int iSkip, void * caller_address) :
exception(estatus, {::error_code(e_error_code_type_unknown, 0)}, scopedstrMessage, scopedstrDetails, iSkip, caller_address)
{
   
   
}


//#else
exception::exception(const ::e_status & estatus, const ::array_non_particle < error_code > & errorcodea, const ::scoped_string& scopedstrMessage, const ::scoped_string& scopedstrDetails, int iSkip, void * caller_address):
m_errorcodea(errorcodea)
//#endif
{

#if !defined(__SANITIZE_ADDRESS__)

   if (s_bEnableCallStackBackTrace && iSkip != SKIP_CALLSTACK)
   {

      if (iSkip == CALLSTACK_DEFAULT_SKIP_TRIGGER)
      {

         iSkip = CALLSTACK_DEFAULT_SKIP;

      }

//#ifdef __ANDROID__
//      
//      m_strCallstack = system()->node()->unwind_callstack(callstack_default_format(), iSkip);
//
//#else

      auto ptask = ::get_task();

      if(ptask)
      {

         auto psystem = ptask->system();

         if(psystem)
         {

            auto pnode = psystem->node();

            if(pnode)
            {

               m_strCallStackTrace = pnode->get_call_stack_trace(call_stack_default_format(), iSkip, caller_address);

               //printf("%s", m_strCallStackTrace.c_str());

            }

         }

      }
      
//#endif

   }

#endif

   m_bDumpCallStackTrace = true;

   m_estatus.defer_failed(error_exception);

   m_bHandled = false;

   m_bContinue = true;

   m_strMessage = scopedstrMessage;

   m_strDetails = scopedstrDetails;

}



exception::exception(const ::exception& exception) :
m_estatus(exception.m_estatus),
m_bDumpCallStackTrace(exception.m_bDumpCallStackTrace),
m_strCallStackTrace(exception.m_strCallStackTrace),
m_bHandled(exception.m_bHandled),
m_bContinue(exception.m_bContinue),
m_econsequenceUserDefault(exception.m_econsequenceUserDefault),
m_strTitle(exception.m_strTitle),
m_strMessage(exception.m_strMessage),
m_strDetails(exception.m_strDetails),
m_strLink(exception.m_strLink),
m_strFile(exception.m_strFile),
m_iLine(exception.m_iLine),
m_errorcodea(exception.m_errorcodea)
{

}


exception::~exception()
{

}


::pointer < ::subparticle > exception::clone()
{

   auto pexception = __allocate::exception(*this);

   return pexception;

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


string exception::get_title() const
{

   return "Exception";

}


string exception::get_consolidated_details(::particle * pparticle) const
{
 
   string strConsolidatedDetails;
   
   strConsolidatedDetails += m_strDetails;
   
   strConsolidatedDetails += "\n";

   for(auto & errorcode : m_errorcodea)
   {

      strConsolidatedDetails.append_formatf("errorcode: %lld %s", errorcode.m_iOsError, pparticle->node()->get_error_code_message(errorcode).c_str());

      strConsolidatedDetails += "\n";

   }

   strConsolidatedDetails += "\n";

   strConsolidatedDetails += m_strCallStackTrace;

   return strConsolidatedDetails;

}



//
//namespace exception
//{


   // CLASS_DECL_ACME void throw_interface_only(const ::scoped_string & scopedstrMessage)
   // {

   //    throw ::exception(error_interface_only, pszMessage);

   // }


   // CLASS_DECL_ACME void throw_not_implemented(const ::scoped_string & scopedstrMessage)
   // {

   //    throw ::exception(error_not_implemented, pszMessage);

   // }


   // string get_all_messages(const array < exception > & a)
   // {

   //    ::collection::count c = a.get_count();

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

   //       ::collection::index i = 0;

   //       a.predicate_each(

   //       [&](auto & e)
   //       {

   //          str += as_string(++i);

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



//   int exception::report_error(unsigned int nType /* = e_message_box_ok */, const ::scoped_string & scopedstrMessageId /* = nullptr */)
//   {
//      string   strErrorMessage;
//      int     nDisposition;
////      unsigned int    nHelpContext;
//
//      // nHelpContext should come with the message "<helpcontext id=\"123\" />"
//      strErrorMessage = get_message();
//      //if (get_message(strErrorMessage, &nHelpContext))
//      //   nDisposition = message_box(nullptr, strErrorMessage, nType);
//      //else
//      //{
//      //   if (scopedstrMessageId == 0)
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
//#ifdef __ANDROID__
//
//         string_array stra;
//
//         stra.add_lines(m_pcallstack->m_pszCallStack);
//
//         for (auto& str : stra)
//         {
//
//            information(str);
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


//CLASS_DECL_ACME ::pointer<::exception>__trace_context_move_throw_exception(::matter * trace_context, ::exception * pexceptionNew)
//{
//
//   __trace_logger_level(trace_context, e_trace_level_error);
//
//   return ::__move_transfer(pexceptionNew);
//
//}


CLASS_DECL_ACME const_char_pointer status_short_description(const ::e_status & estatus)
{

   auto psz = ::file::status_short_description(estatus);

   if (::is_set(psz))
   {

      return psz;

   }

   switch (estatus.as_estatus())
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

   return "(missing e_status text message)";

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


//string estatus_to_string(::e_status estatus)
//{
//
//   if (::succeeded(estatus))
//   {
//      
//      return "success";
//
//   }
//   else
//   {
//
//      return "failed";
//
//   }
//
//}

//
//CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails, int iSkip, void * caller_address)
//{
//
//   throw ::exception(estatus, pszMessage, pszDetails, iSkip, caller_address);
//
//}


//CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::scoped_string & scopedstrMoreDetails)
//{
//
//
//   string strMessage;
//
//   strMessage += "Failed to initialize application\n";
//   strMessage += "\n";
//   strMessage += exception.m_strMessage + "\n";
//   strMessage += "(" + as_string(exception.m_estatus) + ")";
//
//   string strTitle;
//
//   strTitle = "Exception during initialization";
//
//   string strDetails;
//
//   auto pacmenode = pparticle->node();
//
//   auto processid = pacmenode->current_process_identifier();
//
//   auto strProcessId = ::as_string(processid);
//
//   strDetails += strMessage + "\n";
//   strDetails += exception.m_strDetails + "\n\n";
//   strDetails += "\n";
//   strDetails += "PID: " + strProcessId + ::string("\n");
//   //strDetails += "Working Directory: " + string(GetCurrentDirectory()) + "\n\n";
//   
//   if (strMoreDetails.has_character())
//   {
//
//      strDetails += strMoreDetails + "\n";
//
//   }
//
//   if (exception.m_strCallStackTrace.has_character())
//   {
//
//      strDetails += "\n\n" + string(exception.m_strCallStackTrace);
//
//   }
//
//   auto pmessagebox = __initialize_new ::message_box(pparticle, strMessage, strTitle, e_message_box_ok | e_message_box_icon_exclamation, strDetails);

//pmessagebox->sync();
//
//}


void throw_exception(enum_status estatus)
{

   throw ::exception(estatus);

}


CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails, int iSkip)
{

   throw exception(estatus, scopedstrMessage, scopedstrDetails, iSkip);

}


CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage)
{

   throw_exception(estatus, scopedstrMessage, nullptr);

}


CLASS_DECL_ACME void throw_exception(const ::e_status & estatus)
{

   throw_exception(estatus, nullptr);

}


CLASS_DECL_ACME void throw_todo()
{

   throw ::exception(todo);

}



CLASS_DECL_ACME void copy(::string& str, const ::exception& exception)
{

   str = exception.m_strMessage;

}





CLASS_DECL_ACME write_text_stream & operator <<(write_text_stream & stream, const ::exception & exception)
{

   stream << exception.get_message();

   return stream;

}



