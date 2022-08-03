#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



namespace userex
{


   top_view::top_view()
   {

      m_peditview = nullptr;
      m_ptoggleview = nullptr;

   }


   top_view::~top_view()
   {

   }


   void top_view::assert_ok() const
   {

      ::user::split_view::assert_ok();

   }


   void top_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void top_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_view::handle(ptopic, pcontext);

   }


   void top_view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.80);

      initialize_split_layout();

      m_peditview = create_pane_view < top_edit_view >(0, "top_edit_view");

      m_peditview->m_bParseDataPacks = true;

      if (m_peditview == nullptr)
      {

         output_error_message("Could not create folder edit impact");

      }

      m_peditview->m_ptopview = this;

      m_ptoggleview = create_pane_view < top_toggle_view >(1, "top_toggle_view");

      if (m_ptoggleview == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      m_ptoggleview->m_ptopview = this;

   }


   bool top_view::is_this_visible(::user::enum_layout elayout)
   {

      return ::user::split_view::is_this_visible(elayout) && !top_level()->frame_is_transparent();

   }


   void top_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnNcDraw(pgraphics);

   }


   void top_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      string strType = "top_view";

      ::duration t1 = ::duration::now();

      ::user::split_view::_001OnDraw(pgraphics);

      ::duration d1 = t1.elapsed();

#ifdef VERBOSE_LOG      

      if(d1 > 50_ms)
      {

         CATEGORY_INFORMATION(prodevian, "(more than 50ms)(H) "<< strType << "::_000OnDraw took " << integral_millisecond(d1) << ".\n");

      }

#endif

   }


} // namespace userex



