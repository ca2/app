// from console.h by camilo on 2022-09-04 09:03 <3ThomasBorregaardSorensen!!
#pragma once


#include "console.h"


namespace console
{


   class CLASS_DECL_ACME console_client:
      virtual public ::console::console
   {
   public:


      console_client();
      ~console_client() override;


      virtual console * get_console();
      //write_text_stream < ::file::file > & cout() override;


      virtual void redirect_io() override;
      virtual void SetWindowSize(::i32 iHeight, ::i32 iWidth) override;
      virtual void SetCursorVisibility(bool show) override;
      virtual void SetCursorPosition(::i32 y, ::i32 x) override;
      virtual void SetTextColor(::i32 color) override;
      virtual void SetScreenColor(enum_dos_color edoscolor, ::i32 iLineStart = 0, ::i32 iLineCount = -1) override;
      virtual void write(const ::scoped_string & scopedstr) override;
      virtual ::i32_rectangle get_position_rectangle(::i32 y, ::i32 x) override;

   };


} // namespace console




