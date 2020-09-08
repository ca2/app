#pragma once


namespace game
{


   class CLASS_DECL_AQUA game :
      virtual public ::aqua::drawable,
      virtual public ::timer_callback,
      virtual public channel
   {
   public:


      void*                               m_thisa[16];
      __reference(::user::interaction)    m_pinteraction;


      game();
      virtual ~game();

      
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual string sound_path(const char* psz);


   };

}