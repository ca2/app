#pragma once

#include "rdpclient.h"

struct axisrdp_bitmap
{
   rdpBitmap _bitmap;
   ::u8* pdata;
};


struct axisrdp_context:
   public rdpContext
{

   DEFINE_RDP_CLIENT_COMMON();

   rdpSettings* settings;

   ::i8 window_title[64];
   ::i32 width;
   ::i32 height;
   ::i32 offset_x;
   ::i32 offset_y;
   ::i32 client_x;
   ::i32 client_y;
   ::i32 client_width;
   ::i32 client_height;
   ::u32 bitmap_size;
   ::u8* bitmap_buffer;

   //axisrdp_bitmap* primary;
   //axisrdp_bitmap* drawing;

   ::u3216 srcBpp;
   ::u3216 dstBpp;
   rdpCodecs* codecs;
   freerdp* instance;

};
