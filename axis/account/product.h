//
//  account_license.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 11/12/18.
//
#pragma once


#include "acme/primitive/primitive/object.h"


namespace account
{


   class CLASS_DECL_AXIS product :
      virtual public object
   {
   public:
      
      
      ::earth::time     m_timeRequest;
      string               m_strAppId;
      ::e_status           m_estatus;
      ::e_status           m_estatusLicensing;
      ::earth::time     m_timeValid;
      //bool                 m_bInteractive;
      string               m_strGateway;
      
      
      product();
      ~product() override;
      
      
      virtual void license(string strAppId, bool bInteractive);
      
      virtual bool do_license(string strAppId, bool bInteractive);
      
      virtual void _do_license(string strAppId, bool bInteractive);
      
      virtual bool is_ok();
      
      virtual bool is_licensed();
      
      
   };


} // namespace account



