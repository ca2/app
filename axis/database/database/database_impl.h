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
      ::duration        m_durationLastUse;



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
         const ::string & name,
         const ::string & host = nullptr,
         const ::string & port = nullptr,
         const ::string & user = nullptr,
         const ::string & pass = nullptr,
         const ::string & sckt = nullptr,
         u64 uConnectionFlags = 0) override;

      ::e_status     _connect()  override= 0;

      void disconnect() override;
      ::e_status     reset() override;
      ::e_status     create() override;
      ::e_status     drop() override;

      //virtual string escape(const ::string & psz);

      //inline __pointer(class transaction) transaction();


      ::count get_affected_rows_count() override;

      bool in_transaction() override;


      virtual bool exec(const ::string & strQuery) override;


      ::payload get_agent(const ::string & pszTable, const ::string & psz, const ::string & pszUser) override;

      __pointer(result_set) query_result(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) override;
      //inline auto query(const ::string & pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) { return query_result(pszQuery, iRowCount, iColumnCount); }


      //virtual ::payload query(const ::string & pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      __pointer(row_array) query_rows(const ::string & pszQuery) override;
      __pointer(row) query_row(const ::string & pszQuery) override;
      __pointer(payload_array) query_items(const ::string & pszQuery) override;
      ::payload query_item(const ::string & pszQuery, const ::payload & payloadDefault = ::payload()) override;
      bool query_blob(get_memory getmemory, const ::string & pszQuery) override;

      //virtual bool query_rows(__pointer(row_array) & rows, const ::string & pszQuery);
      //virtual bool query_row(__pointer(row) & rows, const ::string & pszQuery);
      //virtual bool query_items(__pointer(payload_array) & items, const ::string & pszQuery);
      //virtual bool query_item(::payload & item, const ::string & pszQuery);


      string escape(const ::string & psz) override;

      string query_error(const ::string & pszPrefix = nullptr) override;
      void trace_error1(const ::string & pszPrefix = nullptr) override;

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

