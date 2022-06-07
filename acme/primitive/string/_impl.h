#pragma once


#include "_impl_prio.h"


#include "_str_trait_ansi_impl.h"
#include "_str_trait_wd16_impl.h"
#include "_str_trait_wd32_impl.h"


#include "_compare_impl.h"


#include "_str_trait_impl.h"






template < typename TYPE_CHAR >
inline ::strsize string_meta_data < TYPE_CHAR>:: memsize_in_chars() const
{

   return (::strsize) ::str().byte_length_to_char_length(&this->get_data()[0], (::strsize)this->m_memsize);

}


#include "_str_ch_ansi_impl.h"
#include "_str_ch_wd16_impl.h"
#include "_str_ch_wd32_impl.h"



