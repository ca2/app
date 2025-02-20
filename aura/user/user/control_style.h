#pragma once


//#include "acme/prototype/prototype/matter.h"


namespace user
{


   class control_style :
      virtual public ::matter
   {
   public:


      ::collection::index        m_iUpdate;


      control_style();
      ~control_style();


      bool is_up_to_date(::user::style * pstyle) const;

      virtual void update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction);

      virtual void on_update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction);

   };




} // namespace user



