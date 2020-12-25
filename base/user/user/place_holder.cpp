#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


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

      MESSAGE_LINK(e_message_show_window, pchannel, this, &place_holder::_001OnShowWindow);

   }


   void place_holder::_001OnShowWindow(::message::message * /* pmessage */ )
   {


   }


   bool place_holder::can_merge(::user::interaction * pinteraction)
   {

      auto puiptraChild = m_puiptraChild;

      if (puiptraChild->contains_interaction(pinteraction))
      {

         return false;

      }

      //auto puiptraChild = m_puiptraChild;
      if (puiptraChild->has_no_interaction())
      {

         return false;

      }

      return puiptraChild->first_interaction()->can_merge(pinteraction);

   }


   bool place_holder::merge(::user::interaction * pinteraction)
   {

      //sync_lock sl(mutex_children());

      if (!can_merge(pinteraction))
      {

         return false;

      }

      auto puiptraChild = m_puiptraChild;

      if (!puiptraChild->first_interaction()->merge(pinteraction))
      {

         return false;

      }

      return true;

   }


   bool place_holder::is_place_holding(::user::interaction * pinteraction)
   {

      auto puiptraChild = m_puiptraChild;
      return puiptraChild->contains_interaction(pinteraction);

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

      {

         //sync_lock sl(mutex_children());

         auto puiptraChild = m_puiptraChild;

         if (!puiptraChild)
         {

            return nullptr;

         }

         if (puiptraChild->contains_interaction(puiChild))
         {

            return this;

         }

         //auto puiptraChild = m_puiptraChild;

         for (auto & puiChildOld : puiptraChild->interactiona())
         {

            Application.place_hold(puiChildOld);

         }

         m_puiptraChild.release();

      }

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

      auto puiptraChild = m_puiptraChild;

      if (!puiptraChild || puiptraChild->has_no_interaction())
      {

         return;

      }

      auto rectClient = get_client_rect();

      if (rectClient.is_empty())
      {

         return;

      }

      auto puiChild = puiptraChild->first_interaction();

      puiChild->start_layout();

      puiChild->place(rectClient);

      puiChild->layout().sketch().set_modified();

      puiChild->display();

      puiChild->set_reposition();

      puiChild->set_need_layout();

      puiChild->set_need_redraw();

      puiChild->set_layout_ready();

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

      auto puiptraChild = m_puiptraChild;

      if (puiptraChild->has_no_interaction())
      {

         return nullptr;

      }

      return puiptraChild->first_interaction();

   }


   void place_holder::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void place_holder::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      auto puiptraChild = m_puiptraChild;

      if(puiptraChild->interaction_count() >= 2)
      {

         output_debug_string("place_holder with more than one child : what?!?!");

      }

      if(puiptraChild->has_interaction())
      {

         puiptraChild->first_interaction()->_000CallOnDraw(pgraphics);

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


   void place_holder::get_child_rect(RECT32* prect)
   {

      GetParent()->get_child_rect(prect);

      offset(prect, -prect->left, -prect->top);

   }


} // namespace user



