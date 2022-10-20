// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "apex/user/primitive.h"
#include "apex/platform/application.h"


namespace progress
{


   progress::progress(::user::primitive * pprimitiveParent, const ::string & strTitle, ::count iStepCount)
   {

      auto puserinteractionTopLevel = pprimitiveParent->_top_level();

      auto papp = pprimitiveParent->get_app();

      auto pprogress = papp->m_papexapplication->show_progress(puserinteractionTopLevel, strTitle, iStepCount);

      ::pointer<::progress::real>::operator =(pprogress);

   }


   progress::~progress() 
   {

      m_p->close_progress();

      release();

   }



} // namespace progress


