// Added get_time_zone memberby camilo on 2021-12-02 14:23 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "system.h"
#include "_binary_stream.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/sequencer.h"
#include "acme/primitive/datetime/_binary_stream.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/primitive/datetime/earth_zone_time.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "acme/primitive/collection/_map_binary_stream.h"
#include "acme/primitive/datetime/_binary_stream.h"
#include "acme/primitive/mathematics/number_double.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/primitive/string/international.h"
#include "acme/primitive/string/str.h"
#include "acme/user/nano/nano.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/open_weather_city.h"
#include "apex/networking/http/context.h"

#include <unac.h>

namespace geo
{


   geo::geo()
   {

      m_bInitialLocalityTimeZoneInit = false;

      m_bLoadedCityTimeZoneFromFile = false;
      m_bLoadedLocalityTimeZoneFromFile = false;

      m_bCityTimeZoneModified = false; 
      m_bLocalityTimeZoneModified = false;

      m_strImplementation = "ca2";
//      m_strBrowserAccount = "weather";
      //m_strApiClientConfig = "camilothomas";

   }


   geo::~geo()
   {


   }


   void geo::initialize(::particle * pparticle)
   {

      ::acme::department::initialize(pparticle);

      m_pathCityTimeZoneFile = acmedirectory()->system() / "datetime_departament_cityTimeZone.bin";

      m_pathLocalityTimeZoneFile = acmedirectory()->system() / "datetime_departament_LocalityTimeZone.bin";

   }
   

   void geo::defer_check_openweather_city_list()
   {

      synchronous_lock synchronouslock(get_openweather_city_mutex());

      if (m_straCityLo.get_size() == m_straCity.get_size()
         && m_straCity.get_size() == m_iaIds.get_size()
         && m_iaIds.get_size() == m_daLon.get_size()
         && m_daLon.get_size() == m_daLat.get_size()
         && m_straCity.get_size() > 1)
      {

         return;

      }

      ::file::path pathFolder = acmedirectory()->system();

      bool bOk = false;

      auto pcontext = m_pcontext->m_pcontext;

      auto pfile = pcontext->m_papexcontext->file();

      {

         try
         {


         auto memory = pfile->as_memory(pathFolder / "weather.bin");

         auto pfile = __allocate< memory_file >(memory);

         binary_stream stream(pfile);


            stream >> m_straCity;
            stream >> m_straCityLo;
            stream >> m_iaIds;
            stream >> m_daLon;
            stream >> m_daLat;

            for (int i = 0; i < 20; i++)
            {

               informationf("dump: %s, %s, %d, %f, %f\n", m_straCity[i].c_str(), m_straCityLo[i].c_str(), m_iaIds[i], m_daLon[i], m_daLat[i]);

            }

            //pcontext->m_papexcontext->file()->to_array(m_straCity,          auto psystem = system();

   //         auto pacmedirectory = psystem->m_pacmedirectory;
   //
   //pacmedirectory->system() / "weather-cit.bin");
            //pcontext->m_papexcontext->file()->to_array(m_straCityLo,          auto psystem = system();

   //         auto pacmedirectory = psystem->m_pacmedirectory;
   //
   //pacmedirectory->system() / "weather-cil.bin");
            //pcontext->m_papexcontext->file()->to_array(m_iaIds,          auto psystem = system();

   //         auto pacmedirectory = psystem->m_pacmedirectory;
   //
   //pacmedirectory->system() / "weather-ids.bin");
            //pcontext->m_papexcontext->file()->to_array(m_daLon,          auto psystem = system();

   //         auto pacmedirectory = psystem->m_pacmedirectory;
   //
   //pacmedirectory->system() / "weather-lon.bin");
            //pcontext->m_papexcontext->file()->to_array(m_daLat,          auto psystem = system();

   //         auto pacmedirectory = psystem->m_pacmedirectory;
   //
   //pacmedirectory->system() / "weather-lat.bin");


            bOk = m_straCityLo.get_size() == m_straCity.get_size()
               && m_straCity.get_size() == m_iaIds.get_size()
               && m_iaIds.get_size() == m_daLon.get_size()
               && m_daLon.get_size() == m_daLat.get_size()
               && m_straCity.get_size() > 1;

         }
         catch (...)
         {

         }

      }

      if (!bOk)
      {

         try
         {

            if (pfile->exists(pathFolder / "weather.bin"))
            {

               pfile->erase(pathFolder / "weather.bin");

            }

         }
         catch (const ::exception & exception)
         {

            auto psequencer = this->nano()->exception_message_box(exception);

            psequencer->do_asynchronously();

         }
         catch (...)
         {

            ::exception exception(error_catch_all_exception);

            auto psequencer = this->nano()->exception_message_box(exception);

            psequencer->do_asynchronously();

         }

         m_straCityLo.erase_all();
         m_straCity.erase_all();
         m_iaIds.erase_all();
         m_daLon.erase_all();
         m_daLat.erase_all();

      }

      if (m_straCityLo.get_size() == m_straCity.get_size()
         && m_straCity.get_size() == m_iaIds.get_size()
         && m_iaIds.get_size() == m_daLon.get_size()
         && m_daLon.get_size() == m_daLat.get_size()
         && m_straCity.get_size() > 1)
      {
      }
      else
      {

         string str;

         ::payload payload;

         payload["nocache"] = true;
         payload["url"] = "https://ca2.software/city-list.json";

         str = pfile->as_string(payload);

         if (str.has_char())
         {

            string_array stra;

            stra.add_lines(str);

            for (auto strJson : stra)
            {

               const ::ansi_character * pszJson = strJson;

               //const ::ansi_character * pszJson = "{\"_id\":6322752, \"name\" : \"Curitiba\", \"country\" : \"BR\", \"coord\" : {\"lon\":-49.290821, \"lat\" : -25.50395}}";

               ::payload v;

               v.parse_network_payload(pszJson);

               string strLine = v["name"] + ", " + v["country"];

               m_straCity.add(strLine);

               m_straCityLo.add(strLine.lowered());

               i64 iId;

               iId = v["_id"];

               m_iaIds.add(iId);

               double dLon = v["coord"]["lon"].as_f64();

               m_daLon.add(dLon);

               double dLat = v["coord"]["lat"].as_f64();

               m_daLat.add(dLat);

            }

            auto pfileOut = pfile->get_writer(pathFolder / "weather.bin");

            binary_stream stream(pfileOut);

            stream << m_straCity;
            stream << m_straCityLo;
            stream << m_iaIds;
            stream << m_daLon;
            stream << m_daLat;

         }

      }

   }


