#include "framework.h"
#include "html_file.h"
#include "acme/primitive/text/context.h"
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


void html_file::print(const ::string& str)
{

   raw_print(str);

}


void html_file::raw_print(const ::string& str)
{

   print(str);

}


#ifndef VARIADIC_TEMPLATE_FORMAT


void html_file::printf(string str, ...)
{

   __UNREFERENCED_PARAMETER(str);

   throw ::interface_only();

}


void html_file::printstr(string str, ...)
{

   __UNREFERENCED_PARAMETER(str);

   throw ::interface_only();

}


#else


void html_file::trace(void*, const char* psz)
{

   print(psz);

}


#endif


void html_file::dprint(const char* pcsz)
{

   __UNREFERENCED_PARAMETER(pcsz);

   throw ::interface_only();

}


///} // namespace html



