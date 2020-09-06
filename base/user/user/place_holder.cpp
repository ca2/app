#include "framework.h"


namespace user
{


   place_holder::place_holder()
   {

      m_flagNonClient.remove(non_client_background);
      m_flagNonClient.remove(non_client_focus_rect);

   }


   place_holder::~place_holder()
   {

   }


   void place_holder::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &place_holder::_001OnShowWindow);

   }


   void place_holder::_001OnShowWindow(::message::message * /* pmessage */ )
   {

      //SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      
   }


   bool place_holder::can_merge(::user::interaction * pinteraction)
   {

      if (m_uiptraChild.contains(pinteraction))
      {

         return false;

      }

      if (m_uiptraChild.is_empty())
      {

         return false;

      }

      return m_uiptraChild[0]->can_merge(pinteraction);

   }


   bool place_holder::merge(::user::interaction * pinteraction)
   {

      if (!can_merge(pinteraction))
      {

         return false;

      }

      if (!m_uiptraChild[0]->merge(pinteraction))
      {

         return false;

      }

      return true;

   }


   bool place_holder::is_place_holding(::user::interaction * pinteraction)
   {

      return m_uiptraChild.contains(pinteraction);

   }


   void place_holder::on_remove_child(::user::interaction * pinteraction)
   {

      if (GetParent() != nullptr)
      {

         GetParent()->on_remove_place_holder_child(pinteraction);

      }

   }


   void place_holder::on_hide_child(::user::interaction * pinteraction)
   {

      if (GetParent() != nullptr)
      {

         GetParent()->on_hide_place_holder_child(pinteraction);

      }

   }


   __pointer(place_holder) place_holder::place_hold(::user::interaction * puiChild)
   {

      if (m_uiptraChild.contains(puiChild))
      {

         return this;

      }

      for (auto & puiChildOld : m_uiptraChild.ptra())
      {

         Application.place_hold(puiChildOld);

      }

      m_uiptraChild.remove_all();

      if (puiChild == nullptr)
      {

         return this;

      }

      puiChild->SetParent(this);

      return this;

   }


   bool place_holder::unplace(::user::interaction * pinteraction)
   {

      return Application.place_hold(pinteraction) != nullptr;

   }


   void place_holder::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_uiptraChild.is_empty())
      {

         return;

      }

      auto rectClient = get_client_rect();

      if (rectClient.is_empty())
      {

         return;

      }

      auto puiChild = m_uiptraChild[0];

      puiChild->place(rectClient);

      puiChild->display();

   }


   bool place_holder::create_window(::user::place_holder_container * pcontainer,id id)
   {

      return ::user::interaction::create_window(pcontainer, id) != FALSE;

   }


   __pointer(place_holder) place_holder::create_shadow_clone()
   {

      __pointer(place_holder) pholder = __new(place_holder);

      if(pholder.is_null())
      {

         return nullptr;

      }

      if(!pholder->::user::interaction::create_window(GetParent(),m_id))
      {

         return nullptr;

      }

      return pholder;

   }


   interaction * place_holder::get_hold()
   {

      if(m_uiptraChild.get_count() <= 0)
         return nullptr;

      return m_uiptraChild[0];

   }


   void place_holder::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      //on_viewport_offset(pgraphics);
      //UNREFERENCED_PARAMETER(pgraphics);

   }


   void place_holder::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {
    
      if(m_uiptraChild.get_size() >= 2)
      {
         
         output_debug_string("place_holder with more than one child : what?!?!");
         
      }
      
      if(m_uiptraChild.has_element())
      {
      
         m_uiptraChild[0]->_000CallOnDraw(pgraphics);
         
      }
   
   }


   void place_holder::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }

   void place_holder::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   i32 place_holder_ptra::place_hold(::user::interaction * pinteraction)
   {

      i32 count = 0;

      for(i32 i = 0; i < this->get_count(); i++)
      {

         try
         {

            if(this->element_at(i)->place_hold(pinteraction))
            {

               count++;

            }

         }
         catch(...)
         {

         }

      }

      return count;

   }


   i32 place_holder_ptra::unplace(::user::interaction * pinteraction)
   {

      i32 count = 0;

      for(i32 i = 0; i < this->get_count(); i++)
      {
         try
         {
            if(this->element_at(i)->unplace(pinteraction))
            {
               count++;
            }
         }
         catch(...)
         {
         }
      }

      return count;

   }

   bool place_holder::is_place_holder()
   {
      return true;
   }

   bool place_holder::_001IsBackgroundBypass()
   {

      return true;

   }


   void place_holder::route_command_message(::user::command * pcommand)
   {

      // then pump through frame
      ::user::interaction::route_command_message(pcommand);

      if(pcommand->m_bRet)
         return;

      // then pump through parent
      __pointer(::user::interaction) puiParent = GetParent();

      if (puiParent != nullptr)
      {

         puiParent->route_command_message(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

   }

   
   void place_holder::get_child_rect(RECT* prect)
   {

      GetParent()->get_child_rect(prect);

      offset(prect, -prect->left, -prect->top);

   }


} // namespace user



