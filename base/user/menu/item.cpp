#include "framework.h"
#include "base/platform/application.h"
#include "aqua/xml/document.h"
#include "aura/graphics/image/context_image.h"
#include "apex/message/command.h"
#include "item.h"
#include "menu.h"
#include "interaction.h"
#include "item_ptra.h"


class menu_item_command : public ::message::command        // class private to this file !
{
public: // re-implementations only

   menu_item_command(::particle * pparticle);
   void enable(bool bOn = true, const ::action_context & context = ::e_source_system) override;
   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
   void _001SetCheck(const e_check & echeck, const ::action_context & context = ::e_source_system) override;   // 0, 1 or 2 (indeterminate)
//   virtual void SetRadio(bool bOn = true, const ::action_context & context = ::e_source_system);
   //void _001SetText(const ::string & pszText, const ::action_context & context = ::e_source_system) override;

};



namespace user
{


   menu_item::menu_item()
   {

      m_puserinteractionHost = nullptr;
      m_bBreak = false;
      m_puserinteraction = nullptr;
      m_pmenuitema = __new(menu_item_ptra(this));
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
            pitemNewChild->m_atom = "separator";
            m_iSeparatorCount++;
         }
         else
         {
            m_iFullHeightItemCount++;
            pitemNewChild->m_atom = strCommand;
            pitemNewChild->m_iLevel = 0;
            pitemNewChild->m_puserinteraction->set_window_text(strCommandTitle);
         }
         add_item(pitemNewChild);
      }

      return iItemCount > 0;

   }


   void menu_item::menu_item_destruct()
   {

      for (auto & pitemChild : *m_pmenuitema)
      {

         pitemChild->menu_item_destruct();

      }

      m_puserinteraction.release();

      m_puserinteractionHost.release();

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

      ::pointer<::base::application>papp = get_app();

      m_bPopup = pnode->get_children_count() > 0 && pnode->get_name() == "menubar";

      if(pnode->get_name() == "separator")
      {

         m_atom = "separator";

         if(m_pmenu->m_pmenuParent != nullptr)
         {

            m_pmenu->m_pmenuParent->m_pmenuitem->m_iSeparatorCount++;

         }

      }
      else
      {

         m_iFullHeightItemCount++;

         ::atom atom = pnode->attribute("id");

         atom = translate_property_id(atom);

         m_atom = atom;

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

         string strImage (pnode->attribute("image").as_string());

         if (strImage.has_char())
         {

            auto pcontext = m_pcontext->m_pauracontext;

            auto pcontextimage = pcontext->context_image();

            __construct(m_pimage, pcontextimage->matter_image(strImage));

         }

      }

      for (i32 i = 0; i < iItemCount; i++)
      {

         auto pnodeChild = pnode->child_at(i);

         auto pitemNewChild = __create_new<menu_item>();

         pitemNewChild->m_pmenu = m_pmenu;

         pitemNewChild->load_menu(pnodeChild);

         add_item(pitemNewChild);

      }

      return true;

   }


   void menu_item::add_item(menu_item * pitem)
   {

      pitem->m_pmenuitemParent = this;

      m_pmenuitema->add(pitem);

   }


   bool menu_item::contains_menu_item(menu_item * pitem, bool bRecursive) const
   {

      if (this == pitem)
      {

         return true;

      }

      if (!m_pmenuitema)
      {

         return false;

      }

      if (m_pmenuitema->contains(pitem))
      {

         return true;

      }

      if (!bRecursive)
      {

         return false;

      }

      for (auto & pitemChild : *m_pmenuitema)
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

      for (i32 iItem = 0; iItem < m_pmenuitema->get_size(); iItem++)
      {

         ::pointer<menu_item>pitem = m_pmenuitema->element_at(iItem);

         ::pointer<::user::interaction>pinteraction = pitem->m_puserinteraction;

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

            pinteraction->start_destroying_window();

         }

         pinteraction->create_control(pmenu, pitem->m_atom);

         //if (!pinteraction->create_control(pmenu, pitem->m_atom))
         //{

         //   return false;

         //}

         pinteraction->m_pmenuitem = pitem;

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

      return m_pmenuitema.is_set() && m_pmenuitema->get_count() > 0;

   }


   menu_item_ptra::menu_item_ptra(menu_item * pitemParent)
   {

      m_pitemParent = pitemParent;

   }


   menu_item_ptra::~menu_item_ptra()
   {

   }


   menu_item * menu_item::find(atom atom)
   {

      if(m_pmenuitema.is_null())
      {
         return nullptr;

      }

      return m_pmenuitema->find(atom);

   }


   void menu_item::OnAddRef()
   {

   }


   void menu_item::OnRelease()
   {

   }

   menu_item * menu_item_ptra::find(atom atom)
   {

      menu_item * pitemFind;

      for(i32 i = 0; i < this->get_size(); i++)
      {

         menu_item * pitem = element_at(i);

         if(pitem->m_atom  == atom)
         {

            return pitem;

         }

         pitemFind = pitem->find(atom);

         if(pitemFind != nullptr)
         {

            return pitemFind;

         }

      }

      return nullptr;

   }


} // namespace user



