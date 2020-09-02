#pragma once


namespace datetime
{


   namespace clock
   {


      class CLASS_DECL_CA2_TIME visual :
         virtual public clock
      {
      public:


         point    m_point;
         size     m_size;


         visual();
         virtual ~visual();


      };


   } // namespace clock


} // namespace datetime








