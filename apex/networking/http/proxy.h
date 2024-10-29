//
// Created by camilo on 2024-10-29 01:30 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace http
{


   class CLASS_DECL_APEX proxy :
      virtual public ::object
   {
   public:


      ::url::url        m_url;
      bool              m_bDirect;
      string            m_strProxy;
      i32               m_iPort;
      class ::time      m_timeLastChecked;


      //proxy(::particle * pparticle);
      proxy();
      ~proxy() override;


   };


} // namespace http



