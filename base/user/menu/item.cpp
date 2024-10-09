#include "framework.h"
#include "acme/constant/id.h"
#include "axis/platform/application.h"
#include "aqua/xml/document.h"
#include "aura/graphics/image/context.h"
#include "apex/message/command.h"
#include "item.h"
#include "aura/user/user/interaction.h"
#include "axis/user/user/user.h"
#include "base/user/menu/menu.h"
#include "item_ptra.h"


class menu_item_command : public ::message::command        // class private to this file !
{
public: // re-implementations only

   menu_item_command(::particle * pparticle);
   void enable(bool bOn = true, const ::action_context & context = ::e_source_system) override;
   //   virtual void set_check(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
   //void set_check(const e_check & echeck, const ::action_context & context = ::e_source_system) override;   // 0, 1 or 2 (indeterminate)
//   virtual void SetRadio(bool bOn = true, const ::action_context & context = ::e_source_system);
   //void set_text(const ::string & pszText, const ::action_context & context = ::e_source_system) override;

};



namespace menu
{


   item::item()
   {

      m_puserinteractionHost = nullptr;
      m_bBreak = false;
      m_puserinteraction = nullptr;
      m_pmenuitema = __new item_ptra(this);
      m_iLevel = 0;
      m_bPopup = false;
      m_item.m_eelement = e_element_item;

   }


   item::~item()
   {

      informationf("item::~item (1)");
      informationf("item::~item (2)");
      informationf("item::~item (3)");

   }


   ::collection::count item::get_separator_item_count()
   {
    
      if(!m_pmenuitema)
      {
       
         return 0;
         
      }
      
      ::collection::count cSeparator = 0;
      
      for(auto & pmenuitem : *m_pmenuitema)
      {
       
         if(pmenuitem->is_separator())
         {
          
            cSeparator++;
            
         }
         
      }
      
      return cSeparator;
      
   }


   ::collection::count item::get_full_height_item_count()
   {
    
      if(!m_pmenuitema)
      {
       
         return 0;
         
      }
      
      ::collection::count cFullItemHeight = 0;
      
      for(auto & pmenuitem : *m_pmenuitema)
      {
       
         if(!pmenuitem->is_separator())
         {
          
            cFullItemHeight++;
            
         }
         
      }
      
      return cFullItemHeight;
      
   }


   bool item::create_menu(const string_array & straCommand, const string_array & straCommandTitle)
   {

      ::collection::count iItemCount = straCommand.get_count();

      if (straCommandTitle.get_size() < straCommand.get_size())
         return false;

      for (i32 i = 0; i < iItemCount; i++)
      {
         string strCommand = straCommand[i];
         string strCommandTitle = straCommandTitle[i];
         auto pitemNewChild = __new item();
         pitemNewChild->m_bPopup = false;
         if (strCommand.is_empty())
         {
            pitemNewChild->m_atom = id_separator;
         }
         else
         {
            pitemNewChild->m_atom = strCommand;
            pitemNewChild->m_iLevel = 0;
            pitemNewChild->m_puserinteraction->set_window_text(strCommandTitle);
         }
         add_item(pitemNewChild);
      }

      return iItemCount > 0;

   }


   void item::menu_item_destruct()
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

   bool item::load_menu(::xml::node * pnode)
   {

      return load_menu(pnode, m_iLevel);

   }


   item * item::separator()
   {

   auto pitem = __create_new<item>();

   pitem->m_atom = id_separator;

   pitem->m_pmenu = m_pmenu;

   add_item(pitem);

   return pitem;

}



   bool item::load_menu(::xml::node * pnode, i32 iLevel)
   {

      ::collection::count iItemCount = pnode->get_children_count();

      //::pointer<::axis::application>papp = get_app();

      m_bPopup = pnode->get_children_count() > 0 && pnode->get_name() == "menubar";

      if(pnode->get_name() == "separator")
      {

         m_atom = id_separator;

      }
      else
      {

         auto atom = pnode->attribute("id").as_atom();

         //atom = translate_property_id(atom);

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

            __construct(m_pimage, image()->matter_image(strImage));

         }

      }

      for (i32 i = 0; i < iItemCount; i++)
      {

         auto pnodeChild = pnode->child_at(i);

         auto pitemNewChild = __create_new<item>();

         pitemNewChild->m_pmenu = m_pmenu;

         pitemNewChild->load_menu(pnodeChild);

         add_item(pitemNewChild);

      }

      return true;

   }


   void item::add_item(item * pitem)
   {

      pitem->m_pmenuitemParent = this;

      m_pmenuitema->add(pitem);

   }


   bool item::contains_menu_item(item * pitem, bool bRecursive) const
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




   bool item::is_popup() const
   {

      return m_bPopup 
      || (m_pmenuitema.is_set() && m_pmenuitema->has_element());

   }


   bool item::is_separator() const
   {

      return m_atom == id_separator;

   }


   void item::release_children_interaction()
   {

      for (auto & pitem : *m_pmenuitema)
      {

         if (pitem)
         {

            try
            {

               pitem->release_children_interaction();

            }
            catch (...)
            {

            }

            if (pitem->m_puserinteraction)
            {

               try
               {

                  pitem->m_puserinteraction->set_finish();

                  pitem->m_puserinteraction.release();

               }
               catch (...)
               {

               }

            }

         }

      }

   }


   item_ptra::item_ptra(item * pitemParent)
   {

      m_pitemParent = pitemParent;

   }


   item_ptra::~item_ptra()
   {

   }


   item * item::find(const atom & atom)
   {

      if(m_pmenuitema.is_null())
      {
         return nullptr;

      }

      return m_pmenuitema->find(atom);

   }


   //void item::OnAddRef()
   //{

   //}


   //void item::OnRelease()
   //{

   //}


   item * item_ptra::find(const ::atom & atom)
   {

      item * pitemFind;

      for(i32 i = 0; i < this->get_size(); i++)
      {

         item * pitem = element_at(i);

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


   bool item::create_buttons(::draw2d::graphics_pointer & pgraphics, ::user::menu * pusermenu)
   {

      ::user::style_pointer pstyle;

      for (i32 iItem = 0; iItem < m_pmenuitema->get_size(); iItem++)
      {

         auto pitem = m_pmenuitema->element_at(iItem);
         
         if (!pitem)
         {

            continue;

         }

         if (pitem->is_separator())
         {

            continue;

         }

         ::pointer<::user::interaction>pinteraction = pitem->m_puserinteraction;

         if (pinteraction.is_null())
         {

            pinteraction = user()->m_paxisuser->create_menu_button(m_pmenu, pgraphics, pitem);

         }

         if (pinteraction.is_null())
         {

            return false;

         }

         if (pinteraction->is_window())
         {

            pinteraction->start_destroying_window();

         }

         pinteraction->create_control(pusermenu, pitem->m_atom);

         //if (!pinteraction->create_control(pmenu, pitem->m_atom))
         //{

         //   return false;

         //}

         pinteraction->m_pmenuitem = pitem;

         if (!pinteraction->is_window())
         {

            return false;

         }

         pitem->m_pmenu = pusermenu;

         pinteraction->set_window_text(pitem->m_strTitle);

         if(pusermenu->m_bInline)
         {

            pitem->create_buttons(pgraphics, pusermenu);

         }

         pitem->m_puserinteraction = pinteraction;

      }

      return true;

   }


} // namespace user



