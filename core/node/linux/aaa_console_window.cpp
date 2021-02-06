#include "framework.h"
#include "acme/os/console.h"
#include "console_window.h"
#include <ncurses.h>


namespace linux
{


   console::console()
   {

      cout.m_p = __new(std_out_buffer());

      initscr();
      raw();
      noecho();
      keypad(stdscr, true);
      start_color();

      init_color(COLOR_WHITE, 1000, 1000, 1000);
      init_color(COLOR_RED, 1000, 0, 0);
      init_color(COLOR_GREEN, 0, 0, 1000);
      init_color(COLOR_BLUE, 0, 0, 500);
      init_color(COLOR_CYAN, 0, 1000, 1000);
      init_color(COLOR_MAGENTA, 1000, 0, 1000);
      init_color(COLOR_YELLOW, 1000, 1000, 0);
      init_color(COLOR_BLACK, 0, 0, 0);

      init_pair(::console::WHITE, COLOR_WHITE, COLOR_BLACK);
      init_pair(::console::RED, COLOR_RED, COLOR_BLACK);
      init_pair(::console::BLUE, COLOR_GREEN, COLOR_BLACK);
      init_pair(::console::DARKBLUE, COLOR_BLUE, COLOR_BLACK);
      init_pair(::console::CYAN, COLOR_CYAN, COLOR_BLACK);
      init_pair(::console::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
      init_pair(::console::YELLOW, COLOR_YELLOW, COLOR_BLACK);
      init_pair(::console::BLACK, COLOR_BLACK, COLOR_BLACK);

      m_iColor = -1;
   }


   console::~console()
   {

      endwin();

   }


   // maximum mumber of lines the output console should have

   static const ::u16 MAX_CONSOLE_LINES = 500;

   void console::redirect_io()
   {

//      int hConHandle;
//
//      long lStdHandle;
//
//      CONSOLE_SCREEN_BUFFER_INFO coninfo;
//
//      FILE *fp;
//
//      // allocate a console for this app
//
//      // set the screen buffer to be big enough to let us scroll text
//
//      GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
//
//       &coninfo);
//
//      coninfo.dwSize.Y = MAX_CONSOLE_LINES;
//
//      SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
//
//       coninfo.dwSize);
//
//      // redirect unbuffered STDOUT to the console
//
//      lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
//
//      hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);
//
//      fp = _fdopen(hConHandle,"w");
//
//      *stdout = *fp;
//
//      setvbuf(stdout,nullptr,_IONBF,0);
//
//      // redirect unbuffered STDIN to the console
//
//      lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
//
//      hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);
//
//      fp = _fdopen(hConHandle,"r");
//
//      *stdin = *fp;
//
//      setvbuf(stdin,nullptr,_IONBF,0);
//
//      // redirect unbuffered STDERR to the console
//
//      lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
//
//      hConHandle = _open_osfhandle(lStdHandle,_O_TEXT);
//
//      fp = _fdopen(hConHandle,"w");
//
//      *stderr = *fp;
//
//      setvbuf(stderr,nullptr,_IONBF,0);

      //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog

      //point to console as well

      //ios::sync_with_stdio();

   }


   void console::SetWindowSize(int height,int width)
   {
      m_iH = height;
      m_iW = width;
      /*      SMALL_RECT window;
            window.Top = 0;
            window.Left = 0;
            window.Bottom = height - 1;
            window.Right = width - 1;
            SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),true,&window);
            COORD buffer ={width,height};
            SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),buffer);
      */
   }

   void console::SetCursorVisibility(bool show)
   {
      /*    CONSOLE_CURSOR_INFO cursor;
          GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
          cursor.bVisible = show;
          SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);*/
   }

   void console::SetCursorPosition(int y,int x)
   {
      move(y, x);
   }

   void console::SetTextColor(int color)
   {
      if(m_iColor != -1)
      {
         attroff(COLOR_PAIR(m_iColor));

      }
      m_iColor = color;
      attron(COLOR_PAIR(m_iColor));
   }

   void console::SetScreenColor(int color, int iLineStart, int iLineCount)
   {
//      COORD coord ={0,iLineStart};
//      ::u32 dwWritten;
//      if(iLineCount < 0)
//         iLineCount = m_iH + iLineCount + 1;
//      if(iLineCount > m_iH - iLineStart)
//         iLineCount = m_iH - iLineStart;
//      FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color,iLineCount * m_iW,coord,&dwWritten);
   }

   void console::write(const char * psz)
   {

      printw(psz);
      refresh();

   }

} // namespace windows



