// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSørensen
#include "framework.h"
#include "drag.h"


namespace user
{


   drag::drag()
   {

      m_eelement = e_element_none;

      m_ecursor = e_cursor_none;

      m_bDrag = false;

      m_bLButtonDown = false;

      m_pmouse = nullptr;

   }


   drag::~drag()
   {


   }


   void drag::start(::user::mouse * pmouse, const ::point_i32 & pointDrag)
   {

      m_pmouse = pmouse;

      m_bLButtonDown = true;

      m_bDrag = false;

      m_pointLButtonDown = m_pmouse->m_point;

      m_sizeLButtonDownOffset = m_pointLButtonDown - pointDrag;

   }


   void drag::end()
   {

      m_bLButtonDown = false;

      m_bDrag = false;

      m_pmouse.release();

   }


   ::point_i32 drag::point() const
   {

      auto pointDrag = m_pmouse->m_point - m_sizeLButtonDownOffset;

      return pointDrag;

   }


      
      
   drag_client::drag_client()
   {


   }


   drag_client::~drag_client()
   {


   }


   void drag_client::destroy()
   {

      for (auto & pdrag : m_mapDrag.values())
      {

         if (::is_set(pdrag))
         {

            pdrag->destroy();

         }

      }

      m_mapDrag.clear();

   }


   void drag_client::enable_drag(::e_element eelement)
   {

      auto & pdrag = m_mapDrag[eelement];

      if (::is_null(pdrag))
      {

         __construct_new(pdrag);

         pdrag->m_eelement = eelement;

      }

   }

   
   drag * drag_client::drag(::e_element eelement) const
   {

      auto p = m_mapDrag.plookup(eelement);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2.m_p;

   }


   bool drag_client::has_drag(::e_element eelement) const
   {

      auto pdrag = drag(eelement);

      return ::is_set(pdrag);

   }


   bool drag_client::drag_on_button_down(::item * pitemButtonDown)
   {

      if (::is_null(pitemButtonDown))
      {

         return false;

      }

      for (auto & pdrag : m_mapDrag.values())
      {

         if (::is_set(pdrag) && pitemButtonDown->m_eelement == pdrag->m_eelement)
         {

            if(pdrag->m_eelement == e_element_resize)
            {

               INFORMATION("drag_on_button_down element_resize");

            }

            drag_on_button_down(pdrag, pitemButtonDown->m_pmouse);

            return true;

         }

      }

      return false;

   }


   void drag_client::drag_on_button_down(::user::drag * pdrag, ::user::mouse * pmouse)
   {

      drag_set_capture();
       
      pdrag->m_pmouse = pmouse;

      auto pointDrag = on_drag_start(pdrag);

      pdrag->start(pmouse, pointDrag);

      m_pdragCurrent = pdrag;

   }


   bool drag_client::drag_on_mouse_move(::user::mouse * pmouse)
   {

      if(m_pdragCurrent)
      {

         ASSERT(m_pdragCurrent->m_bLButtonDown);

         if (m_pdragCurrent->m_bLButtonDown)
         {

            m_pdragCurrent->m_pmouse = pmouse;

            //set_cursor(e_cursor_move);

            //auto integral_milliseconds = integral_millisecond(e_now);

            //string str;
            //str.format("e_mouse_move=-=%lldms\n", integral_milliseconds.m_i);

            //output_debug_string(str);

            if (!m_pdragCurrent->m_bDrag)
            {

               m_pdragCurrent->m_bDrag = true;

               auto pointDrag = pmouse->m_point - m_pdragCurrent->m_sizeLButtonDownOffset;

               drag_shift(m_pdragCurrent);

               if (m_pdragCurrent->m_ecursor != e_cursor_none)
               {

                  drag_set_cursor(m_pdragCurrent);

               }

               m_pdragCurrent->m_bDrag = false;

               return true;

            }

         }

      }

      return false;

   }


   bool drag_client::drag_on_mouse_hover(::item * pitemButtonHover)
   {

      if (::is_null(pitemButtonHover))
      {

         return false;

      }

      for (auto & pdrag : m_mapDrag.values())
      {

         if (::is_set(pdrag) && pitemButtonHover->m_eelement == pdrag->m_eelement)
         {

            pdrag->m_pmouse = pitemButtonHover->m_pmouse;

            drag_hover(pdrag);

            if (pdrag->m_ecursor != e_cursor_none)
            {

               drag_set_cursor(pdrag);

            }

            return false;

         }

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

      drag_shift(m_pdragCurrent);

      m_pdragCurrent->end();

      m_pdragCurrent.release();

      return true;

   }


   //bool drag_client::on_drag(::user::drag * pdrag, const ::point_i32 & point)
   //{

   //   return false;

   //}


} // namespace user



