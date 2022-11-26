//
// Created by camilo on 14/02/2021. 19:10 BRT <3TBS_!!
//
#pragma once


#include "apex/platform/shell_launcher.h"


namespace ansios
{


#ifndef _UWP


   // created near revision 4405
   // this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
   // to detect erronous adaptations of replacement


   class CLASS_DECL_APEX shell_launcher :
      virtual public ::apex::shell_launcher
   {
   public:


      shell_launcher();

      virtual ~shell_launcher();

      //virtual void setup(time timeTimeout = ::one_minute());
      //virtual void setup(oswindow oswindow, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, ::e_display edisplay, time timeTimeout = ::one_minute());

      virtual void launch();


      //inline void status() const {return m_estatus;}


   };


#endif


} // namespace ansios



