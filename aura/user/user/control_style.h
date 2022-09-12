#pragma once


namespace user
{


   class control_style :
      virtual public ::matter
   {
   public:


      ::index        m_iUpdate;


      control_style();
      ~control_style();


      bool is_up_to_date(::user::style * pstyle) const;

      virtual void update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction);

      virtual void on_update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction);

   };




} // namespace user



