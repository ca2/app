#pragma once

typedef struct GeoIPRecordTag {
   char_pointer country_code;
   char_pointer country_code3;
   char_pointer country_name;
   char_pointer region;
   char_pointer city;
   char_pointer postal_code;
   ::f32 latitude;
   ::f32 longitude;
   union {
     ::i32 metro_code; /* metro_code is a alias for dma_code */
     ::i32 dma_code;
        };
   ::i32 area_code;
   ::i32 charset;
   char_pointer continent_code;
} GeoIPRecord;

GEOIP_API GeoIPRecord * GeoIP_record_by_ipnum (GeoIP* gi, ::u32 ipnum);
GEOIP_API GeoIPRecord * GeoIP_record_by_addr (GeoIP* gi, const_char_pointer addr);
GEOIP_API GeoIPRecord * GeoIP_record_by_name (GeoIP* gi, const_char_pointer host);

GEOIP_API GeoIPRecord * GeoIP_record_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum);
GEOIP_API GeoIPRecord * GeoIP_record_by_addr_v6 (GeoIP* gi, const_char_pointer addr);
GEOIP_API GeoIPRecord * GeoIP_record_by_name_v6 (GeoIP* gi, const_char_pointer host);

GEOIP_API ::i32 GeoIP_record_id_by_addr (GeoIP* gi, const_char_pointer addr);
GEOIP_API ::i32 GeoIP_record_id_by_addr_v6 (GeoIP* gi, const_char_pointer addr);

GEOIP_API ::i32 GeoIP_init_record_iter (GeoIP* gi);
/* returns 0 on success, 1 on failure */
GEOIP_API ::i32 GeoIP_next_record (GeoIP* gi, GeoIPRecord **gir, ::i32 *record_iter);

GEOIP_API void GeoIPRecord_delete (GeoIPRecord *gir);

/* nullptr on failure otherwise a malloced string in utf8 */
GEOIP_API char_pointer _iso_8859_1__utf8(const_char_pointer );

