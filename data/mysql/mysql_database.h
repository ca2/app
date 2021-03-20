#pragma once

#include "acme/operating_system.h"
#include <mysql/mysql.h>

#ifndef _UWP

//
//typedef char** MYSQL_ROW;		/* return data as array of strings */
//typedef struct st_mysql MYSQL;


namespace mysql
{


   class CLASS_DECL_CA2_DATA database :
      virtual public ::database::database_impl
   {
      friend class dataset;
   public:


      ::count                 m_cAffectedRows;
      mysql_protocol_type     m_protocol;
      MYSQL *                 m_pmysql;


      database();
      virtual ~database();


      virtual ::e_status initialize(::context_object* pcontextobject) override;
      virtual void finalize() override;


      virtual ::e_status _connect() override;


      bool close_mysql_database();

      virtual void* get_handle();

      virtual bool initialize();

      virtual bool exec(const char* pszQuery) override;

      virtual __pointer(::database::result_set) query_result(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);

      virtual MYSQL_RES* _mysql_query_result(const char* pszSql);
      virtual bool _mysql_result_free(MYSQL_RES* pres);
      virtual MYSQL_ROW _mysql_fetch_row(MYSQL_RES* pres);
      virtual unsigned long* _mysql_fetch_lengths(MYSQL_RES* pres);
      virtual i64 _mysql_num_fields(MYSQL_RES* pres);
      virtual i64 _mysql_num_rows(MYSQL_RES* pres);

      virtual ::count get_affected_rows_count() override;

      using database_impl::query_item;
      using database_impl::query_items;
      using database_impl::query_row;
      using database_impl::query_rows;

      //virtual bool query_table_item(::payload& payload, const char* table, const char * item, const char * where) override;
      virtual bool query_item(::payload & payload, const char* pszSql) override;
      virtual bool query_blob(memory_base& memory, const char* pszSql);
      virtual bool query_items(__pointer(var_array) & pvara, const char* pszSql) override;
      virtual bool query_row(__pointer(::database::row) & prow, const char* pszSql) override;
      virtual bool query_rows(__pointer(::database::row_array) &prowarray, const char* pszSql) override;

      virtual ::payload get_agent(const char* pszTable, const char* pszEmail, const char* pszUser);

      string escape(void* p, strsize iLine);
      string escape(const char* psz);

      ::payload get_insert_id();

      virtual string error1(const char* pszPrefix = nullptr) override;


   };


} //   namespace mysql




#endif


