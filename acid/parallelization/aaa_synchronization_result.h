#pragma once


inline ::i32 signaled_index(::enum_status estatus)
{

   return (estatus >= signaled_base && estatus < signaled_end) ? ((::i32)estatus - (::i32)signaled_base) : -1;

}


inline bool signaled(::enum_status estatus)
{

   return signaled_index(estatus) >= 0;

}


inline ::i32 abandoned_index(::enum_status estatus)
{

   return (estatus >= abandoned_base && estatus < abandoned_end) ? ((::i32)estatus - (::i32)abandoned_base) : -1;

}


inline bool abandoned(::enum_status estatus)
{

   return abandoned_index(estatus) >= 0;

}



inline bool wait_timeout(::enum_status estatus)
{

   return estatus == error_wait_timeout;

}



