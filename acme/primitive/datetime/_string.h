//Created by camilo on 2021-08-30 17:41 BRT <3ThomasBS__!!
#pragma once


namespace datetime
{


   //string Format(string & str, const ::string & strFormat) const;
   //string FormatGmt(string & str, const ::string & strFormat) const;
   CLASS_DECL_ACME string format(const ::string& strFormat, const ::datetime::time_span& timespan, const ::time_shift & timeshift = ::time_shift::none());
   CLASS_DECL_ACME string format(const ::string& strFormat, const ::datetime::time& time, const ::time_shift& timeshift = ::time_shift::none());
   //CLASS_DECL_ACME string utc_format(const ::string& strFormat, const::datetime::time& time);


} // namespace datetime



