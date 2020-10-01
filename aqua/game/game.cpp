#include "framework.h"


namespace aqua
{


   game::game()
   {


   }


   game::~game()
   {


   }


   //void game::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{



   //}


   string game::sound_path(const char* psz)
   {
   
      string strFileName = string(psz) + string(".wav");

      string strFilePath = Context.dir().matter(strFileName);

      return strFilePath;

   }


} // namespace game



