#pragma once

GEOIP_API unsigned int _GeoIP_seek_record (GeoIP *gi, unsigned int ipnum);
GEOIP_API unsigned int _GeoIP_addr_to_num (const_char_pointer addr);

GEOIP_API unsigned int _GeoIP_seek_record_v6 (GeoIP *gi, geoipv6_t ipnum);
GEOIP_API geoipv6_t _GeoIP_addr_to_num_v6 (const_char_pointer addr);

GEOIP_API unsigned int _GeoIP_lookupaddress (const_char_pointer host);
GEOIP_API geoipv6_t _GeoIP_lookupaddress_v6 (const_char_pointer host);
GEOIP_API int __GEOIP_V6_IS_NULL(geoipv6_t v6);

GEOIP_API void _GeoIP_setup_dbfilename();
GEOIP_API char *_GeoIP_full_path_to(const_char_pointer file_name);

