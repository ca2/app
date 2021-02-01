#pragma once

using hicon = void *;

namespace draw2d
{


   /// <summary>
   /// icon * -> image_source_pointer concept
   /// </summary>
   class CLASS_DECL_AURA icon :
      virtual public ::matter
   {
   protected:


      __pointer(::windowing::icon)  m_picon;
      map < ::size_i32, void * >    m_iconmap;
      __pointer(size_image)         m_pimagemap;
      // Sizes of Readily Available Icons in Increasing Sorting Order
      ::size_array                  m_sizea;
      bool                          m_bAutoDelete;
      string                        m_strAppTrayIcon;
      ::size_i32                        m_size;

   public:

      

      icon();
      virtual ~icon();


      virtual ::e_status     initialize(::layered * pobjectContext) override;


      virtual windowing::icon * get_windowing_icon();


      //virtual ::e_status     attach_os_data(void * picon, bool bTakeOwnership = true);



      string get_tray_icon_name();

      //bool load_file(string strPath);


      ::size_i32 get_size();
      ::size_i32 get_smaller_size(const ::size_i32 & size);

      virtual void on_update_icon();


      inline ::size_f64 origin() const { return ::size_f64(); }


      image * get_image(const concrete < ::size_i32 > & size);
      image * get_image(const concrete < ::size_i32 > & size) const
      {

         return ((icon *)this)->get_image(size);

      }


      // inline concrete < ::size_i32 > size_i32(const ::size_f64 & sizeDst, const ::size_f64 & sizeSrc, enum_image_selection eimageselection) const { return get_image(sizeDst)->size_i32(sizeDst, sizeSrc, eimageselection); }
      inline concrete < ::size_i32 > size_i32(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const { return get_image(sizeDst)->size_i32(sizeDst, eimageselection); }
      inline concrete < ::size_i32 > size() const { return get_image(::size_f64())->size(); }

         
   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public i32_map < icon * >
   {
   public:

   };


} // namespace draw2d


#ifdef WINDOWS_DESKTOP

CLASS_DECL_AURA hicon load_icon(::object * pobject, string_array & straMatter, string strIcon, int cx, int cy);

#endif

