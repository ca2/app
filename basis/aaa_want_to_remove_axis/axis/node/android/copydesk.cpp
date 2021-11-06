#include "framework.h"
#include "_.h"


namespace android
{


   copydesk::copydesk(::object * pobject) :
      ::object(pobject),
      ::user::copydesk(pobject)
   {
   }

   copydesk::~copydesk()
   {
   }

   i32 copydesk::get_file_count()
   {
      return 0;
   }


   void copydesk::get_filea(::file::patha & patha)
   {

      patha.add("this_file_does_not_exist_please_implement_android_copydesk_get_filea.txt");

   }

   void copydesk::set_filea(const ::file::patha & patha)
   {

      __throw(todo);

   }



   bool copydesk::initialize()
   {


      if(!::user::copydesk::initialize())
         return false;

      return true;

   }


   bool copydesk::destroy()
   {

      bool bOk;

      bOk = ::user::copydesk::destroy();

//      if(::user::interaction_impl *::is_set() && ::user::interaction_impl *::m_p->is_window())
      {
         //       bOk = ::user::interaction_impl *::m_p->DestroyWindow() != false;
      }
      //  else
      {
         bOk = false;
      }

      return bOk;

   }

   void copydesk::set_plain_text(const ::string & psz)
   {

      __throw(todo);


   }


   string copydesk::get_plain_text()
   {

      return "this text was not actually copied please_implement_android_copydesk_get_plain_text";

   }

/*   bool copydesk::desk_to_image(::image * pimage)
   {

      __throw(todo);

   }


} // namespace linux


