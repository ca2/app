#pragma once


namespace apex
{


#ifndef _UWP


   // created near revision 4405
   // this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
   // to detect erronous adaptations of replacement


   class CLASS_DECL_APEX shell_launcher :
      virtual public ::matter
   {
   public:


      oswindow             m_oswindow;
      string               m_strOperation;
      string               m_strFile;
      string               m_strParameters;
      string               m_strDirectory;
      ::e_display          m_edisplay;
      ::e_activation       m_eactivation;
      duration             m_durationTimeout;
      ::e_status          m_estatus;


   protected:


      i32                  m_iMode;


   public:


      shell_launcher();
      virtual ~shell_launcher();

      virtual void setup(duration durationTimeout = ::minute());
      virtual void setup(oswindow oswindow, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, ::e_display edisplay, duration durationTimeout = ::minute());

      virtual void launch();


      inline ::e_status status() const {return m_estatus;}


   };


#endif


} // namespace apex



