// Created by camilo on 2022-10-06 06:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "exception.h"


namespace xml
{


   exception::exception(enum_parse_error eparseerror, const ::scoped_string & scopedstrMessage, const char * xml) :
      ::exception(error_xml_parsing, scopedstrMessage)
   {

      m_eparseerror = eparseerror;
      m_strXml = ::string(xml, 1024);

   }


} // namespace xml



