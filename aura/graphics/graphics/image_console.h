#pragma once


namespace graphics
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console,
      virtual public ::file::file
   {
   public:

      ::image::image_pointer               m_pimage;
      ::i32_size                        m_sizeTile;
      ::i32_size                        m_sizeWindow;
      ::i32                           m_x;
      ::i32                           m_y;
      ::i32                           m_iColor;
      ::i32                           m_iScreenColor;
      ::i32                           m_iBorder;
      string_array_base                       m_stra;
      array < ::i32_array_base >           m_i2aColor;
      i32_map < ::draw2d::pen_pointer >  m_mappen2;
      i32_map < ::draw2d::pen_pointer >  m_mappen1;
      ::i32                           m_iLastPenColor;
      ::i32                           m_iLastPen;


      console::i32_size sizeTile);

      virtual ::draw2d::pen_pointer & get_pen2(::i32 iColor);
      virtual ::draw2d::pen_pointer & get_pen1(::i32 iColor);

      virtual void SetWindowSize(::i32 iHeight, ::i32 iWidth);
      virtual void SetCursorVisibility(bool show);
      virtual void SetCursorPosition(::i32 y, ::i32 x);
      virtual void SetTextColor(::i32 color);
      virtual void SetScreenColor(::i32 color, ::i32 iLineStart = 0, ::i32 iLineCount = -1);
      virtual void write(const ::scoped_string & scopedstr);
      virtual void write(const void * pdata, memsize nCount);


      virtual bool defer_write(::i8 ch, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy, ::i32 iColor);

      static color32_t console_COLORREF(::i32 iColor);


      virtual void update_image();
      virtual void draw_write(::i8 ch, ::i32 x, ::i32 y, ::i32 iColor);

   };


} // namespace graphics





