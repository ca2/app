#pragma once


namespace calculator
{


   class CLASS_DECL_CA2_MATH token
   {
   public:


      enum enum_type
      {
         type_none,
         type_identifier,
         type_function,
         type_number,
         type_imaginary,
         type_keyword,
         type_end,
         type_error,
         type_addition,
         type_subtraction,
         type_multiplication,
         type_division,
         type_equal,
         type_semi_colon,
         type_open_paren,
         type_close_paren,
         type_char_error,
         type_virgula, // ,
      };


      token();
      ~token();
      /* Tokens */
      enum_type         m_etype;
      string         m_str;
      i32        m_iType;
      bool           m_bKeyword;


   };


} // namespace calculator





