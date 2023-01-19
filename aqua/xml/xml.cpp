#include "framework.h"
#include "xml.h"
#include "edit.h"
#include "entity.h"
#include "disp_option.h"
#include "parse_info.h"
#include "document.h"
#include "acme/platform/system.h"


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


   void xml::init1()
   {

      //if(papp->is_system())
      //{

      factory()->add_factory_item < edit_item > ();

      //}

      ::acme::department::init1();

      //if (!::acme::department::init1())
      //{

      //   return ::error_failed;

      //}

      //auto estatus = 
      __construct_new(m_pentities);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pentities->add_entity('&', "&amp;");
      m_pentities->add_entity('\"', "&quot;");
      m_pentities->add_entity('\'', "&apos;");
      m_pentities->add_entity('<', "&lt;");
      m_pentities->add_entity('>', "&gt;");

      m_poptionDefault     = __new(disp_option(m_pentities));

      m_pparseinfoDefault  = __new(parse_info(m_pentities));

      //return true;

   }


   void xml::init()
   {

      ::acme::department::init();

      //if (!)
      //{

      //   return false;

      //}

      //return true;

   }

   
   //::pointer<::xml::document>xml::create_document()
   //{ 
   //   
   //   auto pxmldocument = __create_new < ::xml::document >(); 

   //   return ::transfer(pxmldocument);

   //}


   string xml::special_chars(const ::scoped_string & scopedstr)
   {

      string str(scopedstr);

      str.replace_with("&amp;", "&");
      str.replace_with("&quot;", "\"");      // quando ENT_NOQUOTES n縊 est・definida.
      str.replace_with("&#039;", "'");       // apenas quando ENT_QUOTES est・definida.
      str.replace_with("&lt;", "<");
      str.replace_with("&gt;", ">");

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

         opt = acmesystem()->xml()->m_poptionDefault;

      }

      string str;

      str = prop.name();
      str += "=";
      str += opt->m_chQuote;
      string strValue;
      if (opt->m_bReferenceValue && opt->m_pentities)
         strValue = opt->m_pentities->entity_to_ref(prop.as_string());
      else
         strValue = prop;

      strValue.replace_with("\\\\", "\\"); // should be first
      strValue.replace_with("\\n", "\n");
      strValue.replace_with("\\t", "\t");
      strValue.replace_with("\\r", "\r");
      strValue.replace_with("\\'", "'");
      strValue.replace_with("\\\"", "\"");

      str += strValue;
      str += opt->m_chQuote;
      str += " ";

      return str;

   }


} //namespace xml



// CLASS_DECL_AQUA void xml_export(::particle * pparticle, string & strXml, xml::exportable & exportable)
// {

//    ::xml::output_tree o(pparticle);

//    o.m_pdocument = __new(::xml::document(pparticle));

//    o.m_pnode = o.m_pdocument->get_root();

//    exportable.xml_export(o);

//    strXml = o.m_pdocument->get_xml();

// }


// CLASS_DECL_AQUA void xml_import(::particle * pparticle, xml::importable & importable, string & strXml)
// {

//    ::xml::input_tree i(pparticle);

//    i.m_pdocument = __new(xml::document(pparticle));

//    if (i.m_pdocument->load(strXml))
//    {

//       i.m_pnode = i.m_pdocument->get_root();

//       importable.xml_import(i);

//    }

// }

