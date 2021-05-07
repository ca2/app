#pragma once


namespace sqlite
{


   class CLASS_DECL_DATABASE_SQLITE3 database :
      public ::database::database_impl
   {
   public:


      void *                                             m_psqlite;

      sqlite3_stmt *                                     m_pstmtSelect;
      int                                                m_iSelectId;

      sqlite3_stmt *                                     m_pstmtReplace;
      int                                                m_iReplaceId;
      int                                                m_iReplaceValue;


      database();
      virtual ~database();


   protected:

      virtual void start_transaction() override;
      virtual void commit_transaction() override;
      virtual void rollback_transaction() override;

   public:


      //virtual __pointer(::database::dataset) dataset() override;
      virtual ::database::e_connection connection_status() override;

      virtual ::e_status     set_error_code(i32 iErrorCode) override;

      virtual void * get_handle() override;
      virtual string get_error_message() override;

      virtual ::e_status     _connect() override;
      virtual void disconnect() override;
      virtual ::e_status     create() override;
      virtual ::e_status     drop() override;


      string escape(const char * psz) override;

      //virtual __pointer(class dataset) dataset() = 0;

      virtual bool isActive();


      virtual ::e_status init();

      virtual string add_error_message(const ::string& strErrorMessage);

      virtual ::e_status     connect(
         const char* name,
         const char* host = nullptr,
         const char* port = nullptr,
         const char* user = nullptr,
         const char* pass = nullptr,
         const char* sckt = nullptr,
         u64 uConnectionFlags = 0);


      virtual ::e_status reset();

      //virtual string escape(const char * psz);



      virtual ::count get_affected_rows_count();

      virtual bool in_transaction();


      virtual bool exec(const char* pszQuery);


      virtual __pointer(::database::result_set) query_result(const char* pszQuery, ::count iRowCount, ::count iColumnCount);

      inline __pointer(::database::result_set) query(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);


      //virtual ::payload query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      virtual __pointer(::database::row_array) query_rows(const char* pszQuery);
      virtual __pointer(::database::row) query_row(const char* pszQuery);
      virtual __pointer(::var_array) query_items(const char* pszQuery);
      virtual ::payload query_item(const char* pszQuery);
      virtual bool memory_query_item(get_memory getmemory, const char* pszQuery);

      //virtual bool query_rows(__pointer(row_array) & rows, const char * pszQuery);
      //virtual bool query_row(__pointer(row) & rows, const char * pszQuery);
      //virtual bool query_items(__pointer(var_array) & items, const char * pszQuery);
      //virtual bool query_item(::payload & item, const char * pszQuery);


      //virtual string escape(const char* psz);

   /*   virtual string error1(const char* pszPrefix = nullptr);
      virtual void trace_error1(const char* pszPrefix = nullptr);
*/

      virtual ::e_status set_id_blob(string strKey, ::block block) override;
      virtual ::e_status get_id_blob(string strKey, ::get_memory getmemory) override;



   };


} // namespace sqlite



