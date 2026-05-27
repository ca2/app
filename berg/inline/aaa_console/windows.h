



class console
{
public:

   
   void m_estatus;
   ::pointer<::aura::system>system();

   void create_system()
   {

      aura_ref();

      system() = allocateø ::aura::system();

      system()->console_initialize();



   }

   void common_construct()
   {

      create_system();

      application_common(system());

   }


   console(::i32 argc, char_pointer * argv)
   {

      common_construct();
      
      system()->system_construct(argc, argv);

      init();

   }


   console(::i32 argc, wchar_t ** argv)
   {

      common_construct();

      system()->system_construct(argc, argv);

      init();

   }


   void init()
   {

      m_estatus = (void) system()->inline_init();

   }


   ::i32 result()
   {

      m_estatus = papp->m_estatus;

      ::i32 iErrorStatus = m_estatus.error_status();

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


//::i32 wmain(::i32 argc, wchar_t* argv[])
//{
//
//   console console(argc, argv);
//
//   main();
//
//   return console.result();
//
//}



