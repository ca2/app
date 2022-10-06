// Created by camilo on 2022-10-06 06:44 <3ThomasBorregaardSorensen!!
#pragma once


namespace xml
{

   
   class CLASS_DECL_AQUA exception :
      virtual public ::exception
   {
   public:


      enum_parse_error        m_eparseerror;       // [get] error code
      ::string                m_strXml;


      exception(enum_parse_error eparserror, const ::string & strMessage, const char * xml);


   };


} // namespace xml



