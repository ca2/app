#include "framework.h"
#include "aura/xml/_.h"


namespace xml
{


   department::department()
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


   department::~department()
   {

      //::acme::del(m_poptionDefault);

      //::acme::del(m_pparseinfoDefault);

   }


   ::estatus department::init1()
   {

      //if(Application.is_system())
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


   ::estatus department::init()
   {

      if(!::apex::department::init())
         return false;

      return true;

   }


   string department::special_chars(const char * psz)
   {

      string str(psz);

      str.replace("&", "&amp;");
      str.replace("\"", "&quot;");      // quando ENT_NOQUOTES n縊 est・definida.
      str.replace("'", "&#039;");       // apenas quando ENT_QUOTES est・definida.
      str.replace("<", "&lt;");
      str.replace(">", "&gt;");

      return str;

   }


} //namespace xml



// CLASS_DECL_AURA void xml_export(::object * pobject, string & strXml, xml::exportable & exportable)
// {

//    ::xml::output_tree o(pobject);

//    o.m_pdocument = __new(::xml::document(pobject));

//    o.m_pnode = o.m_pdocument->get_root();

//    exportable.xml_export(o);

//    strXml = o.m_pdocument->get_xml();

// }


// CLASS_DECL_AURA void xml_import(::object * pobject, xml::importable & importable, string & strXml)
// {

//    ::xml::input_tree i(pobject);

//    i.m_pdocument = __new(xml::document(pobject));

//    if (i.m_pdocument->load(strXml))
//    {

//       i.m_pnode = i.m_pdocument->get_root();

//       importable.xml_import(i);

//    }

// }

