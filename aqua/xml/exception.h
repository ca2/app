// Created by camilo on 2022-10-06 06:44 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/exception/exception.h"


namespace xml
{

   
   class CLASS_DECL_AQUA exception :
      virtual public ::exception
   {
   public:


      enum_parse_error        m_eparseerror;       // [get] error code
      ::string                m_strXml;


      exception(enum_parse_error eparserror, const ::scoped_string & scopedstrMessage, const char * xml);


   };


} // namespace xml