   openweather_city* geo::openweather_find_city(string strQuery)
   {

      auto& pcity = m_mapCity[strQuery];

      if (!pcity)
      {

         pcity = __new< openweather_city >();

         pcity->m_iIndex = openweather_find_city2(
            strQuery,
            pcity->m_strCit,
            pcity->m_iId,
            pcity->m_dLat,
            pcity->m_dLon);

      }

      return pcity;

   }


   index geo::openweather_find_city2(string strQuery, string& strCit, i64& iId, double& dLat, double& dLon)
   {

      string_array stra;

      stra.explode(",", strQuery);

      stra.trim();

      stra.erase_empty();

      if (stra.get_count() <= 0)
      {

         return -1;

      }

      if (stra.get_count() == 1)
      {

         return openweather_find_city2(strQuery, "", strCit, iId, dLat, dLon, true);

      }


      for (index iCount = stra.get_count() - 1; iCount >= 1; iCount--)
      {

         index iIndex = openweather_find_city2(stra.slice(0, iCount).implode(", "), stra.last(), strCit, iId, dLat, dLon, false);

         if (iIndex >= 0)
         {

            return iIndex;

         }

      }

      for (index iCount = stra.get_count() - 1; iCount >= 1; iCount--)
      {

         index iIndex = openweather_find_city2(stra.slice(0, iCount).implode(", "), stra.last(), strCit, iId, dLat, dLon, true);

         if (iIndex >= 0)
         {

            return iIndex;

         }

      }

      return -1;

   }



