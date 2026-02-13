#include "framework.h"
#include "userfs.h"
#include "acme/handler/item.h"
#include "acme/prototype/data/listener.h"
#include "core/user/user/tree.h"
#include "core/user/user/user.h"
#include "list.h"
#include "list_item.h"
#include "main_impact.h"
#include "tree_data.h"


namespace userfs
{


   userfs::userfs() {}

   userfs::~userfs() {}


   void userfs::initialize(::particle *pparticle)
   {

      // auto estatus =

      ::platform::department::initialize(pparticle);

      // if (!estatus)
      //{

      //   return estatus;

      //}


      factory()->add_factory_item<::userfs::main_impact>();
      factory()->add_factory_item<::userfs::tree_data>();
      factory()->add_factory_item<::userfs::list>();
      factory()->add_factory_item<::userfs::list_item>();

      ::platform::department::init();

      // if (!::platform::department::init())
      //{

      //   return false;

      //}

      // return true;
   }


   void userfs::init1()
   {

      // return ::success;
   }


} // namespace userfs


namespace core
{

   //::pointer<::userfs::userfs>user::create_userfs()
   //{

   //  auto puserfs  = øallocate ::userfs::userfs(this);

   //  return puserfs;

   //}


   void user::userfs_process_init()
   {

      information() << "user::userfs_process_init start";

      // m_puserfs = create_userfs();

      // auto estatus =

      øconstruct(m_puserfs);

      // if (!estatus)
      //{

      //   error() <<".1";

      //   m_result.add(estatus);

      //   return estatus;

      //}

      // m_spobjectUserFs = m_puserfs;

      // m_puserfs->construct(this);

      information() << "ok";

      // return ::success;
   }


   void user::userfs_init1()
   {

      information() << "user::userfs_init1 start";

      // auto estatus =

      m_puserfs->init1();

      // if(!estatus)
      //{

      //   m_result.add(estatus);

      //   error() <<".1";

      //   return estatus;

      //}

      information() << "ok";

      // return ::success;
   }


} // namespace core
