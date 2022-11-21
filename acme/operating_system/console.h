#pragma once


#include "acme/operating_system/_const_console.h"
//#include "acme/filesystem/file/file.h"
#include "acme/primitive/primitive/particle.h"


void RedirectIOToConsole();


class std_out_buffer:
   virtual public ::file::file
{
public:


   std_out_buffer() {}
   virtual ~std_out_buffer() {}


   void write(const void * pdata,memsize nCount);



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



      ::write_text_stream < ::file::file >         m_cout;
      int                                          m_iTextColor;


      console();
      ~console() override;


      inline ::write_text_stream < ::file::file > & cout() { return m_cout; }


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



