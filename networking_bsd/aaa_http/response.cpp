#include "framework.h" 
//#include "apex/networking/sockets/_.h"


namespace http
{


   response::response(const string & version) 
   {

      __UNREFERENCED_PARAMETER(version);

      ødefer_construct_new(m_pmemfileBody);

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

      ødefer_construct_new(m_pmemfileBody);

      m_pmemfileBody->memory() = src.m_pmemfileBody->memory();

      return *this;
      
   }


   void response::printf(const ::scoped_string & scopedstrFormat, ...)
   {
      
      va_list args;
      
      va_start(args, pszFormat);
      
      string str;
      
      str.formatf_arguments(scopedstrFormat, args);
      
      va_end(args);
        
   }


   void response::clear()
   {

      transaction::clear();

      ødefer_construct_new(m_pmemfileBody);

      m_pmemfileBody->set_size(0);
   
   }


} // namespace http



