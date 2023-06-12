// From tracer.h by camilo on 2023-06-10 23:27 <3ThomasBorregaardSorensen!!
#include "framework.h"


trace_statement::trace_statement(class tracer & tracer) :
   trace_statement_struct(&tracer) 
{ 
   
   m_pprintingformat = &tracer; 

}


trace_statement::~trace_statement()
{

   if (m_ptracer)
   {

      m_ptracer->flush(*this);

   }

}


void trace_statement::format_output_arguments(const ::ansi_character * psz, va_list & arguments)
{

   //m_ptracer->format_output_arguments(psz, arguments);

   string str;

   str.format_arguments(psz, arguments);

   operator << (str);


}



