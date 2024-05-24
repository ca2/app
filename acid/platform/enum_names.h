// From enum.h by camilo on 2022-11-07 09:51 <3ThomasBorregaardSorensen!!
#pragma once


template <class EENUM>
class base_enum_names :
   public map < EENUM, EENUM, string, string >
{
public:

   typedef typename map < EENUM, EENUM, string, string >::pair AXIS_ENUM_PAIR;

   base_enum_names(AXIS_ENUM_PAIR pairs[]);
};


template <class EENUM>
base_enum_names < EENUM > ::base_enum_names(AXIS_ENUM_PAIR pairs[]) :
   map < EENUM, EENUM, string, string >(pairs)
{
}


