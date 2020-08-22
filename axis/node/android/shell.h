#pragma once


#include "aura/user/user/shell.h"


namespace android
{


   class CLASS_DECL_AXIS shell :
      virtual public ::user::shell
   {
   public:


      class per_fork
      {
      public:

         //            ::windows::comptr < IImageList >                            m_pilSmall;
         //            ::windows::comptr < IImageList >                            m_pilLarge;
         //            ::windows::comptr < IImageList >                            m_pilExtraLarge;
         //            ::windows::comptr < IImageList >                            m_pilJumbo;
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
      manual_reset_event                                          m_evKey;
      ::mutex                                                     m_mutexQueue;
      __pointer_array(::thread)                                   m_threadaGetImage;


      shell();
      virtual ~shell();


      //virtual void initialize() override;

      //virtual void defer_start();
      //virtual void open_folder(oswindow oswindow, const string & strFolder);
      //virtual void close_folder(const string & strFolder);

      virtual i32 get_file_extension_image(const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;
      virtual i32 impl_get_file_image( const image_key& imagekey) override;

      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const widechar * lpcszPath) override;
      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const char * lpcszPath) override;

      //         int add_icon_set(per_fork * pfork, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48);
      //
      //         int add_icon(int iSize, HICON hicon, COLORREF crBk);
      //
      //         int add_icon_path(::file::path path, COLORREF crBk);
      //
      //         int add_icon_info(per_fork * pfork, int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48);
      //
      //         int add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, COLORREF crBck, bool & bUsedImageList);


      //virtual bool do_call();
      //i32 calc_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);
      //i32 calc_get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);




      i32 get_image(per_fork * pfork, image_key key, const widechar * lpcszExtra, COLORREF crBk);
      i32 get_image_by_extension(per_fork * pfork, image_key & key, COLORREF crBk);
      //bool get_icon(oswindow oswindow, const char * pcsz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
      //bool get_icon(oswindow oswindow, IShellFolder * lpsf, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
      //bool get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48);
      //         i32 get_image(oswindow oswindow, IShellFolder * lpsf, const char * pszPath, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, e_icon eicon);
      //         i32 get_image(per_fork * pfork, oswindow oswindow, image_key key, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, COLORREF crBk);
      //         //i32 get_image(per_fork * pfork, oswindow oswindow, image_key key, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, COLORREF crBk);
      i32 get_foo_image(per_fork * pfork, oswindow oswindow, image_key key, COLORREF crBk);



      //         ::windows::comptr < IShellFolder> _017GetShellParentFolder(per_fork * pfork, LPITEMIDLIST lpiidlChild);
      //         //::windows::comptr < IShellFolder> _017GetShellFolder(const string & str, LPITEMIDLIST lpiidlChild);
      //         ::windows::comptr < IShellFolder> _017GetShellFolder(per_fork * pfork, LPITEMIDLIST lpiidlChild);
      //         void _017ItemIDListParsePath(per_fork * pfork, oswindow oswindow, LPITEMIDLIST * lpiidl, const char * pcsz);

      virtual void shell_run();




      //         virtual index GetCSIDLSort(index iCsidl);
      //         virtual index GetCSIDL(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         virtual void GetAscendants(per_fork * pfork, LPITEMIDLIST lpiidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
      //         virtual void Free(per_fork * pfork, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla);
      //
      //         //      string CLASS_DECL_AXIS _017FilePathGetParent(const char * pcsz);
      //
      //         HICON CalcIcon(LPITEMIDLIST lpiidl, const char * lpcszExtra, i32 cx, i32 cy);
      //         bool _017HasSubFolder(::object * pobject, LPITEMIDLIST lpiidl, const char * lpcszExtra);
      //         //      void CLASS_DECL_AXIS GetChildren(string_array & stra, const char * lpcszPath);
      //         LPITEMIDLIST _017ItemIDListGetLast(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         LPITEMIDLIST _017ItemIDListDup(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         LPITEMIDLIST _017ItemIDListGetFolderParent(per_fork * pfork, LPITEMIDLIST lpiidl);
      //         LPITEMIDLIST _017ItemIDListGetAbsolute(per_fork * pfork, LPITEMIDLIST lpiidlParent, LPITEMIDLIST lpiidl);
      //         bool _017ItemIDListIsEqual(LPITEMIDLIST lpiidl1, LPITEMIDLIST lpiidl2);



      //int run();


   };


} // namespace android



