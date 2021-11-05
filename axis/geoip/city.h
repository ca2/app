#pragma once

typedef struct GeoIPRecordTag {
   char *country_code;
   char *country_code3;
   char *country_name;
   char *region;
   char *city;
   char *postal_code;
   float latitude;
   float longitude;
   union {
     i32 metro_code; /* metro_code is a alias for dma_code */
     i32 dma_code;
        };
   i32 area_code;
   i32 charset;
   char *continent_code;
} GeoIPRecord;

GEOIP_API GeoIPRecord * GeoIP_record_by_ipnum (GeoIP* gi, u32 ipnum);
GEOIP_API GeoIPRecord * GeoIP_record_by_addr (GeoIP* gi, const char *addr);
GEOIP_API GeoIPRecord * GeoIP_record_by_name (GeoIP* gi, const char *host);

GEOIP_API GeoIPRecord * GeoIP_record_by_ipnum_v6 (GeoIP* gi, geoipv6_t ipnum);
GEOIP_API GeoIPRecord * GeoIP_record_by_addr_v6 (GeoIP* gi, const char *addr);
GEOIP_API GeoIPRecord * GeoIP_record_by_name_v6 (GeoIP* gi, const char *host);

GEOIP_API i32 GeoIP_record_id_by_addr (GeoIP* gi, const char *addr);
GEOIP_API i32 GeoIP_record_id_by_addr_v6 (GeoIP* gi, const char *addr);

GEOIP_API i32 GeoIP_init_record_iter (GeoIP* gi);
/* returns 0 on success, 1 on failure */
GEOIP_API i32 GeoIP_next_record (GeoIP* gi, GeoIPRecord **gir, i32 *record_iter);

GEOIP_API void GeoIPRecord_delete (GeoIPRecord *gir);

/* nullptr on failure otherwise a malloced string in utf8 */
GEOIP_API char * _iso_8859_1__utf8(const char *);

