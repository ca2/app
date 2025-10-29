#include "framework.h"
#include "html_file.h"
#include "acme/prototype/text/context.h"
#include "acme/exception/interface_only.h"



//html_file::html_file()
//{
//
//}


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


void html_file::dprint(const ::scoped_string & scopedstr)
{

   __UNREFERENCED_PARAMETER(scopedstr);

   throw ::interface_only();

}




