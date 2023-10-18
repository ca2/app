#include "framework.h"
#include "place_holder.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/interaction_array.h"


namespace user
{


   place_holder::place_holder()
   {

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);
      m_bDefaultClickHandling = false;

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


   bool place_holder::on_add_child(::user::interaction * puserinteractionChild)
   {

      //if (m_puserinteractionpointeraChild)
      //{

      //   if(m_puserinteractionpointeraChild->interaction_count() == 1
      //   && m_puserinteractionpointeraChild->first_interaction() == puserinteractionChild)
      //   {

      //      return true;

      //   }
      //   else if (m_puserinteractionpointeraChild->interaction_count() == 1)
      //   {

      //      ::pointer<::user::interaction>puserinteractionOld = m_puserinteractionpointeraChild->first_interaction();

      //      puserinteractionChild->m_pinteractionScaler = m_pinteractionScaler;

      //      m_puserinteractionpointeraChild->m_interactiona.set_at(0, puserinteractionChild);

      //      if (puserinteractionOld)
      //      {

      //         puserinteractionOld->m_puserinteraction->m_puserinteractionParent.release();

      //         ::pointer<::user::interaction>puserinteractionParent = this;

      //         auto pimpact = puserinteractionChild->cast < ::user::impact>();

      //         if (pimpact)
      //         {

      //            while (puserinteractionParent)
      //            {

      //               ::pointer<::user::frame>pframe = puserinteractionParent;

      //               if (pframe)
      //               {

      //                  if (pframe->get_active_impact() == puserinteractionOld)
      //                  {

      //                     pframe->set_active_impact(pimpact);

      //                  }

      //               }

      //               puserinteractionParent = puserinteractionParent->get_parent();

      //            }

      //         }


      //         puserinteractionOld->set_finish();

      //      }

      //      return true;

      //   }
      //   else if(m_puserinteractionpointeraChild->interaction_count() > 1)
      //   {

      //      throw ::exception(error_wrong_state);

      //   }

      //}

      auto bOk = ::user::interaction::on_add_child(puserinteractionChild);

      if(!bOk)
      {

         return false;

      }

      puserinteractionChild->m_bExtendOnParentHostingArea = true;

      return true;

   }


   bool place_holder::can_merge(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(this->synchronization());

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

      synchronous_lock synchronouslock(this->synchronization());

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

      synchronous_lock synchronouslock(this->synchronization());

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
      return puserinteractionpointeraChild->contains_interaction(pinteraction);

   }


   bool place_holder::is_this_visible(enum_layout elayout)
   {

      return ::user::interaction::is_this_visible(elayout);

//      if (!m_pimpl)
//      {
//
//         return false;
//
//      }
//
//      if(!m_puserinteractionpointeraChild)
//      {
//
//         return false;
//
//      }
//
//      if(m_puserinteractionpointeraChild->interaction_count() != 1)
//      {
//
//         return false;
//
//      }
//
//      auto puserinteraction = m_puserinteractionpointeraChild->first_interaction();
//
//      if(::is_null(puserinteraction))
//      {
//
//         return false;
//
//      }
//
//      return puserinteraction->is_this_visible();

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


   ::pointer<place_holder>place_holder::place_hold(::user::interaction * puiChild)
   {

      if (::is_null(puiChild))
      {

         return this;

      }

      /*::pointer<::base::application>papp = get_app();

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (puserinteractionpointeraChild)
      {

         if (puserinteractionpointeraChild->contains_interaction(puiChild))
         {

            return this;

         }

         for (auto & puiChildOld : puserinteractionpointeraChild->interactiona())
         {

            papp->place_hold(puiChildOld);

         }

         m_puserinteractionpointeraChild.release();


      }*/

      puiChild->set_parent(this);

      return this;

   }


   bool place_holder::unplace(::user::interaction * pinteraction)
   {
      
      synchronous_lock synchronouslock(this->synchronization());

      if (m_puserinteractionpointeraChild)
      {

         m_puserinteractionpointeraChild->erase_interaction(pinteraction);

      }

      return true;

      //::pointer<::base::application>papp = get_app();

      //return papp->place_hold(pinteraction) != nullptr;

   }


   void place_holder::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild || puserinteractionpointeraChild->has_no_interaction())
      {

         return;

      }

      auto rectangle = this->rectangle(e_layout_layout);

      if (rectangle.is_set())
      {

         //if (m_rectangleClient2 != rectangle)
         //{

         //   m_rectangleClient2 = rectangle;

         //}

         for (auto & puiChild : puserinteractionpointeraChild->interactiona())
         {

            synchronouslock.unlock();

            //auto puiChild = puserinteractionpointeraChild->first_interaction();

            //lock_sketch_to_design lockSketchToDesign(puiChild);

            puiChild->place(rectangle);

            if (puserinteractionpointeraChild->interaction_count() == 1
               && !puiChild->is_this_visible())
            {

               puiChild->display();

            }

            puiChild->set_reposition();

            puiChild->set_need_layout();

            puiChild->set_need_redraw({rectangle}, pgraphics);

            synchronouslock.lock();

         }

      }

   }


   //bool place_holder::create_interaction(::user::place_holder_container * pcontainer,atom atom)
   //{

   //   return ::user::interaction::create_interaction(pcontainer, atom) != false;

   //}


   ::pointer<place_holder>place_holder::create_shadow_clone()
   {

      ::pointer<place_holder>pholder = __new(place_holder);

      if(pholder.is_null())
      {

         return nullptr;

      }

      pholder->::user::interaction::create_child(get_parent());

      //if(!pholder->::user::interaction::create_child(get_parent()))
      //{

      //   return nullptr;

      //}

      return pholder;

   }


   interaction * place_holder::get_hold()
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild || puserinteractionpointeraChild->has_no_interaction())
      {

         return nullptr;

      }

      for (auto & puiChild : puserinteractionpointeraChild->interactiona())
      {

         if (puiChild->is_this_visible())
         {

            return puiChild;

         }

      }

      return puserinteractionpointeraChild->first_interaction();

   }


   void place_holder::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void place_holder::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {


      ::user::interaction::_001DrawChildren(pgraphics);
      //auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      ////if(puserinteractionpointeraChild->interaction_count() >= 2)
      ////{

      ////   information("place_holder with more than one child : what?!?!");

      ////}

      //if(puserinteractionpointeraChild->has_interaction())
      //{

      //   puserinteractionpointeraChild->first_interaction()->_000CallOnDraw(pgraphics);

      //}

   }


   void place_holder::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   void place_holder::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
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


   void place_holder::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      // then pump through frame
      ::user::interaction::route_command(pcommand, true);

      if(pcommand->m_bRet)
         return;

      // then pump through parent
      ::pointer<::user::interaction>puiParent = get_parent();

      if (puiParent != nullptr)
      {

         puiParent->route_command(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

   }


   void place_holder::get_child_rect(::rectangle_i32 & rectangle)
   {

      get_parent()->get_child_rect(rectangle);

      offset(rectangle, -rectangle.left(), -rectangle.top());

   }


} // namespace user



