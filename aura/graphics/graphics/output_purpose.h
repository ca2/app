#pragma once


////#include "acme/primitive/primitive/object.h"


// class CLASS_DECL_AURA fps_interest :
//    virtual public object
// {
// public:


//    ::pointer<::user::interaction>   m_pinteraction;


//    fps_interest(::user::interaction* pinteraction);

//    ~fps_interest() override;

// };


namespace graphics
{


   class CLASS_DECL_AURA output_purpose :
      virtual public particle
   {
   public:


      enum_output_purpose     m_epurpose;

      ::pointer<::particle>   m_pparticle;


      output_purpose(enum_output_purpose
      epurpose = e_output_purpose_none
      );
      output_purpose(::particle
      * pparticle,
      enum_output_purpose epurpose
      );


//      virtual enum_output_purpose _graphical_output_purpose();
//
//      inline enum_output_purpose graphical_output_purpose()
//      {
//
//         return m_epurpose2 & e_output_purpose_auto ? _graphical_output_purpose() : m_epurpose2;
//
//      }
//
//      virtual ::particle * graphical_output_purpose_particle() = 0;

   };


//   class CLASS_DECL_AURA output_purpose_particle :
//      virtual public output_purpose
//   {
//   public:
//
//
//      ::pointer<::particle>   m_pparticle;
//
//
//   };

} // namespace graphics


