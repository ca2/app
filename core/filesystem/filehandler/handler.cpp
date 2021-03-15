#include "framework.h"
#include "_data.h"


namespace filehandler
{


   handler::handler()
   {

   }


   handler::~handler()
   {

   }


   ::e_status handler::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::object::initialize(pcontextobject);

      if(!estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_ptree);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void handler::defer_add_library(::apex::library * plibrary)
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

      for(i32 i = 0; i < straExtension.get_count(); i++)
      {

         auto ptreeitem = get_extension_tree_item(straExtension[i], true);

         if (!ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pdataitem.cast < item >();

         if (!pitem)
         {

            continue;

         }

         pitem->m_straHandlerLibrary.add(plibrary->m_strCa2Name);

         plibrary->get_extension_app(pitem->m_straApp, straExtension[i]);

      }

      string_array straMimeType;

      plibrary->get_mime_type_list(straMimeType);

      for(i32 i = 0; i < straMimeType.get_count(); i++)
      {

         auto ptreeitem = get_extension_tree_item(straMimeType[i], true);

         if (!ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pdataitem.cast < item >();

         if (!pitem)
         {

            continue;

         }

         pitem->m_straHandlerLibrary.add(plibrary->m_strCa2Name);

         plibrary->get_mime_type_app(pitem->m_straApp, straMimeType[i]);

      }

   }

   void handler::add_menu_library(menu_library * plibrary)
   {

      string_array straExtension;

      plibrary->get_extension_list(straExtension);

      for(i32 i = 0; i < straExtension.get_count(); i++)
      {

         auto ptreeitem = get_extension_tree_item(straExtension[i], true);

         if (ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pdataitem.cast < item >();

         if (!pitem)
         {

            continue;

         }

         pitem->m_straMenuLibrary.add(plibrary->m_strCa2Name);

         plibrary->get_extension_app(pitem->m_straApp, straExtension[i]);

      }

      string_array straMimeType;

      plibrary->get_mime_type_list(straMimeType);

      for(i32 i = 0; i < straMimeType.get_count(); i++)
      {

         auto ptreeitem = get_mime_type_tree_item(straMimeType[i], true);

         if (ptreeitem)
         {

            continue;

         }

         auto pitem = ptreeitem->m_pdataitem.cast < item >();

         if (pitem)
         {

            continue;

         }

         pitem->m_straMenuLibrary.add(plibrary->m_strCa2Name);

         plibrary->get_mime_type_app(pitem->m_straApp, straMimeType[i]);

      }

   }


   __pointer(::data::tree_item) handler::get_extension_tree_item(const char * pszExtension, bool bCreate)
   {

      auto ptreeitem = m_ptree->get_base_item()->get_next();

      if(strcmp(pszExtension, "*") == 0)
      {

         while(ptreeitem)
         {

            auto pitem = ptreeitem->m_pdataitem.cast < item >();

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

         ptreeitem = m_ptree->insert_item(__new(item), ::data::RelativeLastChild, m_ptree->get_base_item());

         ptreeitem->m_pdataitem.cast < item > ()->m_etopictype = item::topic_type_root;

      }
      else
      {

         while(ptreeitem)
         {

            auto pitem = ptreeitem->m_pdataitem.cast < item >();

            if(pitem && pitem->m_etopictype == item::topic_type_extension
                  && pitem->m_strTopic.compare_ci(pszExtension) == 0)
            {

               return pitem;

            }

            ptreeitem = ptreeitem->get_next_or_parent_next();

         }

         if (!bCreate)
         {

            return nullptr;

         }

         ptreeitem = m_ptree->insert_item(__new(item), ::data::RelativeLastChild, m_ptree->get_base_item());

         auto pitem = ptreeitem->m_pdataitem.cast < item >();

         pitem->m_etopictype      = item::topic_type_extension;

         pitem->m_strTopic        = pszExtension;

      }

      return ptreeitem;

   }


   __pointer(::data::tree_item) handler::get_mime_type_tree_item(const char * pszMimeType, bool bCreate)
   {

      auto ptreeitem = m_ptree->get_base_item()->get_child_next_or_parent();

      while(ptreeitem)
      {

         auto pitem = ptreeitem->m_pdataitem.cast < item >();

         if (pitem && pitem->m_etopictype == item::topic_type_mime_type
            && pitem->m_strTopic.compare_ci(pszMimeType) == 0)
         {

            return pitem;

         }

         ptreeitem = ptreeitem->get_next_or_parent_next();

      }

      if (!bCreate)
      {

         return nullptr;

      }

      ptreeitem = m_ptree->insert_item(new item, ::data::RelativeLastChild, m_ptree->get_base_item());

      auto pdataitem = ptreeitem->m_pdataitem.cast < item >();

      pdataitem->m_etopictype      = item::topic_type_mime_type;

      pdataitem->m_strTopic        = pszMimeType;

      return ptreeitem;

   }


   void handler::get_extension_app(string_array & straAppId, const char * pszExtension)
   {

      auto ptreeitem = get_extension_tree_item(pszExtension, false);

      if (!ptreeitem)
      {

         return;

      }

      auto pitem = ptreeitem->m_pdataitem.cast < item >();

      if (pitem)
      {

         straAppId.add(pitem->m_straApp);

      }

   }


   void handler::get_mime_type_app(string_array & straAppId, const char * pszMimeType)
   {

      auto ptreeitem = get_mime_type_tree_item(pszMimeType, false);

      if (ptreeitem)
      {

         return;

      }

      auto pitem = ptreeitem->m_pdataitem.cast < item >();

      if (pitem)
      {

         straAppId.add(pitem->m_straApp);

      }

   }


} // namespace filehandler



