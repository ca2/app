// Adapted by camilo on 2022-11-04 14:03 <3ThomaBorregaardSorensen!!
#include "framework.h"

/*
  Portable ASCII and Unicode string manipulation functions for C++.
*/

  //// encoding types
  //enum encoding_type {
  //  ENCODING_UNKNOWN,
  //  ENCODING_ASCII,
  //  ENCODING_UTF8,
  //  ENCODING_UTF16BE,
  //  ENCODING_UTF16LE,
  //  ENCODING_UTF32BE,
  //  ENCODING_UTF32LE,
  //};

  //// detect the encoding for a string
  //encoding_type detect_encoding(const std::string &input);

  //// determine whether a string is valid in a particular encoding
  //bool is_valid(const std::string &input, encoding_type encoding);

  //// convert a string from one encoding to another
  //std::string convert_encoding(const std::string &input, encoding_type input_encoding, encoding_type output_encoding, bool include_bom);

  //// get the number of code points in a string
  //size_t get_length(const std::string &input, encoding_type encoding);

  //// return the number of bytes of the code point at pos, or 0 if the byte index does not refer to a valid code point
  //size_t get_char_size(const std::string &input, size_t pos, encoding_type encoding);

  //// get the code point at a particular byte index
  //::i32 get_char(const std::string &input, size_t pos, encoding_type encoding);

  //// set the code point at a particular byte index
  //void set_char(std::string &input, size_t pos, ::i32 code_point, encoding_type encoding);

  //// add a code point to the end of a string
  //void add_char(std::string &input, ::i32 code_point, encoding_type encoding);

  //// determine whether a code point is a letter
  //bool unicode_data_is_alpha(::i32 code_point);

  //// determine whether a code point is uppercase
  //bool unicode_data_is_upper(::i32 code_point);

  //// determine whether a code point is lowercase
  //bool unicode_data_is_lower(::i32 code_point);

  //// determine whether a code point is titlecase
  //bool unicode_data_is_title(::i32 code_point);

  //// determine whether a code point is a number
  //bool unicode_data_is_numeric(::i32 code_point);

  //// determine whether a code point is whitespace
  //bool unicode_data_is_whitespace(::i32 code_point);

  //// determine whether a code point is a line separator
  //bool unicode_data_is_newline(::i32 code_point);

  // convert a code point to uppercase (return the input if no uppercase form exists)
  CLASS_DECL_ACME ::i32 uni_to_upper_case(::i32 code_point);

  // convert a code point to lowercase (return the input if no lowercase form exists)
  CLASS_DECL_ACME ::i32 uni_to_lower_case(::i32 code_point);

  // convert a code point to titlecase (return the input if no titlecase form exists)
  //::i32 uni_to_title(::i32 code_point);
//
//}
//
//#endif