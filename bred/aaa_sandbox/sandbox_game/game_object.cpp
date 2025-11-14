#include "framework.h"
#include "SceneFoundry/sandbox_game/game_object.h"


namespace sandbox_game
{


   game_object::game_object()
   {

   }


   void game_object::initialize_game_object(long long llId)
   {

      m_llId = llId;
   }


   long long game_object::getId()
   {
      return m_llId;
   }


   floating_sequence3 game_object::color()
   {
      return m_color;
   }


   ::graphics3d::transform &game_object::transform()
   {
      return m_transform;
   }


   ::graphics3d::IModel *game_object::model()
   {
      return m_pmodel;
   }


   void game_object::set_model(::graphics3d::IModel *pmodel)
   {
      m_pmodel = pmodel;
   }

} // namespace sandbox_game
