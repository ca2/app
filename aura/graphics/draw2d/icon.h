#pragma once


namespace draw2d
{


   /// <summary>
   /// icon * -> image_source_pointer concept
   /// </summary>
   class CLASS_DECL_AURA icon :
      virtual public ::matter
   {
   protected:


      void *                        m_picon;
      map < ::size, void * >        m_iconmap;
      __pointer(size_image)         m_pimagemap;
      // Sizes of Readily Available Icons in Increasing Sorting Order
      ::size_array                  m_sizea;
      bool                          m_bAutoDelete;
      string                        m_strAppTrayIcon;
      ::size                        m_size;

   public:

      

      icon();
      virtual ~icon();


      virtual ::e_status     initialize(::layered * pobjectContext) override;


      operator void *();
#ifdef WINDOWS
      operator HICON();
      virtual HICON get_os_data();
#else
      virtual void * get_os_data();
#endif


      virtual ::e_status     attach_os_data(void * picon, bool bTakeOwnership = true);

#ifdef WINDOWS

      virtual ::e_status     attach_os_data(HICON hicon, bool bTakeOwnership = true);

#endif


      string get_tray_icon_name();

      bool load_file(string strPath);
      bool load_matter(string strPath);
      bool load_app_tray_icon(string strPath);


      ::size get_size();
      ::size get_smaller_size(const ::size & size);

      virtual void on_update_icon();


      inline ::sized origin() const { return ::sized(); }


      image * get_image(const concrete < ::size > & size);
      image * get_image(const concrete < ::size > & size) const
      {

         return ((icon *)this)->get_image(size);

      }


      // inline concrete < ::size > size(const ::sized & sizeDst, const ::sized & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->size(sizeDst, sizeSrc, eimageselection); }
      inline concrete < ::size > size(const ::sized & sizeDst, enum_image_selection eimageselection) const { return get_image(sizeDst)->size(sizeDst, eimageselection); }
      inline concrete < ::size > size() const { return get_image(::sized())->size(); }

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public i32_map < icon * >
   {
   public:

   };


} // namespace draw2d


#ifdef WINDOWS_DESKTOP

CLASS_DECL_AURA HICON load_icon(::object * pobject, string_array & straMatter, string strIcon, int cx, int cy);

#endif

