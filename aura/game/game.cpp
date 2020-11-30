#include "framework.h"


namespace aura
{


   game::game()
   {

      m_thisaGame[0] = this;

   }


   game::~game()
   {


   }


   void game::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



   }


   string game::sound_path(const char* psz)
   {
   
      string strFileName = string(psz) + string(".wav");

      string strFilePath = Context.dir().matter(strFileName);

      return strFilePath;

   }


} // namespace game



