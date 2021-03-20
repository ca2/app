#pragma once


namespace database
{


   class dataset;
   class transaction;


   class CLASS_DECL_AXIS database :
      virtual public ::object
   {
   public:

      friend class transaction;


      database();
      virtual ~database();


   protected:

      virtual void start_transaction();
      virtual void commit_transaction();
      virtual void rollback_transaction();
   

   public:
      //virtual __pointer(class dataset) dataset() = 0;

      virtual bool isActive() = 0;


      virtual ::e_status     init() = 0;
      virtual e_connection connection_status() = 0;
      virtual ::e_status     set_error_code(int iErrorCode) = 0;
      virtual string get_error_message() = 0;
      virtual void * get_handle() = 0;


      virtual ::e_status     connect(
      const char * name,
      const char * host = nullptr,
      const char * port = nullptr,
      const char * user = nullptr,
      const char * pass = nullptr,
      const char * sckt = nullptr,
      u64 uConnectionFlags = 0) = 0;

      virtual ::e_status     _connect() = 0;

      virtual void disconnect();
      virtual ::e_status     reset() = 0;
      virtual ::e_status     create() = 0;
      virtual ::e_status     drop() = 0;

      //virtual string escape(const char * psz);

      virtual  __pointer(class transaction) transaction();

      virtual ::count get_affected_rows_count() = 0;

      virtual bool in_transaction() = 0;


      virtual bool exec(const char * pszQuery) = 0;


      virtual __pointer(result_set) query_result(const char * pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1) = 0;
      virtual __pointer(result_set)  query(const char* pszQuery, ::count iRowCount = -1, ::count iColumnCount = -1);


      //virtual ::payload query(const char * pszQuery, ::count iMaxRowCount = -1, ::count iMaxColumnCount = -1);
      virtual ::payload query_table_item(const char* table, const char* item, const char* where, const ::payload & payload = ::payload());
      virtual __pointer(row_array) query_rows(const char * pszQuery);
      virtual __pointer(row) query_row(const char * pszQuery);
      virtual __pointer(var_array) query_items(const char * pszQuery);
      virtual ::payload query_item(const char * pszQuery, const ::payload & payloadDefault = ::payload());
      virtual bool memory_query_item(get_memory getmemory, const char * pszQuery) = 0;


      virtual bool query_table_item(::payload& payload, const char* table, const char* item, const char* where);


      virtual bool query_rows(__pointer(row_array)& rows, const char* pszQuery);
      virtual bool query_row(__pointer(row)& rows, const char* pszQuery);
      virtual bool query_items(__pointer(var_array)& items, const char* pszQuery);
      virtual bool query_item(::payload& item, const char* pszQuery);



      virtual ::payload get_agent(const char* pszTable, const char* psz, const char* pszUser) = 0;


      virtual string escape(const char * psz) = 0;

      virtual string add_error_message(const ::string& strErrorMessage);


      virtual string error1(const char * pszPrefix = nullptr) = 0;
      virtual void trace_error1(const char * pszPrefix = nullptr) = 0;

      virtual ::payload get_insert_id() = 0;


   };


} // namespace database



