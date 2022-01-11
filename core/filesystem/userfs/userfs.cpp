#include "framework.h"
#include "_data.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_userfs.h"
#endif

#include "core/user/user/_tree.h"


namespace userfs
{


   userfs::userfs()
   {

   }

   userfs::~userfs()
   {

   }

   
   void userfs::initialize(::object * pobject)
   {

      auto estatus = ::acme::department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }


      ::factory::add_factory_item <::userfs::main_impact > ();
      ::factory::add_factory_item <::userfs::tree > ();
      ::factory::add_factory_item <::userfs::list > ();
      ::factory::add_factory_item <::userfs::list_item > ();

      if (!::acme::department::init())
      {

         return false;

      }

      return true;

   }


   void userfs::init1()
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


   void user::userfs_process_init()
   {

      INFORMATION("start");

      //m_puserfs = create_userfs();

      auto estatus = __compose(m_puserfs);

      if (!estatus)
      {

         ERROR(".1");

         m_result.add(estatus);

         return estatus;

      }

      //m_spobjectUserFs = m_puserfs;

      //m_puserfs->construct(this);

      INFORMATION("ok");

      return ::success;

   }


   void user::userfs_init1()
   {

      INFORMATION("start");

      auto estatus = m_puserfs->init1();

      if(!estatus)
      {

         m_result.add(estatus);

         ERROR(".1");

         return estatus;

      }

      INFORMATION("ok");

      return ::success;

   }


} // namespace userfs



