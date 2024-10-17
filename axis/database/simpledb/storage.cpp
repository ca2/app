#include "framework.h"
#include "storage.h"
#include "server.h"
#include "thread.h"
#include "thread_localdatabase.h"


namespace simpledb
{


   storage::storage()
   {

      //m_pstmtSelect = nullptr;

      //m_pstmtReplace = nullptr;

      m_iSelectId = -1;

      m_iReplaceId = -1;

      m_iReplaceValue = -1;

      defer_create_synchronization();

   }


   storage::~storage()
   {


   }


   void storage::destroy()
   {

      if (m_pthread)
      {
         m_pthread->stop_task();

      }

      if (m_pthreadlocal)
      {

         m_pthreadlocal->stop_task();

      }

      m_pthread.defer_destroy();

      m_pthreadlocal.defer_destroy();

      m_phttpsession.defer_destroy();
      m_phandler.defer_destroy();

      m_pserver.release();

      m_map.clear();

      ::property_object::destroy();

   }


   void storage::initialize_simpledb_storage(server * pserver)
   {

      //auto estatus = 
      
      ::matter::initialize(pserver);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pserver = pserver;

      m_strUser = pserver->m_strUser;

      //return estatus;

   }


} // namespace simpledb



