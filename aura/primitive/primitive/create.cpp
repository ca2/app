#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


create::create(::object * pobject) :
   ::object(pobject)
{

   create_common_construct(::type_empty_argument, nullptr);

   defer_initialize();

}

create::create()
{

   create_common_construct(::type_empty_argument, nullptr);

   defer_initialize();

}

create::create(::object * pobject, arguments arguments) :
   ::object(pobject)
{

   create_common_construct(::type_empty_argument, nullptr);

   for(auto & arg : arguments)
   {

      if(arg.get_type() == type_enum_command)
      {

         m_ecommand = arg.m_ecommand;

      }
      else if(arg.get_type() == type_string)
      {

         m_pcommandline = __new(command_line(pobject, arg.get_string()));

      }
      else if(auto pcommandline = arg.cast<command_line>())
      {

         m_pcommandline = pcommandline;

      }
      else if(auto pcreate = arg.cast < create >())
      {

         operator = (*pcreate);

      }

   }

   defer_initialize();

}





create::create(::object * pobject, string strAppId, var varFile, const var & varOptions, ::user::primitive * puiParent, ewindowflag ewindowflag, ::id id) :
   ::object(pobject),
   m_ewindowflag(ewindowflag),
   m_id(id)
{

   create_common_construct(varOptions, puiParent);

   if(strAppId.has_char())
   {

      m_strAppId = strAppId;

   }

   defer_initialize();

   m_pcommandline->m_varFile          = varFile;

}


create::~create()
{

}


void create::create_common_construct(const ::var & varOptions, ::user::primitive * puiParent)
{

   m_bNew                              = true;
   m_ecommand                          = command_default;
   m_varOptions                        = varOptions;
   m_bTransparentBackground            = true;
   m_bClientOnly                       = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_puiAlloc                          = nullptr;
   m_puserinteractionParent            = puiParent;
   m_bMakeVisible                      = m_varOptions.is_true("visible", true);

}


void create::defer_initialize()
{

   if(!m_pcommandline)
   {

      m_pcommandline = __new(command_line(get_context_object()));

   }

   if(m_pcommandline)
   {

      if(m_pcommandline->m_varQuery.has_property("client_only"))
      {

         m_bClientOnly = true;

      }

   }

}



string create::get_description()
{

   return m_strDescription;

}


void create::set_description(string strDescription)
{

   m_strDescription = strDescription;

}


index create::get_edge()
{

   if(!m_pcommandline)
   {

      return 0;

   }

   return m_pcommandline->m_iEdge;

}


