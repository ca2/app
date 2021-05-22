#include "framework.h"


create::create()
{

   m_bMakeVisible = true;

}




::e_status create::initialize_create(arguments arguments) 
{

   create_common_construct(::e_type_empty_argument, nullptr);

   for(auto & arg : arguments)
   {

      if(arg.get_type() == e_type_enum_command)
      {

         m_ecommand = arg.m_ecommand;

      }
      else if(arg.get_type() == e_type_string)
      {

         auto estatus = __construct(m_pcommandline);

         if (!estatus)
         {

            return estatus;

         }
         
         estatus = m_pcommandline->initialize_command_line(arg.get_string());

         if (!estatus)
         {

            return estatus;

         }

      }
      else if(auto pcommandline = arg.cast<command_line>())
      {

         m_pcommandline = pcommandline;

      }
      else if(auto pcreate = arg.cast < create >())
      {

         __throw(todo, "Fix this. This shouldn't happen. (create is \"fat\" object, so it is not meant to be copied through copy constructors, assign operators,...)");
         //operator = (*pcreate);

      }

   }

   return finish_initialization();

}


::e_status create::initialize_create(string strAppId, ::payload varFile, const ::payload & varOptions, ::user::primitive * puiParent, ewindowflag ewindowflag, ::id id)
{

   m_ewindowflag = ewindowflag;
      
   m_id = id;

   create_common_construct(varOptions, puiParent);

   if(strAppId.has_char())
   {

      m_strAppId = strAppId;

   }

   auto estatus = finish_initialization();

   if (!estatus)
   {
      
      return estatus;

   }
   
   m_pcommandline->m_varFile = varFile;

   m_puserprimitiveParent = puiParent;

   return estatus;

}


create::~create()
{

}


void create::create_common_construct(const ::payload & varOptions, ::user::primitive * puiParent)
{

   m_bNew                              = true;
   m_ecommand                          = command_default;
   m_varOptions                        = varOptions;
   m_bTransparentBackground            = true;
   m_bClientOnly                       = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_bMakeVisible                      = m_varOptions.is_true("visible", true);

}


::application* create::create_get_application(::application* pappFallback)
{

   auto pobject = this;

   if (pobject)
   {

      auto papp = pobject->get_application();

      if (papp)
      {

         return papp;

      }

   }

   return pappFallback;

}


::e_status create::finish_initialization()
{

   ::e_status estatus = ::success;

   if(!m_pcommandline)
   {

      estatus = __construct(m_pcommandline);

      if (!estatus)
      {

         return estatus;

      }

   }

   if(m_pcommandline)
   {

      if(m_pcommandline->m_varQuery.has_property("client_only"))
      {

         m_bClientOnly = true;

      }

   }

   return estatus;

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


bool create::has_file() const
{

   if (!m_varFile.is_empty())
   {

      return true;

   }

   if (m_pcommandline && !m_pcommandline->m_varFile.is_empty())
   {

      return true;

   }

   return false;

}


::payload create::get_file() const
{

   if (!m_varFile.is_empty())
   {

      return m_varFile;

   }

   if (m_pcommandline && !m_pcommandline->m_varFile.is_empty())
   {

      return m_pcommandline->m_varFile;

   }

   return ::payload();

}


void create::set_file_path(const ::payload& payload)
{

   m_varFile = payload;

   if (m_pcommandline)
   {

      m_pcommandline->m_varFile = payload;

   }

}



