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





         inline ::core::application* get_app() const { return m_papplication ? m_papplication.cast < ::core::application >() : nullptr; }
         inline ::core::session* get_session() const { return m_psession ? m_psession.cast < ::core::session >() : nullptr; }
         inline ::core::system* system() const { return ::is_set(system()) ? dynamic_cast <::core::system*> (system()) : nullptr; }
         inline ::core::user* user() const { return get_session() ? get_session()->user() : nullptr; }



      };


   } // namespace core


} // namespace user



