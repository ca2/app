#pragma once


namespace userex
{


   class pane_impact;


   class CLASS_DECL_CORE pane_split_impact:
      virtual public ::user::split_impact
   {
   public:


      __pointer(pane_impact) m_ppaneimpact;


      pane_split_impact();
      virtual ~pane_split_impact();


   };


} // namespace userex









