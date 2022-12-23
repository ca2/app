//
// Created by camilo on 23/12/22.
//
#pragma once


bool payload::begins(const ::string & strPrefix) const
{

   return string().begins(strPrefix);

}


bool payload::ends(const ::string & strSuffix) const
{

   return string().ends(strSuffix);

}


bool payload::case_insensitive_begins(const ::string & strPrefix) const
{

   return string().case_insensitive_begins(strPrefix);

}

bool payload::case_insensitive_ends(const ::string & strSuffix) const
{

   return string().case_insensitive_ends(strSuffix);

}
