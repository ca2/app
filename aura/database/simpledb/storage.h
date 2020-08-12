#pragma once


namespace simpledb
{


   class server;


   class CLASS_DECL_AURA storage :
      virtual public ::object
   {
   public:


      __pointer(sockets::socket_handler)                 m_phandler;
      __pointer(sockets::http_session)                   m_phttpsession;
      string_map < item >                                m_map;
      bool                                               m_bIndexed;
      __pointer(server)                                  m_pserver;
      string                                             m_strUser;
      int                                                m_iSelectId;
      int                                                m_iReplaceId;
      int                                                m_iReplaceValue;
      __pointer(class thread)                            m_pthread;
      __pointer(class thread_localdatabase)              m_pthreadlocal;
      sqlite3_stmt *                                     m_pstmtSelect;
      sqlite3_stmt *                                     m_pstmtReplace;


      storage();
      ~storage();


      virtual ::estatus initialize_simpledb_storage(server * pserver);


   };


} // namespace simpledb



