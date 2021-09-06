//Created by camilo on 2021-08-30 17:41 BRT <3ThomasBS__!!
#pragma once


//string Format(string & str, const ::string & strFormat) const;
//string FormatGmt(string & str, const ::string & strFormat) const;
CLASS_DECL_ACME string Format(const ::string & strFormat, const ::datetime::time_span & timespan);
CLASS_DECL_ACME string Format(const ::string & strFormat, const ::datetime::time & time);
CLASS_DECL_ACME string FormatGmt(const ::string & strFormat, const::datetime::time & time);



