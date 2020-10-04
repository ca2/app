#pragma once


#include "aura/user/user/shell.h"


namespace macos
{

   
   class CLASS_DECL_AXIS shell :
      virtual public ::user::shell
   {
   public:
//
//      class per_fork
//      {
//      public:
//
//         string                                                      m_strFolder;
//
//         per_fork(bool bInit = true);
//         ~per_fork();
//
//         void init();
//
//      };

      string m_strEmpty;
      string   m_strFoo;
      bool                                                        m_bStarted;
      delay_thread *                                              m_pdelayRelease;
      address_array < image_key * >                                     m_keyptra;
      manual_reset_event                                          m_evKey;
      ::mutex                                                       m_mutexQueue;
      __pointer_array(::thread)                                               m_threadaGetImage;

      
      shell();
      virtual ~shell();


      virtual i32 impl_get_file_image(const image_key & imagekey) override;


      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const char * lpcszPath) override;

      
      i32 get_image(image_key key, const unichar * lpcszExtra, COLORREF crBk);
      i32 get_image_by_extension(image_key & key, COLORREF crBk);
      i32 get_foo_image(image_key key, COLORREF crBk);

      
      virtual void do_initialize() override;
      

   };


} // namespace macos



