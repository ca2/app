#pragma once


#include "acme/filesystem/file/text_file.h"
//#include "acme/filesystem/file/text_stream.h"
#include "acme/operating_system/console.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/collection/int_map.h"
//#include "acme/prototype/collection/string_array.h"


namespace graphics
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console,
      virtual public ::string_buffer
   {
   public:


      //::write_text_stream < ::file::file >      m_cout;
      ::image::image_pointer                           m_pimage;
      ::int_size                                m_sizeTile;
      ::int_size                                m_sizeWindow;
      int                                       m_x;
      int                                       m_y;
      int                                       m_iColor;
      enum_dos_color                            m_edoscolor;
      int                                       m_iBorder;
      string_array                              m_stra;
      array < ::int_array >                     m_i2aColor;
      int_map < ::draw2d::pen_pointer >         m_mappen2;
      int_map < ::draw2d::pen_pointer >         m_mappen1;
      //int                                     m_iColorPointer;
      ::user::interaction *                     m_puserinteraction;

      
      int                                       m_iLastPenColor;
      int                                       m_iLastPen;


      console(::user::interaction * pinteraction, ::int_size sizeTile);
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
      void write(const ::scoped_string & scopedstr) override;


      using ::string_buffer::write;
      void write(const void * p, ::memsize s) override;

      ::int_rectangle get_position_rectangle(int y, int x) override;
      virtual ::int_rectangle _get_position_rectangle(int y, int x);
      virtual bool defer_write(char ch, const ::int_rectangle & r, int iColor);

      static ::color::color console_dos_color(enum_dos_color edoscolor);

      void get_cursor_position(int & x, int & y, filesize & iPointer);

      virtual void update_image();
      virtual void draw_write(char ch, int x, int y, enum_dos_color edoscolor);

      string right_string(::memsize iReadAtMostByteCount) override;


   };


} // namespace graphics





