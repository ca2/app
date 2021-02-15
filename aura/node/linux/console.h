#pragma once


namespace linux
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console
   {
   public:



      int m_iW;
      int m_iH;
      int m_iColor;

      console();
      virtual ~console();

      void redirect_io();
      void SetWindowSize(int height,int width);
      void SetCursorVisibility(bool show);
      void SetCursorPosition(int y,int x);
      void SetTextColor(int color);
      void SetScreenColor(enum_dos_color color, int iLineStart = 0, int iLineCount = -1);
      void write(const char * psz);

   };


} // namespace windows




