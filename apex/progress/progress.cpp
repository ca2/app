// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "apex/user/primitive.h"


namespace progress
{


   progress::progress(::user::primitive * pprimitiveParent, const ::string & strTitle, ::count iStepCount)
   {

      auto puserinteractionTopLevel = pprimitiveParent->get_top_level();

      auto papp = pprimitiveParent->get_app();

      auto pprogress = papp->m_papplication->show_progress(puserinteractionTopLevel, strTitle, iStepCount);

      ___pointer<::progress::real>::operator =(pprogress);

   }


   progress::~progress() 
   {

      m_p->close_progress();

      release();

   }



} // namespace progress


