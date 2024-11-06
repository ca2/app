#pragma once


CLASS_DECL_AURA void aura_ref();


namespace aura
{


   class console
   {
   public:


      void m_estatus;
      ::pointer<::aura::system>system();


      void create_system()
      {

         aura_ref();

         system() = ::pointer_transfer(platform_create_system(::GetModuleHandle(NULL)));

         system()->console_initialize();

      }


      void common_construct()
      {

         create_system();

         application_common(system());

      }


      console(int argc, char** argv)
      {

         common_construct();

         system()->system_construct(argc, argv);

         init();

      }


      console(int argc, wchar_t** argv)
      {

         common_construct();

         system()->system_construct(argc, argv);

         init();

      }


      void init()
      {

         m_estatus = (void) system()->inline_init();

      }


      int result()
      {

         m_estatus = papp->m_estatus;

         int iErrorStatus = m_estatus.error_status();

         system()->inline_term();

         system().release();

         return iErrorStatus;

      }


      ~console()
      {

         if (system())
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



