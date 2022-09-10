//
//  ds_script.h
//  programming
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2022-09-06 19:55
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#include "script.h"


namespace dynamic_source
{


   class CLASS_DECL_APP_PROGRAMMING ds_script :
      virtual public script
   {
   public:


      __pointer(::acme::library)       m_plibrary;


      file_time_set                     m_ft;
      file_time_set                     m_ftDs;

      bool                             m_bLastVersionCheck;
      ::duration                           m_durationLastVersionCheck;
      ::file::path                     m_strSourcePath;
      ::file::path                     m_strSourceDir;
      ::file::path                     m_strCppPath;
      ::file::path                     m_strScriptPath;
      manual_reset_event               m_evCreationEnabled;
      ::duration                           m_durationLastBuildTime;
      bool                             m_bShouldBuild;
      bool                             m_bShouldCalcTempError;
      bool                             m_bHasTempError;
      bool                             m_bHasTempOsError;
      bool                             m_bHasFatalError;
      bool                             m_bUnloading;
      NET_NODE_CREATE_INSTANCE_PROC    m_lpfnCreateInstance;


      ds_script();
      virtual ~ds_script();


      virtual void defer_build();
      virtual void on_start_build();

      bool DoesMatchVersion();
      bool ShouldBuild() override;
      virtual bool HasCompileOrLinkError() override;
      bool HasTempError();
      bool CalcHasTempError();
      bool HasDelayedTempError();
      bool HasTimedOutLastBuild();
      void Load();
      void Unload();

      string get_stage_path();


      //virtual ::aura::application * get_app() const override;

      __pointer(script_instance) create_instance() override;


   };


} // namespace dynamic_source



