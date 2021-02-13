#pragma once

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


enum enum_dos_color
{
   e_dos_color_foreground_blue_component = 0x0001,
   e_dos_color_foreground_green_component = 0x0002, // text color contains green.
   e_dos_color_foreground_red_component = 0x0004, // text color contains red.
   e_dos_color_foreground_intensity = 0x0008, // text color is intensified.
   e_dos_color_background_blue_component = 0x0010, // background color contains blue.
   e_dos_color_background_green_component = 0x0020, // background color contains green.
   e_dos_color_background_red_component = 0x0040, // background color contains red.
   e_dos_color_background_intensity = 0x0080, // background color is intensified.
   e_dos_color_foreground_white = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component | e_dos_color_foreground_red_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_blue = e_dos_color_foreground_blue_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_green = e_dos_color_foreground_green_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_red = e_dos_color_foreground_red_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_cyan = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_magenta = e_dos_color_foreground_blue_component | e_dos_color_foreground_red_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_yellow = e_dos_color_foreground_red_component | e_dos_color_foreground_green_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_gray = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component | e_dos_color_foreground_red_component,
   e_dos_color_foreground_dark_blue = e_dos_color_foreground_blue_component,
   e_dos_color_foreground_dark_green = e_dos_color_foreground_green_component,
   e_dos_color_foreground_dark_red = e_dos_color_foreground_red_component,
   e_dos_color_foreground_tungsten = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component,
   e_dos_color_foreground_purple = e_dos_color_foreground_blue_component | e_dos_color_foreground_red_component,
   e_dos_color_foreground_kaki = e_dos_color_foreground_red_component | e_dos_color_foreground_green_component,
   e_dos_color_foreground_black = 0,
   e_dos_color_background_white = e_dos_color_background_blue_component | e_dos_color_background_green_component | e_dos_color_background_red_component | e_dos_color_background_intensity,
   e_dos_color_background_blue = e_dos_color_background_blue_component | e_dos_color_background_intensity,
   e_dos_color_background_green = e_dos_color_background_green_component | e_dos_color_background_intensity,
   e_dos_color_background_red = e_dos_color_background_red_component | e_dos_color_background_intensity,
   e_dos_color_background_cyan = e_dos_color_background_blue_component | e_dos_color_background_green_component | e_dos_color_background_intensity,
   e_dos_color_background_magenta = e_dos_color_background_blue_component | e_dos_color_background_red_component | e_dos_color_background_intensity,
   e_dos_color_background_yellow = e_dos_color_background_red_component | e_dos_color_background_green_component | e_dos_color_background_intensity,
   e_dos_color_background_gray = e_dos_color_background_blue_component | e_dos_color_background_green_component | e_dos_color_background_red_component,
   e_dos_color_background_dark_blue = e_dos_color_background_blue_component,
   e_dos_color_background_dark_green = e_dos_color_background_green_component,
   e_dos_color_background_dark_red = e_dos_color_background_red_component,
   e_dos_color_background_tungsten = e_dos_color_background_blue_component | e_dos_color_background_green_component,
   e_dos_color_background_purple = e_dos_color_background_blue_component | e_dos_color_background_red_component,
   e_dos_color_background_kaki = e_dos_color_background_red_component | e_dos_color_background_green_component,
   e_dos_color_background_black = 0,
};

namespace console
{





   class CLASS_DECL_ACME console:
      virtual public ::context_object
   {
   public:

      

      ::string_stream   cout;
      int m_iTextColor;


      console();
      virtual ~console();


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight,int iWidth) = 0;
      virtual void SetCursorVisibility(bool show) = 0;
      virtual void SetCursorPosition(int y,int x) = 0;
      virtual void SetTextColor(int color) = 0;
      inline int GetTextColor() { return m_iTextColor; }
      virtual void SetScreenColor(::enum_dos_color color,int iLineStart = 0,int iLineCount = -1) = 0;
      virtual void write(const char * psz) = 0;


   };



   class CLASS_DECL_ACME console_composite:
      virtual public console
   {
   public:


      __pointer(console)  m_pconsole;


      console_composite();
      virtual ~console_composite();


      virtual void set_console(console* pconsole);


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight, int iWidth);
      virtual void SetCursorVisibility(bool show);
      virtual void SetCursorPosition(int y, int x);
      virtual void SetTextColor(int color);
      virtual void SetScreenColor(enum_dos_color edoscolor, int iLineStart = 0, int iLineCount = -1);
      virtual void write(const char * psz);


   };



} // namespace console



