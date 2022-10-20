#include "framework.h"
#include "game.h"
#include "apex/filesystem/filesystem/dir_context.h"


namespace aura
{


   game::game()
   {

      //m_thisaGame[0] = this;

   }


   game::~game()
   {


   }


   void game::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



   }


   void game::destroy()
   {
   
   
   }


   string game::sound_path(const ::string & psz)
   {
   
      string strFileName = string(psz) + string(".wav");

      string strFilePath = m_pcontext->m_papexcontext->dir().matter(strFileName);

      return strFilePath;

   }


} // namespace game