   index geo::openweather_find_city2(string strQ1, string strQ2, string& strCit, i64& iId, double& dLat, double& dLon, bool bPrefix)
   {

      string strQueryLo;

      string strTry;

      string strTry1;

      string strTry2;

      index iFind;

      defer_check_openweather_city_list();

      if (strQ1.case_insensitive_order("Cologne") == 0 && strQ2.case_insensitive_order("DE") == 0)
      {

         strQ1 = "Koeln";

      }
      else if (strQ1.case_insensitive_order("Washington DC") == 0)
      {

         strQ1 = "Washington, D. C.";

      }

      strQueryLo = strQ1 + ", " + strQ2;

      strQueryLo.make_lower();

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strQueryLo);

      }
      else
      {

         iFind = m_straCityLo.find_first(strQueryLo);

      }

      if (found(iFind))
      {

         goto found;

      }























      strTry = strQueryLo;

      strTry.replace_with("", "'");

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strTry);

      }
      else
      {

         iFind = m_straCityLo.find_first(strTry);

      }

      if (::found(iFind))
      {

         goto found;

      }

































      strTry = strQueryLo;

      strTry.replace_with("saint", "st.");

      {

         char * out = nullptr;
         size_t out_length = 0;

         int iError = unac_string("UTF8", strTry.begin(), strTry.size(), &out, &out_length);

         if (iError != 0)
         {


            throw ::exception(error_wrong_state, "unac_string returned error");
            //throw_errno_exception();

         }

         strTry.assign(out, out_length);

         ::free(out);

      }

      if (bPrefix)
      {

         iFind = m_straCityLo.find_first_begins(strTry);

      }
      else
      {

         iFind = m_straCityLo.find_first(strTry);

      }

      if (::found(iFind))
      {

         goto found;

      }









      return -1;

   found:

      strCit = m_straCity[iFind];

      iId = m_iaIds[iFind];

      dLat = m_daLat[iFind];

      dLon = m_daLon[iFind];

      return iFind;

   }


   bool geo::locality_sunset(openweather_city* pcity, int& iRise, int& iSet)
   {

      if (pcity == nullptr)
      {

         return false;

      }

      const char * pszId =
#include "sensitive/openweather.txt"
         ;

      double dZone = 0.0;

      initial_locality_time_zone(pcity, dZone);

      int iTimeZone = (int)(dZone * 3600.0);

      property_set set;

      string strUrl = "http://api.openweathermap.org/data/2.5/weather?atom=" + ::as_string(pcity->m_iId) + "&APPID=" + string(pszId);

      auto psystem = system()->m_paxissystem;

      string strGetUrl = "https://ca2.software/api/account/openweather?request=" + ::url::encode(strUrl);

      auto pcontext = get_context();

      string str = pcontext->m_papexcontext->http().get(strGetUrl, set);

      synchronous_lock synchronouslock(this->synchronization());

      const ::ansi_character * pszJson = str;

      ::payload v;

      v.parse_network_payload(pszJson);

      ::earth::zone_time timeSunrise({ posix_time_t{}, v["sys"]["sunrise"].as_i64() }, iTimeZone);

      ::earth::zone_time timeSunset({ posix_time_t{}, v["sys"]["sunset"].as_i64() }, iTimeZone);

      iRise = (int)timeSunrise.GetZoneTimeOfDay().m_iSecond;

      iSet = (int)timeSunset.GetZoneTimeOfDay().m_iSecond;

      string strSunrise(timeSunrise.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      string strSunset(timeSunset.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      informationf("sunrise:" + strSunrise + "\n");

      informationf("sunset:" + strSunset + "\n");

      return true;

   }


   bool  geo::locality_sunset(string strCountry, string strLocality, int& iRise, int& iSet)
   {

      auto psystem = system()->m_paxissystem;

      auto pcity = psystem->geo().openweather_find_city(strLocality + ", " + strCountry);

      if (pcity == nullptr)
      {

         return false;

      }

      return locality_sunset(pcity, iRise, iSet);


   }


   string geo::initial_locality_time_zone(openweather_city* pcity, double& dZone)
   {

      ::datetime::time_zone timezone;

      timezone = get_time_zone(pcity);

      dZone = timezone.m_dZone;

      return timezone.m_strZone;

   }


   string  geo::initial_locality_time_zone(string strCountry, string strLocality, double& dZone)
   {

      string str;

      if (strLocality.is_empty())
      {

         str = initial_country_time_zone(strCountry);

         dZone = time_zone(str, strCountry);

         return str;

      }

      string strQ;

      strQ = strLocality;

      if (strCountry.has_char())
      {

         strQ += ", ";

         strQ += strCountry;

      }


      //  i64 iId;

//      double dLat;

      //    double dLon;

      auto psystem = system()->m_paxissystem;

      auto pcity = psystem->geo().openweather_find_city(strQ);

      return initial_locality_time_zone(pcity, dZone);

      //      if (pcity != nullptr)
      //      {
      //
      //
      //
      //         property_set set;
      //
      //         string strLat = as_string(pcity->m_dLat);
      //
      //         string strLng = as_string(pcity->m_dLon);
      //
      //         string strKey;
      //
      //#ifdef WINDOWS
      //
      //         strKey = acmefile()->as_string("C:\\sensitive\\sensitive\\seed\\timezonedb.txt");
      //
      //#else
      //
      //         strKey = acmefile()->as_string("/sensitive/sensitive/seed/timezonedb.txt");
      //
      //#endif
      //
      //         str = papp->http_get("http://api.timezonedb.com/?key=" + strKey + "&format=network_payload&lat=" + strLat + "&lng=" + strLng, set);
      //
      //         if (str.has_char())
      //         {
      //
      //            const ::ansi_character * pszJson = str;
      //
      //            ::payload v;
      //
      //            try
      //            {
      //
      //               v.parse_network_payload(pszJson);
      //
      //               str = v["abbreviation"].get_string().lowered();
      //
      //               dZone = v["gmtoffset"].get_double() / 3600.0;
      //
      //            }
      //            catch (...)
      //            {
      //
      //               str = "utc";
      //
      //               dZone = 0.0;
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            str = "utc";
      //
      //            dZone = 0.0;
      //
      //         }
      //
      //      }
      //      else
      //      {
      //
      //         str = "utc";
      //
      //         dZone = 0.0;
      //
      //      }
      //
      //
      //      timezone.m_strZone = str;
      //
      //      timezone.m_dZone = dZone;
      //
      //      timezone.m_time = now;
      //
      //      {
      //
      //         synchronous_lock synchronouslock(&m);
      //
      //         m_countryLocalityTimeZone[strCountry][strLocality] = timezone;
      //
      //         ::file::path path = acmedirectory()->public_system() / "datetime_departament_m_countryLocalityTimeZone.bin";
      //
      //         auto & file = pcontext->m_papexcontext->file()->friendly_get_file(path, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_defer_create_directory);
      //
      //         stream os(file);
      //
      //         ::file::map::write(os, m_countryLocalityTimeZone);
      //
      //      }
      //
      //      return str;

   }

   // remark: initial does mean "official default" is certainly a rough guess
   string  geo::initial_country_time_zone(string strCountry)
   {




      if (strCountry == "br")
      {

         return "brt";

      }
      else if (strCountry == "ua")
      {

         return "eest";

      }
      else if (strCountry == "us")
      {

         return "pdt";

      }
      else if (strCountry == "jp")
      {

         return "jst";

      }
      else if (strCountry == "de")
      {

         return "cest";

      }
      else if (strCountry == "fr")
      {

         return "cest";

      }
      else if (strCountry == "point_i32")
      {

         return "west";

      }
      else if (strCountry == "es")
      {

         return "cest";

      }
      else if (strCountry == "it")
      {

         return "cest";

      }
      else if (strCountry == "ar")
      {

         return "art";

      }
      else if (strCountry == "cl")
      {

         return "clst";

      }
      else if (strCountry == "uk")
      {

         return "bst";

      }
      else if (strCountry == "nl")
      {

         return "cest";

      }
      else if (strCountry == "cn")
      {

         return "cst";

      }
      else if (strCountry == "tw")
      {

         return "cst";

      }
      else if (strCountry == "ru")
      {

         return "msk";

      }
      else if (strCountry == "pl")
      {

         return "cest";

      }
      else if (strCountry == "am")
      {

         return "amt";

      }
      else if (strCountry == "dk")
      {

         return "cest";

      }
      else if (strCountry == "se")
      {

         return "cest";

      }
      else if (strCountry == "fi")
      {

         return "eest";

      }
      else if (strCountry == "ua")
      {

         return "eest";

      }
      else if (strCountry == "no")
      {

         return "cest";

      }
      else if (strCountry == "no")
      {

         return "cest";

      }
      else if (strCountry == "be")
      {

         return "cest";

      }
      else if (strCountry == "at")
      {

         return "cest";

      }
      else if (strCountry == "lu")
      {

         return "cest";

      }
      else if (strCountry == "li")
      {

         return "cest";

      }
      else if (strCountry == "ch")
      {

         return "cest";

      }
      else if (strCountry == "au")
      {

         return "aest";

      }
      else if (strCountry == "nz")
      {

         return "nzst";

      }
      else if (strCountry == "kr")
      {

         return "kst";

      }
      else if (strCountry == "ph")
      {

         return "pht";

      }
      else if (strCountry == "my")
      {

         return "myt";

      }
      else if (strCountry == "hk")
      {

         return "hkt";

      }
      else if (strCountry == "vn")
      {

         return "ict";

      }
      else if (strCountry == "in")
      {

         return "ist";

      }
      else if (strCountry == "ca")
      {

         return "adt";

      }
      else if (strCountry == "bg")
      {

         return "eet";

      }
      else
      {

         return "utc";

      }

   }



   string geo::utc_offset_string(double dUTCOffset)
   {

      if (dUTCOffset == 1000000.0)
      {

         return "";

      }
      else if (dUTCOffset == 0.0)
      {

         return "UTC";

      }
      else if (utc_offset_invalid(dUTCOffset))
      {

         return "(" + ::str::signed_double(dUTCOffset) + " : invalid UTC?)";

      }
      else
      {

         string strUTCOffset;

         strUTCOffset = "UTC " + ::str::signed_int((int)dUTCOffset);

         double dMod = fmod(fabs(dUTCOffset), 1.0);

         if (dMod > 0.0)
         {

            string strMinutes;

            strMinutes.formatf("%02d", (int)(60.0 * dMod));

            strUTCOffset += ":" + strMinutes;

         }

         return strUTCOffset;

      }

   }


   double geo::time_zone(string str, string strCountryCode)
   {
      str.make_lower();
      strCountryCode.make_lower();
      double dTimeZoneOffset = 0.0;
      //"Moscow Time"(TranslateFromRussian) (UTC+3)
      if (str == "msk")
      {

         dTimeZoneOffset = 3.0;

      }
      else if (str == "brt")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "cet")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "cest")
      {

         dTimeZoneOffset = 2.0;

      }
      else if (str == "eet")
      {

         dTimeZoneOffset = 2.0;

      }
      else if (str == "eest")
      {

         dTimeZoneOffset = 3.0;

      }
      else if (str == "pdt")
      {

         dTimeZoneOffset = -7.0;

      }
      else if (str == "est")
      {

         dTimeZoneOffset = -5.0;

      }
      else if (str == "edt")
      {

         dTimeZoneOffset = -4.0;

      }
      else if (str == "mst")
      {

         dTimeZoneOffset = -7.0;

      }
      else if (str == "mdt")
      {

         dTimeZoneOffset = -6.0;

      }
      else if (str == "jst")
      {

         dTimeZoneOffset = 9.0;

      }
      else if (str == "west")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "art")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "clst")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "bst")
      {

         dTimeZoneOffset = 1.0;

      }
      else if (str == "cdt")
      {

         dTimeZoneOffset = -5.0;

      }
      else if (str == "cst")
      {

         if (strCountryCode == "cn")
         {

            dTimeZoneOffset = 8.0;

         }
         else
         {

            dTimeZoneOffset = -6.0;

         }

      }
      else if (str == "amt")
      {

         dTimeZoneOffset = 4.0;

      }
      else if (str == "aest")
      {

         dTimeZoneOffset = 10.0;

      }
      else if (str == "nzst")
      {

         dTimeZoneOffset = 12.0;

      }
      else if (str == "kst")
      {

         dTimeZoneOffset = 9.0;

      }
      else if (str == "pht")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "myt")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "hkt")
      {

         dTimeZoneOffset = 8.0;

      }
      else if (str == "ict")
      {

         dTimeZoneOffset = 7.0;

      }
      else if (str == "utc")
      {

         dTimeZoneOffset = 0.0;

      }
      else if (str == "alphatime")
      {

         dTimeZoneOffset = -2.0;

      }
      else if (str == "ist")
      {

         dTimeZoneOffset = 5.5;

      }
      else if (str == "adt")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (str == "brst")
      {

         dTimeZoneOffset = -2.0;

      }
      else if (::mathematics::convert_to_double(dTimeZoneOffset, str))
      {

      }
      else if (strCountryCode == "br")
      {

         dTimeZoneOffset = -3.0;

      }
      else if (!::mathematics::convert_to_double(dTimeZoneOffset, strCountryCode))
      {

         informationf("(2) ERROR !! Missing timezone offset information for \"%s\" - \"%s\"", str.c_str(), strCountryCode.c_str());

      }

      return dTimeZoneOffset;

   }

  

   bool utc_offset_invalid(double dUTCOffset)
   {

      return dUTCOffset < -12.0 || dUTCOffset > 14.0;  // don't know (is invalid?)

   }


   ::datetime::time_zone geo::get_time_zone(openweather_city* pcity)
   {

      if (::is_null(pcity))
      {

         return {};

      }

      auto iOpenweatherCity = pcity->m_iId;

      if (iOpenweatherCity < 0)
      {

         return {};

      }

      if (!m_bLoadedCityTimeZoneFromFile)
      {

         m_bLoadedCityTimeZoneFromFile = true;

         ::file::path path = m_pathCityTimeZoneFile;

         try
         {

            auto pfile = file()->get_reader(path);

            if (pfile.ok())
            {

               binary_stream reader(pfile);

               synchronous_lock synchronouslock(m_pmutexCityTimeZone);

               reader >> m_cityTimeZone;

            }

         }
         catch (...)
         {

         }

      }

      try
      {

         synchronous_lock synchronouslock(m_pmutexCityTimeZone);

         auto& timezone = m_cityTimeZone[iOpenweatherCity];

         if (timezone.is_valid(1_day))
         {

            return timezone;

         }

         synchronouslock.unlock();

         timezone = _get_time_zone(pcity);

         if (timezone.m_strZone.has_char())
         {

            set_locality_time_zone_modified();

         }

         return timezone;

      }
      catch (...)
      {

      }

      return {};

   }


   ::datetime::time_zone geo::_get_time_zone(openweather_city* pcity)
   {

      return get_time_zone(pcity->m_dLat, pcity->m_dLon);

   }


   ::datetime::time_zone geo::get_time_zone(double dLat, double dLng)
   {

      if (!m_bLoadedLocalityTimeZoneFromFile)
      {

         m_bLoadedLocalityTimeZoneFromFile = true;

         ::file::path path = m_pathLocalityTimeZoneFile;

         try
         {

            auto pfile = file()->get_reader(path);

            if (pfile.ok())
            {

               binary_stream reader(pfile);

               synchronous_lock synchronouslock(m_pmutexLocalityTimeZone);

               reader >> m_localityTimeZone;

            }

         }
         catch (...)
         {

         }

      }

      dLat = ceil(dLat * 100.0) / 100.0;

      dLng = ceil(dLng * 100.0) / 100.0;

      try
      {

         synchronous_lock synchronouslock(m_pmutexCityTimeZone);

         auto& timezone = m_localityTimeZone[dLat][dLng];

         if (timezone.is_valid(1_day))
         {

            return timezone;

         }

         synchronouslock.unlock();

         timezone = _get_time_zone(dLat, dLng);

         if (timezone.m_strZone.has_char())
         {

            set_locality_time_zone_modified();

         }

         timezone.m_time.Now();

         return timezone;

      }
      catch (...)
      {

      }

      return {};

   }


   ::datetime::time_zone geo::_get_time_zone(double dLat, double dLng)
   {

      ::datetime::time_zone timezone;

      property_set set;

      string strLat;
         
      strLat.formatf("%0.2f", dLat);

      string strLng;

      strLng.formatf("%0.2f", dLng);

      string strUrl = "https://camilothomas.com/account/time_zone";

      try
      {

         property_set set;

         set["post"]["lat"] = strLat;

         set["post"]["lng"] = strLng;

         //auto estatus = 
         
         auto payload = api_get(strUrl, set);

         //if (!estatus)
         //{

         //   return timezone;

         //}

         timezone.m_strZone = payload["zone_name"];

         timezone.m_dZone = payload["zone_offset"].as_f64();

      }
      catch (...)
      {

      }

      return timezone;

   }


   ::payload geo::get_weather(openweather_city* pcity)
   {

      if (!m_bLoadedCityWeatherFromFile)
      {

         m_bLoadedCityWeatherFromFile = true;

         ::file::path path = m_pathCityWeatherFile;

         try
         {

            auto file = ::particle::file()->get_reader(path);

            binary_stream reader(file);

            synchronous_lock synchronouslock(m_pmutexCityWeather);

            reader >> m_cityWeather;

         }
         catch (...)
         {

         }

      }

      if (::is_null(pcity))
      {

         return "";

      }

      if (pcity->m_iId < 0)
      {

         return "";

      }

      try
      {

         synchronous_lock synchronouslock(m_pmutexCityTimeZone);

         auto& stringtimeout = m_cityWeather[pcity->m_iId];

         if (stringtimeout.is_valid(1_min))
         {

            return stringtimeout.m_str;

         }

         synchronouslock.unlock();

         stringtimeout.m_str = _get_weather(pcity);

         if (stringtimeout.m_str.has_char())
         {

            set_locality_time_zone_modified();

         }

         stringtimeout.m_time.Now();

         return stringtimeout.m_str;

      }
      catch (...)
      {

      }

      return {};

   }


   ::payload geo::_get_weather(openweather_city * pcity)
   {

      property_set set;

      string strId = ::as_string(pcity->m_iId);

      string strUrl = "http://ca2.software/account/weather";

      try
      {

         //string strNetworkPayload;

         property_set set;

         set["city_id"] = strId;

         //auto estatus = 
         
         auto payload = api_get(strUrl, set);

  /*       if (!estatus)
         {

            return strNetworkPayload;

         }*/

         return payload;

      }
      catch (...)
      {

      }

      return "";

   }


   void geo::set_city_time_zone_modified()
   {

      m_bCityTimeZoneModified = true;

      if (!m_ptaskSaveCityTimeZone)
      {

         m_ptaskSaveCityTimeZone = fork([this]()
            {

               try
               {

                  while (m_ptaskSaveCityTimeZone->task_get_run())
                  {

                     preempt(1_s);

                     if (m_bCityTimeZoneModified)
                     {

                        try
                        {

                           save_city_time_zone();

                           m_bCityTimeZoneModified = false;

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }
               catch (...)
               {

               }

               m_ptaskSaveCityTimeZone.release();

            });

      }

   }


   void geo::set_locality_time_zone_modified()
   {

      m_bLocalityTimeZoneModified = true;

      if (!m_ptaskSaveLocalityTimeZone)
      {

         m_ptaskSaveLocalityTimeZone = fork([this]()
            {

               try
               {

                  while(!m_ptaskSaveLocalityTimeZone)
                  {

                     preempt(1_s);

                  }

                  while (m_ptaskSaveLocalityTimeZone->task_get_run())
                  {

                     preempt(1_s);

                     if (m_bLocalityTimeZoneModified)
                     {

                        try
                        {

                           save_locality_time_zone();

                           m_bLocalityTimeZoneModified = false;

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }
               catch (...)
               {

               }

               m_ptaskSaveLocalityTimeZone.release();

            });

      }

   }


   void geo::set_city_weather_modified()
   {

      m_bCityWeatherModified = true;

      if (!m_ptaskSaveCityWeather)
      {

         m_ptaskSaveCityWeather = fork([this]()
            {

               try
               {

                  while (m_ptaskSaveCityWeather->task_get_run())
                  {

                     preempt(1_s);

                     if (m_bCityWeatherModified)
                     {

                        try
                        {

                           save_city_weather();

                           m_bCityWeatherModified = false;

                        }
                        catch (...)
                        {

                        }

                     }

                  }

               }
               catch (...)
               {

               }

               m_ptaskSaveCityWeather.release();

            });

      }

   }


   void geo::save_city_time_zone()
   {
      
      ::file::path path = m_pathLocalityTimeZoneFile;

      try
      {

         auto pfile = file()->get_writer(path);

         if (pfile)
         {

            binary_stream writer(pfile);

            synchronous_lock synchronouslock(m_pmutexCityTimeZone);

            writer << m_cityTimeZone;

         }

      }
      catch (...)
      {

      }

   }


   void geo::save_locality_time_zone()
   {

      ::file::path path = m_pathLocalityTimeZoneFile;

      try
      {

         auto pfile = file()->get_writer(path);

         if (pfile)
         {

            binary_stream writer(pfile);

            synchronous_lock synchronouslock(m_pmutexLocalityTimeZone);

            writer << m_localityTimeZone;

         }

      }
      catch (...)
      {

      }

   }


   void geo::save_city_weather()
   {

      ::file::path path = m_pathCityWeatherFile;

      try
      {

         auto pfile = file()->get_writer(path);

         binary_stream writer(pfile);

         synchronous_lock synchronouslock(m_pmutexCityWeather);

         writer << m_cityWeather;

      }
      catch (...)
      {

      }

   }


} // namespace geo



