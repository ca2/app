#pragma once


#ifndef _UWP


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


      virtual ::e_status initialize(::object * pobject) override;
      virtual ::e_status destroy() override;


      virtual ::e_status _connect() override;


      virtual bool close_mysql_database();

      virtual void * get_handle();

      virtual bool initialize();

      virtual bool exec(const char * pszQuery) override;

      virtual __pointer(::database::result_set) query_result(const char * pszQuery, ::count iRowCount  = -1, ::count iColumnCount = -1);



      virtual ::count get_affected_rows_count() override;

      virtual ::payload query_item(const char * pszSql, ::payload varDefault = false);
      virtual bool query_blob(memory_base & memory, const char * pszSql);
      virtual __pointer(payload_array) query_items(const char * pszSql) override;
      virtual __pointer(::database::row) query_row(const char * pszSql) override;
      virtual __pointer(::database::row_array) query_rows(const char * pszSql) override;

      virtual ::payload query_table_item(const char * table, const char * item, const char *where, ::payload notfound = false);

      virtual ::payload get_agent(const char * pszTable, const char * pszEmail, const char * pszUser);

      virtual string escape(void * p, strsize iLine);
      virtual string escape(const char * psz);

      virtual ::payload get_insert_id();

      virtual string error1(const char * pszPrefix = nullptr) override;


   };


} //   namespace mysql




#endif


