#pragma once


#include "aqua/game/game.h"
#include "aura/user/user/drawable.h"


namespace aura
{


   class CLASS_DECL_AURA game :
      virtual public ::aqua::game,
      virtual public ::user::drawable
   {
   public:


      __reference(::user::interaction)    m_pinteraction;


      game();
      ~game() override;

      
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      
      
      void destroy() override;


      virtual string sound_path(const ::string & psz);


   };


}  // namespace aura



