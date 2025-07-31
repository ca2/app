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


      ::pointer<::user::interaction>   m_pinteraction;


      game();
      ~game() override;

      
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      
      
      void destroy() override;


      virtual string sound_path(const ::scoped_string & scopedstr);


   };


}  // namespace aura



