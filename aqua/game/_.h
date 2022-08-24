#pragma once


namespace aura
{


   class game;


} // namespace aura


#define __namespace_game(NAMESPACE) (*(::NAMESPACE::game*)App(this).m_pgame->m_thisa[1])



