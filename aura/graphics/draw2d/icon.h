#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA icon :
      virtual public ::object
   {
   public:

      
      void *                        m_picon;
      map < size, size, void * >    m_iconmap;
      bool                          m_bAutoDelete;
      string                        m_strAppTrayIcon;
      size                          m_size;
      __pointer(size_image)         m_pimagemap;


      icon();
      virtual ~icon();


      virtual ::estatus     initialize(::object * pobjectContext) override;


      operator void *();
#ifdef WINDOWS
      operator HICON();
      virtual HICON get_os_data();
#else
      virtual void * get_os_data();
#endif


      virtual ::estatus     attach_os_data(void * picon, bool bTakeOwnership = true);

#ifdef WINDOWS

      virtual ::estatus     attach_os_data(HICON hicon, bool bTakeOwnership = true);

#endif


      bool load_file(string strPath);
      bool load_matter(string strPath);
      bool load_app_tray_icon(string strPath);


      ::size get_size();

      virtual void on_update_icon();

      image_pointer get_image(const ::size & size);

   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public int_map < icon * >
   {
   public:

   };


} // namespace draw2d


#ifdef WINDOWS_DESKTOP

CLASS_DECL_AURA HICON load_icon(::object * pobject, string_array & straMatter, string strIcon, int cx, int cy);

#endif

