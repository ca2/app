

namespace acme
{


   class console
   {
   public:

      
      void m_estatus;
      //::pointer<::acme::system>acmesystem();

   //   void create_system()
   //   {
   //
   //      acme_ref();
   //
   //      //acmesystem() = ::pointer_transfer(platform_create_system(::GetModuleHandle(NULL)));
   //
   ////      acmesystem() = __new(::acme::system());
   //
   //      //acmesystem()->console_initialize();
   //
   //
   //
   //   }

      void common_construct()
      {

         //create_system();

         //application_common(acmesystem());

      }


      console(int argc, char ** argv)
      {

         common_construct();
         
         //acmesystem()->system_construct(argc, argv);

         init();

      }


      console(int argc, wchar_t ** argv)
      {

         common_construct();

         //acmesystem()->system_construct(argc, argv);

         init();

      }


      void init()
      {

         //m_estatus = (void) acmesystem()->inline_init();

         m_estatus = ::success;

      }


      int result()
      {

         //m_estatus = papp->m_estatus;

         ::i32 iErrorStatus = m_estatus.error_status();

         //acmesystem()->inline_term();

         //acmesystem().release();

         return iErrorStatus;

      }


      ~console()
      {

         //if (acmesystem())
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



