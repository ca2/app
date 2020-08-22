#include "framework.h"
#include "aura/xml/_.h"


namespace user
{


   menu_item::menu_item()
   {

      m_puiHost = nullptr;
      m_bBreak = false;
      m_puserinteraction = nullptr;
      m_spmenuitema      = __new(menu_item_ptra(this));
      m_iLevel       = 0;
      m_bPopup       = false;

   }


   menu_item::~menu_item()
   {

      output_debug_string("menu_item::~menu_item (1)");
      output_debug_string("menu_item::~menu_item (2)");
      output_debug_string("menu_item::~menu_item (3)");

   }


   bool menu_item::create_menu(const string_array & straCommand, const string_array & straCommandTitle)
   {

      ::count iItemCount = straCommand.get_count();

      if(straCommandTitle.get_size() < straCommand.get_size())
         return false;

      for(i32 i = 0; i < iItemCount; i++)
      {
         string strCommand = straCommand[i];
         string strCommandTitle = straCommandTitle[i];
         auto pitemNewChild = __new(menu_item);
         pitemNewChild->m_bPopup = false;
         if(strCommand.is_empty())
         {
            pitemNewChild->m_id = "separator";
            m_iSeparatorCount++;
         }
         else
         {
            m_iFullHeightItemCount++;
            pitemNewChild->m_id = strCommand;
            pitemNewChild->m_iLevel = 0;
            pitemNewChild->m_puserinteraction->set_window_text(strCommandTitle);
         }
         add_item(pitemNewChild);
      }

      return iItemCount > 0;

   }


   void menu_item::menu_item_destruct()
   {

      for (auto & pitemChild : m_spmenuitema->ptra())
      {

         pitemChild->menu_item_destruct();

      }

      m_puserinteraction.release();

      m_puiHost.release();

      m_pmenu.release();

      m_pmenuitemParent.release();

   }

   bool menu_item::load_menu(::xml::node * pnode)
   {

      m_iSeparatorCount       = 0;
      m_iFullHeightItemCount  = 0;

      return load_menu(pnode, m_iLevel);

   }


   bool menu_item::load_menu(::xml::node * pnode, i32 iLevel)
   {

      ::count iItemCount = pnode->get_children_count();


      m_bPopup = pnode->get_children_count() > 0 && pnode->get_name() == "menubar";

      if(pnode->get_name() == "separator")
      {

         m_id = "separator";

         if(m_pmenu->m_pmenuParent != nullptr)
         {

            m_pmenu->m_pmenuParent->m_pmenuitemThis->m_iSeparatorCount++;

         }

      }
      else
      {

         m_iFullHeightItemCount++;

         ::id id = pnode->attribute("id");

         id = translate_property_id(id);

         m_id = id;

         string strText;

         if(m_bPopup)
         {

            m_iLevel = iLevel + 1;

            strText = pnode->attribute("title");

         }
         else
         {

            m_iLevel = iLevel;

            strText = pnode->get_value();

         }

         if (m_puserinteraction != nullptr)
         {

            m_puserinteraction->set_window_text(strText);

         }

         m_strTitle = strText;

         string strImage = pnode->attribute("image");

         if (strImage.has_char())
         {

            __compose(m_pimage, Application.matter_image(strImage));

         }

      }

      for (i32 i = 0; i < iItemCount; i++)
      {

         auto pnodeChild = pnode->child_at(i);

         auto pitemNewChild = __new(menu_item);

         pitemNewChild->m_pmenu = m_pmenu;

         pitemNewChild->load_menu(pnodeChild);

         add_item(pitemNewChild);

      }

      return true;

   }


   void menu_item::add_item(menu_item * pitem)
   {

      pitem->m_pmenuitemParent = this;

      m_spmenuitema->add(pitem);

   }


   bool menu_item::contains_menu_item(menu_item * pitem, bool bRecursive) const
   {

      if (this == pitem)
      {

         return true;

      }

      if (m_spmenuitema.is_null())
      {

         return false;

      }

      if (m_spmenuitema->contains(pitem))
      {

         return true;

      }

      if (!bRecursive)
      {

         return false;

      }

      for (auto & pitemChild : m_spmenuitema->ptra())
      {

         if (pitemChild->contains_menu_item(pitem))
         {

            return true;

         }

      }

      return false;

   }

   bool menu_item::create_buttons(::draw2d::graphics_pointer & pgraphics, menu * pmenu)
   {

      ::user::style_pointer pstyle;

      for (i32 iItem = 0; iItem < m_spmenuitema->get_size(); iItem++)
      {

         __pointer(menu_item) pitem = m_spmenuitema->element_at(iItem);

         __pointer(::user::interaction) pinteraction = pitem->m_puserinteraction;

         if (pinteraction.is_null())
         {

            pinteraction = m_pmenu->create_menu_button(pgraphics, pitem);

         }

         if (pinteraction.is_null())
         {

            return false;

         }

         if (pinteraction->is_window())
         {

            pinteraction->DestroyWindow();

         }

         if (!pinteraction->create_window(pmenu, pitem->m_id))
         {

            return false;

         }

         pinteraction->m_id = pitem->m_id;

         pinteraction->m_pmenuitemThis = pitem;

         if (!pinteraction->is_window())
         {

            return false;

         }

         pitem->m_pmenu = pmenu;

         pinteraction->set_window_text(pitem->m_strTitle);

         if(pmenu->m_bInline)
         {

            pitem->create_buttons(pgraphics, pmenu);

         }

         pitem->m_puserinteraction = pinteraction;

      }

      return true;

   }


   bool menu_item::IsPopup()
   {

      return m_spmenuitema.is_set() && m_spmenuitema->get_count() > 0;

   }


   menu_item_ptra::menu_item_ptra(menu_item * pitemParent) 
   {

      m_pitemParent = pitemParent;

   }


   menu_item_ptra::~menu_item_ptra()
   {

   }


   menu_item * menu_item::find(id id)
   {

      if(m_spmenuitema.is_null())
      {
         return nullptr;

      }

      return m_spmenuitema->find(id);

   }


   void menu_item::OnAddRef()
   {

   }


   void menu_item::OnRelease()
   {

   }

   menu_item * menu_item_ptra::find(id id)
   {

      menu_item * pitemFind;

      for(i32 i = 0; i < this->get_size(); i++)
      {

         menu_item * pitem = element_at(i);

         if(pitem->m_id  == id)
         {

            return pitem;

         }

         pitemFind = pitem->find(id);

         if(pitemFind != nullptr)
         {

            return pitemFind;

         }

      }

      return nullptr;

   }




} // namespace user

