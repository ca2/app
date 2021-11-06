#pragma once


namespace simpledb
{


   class socket_thread;


   class CLASS_DECL_CORE service :
      public plain_service
   {
   public:


      manager *                           m_pmanager;
      address_array < socket_thread * >   m_threadptra;


      service(::object * pobject);
      virtual ~service();


      virtual void serve();


   };



} // namespace simpledb



