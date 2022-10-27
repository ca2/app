#pragma once


#include "base/user/user/split_impact.h"


namespace userex
{


   class CLASS_DECL_CORE top_impact :
      virtual public ::user::split_impact
   {
   public:


      top_edit_impact *                     m_peditview;
      top_toggle_impact *                   m_ptoggleview;


      top_impact();
      ~top_impact() override;

//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;

      virtual void on_create_split_impact() override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace userex







