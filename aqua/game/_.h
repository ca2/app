#pragma once


namespace aura
{


   class game;


} // namespace aura



#include "game.h"


#include "estamira.h"


#define __namespace_game(NAMESPACE) (*(::NAMESPACE::game*)App(get_context_object()).m_pgame->m_thisa[1])


