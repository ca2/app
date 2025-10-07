#pragma once


extern "C"
{


void linux_g_direct_init();
void linux_g_direct_term();
//void * linux_g_direct_app_indicator_new(const ::scoped_string & scopedstrId, const ::scoped_string & scopedstrIcon, const ::scoped_string & scopedstrFolder, struct linux_g_direct_bridge * pi);
//void linux_g_direct_app_indicator_term(void * pind);


} // extern "C"


struct linux_g_direct_bridge
{
public:

   
   linux_g_direct_bridge() {}
   virtual ~linux_g_direct_bridge() {}


};

