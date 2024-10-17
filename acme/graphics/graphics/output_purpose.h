#pragma once


////#include "acme/prototype/prototype/object.h"


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


   class CLASS_DECL_ACME output_purpose :
      virtual public particle
   {
   private:
      ::particle * m_pparticleGraphicalOutputPurposeOriginator2 = nullptr;
#if REFERENCING_DEBUGGING
      ::reference_referer * m_preferer = nullptr;
#endif
   public:


      e_output_purpose     m_egraphicsoutputpurpose;



      output_purpose(enum_output_purpose
      eoutputpurpose = e_output_purpose_none
      );
      output_purpose(::particle
      * pparticleGraphicalOutputPurposeOriginator,
      enum_output_purpose eoutputpurpose
      );


      ~output_purpose() override;


      virtual void set_graphical_output_purpose_originator(::particle * pparticle);
      virtual ::particle * get_graphical_output_purpose_originator();
      virtual void release_graphical_output_purpose_originator();

      void destroy() override;


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


