//
// Created by camilo on 2022-10-22 18:48 <3ThomasBorregaardSorensen!!
//
#pragma once


template < typename TYPE, typename ARG_TYPE = typename argument_of < TYPE >::type, typename PAIR = pair < ::atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE > >
using atom_map = ::map < atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE, PAIR >;

