#pragma once


namespace database
{


   class dataset;
   class transaction;

   class CLASS_DECL_AQUA database :
      virtual public ::object
   {
   public:

      friend class transaction;

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


      database();
      virtual ~database();


   protected:

      virtual void start_transaction() {};
      virtual void commit_transaction() {};
      virtual void rollback_transaction() {};

   public:
      //virtual __pointer(class dataset) dataset() = 0;

      virtual bool isActive() { return m_bActive; }


      virtual ::estatus     init();
      virtual e_connection connection_status() { return m_econnection; }
      virtual ::estatus     set_error_code(int iErrorCode);
      virtual string get_error_message();
      virtual void * get_handle() = 0;

      virtual ::estatus     connect(
      const char * name,
      const char * host = nullptr,
      const char * port = nullptr,
      const char * user = nullptr,
      const char * pass = nullptr,
      const char * sckt = nullptr,
      u64 uConnectionFlags = 0);

      virtual ::estatus     _connect() = 0;

      virtual void disconnect() { m_bActive = false; }
      virtual ::estatus     reset() { return ::success; }
      virtual ::estatus     create() { return ::success; }
      virtual ::estatus     drop() { return ::success; }

      //virtual string escape(const char * psz);

      inline __pointer(class transaction) transaction();


      virtual ::count get_affected_rows_count();

      virtual bool in_transaction() {return m_bTransactionActive;};


      virtual bool exec(const char * pszQuery);


      virtual __pointer(result_set) query_result(const char * pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);
      inline auto query(const char * pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) { return query_result(pszQuery, iRowCount, iColumnCount); }


      //virtual var query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      virtual __pointer(row_array) query_rows(const char * pszQuery);
      virtual __pointer(row) query_row(const char * pszQuery);
      virtual __pointer(var_array) query_items(const char * pszQuery);
      virtual var query_item(const char * pszQuery);
      virtual bool memory_query_item(get_memory getmemory, const char * pszQuery);

      //virtual bool query_rows(__pointer(row_array) & rows, const char * pszQuery);
      //virtual bool query_row(__pointer(row) & rows, const char * pszQuery);
      //virtual bool query_items(__pointer(var_array) & items, const char * pszQuery);
      //virtual bool query_item(var & item, const char * pszQuery);


      virtual string escape(const char * psz);

      virtual string error1(const char * pszPrefix = nullptr);
      virtual void trace_error1(const char * pszPrefix = nullptr);


   };


   class CLASS_DECL_AQUA transaction :
      virtual public context_object
   {
   public:

      bool m_bProcessed;
      __pointer(database) m_pdatabase;

      transaction(database * pdatabase);
      ~transaction();

      void rollback();
      void commit();


   };

   inline __pointer(transaction) database::transaction()
   {
      return __new(class transaction(this));
   }


} // namespace database

