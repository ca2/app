#pragma once


CLASS_DECL_AURA void aura_ref();


namespace aura
{


   class console
   {
   public:


      void m_estatus;
      ::pointer<::aura::system>acmesystem();


      void create_system()
      {

         aura_ref();

         acmesystem() = ::pointer_transfer(platform_create_system(::GetModuleHandle(NULL)));

         acmesystem()->console_initialize();

      }


      void common_construct()
      {

         create_system();

         application_common(acmesystem());

      }


      console(int argc, char** argv)
      {

         common_construct();

         acmesystem()->system_construct(argc, argv);

         init();

      }


      console(int argc, wchar_t** argv)
      {

         common_construct();

         acmesystem()->system_construct(argc, argv);

         init();

      }


      void init()
      {

         m_estatus = (void) acmesystem()->inline_init();

      }


      int result()
      {

         m_estatus = papp->m_estatus;

         ::i32 iErrorStatus = m_estatus.error_status();

         acmesystem()->inline_term();

         acmesystem().release();

         return iErrorStatus;

      }


      ~console()
      {

         if (acmesystem())
         {

            result();

         }


      }


   };


} // namespace aura


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



