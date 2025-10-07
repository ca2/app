#include "framework.h"
#include "game.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/context.h"


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


   string game::sound_path(const ::scoped_string & scopedstr)
   {
   
      string strFileName = string(scopedstr) + string(".wav");

      string strFilePath = directory()->matter(strFileName);

      return ::transfer(strFilePath);

   }


} // namespace game



