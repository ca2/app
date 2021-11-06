#pragma once


extern "C"
{


void linux_g_direct_init();
void linux_g_direct_term();
//void * linux_g_direct_app_indicator_new(const ::string & pszId, const ::string & pszIcon, const ::string & pszFolder, struct linux_g_direct_bridge * pi);
//void linux_g_direct_app_indicator_term(void * pind);


} // extern "C"


struct linux_g_direct_bridge
{
public:

   
   linux_g_direct_bridge() {}
   virtual ~linux_g_direct_bridge() {}


};

