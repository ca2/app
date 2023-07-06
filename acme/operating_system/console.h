#pragma once


#include "acme/operating_system/_const_console.h"
#include "acme/filesystem/file/string_buffer.h"


void RedirectIOToConsole();


class CLASS_DECL_ACME std_out_buffer:
   virtual public ::string_buffer_base
{
public:


   std_out_buffer();
   ~std_out_buffer() override;


   void write(const void * pdata,memsize nCount) override;



};

//class console_ostream:
//   virtual public ::text_stream
//{
//public:
//
//   console_ostream(): ::text_stream(__new(std_out_buffer())){}
//   virtual ~console_ostream(){}
//
//};


namespace console
{


   class CLASS_DECL_ACME console:
      virtual public ::particle
   {
   public:



      ::write_text_stream                          m_cout;
      int                                          m_iTextColor;


      console(const ::pointer < ::string_buffer_base > & pstringbuffer = nullptr);
      ~console() override;


      inline ::write_text_stream & cout() { return m_cout; }


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight,int iWidth) = 0;
      virtual void SetCursorVisibility(bool show) = 0;
      virtual void SetCursorPosition(int y,int x) = 0;
      virtual void SetTextColor(int color) = 0;
      inline int GetTextColor() { return m_iTextColor; }
      virtual void SetScreenColor(::enum_dos_color color,int iLineStart = 0,int iLineCount = -1) = 0;
      virtual void write(const ::string & str) = 0;


   };


} // namespace console



