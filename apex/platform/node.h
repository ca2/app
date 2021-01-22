//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace acme
{


   class CLASS_DECL_ACME node :
      virtual public ::context_object
   {
   public:


      node();
      virtual ~node();

      virtual void os_calc_user_dark_mode();

      virtual string os_get_user_theme();

      virtual void os_process_user_theme(string strTheme);

      virtual void os_launch_uri(const char * pszUri, char * pszError = NULL, int iBufferSize = 0);


   };


} // namespace linux



