#pragma once


namespace sip
{


   class CLASS_DECL_APEX response :
      virtual public transaction
   {
   public:


      response(::object * pobject, const string & version = "HTTP/1.0");
      response(const response& src);
      ~response();

      response& operator=(const response& src);



      //void SetCookie(const string & value);
      //string Cookie(const string & name);
      //list<string> CookieNames() const;

      memory_file & file() { return m_memfileBody; }

      /** replace memfile with file on disk, opened for read. */
   //   void SetFile( const string & path );

      void clear();

   protected:

      //Utility::ncmap<string> m_cookie;
      memory_file m_memfileBody;


   }; // end of class


} // namespace http


