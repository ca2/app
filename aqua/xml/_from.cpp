#include "framework.h"
#include "aqua/xml.h"


namespace xml
{

   // get XML from the property considering it a node
   CLASS_DECL_AQUA string from(const property* pprop, ::xml::disp_option* opt /*= &optDefault*/)
   {

      return from(*pprop, opt);

   }


   // get XML from the property considering it XML attributes part of a node
   CLASS_DECL_AQUA string from(const property & prop, ::xml::disp_option * opt /*= &optDefault*/)
   {
      //   ::text_stream ostring;
      //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";

      //   ostring << (const char *)m_strName << L"=" << (char)opt->m_chQuote
      //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
      //      << (char)opt->m_chQuote << L" ";
      //   return ostring.str();

      if (opt == nullptr)
      {

         opt = System->xml().m_poptionDefault;

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


