

//#include "apex/inline/console/linux.h"



// namespace aura
// {


//    class console
//    {
//    public:


//       ::e_status m_estatus;
//       __pointer(::aura::system) m_psystem;

//       void create_system()
//       {

//          aura_ref();

//          m_psystem = ::move_transfer(platform_create_system(nullptr));

//          m_psystem->console_initialize();

//       }

//       void common_construct()
//       {

//          create_system();

//          application_common(m_psystem);

//       }


//       console(int argc, char** argv)
//       {

//          common_construct();

//          m_psystem->system_construct(argc, argv);

//          init();

//       }


//       console(int argc, wchar_t** argv)
//       {

//          common_construct();

//          m_psystem->system_construct(argc, argv);

//          init();

//       }


//       void init()
//       {

//          m_estatus = (::e_status) m_psystem->inline_init();

//       }


//       int result()
//       {

//          m_estatus = papplication->m_estatus;

//          ::i32 iErrorStatus = m_estatus.error_status();

//          m_psystem->inline_term();

//          m_psystem.release();

//          return iErrorStatus;

//       }


//       ~console()
//       {

//          if (m_psystem)
//          {

//             result();

//          }


//       }



//    };


// } // namespace aura






// static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


// const char * br_init_get_symbol()
// {

//    return s_pszBinRelocInitGetSymbol;

// }





