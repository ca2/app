//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#ifdef LINUX

namespace linux
{

   class appindicator;

}

#endif

namespace aura
{


   class CLASS_DECL_AURA node :
      virtual public ::apex::node
   {
   public:


      __pointer(::windowing::windowing)         m_pwindowing;


      node();
      ~node() override;


      virtual void on_initialize_object() override;

      virtual void dpi_os_initialize();

      virtual void message_box_factory();


      string system_options_html() override;



//#ifdef LINUX

  //    virtual ::linux::appindicator * appindicator_allocate();
    //  virtual void appindicator_destroy(::linux::appindicator * pappindicator);

//#endif


      virtual ::image_pointer get_file_image_by_type_identifier(int iSize, const char * pszTypeIdentifier);

      virtual ::image_pointer get_file_image(int iSize, const char * pszPath);
      
      virtual void defer_dock_application(bool bDock);

      void set_application_menu(::application_menu * pmenu, ::application * papp) override;

//      virtual void * node_wrap_window(void * pdisplay, i64 window);

      //using apex::node::user_fork;

      //virtual void user_fork(const ::routine & routine) override;

      inline ::windowing::windowing * windowing() { return m_pwindowing; }


      //__pointer(::extended::sequence < ::conversation >) message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox) override;


      void BeginWaitCursor();
      void EndWaitCursor();
      void RestoreWaitCursor();

#ifdef WINDOWS_DESKTOP

      virtual void* HICON_from_ico_file(const ::block& block);

#endif

   };


} // namespace aura



