#include "framework.h"
#include "html_file.h"
#include "acme/prototype/text/context.h"
#include "acme/exception/interface_only.h"



html_file::html_file()
{

}


html_file::~html_file()
{

}


const ::text::context* html_file::textcontext()
{

   return m_ptextcontext;

}


void html_file::print(const ::scoped_string & scopedstr)
{

   raw_print(scopedstr);

}


void html_file::raw_print(const ::scoped_string & scopedstr)
{

   print(scopedstr);

}


#ifndef VARIADIC_TEMPLATE_FORMAT


void html_file::printf(const_char_pointer pszFormat, ...)
{

   __UNREFERENCED_PARAMETER(pszFormat);

   throw ::interface_only();

}


void html_file::printstr(const_char_pointer pszFormat, ...)
{

   __UNREFERENCED_PARAMETER(pszFormat);

   throw ::interface_only();

}


#else


void html_file::trace(void*, const ::scoped_string & scopedstr)
{

   print(scopedstr);

}


#endif


void html_file::dprint(const ::scoped_string & scopedstr)
{

   __UNREFERENCED_PARAMETER(scopedstr);

   throw ::interface_only();

}


///} // namespace html



