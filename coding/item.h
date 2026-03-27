//
// Created by camilo on 05/03/23.
//
#pragma once


#include "_constant.h"


namespace coding
{


   class CLASS_DECL_CODING item :
      virtual public matter
   {
   public:


      e_integrate                                        m_eintegrate;
      ::pointer<::user::check_box>                       m_pcheckbox;
      ::pointer<::user::still>                           m_pstill;
      ::pointer<::user::still>                           m_pstillElapsed;
      ::pointer<::user::still>                           m_pstillStatus;
      ::pointer<::user::still>                           m_pstillStatusElapsed;
      ::string                                           m_strName1;
      ::string                                           m_strShortName;
      ::string                                           m_strRelease;
      bool                                               m_bInitialCheck;
      ::pointer < task_group >                           m_ptaskgroup;
      group* m_pgroup;
      ::collection::index  m_iIntegrate;
      //::pointer < ::operating_system::summary >          m_poperatingsystemsummary;


      item();
      ~item() override;
      
      


      virtual ::string get_integrate_item_name() const;

      virtual void integrate();
      


   };


} // namespace coding



