#include "framework.h"
#include "game.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/platform/context.h"


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


   string game::sound_path(const ::scoped_string & scopedstr)
   {
   
      auto strFileName = scopedstr + ".wav";

      auto strFilePath = dir()->matter(strFileName);

      return strFilePath;

   }


} // namespace game



