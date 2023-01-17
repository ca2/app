// From impact.cpp on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "ffmpeg.h"
#include "application.h"
#include "render.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "base/user/user/impact_system.h"
#include "base/user/user/split_impact.h"
#include "acme/platform/system.h"


namespace app_integration
{


   ffmpeg::ffmpeg()
   {

      m_flagNonClient.erase(e_non_client_background);

      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   ffmpeg::~ffmpeg()
   {

   }


//   void ffmpeg::assert_ok() const
//   {
//
//      user::box::assert_ok();
//
//   }
//
//
//   void ffmpeg::dump(dump_context & dumpcontext) const
//   {
//
//      user::box::dump(dumpcontext);
//
//   }


#ifdef _DEBUG


   int64_t ffmpeg::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t ffmpeg::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::impact::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   void ffmpeg::install_message_routing(::channel * psender)
   {

      ::user::impact::install_message_routing(psender);

      MESSAGE_LINK(MESSAGE_CREATE,psender,this,&impact::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, psender, this, &ffmpeg::on_message_destroy);

   }


   void ffmpeg::on_message_create(::message::message * pmessage)
   {

      payload(FONTSEL_IMPACT) = true;

      ::pointer<::message::create> pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      ::property_set set;

      acmesystem()->url()->defer_raw_http(set);

      string strRelease = acmeapplication()->http().get("https://raw.githubusercontent.com/FFmpeg/FFmpeg/master/RELEASE", set);

      strRelease.trim();

      strRelease.ends_eat(".git");

      m_strRelease = strRelease;
      //{

      //   auto psignal = get_app()->get_signal("simple_checkbox");

      //   psignal->add_handler(this);

      //}

      //{

      //   auto psignal = get_app()->get_signal("no_client_frame");

      //   psignal->add_handler(this);

      //}

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

   }


   void ffmpeg::on_message_destroy(::message::message * pmessage)
   {

   }


   void ffmpeg::download()
   {

#!/bin/bash


      RELEASE = `http_get - case_insensitive_ends_eat.git - trim https ://raw.githubusercontent.com/FFmpeg/FFmpeg/master/RELEASE`


      SRC_FOLDER = "/c/main/operating-system/operating-system-windows"


         STG_FOLDER = "/c/operating-system/storage-windows"


         if[!- d $BASE_DIR]; then

            echo "$BASE_DIR does not exist!!"

            exit - 1

            fi


            cd $BASE_DIR


            function prepare()
         {


            PATH = "openssl/$RELEASE/$PLATFORM/$CONFIGURATION"


               if["$PLATFORM" == "Win32"]; then

                  ARCH = "i386"

                  elif["$PLATFORM" == "x64"]; then

                  ARCH = "x86_64"

               else

                  echo "Unsupported Platform \"$PLATFORM\"?!?"

                  exit - 1

                  fi

                  if["$CONFIGURATION" == *"Debug" *]; then

                     DEBUG = "--enable-debug"

                  else

                     DEBUG = "--disable-debug"

                     fi

                     if["$CONFIGURATION" == *"Static" *]; then

                        SHARED = ""

                        STATIC = ""

                     else

                        SHARED = "--enable-shared"

                        STATIC = "--disable-static"

                        fi


         }


      function compile()
      {

         PLATFORM = $1
            CONFIGURATION = $2


            prepare


            cd "$BASE_DIR"
            mkdir - p "$PATH"
            cd "$PATH"


            echo "BASE_DIR is $BASE_DIR"
            echo "PATH is $PATH"
            echo "RELEASE is $RELEASE"
            echo "ARCH is $ARCH"
            echo "DEBUG is $DEBUG"
            echo "SHARED is $SHARED"
            echo "STATIC is $STATIC"


            exit - 1
            #DEBUG --enable - debug

            #ARCH i386   x86_64

            #for shared: --enable - shared --disable - static
            #for static: ""              ""

#(compile x64 Debug --enable-debug --enable-shared --disable-static -MDd???) &
#(compile x64 Release --disable-debug --enable-shared --disable-static -MD???) &
#(compile x64 StaticDebug --enable-debug "" "" -MTd???) &
#(compile x64 StaticRelease --disable-debug "" "" -MT???) &


            git clone https ://git.ffmpeg.org/ffmpeg.git .
#./configure --enable-asm --enable-yasm --arch=$ARCH --disable-ffserver --disable-avdevice --disable-swscale --disable-doc --disable-ffplay --disable-ffprobe --disable-ffmpeg $SHARED $STATIC --disable-bzlib --disable-libopenjpeg --disable-iconv --disable-zlib --prefix=$BASE_DIR/output/$NAME --toolchain=msvc $DEBUG
         . / configure --enable - asm --enable - yasm --arch = $ARCH --disable - doc $SHARED $STATIC --disable - bzlib --disable - libopenjpeg --disable - iconv --disable - zlib --prefix = $BASE_DIR / $PATH / build --toolchain = msvc $DEBUG
            make - j 8

      }


      function install_lib()
      {

         REL = $3
            SRC_FOLDER = $4
            STG_FOLDER = $5
            LIBRARY_NAME = $6

            cp - Rf $BASE_DIR / $NAME / lib$LIBRARY_NAME/*.dll $STORAGE_DIR/binary/
            cp -Rf $BASE_DIR/$NAME/lib$LIBRARY_NAME/*.pdb $STORAGE_DIR/binary/

         }

         function install()
         {

            NAME=$2
            REL=$3
            SRC_FOLDER=$4
            STG_FOLDER=$5

            cd $BASE_DIR
            cd $NAME

            make install

            SOURCE_DIR="$SRC_FOLDER"
            STORAGE_DIR="$STG_FOLDER/$REL"

            mkdir -p $SOURCE_DIR/include/
            mkdir -p $STORAGE_DIR/binary/
            mkdir -p $STORAGE_DIR/library/

            cp -Rf $BASE_DIR/$NAME/build/include/* $SOURCE_DIR/include/
            cp -Rf $BASE_DIR/$NAME/build/bin/*.exe $STORAGE_DIR/binary/
            cp -Rf $BASE_DIR/$NAME/build/bin/*.lib $STORAGE_DIR/library/
            cp -Rf $BASE_DIR/$NAME/build/lib/* $STORAGE_DIR/library/

            install_lib "$1" "$2" "$3" "$4" "$5" "avcodec"
            install_lib "$1" "$2" "$3" "$4" "$5" "avdevice"
            install_lib "$1" "$2" "$3" "$4" "$5" "avfilter"
            install_lib "$1" "$2" "$3" "$4" "$5" "avformat"
            install_lib "$1" "$2" "$3" "$4" "$5" "avutil"
            install_lib "$1" "$2" "$3" "$4" "$5" "swresample"
            install_lib "$1" "$2" "$3" "$4" "$5" "swscale"

         }





   }


   void ffmpeg::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == "simple_checkbox"
         || ptopic->m_atom == "no_client_frame")
      {

         set_need_redraw();
         
         post_redraw();

      }

      ::user::impact::handle(ptopic, pcontext);
   }


   ::user::document * ffmpeg::get_document()
   {

      return ::user::impact::get_document();

   }


   void ffmpeg::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
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


   void ffmpeg::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if(rectangleClient.is_empty())
      {

         return;

      }

      //m_prender->m_rectangle = rectangleClient;

   }


} // namespace simple_drawing



