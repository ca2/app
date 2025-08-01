#include "framework.h"
#include "handler.h"
#include "menu_library.h"
#include "item.h"
#include "tree_interface.h"
#include "acme/prototype/data/listener.h"


namespace filehandler
{


   handler::handler()
   {

   }


   handler::~handler()
   {

   }


   void handler::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      __construct_new(m_ptree);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void handler::defer_add_library(::acme::library * plibrary)
   {

      menu_library * pmenulibrary = dynamic_cast < menu_library * > (plibrary);

      if(pmenulibrary != nullptr)
      {

         add_menu_library(pmenulibrary);

      }
      else
      {

         library * phandlerlibrary = dynamic_cast < library * > (plibrary);

         if(phandlerlibrary != nullptr)
         {

            add_library(phandlerlibrary);

         }

      }

   }


   void handler::add_library(library * plibrary)
   {

      string_array straExtension;

      plibrary->get_extension_list(straExtension);

      for(int i = 0; i < straExtension.get_count(); i++)
      {

         auto ptreeitem = get_extension_tree_item(straExtension[i], true);

         if (!ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pitem.cast < item >();

         if (!pitem)
         {

            continue;

         }

         pitem->m_straHandlerLibrary.add(plibrary->m_strName);

         plibrary->get_extension_app(pitem->m_straApp, straExtension[i]);

      }

      string_array straMimeType;

      plibrary->get_mime_type_list(straMimeType);

      for(int i = 0; i < straMimeType.get_count(); i++)
      {

         auto ptreeitem = get_extension_tree_item(straMimeType[i], true);

         if (!ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pitem.cast < item >();

         if (!pitem)
         {

            continue;

         }

         pitem->m_straHandlerLibrary.add(plibrary->m_strName);

         plibrary->get_mime_type_app(pitem->m_straApp, straMimeType[i]);

      }

   }

   void handler::add_menu_library(menu_library * plibrary)
   {

      string_array straExtension;

      plibrary->get_extension_list(straExtension);

      for(int i = 0; i < straExtension.get_count(); i++)
      {

         auto ptreeitem = get_extension_tree_item(straExtension[i], true);

         if (ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pitem.cast < item >();

         if (!pitem)
         {

            continue;

         }

         pitem->m_straMenuLibrary.add(plibrary->m_strName);

         plibrary->get_extension_app(pitem->m_straApp, straExtension[i]);

      }

      string_array straMimeType;

      plibrary->get_mime_type_list(straMimeType);

      for(int i = 0; i < straMimeType.get_count(); i++)
      {

         auto ptreeitem = get_mime_type_tree_item(straMimeType[i], true);

         if (ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pitem.cast < item >();

         if (pitem)
         {

            continue;

         }

         pitem->m_straMenuLibrary.add(plibrary->m_strName);

         plibrary->get_mime_type_app(pitem->m_straApp, straMimeType[i]);

      }

   }


   ::pointer<::data::tree_item<item>>handler::get_extension_tree_item(const ::scoped_string & scopedstrExtension, bool bCreate)
   {

      auto ptreeitem = m_ptree->get_base_item()->get_next();

      if(ansi_cmp(scopedstrExtension, "*") == 0)
      {

         while(ptreeitem)
         {

            auto pitem = ptreeitem->m_pitem.cast < item >();

            if (pitem && pitem->m_etopictype == item::topic_type_root)
            {

               return pitem;

            }

            ptreeitem = ptreeitem->get_next_or_parent_next();

         }

         if (!bCreate)
         {

            return nullptr;

         }

         ptreeitem = m_ptree->insert_item(__allocate item(), ::data::e_relative_last_child, m_ptree->get_base_item());

         ptreeitem->m_pitem.cast < item > ()->m_etopictype = item::topic_type_root;

      }
      else
      {

         while(ptreeitem)
         {

            auto pitem = ptreeitem->m_pitem.cast < item >();

            if(pitem && pitem->m_etopictype == item::topic_type_extension
                  && pitem->m_strTopic.case_insensitive_order(scopedstrExtension) == 0)
            {

               return pitem;

            }

            ptreeitem = ptreeitem->get_next_or_parent_next();

         }

         if (!bCreate)
         {

            return nullptr;

         }

         ptreeitem = m_ptree->insert_item(__allocate item(), ::data::e_relative_last_child, m_ptree->get_base_item());

         auto pitem = ptreeitem->m_pitem.cast < item >();

         pitem->m_etopictype      = item::topic_type_extension;

         pitem->m_strTopic        = scopedstrExtension;

      }

      return ptreeitem;

   }


   ::pointer<::data::tree_item<item>>handler::get_mime_type_tree_item(const ::scoped_string & scopedstrMimeType, bool bCreate)
   {

      auto ptreeitem = m_ptree->get_base_item()->get_child_next_or_parent();

      while(ptreeitem)
      {

         auto pitem = ptreeitem->m_pitem.cast < item >();

         if (pitem && pitem->m_etopictype == item::topic_type_mime_type
            && pitem->m_strTopic.case_insensitive_order(scopedstrMimeType) == 0)
         {

            return pitem;

         }

         ptreeitem = ptreeitem->get_next_or_parent_next();

      }

      if (!bCreate)
      {

         return nullptr;

      }

      ptreeitem = m_ptree->insert_item(__allocate item(), ::data::e_relative_last_child, m_ptree->get_base_item());

      auto pdataitem = ptreeitem->m_pitem.cast < item >();

      pdataitem->m_etopictype      = item::topic_type_mime_type;

      pdataitem->m_strTopic        = scopedstrMimeType;

      return ptreeitem;

   }


   void handler::get_extension_app(string_array & straAppId, const ::scoped_string & scopedstrExtension)
   {

      auto ptreeitem = get_extension_tree_item(scopedstrExtension, false);

      if (!ptreeitem)
      {

         return;

      }

      auto pitem = ptreeitem->m_pitem.cast < item >();

      if (pitem)
      {

         straAppId.append(pitem->m_straApp);

      }

   }


   void handler::get_mime_type_app(string_array & straAppId, const ::scoped_string & scopedstrMimeType)
   {

      auto ptreeitem = get_mime_type_tree_item(scopedstrMimeType, false);

      if (ptreeitem)
      {

         return;

      }

      auto pitem = ptreeitem->m_pitem.cast < item >();

      if (pitem)
      {

         straAppId.append(pitem->m_straApp);

      }

   }


} // namespace filehandler



