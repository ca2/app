//
// Created by camilo on 23/12/2022 01:54 <3ThomasBorregaardSorensen!!
//
#pragma once


inline property & property_set::payload(const ::scoped_string & scopedstrName) { return operator [](::atom(scopedstrName)); }
inline const property & property_set::payload(const ::scoped_string & scopedstrName) const { return operator [](::atom(scopedstrName)); }

inline property & property_set::payload(const ::string & strName) { return operator [](::atom(strName)); }
inline const property & property_set::payload(const ::string & strName) const { return operator [](::atom(strName)); }

inline property & property_set::payload(::index iIndex) { return operator [](::atom(iIndex)); }
inline const property & property_set::payload(::index iIndex) const { return operator [](::atom(iIndex)); }

inline property & property_set::payload(const ::payload & payload) { return operator [](::atom(payload)); }
inline const property & property_set::payload(const ::payload & payload) const { return operator [](::atom(payload)); }



