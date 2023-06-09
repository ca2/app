//
//  session.h
//  acme
//
//  Created by camilo on 2022-12-01 11:27 BRT <3TBS_!!
//
#pragma once


#include "context.h"
#include "application_container.h"


namespace acme
{


   class CLASS_DECL_ACME session :
      virtual public ::acme::context,
      virtual public ::acme::application_container
   {
   public:


      index             m_iEdge;



      ::apex::session* m_papexsession;
      ::aqua::session* m_paquasession;
      ::aura::session* m_paurasession;
      ::axis::session* m_paxissession;
      ::base::session* m_pbasesession;
      ::bred::session* m_pbredsession;
      ::core::session* m_pcoresession;


      ::pointer<::text::context>                     m_ptextcontext;





      session();
      ~session() override;



      ::text::context* text_context() { return m_ptextcontext.get(); }


   };


} // namespace apex



