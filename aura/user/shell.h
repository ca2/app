#pragma once


namespace user
{


   class CLASS_DECL_AURA shell :
      virtual public ::task
   {
   public:


      enum enum_file_attribute
      {

         e_file_attribute_none,
         e_file_attribute_normal,
         e_file_attribute_directory,

      };


      enum enum_folder
      {

         e_folder_none,
         e_folder_file_system,
         e_folder_zip,

      };


      enum enum_icon
      {

         e_icon_normal,
         e_icon_open,

      };


      class CLASS_DECL_AURA image_key
      {
      public:


         string                                 m_strPath;
         string                                 m_strShellThemePrefix;
         enumeration < enum_file_attribute >    m_eattribute;
         enumeration < enum_icon >              m_eicon;
         i32                                    m_iIcon;
         string                                 m_strExtension;


         image_key();
         image_key(const image_key & imagekey);
         image_key(const ::string & strPath, const ::string & strShellThemePrefix, enum_file_attribute eattribute, enum_icon eicon);
         ~image_key();


         bool operator == (const image_key & key) const;
         void set_path(const ::string & strPath, bool bSetExtension = true);
         void set_extension(const ::string & strPath);


      };

      
      struct _get_file_image_
      {

         
         int               m_iImage;
         ::file::path      m_pathProcessed;
         ::file::path      m_pathFinal;
         image_key         m_imagekey;


      };


      template < typename VALUE, class ARG_VALUE = typename argument_of < VALUE >::type, class PAIR = pair < image_key, VALUE, typename argument_of < image_key >::type, ARG_VALUE > >
      using image_key_map = map< image_key, VALUE, typename argument_of < image_key >::type, ARG_VALUE, PAIR >;

      bool m_bGetFileImageByIconPath : 1;
      bool m_bGetFileImageByFileTypeImage : 1;
      bool m_bGetFileImageByFileImage : 1;

   protected:

      ::i32_map < __pointer(::image_list) >                                   m_pil; // int is the size_i32
      ::i32_map < __pointer(::image_list) >                                   m_pilHover; // int is the size;

   public:


      //class CLASS_DECL_AURA thread :
      //   virtual public ::thread
      //{
      //public:


      //   __reference(shell)         m_pshell;

      //   image_key                  m_imagekey;


         //thread(shell * pshell);
         //~thread() override;

//         ::e_status init_tashread() override;

         ::e_status run() override;

         ::e_status destroy() override;


      //};


      bool                                               m_bPendingUpdate;


   protected:


      int_array                                          m_iaSize;


   public:


      image_key_map < i32 >                              m_imagemap;
      image_key_map < image_key >                        m_imagekeymap;

      string                                             m_strShellThemePrefix;
      string_array                                       m_straThemeableIconName;
      __pointer(manual_reset_event)                      m_pevNewImageKey;

      index                                              m_iMaxThreadCount;
      index                                              m_iActiveThreadCount;
      index                                              m_iThread;
      ::mutex                                            m_mutexImage;
      //__pointer_array(thread)                            m_threadptra;
      millis                                               m_millisLastMax;
      ::u32                                              m_bMax;
      bool                                               m_bInitialized;

      ::array < image_key >                              m_imagekeySchedule;
      bool                                            m_bRequireHighQualityThumbnail;
      bool                                            m_bAddDefaultIcons;


      shell();
      ~shell() override;


      ::e_status initialize(::object * pobject) override;
      virtual void do_initialize();


      virtual _get_file_image_ * new_get_file_image();

      virtual ::file::path & processed_path(_get_file_image_ & getfileimage);
      virtual ::file::path & final_path(_get_file_image_ & getfileimage);

      inline ::aura::application * get_application() { return m_pcontext ? m_pcontext->m_pauraapplication : nullptr; }
      inline ::aura::session * get_session() { return m_pcontext ? m_pcontext->m_paurasession : nullptr; }
      inline ::aura::system * get_system() { return m_psystem ? m_psystem->m_paurasystem : nullptr; }


      //virtual void add_thread();

      
      virtual bool would_set_thumbnail_for(_get_file_image_ & getfileimage);

      virtual void on_update_sizes_interest();

      void add_size_interest(int_array iaSize);
      void set_size_interest(int_array iaSize);

      i32 _reserve_image(const image_key & key);

      bool contains_image(const image_key & imagekey, i32 & iImage);
      bool reserve_image(_get_file_image_ & getfileimage);


      virtual void get_scheduled_image_key(image_key & imagekey);


      virtual void on_add_default_file_image(_get_file_image_ & getfileimage);

      

      virtual void get_file_extension_image(_get_file_image_ & getfileimage);
      virtual i32 create_file_icon_image(const ::string & strPath, enum_file_attribute eattribute, enum_icon eicon, const string & strIcon, _get_file_image_ & getfileimage);
      virtual i32 _create_file_icon_image(const ::string & strPath, enum_file_attribute eattribute, enum_icon eicon, const string & strIcon, _get_file_image_ & getfileimage);



      virtual i32 get_file_image(const ::file::path & path, const ::user::shell::enum_file_attribute & eattribute, ::user::shell::enum_icon eicon);
      virtual i32 get_file_image(const image_key & imagekey);
      virtual i32 schedule_get_file_image(const image_key & imagekey);

      virtual bool get_image_by_file_extension(_get_file_image_ & getfileimage);

      virtual bool _get_file_image(_get_file_image_ & getfileimage);

      virtual bool defer_set_thumbnail(_get_file_image_ & getfileimage);
      
      virtual bool defer_get_file_image_by_icon_path(_get_file_image_ & getfileimage);
      
      virtual bool defer_get_file_image_by_file_type_image(_get_file_image_ & getfileimage);
      
      virtual bool defer_get_file_image_by_file_image(_get_file_image_ & getfileimage);





      //virtual i32 impl_get_file_image(const image_key & imagekey) = 0;


      ::image_list * GetImageList(int iSize);
      ::image_list * GetImageListHover(int iSize);


      virtual enum_folder get_folder_type(::object * pobject, const ::wstring & wstrPath);
      virtual enum_folder get_folder_type(::object * pobject, const ::string & strPath);


//      void set_image(int iIndex, int iSize, ::image * pimage);

      virtual void set_image(int iIndex, int iSize, ::image_drawing imagedrawing);
      virtual void set_icon(int iIndex, const ::file::path & pathIcon);


      //::e_status destroy() override;


   };


   inline bool shell::image_key::operator == (const image_key & key) const
   {
      return m_eattribute == key.m_eattribute
         && m_eicon == key.m_eicon
         && m_strExtension == key.m_strExtension
         && m_strShellThemePrefix == key.m_strShellThemePrefix
         && m_strPath == key.m_strPath
         && m_iIcon == key.m_iIcon;
   }


} // namespace user


template < >
inline u32 u32_hash<const ::user::shell::image_key &>(const ::user::shell::image_key & key)
{
   // default identity hash - works for most primitive values
   return hash_cat(u32_hash(key.m_strPath),
      hash_cat(u32_hash(key.m_strShellThemePrefix),
         hash_cat(u32_hash(key.m_strExtension),
            (((int)key.m_eicon) << 8) ^ (((int)key.m_eattribute) << 16)) ^ (((int)key.m_iIcon))));
}



template <  >
inline bool EqualElements(const ::user::shell::image_key & element1, const ::user::shell::image_key & element2)
{

   return element1 == element2;

}
