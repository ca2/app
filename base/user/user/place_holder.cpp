#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   place_holder::place_holder()
   {

      m_flagNonClient.erase(non_client_background);
      m_flagNonClient.erase(non_client_focus_rect);

   }


   place_holder::~place_holder()
   {

   }


   void place_holder::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &place_holder::on_message_show_window);

   }


   void place_holder::on_message_show_window(::message::message * /* pmessage */ )
   {


   }


   bool place_holder::can_merge(::user::interaction * pinteraction)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      if (puserinteractionpointeraChild->contains_interaction(pinteraction))
      {

         return false;

      }


      return puserinteractionpointeraChild->first_interaction()->can_merge(pinteraction);

   }


   bool place_holder::merge(::user::interaction * pinteraction)
   {

      //synchronous_lock synchronouslock(mutex_children());

      if (!can_merge(pinteraction))
      {

         return false;

      }

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild->first_interaction()->merge(pinteraction))
      {

         return false;

      }

      return true;

   }


   bool place_holder::is_place_holding(::user::interaction * pinteraction)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
      return puserinteractionpointeraChild->contains_interaction(pinteraction);

   }


   void place_holder::on_erase_child(::user::interaction * pinteraction)
   {

      if (get_parent() != nullptr)
      {

         get_parent()->on_erase_place_holder_child(pinteraction);

      }

   }


   void place_holder::on_hide_child(::user::interaction * pinteraction)
   {

      if (get_parent() != nullptr)
      {

         get_parent()->on_hide_place_holder_child(pinteraction);

      }

   }


   __pointer(place_holder) place_holder::place_hold(::user::interaction * puiChild)
   {

      if (::is_null(puiChild))
      {

         return this;

      }

      __pointer(::base::application) papplication = get_application();

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (puserinteractionpointeraChild)
      {

         if (puserinteractionpointeraChild->contains_interaction(puiChild))
         {

            return this;

         }

         for (auto & puiChildOld : puserinteractionpointeraChild->interactiona())
         {

            papplication->place_hold(puiChildOld);

         }

         m_puserinteractionpointeraChild.release();


      }

      puiChild->set_parent(this);

      return this;

   }


   bool place_holder::unplace(::user::interaction * pinteraction)
   {

      __pointer(::base::application) papplication = get_application();

      return papplication->place_hold(pinteraction) != nullptr;

   }


   void place_holder::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild || puserinteractionpointeraChild->has_no_interaction())
      {

         return;

      }

      auto rectangleClient = get_client_rect();

      if (rectangleClient.is_empty())
      {

         return;

      }

      {

         auto puiChild = puserinteractionpointeraChild->first_interaction();

         lock_sketch_to_design lockSketchToDesign(puiChild);

         puiChild->place(rectangleClient);

         puiChild->display();

         puiChild->set_reposition();

         puiChild->set_need_layout();

         puiChild->set_need_redraw();

      }

   }


   //bool place_holder::create_interaction(::user::place_holder_container * pcontainer,id id)
   //{

   //   return ::user::interaction::create_interaction(pcontainer, id) != false;

   //}


   __pointer(place_holder) place_holder::create_shadow_clone()
   {

      __pointer(place_holder) pholder = __new(place_holder);

      if(pholder.is_null())
      {

         return nullptr;

      }

      if(!pholder->::user::interaction::create_child(get_parent()))
      {

         return nullptr;

      }

      return pholder;

   }


   interaction * place_holder::get_hold()
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild || puserinteractionpointeraChild->has_no_interaction())
      {

         return nullptr;

      }

      return puserinteractionpointeraChild->first_interaction();

   }


   void place_holder::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void place_holder::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if(puserinteractionpointeraChild->interaction_count() >= 2)
      {

         output_debug_string("place_holder with more than one child : what?!?!");

      }

      if(puserinteractionpointeraChild->has_interaction())
      {

         puserinteractionpointeraChild->first_interaction()->_000CallOnDraw(pgraphics);

      }

   }


   void place_holder::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   void place_holder::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

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


   void place_holder::route_command_message(::message::command * pcommand)
   {

      // then pump through frame
      ::user::interaction::route_command_message(pcommand);

      if(pcommand->m_bRet)
         return;

      // then pump through parent
      __pointer(::user::interaction) puiParent = get_parent();

      if (puiParent != nullptr)
      {

         puiParent->route_command_message(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

   }


   void place_holder::get_child_rect(RECTANGLE_I32* prectangle)
   {

      get_parent()->get_child_rect(prectangle);

      offset(prectangle, -prectangle->left, -prectangle->top);

   }


} // namespace user



