#pragma once


namespace http
{


   /** Parse/store a http query_string/form-data body.
      \ingroup webserver */
   class CLASS_DECL_APEX form :
      virtual public ::object
   {
   public:


      form();
      virtual ~form();

      /**
       * Default constructor (used in POST operations).
       * Input is read from stdin. Number of characters to read
       * can be found in the environment ::payload CONTENT_LENGTH.
      */
      void parse_body(::file::file *, const char * pszContentType, strsize content_length);
      /**
       * Another constructor (used in GET operations).
       * Input is read from the environment ::payload QUERY_STRING.
       * @lparam query_string The httpd server provided QUERY_STRING
       * @lparam length Query string length.
      */
      void parse_query_string(const string & query_string,strsize length);

      void EnableRaw(bool bRaw = true);

      /** Encode characters '<' '>' '&' as &lt; &gt; &amp; */
      void strcpyval(string &,const char *) const;

      /* get value */
      property_set & get();
      property_set & post();
      property_set & request();

      string & boundary();

      void clear();

      form(const form& ) {}
      form& operator=(const form& ) { return *this; }

   protected:

      
      property_set   m_setGet;
      property_set   m_setPost;
      property_set   m_setRequest;

      string         m_strBoundary;
      bool           m_bRaw;


   };


   inline property_set & form::get()
   {
      return m_setGet;
   }

   inline property_set & form::post()
   {
      return m_setPost;
   }

   inline property_set & form::request()
   {
      return m_setRequest;
   }

   inline void form::parse_query_string(const string & buffer, strsize)
   {
      m_setGet._parse_url_query(buffer);
   }


} // namespace http




