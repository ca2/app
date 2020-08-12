#pragma once


namespace userex
{


   class pane_view;


   class CLASS_DECL_CORE pane_split_view:
      virtual public ::user::split_view
   {
   public:


      __pointer(pane_view) m_ppaneview;


      pane_split_view();
      virtual ~pane_split_view();


   };


} // namespace userex









