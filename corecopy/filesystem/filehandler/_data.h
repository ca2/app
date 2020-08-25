#pragma once


#include "aura/primitive/data/_data.h"


#include "tree_interface.h"


inline stream& operator <<(stream& s, const ::filehandler::handler& handler)
{

   return s << *handler.m_ptree;

}


inline stream& operator >>(stream& s, ::filehandler::handler& handler)
{

   return s >> *handler.m_ptree;

}


