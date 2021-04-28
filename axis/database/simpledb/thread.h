#pragma once


namespace simpledb
{

   class storage;


   class CLASS_DECL_AXIS thread :
      virtual public ::thread
   {
   public:


      storage *                                 m_pstorage;
      sockets::socket_handler                   m_handler;
      __pointer(sockets::http_session)          m_phttpsession;

      pointer_array < queue_item >              m_itema;


      thread()
      {

      }

      virtual ~thread() {}


      virtual ::e_status     run() override;

      void queue(const char * pszKey, block block);

   };


} // namespace simpledb



