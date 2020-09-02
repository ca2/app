#pragma once


namespace datetime
{


   class CLASS_DECL_CA2_TIME clock:
      virtual public clock_interface
   {
   public:


      point    m_point;
      size     m_size;


      clock(::aura::application * papp);


   };


} // namespace datetime








