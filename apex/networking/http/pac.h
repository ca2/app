//
// Created by camilo on 2024-10-29 01:29 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace http
{


   class CLASS_DECL_APEX pac :
      virtual public ::object
   {
   public:


      ::url::url              m_url;
      string                  m_strAutoConfigScript;
      ::pointer < tinyjs >    m_pjs;
      class ::time            m_timeLastChecked;


      //pac(::particle * pparticle);
      pac();


      ~pac() override;


   };


} // namespace http




