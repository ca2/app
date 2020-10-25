#pragma once


namespace http
{


   class CLASS_DECL_APEX application :
      virtual public ::object
   {
   public:


      ::property_set       m_setHttp;


      application(::layered * pobjectContext);
      virtual ~application();

      void http_application_destruct();

      property_set & process_set(property_set & set, const char * pszUrl);

      DECL_GEN_SIGNAL(get);

      virtual bool get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & psocket, const char * pszUrl, property_set & set);

      virtual string api_get(const char * pszUrl, property_set & set);
      virtual string api_get(const char * pszUrl);

      virtual bool exists(const char * pszUrl, property_set & set);
      virtual bool is_file_or_dir(const char * pszUrl, var * pvarQuery, ::file::enum_type * petype, property_set & set);

      virtual var length(const char * pszUrl, property_set & set);
      virtual var length(const char * pszUrl, var * pvarQuery, property_set & set);

      virtual string get(const char * pszUrl, property_set & set);
      virtual ::estatus _get(const char * pszUrl, property_set & set);

      virtual ::estatus get(string & str, const char * pszUrl, property_set & set);
      virtual ::estatus get(memory_base & memory, const char * pszUrl, property_set & set);

      virtual bool request(const char * pszRequest, const char * pszUrl, property_set & set);

      virtual bool download(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession,const char * pszUrl, var varFile,property_set & set);
      virtual bool download(const char * pszUrl, var varFile, property_set & set);


      virtual bool put(const char * pszUrl, memory & memory, property_set & set);
      virtual bool put(const char * pszUrl, file_pointer  pfile, property_set & set);

      virtual string locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema);

      virtual string get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);

   };


} // namespace htttp
