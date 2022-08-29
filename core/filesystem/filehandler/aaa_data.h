#pragma once


#include "acme/primitive/data/_data.h"

#include "core/filesystem/filehandler/_component.h"

#include "tree_interface.h"

#include "handler.h"


inline stream& operator <<(stream& s, const ::filehandler::handler& handler)
{

   return s << *handler.m_ptree;

}


inline stream& operator >>(stream& s, ::filehandler::handler& handler)
{

   return s >> *handler.m_ptree;

}


