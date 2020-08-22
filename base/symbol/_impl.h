#pragma once


inline message_box::message_box(const var& var)
{

   if (var.get_type() == type_string)
   {

      m_strMessage = var;

   }
   else if (var.has_property("message") && var["message"].has_char())
   {

      m_strMessage = var["message"];

   }
   else if (var.has_property("format") && var["format"].has_char())
   {

      m_strMessage = var.propset().format(var["format"]);

   }

   m_puserinteractionParent = var["parent"].cast < ::user::primitive >();
   m_strTitle = var["title"];
   m_uFlags = var["flags"];

   if (m_puserinteractionParent)
   {

      m_oswindow = m_puserinteractionParent->get_safe_handle();

   }

}



