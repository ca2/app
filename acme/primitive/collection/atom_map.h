//
// Created by camilo on 2022-10-22 18:48 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/primitive/atom.h"
#include "map.h"


template < typename TYPE, typename ARG_TYPE = typename argument_of < TYPE >::type, typename PAIR = pair < ::atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE > >
using atom_map = ::map < atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE, PAIR >;


using id_to_id = atom_map < atom >;


using id_to_index = atom_map < index >;



