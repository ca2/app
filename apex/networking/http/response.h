#pragma once


namespace http
{


   class CLASS_DECL_APEX response : 
      public http::transaction
   {
   public:


      memory_file_pointer           m_pmemfileBody;
      string                        m_strFile;


      response(const string & version = "HTTP/1.0");
      response(const response& src);
      ~response();

      response& operator=(const response& src);

      ::memory_file * file() { return m_pmemfileBody; }
      
      //void print(const ::string & str) { m_pmemfileBody->print(str); }
      //void println(const::string & str) { m_pmemfileBody->println(str); }
      //void printf(const char * psz, ...);

      void clear();
      

   }; // end of class


} // namespace http



