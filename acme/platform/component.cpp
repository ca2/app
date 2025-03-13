// Created by camilo on 2025-03-09 01:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "component.h"
#include "component_implementation.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"


component::component()
{

}


component::~component()
{


}


void component::on_initialize_particle()
{

   ::particle::on_initialize_particle();

   defer_create_synchronization();

   add_handler(this);

}


void component::update()
{

   _synchronous_lock synchronouslock(this->synchronization());

   m_straImplementationAll.clear();
   m_straImplementationOnShelf.clear();
   m_straImplementationInstalled.clear();
   m_straImplementationEnabled.clear();

   _update_implementations_on_shelf();

   _update_installed_implementations();

   _update_enabled_implementations();

   m_straImplementationAll.append_unique(m_straImplementationOnShelf);
   m_straImplementationAll.append_unique(m_straImplementationInstalled);

}


void component::_update_implementations_on_shelf()
{

   ::file::path pathUrl = "https://ca2.network/component_implementations?component_path=" + m_strComponentPath;

   pathUrl.flags() += ::file::e_flag_bypass_cache;

   auto straImplementationOnShelf = file()->lines(pathUrl);

   for (auto & str : straImplementationOnShelf)
   {

      ::string_array stra;

      stra.explode("=", str);

      if (stra.size() == 2)
      {

         ::string strImplementation = stra[0];

         ::string strPath = stra[1];

         m_straImplementationOnShelf.add(strImplementation);

         m_straImplementationOnShelfPath.add(strPath);

      }

   }

}


void component::_update_installed_implementations()
{

   auto module_folder_files = directory_system()->files(directory_system()->module());

   for (auto file : module_folder_files)
   {

      ::string strImplementation = file.name();

      if (strImplementation.case_insensitive_begins_eat(m_strComponent + "_")
         && strImplementation.case_insensitive_ends_eat(node()->dynamic_library_suffix()))
      {

         m_straImplementationInstalled.add(strImplementation);

      }

   }

}


void component::_update_enabled_implementations()
{

   throw ::interface_only();

}


void component::_001CreateForm(::user::interaction * puserinteractionParent)
{

   throw ::interface_only();

}


//void component::update_components()
//{
//
//
//   ::string_array straImplementationOnShelf;
//   ::string_array straImplementationInstalled;
//   ::string_array straImplementationEnabled;
//   ::string_array straImplementationAll;
//
//
//   auto module_folder_files = directory_system()->files(directory_system()->module());
//
//   for (auto file : module_folder_files)
//      if (file.case_insensitive_begins(m_strComponent + "_"))
//         if (file.case_insensitive_ends_eat(node()->dynamic_library_suffix()))
//            straWallpaperImplementationInstalled.add(file);
//
//   straImplementationOnShelf.make_lower();
//   straImplementationInstalled.make_lower();
//
//   straImplementationAll.add_unique(straImplementationOnShelf);
//   straImplementationAll.add_unique(straImplementationInstalled);
//
//   update_installed();
//
//   m_straImplementationOnShelf = straImplementationOnShelf;
//   m_straImplementationInstalled = straImplementationInstalled;
//   m_straImplementationEnabled = straImplementationEnabled;
//   m_straImplementationAll = straImplementationAll;
//
//}


bool component::is_implementation(const ::scoped_string & scopedstrImplementation)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto strImplementation = scopedstrImplementation.lowered();

   return m_straImplementationAll.contains(strImplementation);

}


bool component::is_implementation_installed(const ::scoped_string & scopedstrImplementation)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto strImplementation = scopedstrImplementation.lowered();

   return m_straImplementationInstalled.contains(strImplementation);

}



bool component::is_implementation_on_shelf(const ::scoped_string & scopedstrImplementation)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto strImplementation = scopedstrImplementation.lowered();
   
   return m_straImplementationOnShelf.contains(strImplementation);

}


bool component::is_implementation_enabled(const ::scoped_string & scopedstrImplementation)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto strImplementation = scopedstrImplementation.lowered();

   return m_straImplementationEnabled.contains(strImplementation);

}


::string component::implementation_path(const ::scoped_string & scopedstrImplementation)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto strImplementation = scopedstrImplementation.lowered();

   auto iFind = m_straImplementationOnShelf.find_first(strImplementation);

   if (iFind < 0 || iFind >= m_straImplementationOnShelfPath.size())
   {

      return {};

   }

   auto strPath = m_straImplementationOnShelfPath[iFind];

   return strPath;

}


::component_implementation * component::implementation(const ::scoped_string & scopedstrImplementation)
{

   auto & pimplementation = m_mapImplementation[scopedstrImplementation];

   if (pimplementation.is_null())
   {

      pimplementation = create_implementation(scopedstrImplementation);

   }

   return pimplementation;

}


::pointer < ::component_implementation > component::create_implementation(const ::scoped_string & scopedstrImplementation)
{

   ::factory::factory_pointer pfactory;

   try
   {

      pfactory = system()->factory(m_strComponent, scopedstrImplementation);

      if (pfactory.is_null())
      {

         return nullptr;

      }

   }
   catch (...)
   {

      return nullptr;

   }

   ::pointer < ::component_implementation > pimplementation;

   __øconstruct(pimplementation, pfactory);

   if (pimplementation.is_null())
   {

      return nullptr;

   }

   return pimplementation;

}


::pointer_array < ::component_implementation > component::enabled_implementations()
{

   ::pointer_array < ::component_implementation > implementationa;

   for (auto & strImplementation : m_straImplementationEnabled)
   {

      auto pimplementation = implementation(strImplementation);

      if (::is_set(pimplementation))
      {

         implementationa.add(pimplementation);

      }

   }

   return ::transfer(implementationa);

}