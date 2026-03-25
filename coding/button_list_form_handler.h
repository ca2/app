// From integration_build_tool/options_impact_handler and
// from integration_integration/options_impact_handler to
// button_list_impact_handler on 2024-05-03 01:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "berg/user/user/options_impact_handler.h"
#include "acme/prototype/collection/bool_array.h"
#include "berg/user/user/form_handler.h"


namespace user
{


   class CLASS_DECL_CODING button_list_form_handler :
      virtual public ::berg::form_handler
   {
   public:


      ::pointer<::user::button>             m_pbutton[8];
      //::pointer<::user::button>             m_pbuttonWin32Release;
      //::pointer<::user::button>             m_pbuttonWin32StaticDebug;
      //::pointer<::user::button>             m_pbuttonWin32StaticRelease;
      //::pointer<::user::button>             m_pbuttonX64Debug;
      //::pointer<::user::button>             m_pbuttonX64Release;
      //::pointer<::user::button>             m_pbuttonX64StaticDebug;
      //::pointer<::user::button>             m_pbuttonX64StaticRelease;


      ::pointer<::user::still>              m_pstill[8];
      //::pointer<::user::still>              m_pstillWin32Release;
      //::pointer<::user::still>              m_pstillWin32StaticDebug;
      //::pointer<::user::still>              m_pstillWin32StaticRelease;
      //::pointer<::user::still>              m_pstillX64Debug;
      //::pointer<::user::still>              m_pstillX64Release;
      //::pointer<::user::still>              m_pstillX64StaticDebug;
      //::pointer<::user::still>              m_pstillX64StaticRelease;

      ::string_array *                       m_pstraId;
      ::string_array *                       m_pstraText;
      bool_array *                           m_pba;


      button_list_form_handler();
      ~button_list_form_handler() override;


      virtual void create_button_list_form_handler(::user::interaction* pinteraction);


      //virtual integration* get_integration();


   };


} // namespace user




