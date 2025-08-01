#pragma once


//#include "acme/filesystem/filesystem/path.h"
#include "acme/parallelization/task.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/platform/auto_pointer.h"
//#include "acme/prototype/collection/numeric_array.h"
//#include "acme/prototype/collection/string_array.h"


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
         int                                    m_iIcon;
         string                                 m_strExtension;


         image_key();
         image_key(const image_key & imagekey);
         image_key(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrShellThemePrefix, enum_file_attribute eattribute, enum_icon eicon);
         ~image_key();


         bool operator == (const image_key & key) const;
         void set_path(const ::scoped_string & scopedstrPath, bool bSetExtension = true);
         void set_extension(const ::scoped_string & scopedstrPath);

         inline operator ::hash32() const
         {
            // default identity hash - works for most primitive values
            return
               as_hash32(m_strPath) +
               as_hash32(m_strShellThemePrefix) +
               as_hash32(m_strExtension) +
               as_hash32(((int)m_eicon)) +
               as_hash32(((int)m_eattribute)) +
               as_hash32(((int)m_iIcon));
         }


      };

      
      struct _get_file_image_
      {

         
         int               m_iImage;
         ::file::path      m_pathProcessed;
         ::file::path      m_pathFinal;
         image_key         m_imagekey;


      };


      template < typename PAYLOAD, class PAIR = pair < image_key, PAYLOAD > >
      using image_key_map = map< image_key, PAYLOAD, PAIR >;

      bool m_bGetFileImageByIconPath : 1;
      bool m_bGetFileImageByFileTypeImage : 1;
      bool m_bGetFileImageByFileImage : 1;

   protected:

      ::int_map < ::image::image_list_pointer  >                          m_pimagelist; // int is the int_size
      ::int_map < ::image::image_list_pointer  >                          m_pimagelistHover; // int is the size;
      map < ::pointer < ::user::interaction >, ::string_array >      m_mapInterest;


   public:

      auto_pointer < _get_file_image_ > m_pgetfileimage;
      //class CLASS_DECL_AURA thread :
      //   virtual public ::thread
      //{
      //public:


      //   ::pointer<shell>        m_pshell;

      //   image_key                  m_imagekey;


         //thread(shell * pshell);
         //~thread() override;

         void init_task() override;

         void run() override;

         void destroy() override;


      //};


      bool                                               m_bPendingUpdate;


   protected:


      ::int_array                                          m_iaSize;


   public:


      image_key_map < int >                              m_imagemap;
      image_key_map < image_key >                        m_imagekeymap;

      string                                             m_strShellThemePrefix;
      string_array                                       m_straThemeableIconName;
      ::pointer<manual_reset_happening>                     m_pevNewImageKey;

      ::collection::index                                              m_iMaxThreadCount;
      ::collection::index                                              m_iActiveThreadCount;
      ::collection::index                                              m_iThread;
      ::pointer < ::mutex >                                            m_pmutexImage;
      //pointer_array < thread >                            m_threadptra;
      class ::time                                               m_timeLastMax;
      unsigned int                                              m_bMax;
      bool                                               m_bInitialized;

      ::array < image_key >                              m_imagekeySchedule;
      bool                                            m_bRequireHighQualityThumbnail;
      bool                                            m_bAddDefaultIcons;


      shell();
      ~shell() override;


      void initialize(::particle * pparticle) override;
      virtual void do_initialize();


      virtual _get_file_image_ * new_get_file_image();

      virtual ::file::path & processed_path(_get_file_image_ & getfileimage);
      virtual ::file::path & final_path(_get_file_image_ & getfileimage);

      //::aura::application * get_app();
      //::aura::session * get_session();
      //::aura::system * system();


      //virtual void add_thread();

      
      virtual bool would_set_thumbnail_for(_get_file_image_ & getfileimage);

      virtual void on_update_sizes_interest();

      void add_size_interest(::int_array iaSize);
      void set_size_interest(::int_array iaSize);

      int _reserve_image(const image_key & key);

      bool contains_image(const image_key & imagekey, int & iImage);
      bool reserve_image(_get_file_image_ & getfileimage);


      virtual void get_scheduled_image_key(image_key & imagekey);


      virtual void on_add_default_file_image(_get_file_image_ & getfileimage);

      

      virtual void get_file_extension_image(_get_file_image_ & getfileimage);
      virtual int create_file_icon_image(const ::scoped_string & scopedstrPath, enum_file_attribute eattribute, enum_icon eicon, const ::scoped_string & scopedstrIcon, _get_file_image_ & getfileimage);
      virtual int _create_file_icon_image(const ::scoped_string & scopedstrPath, enum_file_attribute eattribute, enum_icon eicon, const ::scoped_string & scopedstrIcon, _get_file_image_ & getfileimage);



      virtual int get_file_image(const ::file::path & path, const ::user::shell::enum_file_attribute & eattribute, ::user::shell::enum_icon eicon);
      virtual int get_file_image(const image_key & imagekey);
      virtual int schedule_get_file_image(const image_key & imagekey);

      virtual void warn_when_ok(const ::file::path & path, const ::user::interaction_array & userinteractionaInterested);

      virtual void warn_ok(const ::file::path & path);

      virtual bool get_image_by_file_extension(_get_file_image_ & getfileimage);

      virtual bool _get_file_image(_get_file_image_ & getfileimage);

      virtual bool defer_set_thumbnail(_get_file_image_ & getfileimage);
      
      virtual bool defer_get_file_image_by_icon_path(_get_file_image_ & getfileimage);
      
      virtual bool defer_get_file_image_by_file_type_image(_get_file_image_ & getfileimage);
      
      virtual bool defer_get_file_image_by_file_image(_get_file_image_ & getfileimage);





      //virtual int impl_get_file_image(const image_key & imagekey) = 0;


      ::image::image_list * GetImageList(int iSize);
      ::image::image_list * GetImageListHover(int iSize);


      //virtual enum_folder get_folder_type(::particle * pparticle, const ::wstring & wstrPath);
      virtual enum_folder get_folder_type(::particle * pparticle, const ::scoped_string & scopedstrPath);


//      void set_image(int iIndex, int iSize, ::image::image *pimage);

      virtual void set_image(int iIndex, int iSize, ::image::image_drawing imagedrawing);
      virtual void set_icon(int iIndex, const ::file::path & pathIcon);


      //void destroy() override;


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



template <  >
inline bool EqualElements(const ::user::shell::image_key & element1, const ::user::shell::image_key & element2)
{

   return element1 == element2;

}



