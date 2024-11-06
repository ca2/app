#pragma once


namespace graphics
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console,
      virtual public ::file::file
   {
   public:

      ::image::image_pointer               m_pimage;
      ::int_size                        m_sizeTile;
      ::int_size                        m_sizeWindow;
      int                           m_x;
      int                           m_y;
      int                           m_iColor;
      int                           m_iScreenColor;
      int                           m_iBorder;
      string_array                       m_stra;
      array < ::int_array >           m_i2aColor;
      int_map < ::draw2d::pen_pointer >  m_mappen2;
      int_map < ::draw2d::pen_pointer >  m_mappen1;
      int                           m_iLastPenColor;
      int                           m_iLastPen;


      console::int_size sizeTile);

      virtual ::draw2d::pen_pointer & get_pen2(int iColor);
      virtual ::draw2d::pen_pointer & get_pen1(int iColor);

      virtual void SetWindowSize(int iHeight, int iWidth);
      virtual void SetCursorVisibility(bool show);
      virtual void SetCursorPosition(int y, int x);
      virtual void SetTextColor(int color);
      virtual void SetScreenColor(int color, int iLineStart = 0, int iLineCount = -1);
      virtual void write(const ::string & psz);
      virtual void write(const void * pdata, memsize nCount);


      virtual bool defer_write(char ch, int x, int y, int cx, int cy, int iColor);

      static color32_t console_COLORREF(int iColor);


      virtual void update_image();
      virtual void draw_write(char ch, int x, int y, int iColor);

   };


} // namespace graphics





