#include "framework.h"


namespace aqua
{


   application::application()
   {

      m_paquaapplication = this;
      ///set_layer(LAYERED_AQUA, this);

   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   ::e_status application::initialize(::object * pobject)
   {

      auto estatus = ::application::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status application::exit_application()
   {

      if (get_system()->m_pmultimedia)
      {

         auto estatus = get_system()->m_pmultimedia->exit_application();

         if (!estatus)
         {

            return estatus;

         }

      }

      auto estatus = ::application::exit_application();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void application::game_on_create(::aqua::game * pgame)
   {

   }


   bool application::load_cached_string(string& str, const ::id& id, bool bLoadStringTable)
   {

      auto pdocument = __create_new<::xml::document>();

      if (!pdocument->load(id))
      {

         return load_cached_string_by_id(str, id, bLoadStringTable);

      }

      auto pnodeRoot = pdocument->root();

      if (pnodeRoot->get_name() == "string")
      {

         string strId = pnodeRoot->attribute("id");

         if (!load_cached_string_by_id(str, strId, bLoadStringTable))
         {

            str = pnodeRoot->get_value();

         }

         return true;

      }

      return false;

   }


   //LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   get_system()-

   //}



} // namespace aqua



