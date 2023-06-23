#pragma once


#include "acme/primitive/primitive/particle.h"


namespace apex
{


#ifndef UNIVERSAL_WINDOWS


   // created near revision 4405
   // this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
   // to detect erronous adaptations of replacement


   class CLASS_DECL_APEX shell_launcher :
      virtual public ::particle
   {
   public:


      oswindow             m_oswindow;
      string               m_strOperation;
      string               m_strFile;
      string               m_strParameters;
      string               m_strDirectory;
      ::e_display          m_edisplay;
      ::e_activation       m_eactivation;
      class ::time         m_timeTimeout;
      ::e_status           m_estatus;


   protected:


      i32                  m_iMode;


   public:


      shell_launcher();
      virtual ~shell_launcher();

      virtual void setup(const class time & timeTimeout = 1_minute);
      virtual void setup(oswindow oswindow, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParameters, const ::scoped_string & scopedstrDirectory, ::e_display edisplay, const class time & timeTimeout = 1_minute);

      virtual void launch();


      inline ::e_status status() const {return m_estatus;}


   };


#endif


} // namespace apex



