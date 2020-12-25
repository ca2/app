#include "framework.h"


namespace calculator
{


   frame::frame(::layered * pobjectContext) :
      ::object(pobject),
      simple_frame_window(pobject)
   {

      m_pimagelist = nullptr;



      window_enable_full_screen();

   }

   frame::~frame()
   {
   }

   void frame::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

      m_pimagelist = new image_list(get_object());
      m_pimagelist->create(16, 16, 0, 10, 10);


   }


   bool frame::pre_create_window(::user::create_struct * pcreatestruct)
   {

      if( !simple_frame_window::pre_create_window(pcreatestruct) )
         return FALSE;

      pcreatestruct->m_createstruct.dwExStyle &= ~WS_EX_WINDOWEDGE;

      return TRUE;
   }

   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }



   void frame::OnTimer(::u32 uEvent)
   {
      static float theta;
      if(uEvent == 3)
      {

      }
      else if(uEvent == 1000)
      {

         display();
         
         KillTimer(uEvent);

         m_bTimerOn = false;

      }
      else if(uEvent == 8913)
      {
      }
      else if(uEvent == 4033)
      {
         // OpenGL animation code goes here

         //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
         //glClear( GL_COLOR_BUFFER_BIT );

         /*glPushMatrix();
         glRotatef( theta, 0.0f, 1.0f, 1.0f );
         glBegin( GL_TRIANGLES );
         glColor3f( 1.0f, 0.0f, 0.0f ); glVertgenf( 0.0f, 1.0f );
         glColor3f( 0.0f, 1.0f, 0.0f ); glVertgenf( 0.87f, -0.5f );
         glColor3f( 0.0f, 0.0f, 1.0f ); glVertgenf( -0.87f, -0.5f );
         glEnd();
         glPopMatrix();*/

         //SwapBuffers( m_hdcOpenGL );

         theta += 2.0f;

      }
      //   simple_frame_window::OnTimer(uEvent);
   }


   void frame::ShowControlBars(bool bShow)
   {
      ::u32 nShow;
      if(bShow)
      {
         nShow = e_display_normal;
      }
      else
      {
         nShow = SW_HIDE;
      }

      /*   m_toolbar.ShowWindow(nShow);
         m_toolbarView.ShowWindow(nShow);
      //   m_statusbar.ShowWindow(nShow);
         m_menubar.ShowWindow(nShow);
         m_dialogbar.ShowWindow(nShow);*/

   }

} // namespace calculator



