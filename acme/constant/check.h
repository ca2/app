#pragma once



enum enum_check : ::i32
{

   check_undefined, // not set, unitialized
   check_unchecked,
   check_checked,
   check_tristate

};


inline bool __bool(::enum_check echeck) { return echeck == ::check_checked; }


