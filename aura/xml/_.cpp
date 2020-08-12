#include "framework.h"
#include "aura/xml/_.h"


namespace xml
{


   CLASS_DECL_AURA string get(const property & prop, ::xml::disp_option * opt /*= &optDefault*/)
   {
      //   ::text_stream ostring;
      //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";

      //   ostring << (const char *)m_strName << L"=" << (CHAR)opt->m_chQuote
      //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
      //      << (CHAR)opt->m_chQuote << L" ";
      //   return ostring.str();

      if (opt == ((::xml::disp_option *) 1))
      {

         opt = System.xml().m_poptionDefault;

      }

      string str;

      str = prop.name();
      str += "=";
      str += opt->m_chQuote;
      string strValue;
      if (opt->m_bReferenceValue && opt->m_pentities)
         strValue = opt->m_pentities->entity_to_ref(prop.get_string());
      else
         strValue = prop.get_string();

      strValue.replace("\\", "\\\\"); // should be first
      strValue.replace("\n", "\\n");
      strValue.replace("\t", "\\t");
      strValue.replace("\r", "\\r");
      strValue.replace("'", "\\'");
      strValue.replace("\"", "\\\"");

      str += strValue;
      str += opt->m_chQuote;
      str += " ";

      return str;

   }


} // namespace xml


