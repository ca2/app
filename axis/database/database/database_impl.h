#pragma once


#include "axis/database/database/database.h"


namespace database
{


   class dataset;
   class transaction;

   class CLASS_DECL_AXIS database_impl :
      virtual public ::database::database
   {
   public:


      bool              m_bActive;
      enum_connection   m_econnection;
      string            m_strError;
      string            m_strHost;
      string            m_strPort;
      string            m_strName;
      string            m_strUser;
      string            m_strPass;
      string            m_strSckt;
      unsigned long long               m_uConnectionFlags;


      bool              m_bTransactionActive;
      int               m_iLastError;
      string            m_strLastError;
      class ::time        m_timeLastUse;



      friend class transaction;

      database_impl();
      ~database_impl() override;


   protected:

      void start_transaction()  override{};
      void commit_transaction() override {};
      void rollback_transaction() override {};

   public:
      //virtual ::pointer<class dataset> dataset() = 0;

      bool isActive() override { return m_bActive; }


      void     init() override;
      enum_connection connection_status() override { return m_econnection; }
      void     set_error_code(int iErrorCode) override;
      string get_error_message() override;
      void* get_handle() override = 0;

      void     connect(
         const ::scoped_string & scopedstrName,
         const ::scoped_string & scopedstrHost = nullptr,
         const ::scoped_string & scopedstrPort = nullptr,
         const ::scoped_string & scopedstrUser = nullptr,
         const ::scoped_string & scopedstrPass = nullptr,
         const ::scoped_string & scopedstrSocket = nullptr,
         unsigned long long uConnectionFlags = 0) override;

      void     _connect()  override= 0;

      void disconnect() override;
      void     reset() override;
      void     create() override;
      void     drop() override;

      //virtual string escape(const ::scoped_string & scopedstr);

      //inline ::pointer<class transaction> transaction();


      ::collection::count get_affected_rows_count() override;

      bool in_transaction() override;


      virtual bool exec(const ::scoped_string & scopedstrQuery) override;


      ::payload get_agent(const ::scoped_string & scopedstrTable, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrUser) override;

      ::pointer<result_set>query_result(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1) override;
      //inline auto query(const ::scoped_string & scopedstrQuery, ::collection::count iRowCount = -1, ::collection::count iColumnCount = -1) { return query_result(scopedstrQuery, iRowCount, iColumnCount); }


      //virtual ::payload query(const ::scoped_string & scopedstrQuery, ::collection::count iMaxRowCount = -1, ::collection::count iMaxColumnCount = -1);
      ::pointer<row_array>query_rows(const ::scoped_string & scopedstrQuery) override;
      ::pointer<row>query_row(const ::scoped_string & scopedstrQuery) override;
      ::pointer<payload_array>query_items(const ::scoped_string & scopedstrQuery) override;
      ::payload query_item(const ::scoped_string & scopedstrQuery, const ::payload & payloadDefault = ::payload()) override;
      bool query_blob(get_memory getmemory, const ::scoped_string & scopedstrQuery) override;

      //virtual bool query_rows(::pointer<row_array>& rows, const ::scoped_string & scopedstrQuery);
      //virtual bool query_row(::pointer<row>& rows, const ::scoped_string & scopedstrQuery);
      //virtual bool query_items(::pointer<payload_array>& items, const ::scoped_string & scopedstrQuery);
      //virtual bool query_item(::payload & item, const ::scoped_string & scopedstrQuery);


      string escape(const ::scoped_string & scopedstr) override;

      string query_error(const ::scoped_string & scopedstrPrefix = nullptr) override;
      void trace_error1(const ::scoped_string & scopedstrPrefix = nullptr) override;

      ::payload get_insert_id() override;

   };


   //class CLASS_DECL_AXIS transaction :
   //   virtual public object
   //{
   //public:

   //   bool m_bProcessed;
   //   ::pointer<database>m_pdatabase;

   //   transaction(database* pdatabase);
   //   ~transaction();

   //   void rollback();
   //   void commit();


   //};

   //inline ::pointer<transaction>database::transaction()
   //{
   //   return __allocate class transaction (this);
   //}


} // namespace database

