#pragma once


#include "acme/primitive/data/_data.h"

#include "core/filesystem/filehandler/_filehandler.h"

#include "tree_interface.h"


inline stream& operator <<(stream& s, const ::filehandler::handler& handler)
{

   return s << *handler.m_ptree;

}


inline stream& operator >>(stream& s, ::filehandler::handler& handler)
{

   return s >> *handler.m_ptree;

}


