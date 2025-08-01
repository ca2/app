// From tracer.h by camilo on 2023-06-10 23:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/platform/tracer.h"
#include <stdarg.h>


class tracer * fallback_tracer();

trace_statement::trace_statement(class tracer * ptracer) :
   trace_statement_struct(ptracer)
{ 
   
   m_pprintingformat = ptracer;

   if(m_ptracer == nullptr)
   {

      m_ptracer = fallback_tracer();

   }

   if(m_pprintingformat == nullptr)
   {

      m_pprintingformat = fallback_tracer();

   }

}


trace_statement::~trace_statement()
{

   if (m_ptracer)
   {

      m_ptracer->flush(*this);

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



