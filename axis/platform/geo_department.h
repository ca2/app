#pragma once


namespace geo
{


   class CLASS_DECL_AXIS department :
      virtual public ::acme::department
   {
   public:



      //bool                                          m_bInitialCountryTimeZoneInit;
      bool                                            m_bInitialLocalityTimeZoneInit;

      ::mutex                                         m_mutexOpenweatherCity;
      iptr_map < ::datetime::department::time_zone >  m_cityTimeZone;
      //string_map < time_zone >      m_countryTimeZone;

      string_array                                       m_straCityLo;
      string_array                                       m_straCity;
      i64_array                                          m_iaIds;
      double_array                                       m_daLon;
      double_array                                       m_daLat;

      string_map < __pointer(openweather_city) >         m_mapCity;


      department();
      virtual ~department();

      virtual void defer_check_openweather_city_list();

      ::mutex * get_openweather_city_mutex() { return &m_mutexOpenweatherCity; }

      virtual openweather_city* openweather_find_city(string strQuery);
      virtual index openweather_find_city2(string strQuery, string& strCit, i64& iId, double& dLat, double& dLon);
      virtual index openweather_find_city2(string strQ1, string strQ2, string& strCit, i64& iId, double& dLat, double& dLon, bool bPrefix);



      virtual bool locality_sunset(openweather_city* pcity, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(openweather_city* pcity, double& dZone);
      virtual bool locality_sunset(string strCountry, string strLocality, int& iRise, int& iSet);
      virtual string initial_locality_time_zone(string strCountry, string strLocality, double& dZone);
      virtual string initial_country_time_zone(string strCountry);
      virtual string utc_offset_string(double dUTCOffset);
      virtual double time_zone(string str, string strCountryCode);


   };


   CLASS_DECL_AXIS bool utc_offset_invalid(double dUTCOffset);


} // namespace geo




