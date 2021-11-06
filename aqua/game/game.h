#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA game :
      virtual public ::timer_callback,
      virtual public channel
   {
   public:


      //void*                               m_thisaGame[16];
      ::aura::game *                      m_pauragame;
      __reference(::user::controller)     m_pcontroller;


      game();
      virtual ~game();

      
      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual string sound_path(const char* psz);


   };

}
