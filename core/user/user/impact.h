#pragma once


namespace user
{


   namespace core
   {


      template < class VIEW >
      class show :
         virtual public ::user::show < VIEW >
      {
      public:





         inline ::core::application* get_app() const { return m_pacmeapplication ? m_pacmeapplication.cast < ::core::application >() : nullptr; }
         inline ::core::session* get_session() const { return m_psession ? m_psession.cast < ::core::session >() : nullptr; }
         inline ::core::system* get_system() const { return ::is_set(m_psystem) ? dynamic_cast <::core::system*> (m_psystem) : nullptr; }
         inline ::core::user* user() const { return get_session() ? get_session()->user() : nullptr; }



      };


   } // namespace core


} // namespace user



