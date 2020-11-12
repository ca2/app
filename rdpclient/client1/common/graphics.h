#pragma once

#include "rdpclient.h"

struct axisrdp_bitmap
{
   rdpBitmap _bitmap;
   byte* pdata;
};


struct axisrdp_context:
   public rdpContext
{

   DEFINE_RDP_CLIENT_COMMON();

   rdpSettings* settings;

   char window_title[64];
   int width;
   int height;
   int offset_x;
   int offset_y;
   int client_x;
   int client_y;
   int client_width;
   int client_height;
   ::u32 bitmap_size;
   byte* bitmap_buffer;

   //axisrdp_bitmap* primary;
   //axisrdp_bitmap* drawing;

   ::u3216 srcBpp;
   ::u3216 dstBpp;
   rdpCodecs* codecs;
   freerdp* instance;

};