

namespace acme
{


   class console
   {
   public:

      
      ::e_status m_estatus;
      //__pointer(class ::system) m_psystem;

   //   void create_system()
   //   {
   //
   //      acme_ref();
   //
   //      //m_psystem = ::move_transfer(platform_create_system(::GetModuleHandle(NULL)));
   //
   ////      m_psystem = __new(class ::system());
   //
   //      //m_psystem->console_initialize();
   //
   //
   //
   //   }

      void common_construct()
      {

         //create_system();

         //application_common(m_psystem);

      }


      console(int argc, char ** argv)
      {

         common_construct();
         
         //m_psystem->system_construct(argc, argv);

         init();

      }


      console(int argc, wchar_t ** argv)
      {

         common_construct();

         //m_psystem->system_construct(argc, argv);

         init();

      }


      void init()
      {

         //m_estatus = (::e_status) m_psystem->inline_init();

         m_estatus = ::success;

      }


      int result()
      {

         //m_estatus = papplication->m_estatus;

         ::i32 iErrorStatus = m_estatus.error_status();

         //m_psystem->inline_term();

         //m_psystem.release();

         return iErrorStatus;

      }


      ~console()
      {

         //if (m_psystem)
         //{

         //   result();

         //}


      }


   };


   //int wmain(int argc, wchar_t* argv[])
   //{
   //
   //   console console(argc, argv);
   //
   //   main();
   //
   //   return console.result();
   //
   //}


} // namespace acme



