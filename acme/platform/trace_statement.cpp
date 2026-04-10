// From tracer.h by camilo on 2023-06-10 23:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/platform/tracer.h"
#include <stdarg.h>


namespace platform
{


   ::platform::tracer * fallback_tracer();


} // namespace platform


trace_statement::trace_statement(::platform::tracer * ptracer) :
   trace_statement_struct(ptracer)
{

   __check_refdbg
   
   m_pprintingformat = ptracer;

   __check_refdbg

   if(m_ptracer == nullptr)
   {

      __check_refdbg

      m_ptracer = ::platform::fallback_tracer();

      __check_refdbg

   }

   if(m_pprintingformat == nullptr)
   {

      __check_refdbg

      m_pprintingformat = ::platform::fallback_tracer();

      __check_refdbg

   }

}


trace_statement::~trace_statement()
{

   __check_refdbg

   if (m_ptracer)
   {

      __check_refdbg

      m_ptracer->flush(*this);

      __check_refdbg

   }

}


void trace_statement::formatf_output_arguments(const_char_pointer pszFormat, va_list & arguments)
{

   //m_ptracer->format_output_arguments(scopedstr, arguments);

   string str;

   str.formatf_arguments(pszFormat, arguments);

   operator << (str);


}


//trace_statement & trace_statement::operator()(const_char_pointer pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   string str;
//
//   str.formatf_arguments(scopedstrFormat, arguments);
//
//   operator << (str);
//
//   va_end(arguments);
//
//   return *this;
//
//}


string trace_statement::prefix() const
{

   if (::is_set(m_ptracer))
   {

      return m_ptracer->trace_prefix();

   }

   ::string strTaskName;

   strTaskName = ::current_task_name();

   return strTaskName;

}

