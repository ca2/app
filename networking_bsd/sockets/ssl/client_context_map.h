#pragma once



////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/string_map.h"


namespace sockets_bsd
{


   class CLASS_DECL_NETWORKING_BSD ssl_client_context_map :
      virtual public object
   {
   public:


      string_map_base < map_base < const SSL_METHOD *, ::pointer<ssl_client_context >>> m_map;


      ssl_client_context_map();
      virtual ~ssl_client_context_map();


      ::pointer<ssl_client_context> get_context(const ::scoped_string & scopedstrContext, const SSL_METHOD * pmethod);


   };


} // namespace sockets_bsd



