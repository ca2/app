#pragma once


namespace simpledb
{


   class CLASS_DECL_CORE server:
      virtual public ::object
   {
      friend class result;
   public:


      string m_strLastError;
      long long m_iLastUsedTime;

      int       m_protocol;


      database(::particle * pparticle);
      virtual ~database();

      server(::particle * pparticle);
      virtual ~server();


      virtual bool open(const ::scoped_string & scopedstrDatabase);
      virtual bool close();


      virtual bool sql(const ::scoped_string & scopedstrQuery, ::payload & payload);



      virtual bool connect(
      const ::scoped_string & scopedstrHost,
      const ::scoped_string & scopedstrUser,
      const ::scoped_string & scopedstrPassword,
      const ::scoped_string & scopedstrDatabase,
      int iPort = 0,
      const ::scoped_string & scopedstrSocketName = nullptr,
      unsigned int uFlags = 0);

      virtual bool close();

      virtual bool initialize();

      virtual ::pointer<result>query(const ::scoped_string & scopedstrSql);
      virtual ::payload query_item(const ::scoped_string & scopedstrSql,::payload varDefault = false);
      virtual bool query_blob(memory_base & memory, const ::scoped_string & scopedstrSql);
      virtual ::payload query_items(const ::scoped_string & scopedstrSql);
      virtual ::payload query_row(const ::scoped_string & scopedstrSql);
      virtual ::payload query_rows(const ::scoped_string & scopedstrSql);


      virtual ::payload query_table_item(const ::string & table, const ::string & item, const ::string &where,::payload notfound = false);

      virtual ::payload get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstrEmail, const ::scoped_string & scopedstrUser);

      virtual string escape(void * p,character_count iLine);
      virtual string escape(const ::scoped_string & scopedstr);

      virtual ::payload get_insert_id();

      virtual string error1(const ::scoped_string & scopedstrPrefix = nullptr);
      virtual void trace_error1(const ::scoped_string & scopedstrPrefix = nullptr);

   };


} //   namespace simpledb



