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

namespace console
{


   const int WHITE    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int RED      = FOREGROUND_RED | FOREGROUND_INTENSITY;
   const int BLUE     = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int DARKBLUE = FOREGROUND_BLUE;
   const int CYAN     = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int MAGENTA  = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
   const int YELLOW   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
   const int BLACK    = 0;


   class CLASS_DECL_ACME console:
      virtual public ::matter
   {
   public:

      

      ::string_stream   cout;
      int m_iTextColor;


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight,int iWidth) = 0;
      virtual void SetCursorVisibility(bool show) = 0;
      virtual void SetCursorPosition(int y,int x) = 0;
      virtual void SetTextColor(int color) = 0;
      inline int GetTextColor() { return m_iTextColor; }
      virtual void SetScreenColor(int color,int iLineStart = 0,int iLineCount = -1) = 0;
      virtual void write(const char * psz) = 0;


   };



   class CLASS_DECL_ACME console_composite:
      virtual public console
   {
   public:


      __pointer(console)  m_pconsole;


      console_composite();


      virtual void set_console(console* pconsole);


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight, int iWidth);
      virtual void SetCursorVisibility(bool show);
      virtual void SetCursorPosition(int y, int x);
      virtual void SetTextColor(int color);
      virtual void SetScreenColor(int color, int iLineStart = 0, int iLineCount = -1);
      virtual void write(const char * psz);


   };



} // namespace console



