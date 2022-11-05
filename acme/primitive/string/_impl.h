#pragma once


#include "_impl_prio.h"



#include "_ch_impl.h"


//#include "_str_compare_impl.h"


//#include "_str_trait_impl.h"



template < typename TYPE_CHAR >
inline ::strsize string_meta_data < TYPE_CHAR>:: memsize_in_chars() const
{

   return (::strsize) byte_length_to_char_length(&this->get_data()[0], (::strsize)this->m_memsize);

}


template < typename TYPE_CHAR >
inline ::memsize string_meta_data < TYPE_CHAR>::length_in_bytes() const { return ::str().char_length_to_byte_length(&this->get_data()[0], this->m_datasize); }



template < typename CHAR_TYPE >
::wd32char string_iterator < CHAR_TYPE > ::operator *(){return unicode_index(m_psz); }


template < typename CHAR_TYPE >
string_iterator < CHAR_TYPE > & string_iterator < CHAR_TYPE > ::operator ++()
{

   unicode_increment(m_psz);

   return *this;

}

template < typename CHAR_TYPE >
string_iterator < CHAR_TYPE > string_iterator < CHAR_TYPE > ::operator ++(int)
{

   auto psz = m_psz;

   unicode_increment(m_psz);

   return psz;

}

#include "_string_base_impl.h"

//#include "_str_ch_ansi_impl.h"
//#include "_str_ch_wd16_impl.h"
//#include "_str_ch_wd32_impl.h"




