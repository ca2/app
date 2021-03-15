#include "framework.h"
#include "_data.h"
#include "_userfs.h"
#include "core/user/user/_tree.h"


namespace userfs
{


   userfs::userfs()
   {

   }

   userfs::~userfs()
   {

   }

   
   ::e_status userfs::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::department::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      if(papplication->is_system())
      {

         create_factory <::userfs::main_view > ();
         create_factory <::userfs::tree > ();
         create_factory <::userfs::list > ();
         create_factory <::userfs::list_item > ();

      }

      if (!::apex::department::init())
      {

         return false;

      }

      return true;

   }


   ::e_status userfs::init1()
   {

      return ::success;

   }


} // namespace aura



namespace core
{


   //__pointer(::userfs::userfs) user::create_userfs()
   //{

   //  auto puserfs  = __new(::userfs::userfs(this));

   //  return puserfs;

   //}


   ::e_status user::userfs_process_init()
   {

      INFO("start");

      //m_puserfs = create_userfs();

      auto estatus = __compose(m_puserfs);

      if (!estatus)
      {

         ERR(".1");

         m_result.add(estatus);

         return estatus;

      }

      //m_spobjectUserFs = m_puserfs;

      //m_puserfs->construct(this);

      INFO("ok");

      return ::success;

   }


   ::e_status user::userfs_init1()
   {

      INFO("start");

      auto estatus = m_puserfs->init1();

      if(!estatus)
      {

         m_result.add(estatus);

         ERR(".1");

         return estatus;

      }

      INFO("ok");

      return ::success;

   }


} // namespace userfs



