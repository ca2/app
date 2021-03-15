#include "framework.h"
#include "aqua/xml.h"


namespace xml
{


   xml::xml()
   {

      //m_poptionDefault     = nullptr;
      //m_pparseinfoDefault  = nullptr;

      m_pentitiesHashDefault = __new(string_to_string);

      m_pentitiesHashDefault->set_at("lt", "<");
      m_pentitiesHashDefault->set_at("gt", ">");
      m_pentitiesHashDefault->set_at("quot", "\"");
      m_pentitiesHashDefault->set_at("apos", "'");
      m_pentitiesHashDefault->set_at("amp", "&");


   }


   xml::~xml()
   {

      //::acme::del(m_poptionDefault);

      //::acme::del(m_pparseinfoDefault);

   }


   ::e_status xml::init1()
   {

      //if(papplication->is_system())
      //{

         create_factory < edit_item > ();

      //}

      if (!::apex::department::init1())
      {

         return ::error_failed;

      }

      auto estatus = __construct_new(m_pentities);

      if (!estatus)
      {

         return estatus;

      }

      m_pentities->add_entity('&', "&amp;");
      m_pentities->add_entity('\"', "&quot;");
      m_pentities->add_entity('\'', "&apos;");
      m_pentities->add_entity('<', "&lt;");
      m_pentities->add_entity('>', "&gt;");

      m_poptionDefault     = __new(disp_option(m_pentities));

      m_pparseinfoDefault  = __new(parse_info(m_pentities));

      return true;

   }


   ::e_status xml::init()
   {

      if (!::apex::department::init())
      {

         return false;

      }

      return true;

   }


   string xml::special_chars(const char * psz)
   {

      string str(psz);

      str.replace("&", "&amp;");
      str.replace("\"", "&quot;");      // quando ENT_NOQUOTES n縊 est・definida.
      str.replace("'", "&#039;");       // apenas quando ENT_QUOTES est・definida.
      str.replace("<", "&lt;");
      str.replace(">", "&gt;");

      return str;

   }



      // get XML from the property considering it a node
      string xml::from(const property* pprop, ::xml::disp_option* opt /*= &optDefault*/)
      {

         return from(*pprop, opt);

      }


      // get XML from the property considering it XML attributes part of a node
      string xml::from(const property& prop, ::xml::disp_option* opt /*= &optDefault*/)
      {
         //   ::text_stream ostring;
         //   //ostring << (const char *)m_strName << "='" << (const char *)m_strValue << "' ";

         //   ostring << (const char *)m_strName << L"=" << (char)opt->m_chQuote
         //      << (const char *)(opt->reference_value&&opt->m_pentities?opt->m_pentities->entity_to_ref(m_strValue):m_strValue)
         //      << (char)opt->m_chQuote << L" ";
         //   return ostring.str();

         if (opt == nullptr)
         {

            opt = get_system()->xml()->m_poptionDefault;

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




} //namespace xml



// CLASS_DECL_AQUA void xml_export(::object * pobject, string & strXml, xml::exportable & exportable)
// {

//    ::xml::output_tree o(pobject);

//    o.m_pdocument = __new(::xml::document(pobject));

//    o.m_pnode = o.m_pdocument->get_root();

//    exportable.xml_export(o);

//    strXml = o.m_pdocument->get_xml();

// }


// CLASS_DECL_AQUA void xml_import(::object * pobject, xml::importable & importable, string & strXml)
// {

//    ::xml::input_tree i(pobject);

//    i.m_pdocument = __new(xml::document(pobject));

//    if (i.m_pdocument->load(strXml))
//    {

//       i.m_pnode = i.m_pdocument->get_root();

//       importable.xml_import(i);

//    }

// }

