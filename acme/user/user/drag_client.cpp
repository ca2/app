// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSorensen
#include "framework.h"
#include "drag_client.h"
#include "drag.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/item.h"


namespace user
{


   drag_client::drag_client()
   {


   }


   drag_client::~drag_client()
   {


   }


   void drag_client::destroy()
   {

      ::user::acme_container::destroy();

      for (auto & pair : m_mapDrag)
      {

         if (::is_set(pair.payload()))
         {

            pair.payload().defer_destroy();

         }

      }

      m_mapDrag.clear();

      m_pdragCurrent.release();

   }


   void drag_client::enable_drag(::item * pitem, ::user::e_zorder ezorder)
   {

      auto & pdrag = m_mapDrag[pitem->m_item];

      if (::is_null(pdrag))
      {

         __construct_new(pdrag);

         pdrag->m_pitem = pitem;

         //pdrag->m_item.m_eelement = eelement;
         
         //add_item(pdrag);
         
         user_item(pitem)->m_ezorder = ezorder;

      }

   }


   drag * drag_client::drag(::item * pitem) const
   {

      if (!::is_item_set(pitem))
      {

         return nullptr;

      }

      auto ppair = m_mapDrag.plookup(pitem->m_item);

      if (ppair.is_null())
      {

         return nullptr;

      }

      return ppair->payload();

   }


   bool drag_client::has_drag(::item * pitem) const
   {

      auto pdrag = drag(pitem);

      return ::is_set(pdrag);

   }


   bool drag_client::drag_on_button_down(::item * pitem)
   {

      if (::is_null(pitem))
      {

         return false;

      }

      auto pdrag = drag(pitem);

      //for (auto & pair : m_mapDrag)
      //{

      //   auto & pdrag = pair.payload();
      //   
      //   if (::is_set(pdrag) && pitemButtonDown->m_item.m_eelement == pdrag->m_item.m_eelement)
      //   {
      if(::is_set(pdrag))
      {

         if (pitem->m_item.m_eelement == e_element_resize)
         {

            information() << "drag_on_button_down element_resize";

         }

         auto puseritem = user_item(pitem);

         if(drag_on_button_down(pitem, puseritem->m_pmouse))
         {

            return true;

         }

      }

      //}

      return false;

   }


   bool drag_client::drag_on_button_down(::item * pitem, ::user::mouse * pmouse)
   {

      auto pdrag = drag(pitem);

      if (pdrag)
      {

         pdrag->m_pmouse = pmouse;

         ::point_i32 pointDrag;
         
         if (on_drag_start(pointDrag, pitem))
         {

            drag_set_capture();

            pdrag->drag_start(pmouse, this, pitem, pointDrag);

            m_pdragCurrent = pdrag;

            return true;

         }

      }

      return false;

   }


   bool drag_client::drag_on_mouse_move(::user::mouse * pmouse)
   {

      _synchronous_lock _synchronouslock(this->synchronization());

      if (m_pdragCurrent)
      {

         ASSERT(m_pdragCurrent->m_bLButtonDown);

         if (m_pdragCurrent->m_bLButtonDown)
         {

            m_pdragCurrent->m_pmouse = pmouse;

            //set_cursor(e_cursor_move);

            //auto integral_milliseconds = integral_millisecond(now_t{});

            //string str;
            //str.formatf("e_mouse_move=-=%lldms\n", integral_milliseconds.m_i);

            //information(str);

            if (!m_pdragCurrent->m_bDrag)
            {

               auto pdrag = m_pdragCurrent;

               _synchronouslock.unlock();

               pdrag->m_bDrag = true;

               drag_shift(pdrag->m_pitem, pmouse);

               if (pdrag->m_ecursor != e_cursor_none)
               {

                     drag_set_cursor(pdrag->m_pitem);

               }

               pdrag->m_bDrag = false;

               return true;

            }

         }

      }

      return false;

   }


   bool drag_client::drag_on_mouse_hover(::item * pitem)
   {

      if (::is_null(pitem))
      {

         return false;

      }

      auto pdrag = drag(pitem);

      if (pdrag)
      {


      //for (auto & pair : m_mapDrag)
      //{

      //   auto & pdrag = pair.payload();

      //   if (::is_set(pdrag) && pitemButtonHover->m_item.m_eelement == pdrag->m_item.m_eelement)
      //   {

            auto * puseritem = user_item(pitem);

            pdrag->m_pmouse = puseritem->m_pmouse;

            bool bRet = drag_hover(pitem);

            if (pdrag->m_ecursor != e_cursor_none)
            {

               drag_set_cursor(pitem);

            }

            return bRet;

         //}

      }

      return false;

   }


   bool drag_client::drag_on_button_up(::user::mouse * pmouse)
   {

      if (::is_null(m_pdragCurrent))
      {

         return false;

      }

      ASSERT(m_pdragCurrent->m_bLButtonDown || m_pdragCurrent->m_bDrag);

      m_pdragCurrent->m_pmouse = pmouse;

      drag_release_capture();

      //drag_shift(m_pdragCurrent->m_pitem);

      m_pdragCurrent->drag_end();

      m_pdragCurrent.release();

      return true;

   }


   //bool drag_client::on_drag(::user::drag * pdrag, const ::point_i32 & point)
   //{

   //   return false;

   //}


   ::point_i32 drag_client::drag_point(::item * pitem, ::user::mouse * pmouse)
   {

      auto pdrag = drag(pitem);

      //auto pointLButtonDown2 = drag_mouse_cursor_position(pitem, pdrag->m_pointLButtonDown2);

      auto Δ = pdrag->m_pointLButtonDown2 - pdrag->m_pointInitial;

      auto pointCursor = drag_mouse_cursor_position(pitem, pmouse->m_pointAbsolute);

      auto pointDrag = pointCursor - Δ;

      information() << "drag_client::drag_point";
      information() << "pointLButtonDown2 : " << pdrag->m_pointLButtonDown2;
      information() << "pointInitial : " << pdrag->m_pointInitial;
      information() << "pointAbsolute : " << pmouse->m_pointAbsolute;
      information() << "pointCursor : " << pointCursor;
      information() << "pointDrag : " << pointDrag;

      return pointDrag;

   }


} // namespace user



