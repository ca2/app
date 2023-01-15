#include "framework.h"
#include "openssl.h"
#include "application.h"
#include "render.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "base/user/user/impact_system.h"
#include "base/user/user/split_impact.h"


namespace app_integration
{


   openssl::openssl()
   {

      m_strRelease = "3.0.7";

      m_pathDownloadURL = "https ://www.openssl.org/source/openssl-" + m_strRelease + ".tar.gz";

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   openssl::~openssl()
   {

   }


//   void openssl::assert_ok() const
//   {
//
//      user::box::assert_ok();
//
//   }
//
//
//   void openssl::dump(dump_context & dumpcontext) const
//   {
//
//      user::box::dump(dumpcontext);
//
//   }


#ifdef _DEBUG


   int64_t openssl::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t openssl::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void openssl::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE,psender,this,&openssl::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, psender, this, &openssl::on_message_destroy);

   }


   void openssl::on_message_create(::message::message * pmessage)
   {

      payload(FONTSEL_IMPACT) = true;

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      {

         auto psignal = get_app()->get_signal("simple_checkbox");

         psignal->add_handler(this);

      }

      {

         auto psignal = get_app()->get_signal("no_client_frame");

         psignal->add_handler(this);

      }

      //auto estatus = 
      
      //__construct_new(m_prender);

      //if(!estatus)
      //{

      //   pcreate->set_fail();

      //   return;

      //}

      //m_prender->m_pimpact = this;

      auto pdocument = get_document();

      auto pimpactsystem = pdocument->m_pimpactsystem;

      string strId = pimpactsystem->m_atom;

      string strText;

      if(get_typed_parent<::user::split_impact>() != nullptr)
      {

         if(get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            auto pinteraction = get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact");

            pinteraction->_001SetText(strText,::e_source_initialize);

         }

      }

      fork([]()
         {


            fork([]() { build("Win32", "Debug"); });
      fork([]() { build("Win32", "Release"); });
      fork([]() { build("Win32", "StaticDebug"); });
      fork([]() { build("Win32", "StaticRelease"); });

      fork([]() { build("x64", "Debug"); });
      fork([]() { build("x64", "Release"); });
      fork([]() { build("x64", "StaticDebug"); });
      fork([]() { build("x64", "StaticRelease"); });

      });

   }


   void openssl::on_message_destroy(::message::message * pmessage)
   {

   }


   void openssl::build(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
   {

      download(scopedstrPlatform, scopedstrConfiguration)

      compile(scopedstrPlatform, scopedstrConfiguration);

      install(scopedstrPlatform, scopedstrConfiguration);

   }


   void openssl::compile()
   {

   }


   void openssl::install()
   {


   }



   void openssl::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == "simple_checkbox"
         || ptopic->m_atom == "no_client_frame")
      {

         set_need_redraw();
         
         post_redraw();

      }

      ::user::impact::handle(ptopic, pcontext);
   }


   ::user::document * openssl::get_document()
   {

      return ::user::impact::get_document();

   }


   void openssl::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (get_app()->application_properties().m_echeckNoClientFrame != ::e_check_checked)
      {

         ::rectangle_i32 rectangle = get_client_rect();

         for (index i = 0; i < 11; i++)
         {

            pgraphics->draw_inset_rectangle(rectangle, argb(180, 80, 80, 80));

            rectangle.deflate(1, 1);

         }

      }

      //m_prender->_001OnDraw(pgraphics);

   }


   void openssl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      //m_prender->m_rectangle = rectangleClient;

   }



   VERSION = "3.0.7"


      SRC_FOLDER = "/c/main/operating-system/operating-system-windows"


      STG_FOLDER = "/c/operating-system/storage-windows"


      if[!- d $BASE_DIR]; then

         echo "$BASE_DIR does not exist!!"

         exit - 1

         fi


         cd $BASE_DIR


         function compile()
      {


         PLATFORM = $1
            CONFIGURATION = $2
            NAME = $3
            DEBUG = $4
            CONFIGURE = $5
            SHARED = $6


            RELATIVE = openssl / $VERSION / $PLATFORM / $CONFIGURATION


            cd $BASE_DIR
            mkdir - p $RELATIVE
            cd $RELATIVE


            echo "Downloading openssl.tar.gz to $RELATIVE ..."
            wget - O openssl.tar.gz  https ://www.openssl.org/source/openssl-$VERSION.tar.gz
         echo "Uncompressing openssl.tar.gz to $RELATIVE ..."
            tar - xzf openssl.tar.gz --strip - components = 1 - C .
            perl Configure $CONFIGURE $DEBUG --prefix = $BASE_DIR / $RELATIVE / build --openssldir = $BASE_DIR / $RELATIVE / program $SHARED
            nmake

      }

   function install()
   {

      BASE_DIR = $1
         VERSION = $2
         PLATFORM = $3
         CONFIGURATION = $4
         REL = $5
         SRC_FOLDER = $6
         STG_FOLDER = $7


         RELATIVE = openssl / $VERSION / $PLATFORM / $CONFIGURATION


         cd $BASE_DIR
         cd $RELATIVE

         nmake install

         SOURCE_DIR = "$SRC_FOLDER/$REL"
         STORAGE_DIR = "$STG_FOLDER/$REL"

         mkdir - p $SOURCE_DIR / include /
         mkdir - p $STORAGE_DIR / binary /
         mkdir - p $STORAGE_DIR / library /

         cp - Rf $BASE_DIR / $NAME / build / include/* $SOURCE_DIR/include/
         cp -Rf $BASE_DIR/$NAME/build/bin/* $STORAGE_DIR/binary/
         cp -Rf $BASE_DIR/$NAME/build/lib/* $STORAGE_DIR/library/

      }






} // namespace simple_drawing



