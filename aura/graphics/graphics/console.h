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
      ::i32_size                                m_sizeTile;
      ::i32_size                                m_sizeWindow;
      ::i32                                       m_x;
      ::i32                                       m_y;
      ::i32                                       m_iColor;
      enum_dos_color                            m_edoscolor;
      ::i32                                       m_iBorder;
      string_array_base                              m_stra;
      array < ::i32_array_base >                     m_i2aColor;
      i32_map < ::draw2d::pen_pointer >         m_mappen2;
      i32_map < ::draw2d::pen_pointer >         m_mappen1;
      //::i32                                     m_iColorPointer;
      ::user::interaction *                     m_puserinteraction;

      
      ::i32                                       m_iLastPenColor;
      ::i32                                       m_iLastPen;


      console(::user::interaction * pinteraction, ::i32_size sizeTile);
      ~console() override;


      // void assert_ok() const override;
      // virtual void dump(dump_context & dump) const override;


      //::write_text_stream < ::file::file > & cout() override;

      
      virtual ::draw2d::pen_pointer & get_pen2(enum_dos_color edoscolor);
      virtual ::draw2d::pen_pointer & get_pen1(enum_dos_color edoscolor);


      void SetWindowSize(::i32 iHeight, ::i32 iWidth) override;
      void SetCursorVisibility(bool show) override;
      void SetCursorPosition(::i32 y, ::i32 x) override;
      void SetTextColor(::i32 color) override;
      void SetScreenColor(::enum_dos_color color, ::i32 iLineStart = 0, ::i32 iLineCount = -1) override;
      void write(const ::scoped_string & scopedstr) override;


      using ::string_buffer::write;
      void write(const void * p, ::memsize s) override;

      ::i32_rectangle get_position_rectangle(::i32 y, ::i32 x) override;
      virtual ::i32_rectangle _get_position_rectangle(::i32 y, ::i32 x);
      virtual bool defer_write(::i8 ch, const ::i32_rectangle & r, ::i32 iColor);

      static ::color::color console_dos_color(enum_dos_color edoscolor);

      void get_cursor_position(::i32 & x, ::i32 & y, filesize & iPointer);

      virtual void update_image();
      virtual void draw_write(::i8 ch, ::i32 x, ::i32 y, enum_dos_color edoscolor);

      string right_string(::memsize iReadAtMostByteCount) override;


   };


} // namespace graphics





