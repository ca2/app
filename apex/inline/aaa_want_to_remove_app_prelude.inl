#include "apex/.h"


#undef new

int main(int argc, char * argv[])
{

   class apex_apex apex;

   app_prelude with_class;

   ap(apex_main_data) pmaindata = new apex_main_data(argc, argv);

   br_init_set_symbol(g_psz_br_init_symbol_app);

   return (int) apex_apex(pmaindata);

}





