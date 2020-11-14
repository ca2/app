#include "framework.h"


namespace console
{


   prompt_impact::prompt_impact(::layered * pobjectContext) :
      ::object(pobject)
   {

      m_tickCaretPeriod   = 500;

      m_iNewChar        = 0;

      m_iCursor = 0;
      m_sizeChar.cx = 32;
      m_sizeChar.cy = 32;
      m_iCursor = 0;
      m_bOk = true;

   }


   prompt_impact::~prompt_impact()
   {


   }


   void prompt_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&prompt_impact::_001OnCreate);
      MESSAGE_LINK(e_message_key_down,pchannel,this,&prompt_impact::_001OnKeyDown);
      MESSAGE_LINK(e_message_key_up,pchannel,this,&prompt_impact::_001OnKeyUp);
      MESSAGE_LINK(e_message_show_window,pchannel,this,&prompt_impact::_001OnShowWindow);

   }


   void prompt_impact::clear()
   {

      m_strCommand.Empty();

      m_iCursor = 0;

   }


   void prompt_impact::_001OnShowWindow(::message::message * pmessage)
   {
      SCAST_PTR(::message::show_window,pshowwindow,pmessage);
      if(pshowwindow->m_bShow)
      {
         m_tickLastError = ::get_tick();
         m_bOk = false;
      }
   }


   void prompt_impact::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      if (pcreate->previous())
      {

         return;

      }

      m_tickCaretStart = ::get_tick();

   }


   void prompt_impact::interpret_command()
   {

      bool m_bOk = true;

      if(m_strCommand == ":q")
      {

         ::multithreading::set_finish(&System);

      }
      else
      {

         m_tickLastError = ::get_tick();

         m_bOk = false;

      }

      if(m_bOk)
      {

         clear();

      }

   }


   void prompt_impact::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key,pkey,pmessage);

      m_tickCaretStart.Now();

      ::message::key & key = *pkey;

      if(key.m_ekey == ::user::key_escape)
      {

         GetTypedParent < prompt_frame > ()->hide();

         Application.m_puiMain->m_puiThis->SetActiveWindow();

         clear();

      }
      else if(key.m_ekey == ::user::key_return)
      {

         interpret_command();

      }
      else if(key.m_ekey == ::user::key_shift || key.m_ekey == ::user::key_lshift || key.m_ekey == ::user::key_rshift
              || key.m_ekey == ::user::key_control || key.m_ekey == ::user::key_lcontrol || key.m_ekey == ::user::key_rcontrol
              || key.m_ekey == ::user::key_alt || key.m_ekey == ::user::key_lalt || key.m_ekey == ::user::key_ralt
             )
      {


      }
      else if(pkey->m_ekey == ::user::key_back)
      {

         if(m_iCursor <= 0)
            return;

         const char * lpsz = &m_strCommand[m_iCursor];

         const char * lpszDec = ::str::utf8_dec(m_strCommand, lpsz);

         if(lpsz - lpszDec > 0)
         {

            m_strCommand.erase(lpszDec - m_strCommand,lpsz - lpszDec);

            m_iCursor--;

         }

         return;

      }
      else if(pkey->m_ekey == ::user::key_delete)
      {

         if(m_iCursor >= m_strCommand.utf8_get_length())
            return;

         const char * lpsz = &m_strCommand[m_iCursor];

         const char * lpszInc = ::str::utf8_inc(lpsz);

         if(lpszInc - lpsz > 0)
         {

            m_strCommand.erase(lpsz - m_strCommand,lpszInc - lpsz);

         }

         return;

      }
      else if(pkey->m_ekey == ::user::key_left)
      {

         if(m_iCursor <= 0)
            return;

         m_iCursor--;

         return;

      }
      else if(pkey->m_ekey == ::user::key_right)
      {

         if(m_iCursor >= m_strCommand.utf8_get_length())
            return;

         m_iCursor++;

         return;

      }
      else
      {

         string str;

         if(pkey->m_ekey == ::user::key_space)
         {

            str = " ";

         }
         else
         {

            str = psession->keyboard().process_key(pkey->m_ekey);

         }

         if(str.has_char())
         {

            if(m_iNewChar == 0x80000000)
            {

               m_iNewChar = str[0];

               m_evNewChar.SetEvent();

            }
            else
            {

               m_strCommand += str;
               m_iCursor += str.utf8_get_length();

            }

         }

      }

   }


   void prompt_impact::_001OnKeyUp(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }

   void prompt_impact::simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics)
   {
      //if(GetTypedParent <prompt_frame>()->get_display() != ::display_minimal)
      {
         ::user::impact::simple_ui_draw_focus_rect(pgraphics);
      }
   }


   int prompt_impact::getch()
   {

      m_tickCaretPeriod.Now();

      m_iNewChar = 0x80000000;

      m_evNewChar.wait();

      return (int) m_iNewChar;

   }

   int prompt_impact::ungetch(int c)
   {

      return 0;

   }


   void prompt_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      ::draw2d::font_pointer f(e_create);

      f->create_pixel_font("Consolas",16.0);

      pgraphics->SelectObject(f);

      ::u32 dwAlpha = 123;

      color32_t crTopic;

      if(m_tickLastError.elapsed() < 84 && !m_bOk)
      {

         crTopic = ARGB(255,255,0,210);

      }
      else
      {

         m_bOk = true;

         crTopic = ARGB(255,100,210,84);

      }

      bool bCaretOn = m_tickCaretStart.on_off(m_tickCaretPeriod);

      auto rectClient = get_client_rect();

      m_sizeChar = pgraphics.GetTextExtent("M");
      
      m_sizeChar = m_sizeChar.max(pgraphics.GetTextExtent("p"));

      pgraphics->fill_rect(rectClient,ARGB(dwAlpha,0,0,0));

      pgraphics->set_text_color(crTopic);

      int i;

      int iLeftMargin = 2;

      for( i = 0; i < m_strCommand.length(); i++)
      {

         pgraphics->text_out(iLeftMargin +m_sizeChar.cx *i,0,m_strCommand.Mid(i,1));

      }

      if(bCaretOn)
      {

         ::rect rectCaret;

         rectCaret.left = (::i32) (iLeftMargin+m_sizeChar.cx * m_iCursor);
         rectCaret.right = rectCaret.left + m_sizeChar.cx;
         rectCaret.top = m_sizeChar.cy - 3;
         rectCaret.bottom = m_sizeChar.cy;



         pgraphics->fill_rect(rectCaret,crTopic);

      }

   }


   bool prompt_impact::keyboard_focus_is_focusable()
   {

      return true;

   }


} // namespace console








































