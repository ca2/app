#pragma once



enum enum_check : ::i32
{

   e_check_undefined, // not set, unitialized
   e_check_unchecked,
   e_check_checked,
   e_check_tristate

};


inline bool __bool(::enum_check echeck) { return echeck == ::e_check_checked; }







