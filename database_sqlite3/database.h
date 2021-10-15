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
      ~database() override;


   protected:

      void start_transaction() override;
      void commit_transaction() override;
      void rollback_transaction() override;

   public:


      //virtual __pointer(::database::dataset) dataset() override;
      ::database::e_connection connection_status() override;

      ::e_status set_error_code(i32 iErrorCode) override;

      void * get_handle() override;
      string get_error_message() override;

      ::e_status _connect() override;
      void disconnect() override;
      ::e_status create() override;
      ::e_status drop() override;


      string escape(const ::string & psz) override;

      //virtual __pointer(class dataset) dataset() = 0;

      bool isActive() override;


      ::e_status init() override;

      string add_error_message(const ::string& strErrorMessage) override;

      ::e_status connect(
         const ::string & name,
         const ::string & host = nullptr,
         const ::string & port = nullptr,
         const ::string & user = nullptr,
         const ::string & pass = nullptr,
         const ::string & sckt = nullptr,
         u64 uConnectionFlags = 0) override;


      ::e_status reset() override;

      //virtual string escape(const ::string & psz);

      ::count get_affected_rows_count() override;

      bool in_transaction() override;

      bool exec(const ::string & pszQuery) override;

      __pointer(::database::result_set) query_result(const ::string & pszQuery, ::count iRowCount, ::count iColumnCount) override;

      __pointer(::database::result_set) query(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;


      //virtual ::payload query(const ::string & pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      __pointer(::database::row_array) query_rows(const ::string & pszQuery) override;
      
      __pointer(::database::row) query_row(const ::string & pszQuery) override;
      
      __pointer(::payload_array) query_items(const ::string & pszQuery) override;
      
      virtual ::payload query_item(const ::string & pszQuery);
      virtual bool memory_query_item(get_memory getmemory, const ::string & pszQuery);

      //virtual bool query_rows(__pointer(row_array) & rows, const ::string & pszQuery);
      //virtual bool query_row(__pointer(row) & rows, const ::string & pszQuery);
      //virtual bool query_items(__pointer(payload_array) & items, const ::string & pszQuery);
      //virtual bool query_item(::payload & item, const ::string & pszQuery);


      //virtual string escape(const ::string & psz);

      virtual string error1(const ::string & pszPrefix = nullptr);
      virtual void trace_error1(const ::string & pszPrefix = nullptr);
      virtual string query_error(const ::string& pszPrefix = nullptr);


      virtual ::e_status set_id_blob(string strKey, ::block block) override;
      virtual ::e_status get_id_blob(string strKey, ::get_memory getmemory) override;



   };


} // namespace sqlite



