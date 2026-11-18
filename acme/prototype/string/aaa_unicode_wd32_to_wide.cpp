#include "platform.h"


CLASS_DECL_ACME character_count wd32_to_wide_len(const ::wd32_character * pcwsz, character_count input_size)
{

   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {
      
      return wd32_to_wd32_len(pcwsz, input_size);

   }
   else
   {

      return wd32_to_wd16_len(pcwsz, input_size);

   }

}


CLASS_DECL_ACME character_count wd32_to_wide_len2(const ::wd32_character * pcwsz, character_count & input_size)
{
   
   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {

      return wd32_to_wd32_len2(pcwsz, input_size);

   }
   else
   {

      return wd32_to_wd16_len2(pcwsz, input_size);

   } 

}


CLASS_DECL_ACME character_count wd32_to_wide(::wide_character * pwsz, const ::wd32_character * pcwsz, character_count input_size)
{

   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {

      return wd32_to_wd32((::wd32_character *)pwsz, pcwsz, input_size);

   }
   else
   {

      return wd32_to_wd16((::wd16_character *)pwsz, pcwsz, input_size);

   }

}


CLASS_DECL_ACME::wide_character * wd32_to_wide_dup(const ::wd32_character * pcwsz, character_count input_size)
{
   
   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {

      return (::wide_character *)wd32_to_wd32_dup(pcwsz, input_size);

   }
   else
   {

      return (::wide_character *)wd32_to_wd16_dup(pcwsz, input_size);

   } 

}


CLASS_DECL_ACME::wd32_character * wide_to_wd32_alloc(const ::wide_character * pcwsz, character_count input_size, MALLOC_FUNCTION * malloc_function)
{

   auto p = (::wd32_character * ) malloc_function(sizeof(wd32_character) * (input_size + 1));

   if (!p)
   {
      
      throw ::exception(error_no_memory, "wd32_to_wd32_dup :: not enough memory");

   }

   wide_to_wd32(p, pcwsz, input_size);

   return p;

}




