// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA icon :
      virtual public ::matter
   {
   public:


      string      m_strAppTrayIcon;


      icon();
      virtual ~icon();


      virtual iptr get_os_data() const;


      virtual bool load_matter(string strPath);
      virtual bool load_app_tray_icon(string strPath);
      virtual bool load_file(string strPath);


      virtual image * get_image(const concrete < ::size_i32 > & size);

//
//#ifdef WINDOWS
//
//      virtual ::e_status     attach_os_data(hicon hicon, bool bTakeOwnership = true);
//
//#endif


      
   };



} // namespace windowing



