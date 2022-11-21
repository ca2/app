// from console.h by camilo on 2022-09-04 09:03 <3ThomasBorregaardSorensen!!
#pragma once


#include "console.h"


namespace console
{


   class CLASS_DECL_ACME console_client:
      virtual public console
   {
   public:


      console_client();
      ~console_client() override;


      virtual console * get_console();
      //write_text_stream < ::file::file > & cout() override;


      virtual void redirect_io() override;
      virtual void SetWindowSize(int iHeight, int iWidth) override;
      virtual void SetCursorVisibility(bool show) override;
      virtual void SetCursorPosition(int y, int x) override;
      virtual void SetTextColor(int color) override;
      virtual void SetScreenColor(enum_dos_color edoscolor, int iLineStart = 0, int iLineCount = -1) override;
      virtual void write(const ::string & str) override;


   };


} // namespace console




