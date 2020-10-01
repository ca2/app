#pragma once


namespace aura
{


   class CLASS_DECL_AURA game :
      virtual public ::aqua::game,
      virtual public ::aura::drawable
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