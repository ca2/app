#include "framework.h"

const char* GeoIP_time_zone_by_country_and_region(const char * country,const char * region)
{
   const char* timezone = nullptr;
   if (country == nullptr)
   {
      return nullptr;
   }
   if (region == nullptr)
   {
      region = "";
   }
   if(strlen(country) == 2)
   {
      if(country[0] == 'A')
      {
         if(country[1] == 'D')
         {
            timezone = "Europe/Andorra";
         }
         else if(country[1] == 'E')
         {
            timezone = "Asia/Dubai";
         }
         else if(country[1] == 'F')
         {
            timezone = "Asia/Kabul";
         }
         else if(country[1] == 'G')
         {
            timezone = "America/Antigua";
         }
         else if(country[1] == 'I')
         {
            timezone = "America/Anguilla";
         }
         else if(country[1] == 'L')
         {
            timezone = "Europe/Tirane";
         }
         else if(country[1] == 'M')
         {
            timezone = "Asia/Yerevan";
         }
         else if(country[1] == 'N')
         {
            timezone = "America/Curacao";
         }
         else if(country[1] == 'O')
         {
            timezone = "Africa/Luanda";
         }
         else if(country[1] == 'R')
         {
            timezone = "America/Mendoza";
         }
         else if(country[1] == 'S')
         {
            timezone = "US/Samoa";
         }
         else if(country[1] == 'T')
         {
            timezone = "Europe/Vienna";
         }
         else if(country[1] == 'U')
         {
            if(strcmp (region, "01") == 0 )
            {
               timezone = "Australia/Canberra";
            }
            else if ( strcmp (region, "02") == 0 ) 
            {
               timezone = "Australia/NSW";
            }
            else if ( strcmp (region, "03") == 0 )
            {
               timezone = "Australia/North";
            }
            else if ( strcmp (region, "04") == 0 )
            {
               timezone = "Australia/Queensland";
            }
            else if ( strcmp (region, "05") == 0 )
            {
               timezone = "Australia/South";
            }
            else if ( strcmp (region, "06") == 0 )
            {
               timezone = "Australia/Tasmania";
            }
            else if ( strcmp (region, "07") == 0 )
            {
               timezone = "Australia/Victoria";
            }
            else if ( strcmp (region, "08") == 0 )
            {
               timezone = "Australia/West";
            }
         }
         else if(country[1] == 'w')
         {
            timezone = "America/Aruba";
         }
         else if(country[1] == 'X')
         {
            timezone = "Europe/Mariehamn";
         }
         else if(country[1] == 'Z')
         {
            timezone = "Asia/Baku";
         }
      }
      else if(country[0] == 'B')
      {
         if(country[1] == 'A')
         {
            timezone = "Europe/Sarajevo";
         }
         else if(country[1] == 'B')
         {
            timezone = "America/Barbados";
         }
         else if(country[1] == 'D')
         {
            timezone = "Asia/Dhaka";
         }
         else if(country[1] == 'E')
         {
            timezone = "Europe/Brussels";
         }
         else if(country[1] == 'F')
         {
            timezone = "Africa/Ouagadougou";
         }
         else if(country[1] == 'G')
         {
            timezone = "Europe/Sofia";
         }
         else if(country[1] == 'H')
         {
            timezone = "Asia/Bahrain";
         }
         else if(country[1] == 'I')
         {
            timezone = "Africa/Bujumbura";
         }
         else if(country[1] == 'J')
         {
            timezone = "Africa/Porto-Novo";
         }
         else if(country[1] == 'L')
         {
            timezone = "America/St_Barthelemy";
         }
         else if(country[1] == 'M')
         {
            timezone = "Atlantic/Bermuda";
         }
         else if(country[1] == 'N')
         {
            timezone = "Asia/Brunei";
         }
         else if(country[1] == 'O')
         {
            timezone = "America/La_Paz";
         }
         else if(country[1] == 'R')
         {
            timezone = "Brazil/Acre";
         }
         else if(country[1] == 'S')
         {
            timezone = "America/Nassau";
         }
         else if(country[1] == 'T')
         {
            timezone = "Asia/Thimphu";
         }
         else if(country[1] == 'W')
         {
            timezone = "Africa/Gaborone";
         }
         else if(country[1] == 'Y')
         {
            timezone = "Europe/Minsk";
         }
         else if(country[1] == 'Z')
         {
            timezone = "America/Belize";
         }
      }
      else if(country[0] == 'C')
      {
         if(country[1] == 'A')
         {
            if( strcmp (region, "AB") == 0 )
            {
               timezone = "America/Edmonton";
            }
            else if ( strcmp (region, "BC") == 0 )
            {
               timezone = "America/Vancouver";
            }
            else if ( strcmp (region, "MB") == 0 )
            {
               timezone = "America/Winnipeg";
            }
            else if ( strcmp (region, "NB") == 0 )
            {
               timezone = "America/Halifax";
            }
            else if ( strcmp (region, "NL") == 0 )
            {
               timezone = "America/St_Johns";
            }
            else if ( strcmp (region, "NS") == 0 )
            {
               timezone = "America/Halifax";
            }
            else if ( strcmp (region, "NT") == 0 )
            {
               timezone = "America/Yellowknife";
            }
            else if ( strcmp (region, "NU") == 0 )
            {
               timezone = "America/Rankin_Inlet";
            }
            else if ( strcmp (region, "ON") == 0 )
            {
               timezone = "America/Rainy_River";
            }
            else if ( strcmp (region, "PE") == 0 )
            {
               timezone = "America/Halifax";
            }
            else if ( strcmp (region, "QC") == 0 )
            {
               timezone = "America/Montreal";
            }
            else if ( strcmp (region, "SK") == 0 )
            {
               timezone = "America/Regina";
            }
            else if ( strcmp (region, "YT") == 0 )
            {
               timezone = "America/Whitehorse";
            }
         }
         else if(country[1] == 'C')
         {
            timezone = "Indian/Cocos";
         }
         else if(country[1] == 'F')
         {
            timezone = "Africa/Bangui";
         }
         else if(country[1] == 'G')
         {
            timezone = "Africa/Brazzaville";
         }
         else if(country[1] == 'H')
         {
          timezone = "Europe/Zurich";
        }
        else if(country[1] == 'I')
        {
          timezone = "Africa/Abidjan";
        }
        else if(country[1] == 'K')
        {
          timezone = "Pacific/Rarotonga";
        }
        else if(country[1] == 'L')
        {
          timezone = "Chile/Continental";
        }
        else if(country[1] == 'M')
        {
          timezone = "Africa/Lagos";
        }
        else if(country[1] == 'N')
        {
          timezone = "Asia/Chongqing";
        }
        else if(country[1] == 'O')
        {
          timezone = "America/Bogota";
        }
        else if(country[1] == 'R')
        {
          timezone = "America/Costa_Rica";
        }
        else if(country[1] == 'U')
        {
          timezone = "America/Havana";
        }
        else if(country[1] == 'V')
        {
          timezone = "Atlantic/Cape_Verde";
        }
        else if(country[1] == 'X')
        {
          timezone = "Indian/Christmas";
        }
        else if(country[1] == 'Y')
        {
            timezone = "Asia/Nicosia";
        }
        else if(country[1] == 'Z')
        {
            timezone = "Europe/Prague";
        }
      }
      else if(country[0] == 'D')
      {
         if(country[1] == 'E')
         {
            timezone = "Europe/Berlin";
         }
         else if(country[1] == 'J')
         {
            timezone = "Africa/Djibouti";
         }
         else if(country[1] == 'K')
         {
            timezone = "Europe/Copenhagen";
         }
         else if(country[1] == 'M')
         {
            timezone = "America/Dominica";
         }
         else if(country[1] == 'O')
         {
            timezone = "America/Santo_Domingo";
         }
         else if(country[1] == 'Z')
         {
            timezone = "Africa/Algiers";
         }
      }
      else if(country[1] == 'E')
      {
         if(country[1] == 'C')
         {
            timezone = "America/Guayaquil";
         }
         else if(country[1] == 'E')
         {
            timezone = "Europe/Tallinn";
         }
         else if(country[1] == 'G')
         {
            timezone = "Africa/Cairo";
         }
         else if(country[1] == 'H')
         {
            timezone = "Africa/El_Aaiun";
         }
         else if(country[1] == 'R')
         {
            timezone = "Africa/Asmera";
         }
         else if(country[1] == 'S')
         {
            timezone = "Europe/Madrid";
         }
         else if(country[1] == 'T')
         {
            timezone = "Africa/Addis_Ababa";
         }
      }
      else if(country[0] == 'F')
      {
         if(country[1] == 'I')
         {
            timezone = "Europe/Helsinki";
         }
         else if(country[1] == 'J')
         {
            timezone = "Pacific/Fiji";
         }
         else if(country[1] == 'K')
         {
            timezone = "Atlantic/Stanley";
         }
         else if(country[1] == 'O')
         {
            timezone = "Atlantic/Faeroe";
         }
         else if(country[1] == 'R')
         {
            timezone = "Europe/Paris";
         }
         else if(country[1] == 'X')
         {
            timezone = "Europe/Paris";
         }
      }
      else if(country[0] == 'G')
      {
         if(country[1] == 'A')
         {
            timezone = "Africa/Libreville";
         }
         else if(country[1] == 'B')
         {
            timezone = "Europe/London";
         }
         else if(country[1] == 'D')
         {
            timezone = "America/Grenada";
         }
         else if(country[1] == 'E')
         {
            timezone = "Asia/Tbilisi";
         }
         else if(country[1] == 'F')
         {
            timezone = "America/Cayenne";
         }
         else if(country[1] == 'G')
         {
            timezone = "Europe/Guernsey";
         }
         else if(country[1] == 'H')
         {
            timezone = "Africa/Accra";
         }
         else if(country[1] == 'I')
         {
            timezone = "Europe/Gibraltar";
         }
         else if(country[1] == 'L')
         {
            timezone = "America/Godthab";
         }
         else if(country[1] == 'M')
         {
            timezone = "Africa/Banjul";
         }
         else if(country[1] == 'N')
         {
            timezone = "Africa/Conakry";
         }
         else if(country[1] == 'P')
         {
            timezone = "America/Guadeloupe";
         }
         else if(country[1] == 'Q')
         {
            timezone = "Africa/Malabo";
         }
         else if(country[1] == 'R')
         {
            timezone = "Europe/Athens";
         }
         else if(country[1] == 'S')
         {
            timezone = "Atlantic/South_Georgia";
         }
         else if(country[1] == 'T')
         {
            timezone = "America/Guatemala";
         }
         else if(country[1] == 'U')
         {
            timezone = "Pacific/Guam";
         }
         else if(country[1] == 'W')
         {
            timezone = "Africa/Bissau";
         }
         else if(country[1] == 'Y')
         {
            timezone = "America/Guyana";
         }
     }   
     else if(country[0] == 'H')
     {
         if(country[1] == 'K')
         {
            timezone = "Asia/Hong_Kong";
         }
         else if(country[1] == 'N')
         {
            timezone = "America/Tegucigalpa";
         }
         else if(country[1] == 'R')
         {
            timezone = "Europe/Zagreb";
         }
         else if(country[1] == 'T')
         {
            timezone = "America/Port-au-Prince";
         }
        else if(country[1] == 'U')
        {
          timezone = "Europe/Budapest";
        }
   }
   else if(country[0] == 'I')
   {
      if(country[1] == 'D')
      {
         timezone = "Asia/Jakarta";
      }
      else if(country[1] == 'E')
      {
         timezone = "Europe/Dublin";
      }
      else if(country[1] == 'L')
      {
         timezone = "Asia/Jerusalem";
      }
      else if(country[1] == 'M')
      {
         timezone = "Europe/Isle_of_Man";
      }
      else if(country[1] == 'N')
      {
         timezone = "Asia/Calcutta";
      }
      else if(country[1] == 'O')
      {
         timezone = "Indian/Chagos";
      }
      else if(country[1] == 'Q')
      {
         timezone = "Asia/Baghdad";
      }
      else if(country[1] == 'R')
      {
         timezone = "Asia/Tehran";
      }
      else if(country[1] == 'S')
      {
         timezone = "Atlantic/Reykjavik";
      }
      else if(country[1] == 'T')
      {
         timezone = "Europe/Rome";
      }
    }
    else if(country[0] == 'J')
    {
      if(country[1] == 'E')
      {
         timezone = "Europe/Jersey";
      }
      else if(country[1] == 'M')
      {
         timezone = "America/Jamaica";
      }
      else if(country[1] == 'O')
      {
         timezone = "Asia/Amman";
      }
      else if(country[1] == 'P')
      {
         timezone = "Asia/Tokyo";
      }
   }
   else if(country[0] == 'K')
   {
      if(country[1] == 'E')
      {
         timezone = "Africa/Nairobi";
      }
      else if(country[1] == 'G')
      {
         timezone = "Asia/Bishkek";
      }
      else if(country[1] == 'H')
      {
         timezone = "Asia/Phnom_Penh";
      }
      else if(country[1] == 'I')
      {
         timezone = "Pacific/Tarawa";
      }
      else if(country[1] == 'M')
      {
         timezone = "Indian/Comoro";
      }
      else if(country[1] == 'N')
      {
         timezone = "America/St_Kitts";
      }
      else if(country[1] == 'P')
      {
         timezone = "Asia/Pyongyang";
      }
      else if(country[1] == 'R')
      {
         timezone = "Asia/Seoul";
      }
      else if(country[1] == 'W')
      {
         timezone = "Asia/Kuwait";
      }
      else if(country[1] == 'Y')
      {
         timezone = "America/Cayman";
      }
      else if(country[1] == 'Z')
      {
         timezone = "Asia/Almaty";
      }
    }
    else if(country[0] == 'L')
    {
      if(country[1] == 'A')
      {
         timezone = "Asia/Vientiane";
      }
      else if(country[1] == 'B')
      {
         timezone = "Asia/Beirut";
      }
      else if(country[1] == 'C')
      {
         timezone = "America/St_Lucia";
      }
      else if(country[1] == 'I')
      {
         timezone = "Europe/Vaduz";
      }
      else if(country[1] == 'K')
      {
         timezone = "Asia/Colombo";
      }
      else if(country[1] == 'R')
      {
         timezone = "Africa/Monrovia";
      }
      else if(country[1] == 'S')
      {
         timezone = "Africa/Maseru";
      }
      else if(country[1] == 'T')
      {
         timezone = "Europe/Vilnius";
      }
      else if(country[1] == 'U')
      {
         timezone = "Europe/Luxembourg";
      }
      else if(country[1] == 'V')
      {
         timezone = "Europe/Riga";
      }
      else if(country[1] == 'Y')
      {
         timezone = "Africa/Tripoli";
      }
   }
   else if(country[0] == 'M')
   {
      if(country[1] == 'A')
      {
         timezone = "Africa/Casablanca";
      }
      else if(country[1] == 'C')
      {
         timezone = "Europe/Monaco";
      }
      else if(country[1] == 'D')
      {
         timezone = "Europe/Chisinau";
      }
      else if(country[1] == 'E')
      {
         timezone = "Europe/Podgorica";
      }
      else if(country[1] == 'F')
      {
         timezone = "America/Marigot";
      }
      else if(country[1] == 'G')
      {
         timezone = "Indian/Antananarivo";
      }
      else if(country[1] == 'K')
      {
         timezone = "Europe/Skopje";
      }
      else if(country[1] == 'L')
      {
         timezone = "Africa/Bamako";
      }
      else if(country[1] == 'M')
      {
         timezone = "Asia/Rangoon";
      }
      else if(country[1] == 'N')
      {
         timezone = "Asia/Choibalsan";
      }
      else if(country[1] == 'O')
      {
         timezone = "Asia/Macao";
      }
      else if(country[1] == 'P')
      {
         timezone = "Pacific/Saipan";
      }
      else if(country[1] == 'Q')
      {
         timezone = "America/Martinique";
      }
      else if(country[1] == 'R')
      {
         timezone = "Africa/Nouakchott";
      }
      else if(country[1] == 'S')
      {
         timezone = "America/Montserrat";
      }
      else if(country[1] == 'T')
      {
         timezone = "Europe/Malta";
      }
      else if(country[1] == 'U')
      {
         timezone = "Indian/Mauritius";
      }
      else if(country[1] == 'V')
      {
         timezone = "Indian/Maldives";
      }
      else if(country[1] == 'W')
      {
         timezone = "Africa/Blantyre";
      }
      else if(country[1] == 'X')
      {
         timezone = "America/Chihuahua";
      }
      else if(country[1] == 'Z')
      {
         timezone = "Africa/Maputo";
      }
   }
   else if(country[0] == 'N')
   {
      if(country[1] == 'A')
      {
         timezone = "Africa/Windhoek";
      }
      else if(country[1] == 'C')
      {
         timezone = "Pacific/Noumea";
      }
      else if(country[1] == 'E')
      {
         timezone = "Africa/Niamey";
      }
      else if(country[1] == 'F')
      {
         timezone = "Pacific/Norfolk";
      }
      else if(country[1] == 'G')
      {
         timezone = "Africa/Lagos";
      }
      else if(country[1] == 'I')
      {
         timezone = "America/Managua";
      }
      else if(country[1] == 'L')
      {
         timezone = "Europe/Amsterdam";
      }
      else if(country[1] == 'O')
      {
         timezone = "Europe/Oslo";
      }
      else if(country[1] == 'P')
      {
         timezone = "Asia/Katmandu";
      }
      else if(country[1] == 'R')
      {
         timezone = "Pacific/Nauru";
      }
      else if(country[1] == 'U')
      {
         timezone = "Pacific/Niue";
      }
      else if(country[1] == 'Z')
      {
         timezone = "Pacific/Auckland";
      }
   }
   else if(country[0] == 'O')
   {
      if(country[1] == 'M')
      {
         timezone = "Asia/Muscat";
      }
   }
   else if(country[0] == 'P')
   {
      if(country[1] == 'A')
      {
         timezone = "America/Panama";
      }
      else if(country[1] == 'E')
      {
         timezone = "America/Lima";
      }
      else if(country[1] == 'G')
      {
         timezone = "Pacific/Port_Moresby";
      }
      else if(country[1] == 'H')
      {
         timezone = "Asia/Manila";
      }
      else if(country[1] == 'K')
      {
         timezone = "Asia/Karachi";
      }
      else if(country[1] == 'L')
      {
         timezone = "Europe/Warsaw";
      }
      else if(country[1] == 'M')
      {
         timezone = "America/Miquelon";
      }
      else if(country[1] == 'N')
      {
         timezone = "Pacific/Pitcairn";
      }
      else if(country[1] == 'R')
      {
         timezone = "America/Puerto_Rico";
      }
      else if(country[1] == 'S')
      {
         timezone = "Asia/Gaza";
      }
      else if(country[1] == 'T')
      {
         timezone = "Atlantic/Azores";
      }
      else if(country[1] == 'W')
      {
         timezone = "Pacific/Palau";
      }
      else if(country[1] == 'Y')
      {
         timezone = "America/Asuncion";
      }
   }
   else if(country[0] == 'Q')
   {
      if(country[1] == 'A')
      {
         timezone = "Asia/Qatar";
      }
   }
   else if(country[0] == 'R')
   {
      if(country[1] == 'E')
      {
         timezone = "Indian/Reunion";
      }
      else if(country[1] == 'O')
      {
         timezone = "Europe/Bucharest";
      }
      else if(country[1] == 'S')
      {
         timezone = "Europe/Belgrade";
      }
      else if(country[1] == 'U')
      {
         timezone = "Europe/Moscow";
      }
      else if(country[1] == 'W')
      {
         timezone = "Africa/Kigali";
      }
   }
   else if(country[0] == 'S')
   {
      if(country[1] == 'A')
      {
         timezone = "Asia/Riyadh";
      }
      else if(country[1] == 'B')
      {
         timezone = "Pacific/Guadalcanal";
      }
      else if(country[1] == 'C')
      {
         timezone = "Indian/Mahe";
      }
      else if(country[1] == 'D')
      {
         timezone = "Africa/Khartoum";
      }
      else if(country[1] == 'E')
      {
         timezone = "Europe/Stockholm";
      }
      else if(country[1] == 'G')
      {
         timezone = "Asia/Singapore";
      }
      else if(country[1] == 'H')
      {
         timezone = "Atlantic/St_Helena";
      }
      else if(country[1] == 'I')
      {
         timezone = "Europe/Ljubljana";
      }
      else if(country[1] == 'J')
      {
         timezone = "Arctic/Longyearbyen";
      }
      else if(country[1] == 'K')
      {
         timezone = "Europe/Bratislava";
      }
      else if(country[1] == 'L')
      {
         timezone = "Africa/Freetown";
      }
      else if(country[1] == 'M')
      {
         timezone = "Europe/San_Marino";
      }
      else if(country[1] == 'N')
      {
         timezone = "Africa/Dakar";
      }
      else if(country[1] == 'O')
      {
         timezone = "Africa/Mogadishu";
      }
      else if(country[1] == 'R')
      {
         timezone = "America/Paramaribo";
      }
      else if(country[1] == 'T')
      {
         timezone = "Africa/Sao_Tome";
      }
      else if(country[1] == 'V')
      {
         timezone = "America/El_Salvador";
      }
      else if(country[1] == 'Y')
      {
         timezone = "Asia/Damascus";
      }
      else if(country[1] == 'Z')
      {
         timezone = "Africa/Mbabane";
      }
   }
 }
 if ( strcmp (country, "TC") == 0 ) {
    timezone = "America/Grand_Turk";
  }
  else if ( strcmp (country, "TD") == 0 ) {
    timezone = "Africa/Ndjamena";
  }
  else if ( strcmp (country, "TF") == 0 ) {
    timezone = "Indian/Kerguelen";
  }
  else if ( strcmp (country, "TG") == 0 ) {
    timezone = "Africa/Lome";
  }
  else if ( strcmp (country, "TH") == 0 ) {
    timezone = "Asia/Bangkok";
  }
  else if ( strcmp (country, "TJ") == 0 ) {
    timezone = "Asia/Dushanbe";
  }
  else if ( strcmp (country, "TK") == 0 ) {
    timezone = "Pacific/Fakaofo";
  }
  else if ( strcmp (country, "TL") == 0 ) {
    timezone = "Asia/Jakarta";
  }
  else if ( strcmp (country, "TM") == 0 ) {
    timezone = "Asia/Ashgabat";
  }
  else if ( strcmp (country, "TN") == 0 ) {
    timezone = "Africa/Tunis";
  }
  else if ( strcmp (country, "TO") == 0 ) {
    timezone = "Pacific/Tongatapu";
  }
  else if ( strcmp (country, "TR") == 0 ) {
    timezone = "Asia/Istanbul";
  }
  else if ( strcmp (country, "TT") == 0 ) {
    timezone = "America/Port_of_Spain";
  }
  else if ( strcmp (country, "TV") == 0 ) {
    timezone = "Pacific/Funafuti";
  }
  else if ( strcmp (country, "TW") == 0 ) {
    timezone = "Asia/Taipei";
  }
  else if ( strcmp (country, "TZ") == 0 ) {
    timezone = "Africa/Dar_es_Salaam";
  }
  else if ( strcmp (country, "UA") == 0 ) {
    timezone = "Europe/Kiev";
  }
  else if ( strcmp (country, "UG") == 0 ) {
    timezone = "Africa/Kampala";
  }
  else if ( strcmp (country, "US") == 0 ) {
    if ( strcmp (region, "AK") == 0 ) {
      timezone = "America/Anchorage";
    }
    else if ( strcmp (region, "AL") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "AR") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "AZ") == 0 ) {
      timezone = "America/Phoenix";
    }
    else if ( strcmp (region, "CA") == 0 ) {
      timezone = "America/Los_Angeles";
    }
    else if ( strcmp (region, "CO") == 0 ) {
      timezone = "America/Denver";
    }
    else if ( strcmp (region, "CT") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "DC") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "DE") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "FL") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "GA") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "HI") == 0 ) {
      timezone = "Pacific/Honolulu";
    }
    else if ( strcmp (region, "IA") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "ID") == 0 ) {
      timezone = "America/Denver";
    }
    else if ( strcmp (region, "IL") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "IN") == 0 ) {
      timezone = "America/Indianapolis";
    }
    else if ( strcmp (region, "KS") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "KY") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "LA") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "MA") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "MD") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "ME") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "MI") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "MN") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "MO") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "MS") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "MT") == 0 ) {
      timezone = "America/Denver";
    }
    else if ( strcmp (region, "NC") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "ND") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "NE") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "NH") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "NJ") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "NM") == 0 ) {
      timezone = "America/Denver";
    }
    else if ( strcmp (region, "NV") == 0 ) {
      timezone = "America/Los_Angeles";
    }
    else if ( strcmp (region, "NY") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "OH") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "OK") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "OR") == 0 ) {
      timezone = "America/Los_Angeles";
    }
    else if ( strcmp (region, "PA") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "RI") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "SC") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "SD") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "TN") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "TX") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "UT") == 0 ) {
      timezone = "America/Denver";
    }
    else if ( strcmp (region, "VA") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "VT") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "WA") == 0 ) {
      timezone = "America/Los_Angeles";
    }
    else if ( strcmp (region, "WI") == 0 ) {
      timezone = "America/Chicago";
    }
    else if ( strcmp (region, "WV") == 0 ) {
      timezone = "America/New_York";
    }
    else if ( strcmp (region, "WY") == 0 ) {
      timezone = "America/Denver";
    }
  }
  else if ( strcmp (country, "UY") == 0 ) {
    timezone = "America/Montevideo";
  }
  else if ( strcmp (country, "UZ") == 0 ) {
    timezone = "Asia/Tashkent";
  }
  else if ( strcmp (country, "VA") == 0 ) {
    timezone = "Europe/Vatican";
  }
  else if ( strcmp (country, "VC") == 0 ) {
    timezone = "America/St_Vincent";
  }
  else if ( strcmp (country, "VE") == 0 ) {
    timezone = "America/Caracas";
  }
  else if ( strcmp (country, "VG") == 0 ) {
    timezone = "America/Tortola";
  }
  else if ( strcmp (country, "VI") == 0 ) {
    timezone = "America/St_Thomas";
  }
  else if ( strcmp (country, "VN") == 0 ) {
    timezone = "Asia/Phnom_Penh";
  }
  else if ( strcmp (country, "VU") == 0 ) {
    timezone = "Pacific/Efate";
  }
  else if ( strcmp (country, "WF") == 0 ) {
    timezone = "Pacific/Wallis";
  }
  else if ( strcmp (country, "WS") == 0 ) {
    timezone = "Pacific/Samoa";
  }
  else if ( strcmp (country, "YE") == 0 ) {
    timezone = "Asia/Aden";
  }
  else if ( strcmp (country, "YT") == 0 ) {
    timezone = "Indian/Mayotte";
  }
  else if ( strcmp (country, "YU") == 0 ) {
    timezone = "Europe/Belgrade";
  }
  else if ( strcmp (country, "ZA") == 0 ) {
    timezone = "Africa/Johannesburg";
  }
  else if ( strcmp (country, "ZM") == 0 ) {
    timezone = "Africa/Lusaka";
  }
  else if ( strcmp (country, "ZW") == 0 ) {
    timezone = "Africa/Harare";
  }
  return timezone;
}
