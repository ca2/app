#include "framework.h"
#include "geoip.h"
#include <stdio.h>
#include <string.h>

static
const ::i32 FULL_RECORD_LENGTH = 50;

static
GeoIPRecord * _extract_record(GeoIP* gi, ::u32 seek_record, ::i32 *next_record_ptr)
{
   ::i32 record_pointer;
   ::u8 * record_buf = nullptr;
   ::u8 * begin_record_buf = nullptr;
   GeoIPRecord * record;
   ::i32 str_length = 0;
   ::i32 j;
   ::f64 latitude = 0, longitude = 0;
   ::i32 metroarea_combo = 0;
   size_t bytes_read = 0;
   if (seek_record == gi->databaseSegments[0])
      return nullptr;

   record = (GeoIPRecord *) malloc(sizeof(GeoIPRecord));
   memory_set(record, 0, sizeof(GeoIPRecord));

   record->charset = gi->charset;

   record_pointer = seek_record + (2 * gi->record_length - 1) * gi->databaseSegments[0];

   if (gi->cache == nullptr)
   {
      fseek(gi->GeoIPDataaxis, record_pointer, SEEK_SET);
      begin_record_buf = record_buf = (::u8 * ) malloc(sizeof(::i8) * FULL_RECORD_LENGTH);
      bytes_read = fread(record_buf, sizeof(::i8), FULL_RECORD_LENGTH, gi->GeoIPDataaxis);
      if (bytes_read == 0)
      {
         /* eof or other error */
         free(begin_record_buf);
         free(record);
         return nullptr;
      }
   }
   else
   {
      record_buf = gi->cache + (long)record_pointer;
   }

   /* get country */
   record->continent_code = (char_pointer ) GeoIP_country_continent[record_buf[0]];
   record->country_code   = (char_pointer ) GeoIP_country_code [record_buf[0]];
   record->country_code3 = (char_pointer ) GeoIP_country_code3[record_buf[0]];
   record->country_name   = (char_pointer ) GeoIP_country_name [record_buf[0]];
   record_buf++;

   /* get region */
   while (record_buf[str_length] != '\0')
      str_length++;
   if (str_length > 0)
   {
      record->region = (char_pointer ) malloc(str_length+1);
      ansi_count_copy(record->region, (char_pointer )record_buf, str_length+1);
   }
   record_buf += str_length + 1;
   str_length = 0;

   /* get city */
   while (record_buf[str_length] != '\0')
      str_length++;
   if (str_length > 0)
   {
      if ( gi->charset == GEOIP_CHARSET_UTF8 )
      {
         record->city = _iso_8859_1__utf8( (const_char_pointer )record_buf );
      }
      else
      {
         record->city = (char_pointer ) malloc(str_length+1);
         ansi_count_copy(record->city, ( const_char_pointer )record_buf, str_length+1);
      }
   }
   record_buf += (str_length + 1);
   str_length = 0;

   /* get postal code */
   while (record_buf[str_length] != '\0')
      str_length++;
   if (str_length > 0)
   {
      record->postal_code = (char_pointer ) malloc(str_length+1);
      ansi_count_copy(record->postal_code, (char_pointer )record_buf, str_length+1);
   }
   record_buf += (str_length + 1);

   /* get latitude */
   for (j = 0; j < 3; ++j)
      latitude += (record_buf[j] << (j * 8));
   record->latitude = (::f32) (latitude/10000 - 180);
   record_buf += 3;

   /* get longitude */
   for (j = 0; j < 3; ++j)
      longitude += (record_buf[j] << (j * 8));
   record->longitude = (::f32) (longitude/10000 - 180);

   /* get area code and metro code for post April 2002 databases and for US locations */
   if ((::i8) GEOIP_CITY_EDITION_REV1 == gi->databaseType)
   {
      if (!strcmp(record->country_code, "US"))
      {
         record_buf += 3;
         for (j = 0; j < 3; ++j)
            metroarea_combo += (record_buf[j] << (j * 8));
         record->metro_code = metroarea_combo/1000;
         record->area_code = metroarea_combo % 1000;
      }
   }

   if (gi->cache == nullptr)
      free(begin_record_buf);

   /* Used for GeoIP_next_record */
   if (next_record_ptr != nullptr)
      *next_record_ptr = (::i32) (seek_record + record_buf - begin_record_buf + 3);

   return record;
}


