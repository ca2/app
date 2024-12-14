//
// Created by camilo 2024-Dec <3ThomasBorregaardSorensen!!
//
#pragma once


template <typename T1, typename T2>
inline bool is_equivalent(T1 t1, T2 t2)
{

   return default_equivalence_sink(t1) == default_equivalence_sink(t2);

}



