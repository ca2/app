#pragma once


#include "acme/user/user/shell.h"


namespace android
{


   class CLASS_DECL_ACME shell :
      virtual public ::user::shell
   {
   public:


      class per_fork
      {
      public:

         //            ::windows::comptr < IImageList >                            m_pimagelistSmall;
         //            ::windows::comptr < IImageList >                            m_pimagelistLarge;
         //            ::windows::comptr < IImageList >                            m_pimagelistExtraLarge;
         //            ::windows::comptr < IImageList >                            m_pimagelistJumbo;
         //            ::windows::comptr < IMalloc >                               m_pmalloc;
         //            ::windows::comptr < IShellFolder >                          m_pfolderDesktop;
         //            ::windows::comptr < IShellFolder >                          m_pfolder;
         //            LPITEMIDLIST                                                m_lpiidl;
         string                                                      m_strFolder;

         per_fork(bool bInit = true);
         ~per_fork();

         void init();
         //void _017ItemIDListFree(LPITEMIDLIST lpiidl);

      };


      bool                                                        m_bStarted;
      delay_thread *                                              m_pdelayRelease;
      address_array < image_key * >                               m_keyptra;
      manual_reset_happening                                          m_happeningKey;
      ::pointer < ::mutex >                                                     m_pmutexQueue;
      pointer_array < ::thread >                                   m_threadaGetImage;


      shell();
      virtual ~shell();


      //virtual void initialize() override;

      //virtual void defer_start();
      //virtual void open_folder(oswindow oswindow, const ::scoped_string & scopedstrFolder);
      //virtual void close_folder(const ::scoped_string & scopedstrFolder);

      virtual int get_file_extension_image(const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
      virtual int impl_get_file_image( const image_key& imagekey) override;

      virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const ::wide_character * lpcszPath) override;
      virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const char * lpcszPath) override;

      //         int add_icon_set(per_fork * pfork, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, color32_t crBk, bool & bUsedImageList16, bool & bUsedImageList48);
      //
      //         int add_icon(int iSize, HICON hicon, color32_t crBk);
      //
      //         int add_icon_path(::file::path path, color32_t crBk);
      //
      //         int add_icon_info(per_fork * pfork, int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, color32_t crBk, bool & bUsedImageList16, bool & bUsedImageList48);
      //
      //         int add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, color32_t crBck, bool & bUsedImageList);


      //virtual bool do_call();
      //int calc_image_foo(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0);
      //int calc_get_image(oswindow oswindow, const ::scoped_string & scopedstrPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0);




      int get_image(per_fork * pfork, image_key key, const ::wide_character * lpcszExtra, color32_t crBk);
      int get_image_by_extension(per_fork * pfork, image_key & key, color32_t crBk);
      //bool get_icon(oswindow oswindow, const ::scoped_string & scopedstr, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
      //bool get_icon(oswindow oswindow, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
      //bool get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
      //         int get_image(oswindow oswindow, IShellFolder * lpsf, const ::file::path & path, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, e_icon eicon);
      //         int get_image(per_fork * pfork, oswindow oswindow, image_key key, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, color32_t crBk);
      //         //int get_image(per_fork * pfork, oswindow oswindow, image_key key, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, color32_t crBk);
      int get_foo_image(per_fork * pfork, oswindow oswindow, image_key key, color32_t crBk);



      //         ::windows::comptr < IShellFolder> _017GetShellParentFolder(per_fork * pfork, LPITEMIDLIST lpiidlChild);
      //         //::windows::comptr < IShellFolder> _017GetShellFolder(const ::scoped_string & scopedstr, LPITEMIDLIST lpiidlChild);
      //         ::windows::comptr < IShellFolder> _017GetShellFolder(per_fork * pfork, LPITEMIDLIST lpiidlChild);
      //         void _017ItemIDListParsePath(per_fork * pfork, oswindow oswindow, LPITEMIDLIST * lpiidl, const ::scoped_string & scopedstr);

      virtual void shell_run();




      //         virtual ::collection::index GetCSIDLSort(::collection::index iCsidl);
      //         virtual ::collection::index GetCSIDL(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         virtual void GetAscendants(per_fork * pfork, LPITEMIDLIST lpiidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
      //         virtual void Free(per_fork * pfork, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
      //
      //         //      string CLASS_DECL_ACME _017FilePathGetParent(const ::scoped_string & scopedstr);
      //
      //         HICON CalcIcon(LPITEMIDLIST lpiidl, const char * lpcszExtra, int cx, int cy);
      //         bool _017HasSubFolder(::particle * pparticle, LPITEMIDLIST lpiidl, const char * lpcszExtra);
      //         //      void CLASS_DECL_ACME GetChildren(string_array_base & stra, const char * lpcszPath);
      //         LPITEMIDLIST _017ItemIDListGetLast(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         LPITEMIDLIST _017ItemIDListDup(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         LPITEMIDLIST _017ItemIDListGetFolderParent(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         LPITEMIDLIST _017ItemIDListGetAbsolute(per_fork * pfork, LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl);
      //         bool _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2);



      //int run();


   };


} // namespace android



