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


      virtual ::e_status on_initialize_object() override;

      virtual void dpi_os_initialize();


//#ifdef LINUX

  //    virtual ::linux::appindicator * appindicator_allocate();
    //  virtual void appindicator_destroy(::linux::appindicator * pappindicator);

//#endif


      virtual ::image_pointer get_file_image_by_type_identifier(int iSize, const char * pszTypeIdentifier);

      virtual ::image_pointer get_file_image(int iSize, const char * pszPath);
      
      virtual void defer_dock_application(bool bDock);

      void set_application_menu(::application_menu * pmenu, ::application * papplication) override;

//      virtual void * node_wrap_window(void * pdisplay, i64 window);

      //using apex::node::user_fork;

      //virtual void user_fork(const ::routine & routine) override;

      inline ::windowing::windowing * windowing() { return m_pwindowing; }


   };


} // namespace aura



