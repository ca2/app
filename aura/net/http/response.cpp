#include "framework.h" 
#include "aura/net/sockets/_.h"


namespace http
{


   response::response(const string & version) :
      m_pmemfileBody(e_create_new)
   {

      UNREFERENCED_PARAMETER(version);

   }


   response::response(const response& src) :
      transaction(src),
      m_pmemfileBody(src.m_pmemfileBody)
   {

   }


   response::~response()
   {

   }


   response& response::operator=(const response& src)
   {

      transaction::operator=(src);

      m_pmemfileBody->memory() = src.m_pmemfileBody->memory();

      return *this;
      
   }


   void response::printf(const char * pszFormat, ...)
   {
      
      va_list args;
      
      va_start(args, pszFormat);
      
      string str;
      
      str.FormatV(pszFormat, args);
      
      va_end(args);
        
   }


   void response::clear()
   {

      transaction::clear();

      m_pmemfileBody->set_size(0);
   
   }


} // namespace http



