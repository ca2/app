#pragma once


namespace sip
{

   class CLASS_DECL_AURA request : 
      virtual public transaction
   {
   public:
   
      string m_null;
      memory_file m_file;
      http::form m_form;


      request(::context_object * pcontextobject);
      request(const request& src);
      ~request();


      /** Cookies */
      void add_cookie(const char * pszSetCookie);

      /** open file for body data */
      void InitBody( size_t sz );

      /** write body data */
      void write( const char *buf, size_t sz );

      /** No more writing */
      void CloseBody();

      void ParseBody();

      http::form & form();

      memory_file & file() { return m_file; }

      virtual void clear();

      

   }; // end of class

   
} // namespace http



