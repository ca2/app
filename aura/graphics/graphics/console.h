#pragma once


namespace graphics
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console,
      virtual public ::file::text_file
   {
   public:


      ::image_pointer                     m_pimage;
      ::size                              m_sizeTile;
      ::size                              m_sizeWindow;
      int                                 m_x;
      int                                 m_y;
      int                                 m_iColor;
      int                                 m_iScreenColor;
      int                                 m_iBorder;
      string_array                        m_stra;
      array < int_array >                 m_i2aColor;
      int_map < ::draw2d::pen_pointer >   m_mappen2;
      int_map < ::draw2d::pen_pointer >   m_mappen1;
      //int                                 m_iColorPointer;

      
      int                                 m_iLastPenColor;
      int                                 m_iLastPen;


      console(size sizeTile);
      virtual ~console();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dump) const override;

      
      virtual ::draw2d::pen_pointer & get_pen2(int iColor);
      virtual ::draw2d::pen_pointer & get_pen1(int iColor);


      virtual void SetWindowSize(int iHeight, int iWidth) override;
      virtual void SetCursorVisibility(bool show) override;
      virtual void SetCursorPosition(int y, int x) override;
      virtual void SetTextColor(int color) override;
      virtual void SetScreenColor(int color, int iLineStart = 0, int iLineCount = -1) override;
      virtual void write(const char * psz) override;
      virtual void write(const void * pdata, memsize nCount) override;


      virtual bool defer_write(char ch, int x, int y, int cx, int cy, int iColor);

      static COLORREF console_COLORREF(int iColor);

      void get_cursor_position(int & x, int & y, filesize & iPointer);

      virtual void update_image();
      virtual void draw_write(char ch, int x, int y, int iColor);

      virtual void to_string(const string_exchange & str) const override;

   };


} // namespace graphics





