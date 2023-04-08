#pragma once


#ifdef WINDOWS
namespace windows
{

   class media_foundation;

}
#endif


//#include "audio/_.h"


#include "_constant.h"


//#include "decoder.h"
//
//
//#include "decoder_plugin.h"
//
//
//#include "file_application.h"
//
//
//#include "exception.h"


typedef ::multimedia::decoder * NEW_MULTIMEDIA_DECODER();


typedef NEW_MULTIMEDIA_DECODER * LPFN_NEW_MULTIMEDIA_DECODER;


namespace audio
{


   class audio;


} // namespace audio

namespace aqua
{

class audio;
class multimedia;


}


namespace multimedia
{


   class information;

   class multimedia;


} // namespace multimedia


namespace veriwell
{


   namespace multimedia
   {


      class multimedia;


   } // namespace veriwell::multimedia


} // namespace veriwell

//
//#include "audio.h"
//
//
//#include "multimedia.h"
//


