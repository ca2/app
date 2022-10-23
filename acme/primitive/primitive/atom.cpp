﻿// Created by camilo on 2022-10-06 19:47 <3ThomasBorregaardSorensen!!
#include "framework.h"



atom::atom(const ::lparam & lparam)
{

   m_etype = e_type_integer;

   m_u = lparam.m_lparam;

}


atom::atom(const ::payload & payload)
{

   m_etype = e_type_integer;

   m_u = 0;

   if (payload.is_null())
   {

      operator = (e_type_null);

   }
   else if (payload.is_empty())
   {

      operator = (e_type_empty);

   }
   else if (payload.get_type() == ::e_type_id)
   {

      operator = (payload.m_atom);

   }
   else if (payload.is_integer())
   {

      operator = (payload.iptr());

   }
   else
   {

      operator = (payload.string());

   }

}




bool is_filemanager(const ::atom & atom)
{

   if(atom.is_text())
   {

      return ::str().begins(atom.m_str, "file_manager_");

   }

   return is_impact_group(atom.i64(), FILEMANAGER_IMPACT);

}


bool is_filemanager_group(const ::atom & atom, const char * pszGroup)
{

   if(!atom.is_text())
   {

      return false;

   }

   string strFileManagerGroup;

   strFileManagerGroup.format("file_manager_%s", pszGroup);

   if(atom == strFileManagerGroup)
   {

      return true;

   }

   strFileManagerGroup += "_";

   if(::str().begins(atom.m_str, strFileManagerGroup))
   {


      return true;

   }

   return false;

}


bool is_filemanager_group(const ::atom & atom, int iGroup)
{

   if(atom.is_text())
   {

      return false;

   }

   return is_impact_subgroup(atom.i64(), FILEMANAGER_IMPACT + iGroup);

}
