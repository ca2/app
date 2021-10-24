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


   class plain_edit_style :
      virtual public control_style
   {
   public:


      ::draw2d::pen_pointer              m_ppenCaret;
      ::draw2d::brush_pointer            m_pbrushText;
      ::draw2d::brush_pointer            m_pbrushTextCr;
      ::draw2d::brush_pointer            m_pbrushTextSel;
      ::draw2d::brush_pointer            m_pbrushTextEmpty;


      plain_edit_style();
      ~plain_edit_style() override;


      virtual void on_update(::draw2d::graphics_pointer & pgraphics, style * ppstyle, ::user::interaction * pinteraction) override;


   };



} // namespace user



