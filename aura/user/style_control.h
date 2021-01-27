#pragma once


namespace user
{


   class control_style :
      virtual public ::matter
   {
   public:

      ::index        m_iUpdate;

      control_style();
      virtual ~control_style();

      bool is_up_to_date(::user::style * pstyle) const;

      virtual void update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction);

      virtual void on_update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction);

   };


   class plain_edit_style :
      virtual public control_style
   {
   public:


      ::draw2d::pen_pointer              m_penCaret;
      ::draw2d::brush_pointer            m_brushText;
      ::draw2d::brush_pointer            m_brushTextCr;
      ::draw2d::brush_pointer            m_brushTextSel;
      ::draw2d::brush_pointer            m_brushTextEmpty;


      plain_edit_style();
      virtual ~plain_edit_style();


      virtual void on_update(::draw2d::graphics_pointer & pgraphics, style * ppstyle, ::user::interaction * pinteraction) override;


   };



} // namespace user



