



class console
{
public:

   
   ::estatus m_estatus;
   __pointer(::aura::system) m_psystem;

   void create_system()
   {

      aura_ref();

      m_psystem = __new(::aura::system());

      m_psystem->console_initialize();



   }

   void common_construct()
   {

      create_system();

      application_common(m_psystem);

   }


   console(int argc, char ** argv)
   {

      common_construct();
      
      m_psystem->system_construct(argc, argv);

      init();

   }


   console(int argc, wchar_t ** argv)
   {

      common_construct();

      m_psystem->system_construct(argc, argv);

      init();

   }


   void init()
   {

      m_estatus = (::estatus) m_psystem->inline_init();

   }


   int result()
   {

      m_estatus = Application.m_estatus;

      ::i32 iErrorStatus = m_estatus.error_status();

      m_psystem->inline_term();

      m_psystem.release();

      return iErrorStatus;

   }


   ~console()
   {

      if (m_psystem)
      {

         result();

      }


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



