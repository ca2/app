#include "framework.h"
#include "game.h"
#include "apex/filesystem/filesystem/dir_context.h"


namespace aqua
{


   game::game()
   {

      m_pauragame = nullptr;

   }


   game::~game()
   {


   }


   //void game::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{



   //}


   void game::destroy()
   {
      
      ::channel::destroy();
      
   }


   string game::sound_path(const char* psz)
   {
   
      string strFileName = string(psz) + string(".wav");

      string strFilePath = m_pcontext->m_papexcontext->dir().matter(strFileName);

      return strFilePath;

   }


} // namespace game



