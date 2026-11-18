#include "platform.h"


CLASS_DECL_ACME character_count wide_to_wd32_len(const ::wide_character * pcwsz, character_count input_size)
{

   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {
      
      return wd32_to_wd32_len((const ::wd32_character *)pcwsz, input_size);

   }
   else
   {

      return wd16_to_wd32_len((const ::wd16_character *)pcwsz, input_size);

   }

}



CLASS_DECL_ACME character_count wide_to_wd32_len2(const ::wide_character * pcwsz, character_count input_size)
{

   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {

      return wd32_to_wd32_len2((const ::wd32_character *)pcwsz, input_size);

   }
   else
   {

      return wd16_to_wd32_len2((const ::wd16_character *)pcwsz, input_size);

   }

}



CLASS_DECL_ACME character_count wide_to_wd32(::wd32_character * pwsz, const ::wide_character * pcwsz, character_count input_size)
{
   
   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {

      return wd32_to_wd32(pwsz, (const ::wd32_character *)pcwsz, input_size);

   }
   else
   {

      return wd16_to_wd32(pwsz, (const ::wd16_character *)pcwsz, input_size);

   }

}  



CLASS_DECL_ACME::wide_character * wide_to_wd32_alloc(const ::wide_character * pcwsz, character_count input_size, MALLOC_FUNCTION * malloc_function)
{

   if constexpr (sizeof(::wide_character) == sizeof(::wd32_character))
   {

      return wd32_to_wd32_alloc((const ::wd32_character *)pcwsz, input_size);

   }
   else
   {

      return wd16_to_wd32_alloc((const ::wd16_character *)pcwsz, input_size);

   }
}



