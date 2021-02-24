//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace apex
{


   class CLASS_DECL_APEX node :
      virtual public ::acme::node
   {
   public:


      node();
      virtual ~node();




      virtual void set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication);


      virtual ::file::path get_desktop_file_path(::apex::application * papplication) const;


      virtual void defer_notify_startup_complete();


      virtual ::e_status start();


#ifdef WINDOWS_DESKTOP

      virtual ::e_status register_dll(const ::file::path & pathDll);

#endif

   };


} // namespace apex



