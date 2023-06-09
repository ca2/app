// From layout_state.cpp by camilo on 2022-08-27 12:23 <3ThomasBorregaardSorensen!! ThomasIsMyPriest!!
#include "framework.h"
#include "visual_state.h"


namespace user
{


   ::e_appearance visual_state::appearance() const
   {

      return m_eappearance;

   }


   visual_state & visual_state::operator = (const enum_appearance & eappearance)
   {

      m_eappearance = eappearance;

      return *this;

   }


   visual_state & visual_state::operator |= (const enum_appearance & eappearance)
   {

      m_eappearance |= eappearance;

      return *this;

   }


   visual_state & visual_state::operator -= (const enum_appearance & eappearance)
   {

      m_eappearance -= eappearance;

      return *this;

   }


   visual_state & visual_state::operator ^= (const enum_appearance & eappearance)
   {

      m_eappearance ^= eappearance;

      return *this;

   }


} // namespace user



