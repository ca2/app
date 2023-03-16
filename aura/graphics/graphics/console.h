#pragma once


#include "acme/filesystem/file/text_file.h"
//#include "acme/filesystem/file/text_stream.h"
#include "acme/operating_system/console.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/collection/int_map.h"
//#include "acme/primitive/collection/string_array.h"


namespace graphics
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console,
      virtual public ::file::text_file
   {
   public:


      //::write_text_stream < ::file::file >      m_cout;
      ::image_pointer                           m_pimage;
      ::size_i32                                m_sizeTile;
      ::size_i32                                m_sizeWindow;
      int                                       m_x;
      int                                       m_y;
      int                                       m_iColor;
      enum_dos_color                            m_edoscolor;
      int                                       m_iBorder;
      string_array                              m_stra;
      array < int_array >                       m_i2aColor;
      i32_map < ::draw2d::pen_pointer >         m_mappen2;
      i32_map < ::draw2d::pen_pointer >         m_mappen1;
      //int                                     m_iColorPointer;
      ::user::interaction *                     m_puserinteraction;

      
      int                                       m_iLastPenColor;
      int                                       m_iLastPen;


      console(::user::interaction * pinteraction, ::size_i32 sizeTile);
      ~console() override;


      // void assert_ok() const override;
      // virtual void dump(dump_context & dump) const override;


      //::write_text_stream < ::file::file > & cout() override;

      
      virtual ::draw2d::pen_pointer & get_pen2(enum_dos_color edoscolor);
      virtual ::draw2d::pen_pointer & get_pen1(enum_dos_color edoscolor);


      void SetWindowSize(int iHeight, int iWidth) override;
      void SetCursorVisibility(bool show) override;
      void SetCursorPosition(int y, int x) override;
      void SetTextColor(int color) override;
      void SetScreenColor(::enum_dos_color color, int iLineStart = 0, int iLineCount = -1) override;
      void write(const ::string & psz) override;


      using ::file::text_file::write;
      void write(const void * p, ::memsize s) override;


      virtual bool defer_write(char ch, int x, int y, int cx, int cy, int iColor);

      static ::color::color console_dos_color(enum_dos_color edoscolor);

      void get_cursor_position(int & x, int & y, filesize & iPointer);

      virtual void update_image();
      virtual void draw_write(char ch, int x, int y, enum_dos_color edoscolor);

      string as_string() const override;


   };


} // namespace graphics





