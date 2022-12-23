//
// Created by camilo on 23/12/2022 01:54 <3ThomasBorregaardSorensen!!
//
#pragma once


inline property & property_set::payload(const ::scoped_string & scopedstrName) { return operator [](::atom(scopedstrName)); }
inline const property & property_set::payload(const ::scoped_string & scopedstrName) const { return operator [](::atom(scopedstrName)); }



