#pragma once


// GDK, GTK :: C++


namespace user
{


   bool gsettings_get(string & str, const char * pszSchema, const char * pszKey);


} // namespace user


void gdk_branch(::matter * preference, e_priority epriority = priority_normal);


template < typename PRED >
auto gdk_fork(PRED pred, e_priority epriority = priority_normal)
{

   return async_predicate(&gdk_branch, pred, epriority);

}


template < typename PRED >
auto gdk_sync(const duration & durationTimeout, PRED pred, e_priority epriority = priority_normal)
{

   return sync_predicate(&gdk_branch, pred, durationTimeout, epriority);

}





