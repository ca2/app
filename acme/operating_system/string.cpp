//
// Created by camilo on Jul/4/2023.
//
#include "framework.h"


CLASS_DECL_ACME int ansi_icmp(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

CLASS_DECL_ACME int ansi_nicmp(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}


CLASS_DECL_ACME int ansi_icoll(const ::ansi_character * psz1, const ::ansi_character * psz2)
{
#ifdef WINDOWS
   return _stricmp(psz1, psz2);
#else
   return strcasecmp(psz1, psz2);
#endif
}

inline int ansi_nicoll(const ::ansi_character * psz1, const ::ansi_character * psz2, strsize s)
{
#ifdef WINDOWS
   return _strnicmp(psz1, psz2, s);
#else
   return strncasecmp(psz1, psz2, s);
#endif
}



