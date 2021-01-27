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


   void top_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void top_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void top_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::split_view::on_subject(psubject, pcontext);

   }


   void top_view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0, 0.80);

      initialize_split_layout();

      m_peditview = create_pane_view < top_edit_view >(0, "top_edit_view");

      m_peditview->m_bParseDataPacks = true;

      if (m_peditview == nullptr)
      {

         System.message_box("Could not create folder edit view");

      }

      m_peditview->m_ptopview = this;

      m_ptoggleview = create_pane_view < top_toggle_view >(1, "top_toggle_view");

      if (m_ptoggleview == nullptr)
      {

         System.message_box("Could not create file list ::user::impact");

      }

      m_ptoggleview->m_ptopview = this;

   }


   bool top_view::is_this_visible(::user::enum_layout elayout)
   {

      return ::user::split_view::is_this_visible(elayout) && !get_top_level()->frame_is_transparent();

   }


   void top_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnNcDraw(pgraphics);

   }


   void top_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      string strType = "top_view";

      millis t1 = millis::now();

      ::user::split_view::_001OnDraw(pgraphics);

      millis d1 = t1.elapsed();

      if(d1 > 50)
      {

         CINFO(prodevian)("(more than 50ms) "+strType+"::_000OnDraw took " + __str(d1) + ".\n");

      }

   }


} // namespace userex



