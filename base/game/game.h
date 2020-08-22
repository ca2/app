#pragma once


namespace game
{


   class CLASS_DECL_AURA game :
      virtual public ::aura::drawable,
      virtual public ::timer_callback,
      virtual public channel
   {
   public:


      void*                               m_thisa[16];
      __reference(::user::impact)         m_pview;


      game();
      virtual ~game();

      
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual string sound_path(const char* psz);


   };

}