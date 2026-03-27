#pragma once


#include "apex/platform/app_consumer.h"
#include "code_application.h"
#include "berg/user/user/options_impact_handler.h"
#include "_constant.h"


namespace coding
{


   class CLASS_DECL_CODING options_impact_handler :
      virtual public ::app_consumer < application, ::user::options_impact_handler >
   {
   public:


//      //::pointer<::user::button>               m_pbutton[e_phase_count];
//      ::pointer<::user::check_box>              m_pcheckboxExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization;
//      ////::pointer<::user::button>             m_pbuttonApplicationList;
//      ////::pointer<::user::button>             m_pbuttonPrepareApplications;
//      ////::pointer<::user::button>             m_pbuttonProjectList;
//      ////::pointer<::user::button>             m_pbuttonPrepareProjects;
//      ////::pointer<::user::button>             m_pbuttonCmake;
//      ////::pointer<::user::button>             m_pbuttonClean;
//
//
//      //::pointer<::user::still>                m_pstill[e_phase_count];
//      ::pointer<::user::still>                  m_pstillExcludeAllFoldersExceptBoxFolderFromDropboxSynchronization;
//      ////::pointer<::user::still>              m_pstillApplicationList;
//      ////::pointer<::user::still>              m_pstillPrepareApplications;
//      ////::pointer<::user::still>              m_pstillProjectList;
//      ////::pointer<::user::still>              m_pstillPrepareProjects;
//      ////::pointer<::user::still>              m_pstillCmake;
//      ////::pointer<::user::still>              m_pstillClean;


      options_impact_handler();
      ~options_impact_handler() override;


      void create_options_impact(::user::interaction * pinteraction) override;


      //virtual integration* get_integration();


   };


} // namespace coding




