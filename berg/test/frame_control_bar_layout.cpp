#include "berg/platform.h"
#include "berg/user/user/frame_window.h"
#include "berg/user/user/impact.h"
#include "berg/user/user/control_bar.h"
#include "aura/user/user/size_parent_layout.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "acme/constant/user_message.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"

namespace
{
   class layout_frame : public ::user::frame_window
   {
   public:
      ::user::interaction * m_pbar = nullptr;
      bool _is_window() const override { return true; }
      ::user::interaction * first_child() override { return m_pbar; }
      ::user::interaction * next_sibling(::user::interaction * pchild) override
      {
         return pchild == m_pbar ? m_pimpactMain.m_p : nullptr;
      }
   };

   class layout_impact : public ::user::impact
   {
   public:
      ::user::interaction * m_pframe = nullptr;
      ::i32_rectangle m_rectanglePlaced;
      int m_iPlacements = 0;
      ::user::interaction * get_parent() override { return m_pframe; }
      void place(const ::i32_rectangle & rectangle, ::user::enum_layout, ::draw2d::graphics *) override
      {
         m_rectanglePlaced = rectangle;
         ++m_iPlacements;
      }
      ::i32_rectangle parent_client_rectangle(::user::enum_layout) override { return m_rectanglePlaced; }
      void display(::e_display, const ::user::activation &) override {}
      void set_need_layout() override {}
   };

   class layout_bar : public ::user::control_bar
   {
   public:
      int m_iHeight = 36;
      bool m_bVisible = true;
      void on_command_probe(::user::interaction *, bool) override {}
      lresult call_route_message(::user::enum_message emessage, ::wparam, ::lparam lparam) override
      {
         if (emessage == ::user::e_message_size_parent && m_bVisible)
         {
            auto playout = reinterpret_cast<size_parent_layout *>(lparam.m_lparam);
            playout->m_rectangle.top += m_iHeight;
            playout->m_sizeTotal.cy += m_iHeight;
         }
         return 0;
      }
   };
}

int main()
{
   ::platform::system testSystem;
   ::pointer < layout_frame > pframe(allocate_t{});
   ::pointer < layout_impact > pimpact(allocate_t{});
   ::pointer < layout_bar > pbar(allocate_t{});
   pframe->m_bWindowFrame = false; // Embedded File Manager, without frame chrome.
   pframe->m_pimpactMain = pimpact;
   pimpact->m_pframe = pframe;
   pframe->m_controlbara.add(pbar);
   pframe->m_pbar = pbar;
   ::draw2d::graphics_pointer pgraphics;
   ::i32_rectangle rectangleClient(0, 0, 800, 600);
   pframe->RepositionBars(pgraphics, 0, 0xffff, pimpact, 0, nullptr, rectangleClient);
   auto content = pframe->hosting_rectangle();
   if (content != ::i32_rectangle(0, 36, 800, 600) || content != pimpact->m_rectanglePlaced) return 1;

   // Repeated layout must not accumulate the toolbar inset.
   pframe->RepositionBars(pgraphics, 0, 0xffff, pimpact, 0, nullptr, rectangleClient);
   if (pframe->hosting_rectangle() != content) return 2;

   // Wrapped/rescaled toolbars and resizing must use the new allocation.
   pbar->m_iHeight = 72;
   rectangleClient = {0, 0, 500, 360};
   pframe->RepositionBars(pgraphics, 0, 0xffff, pimpact, 0, nullptr, rectangleClient);
   content = pframe->hosting_rectangle();
   if (content != ::i32_rectangle(0, 72, 500, 360)) return 3;

   int placements = pimpact->m_iPlacements;
   ::i32_rectangle query;
   pbar->m_iHeight = 40;
   pframe->RepositionBars(pgraphics, 0, 0xffff, pimpact, pframe->reposQuery, &query, rectangleClient);
   if (query.top != 40 || pimpact->m_iPlacements != placements || pframe->hosting_rectangle() != content) return 4;

   // A hidden bar returns its space to the impacts.
   pbar->m_bVisible = false;
   pframe->RepositionBars(pgraphics, 0, 0xffff, pimpact, 0, nullptr, rectangleClient);
   if (pframe->hosting_rectangle() != rectangleClient) return 5;
   return 0;
}
