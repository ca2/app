#pragma once


#include "acme/user/user/shell.h"


namespace ios
{


   class CLASS_DECL_ACME shell :
      virtual public ::user::shell
   {
   public:
      

//      class per_fork
//      {
//      public:
//
//
//         string                                                      m_strFolder;
//
//         per_fork(bool bInit = true);
//         ~per_fork();
//
//         void init();
//
//      };
      

      bool                                                           m_bStarted;
      delay_thread *                                                 m_pdelayRelease;
      address_array < image_key * >                                  m_keyptra;
      manual_reset_happening                                             m_happeningKey;
      ::pointer < ::mutex >                                                        m_pmutexQueue;
      pointer_array < ::thread >                                      m_threadaGetImage;

      
      shell();
      virtual ~shell();


      virtual int impl_get_file_image(const image_key & imagekey) override;


      virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const char * lpcszPath) override;

       
      int get_image(image_key key, const unichar * lpcszExtra, color32_t crBk);
      int get_image_by_extension(image_key & key, color32_t crBk);
      int get_foo_image(image_key key, color32_t crBk);

       
      virtual void do_initialize() override;


   };


} // namespace windows

 

