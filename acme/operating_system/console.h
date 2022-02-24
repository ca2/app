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


   class CLASS_DECL_ACME console:
      virtual public object
   {
   public:

      

      int               m_iTextColor;


      console();
      virtual ~console();


      virtual ::string_stream & cout() = 0;


      virtual void redirect_io();
      virtual void SetWindowSize(int iHeight,int iWidth) = 0;
      virtual void SetCursorVisibility(bool show) = 0;
      virtual void SetCursorPosition(int y,int x) = 0;
      virtual void SetTextColor(int color) = 0;
      inline int GetTextColor() { return m_iTextColor; }
      virtual void SetScreenColor(::enum_dos_color color,int iLineStart = 0,int iLineCount = -1) = 0;
      virtual void write(const ::string & str) = 0;


   };



   class CLASS_DECL_ACME console_client:
      virtual public console
   {
   public:



      console_client();
      ~console_client() override;


      virtual console * get_console();
      string_stream & cout() override;


      virtual void redirect_io() override;
      virtual void SetWindowSize(int iHeight, int iWidth) override;
      virtual void SetCursorVisibility(bool show) override;
      virtual void SetCursorPosition(int y, int x) override;
      virtual void SetTextColor(int color) override;
      virtual void SetScreenColor(enum_dos_color edoscolor, int iLineStart = 0, int iLineCount = -1) override;
      virtual void write(const ::string & str) override;


   };



} // namespace console







