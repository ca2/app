/// Created by camilo on 2026-05-28 12:34 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "key_state.h"
#include "acme/constant/key_state.h"


namespace user
{


   key_state::key_state()
   {

      m_ekeystate = ::user::e_key_state_none;

   }


   key_state::key_state(const ::user::e_key_state & ekeystate): m_ekeystate(ekeystate)
   {

   }


   key_state::key_state(const ::user::key_state &keystate): m_ekeystate(keystate.m_ekeystate) {}



   key_state::~key_state()
   {


   }


       key_state & key_state::operator = (const ::user::key_state &keystate) {
       if (this != &keystate) {
           m_ekeystate = keystate.m_ekeystate;
       }
       return *this;
   }
       key_state & key_state::operator = (const ::user::key_state * pkeystate) {
       if (this != pkeystate) {
           m_ekeystate = pkeystate->m_ekeystate;
       }
       return *this;

   }



   bool key_state::is_mouse_state(const ::user::e_key_state &ekeystate) const
   {

      return (m_ekeystate & ::user::e_key_state_mouse_mask) == ekeystate;

   }


   i32_boolean key_state::has_mouse_state(const ::user::e_key_state &ekeystate) const
   {
      
      return m_ekeystate & ekeystate; 
   
   }


} // namespace user
