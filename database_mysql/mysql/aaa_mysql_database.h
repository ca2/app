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

      virtual bool exec(const ::scoped_string & scopedstrQuery) override;

      virtual ::pointer<::database::result_set>query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount  = -1, ::collection::count iColumnCount = -1);



      virtual ::collection::count get_affected_rows_count() override;

      virtual ::payload query_item(const ::scoped_string & scopedstrSql, ::payload varDefault = false);
      virtual bool query_blob(memory_base & memory, const ::scoped_string & scopedstrSql);
      virtual ::pointer<payload_array>query_items(const ::scoped_string & scopedstrSql) override;
      virtual ::pointer<::database::row>query_row(const ::scoped_string & scopedstrSql) override;
      virtual ::pointer<::database::row_array>query_rows(const ::scoped_string & scopedstrSql) override;

      virtual ::payload query_table_item(const ::string & table, const ::string & item, const ::string &where, ::payload notfound = false);

      virtual ::payload get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstrEmail, const ::scoped_string & scopedstrUser);

      virtual string escape(void * p, character_count iLine);
      virtual string escape(const ::scoped_string & scopedstr);

      virtual ::payload get_insert_id();

      virtual string error1(const ::scoped_string & scopedstrPrefix = nullptr) override;


   };


} //   namespace mysql




#endif


