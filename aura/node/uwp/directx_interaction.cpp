#include "framework.h"
#include "_uwp.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"


namespace universal_windows
{


   directx_interaction::directx_interaction()
   {

   }


   directx_interaction::~directx_interaction()
   {


   }


   bool directx_interaction::is_host_top_level() const
   {

      return true;

   }


   bool directx_interaction::is_os_host() const
   {

      return true;

   }


   void directx_interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_001DrawThis(pgraphics);

   }


   void directx_interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         if (m_puserinteractionpointeraChild && m_puserinteractionpointeraChild->has_interaction())
         {

            try
            {

               _001DrawChildren(pgraphics);

            }
            catch (...)
            {

               TRACE("Exception: interaction::_000OnDraw _001DrawChildren %s", typeid(*this).name());

            }

         }

      }
      catch (...)
      {

      }

   }


   void directx_interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::interaction::_001DrawChildren(pgraphics);

      ::draw2d::savedc k(pgraphics);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      // while drawing layout can occur and change z-order.
      // keep this past z-order
      auto uia = puserinteractionpointeraChild->m_interactiona;

      for (auto & pinteraction : uia)
      {

         try
         {

            ::draw2d::savedc keep(pgraphics);

            if (!pinteraction->is_custom_draw())
            {

               pinteraction->_000OnDraw(pgraphics);

            }

         }
         catch (...)
         {

            TRACE("\n\nException thrown while drawing user::interaction\n\n");

         }

      }

   }


   void directx_interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void directx_interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


   bool directx_interaction::is_this_visible(::user::enum_layout elayout)
   {

      return true;

   }


   ::user::interaction* create_host_window()
   {

      return new directx_interaction();

   }


} // namespace universal_windows



