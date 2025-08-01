#pragma once


#include "acme/_operating_system.h"


#include <mysql/mysql.h>

#ifndef UNIVERSAL_WINDOWS

//
//typedef char** MYSQL_ROW;		/* return data as array of strings */
//typedef struct st_mysql MYSQL;
#include "axis/database/database/database_impl.h"


namespace mysql
{


   class CLASS_DECL_CA2_DATA database :
      virtual public ::database::database_impl
   {
      friend class dataset;
   public:


      ::collection::count                 m_cAffectedRows;
      mysql_protocol_type     m_protocol;
      MYSQL *                 m_pmysql;


      database();
      virtual ~database();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      virtual void _connect() override;


      bool close_mysql_database();

      virtual void* get_handle();

      virtual bool initialize();

      virtual bool exec(const ::scoped_string & scopedstrQuery) override;

      virtual ::pointer<::database::result_set>query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1);

      virtual MYSQL_RES* _mysql_query_result(const ::scoped_string & scopedstrSql);
      virtual bool _mysql_result_free(MYSQL_RES* pres);
      virtual MYSQL_ROW _mysql_fetch_row(MYSQL_RES* pres);
      virtual unsigned long* _mysql_fetch_lengths(MYSQL_RES* pres);
      virtual long long _mysql_num_fields(MYSQL_RES* pres);
      virtual long long _mysql_num_rows(MYSQL_RES* pres);

      virtual ::collection::count get_affected_rows_count() override;

      using database_impl::query_item;
      using database_impl::query_items;
      using database_impl::query_row;
      using database_impl::query_rows;

      //virtual bool query_table_item(::payload& payload, const ::string & table, const ::scoped_string & scopedstrItem, const ::string & where) override;
      virtual bool query_item(::payload & payload, const ::scoped_string & scopedstrSql) override;
      virtual bool query_blob(memory_base& memory, const ::scoped_string & scopedstrSql);
      virtual bool query_items(::pointer<payload_array>& pvara, const ::scoped_string & scopedstrSql) override;
      virtual bool query_row(::pointer<::database::row>& prow, const ::scoped_string & scopedstrSql) override;
      virtual bool query_rows(::pointer<::database::row_array>&prowarray, const ::scoped_string & scopedstrSql) override;

      virtual ::payload get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstrEmail, const ::scoped_string & scopedstrUser);

      string escape(const char * psz, character_count size);
      string escape(const ::scoped_string & scopedstr);

      ::payload get_insert_id();

      virtual string query_error(const ::scoped_string & scopedstrPrefix = nullptr) override;


   };


} //   namespace mysql




#endif


