//Created by camilo on 2021-08-30 17:41 BRT <3ThomasBS__!!
#pragma once


namespace earth
{


   CLASS_DECL_ACME string format(const ::string& strFormat, const time_span& timespan, const time_shift & timeshift = time_shift::none());
   CLASS_DECL_ACME string format(const ::string& strFormat, const time& time, const time_shift& timeshift = time_shift::none());


} // namespace earth



