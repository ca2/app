// Created by camilo on 2022-10-06 19:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "payload.h"







bool is_filemanager(const ::atom & atom)
{

   if(atom.is_text())
   {

      return atom.m_str.begins("file_manager_");

   }

   return is_impact_group(atom.as_i64(), FILEMANAGER_IMPACT);

}


bool is_filemanager_group(const ::atom & atom, const ::scoped_string & scopedstrGroup)
{

   if(!atom.is_text())
   {

      return false;

   }

   string strFileManagerGroup;

   strFileManagerGroup.formatf("file_manager_%s", scopedstrGroup.c_str());

   if(atom == strFileManagerGroup)
   {

      return true;

   }

   strFileManagerGroup += "_";

   if(atom.m_str.begins(strFileManagerGroup))
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

   return is_impact_subgroup(atom.as_i64(), FILEMANAGER_IMPACT + iGroup);

}



bool is_color_sel(const ::atom & atom)
{
   
   return is_impact_group(atom.as_i64(), COLORSEL_IMPACT);

}


bool is_font_sel(const ::atom & atom) 
{
   
   return is_impact_group(atom.as_i64(), FONTSEL_IMPACT);

}


::string atom::as_string() const
{

   if (m_etype == e_type_null)
   {

      return "(null)";

   }
   else if (m_etype == e_type_empty)
   {

      return "(empty)";

   }
   else if (is_text())
   {

      return m_str;

   }
   else if (is_integer())
   {

      return ::transfer(::as_string(m_iLargest));

   }
   else
   {

      return ::transfer(::string("(atom : type:") + ::as_string(m_etype) + ",body:" + ::as_string(m_uLargest) + ")");

   }

}


bool atom::is_true(bool bDefault) const
{

   if(is_empty())
   {

      return bDefault;

   }

   switch(m_etype)
   {
      case e_type_status:
         return m_estatus.succeeded();
      case e_type_check:
         return __bool(m_echeck);
      default:
         break;
   };

   if(is_text())
   {

      return as_string().has_char();

   }
   else
   {

      return m_iLargest != 0;

   }

}
