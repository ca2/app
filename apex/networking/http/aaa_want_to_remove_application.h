#pragma once


namespace http
{


   class CLASS_DECL_APEX application :
      virtual public ::object
   {
   public:


      ::property_set       m_setHttp;


      application(::object * pobject);
      virtual ~application();

      void http_application_destruct();

      property_set & process_set(property_set & set, const char * pszUrl);

      DECLARE_MESSAGE_HANDLER(get);

      virtual bool get(::sockets::socket_handler & handler, __pointer(::sockets::http_client_socket) & psocket, const char * pszUrl, property_set & set);

      virtual string api_get(const char * pszUrl, property_set & set);
      virtual string api_get(const char * pszUrl);

      virtual bool exists(const char * pszUrl, property_set & set);
      virtual bool is_file_or_dir(const char * pszUrl, ::payload * pvarQuery, ::file::enum_type * petype, property_set & set);

      virtual ::payload length(const char * pszUrl, property_set & set);
      virtual ::payload length(const char * pszUrl, ::payload * pvarQuery, property_set & set);

      virtual string get(const char * pszUrl, property_set & set);
      virtual ::e_status _get(const char * pszUrl, property_set & set);

      virtual ::e_status get(string & str, const char * pszUrl, property_set & set);
      virtual ::e_status get(memory_base & memory, const char * pszUrl, property_set & set);

      virtual bool request(const char * pszRequest, const char * pszUrl, property_set & set);

      virtual bool download(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession,const char * pszUrl, ::payload payloadFile,property_set & set);
      virtual bool download(const char * pszUrl, ::payload payloadFile, property_set & set);


      virtual bool put(const char * pszUrl, memory & memory, property_set & set);
      virtual bool put(const char * pszUrl, file_pointer  pfile, property_set & set);

      virtual string locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema);

      virtual string get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);

   };


} // namespace htttp
