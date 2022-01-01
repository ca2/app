#include "framework.h"
#include "html_file.h"
#include "acme/primitive/text/context.h"


namespace html
{


   file::file()
   {
      
   }


   file::~file()
   {

   }


   const ::text::context * file::textcontext()
   {
      
      return m_ptextcontext;

   }


   void file::print(const ::string & str)
   {

      raw_print(str);

   }


   void file::raw_print(const ::string & str)
   {

      print(str);

   }


#ifndef VARIADIC_TEMPLATE_FORMAT


   void file::printf(string str,...)
   {

      __UNREFERENCED_PARAMETER(str);

      throw ::interface_only_exception();

   }


   void file::printstr(string str,...)
   {

      __UNREFERENCED_PARAMETER(str);

      throw ::interface_only_exception();

   }


#else


   void file::trace(void *,const char * psz)
   {

      print(psz);

   }


#endif


   void file::dprint(const char * pcsz)
   {

      __UNREFERENCED_PARAMETER(pcsz);

      throw ::interface_only_exception();

   }


} // namespace html



