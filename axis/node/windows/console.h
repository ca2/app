#pragma once


namespace windows
{


   class CLASS_DECL_AURA console :
      virtual public ::console::console
   {
   public:



      int m_iW;
      int m_iH;

      console();
      virtual ~console();

      void redirect_io();
      void SetWindowSize(int height,int width);
      void SetCursorVisibility(bool show);
      void SetCursorPosition(int y,int x);
      void SetTextColor(int color);
      void SetScreenColor(int color, int iLineStart = 0, int iLineCount = -1);
      void write(const char * psz);

   };


} // namespace windows




