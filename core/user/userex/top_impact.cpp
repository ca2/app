#include "framework.h"
#include "top_impact.h"
#include "top_edit_impact.h"
#include "top_toggle_impact.h"


namespace userex
{


   top_impact::top_impact()
   {

      m_peditview = nullptr;
      m_ptoggleview = nullptr;

   }


   top_impact::~top_impact()
   {

   }


//   void top_impact::assert_ok() const
//   {
//
//      ::user::split_impact::assert_ok();
//
//   }
//
//
//   void top_impact::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::split_impact::dump(dumpcontext);
//
//   }


   void top_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_impact::handle(ptopic, pcontext);

   }


   void top_impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.80);

      initialize_split_layout();

      m_peditview = create_pane_impact < top_edit_impact >(0, "top_edit_impact");

      m_peditview->m_bParseDataPacks = true;

      if (m_peditview == nullptr)
      {

         output_error_message("Could not create folder edit impact");

      }

      m_peditview->m_ptopview = this;

      m_ptoggleview = create_pane_impact < top_toggle_impact >(1, "top_toggle_impact");

      if (m_ptoggleview == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      m_ptoggleview->m_ptopview = this;

   }


   bool top_impact::is_this_visible(::user::enum_layout elayout)
   {

      return ::user::split_impact::is_this_visible(elayout) && !top_level()->frame_is_transparent();

   }


   void top_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnNcDraw(pgraphics);

   }


   void top_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      string strType = "top_impact";

      auto timeStart = ::time::now();

      ::user::split_impact::_001OnDraw(pgraphics);

      auto timeEllapsed = timeStart.elapsed();

#ifdef VERBOSE_LOG      

      if(d1 > 50_ms)
      {

         CATEGORY_INFORMATION(prodevian, "(more than 50ms)(H) "<< strType << "::_000OnDraw took " << integral_millisecond(d1) << ".\n");

      }

#endif

   }


} // namespace userex



