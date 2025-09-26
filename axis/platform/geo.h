// Added get_time_zone memberby camilo on 2021-12-02 14:23 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/collection/string_map.h"
#include "apex/platform/api.h"
#include "apex/platform/api_client.h"
#include "acme/prototype/datetime/time_zone.h"
#include "acme/platform/department.h"


class CLASS_DECL_AXIS string_timeout
{
public:


   string               m_str;
   ::earth::time     m_time; /// time when this network_payload was last updated


   bool is_valid(const class ::time& timeTimeOut) const
   {

      return m_time.elapsed() < timeTimeOut;

   }


};


namespace geo
{


   class CLASS_DECL_AXIS geo :
      virtual public ::acme::department,
      virtual public ::api_client
   {
   public:


      bool                                                  m_bOpenWeatherCityListLock;

      //bool                                                            m_bInitialCountryTimeZoneInit;
      bool                                                  m_bInitialLocalityTimeZoneInit;

      ::pointer < ::mutex >                                               m_pmutexOpenweatherCity;

      ::pointer < ::mutex >                                               m_pmutexCityTimeZone;
      index_map_base < ::datetime::time_zone >                   m_cityTimeZone;
      bool                                                  m_bLoadedCityTimeZoneFromFile;
      ::file::path                                          m_pathCityTimeZoneFile;
      task_pointer                                          m_ptaskSaveCityTimeZone;
      bool                                                  m_bCityTimeZoneModified;



      ::pointer < ::mutex >                                               m_pmutexLocalityTimeZone;
      double_map < double_map < ::datetime::time_zone > >   m_localityTimeZone;
      bool                                                  m_bLoadedLocalityTimeZoneFromFile;
      ::file::path                                          m_pathLocalityTimeZoneFile;
      task_pointer                                          m_ptaskSaveLocalityTimeZone;
      bool                                                  m_bLocalityTimeZoneModified;


      ::pointer < ::mutex >                                               m_pmutexCityWeather;
      index_map_base < string_timeout >                          m_cityWeather;
      bool                                                  m_bLoadedCityWeatherFromFile;
      ::file::path                                          m_pathCityWeatherFile;
      task_pointer                                          m_ptaskSaveCityWeather;
      bool                                                  m_bCityWeatherModified;


      //string_map_base < time_zone >      m_countryTimeZone;

      string_array_base                                       m_straCityLo;
      string_array_base                                       m_straCity;
      long_long_array_base                                          m_iaIds;
      double_array                                       m_daLon;
      double_array                                       m_daLat;

      string_map_base < openweather_city* >                  m_mapCity;


      geo();
      ~geo() override;


      void initialize(::particle* pparticle) override;


      virtual void defer_check_openweather_city_list();

      ::pointer< ::mutex > get_openweather_city_mutex() { return m_pmutexOpenweatherCity; }

      virtual openweather_city* openweather_find_city(const ::scoped_string & scopedstrQuery);
      virtual ::collection::index openweather_find_city2(const ::scoped_string & scopedstrQuery, string& strCit, long long& iId, double& dLat, double& dLon);
      virtual ::collection::index openweather_find_city2(const ::scoped_string & scopedstrQ1, const ::scoped_string & scopedstrQ2, string& strCit, long long& iId, double& dLat, double& dLon, bool bPrefix);



      virtual bool locality_sunset(openweather_city* pcity, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(openweather_city* pcity, double& dZone);
      virtual bool locality_sunset(const ::scoped_string & scopedstrCountry, const ::scoped_string & scopedstrLocality, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(const ::scoped_string & scopedstrCountry, const ::scoped_string & scopedstrLocality, double& dZone);
      virtual string initial_country_time_zone(const ::scoped_string & scopedstrCountry);
      virtual string utc_offset_string(double dUTCOffset);
      virtual double time_zone(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrCountryCode);


      virtual ::datetime::time_zone get_time_zone(openweather_city* pcity);

      virtual ::datetime::time_zone _get_time_zone(openweather_city* pcity);

      virtual ::datetime::time_zone get_time_zone(double dLat, double dLng);

      virtual ::datetime::time_zone _get_time_zone(double dLat, double dLng);

      virtual ::payload get_weather(openweather_city* pcity);

      virtual ::payload _get_weather(openweather_city* pcity);

      virtual void set_city_time_zone_modified();

      virtual void set_locality_time_zone_modified();

      virtual void set_city_weather_modified();

      virtual void save_city_time_zone();

      virtual void save_locality_time_zone();

      virtual void save_city_weather();

   };


   CLASS_DECL_AXIS bool utc_offset_invalid(double dUTCOffset);


} // namespace geo




