// 2026.3 API Created by camilo on 2026-03-25 18:27 <3ThomasBorregaardSørensen!!
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
//   console_ostream(): ::text_stream(::as(___new std_out_buffer())){}
//   virtual ~console_ostream(){}
//
//};


namespace console
{

   enum enum_response
   {

      e_response_no = -1,
      e_response_cancel = 0,
      e_response_yes = 1,

   };

   class CLASS_DECL_ACME console:
      virtual public ::particle
   {
   public:



      ::write_text_stream                          m_cout;
      int                                          m_iTextColor;


      console(const ::pointer < ::string_buffer_base > & pstringbuffer = nullptr);
      ~console() override;


      // 2025 API
      inline ::write_text_stream & cout() { return m_cout; }
      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight,int iWidth);
      virtual void SetCursorVisibility(bool show);
      virtual void SetCursorPosition(int y,int x);
      virtual void SetTextColor(int color);
      inline int GetTextColor() { return m_iTextColor; }
      virtual void SetScreenColor(::enum_dos_color color,int iLineStart = 0,int iLineCount = -1);
      virtual void write(const ::scoped_string & scopedstr);
      virtual ::int_rectangle get_position_rectangle(int y, int x);



      // 2026.3 API
      virtual void defer_non_root();
      virtual void start_input();
      virtual int getch(void);
      virtual int get_thoughtful_character();
      virtual enum_response yes_no(const char * pszPrompt);
      virtual enum_response yes_no_default_yes(const char * pszPrompt);



   };


} // namespace console



