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
      ::i32                                          m_iTextColor;


      console(const ::pointer < ::string_buffer_base > & pstringbuffer = nullptr);
      ~console() override;


      // 2025 API
      inline ::write_text_stream & cout() { return m_cout; }
      virtual void redirect_io();
      virtual void SetWindowSize(::i32 iHeight,::i32 iWidth);
      virtual void SetCursorVisibility(bool show);
      virtual void SetCursorPosition(::i32 y,::i32 x);
      virtual void SetTextColor(::i32 color);
      inline ::i32 GetTextColor() { return m_iTextColor; }
      virtual void SetScreenColor(::enum_dos_color color,::i32 iLineStart = 0,::i32 iLineCount = -1);
      virtual void write(const ::scoped_string & scopedstr);
      virtual ::i32_rectangle get_position_rectangle(::i32 y, ::i32 x);



      // 2026.3 API
      virtual void defer_non_root();
      virtual void start_input();
      virtual ::i32 getch(void);
      virtual ::i32 get_thoughtful_character();
      virtual enum_response yes_no(const_char_pointer pszPrompt);
      virtual enum_response yes_no_default_yes(const_char_pointer pszPrompt);
      virtual ::string prompt_line(const_char_pointer pszPrompt);


   };


} // namespace console


CLASS_DECL_ACME ::i32 current_getch();
CLASS_DECL_ACME ::i32 current_getch_utf8(::string &strChar);



