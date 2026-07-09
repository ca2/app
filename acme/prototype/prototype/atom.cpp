// Created by camilo on 2022-10-06 19:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "payload.h"


CLASS_DECL_ACME ::string file_manager_group(const ::atom &atom)
{

   if (!atom.is_text())
   {

      return "";

   }

   ::string str = atom.m_str;

   if (str == "file_manager_impact")
   {

      return "file_manager_impact";

   }
   else if (str.begins_eat("file_manager_impact_"))
   {

      return str;

   }

   return "";

}


bool is_file_manager(const ::atom & atom)
{

   auto strFileManagerGroup = file_manager_group(atom);

   if (strFileManagerGroup.is_empty())
   {

      return false;

   }

   return true;

}


//bool is_filemanager_group(const ::atom & atom, const ::scoped_string & scopedstrGroup)
//{
//
//   if(!atom.is_text())
//   {
//
//      return false;
//
//   }
//
//   string strFileManagerGroup;
//
//   strFileManagerGroup.formatf("file_manager_%s", scopedstrGroup.as_string().c_str());
//
//   if(atom == strFileManagerGroup)
//   {
//
//      return true;
//
//   }
//
//   strFileManagerGroup += "_";
//
//   if(atom.m_str.begins(strFileManagerGroup))
//   {
//
//
//      return true;
//
//   }
//
//   return false;
//
//}


//bool is_filemanager_group(const ::atom & atom, ::i32 iGroup)
//{
//
//   if(atom.is_text())
//   {
//
//      return false;
//
//   }
//
//   return is_impact_subgroup(atom.as_i64(), "file_manager_impact" + iGroup);
//
//}



::string color_selection_group(const ::atom & atom)
{
   
   //return is_impact_group(atom.as_i64(), "color_selection_impact");

      if (!atom.is_text())
   {

      return "";
   }

   ::string str = atom.m_str;

   if (str == "color_selection_impact")
   {

      return "color_selection_impact";
   }
   else if (str.begins_eat("color_selection_impact_"))
   {

      return str;
   }

   return "";

}

bool is_color_selection(const ::atom &atom)
{

   auto strColorSelectionGroup = color_selection_group(atom);

   if (strColorSelectionGroup.is_empty())
   {

      return false;
   }

   return true;
}



::string font_selection_group(const ::atom &atom)
{

   // return is_impact_group(atom.as_i64(), "color_selection_impact");

   if (!atom.is_text())
   {

      return "";
   }

   ::string str = atom.m_str;

   if (str == "font_selection_impact")
   {

      return "font_selection_impact";
   }
   else if (str.begins_eat("font_selection_impact_"))
   {

      return str;
   }

   return "";
}

//bool _is_font_sel(const ::atom & atom) 
//{
//   
//   return is_impact_group(atom.as_i64(), "font_selection_impact");
//
//}

bool is_font_selection(const ::atom &atom)
{

   auto strFontSelectionGroup = font_selection_group(atom);

   if (strFontSelectionGroup.is_empty())
   {

      return false;
   }

   return true;
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


::domain_id atom::as_domainid() const
{

   if(m_etype != e_type_domainid)
   {

      return {};

   }

   return m_domainid;

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
         return m_echeck.is_checked();
      default:
         break;
   };

   if(is_text())
   {

      return as_string().has_character();

   }
   else
   {

      return m_iLargest != 0;

   }

}
