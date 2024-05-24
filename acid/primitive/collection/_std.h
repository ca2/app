// From PPP by camilo on 2023-02-03 03:26 <3ThomasBorregaardSorensen!!
#pragma once


template<size_t N>
inline ::string as_string(const std::bitset<N>& v)
{

   return v.to_string().c_str();

}


template <size_t N>
inline void from_string(std::bitset<N>& dst, const ::scoped_string& scopedstr)
{

   dst = std::bitset<N>(::std::string(scopedstr.begin(), scopedstr.end()));

}



