//////////////////////////////////////////////////////
//
//  by camilo 24-08-2022 01-27 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace aura
{

   
   class game;


} // namespace aura


namespace aqua
{


   class game;


   class estamira;


} // namespace aqua


#define __namespace_game(NAMESPACE) (*(::NAMESPACE::game*)App(this).m_pgame->m_thisa[1])



