#pragma once


#include "acme/primitive/comparison/equals.h"


#include "acme/primitive/primitive/trait_predicate.h"




template < typename PRED >
inline void add_handler(::message::handler_array& handlera, PRED pred)
{

   handlera.add(__handler(pred));

}

