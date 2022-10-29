#pragma once


#include "acme/platform/timer_callback.h"
#include "apex/message/channel.h"


namespace aqua
{


   class CLASS_DECL_AQUA game :
      virtual public ::timer_callback,
      virtual public channel
   {
   public:


      //void*                               m_thisaGame[16];
      ::aura::game *                      m_pauragame;
      ::pointer<::user::controller>    m_pcontroller;


      game();
      ~game() override;

      
      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void destroy() override;

      virtual string sound_path(const char* psz);


   };

}
