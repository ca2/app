#pragma once


#ifndef UNIVERSAL_WINDOWS


typedef char **MYSQL_ROW;		/* return data as array of strings */
typedef struct st_mysql MYSQL;


namespace mysql
{


   class CLASS_DECL_CA2_DATA database :
      virtual public ::database::database
   {
      friend class dataset;
   public:



      database();
      virtual ~database();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      virtual void _connect() override;


      virtual bool close_mysql_database();

      virtual void * get_handle();

      virtual bool initialize();

      virtual bool exec(const ::string & pszQuery) override;

      virtual ::pointer<::database::result_set>query_result(const ::string & pszQuery, ::collection::count iRowCount  = -1, ::collection::count iColumnCount = -1);



      virtual ::collection::count get_affected_rows_count() override;

      virtual ::payload query_item(const ::string & pszSql, ::payload varDefault = false);
      virtual bool query_blob(memory_base & memory, const ::string & pszSql);
      virtual ::pointer<payload_array>query_items(const ::string & pszSql) override;
      virtual ::pointer<::database::row>query_row(const ::string & pszSql) override;
      virtual ::pointer<::database::row_array>query_rows(const ::string & pszSql) override;

      virtual ::payload query_table_item(const ::string & table, const ::string & item, const ::string &where, ::payload notfound = false);

      virtual ::payload get_agent(const ::string & pszTable, const ::string & pszEmail, const ::string & pszUser);

      virtual string escape(void * p, character_count iLine);
      virtual string escape(const ::string & psz);

      virtual ::payload get_insert_id();

      virtual string error1(const ::string & pszPrefix = nullptr) override;


   };


} //   namespace mysql




#endif


