#pragma once


namespace datetime
{


   class CLASS_DECL_CA2_TIME token
   {
   public:


      enum_token        m_etoken;
      string            m_str;
      int32_t           m_iType;
      bool              m_bKeyword;



      token();
      ~token();


   };


} // namespace datetime



