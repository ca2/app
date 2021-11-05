#include "framework.h"


namespace console
{


   prompt_impact::prompt_impact(::object * pobject) :
      ::object(pobject)
   {

      m_durationCaretPeriod   = 500;

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

      MESSAGE_LINK(e_message_create,pchannel,this,&prompt_impact::on_message_create);
      MESSAGE_LINK(e_message_key_down,pchannel,this,&prompt_impact::on_message_key_down);
      MESSAGE_LINK(e_message_key_up,pchannel,this,&prompt_impact::on_message_key_up);
      MESSAGE_LINK(e_message_show_window,pchannel,this,&prompt_impact::on_message_show_window);

   }


   void prompt_impact::clear()
   {

      m_strCommand.Empty();

      m_iCursor = 0;

   }


   void prompt_impact::on_message_show_window(::message::message * pmessage)
   {
      __pointer(::message::show_window) pshowwindow(pmessage);
      if(pshowwindow->m_bShow)
      {
         m_durationLastError= ::duration::now();
         m_bOk = false;
      }
   }


   void prompt_impact::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      if (pcreate->previous())
      {

         return;

      }

      m_durationCaretStart= ::duration::now();

   }


   void prompt_impact::interpret_command()
   {

      bool m_bOk = true;

      if(m_strCommand == ":q")
      {

         ::parallelization::set_finish(System);

      }
      else
      {

         m_durationLastError= ::duration::now();

         m_bOk = false;

      }

      if(m_bOk)
      {

         clear();

      }

   }


   void prompt_impact::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      m_durationCaretStart.Now();

      ::message::key & key = *pkey;

      if(key.m_ekey == ::user::e_key_escape)
      {

         GetTypedParent < prompt_frame > ()->hide();

         papplication->m_puiMain->m_puiThis->SetActiveWindow();

         clear();

      }
      else if(key.m_ekey == ::user::e_key_return)
      {

         interpret_command();

      }
      else if(key.m_ekey == ::user::e_key_shift || key.m_ekey == ::user::e_key_left_shift || key.m_ekey == ::user::e_key_right_shift
              || key.m_ekey == ::user::e_key_control || key.m_ekey == ::user::e_key_left_control || key.m_ekey == ::user::e_key_right_control
              || key.m_ekey == ::user::e_key_alt || key.m_ekey == ::user::e_key_left_alt || key.m_ekey == ::user::e_key_right_alt
             )
      {


      }
      else if(pkey->m_ekey == ::user::e_key_back)
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
      else if(pkey->m_ekey == ::user::e_key_delete)
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
      else if(pkey->m_ekey == ::user::e_key_left)
      {

         if(m_iCursor <= 0)
            return;

         m_iCursor--;

         return;

      }
      else if(pkey->m_ekey == ::user::e_key_right)
      {

         if(m_iCursor >= m_strCommand.utf8_get_length())
            return;

         m_iCursor++;

         return;

      }
      else
      {

         string str;

         if(pkey->m_ekey == ::user::e_key_space)
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


   void prompt_impact::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }

   void prompt_impact::simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics)
   {
      //if(GetTypedParent <prompt_frame>()->get_display() != ::e_display_minimal)
      {
         ::user::impact::simple_ui_draw_focus_rect(pgraphics);
      }
   }


   int prompt_impact::getch()
   {

      m_durationCaretPeriod.Now();

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



      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      ::write_text::font_pointer f(e_create);

      f->create_pixel_font("Consolas",16.0);

      pgraphics->SelectObject(f);

      ::u32 dwAlpha = 123;

      color32_t crTopic;

      if(m_durationLastError.elapsed() < 84 && !m_bOk)
      {

         crTopic = argb(255,255,0,210);

      }
      else
      {

         m_bOk = true;

         crTopic = argb(255,100,210,84);

      }

      bool bCaretOn = m_durationCaretStart.on_off(m_durationCaretPeriod);

      auto rectangleClient = get_client_rect();

      m_sizeChar = pgraphics.get_text_extent("M");
      
      m_sizeChar = m_sizeChar.maximum(pgraphics.get_text_extent("p"));

      pgraphics->fill_rectangle(rectangleClient,argb(dwAlpha,0,0,0));

      pgraphics->set_text_color(crTopic);

      int i;

      int iLeftMargin = 2;

      for( i = 0; i < m_strCommand.length(); i++)
      {

         pgraphics->text_out(iLeftMargin +m_sizeChar.cx *i,0,m_strCommand.Mid(i,1));

      }

      if(bCaretOn)
      {

         ::rectangle_i32 rectangleCaret;

         rectangleCaret.left = (::i32) (iLeftMargin+m_sizeChar.cx * m_iCursor);
         rectangleCaret.right = rectangleCaret.left + m_sizeChar.cx;
         rectangleCaret.top = m_sizeChar.cy - 3;
         rectangleCaret.bottom = m_sizeChar.cy;



         pgraphics->fill_rectangle(rectangleCaret,crTopic);

      }

   }


   bool prompt_impact::keyboard_focus_is_focusable()
   {

      return true;

   }


} // namespace console








































