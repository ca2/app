﻿#include "framework.h"
#include "_uwp.h"


namespace uwp
{


   directx_interaction::directx_interaction()
   {

      

   }


   directx_interaction::~directx_interaction()
   {


   }


   void directx_interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_001DrawThis(pgraphics);

   }


   void directx_interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_001DrawChildren(pgraphics);

      ::draw2d::savedc k(pgraphics);

      // while drawing layout can occur and change z-order.
      // keep this past z-order
      ::user::interaction_pointer_array uia = m_uiptraChild;

      for (auto & pinteraction : uia)
      {

         try
         {

            ::draw2d::savedc keep(pgraphics);

            if (!pinteraction->is_custom_draw())
            {

               pinteraction->_000OnDraw1(pgraphics);

            }

         }
         catch (...)
         {

            TRACE("\n\nException thrown while drawing user::interaction\n\n");

         }

      }

   }


   void directx_interaction::_000OnDraw1(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_000OnDraw1(pgraphics);

   }


   void directx_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void directx_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


   bool directx_interaction::is_this_visible()
   {

      return true;

   }


   ::user::interaction* create_host_window()
   {

      return new directx_interaction();

   }


} // namespace uwp



