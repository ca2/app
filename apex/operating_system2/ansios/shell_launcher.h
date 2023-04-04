#pragma once


namespace ansios
{


#ifndef UNIVERSAL_WINDOWS


   // created near revision 4405
   // this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
   // to detect erronous adaptations of replacement


   class CLASS_DECL_APEX shell_launcher :
      virtual public ::apex::shell_launcher
   {
   public:


   bool        m_bOk;
   i32         m_dwResult;
   i32         m_pid;

protected:


   i32         m_iMode;


public:


   shell_launcher(time timeTimeout = ::one_minute());
   shell_launcher(::windowing::window * pwindow, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParameters, const ::scoped_string & scopedstrDirectory, ::e_display edisplay, time timeTimeout = ::one_minute());


   void execute();


   bool succeeded();


   };


#endif


} // namespace ansios



