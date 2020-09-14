#pragma once


#include "apex/primitive/data/_data.h"


#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filehandler/_filehandler.h"
#endif

#include "tree_interface.h"


inline stream& operator <<(stream& s, const ::filehandler::handler& handler)
{

   return s << *handler.m_ptree;

}


inline stream& operator >>(stream& s, ::filehandler::handler& handler)
{

   return s >> *handler.m_ptree;

}


