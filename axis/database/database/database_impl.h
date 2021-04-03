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
      virtual ~database_impl();


   protected:

      virtual void start_transaction() {};
      virtual void commit_transaction() {};
      virtual void rollback_transaction() {};

   public:
      //virtual __pointer(class dataset) dataset() = 0;

      virtual bool isActive() { return m_bActive; }


      virtual ::e_status     init();
      virtual e_connection connection_status() { return m_econnection; }
      virtual ::e_status     set_error_code(int iErrorCode);
      virtual string get_error_message();
      virtual void* get_handle() = 0;

      virtual ::e_status     connect(
         const char* name,
         const char* host = nullptr,
         const char* port = nullptr,
         const char* user = nullptr,
         const char* pass = nullptr,
         const char* sckt = nullptr,
         u64 uConnectionFlags = 0);

      virtual ::e_status     _connect() = 0;

      virtual void disconnect();
      virtual ::e_status     reset();
      virtual ::e_status     create();
      virtual ::e_status     drop();

      //virtual string escape(const char * psz);

      //inline __pointer(class transaction) transaction();


      virtual ::count get_affected_rows_count();

      virtual bool in_transaction();


      virtual bool exec(const char* pszQuery) override;


      virtual ::payload get_agent(const char* pszTable, const char* psz, const char* pszUser);

      virtual __pointer(result_set) query_result(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);
      //inline auto query(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) { return query_result(pszQuery, iRowCount, iColumnCount); }


      //virtual ::payload query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      virtual __pointer(row_array) query_rows(const char* pszQuery) override;
      virtual __pointer(row) query_row(const char* pszQuery) override;
      virtual __pointer(var_array) query_items(const char* pszQuery) override;
      virtual ::payload query_item(const char* pszQuery, const ::payload & payloadDefault = ::payload()) override;
      virtual bool query_blob(get_memory getmemory, const char* pszQuery) override;

      //virtual bool query_rows(__pointer(row_array) & rows, const char * pszQuery);
      //virtual bool query_row(__pointer(row) & rows, const char * pszQuery);
      //virtual bool query_items(__pointer(var_array) & items, const char * pszQuery);
      //virtual bool query_item(::payload & item, const char * pszQuery);


      virtual string escape(const char* psz) override;

      virtual string error1(const char* pszPrefix = nullptr) override;
      virtual void trace_error1(const char* pszPrefix = nullptr) override;

      virtual ::payload get_insert_id() override;

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