static GeoIPRecord * _get_record(GeoIP* gi, ::u32 ipnum)
{
   
   ::u32 seek_record;

   if (gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV0 &&
         gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV1)
   {
      
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(::i32)gi->databaseType], GeoIPDBDescription[GEOIP_CITY_EDITION_REV1]);
      
      return 0;

   }

   seek_record = _GeoIP_seek_record(gi, ipnum);
   
   return _extract_record(gi, seek_record, nullptr);

}


#ifdef GEOIP_NETWORKING
static
GeoIPRecord * _get_record_v6(GeoIP* gi, geoipv6_t ipnum)
{
   ::u32 seek_record;

   if (gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV0 &&
         gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(::i32)gi->databaseType], GeoIPDBDescription[GEOIP_CITY_EDITION_REV1]);
      return 0;
   }

   seek_record = _GeoIP_seek_record_v6(gi, ipnum);
   return _extract_record(gi, seek_record, nullptr);
}



GeoIPRecord * GeoIP_record_by_ipnum (GeoIP* gi, ::u32 ipnum)
{
   return _get_record(gi, ipnum);
}

GeoIPRecord * GeoIP_record_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum)
{
   return _get_record_v6(gi, ipnum);
}

GeoIPRecord * GeoIP_record_by_addr (GeoIP* gi, const_char_pointer addr)
{
   ::u32 ipnum;
   if (addr == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_addr_to_num(addr);
   return _get_record(gi, ipnum);
}

GeoIPRecord * GeoIP_record_by_addr_v6 (GeoIP* gi, const_char_pointer addr)
{
   geoipv6_t ipnum;
   if (addr == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_addr_to_num_v6(addr);
   return _get_record_v6(gi, ipnum);
}

GeoIPRecord * GeoIP_record_by_name (GeoIP* gi, const_char_pointer pszName)
{
   ::u32 ipnum;
   if (name == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_lookupaddress(name);
   return _get_record(gi, ipnum);
}

GeoIPRecord * GeoIP_record_by_name_v6 (GeoIP* gi, const_char_pointer pszName)
{
   geoipv6_t ipnum;
   if (name == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_lookupaddress_v6(name);
   return _get_record_v6(gi, ipnum);
}

::i32 GeoIP_record_id_by_addr (GeoIP* gi, const_char_pointer addr)
{
   ::u32 ipnum;
   if (gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV0 &&
         gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(::i32)gi->databaseType], GeoIPDBDescription[GEOIP_CITY_EDITION_REV1]);
      return 0;
   }
   if (addr == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_addr_to_num(addr);
   return _GeoIP_seek_record(gi, ipnum);
}

::i32 GeoIP_record_id_by_addr_v6 (GeoIP* gi, const_char_pointer addr)
{
   geoipv6_t ipnum;
   if (gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV0 &&
         gi->databaseType != (::i8) GEOIP_CITY_EDITION_REV1)
   {
      debug_print("Invalid database type %s, expected %s\n", GeoIPDBDescription[(::i32)gi->databaseType], GeoIPDBDescription[GEOIP_CITY_EDITION_REV1]);
      return 0;
   }
   if (addr == nullptr)
   {
      return 0;
   }
   ipnum = _GeoIP_addr_to_num_v6(addr);
   return _GeoIP_seek_record_v6(gi, ipnum);
}
#endif // GEOIP_NETWORKING

::i32 GeoIP_init_record_iter (GeoIP* gi)
{
   return gi->databaseSegments[0] + 1;
}

::i32 GeoIP_next_record (GeoIP* gi, GeoIPRecord **gir, ::i32 *record_iter)
{
   if (gi->cache != nullptr)
   {
      debug_print("GeoIP_next_record not supported in memory cache mode\n");
      return 1;
   }
   *gir = _extract_record(gi, *record_iter, record_iter);
   return 0;
}

void GeoIPRecord_delete (GeoIPRecord *gir)
{
   free(gir->region);
   free(gir->city);
   free(gir->postal_code);
   free(gir);
}



char_pointer _iso_8859_1__utf8(const_char_pointer iso)
{

   ::i8 ca;
   ::i8 k;
   char_pointer p;
   char_pointer t = (char_pointer )iso;
   character_count len = 0;
   while ( ( ca = *t++) )
   {
      if ( ca < 0 )
         len++;
   }
   len += t - iso;
   t = p = (char_pointer ) malloc( (size_t) len );

   if ( p )
   {
      while ( ( ca = *iso++ ) )
      {
         if (ca < 0 )
         {
            k = '\xc2';
            if (ca >= -64 )
               k++;
            *t++ = k;
            ca &= ~0x40;
         }
         *t++ = ca;
      }
      *t++ = 0x00;
   }
   return p;
}
