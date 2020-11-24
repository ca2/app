#pragma once


namespace simpledb
{


   class CLASS_DECL_CORE server:
      virtual public ::object
   {
      friend class result;
   public:


      string m_strLastError;
      i64 m_iLastUsedTime;

      int       m_protocol;


      database(::layered * pobjectContext);
      virtual ~database();

      server(::layered * pobjectContext);
      virtual ~server();


      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool sql(const char * pszQuery, payload & payload);



      virtual bool connect(
      const char * pszHost,
      const char * pszUser,
      const char * pszPassword,
      const char * pszDatabase,
      i32 iPort = 0,
      const char * pszSocketName = nullptr,
      u32 uFlags = 0);

      virtual bool close();

      virtual bool initialize();

      virtual __pointer(result) query(const char * pszSql);
      virtual payload query_item(const char * pszSql,payload varDefault = false);
      virtual bool query_blob(memory_base & memory,const char * pszSql);
      virtual payload query_items(const char * pszSql);
      virtual payload query_row(const char * pszSql);
      virtual payload query_rows(const char * pszSql);


      virtual payload query_table_item(const char * table,const char * item,const char *where,payload notfound = false);

      virtual payload get_agent(const char * pszTable,const char * pszEmail,const char * pszUser);

      virtual string escape(void * p,strsize iLine);
      virtual string escape(const char * psz);

      virtual payload get_insert_id();

      virtual string error1(const char * pszPrefix = nullptr);
      virtual void trace_error1(const char * pszPrefix = nullptr);

   };


} //   namespace simpledb



