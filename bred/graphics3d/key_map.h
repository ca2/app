// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 06:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/user_key.h"
#include "bred/graphics3d/types.h"


namespace graphics3d
{

   enum enum_key
   {

      e_key_moveLeft = 0,
      e_key_moveRight,
      e_key_moveForward,
      e_key_moveBackward,
      e_key_moveUp,
      e_key_moveDown,
      e_key_lookLeft,
      e_key_lookRight,
      e_key_lookUp,
      e_key_lookDown,
      e_key_Exit,
      e_key_count,

   };

   struct key_map_t
   {

      ::user::e_key m_ekeya[e_key_count];

      void map(::graphics3d::enum_key ekeyCube, ::user::e_key ekey)
      {

         m_ekeya[ekeyCube] = ekey;
      }
      //::user::e_key moveRight;
      //::user::e_key moveForward;
      //::user::e_key moveBackward;
      //::user::e_key moveUp;
      //::user::e_key moveDown;
      //::user::e_key lookLeft;
      //::user::e_key lookRight;
      //::user::e_key lookUp;
      //::user::e_key lookDown;
      //::user::e_key Exit;

   };

   class CLASS_DECL_BRED key_map :
      virtual public key_map_t,
      virtual public ::particle
   {
   public:

      ::pointer < ::user::graphics3d > m_pimpact;


      ::user::enum_key_state key(::graphics3d::enum_key ekey);



      ::block as_block() { return ::as_memory_block((key_map_t&)*this); }
   };



} // namespace graphics3d


