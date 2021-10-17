// Created by camilo on 2021-08-08 14:11 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


namespace progress
{


   progress::progress(::user::primitive * pprimitiveParent, const ::string & strTitle, ::count iStepCount)
   {

      auto puserinteractionTopLevel = pprimitiveParent->get_top_level();

      auto papplication = pprimitiveParent->get_application();

      auto pprogress = papplication->show_progress(puserinteractionTopLevel, strTitle, iStepCount);

      ___pointer<::progress::real>::operator =(pprogress);

   }


   progress::~progress() 
   {

      m_p->close_progress();

      release();

   }



} // namespace progress


