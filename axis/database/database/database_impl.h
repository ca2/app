#pragma once


namespace database
{


   class dataset;
   class transaction;

   class CLASS_DECL_AXIS database_impl :
      virtual public ::database::database
   {
   public:


      bool              m_bActive;
      e_connection      m_econnection;
      string            m_strError;
      string            m_strHost;
      string            m_strPort;
      string            m_strName;
      string            m_strUser;
      string            m_strPass;
      string            m_strSckt;
      u64               m_uConnectionFlags;


      bool              m_bTransactionActive;
      i32               m_iLastError;
      string            m_strLastError;
      i64               m_iLastUsedTime;



      friend class transaction;

      database_impl();
      ~database_impl() override;


   protected:

      void start_transaction()  override{};
      void commit_transaction() override {};
      void rollback_transaction() override {};

   public:
      //virtual __pointer(class dataset) dataset() = 0;

      bool isActive() override { return m_bActive; }


      ::e_status     init() override;
      e_connection connection_status() override { return m_econnection; }
      ::e_status     set_error_code(int iErrorCode) override;
      string get_error_message() override;
      void* get_handle() override = 0;

      ::e_status     connect(
         const char* name,
         const char* host = nullptr,
         const char* port = nullptr,
         const char* user = nullptr,
         const char* pass = nullptr,
         const char* sckt = nullptr,
         u64 uConnectionFlags = 0) override;

      ::e_status     _connect()  override= 0;

      void disconnect() override;
      ::e_status     reset() override;
      ::e_status     create() override;
      ::e_status     drop() override;

      //virtual string escape(const char * psz);

      //inline __pointer(class transaction) transaction();


      ::count get_affected_rows_count() override;

      bool in_transaction() override;


      virtual bool exec(const char* pszQuery) override;


      ::payload get_agent(const char* pszTable, const char* psz, const char* pszUser) override;

      __pointer(result_set) query_result(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;
      //inline auto query(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) { return query_result(pszQuery, iRowCount, iColumnCount); }


      //virtual ::payload query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      __pointer(row_array) query_rows(const char* pszQuery) override;
      __pointer(row) query_row(const char* pszQuery) override;
      __pointer(var_array) query_items(const char* pszQuery) override;
      ::payload query_item(const char* pszQuery, const ::payload & payloadDefault = ::payload()) override;
      bool query_blob(get_memory getmemory, const char* pszQuery) override;

      //virtual bool query_rows(__pointer(row_array) & rows, const char * pszQuery);
      //virtual bool query_row(__pointer(row) & rows, const char * pszQuery);
      //virtual bool query_items(__pointer(var_array) & items, const char * pszQuery);
      //virtual bool query_item(::payload & item, const char * pszQuery);


      string escape(const char* psz) override;

      string error1(const char* pszPrefix = nullptr) override;
      void trace_error1(const char* pszPrefix = nullptr) override;

      ::payload get_insert_id() override;

   };


   //class CLASS_DECL_AXIS transaction :
   //   virtual public object
   //{
   //public:

   //   bool m_bProcessed;
   //   __pointer(database) m_pdatabase;

   //   transaction(database* pdatabase);
   //   ~transaction();

   //   void rollback();
   //   void commit();


   //};

   //inline __pointer(transaction) database::transaction()
   //{
   //   return __new(class transaction(this));
   //}


} // namespace database

