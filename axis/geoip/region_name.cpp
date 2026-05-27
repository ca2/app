#include "framework.h"
#include "geoip.h"
#include <string.h>


const_char_pointer GeoIP_region_name_by_code(const_char_pointer country_code,const_char_pointer region_code) {
  const_char_pointer pszName = nullptr;
  ::i32 region_code2 = -1;
  if (region_code == nullptr) { return nullptr; }

  if (   ((region_code[0] >= 48) && (region_code[0] < (48 + 10)))
      && ((region_code[1] >= 48) && (region_code[1] < (48 + 10)))
  ) {

    /* only numbers, that shorten the large switch statements */
    region_code2 = (region_code[0] - 48) * 10 + region_code[1] - 48;
  }

  else if (    (    ((region_code[0] >= 65) && (region_code[0] < (65 + 26)))
                 || ((region_code[0] >= 48) && (region_code[0] < (48 + 10))))
            && (    ((region_code[1] >= 65) && (region_code[1] < (65 + 26)))
                 || ((region_code[1] >= 48) && (region_code[1] < (48 + 10))))
  ) {

    region_code2 = (region_code[0] - 48) * (65 + 26 - 48) + region_code[1] - 48 + 100;
  }

  if (region_code2 == -1) {return nullptr;}

  if (strcmp(country_code,"CA") == 0) {
    switch (region_code2) {
      case 849:
      pszName = "Alberta";
      break;
      case 893:
      pszName = "British Columbia";
      break;
      case 1365:
      pszName = "Manitoba";
      break;
      case 1408:
      pszName = "New Brunswick";
      break;
      case 1418:
      pszName = "Newfoundland";
      break;
      case 1425:
      pszName = "Nova Scotia";
      break;
      case 1427:
      pszName = "Nunavut";
      break;
      case 1463:
      pszName = "Ontario";
      break;
      case 1497:
      pszName = "Prince Edward Island";
      break;
      case 1538:
      pszName = "Quebec";
      break;
      case 1632:
      pszName = "Saskatchewan";
      break;
      case 1426:
      pszName = "Northwest Territories";
      break;
      case 1899:
      pszName = "Yukon Territory";
      break;
    }
  }
  if (strcmp(country_code,"US") == 0) {
    switch (region_code2) {
      case 848:
      pszName = "Armed Forces Americas";
      break;
      case 852:
      pszName = "Armed Forces Europe, Middle East, & Canada";
      break;
      case 858:
      pszName = "Alaska";
      break;
      case 859:
      pszName = "Alabama";
      break;
      case 863:
      pszName = "Armed Forces Pacific";
      break;
      case 865:
      pszName = "Arkansas";
      break;
      case 866:
      pszName = "American Samoa";
      break;
      case 873:
      pszName = "Arizona";
      break;
      case 934:
      pszName = "California";
      break;
      case 948:
      pszName = "Colorado";
      break;
      case 953:
      pszName = "Connecticut";
      break;
      case 979:
      pszName = "District of Columbia";
      break;
      case 981:
      pszName = "Delaware";
      break;
      case 1074:
      pszName = "Florida";
      break;
      case 1075:
      pszName = "Federated States of Micronesia";
      break;
      case 1106:
      pszName = "Georgia";
      break;
      case 1126:
      pszName = "Guam";
      break;
      case 1157:
      pszName = "Hawaii";
      break;
      case 1192:
      pszName = "Iowa";
      break;
      case 1195:
      pszName = "Idaho";
      break;
      case 1203:
      pszName = "Illinois";
      break;
      case 1205:
      pszName = "Indiana";
      break;
      case 1296:
      pszName = "Kansas";
      break;
      case 1302:
      pszName = "Kentucky";
      break;
      case 1321:
      pszName = "Louisiana";
      break;
      case 1364:
      pszName = "Massachusetts";
      break;
      case 1367:
      pszName = "Maryland";
      break;
      case 1368:
      pszName = "Maine";
      break;
      case 1371:
      pszName = "Marshall Islands";
      break;
      case 1372:
      pszName = "Michigan";
      break;
      case 1377:
      pszName = "Minnesota";
      break;
      case 1378:
      pszName = "Missouri";
      break;
      case 1379:
      pszName = "Northern Mariana Islands";
      break;
      case 1382:
      pszName = "Mississippi";
      break;
      case 1383:
      pszName = "Montana";
      break;
      case 1409:
      pszName = "North Carolina";
      break;
      case 1410:
      pszName = "North Dakota";
      break;
      case 1411:
      pszName = "Nebraska";
      break;
      case 1414:
      pszName = "New Hampshire";
      break;
      case 1416:
      pszName = "New Jersey";
      break;
      case 1419:
      pszName = "New Mexico";
      break;
      case 1428:
      pszName = "Nevada";
      break;
      case 1431:
      pszName = "New York";
      break;
      case 1457:
      pszName = "Ohio";
      break;
      case 1460:
      pszName = "Oklahoma";
      break;
      case 1467:
      pszName = "Oregon";
      break;
      case 1493:
      pszName = "Pennsylvania";
      break;
      case 1510:
      pszName = "Puerto Rico";
      break;
      case 1515:
      pszName = "Palau";
      break;
      case 1587:
      pszName = "Rhode Island";
      break;
      case 1624:
      pszName = "South Carolina";
      break;
      case 1625:
      pszName = "South Dakota";
      break;
      case 1678:
      pszName = "Tennessee";
      break;
      case 1688:
      pszName = "Texas";
      break;
      case 1727:
      pszName = "Utah";
      break;
      case 1751:
      pszName = "Virginia";
      break;
      case 1759:
      pszName = "Virgin Islands";
      break;
      case 1770:
      pszName = "Vermont";
      break;
      case 1794:
      pszName = "Washington";
      break;
      case 1815:
      pszName = "West Virginia";
      break;
      case 1802:
      pszName = "Wisconsin";
      break;
      case 1818:
      pszName = "Wyoming";
      break;
    }
  }
  if (strcmp(country_code,"AD") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Canillo";
      break;
      case 3:
      pszName = "Encamp";
      break;
      case 4:
      pszName = "La Massana";
      break;
      case 5:
      pszName = "Ordino";
      break;
      case 6:
      pszName = "Sant Julia de Loria";
      break;
      case 7:
      pszName = "Andorra la Vella";
      break;
      case 8:
      pszName = "Escaldes-Engordany";
      break;
    }
  }
  if (strcmp(country_code,"AE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Abu Dhabi";
      break;
      case 2:
      pszName = "Ajman";
      break;
      case 3:
      pszName = "Dubai";
      break;
      case 4:
      pszName = "Fujairah";
      break;
      case 5:
      pszName = "Ras Al Khaimah";
      break;
      case 6:
      pszName = "Sharjah";
      break;
      case 7:
      pszName = "Umm Al Quwain";
      break;
    }
  }
  if (strcmp(country_code,"AF") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Badakhshan";
      break;
      case 2:
      pszName = "Badghis";
      break;
      case 3:
      pszName = "Baghlan";
      break;
      case 5:
      pszName = "Bamian";
      break;
      case 6:
      pszName = "Farah";
      break;
      case 7:
      pszName = "Faryab";
      break;
      case 8:
      pszName = "Ghazni";
      break;
      case 9:
      pszName = "Ghowr";
      break;
      case 10:
      pszName = "Helmand";
      break;
      case 11:
      pszName = "Herat";
      break;
      case 13:
      pszName = "Kabol";
      break;
      case 14:
      pszName = "Kapisa";
      break;
      case 15:
      pszName = "Konar";
      break;
      case 16:
      pszName = "Laghman";
      break;
      case 17:
      pszName = "Lowgar";
      break;
      case 18:
      pszName = "Nangarhar";
      break;
      case 19:
      pszName = "Nimruz";
      break;
      case 21:
      pszName = "Paktia";
      break;
      case 22:
      pszName = "Parvan";
      break;
      case 23:
      pszName = "Kandahar";
      break;
      case 24:
      pszName = "Kondoz";
      break;
      case 26:
      pszName = "Takhar";
      break;
      case 27:
      pszName = "Vardak";
      break;
      case 28:
      pszName = "Zabol";
      break;
      case 29:
      pszName = "Paktika";
      break;
      case 30:
      pszName = "Balkh";
      break;
      case 31:
      pszName = "Jowzjan";
      break;
      case 32:
      pszName = "Samangan";
      break;
      case 33:
      pszName = "Sar-e Pol";
      break;
      case 34:
      pszName = "Konar";
      break;
      case 35:
      pszName = "Laghman";
      break;
      case 36:
      pszName = "Paktia";
      break;
      case 37:
      pszName = "Khowst";
      break;
      case 38:
      pszName = "Nurestan";
      break;
      case 39:
      pszName = "Oruzgan";
      break;
      case 40:
      pszName = "Parvan";
      break;
      case 41:
      pszName = "Daykondi";
      break;
      case 42:
      pszName = "Panjshir";
      break;
    }
  }
  if (strcmp(country_code,"AG") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Barbuda";
      break;
      case 3:
      pszName = "Saint George";
      break;
      case 4:
      pszName = "Saint John";
      break;
      case 5:
      pszName = "Saint Mary";
      break;
      case 6:
      pszName = "Saint Paul";
      break;
      case 7:
      pszName = "Saint Peter";
      break;
      case 8:
      pszName = "Saint Philip";
      break;
    }
  }
  if (strcmp(country_code,"AL") == 0) {
    switch (region_code2) {
      case 40:
      pszName = "Berat";
      break;
      case 41:
      pszName = "Diber";
      break;
      case 42:
      pszName = "Durres";
      break;
      case 43:
      pszName = "Elbasan";
      break;
      case 44:
      pszName = "Fier";
      break;
      case 45:
      pszName = "Gjirokaster";
      break;
      case 46:
      pszName = "Korce";
      break;
      case 47:
      pszName = "Kukes";
      break;
      case 48:
      pszName = "Lezhe";
      break;
      case 49:
      pszName = "Shkoder";
      break;
      case 50:
      pszName = "Tirane";
      break;
      case 51:
      pszName = "Vlore";
      break;
    }
  }
  if (strcmp(country_code,"AM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aragatsotn";
      break;
      case 2:
      pszName = "Ararat";
      break;
      case 3:
      pszName = "Armavir";
      break;
      case 4:
      pszName = "Geghark'unik'";
      break;
      case 5:
      pszName = "Kotayk'";
      break;
      case 6:
      pszName = "Lorri";
      break;
      case 7:
      pszName = "Shirak";
      break;
      case 8:
      pszName = "Syunik'";
      break;
      case 9:
      pszName = "Tavush";
      break;
      case 10:
      pszName = "Vayots' Dzor";
      break;
      case 11:
      pszName = "Yerevan";
      break;
    }
  }
  if (strcmp(country_code,"AO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Benguela";
      break;
      case 2:
      pszName = "Bie";
      break;
      case 3:
      pszName = "Cabinda";
      break;
      case 4:
      pszName = "Cuando Cubango";
      break;
      case 5:
      pszName = "Cuanza Norte";
      break;
      case 6:
      pszName = "Cuanza Sul";
      break;
      case 7:
      pszName = "Cunene";
      break;
      case 8:
      pszName = "Huambo";
      break;
      case 9:
      pszName = "Huila";
      break;
      case 10:
      pszName = "Luanda";
      break;
      case 12:
      pszName = "Malanje";
      break;
      case 13:
      pszName = "Namibe";
      break;
      case 14:
      pszName = "Moxico";
      break;
      case 15:
      pszName = "Uige";
      break;
      case 16:
      pszName = "Zaire";
      break;
      case 17:
      pszName = "Lunda Norte";
      break;
      case 18:
      pszName = "Lunda Sul";
      break;
      case 19:
      pszName = "Bengo";
      break;
      case 20:
      pszName = "Luanda";
      break;
    }
  }
  if (strcmp(country_code,"AR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Buenos Aires";
      break;
      case 2:
      pszName = "Catamarca";
      break;
      case 3:
      pszName = "Chaco";
      break;
      case 4:
      pszName = "Chubut";
      break;
      case 5:
      pszName = "Cordoba";
      break;
      case 6:
      pszName = "Corrientes";
      break;
      case 7:
      pszName = "Distrito Federal";
      break;
      case 8:
      pszName = "Entre Rios";
      break;
      case 9:
      pszName = "Formosa";
      break;
      case 10:
      pszName = "Jujuy";
      break;
      case 11:
      pszName = "La Pampa";
      break;
      case 12:
      pszName = "La Rioja";
      break;
      case 13:
      pszName = "Mendoza";
      break;
      case 14:
      pszName = "Misiones";
      break;
      case 15:
      pszName = "Neuquen";
      break;
      case 16:
      pszName = "Rio Negro";
      break;
      case 17:
      pszName = "Salta";
      break;
      case 18:
      pszName = "San Juan";
      break;
      case 19:
      pszName = "San Luis";
      break;
      case 20:
      pszName = "Santa Cruz";
      break;
      case 21:
      pszName = "Santa Fe";
      break;
      case 22:
      pszName = "Santiago del Estero";
      break;
      case 23:
      pszName = "Tierra del Fuego";
      break;
      case 24:
      pszName = "Tucuman";
      break;
    }
  }
  if (strcmp(country_code,"AT") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Burgenland";
      break;
      case 2:
      pszName = "Karnten";
      break;
      case 3:
      pszName = "Niederosterreich";
      break;
      case 4:
      pszName = "Oberosterreich";
      break;
      case 5:
      pszName = "Salzburg";
      break;
      case 6:
      pszName = "Steiermark";
      break;
      case 7:
      pszName = "Tirol";
      break;
      case 8:
      pszName = "Vorarlberg";
      break;
      case 9:
      pszName = "Wien";
      break;
    }
  }
  if (strcmp(country_code,"AU") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Australian Capital Territory";
      break;
      case 2:
      pszName = "New South Wales";
      break;
      case 3:
      pszName = "Northern Territory";
      break;
      case 4:
      pszName = "Queensland";
      break;
      case 5:
      pszName = "South Australia";
      break;
      case 6:
      pszName = "Tasmania";
      break;
      case 7:
      pszName = "Victoria";
      break;
      case 8:
      pszName = "Western Australia";
      break;
    }
  }
  if (strcmp(country_code,"AZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Abseron";
      break;
      case 2:
      pszName = "Agcabadi";
      break;
      case 3:
      pszName = "Agdam";
      break;
      case 4:
      pszName = "Agdas";
      break;
      case 5:
      pszName = "Agstafa";
      break;
      case 6:
      pszName = "Agsu";
      break;
      case 7:
      pszName = "Ali Bayramli";
      break;
      case 8:
      pszName = "Astara";
      break;
      case 9:
      pszName = "Baki";
      break;
      case 10:
      pszName = "Balakan";
      break;
      case 11:
      pszName = "Barda";
      break;
      case 12:
      pszName = "Beylaqan";
      break;
      case 13:
      pszName = "Bilasuvar";
      break;
      case 14:
      pszName = "Cabrayil";
      break;
      case 15:
      pszName = "Calilabad";
      break;
      case 16:
      pszName = "Daskasan";
      break;
      case 17:
      pszName = "Davaci";
      break;
      case 18:
      pszName = "Fuzuli";
      break;
      case 19:
      pszName = "Gadabay";
      break;
      case 20:
      pszName = "Ganca";
      break;
      case 21:
      pszName = "Goranboy";
      break;
      case 22:
      pszName = "Goycay";
      break;
      case 23:
      pszName = "Haciqabul";
      break;
      case 24:
      pszName = "Imisli";
      break;
      case 25:
      pszName = "Ismayilli";
      break;
      case 26:
      pszName = "Kalbacar";
      break;
      case 27:
      pszName = "Kurdamir";
      break;
      case 28:
      pszName = "Lacin";
      break;
      case 29:
      pszName = "Lankaran";
      break;
      case 30:
      pszName = "Lankaran";
      break;
      case 31:
      pszName = "Lerik";
      break;
      case 32:
      pszName = "Masalli";
      break;
      case 33:
      pszName = "Mingacevir";
      break;
      case 34:
      pszName = "Naftalan";
      break;
      case 35:
      pszName = "Naxcivan";
      break;
      case 36:
      pszName = "Neftcala";
      break;
      case 37:
      pszName = "Oguz";
      break;
      case 38:
      pszName = "Qabala";
      break;
      case 39:
      pszName = "Qax";
      break;
      case 40:
      pszName = "Qazax";
      break;
      case 41:
      pszName = "Qobustan";
      break;
      case 42:
      pszName = "Quba";
      break;
      case 43:
      pszName = "Qubadli";
      break;
      case 44:
      pszName = "Qusar";
      break;
      case 45:
      pszName = "Saatli";
      break;
      case 46:
      pszName = "Sabirabad";
      break;
      case 47:
      pszName = "Saki";
      break;
      case 48:
      pszName = "Saki";
      break;
      case 49:
      pszName = "Salyan";
      break;
      case 50:
      pszName = "Samaxi";
      break;
      case 51:
      pszName = "Samkir";
      break;
      case 52:
      pszName = "Samux";
      break;
      case 53:
      pszName = "Siyazan";
      break;
      case 54:
      pszName = "Sumqayit";
      break;
      case 55:
      pszName = "Susa";
      break;
      case 56:
      pszName = "Susa";
      break;
      case 57:
      pszName = "Tartar";
      break;
      case 58:
      pszName = "Tovuz";
      break;
      case 59:
      pszName = "Ucar";
      break;
      case 60:
      pszName = "Xacmaz";
      break;
      case 61:
      pszName = "Xankandi";
      break;
      case 62:
      pszName = "Xanlar";
      break;
      case 63:
      pszName = "Xizi";
      break;
      case 64:
      pszName = "Xocali";
      break;
      case 65:
      pszName = "Xocavand";
      break;
      case 66:
      pszName = "Yardimli";
      break;
      case 67:
      pszName = "Yevlax";
      break;
      case 68:
      pszName = "Yevlax";
      break;
      case 69:
      pszName = "Zangilan";
      break;
      case 70:
      pszName = "Zaqatala";
      break;
      case 71:
      pszName = "Zardab";
      break;
    }
  }
  if (strcmp(country_code,"BA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Federation of Bosnia and Herzegovina";
      break;
      case 2:
      pszName = "Republika Srpska";
      break;
    }
  }
  if (strcmp(country_code,"BB") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Christ Church";
      break;
      case 2:
      pszName = "Saint Andrew";
      break;
      case 3:
      pszName = "Saint George";
      break;
      case 4:
      pszName = "Saint James";
      break;
      case 5:
      pszName = "Saint John";
      break;
      case 6:
      pszName = "Saint Joseph";
      break;
      case 7:
      pszName = "Saint Lucy";
      break;
      case 8:
      pszName = "Saint Michael";
      break;
      case 9:
      pszName = "Saint Peter";
      break;
      case 10:
      pszName = "Saint Philip";
      break;
      case 11:
      pszName = "Saint Thomas";
      break;
    }
  }
  if (strcmp(country_code,"BD") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Barisal";
      break;
      case 4:
      pszName = "Bandarban";
      break;
      case 5:
      pszName = "Comilla";
      break;
      case 12:
      pszName = "Mymensingh";
      break;
      case 13:
      pszName = "Noakhali";
      break;
      case 15:
      pszName = "Patuakhali";
      break;
      case 22:
      pszName = "Bagerhat";
      break;
      case 23:
      pszName = "Bhola";
      break;
      case 24:
      pszName = "Bogra";
      break;
      case 25:
      pszName = "Barguna";
      break;
      case 26:
      pszName = "Brahmanbaria";
      break;
      case 27:
      pszName = "Chandpur";
      break;
      case 28:
      pszName = "Chapai Nawabganj";
      break;
      case 29:
      pszName = "Chattagram";
      break;
      case 30:
      pszName = "Chuadanga";
      break;
      case 31:
      pszName = "Cox's Bazar";
      break;
      case 32:
      pszName = "Dhaka";
      break;
      case 33:
      pszName = "Dinajpur";
      break;
      case 34:
      pszName = "Faridpur";
      break;
      case 35:
      pszName = "Feni";
      break;
      case 36:
      pszName = "Gaibandha";
      break;
      case 37:
      pszName = "Gazipur";
      break;
      case 38:
      pszName = "Gopalganj";
      break;
      case 39:
      pszName = "Habiganj";
      break;
      case 40:
      pszName = "Jaipurhat";
      break;
      case 41:
      pszName = "Jamalpur";
      break;
      case 42:
      pszName = "Jessore";
      break;
      case 43:
      pszName = "Jhalakati";
      break;
      case 44:
      pszName = "Jhenaidah";
      break;
      case 45:
      pszName = "Khagrachari";
      break;
      case 46:
      pszName = "Khulna";
      break;
      case 47:
      pszName = "Kishorganj";
      break;
      case 48:
      pszName = "Kurigram";
      break;
      case 49:
      pszName = "Kushtia";
      break;
      case 50:
      pszName = "Laksmipur";
      break;
      case 51:
      pszName = "Lalmonirhat";
      break;
      case 52:
      pszName = "Madaripur";
      break;
      case 53:
      pszName = "Magura";
      break;
      case 54:
      pszName = "Manikganj";
      break;
      case 55:
      pszName = "Meherpur";
      break;
      case 56:
      pszName = "Moulavibazar";
      break;
      case 57:
      pszName = "Munshiganj";
      break;
      case 58:
      pszName = "Naogaon";
      break;
      case 59:
      pszName = "Narail";
      break;
      case 60:
      pszName = "Narayanganj";
      break;
      case 61:
      pszName = "Narsingdi";
      break;
      case 62:
      pszName = "Nator";
      break;
      case 63:
      pszName = "Netrakona";
      break;
      case 64:
      pszName = "Nilphamari";
      break;
      case 65:
      pszName = "Pabna";
      break;
      case 66:
      pszName = "Panchagar";
      break;
      case 67:
      pszName = "Parbattya Chattagram";
      break;
      case 68:
      pszName = "Pirojpur";
      break;
      case 69:
      pszName = "Rajbari";
      break;
      case 70:
      pszName = "Rajshahi";
      break;
      case 71:
      pszName = "Rangpur";
      break;
      case 72:
      pszName = "Satkhira";
      break;
      case 73:
      pszName = "Shariyatpur";
      break;
      case 74:
      pszName = "Sherpur";
      break;
      case 75:
      pszName = "Sirajganj";
      break;
      case 76:
      pszName = "Sunamganj";
      break;
      case 77:
      pszName = "Sylhet";
      break;
      case 78:
      pszName = "Tangail";
      break;
      case 79:
      pszName = "Thakurgaon";
      break;
      case 81:
      pszName = "Dhaka";
      break;
      case 82:
      pszName = "Khulna";
      break;
      case 83:
      pszName = "Rajshahi";
      break;
      case 84:
      pszName = "Chittagong";
      break;
      case 85:
      pszName = "Barisal";
      break;
      case 86:
      pszName = "Sylhet";
      break;
    }
  }
  if (strcmp(country_code,"BE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Antwerpen";
      break;
      case 2:
      pszName = "Brabant";
      break;
      case 3:
      pszName = "Hainaut";
      break;
      case 4:
      pszName = "Liege";
      break;
      case 5:
      pszName = "Limburg";
      break;
      case 6:
      pszName = "Luxembourg";
      break;
      case 7:
      pszName = "Namur";
      break;
      case 8:
      pszName = "Oost-Vlaanderen";
      break;
      case 9:
      pszName = "West-Vlaanderen";
      break;
      case 10:
      pszName = "Brabant Wallon";
      break;
      case 11:
      pszName = "Brussels Hoofdstedelijk Gewest";
      break;
      case 12:
      pszName = "Vlaams-Brabant";
      break;
    }
  }
  if (strcmp(country_code,"BF") == 0) {
    switch (region_code2) {
      case 15:
      pszName = "Bam";
      break;
      case 19:
      pszName = "Boulkiemde";
      break;
      case 20:
      pszName = "Ganzourgou";
      break;
      case 21:
      pszName = "Gnagna";
      break;
      case 28:
      pszName = "Kouritenga";
      break;
      case 33:
      pszName = "Oudalan";
      break;
      case 34:
      pszName = "Passore";
      break;
      case 36:
      pszName = "Sanguie";
      break;
      case 40:
      pszName = "Soum";
      break;
      case 42:
      pszName = "Tapoa";
      break;
      case 44:
      pszName = "Zoundweogo";
      break;
      case 45:
      pszName = "Bale";
      break;
      case 46:
      pszName = "Banwa";
      break;
      case 47:
      pszName = "Bazega";
      break;
      case 48:
      pszName = "Bougouriba";
      break;
      case 49:
      pszName = "Boulgou";
      break;
      case 50:
      pszName = "Gourma";
      break;
      case 51:
      pszName = "Houet";
      break;
      case 52:
      pszName = "Ioba";
      break;
      case 53:
      pszName = "Kadiogo";
      break;
      case 54:
      pszName = "Kenedougou";
      break;
      case 55:
      pszName = "Komoe";
      break;
      case 56:
      pszName = "Komondjari";
      break;
      case 57:
      pszName = "Kompienga";
      break;
      case 58:
      pszName = "Kossi";
      break;
      case 59:
      pszName = "Koulpelogo";
      break;
      case 60:
      pszName = "Kourweogo";
      break;
      case 61:
      pszName = "Leraba";
      break;
      case 62:
      pszName = "Loroum";
      break;
      case 63:
      pszName = "Mouhoun";
      break;
      case 64:
      pszName = "Namentenga";
      break;
      case 65:
      pszName = "Naouri";
      break;
      case 66:
      pszName = "Nayala";
      break;
      case 67:
      pszName = "Noumbiel";
      break;
      case 68:
      pszName = "Oubritenga";
      break;
      case 69:
      pszName = "Poni";
      break;
      case 70:
      pszName = "Sanmatenga";
      break;
      case 71:
      pszName = "Seno";
      break;
      case 72:
      pszName = "Sissili";
      break;
      case 73:
      pszName = "Sourou";
      break;
      case 74:
      pszName = "Tuy";
      break;
      case 75:
      pszName = "Yagha";
      break;
      case 76:
      pszName = "Yatenga";
      break;
      case 77:
      pszName = "Ziro";
      break;
      case 78:
      pszName = "Zondoma";
      break;
    }
  }
  if (strcmp(country_code,"BG") == 0) {
    switch (region_code2) {
      case 33:
      pszName = "Mikhaylovgrad";
      break;
      case 38:
      pszName = "Blagoevgrad";
      break;
      case 39:
      pszName = "Burgas";
      break;
      case 40:
      pszName = "Dobrich";
      break;
      case 41:
      pszName = "Gabrovo";
      break;
      case 42:
      pszName = "Grad Sofiya";
      break;
      case 43:
      pszName = "Khaskovo";
      break;
      case 44:
      pszName = "Kurdzhali";
      break;
      case 45:
      pszName = "Kyustendil";
      break;
      case 46:
      pszName = "Lovech";
      break;
      case 47:
      pszName = "Montana";
      break;
      case 48:
      pszName = "Pazardzhik";
      break;
      case 49:
      pszName = "Pernik";
      break;
      case 50:
      pszName = "Pleven";
      break;
      case 51:
      pszName = "Plovdiv";
      break;
      case 52:
      pszName = "Razgrad";
      break;
      case 53:
      pszName = "Ruse";
      break;
      case 54:
      pszName = "Shumen";
      break;
      case 55:
      pszName = "Silistra";
      break;
      case 56:
      pszName = "Sliven";
      break;
      case 57:
      pszName = "Smolyan";
      break;
      case 58:
      pszName = "Sofiya";
      break;
      case 59:
      pszName = "Stara Zagora";
      break;
      case 60:
      pszName = "Turgovishte";
      break;
      case 61:
      pszName = "Varna";
      break;
      case 62:
      pszName = "Veliko Turnovo";
      break;
      case 63:
      pszName = "Vidin";
      break;
      case 64:
      pszName = "Vratsa";
      break;
      case 65:
      pszName = "Yambol";
      break;
    }
  }
  if (strcmp(country_code,"BH") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Al Hadd";
      break;
      case 2:
      pszName = "Al Manamah";
      break;
      case 3:
      pszName = "Al Muharraq";
      break;
      case 5:
      pszName = "Jidd Hafs";
      break;
      case 6:
      pszName = "Sitrah";
      break;
      case 7:
      pszName = "Ar Rifa' wa al Mintaqah al Janubiyah";
      break;
      case 8:
      pszName = "Al Mintaqah al Gharbiyah";
      break;
      case 9:
      pszName = "Mintaqat Juzur Hawar";
      break;
      case 10:
      pszName = "Al Mintaqah ash Shamaliyah";
      break;
      case 11:
      pszName = "Al Mintaqah al Wusta";
      break;
      case 12:
      pszName = "Madinat";
      break;
      case 13:
      pszName = "Ar Rifa";
      break;
      case 14:
      pszName = "Madinat Hamad";
      break;
      case 15:
      pszName = "Al Muharraq";
      break;
      case 16:
      pszName = "Al Asimah";
      break;
      case 17:
      pszName = "Al Janubiyah";
      break;
      case 18:
      pszName = "Ash Shamaliyah";
      break;
      case 19:
      pszName = "Al Wusta";
      break;
    }
  }
  if (strcmp(country_code,"BI") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Bujumbura";
      break;
      case 9:
      pszName = "Bubanza";
      break;
      case 10:
      pszName = "Bururi";
      break;
      case 11:
      pszName = "Cankuzo";
      break;
      case 12:
      pszName = "Cibitoke";
      break;
      case 13:
      pszName = "Gitega";
      break;
      case 14:
      pszName = "Karuzi";
      break;
      case 15:
      pszName = "Kayanza";
      break;
      case 16:
      pszName = "Kirundo";
      break;
      case 17:
      pszName = "Makamba";
      break;
      case 18:
      pszName = "Muyinga";
      break;
      case 19:
      pszName = "Ngozi";
      break;
      case 20:
      pszName = "Rutana";
      break;
      case 21:
      pszName = "Ruyigi";
      break;
      case 22:
      pszName = "Muramvya";
      break;
      case 23:
      pszName = "Mwaro";
      break;
    }
  }
  if (strcmp(country_code,"BJ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Atakora";
      break;
      case 2:
      pszName = "ca_antique";
      break;
      case 3:
      pszName = "Borgou";
      break;
      case 4:
      pszName = "Mono";
      break;
      case 5:
      pszName = "Oueme";
      break;
      case 6:
      pszName = "Zou";
      break;
      case 7:
      pszName = "Alibori";
      break;
      case 8:
      pszName = "Atakora";
      break;
      case 9:
      pszName = "ca_anyique";
      break;
      case 10:
      pszName = "Borgou";
      break;
      case 11:
      pszName = "Collines";
      break;
      case 12:
      pszName = "Kouffo";
      break;
      case 13:
      pszName = "Donga";
      break;
      case 14:
      pszName = "Littoral";
      break;
      case 15:
      pszName = "Mono";
      break;
      case 16:
      pszName = "Oueme";
      break;
      case 17:
      pszName = "Plateau";
      break;
      case 18:
      pszName = "Zou";
      break;
    }
  }
  if (strcmp(country_code,"BM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Devonshire";
      break;
      case 2:
      pszName = "Hamilton";
      break;
      case 3:
      pszName = "Hamilton";
      break;
      case 4:
      pszName = "Paget";
      break;
      case 5:
      pszName = "Pembroke";
      break;
      case 6:
      pszName = "Saint George";
      break;
      case 7:
      pszName = "Saint George's";
      break;
      case 8:
      pszName = "Sandys";
      break;
      case 9:
      pszName = "Smiths";
      break;
      case 10:
      pszName = "Southampton";
      break;
      case 11:
      pszName = "Warwick";
      break;
    }
  }
  if (strcmp(country_code,"BN") == 0) {
    switch (region_code2) {
      case 7:
      pszName = "Alibori";
      break;
      case 8:
      pszName = "Belait";
      break;
      case 9:
      pszName = "Brunei and Muara";
      break;
      case 10:
      pszName = "Temburong";
      break;
      case 11:
      pszName = "Collines";
      break;
      case 12:
      pszName = "Kouffo";
      break;
      case 13:
      pszName = "Donga";
      break;
      case 14:
      pszName = "Littoral";
      break;
      case 15:
      pszName = "Tutong";
      break;
      case 16:
      pszName = "Oueme";
      break;
      case 17:
      pszName = "Plateau";
      break;
      case 18:
      pszName = "Zou";
      break;
    }
  }
  if (strcmp(country_code,"BO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Chuquisaca";
      break;
      case 2:
      pszName = "Cochabamba";
      break;
      case 3:
      pszName = "El Beni";
      break;
      case 4:
      pszName = "La Paz";
      break;
      case 5:
      pszName = "Oruro";
      break;
      case 6:
      pszName = "Pando";
      break;
      case 7:
      pszName = "Potosi";
      break;
      case 8:
      pszName = "Santa Cruz";
      break;
      case 9:
      pszName = "Tarija";
      break;
    }
  }
  if (strcmp(country_code,"BR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Acre";
      break;
      case 2:
      pszName = "Alagoas";
      break;
      case 3:
      pszName = "Amapa";
      break;
      case 4:
      pszName = "Amazonas";
      break;
      case 5:
      pszName = "Bahia";
      break;
      case 6:
      pszName = "Ceara";
      break;
      case 7:
      pszName = "Distrito Federal";
      break;
      case 8:
      pszName = "Espirito Santo";
      break;
      case 11:
      pszName = "Mato Grosso do Sul";
      break;
      case 13:
      pszName = "Maranhao";
      break;
      case 14:
      pszName = "Mato Grosso";
      break;
      case 15:
      pszName = "Minas Gerais";
      break;
      case 16:
      pszName = "Para";
      break;
      case 17:
      pszName = "Paraiba";
      break;
      case 18:
      pszName = "Parana";
      break;
      case 20:
      pszName = "Piaui";
      break;
      case 21:
      pszName = "Rio de Janeiro";
      break;
      case 22:
      pszName = "Rio Grande do Norte";
      break;
      case 23:
      pszName = "Rio Grande do Sul";
      break;
      case 24:
      pszName = "Rondonia";
      break;
      case 25:
      pszName = "Roraima";
      break;
      case 26:
      pszName = "Santa Catarina";
      break;
      case 27:
      pszName = "Sao Paulo";
      break;
      case 28:
      pszName = "Sergipe";
      break;
      case 29:
      pszName = "Goias";
      break;
      case 30:
      pszName = "Pernambuco";
      break;
      case 31:
      pszName = "Tocantins";
      break;
    }
  }
  if (strcmp(country_code,"BS") == 0) {
    switch (region_code2) {
      case 5:
      pszName = "Bimini";
      break;
      case 6:
      pszName = "Cat Island";
      break;
      case 10:
      pszName = "Exuma";
      break;
      case 13:
      pszName = "Inagua";
      break;
      case 15:
      pszName = "Long Island";
      break;
      case 16:
      pszName = "Mayaguana";
      break;
      case 18:
      pszName = "Ragged Island";
      break;
      case 22:
      pszName = "Harbour Island";
      break;
      case 23:
      pszName = "New Providence";
      break;
      case 24:
      pszName = "Acklins and Crooked Islands";
      break;
      case 25:
      pszName = "Freeport";
      break;
      case 26:
      pszName = "Fresh Creek";
      break;
      case 27:
      pszName = "Governor's Harbour";
      break;
      case 28:
      pszName = "Green Turtle Cay";
      break;
      case 29:
      pszName = "High Rock";
      break;
      case 30:
      pszName = "Kemps Bay";
      break;
      case 31:
      pszName = "Marsh Harbour";
      break;
      case 32:
      pszName = "Nichollstown and Berry Islands";
      break;
      case 33:
      pszName = "Rock Sound";
      break;
      case 34:
      pszName = "Sandy Point";
      break;
      case 35:
      pszName = "San Salvador and Rum Cay";
      break;
    }
  }
  if (strcmp(country_code,"BT") == 0) {
    switch (region_code2) {
      case 5:
      pszName = "Bumthang";
      break;
      case 6:
      pszName = "Chhukha";
      break;
      case 7:
      pszName = "Chirang";
      break;
      case 8:
      pszName = "Daga";
      break;
      case 9:
      pszName = "Geylegphug";
      break;
      case 10:
      pszName = "Ha";
      break;
      case 11:
      pszName = "Lhuntshi";
      break;
      case 12:
      pszName = "Mongar";
      break;
      case 13:
      pszName = "Paro";
      break;
      case 14:
      pszName = "Pemagatsel";
      break;
      case 15:
      pszName = "Punakha";
      break;
      case 16:
      pszName = "Samchi";
      break;
      case 17:
      pszName = "Samdrup";
      break;
      case 18:
      pszName = "Shemgang";
      break;
      case 19:
      pszName = "Tashigang";
      break;
      case 20:
      pszName = "Thimphu";
      break;
      case 21:
      pszName = "Tongsa";
      break;
      case 22:
      pszName = "Wangdi Phodrang";
      break;
    }
  }
  if (strcmp(country_code,"BW") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Central";
      break;
      case 3:
      pszName = "Ghanzi";
      break;
      case 4:
      pszName = "Kgalagadi";
      break;
      case 5:
      pszName = "Kgatleng";
      break;
      case 6:
      pszName = "Kweneng";
      break;
      case 8:
      pszName = "North-East";
      break;
      case 9:
      pszName = "South-East";
      break;
      case 10:
      pszName = "Southern";
      break;
      case 11:
      pszName = "North-West";
      break;
    }
  }
  if (strcmp(country_code,"BY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Brestskaya Voblasts'";
      break;
      case 2:
      pszName = "Homyel'skaya Voblasts'";
      break;
      case 3:
      pszName = "Hrodzyenskaya Voblasts'";
      break;
      case 4:
      pszName = "Minsk";
      break;
      case 5:
      pszName = "Minskaya Voblasts'";
      break;
      case 6:
      pszName = "Mahilyowskaya Voblasts'";
      break;
      case 7:
      pszName = "Vitsyebskaya Voblasts'";
      break;
    }
  }
  if (strcmp(country_code,"BZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Belize";
      break;
      case 2:
      pszName = "Cayo";
      break;
      case 3:
      pszName = "Corozal";
      break;
      case 4:
      pszName = "Orange Walk";
      break;
      case 5:
      pszName = "Stann Creek";
      break;
      case 6:
      pszName = "Toledo";
      break;
    }
  }
  if (strcmp(country_code,"CD") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bandundu";
      break;
      case 2:
      pszName = "Equateur";
      break;
      case 4:
      pszName = "Kasai-Oriental";
      break;
      case 5:
      pszName = "Katanga";
      break;
      case 6:
      pszName = "Kinshasa";
      break;
      case 7:
      pszName = "Kivu";
      break;
      case 8:
      pszName = "Bas-Congo";
      break;
      case 9:
      pszName = "Orientale";
      break;
      case 10:
      pszName = "Maniema";
      break;
      case 11:
      pszName = "Nord-Kivu";
      break;
      case 12:
      pszName = "Sud-Kivu";
      break;
      case 13:
      pszName = "Cuvette";
      break;
    }
  }
  if (strcmp(country_code,"CF") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bamingui-Bangoran";
      break;
      case 2:
      pszName = "Basse-Kotto";
      break;
      case 3:
      pszName = "Haute-Kotto";
      break;
      case 4:
      pszName = "Mambere-Kadei";
      break;
      case 5:
      pszName = "Haut-Mbomou";
      break;
      case 6:
      pszName = "Kemo";
      break;
      case 7:
      pszName = "Lobaye";
      break;
      case 8:
      pszName = "Mbomou";
      break;
      case 9:
      pszName = "Nana-Mambere";
      break;
      case 11:
      pszName = "Ouaka";
      break;
      case 12:
      pszName = "Ouham";
      break;
      case 13:
      pszName = "Ouham-Pende";
      break;
      case 14:
      pszName = "Cuvette-Ouest";
      break;
      case 15:
      pszName = "Nana-Grebizi";
      break;
      case 16:
      pszName = "Sangha-Mbaere";
      break;
      case 17:
      pszName = "Ombella-Mpoko";
      break;
      case 18:
      pszName = "Bangui";
      break;
    }
  }
  if (strcmp(country_code,"CG") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bouenza";
      break;
      case 3:
      pszName = "Cuvette";
      break;
      case 4:
      pszName = "Kouilou";
      break;
      case 5:
      pszName = "Lekoumou";
      break;
      case 6:
      pszName = "Likouala";
      break;
      case 7:
      pszName = "Niari";
      break;
      case 8:
      pszName = "Plateaux";
      break;
      case 10:
      pszName = "Sangha";
      break;
      case 11:
      pszName = "Pool";
      break;
      case 12:
      pszName = "Brazzaville";
      break;
    }
  }
  if (strcmp(country_code,"CH") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aargau";
      break;
      case 2:
      pszName = "Ausser-Rhoden";
      break;
      case 3:
      pszName = "Basel-Landschaft";
      break;
      case 4:
      pszName = "Basel-Stadt";
      break;
      case 5:
      pszName = "Bern";
      break;
      case 6:
      pszName = "Fribourg";
      break;
      case 7:
      pszName = "Geneve";
      break;
      case 8:
      pszName = "Glarus";
      break;
      case 9:
      pszName = "Graubunden";
      break;
      case 10:
      pszName = "Inner-Rhoden";
      break;
      case 11:
      pszName = "Luzern";
      break;
      case 12:
      pszName = "Neuchatel";
      break;
      case 13:
      pszName = "Nidwalden";
      break;
      case 14:
      pszName = "Obwalden";
      break;
      case 15:
      pszName = "Sankt Gallen";
      break;
      case 16:
      pszName = "Schaffhausen";
      break;
      case 17:
      pszName = "Schwyz";
      break;
      case 18:
      pszName = "Solothurn";
      break;
      case 19:
      pszName = "Thurgau";
      break;
      case 20:
      pszName = "Ticino";
      break;
      case 21:
      pszName = "Uri";
      break;
      case 22:
      pszName = "Valais";
      break;
      case 23:
      pszName = "Vaud";
      break;
      case 24:
      pszName = "Zug";
      break;
      case 25:
      pszName = "Zurich";
      break;
      case 26:
      pszName = "Jura";
      break;
    }
  }
  if (strcmp(country_code,"CI") == 0) {
    switch (region_code2) {
      case 51:
      pszName = "Sassandra";
      break;
      case 61:
      pszName = "Abidjan";
      break;
      case 74:
      pszName = "Agneby";
      break;
      case 75:
      pszName = "Bafing";
      break;
      case 76:
      pszName = "Bas-Sassandra";
      break;
      case 77:
      pszName = "Denguele";
      break;
      case 78:
      pszName = "Dix-Huit Montagnes";
      break;
      case 79:
      pszName = "Fromager";
      break;
      case 80:
      pszName = "Haut-Sassandra";
      break;
      case 81:
      pszName = "Lacs";
      break;
      case 82:
      pszName = "Lagunes";
      break;
      case 83:
      pszName = "Marahoue";
      break;
      case 84:
      pszName = "Moyen-Cavally";
      break;
      case 85:
      pszName = "Moyen-Comoe";
      break;
      case 86:
      pszName = "N'zi-Comoe";
      break;
      case 87:
      pszName = "Savanes";
      break;
      case 88:
      pszName = "Sud-Bandama";
      break;
      case 89:
      pszName = "Sud-Comoe";
      break;
      case 90:
      pszName = "Vallee du Bandama";
      break;
      case 91:
      pszName = "Worodougou";
      break;
      case 92:
      pszName = "Zanzan";
      break;
    }
  }
  if (strcmp(country_code,"CL") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Valparaiso";
      break;
      case 2:
      pszName = "Aisen del General Carlos Ibanez del Campo";
      break;
      case 3:
      pszName = "Antofagasta";
      break;
      case 4:
      pszName = "Araucania";
      break;
      case 5:
      pszName = "Atacama";
      break;
      case 6:
      pszName = "Bio-Bio";
      break;
      case 7:
      pszName = "Coquimbo";
      break;
      case 8:
      pszName = "Libertador General Bernardo O'Higgins";
      break;
      case 9:
      pszName = "Los Lagos";
      break;
      case 10:
      pszName = "Magallanes y de la Antartica Chilena";
      break;
      case 11:
      pszName = "Maule";
      break;
      case 12:
      pszName = "Region Metropolitana";
      break;
      case 13:
      pszName = "Tarapaca";
      break;
    }
  }
  if (strcmp(country_code,"CM") == 0) {
    switch (region_code2) {
      case 4:
      pszName = "Est";
      break;
      case 5:
      pszName = "Littoral";
      break;
      case 7:
      pszName = "Nord-Ouest";
      break;
      case 8:
      pszName = "Ouest";
      break;
      case 9:
      pszName = "Sud-Ouest";
      break;
      case 10:
      pszName = "Adamaoua";
      break;
      case 11:
      pszName = "Centre";
      break;
      case 12:
      pszName = "Extreme-Nord";
      break;
      case 13:
      pszName = "Nord";
      break;
      case 14:
      pszName = "Sud";
      break;
    }
  }
  if (strcmp(country_code,"CN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Anhui";
      break;
      case 2:
      pszName = "Zhejiang";
      break;
      case 3:
      pszName = "Jiangxi";
      break;
      case 4:
      pszName = "Jiangsu";
      break;
      case 5:
      pszName = "Jilin";
      break;
      case 6:
      pszName = "Qinghai";
      break;
      case 7:
      pszName = "Fujian";
      break;
      case 8:
      pszName = "Heilongjiang";
      break;
      case 9:
      pszName = "Henan";
      break;
      case 10:
      pszName = "Hebei";
      break;
      case 11:
      pszName = "Hunan";
      break;
      case 12:
      pszName = "Hubei";
      break;
      case 13:
      pszName = "Xinjiang";
      break;
      case 14:
      pszName = "Xizang";
      break;
      case 15:
      pszName = "Gansu";
      break;
      case 16:
      pszName = "Guangxi";
      break;
      case 18:
      pszName = "Guizhou";
      break;
      case 19:
      pszName = "Liaoning";
      break;
      case 20:
      pszName = "Nei Mongol";
      break;
      case 21:
      pszName = "Ningxia";
      break;
      case 22:
      pszName = "Beijing";
      break;
      case 23:
      pszName = "Shanghai";
      break;
      case 24:
      pszName = "Shanxi";
      break;
      case 25:
      pszName = "Shandong";
      break;
      case 26:
      pszName = "Shaanxi";
      break;
      case 28:
      pszName = "Tianjin";
      break;
      case 29:
      pszName = "Yunnan";
      break;
      case 30:
      pszName = "Guangdong";
      break;
      case 31:
      pszName = "Hainan";
      break;
      case 32:
      pszName = "Sichuan";
      break;
      case 33:
      pszName = "Chongqing";
      break;
    }
  }
  if (strcmp(country_code,"CO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Amazonas";
      break;
      case 2:
      pszName = "Antioquia";
      break;
      case 3:
      pszName = "Arauca";
      break;
      case 4:
      pszName = "Atlantico";
      break;
      case 5:
      pszName = "Bolivar Department";
      break;
      case 6:
      pszName = "Boyaca Department";
      break;
      case 7:
      pszName = "Caldas Department";
      break;
      case 8:
      pszName = "Caqueta";
      break;
      case 9:
      pszName = "Cauca";
      break;
      case 10:
      pszName = "Cesar";
      break;
      case 11:
      pszName = "Choco";
      break;
      case 12:
      pszName = "Cordoba";
      break;
      case 14:
      pszName = "Guaviare";
      break;
      case 15:
      pszName = "Guainia";
      break;
      case 16:
      pszName = "Huila";
      break;
      case 17:
      pszName = "La Guajira";
      break;
      case 18:
      pszName = "Magdalena Department";
      break;
      case 19:
      pszName = "Meta";
      break;
      case 20:
      pszName = "Narino";
      break;
      case 21:
      pszName = "Norte de Santander";
      break;
      case 22:
      pszName = "Putumayo";
      break;
      case 23:
      pszName = "Quindio";
      break;
      case 24:
      pszName = "Risaralda";
      break;
      case 25:
      pszName = "San Andres y Providencia";
      break;
      case 26:
      pszName = "Santander";
      break;
      case 27:
      pszName = "Sucre";
      break;
      case 28:
      pszName = "Tolima";
      break;
      case 29:
      pszName = "Valle del Cauca";
      break;
      case 30:
      pszName = "Vaupes";
      break;
      case 31:
      pszName = "Vichada";
      break;
      case 32:
      pszName = "Casanare";
      break;
      case 33:
      pszName = "Cundinamarca";
      break;
      case 34:
      pszName = "Distrito Especial";
      break;
      case 35:
      pszName = "Bolivar";
      break;
      case 36:
      pszName = "Boyaca";
      break;
      case 37:
      pszName = "Caldas";
      break;
      case 38:
      pszName = "Magdalena";
      break;
    }
  }
  if (strcmp(country_code,"CR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Alajuela";
      break;
      case 2:
      pszName = "Cartago";
      break;
      case 3:
      pszName = "Guanacaste";
      break;
      case 4:
      pszName = "Heredia";
      break;
      case 6:
      pszName = "Limon";
      break;
      case 7:
      pszName = "Puntarenas";
      break;
      case 8:
      pszName = "San Jose";
      break;
    }
  }
  if (strcmp(country_code,"CU") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Pinar del Rio";
      break;
      case 2:
      pszName = "Ciudad de la Habana";
      break;
      case 3:
      pszName = "Matanzas";
      break;
      case 4:
      pszName = "Isla de la Juventud";
      break;
      case 5:
      pszName = "Camaguey";
      break;
      case 7:
      pszName = "Ciego de Avila";
      break;
      case 8:
      pszName = "Cienfuegos";
      break;
      case 9:
      pszName = "Granma";
      break;
      case 10:
      pszName = "Guantanamo";
      break;
      case 11:
      pszName = "La Habana";
      break;
      case 12:
      pszName = "Holguin";
      break;
      case 13:
      pszName = "Las Tunas";
      break;
      case 14:
      pszName = "Sancti Spiritus";
      break;
      case 15:
      pszName = "Santiago de Cuba";
      break;
      case 16:
      pszName = "Villa Clara";
      break;
    }
  }
  if (strcmp(country_code,"CV") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Boa Vista";
      break;
      case 2:
      pszName = "Brava";
      break;
      case 4:
      pszName = "Maio";
      break;
      case 5:
      pszName = "Paul";
      break;
      case 7:
      pszName = "Ribeira Grande";
      break;
      case 8:
      pszName = "Sal";
      break;
      case 10:
      pszName = "Sao Nicolau";
      break;
      case 11:
      pszName = "Sao Vicente";
      break;
      case 13:
      pszName = "Mosteiros";
      break;
      case 14:
      pszName = "Praia";
      break;
      case 15:
      pszName = "Santa Catarina";
      break;
      case 16:
      pszName = "Santa Cruz";
      break;
      case 17:
      pszName = "Sao Domingos";
      break;
      case 18:
      pszName = "Sao Filipe";
      break;
      case 19:
      pszName = "Sao Miguel";
      break;
      case 20:
      pszName = "Tarrafal";
      break;
    }
  }
  if (strcmp(country_code,"CY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Famagusta";
      break;
      case 2:
      pszName = "Kyrenia";
      break;
      case 3:
      pszName = "Larnaca";
      break;
      case 4:
      pszName = "Nicosia";
      break;
      case 5:
      pszName = "Limassol";
      break;
      case 6:
      pszName = "Paphos";
      break;
    }
  }
  if (strcmp(country_code,"CZ") == 0) {
    switch (region_code2) {
      case 3:
      pszName = "Blansko";
      break;
      case 4:
      pszName = "Breclav";
      break;
      case 20:
      pszName = "Hradec Kralove";
      break;
      case 21:
      pszName = "Jablonec nad Nisou";
      break;
      case 23:
      pszName = "Jicin";
      break;
      case 24:
      pszName = "Jihlava";
      break;
      case 30:
      pszName = "Kolin";
      break;
      case 33:
      pszName = "Liberec";
      break;
      case 36:
      pszName = "Melnik";
      break;
      case 37:
      pszName = "Mlada Boleslav";
      break;
      case 39:
      pszName = "Nachod";
      break;
      case 41:
      pszName = "Nymburk";
      break;
      case 45:
      pszName = "Pardubice";
      break;
      case 52:
      pszName = "Hlavni mesto Praha";
      break;
      case 61:
      pszName = "Semily";
      break;
      case 70:
      pszName = "Trutnov";
      break;
      case 78:
      pszName = "Jihomoravsky kraj";
      break;
      case 79:
      pszName = "Jihocesky kraj";
      break;
      case 80:
      pszName = "Vysocina";
      break;
      case 81:
      pszName = "Karlovarsky kraj";
      break;
      case 82:
      pszName = "Kralovehradecky kraj";
      break;
      case 83:
      pszName = "Liberecky kraj";
      break;
      case 84:
      pszName = "Olomoucky kraj";
      break;
      case 85:
      pszName = "Moravskoslezsky kraj";
      break;
      case 86:
      pszName = "Pardubicky kraj";
      break;
      case 87:
      pszName = "Plzensky kraj";
      break;
      case 88:
      pszName = "Stredocesky kraj";
      break;
      case 89:
      pszName = "Ustecky kraj";
      break;
      case 90:
      pszName = "Zlinsky kraj";
      break;
    }
  }
  if (strcmp(country_code,"DE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Baden-Wurttemberg";
      break;
      case 2:
      pszName = "Bayern";
      break;
      case 3:
      pszName = "Bremen";
      break;
      case 4:
      pszName = "Hamburg";
      break;
      case 5:
      pszName = "Hessen";
      break;
      case 6:
      pszName = "Niedersachsen";
      break;
      case 7:
      pszName = "Nordrhein-Westfalen";
      break;
      case 8:
      pszName = "Rheinland-Pfalz";
      break;
      case 9:
      pszName = "Saarland";
      break;
      case 10:
      pszName = "Schleswig-Holstein";
      break;
      case 11:
      pszName = "Brandenburg";
      break;
      case 12:
      pszName = "Mecklenburg-Vorpommern";
      break;
      case 13:
      pszName = "Sachsen";
      break;
      case 14:
      pszName = "Sachsen-Anhalt";
      break;
      case 15:
      pszName = "Thuringen";
      break;
      case 16:
      pszName = "Berlin";
      break;
    }
  }
  if (strcmp(country_code,"DJ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ali Sabieh";
      break;
      case 4:
      pszName = "Obock";
      break;
      case 5:
      pszName = "Tadjoura";
      break;
      case 6:
      pszName = "Dikhil";
      break;
      case 7:
      pszName = "Djibouti";
      break;
      case 8:
      pszName = "Arta";
      break;
    }
  }
  if (strcmp(country_code,"DK") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Arhus";
      break;
      case 2:
      pszName = "Bornholm";
      break;
      case 3:
      pszName = "Frederiksborg";
      break;
      case 4:
      pszName = "Fyn";
      break;
      case 5:
      pszName = "Kobenhavn";
      break;
      case 6:
      pszName = "Staden Kobenhavn";
      break;
      case 7:
      pszName = "Nordjylland";
      break;
      case 8:
      pszName = "Ribe";
      break;
      case 9:
      pszName = "Ringkobing";
      break;
      case 10:
      pszName = "Roskilde";
      break;
      case 11:
      pszName = "Sonderjylland";
      break;
      case 12:
      pszName = "Storstrom";
      break;
      case 13:
      pszName = "Vejle";
      break;
      case 14:
      pszName = "Vestsjalland";
      break;
      case 15:
      pszName = "Viborg";
      break;
      case 17:
      pszName = "Hovedstaden";
      break;
      case 18:
      pszName = "Midtjyllen";
      break;
      case 19:
      pszName = "Nordjylland";
      break;
      case 20:
      pszName = "Sjelland";
      break;
      case 21:
      pszName = "Syddanmark";
      break;
    }
  }
  if (strcmp(country_code,"DM") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Saint Andrew";
      break;
      case 3:
      pszName = "Saint David";
      break;
      case 4:
      pszName = "Saint George";
      break;
      case 5:
      pszName = "Saint John";
      break;
      case 6:
      pszName = "Saint Joseph";
      break;
      case 7:
      pszName = "Saint Luke";
      break;
      case 8:
      pszName = "Saint Mark";
      break;
      case 9:
      pszName = "Saint Patrick";
      break;
      case 10:
      pszName = "Saint Paul";
      break;
      case 11:
      pszName = "Saint Peter";
      break;
    }
  }
  if (strcmp(country_code,"DO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Azua";
      break;
      case 2:
      pszName = "Baoruco";
      break;
      case 3:
      pszName = "Barahona";
      break;
      case 4:
      pszName = "Dajabon";
      break;
      case 5:
      pszName = "Distrito Nacional";
      break;
      case 6:
      pszName = "Duarte";
      break;
      case 8:
      pszName = "Espaillat";
      break;
      case 9:
      pszName = "Independencia";
      break;
      case 10:
      pszName = "La Altagracia";
      break;
      case 11:
      pszName = "Elias Pina";
      break;
      case 12:
      pszName = "La Romana";
      break;
      case 14:
      pszName = "Maria Trinidad Sanchez";
      break;
      case 15:
      pszName = "Monte Cristi";
      break;
      case 16:
      pszName = "Pedernales";
      break;
      case 17:
      pszName = "Peravia";
      break;
      case 18:
      pszName = "Puerto Plata";
      break;
      case 19:
      pszName = "Salcedo";
      break;
      case 20:
      pszName = "Samana";
      break;
      case 21:
      pszName = "Sanchez Ramirez";
      break;
      case 23:
      pszName = "San Juan";
      break;
      case 24:
      pszName = "San Pedro De Macoris";
      break;
      case 25:
      pszName = "Santiago";
      break;
      case 26:
      pszName = "Santiago Rodriguez";
      break;
      case 27:
      pszName = "Valverde";
      break;
      case 28:
      pszName = "El Seibo";
      break;
      case 29:
      pszName = "Hato Mayor";
      break;
      case 30:
      pszName = "La Vega";
      break;
      case 31:
      pszName = "Monsenor Nouel";
      break;
      case 32:
      pszName = "Monte Plata";
      break;
      case 33:
      pszName = "San Cristobal";
      break;
      case 34:
      pszName = "Distrito Nacional";
      break;
      case 35:
      pszName = "Peravia";
      break;
      case 36:
      pszName = "San Jose de Ocoa";
      break;
      case 37:
      pszName = "Santo Domingo";
      break;
    }
  }
  if (strcmp(country_code,"DZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Alger";
      break;
      case 3:
      pszName = "Batna";
      break;
      case 4:
      pszName = "Constantine";
      break;
      case 6:
      pszName = "Medea";
      break;
      case 7:
      pszName = "Mostaganem";
      break;
      case 9:
      pszName = "Oran";
      break;
      case 10:
      pszName = "Saida";
      break;
      case 12:
      pszName = "Setif";
      break;
      case 13:
      pszName = "Tiaret";
      break;
      case 14:
      pszName = "Tizi Ouzou";
      break;
      case 15:
      pszName = "Tlemcen";
      break;
      case 18:
      pszName = "Bejaia";
      break;
      case 19:
      pszName = "Biskra";
      break;
      case 20:
      pszName = "Blida";
      break;
      case 21:
      pszName = "Bouira";
      break;
      case 22:
      pszName = "Djelfa";
      break;
      case 23:
      pszName = "Guelma";
      break;
      case 24:
      pszName = "Jijel";
      break;
      case 25:
      pszName = "Laghouat";
      break;
      case 26:
      pszName = "Mascara";
      break;
      case 27:
      pszName = "M'sila";
      break;
      case 29:
      pszName = "Oum el Bouaghi";
      break;
      case 30:
      pszName = "Sidi Bel Abbes";
      break;
      case 31:
      pszName = "Skikda";
      break;
      case 33:
      pszName = "Tebessa";
      break;
      case 34:
      pszName = "Adrar";
      break;
      case 35:
      pszName = "Ain Defla";
      break;
      case 36:
      pszName = "Ain Temouchent";
      break;
      case 37:
      pszName = "Annaba";
      break;
      case 38:
      pszName = "Bechar";
      break;
      case 39:
      pszName = "Bordj Bou Arreridj";
      break;
      case 40:
      pszName = "Boumerdes";
      break;
      case 41:
      pszName = "Chlef";
      break;
      case 42:
      pszName = "El Bayadh";
      break;
      case 43:
      pszName = "El Oued";
      break;
      case 44:
      pszName = "El Tarf";
      break;
      case 45:
      pszName = "Ghardaia";
      break;
      case 46:
      pszName = "Illizi";
      break;
      case 47:
      pszName = "Khenchela";
      break;
      case 48:
      pszName = "Mila";
      break;
      case 49:
      pszName = "Naama";
      break;
      case 50:
      pszName = "Ouargla";
      break;
      case 51:
      pszName = "Relizane";
      break;
      case 52:
      pszName = "Souk Ahras";
      break;
      case 53:
      pszName = "Tamanghasset";
      break;
      case 54:
      pszName = "Tindouf";
      break;
      case 55:
      pszName = "Tipaza";
      break;
      case 56:
      pszName = "Tissemsilt";
      break;
    }
  }
  if (strcmp(country_code,"EC") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Galapagos";
      break;
      case 2:
      pszName = "Azuay";
      break;
      case 3:
      pszName = "Bolivar";
      break;
      case 4:
      pszName = "Canar";
      break;
      case 5:
      pszName = "Carchi";
      break;
      case 6:
      pszName = "Chimborazo";
      break;
      case 7:
      pszName = "Cotopaxi";
      break;
      case 8:
      pszName = "El Oro";
      break;
      case 9:
      pszName = "Esmeraldas";
      break;
      case 10:
      pszName = "Guayas";
      break;
      case 11:
      pszName = "Imbabura";
      break;
      case 12:
      pszName = "Loja";
      break;
      case 13:
      pszName = "Los Rios";
      break;
      case 14:
      pszName = "Manabi";
      break;
      case 15:
      pszName = "Morona-Santiago";
      break;
      case 17:
      pszName = "Pastaza";
      break;
      case 18:
      pszName = "Pichincha";
      break;
      case 19:
      pszName = "Tungurahua";
      break;
      case 20:
      pszName = "Zamora-Chinchipe";
      break;
      case 22:
      pszName = "Sucumbios";
      break;
      case 23:
      pszName = "Napo";
      break;
      case 24:
      pszName = "Orellana";
      break;
    }
  }
  if (strcmp(country_code,"EE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Harjumaa";
      break;
      case 2:
      pszName = "Hiiumaa";
      break;
      case 3:
      pszName = "Ida-Virumaa";
      break;
      case 4:
      pszName = "Jarvamaa";
      break;
      case 5:
      pszName = "Jogevamaa";
      break;
      case 6:
      pszName = "Kohtla-Jarve";
      break;
      case 7:
      pszName = "Laanemaa";
      break;
      case 8:
      pszName = "Laane-Virumaa";
      break;
      case 9:
      pszName = "Narva";
      break;
      case 10:
      pszName = "Parnu";
      break;
      case 11:
      pszName = "Parnumaa";
      break;
      case 12:
      pszName = "Polvamaa";
      break;
      case 13:
      pszName = "Raplamaa";
      break;
      case 14:
      pszName = "Saaremaa";
      break;
      case 15:
      pszName = "Sillamae";
      break;
      case 16:
      pszName = "Tallinn";
      break;
      case 17:
      pszName = "Tartu";
      break;
      case 18:
      pszName = "Tartumaa";
      break;
      case 19:
      pszName = "Valgamaa";
      break;
      case 20:
      pszName = "Viljandimaa";
      break;
      case 21:
      pszName = "Vorumaa";
      break;
    }
  }
  if (strcmp(country_code,"EG") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ad Daqahliyah";
      break;
      case 2:
      pszName = "Al Bahr al Ahmar";
      break;
      case 3:
      pszName = "Al Buhayrah";
      break;
      case 4:
      pszName = "Al Fayyum";
      break;
      case 5:
      pszName = "Al Gharbiyah";
      break;
      case 6:
      pszName = "Al Iskandariyah";
      break;
      case 7:
      pszName = "Al Isma'iliyah";
      break;
      case 8:
      pszName = "Al Jizah";
      break;
      case 9:
      pszName = "Al Minufiyah";
      break;
      case 10:
      pszName = "Al Minya";
      break;
      case 11:
      pszName = "Al Qahirah";
      break;
      case 12:
      pszName = "Al Qalyubiyah";
      break;
      case 13:
      pszName = "Al Wadi al Jadid";
      break;
      case 14:
      pszName = "Ash Sharqiyah";
      break;
      case 15:
      pszName = "As Suways";
      break;
      case 16:
      pszName = "Aswan";
      break;
      case 17:
      pszName = "Asyut";
      break;
      case 18:
      pszName = "Bani Suwayf";
      break;
      case 19:
      pszName = "Bur Sa'atom";
      break;
      case 20:
      pszName = "Dumyat";
      break;
      case 21:
      pszName = "Kafr ash Shaykh";
      break;
      case 22:
      pszName = "Matruh";
      break;
      case 23:
      pszName = "Qina";
      break;
      case 24:
      pszName = "Suhaj";
      break;
      case 26:
      pszName = "Janub Sina'";
      break;
      case 27:
      pszName = "Shamal Sina'";
      break;
    }
  }
  if (strcmp(country_code,"ER") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Anseba";
      break;
      case 2:
      pszName = "Debub";
      break;
      case 3:
      pszName = "Debubawi K'eyih Bahri";
      break;
      case 4:
      pszName = "Gash Barka";
      break;
      case 5:
      pszName = "Ma'akel";
      break;
      case 6:
      pszName = "Semenawi K'eyih Bahri";
      break;
    }
  }
  if (strcmp(country_code,"ES") == 0) {
    switch (region_code2) {
      case 7:
      pszName = "Islas Baleares";
      break;
      case 27:
      pszName = "La Rioja";
      break;
      case 29:
      pszName = "Madrid";
      break;
      case 31:
      pszName = "Murcia";
      break;
      case 32:
      pszName = "Navarra";
      break;
      case 34:
      pszName = "Asturias";
      break;
      case 39:
      pszName = "Cantabria";
      break;
      case 51:
      pszName = "Andalucia";
      break;
      case 52:
      pszName = "Aragon";
      break;
      case 53:
      pszName = "Canarias";
      break;
      case 54:
      pszName = "Castilla-La Mancha";
      break;
      case 55:
      pszName = "Castilla y Leon";
      break;
      case 56:
      pszName = "Catalonia";
      break;
      case 57:
      pszName = "Extremadura";
      break;
      case 58:
      pszName = "Galicia";
      break;
      case 59:
      pszName = "Pais Vasco";
      break;
      case 60:
      pszName = "Comunidad Valenciana";
      break;
    }
  }
  if (strcmp(country_code,"ET") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Amhara";
      break;
      case 7:
      pszName = "Somali";
      break;
      case 8:
      pszName = "Gambella";
      break;
      case 10:
      pszName = "Addis Abeba";
      break;
      case 11:
      pszName = "Southern";
      break;
      case 12:
      pszName = "Tigray";
      break;
      case 13:
      pszName = "Benishangul";
      break;
      case 14:
      pszName = "Afar";
      break;
      case 44:
      pszName = "Adis Abeba";
      break;
      case 45:
      pszName = "Afar";
      break;
      case 46:
      pszName = "Amara";
      break;
      case 47:
      pszName = "Binshangul Gumuz";
      break;
      case 48:
      pszName = "Dire Dawa";
      break;
      case 49:
      pszName = "Gambela Hizboch";
      break;
      case 50:
      pszName = "Hareri Hizb";
      break;
      case 51:
      pszName = "Oromiya";
      break;
      case 52:
      pszName = "Sumale";
      break;
      case 53:
      pszName = "Tigray";
      break;
      case 54:
      pszName = "YeDebub Biheroch Bihereseboch na Hizboch";
      break;
    }
  }
  if (strcmp(country_code,"FI") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aland";
      break;
      case 6:
      pszName = "Lapland";
      break;
      case 8:
      pszName = "Oulu";
      break;
      case 13:
      pszName = "Southern Finland";
      break;
      case 14:
      pszName = "Eastern Finland";
      break;
      case 15:
      pszName = "Western Finland";
      break;
    }
  }
  if (strcmp(country_code,"FJ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Central";
      break;
      case 2:
      pszName = "Eastern";
      break;
      case 3:
      pszName = "Northern";
      break;
      case 4:
      pszName = "Rotuma";
      break;
      case 5:
      pszName = "Western";
      break;
    }
  }
  if (strcmp(country_code,"FM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Kosrae";
      break;
      case 2:
      pszName = "Pohnpei";
      break;
      case 3:
      pszName = "Chuuk";
      break;
      case 4:
      pszName = "Yap";
      break;
    }
  }
  if (strcmp(country_code,"FR") == 0) {
    switch (region_code2) {
      case 97:
      pszName = "Aquitaine";
      break;
      case 98:
      pszName = "Auvergne";
      break;
      case 99:
      pszName = "Basse-Normandie";
      break;
      case 832:
      pszName = "Bourgogne";
      break;
      case 833:
      pszName = "Bretagne";
      break;
      case 834:
      pszName = "Centre";
      break;
      case 835:
      pszName = "Champagne-Ardenne";
      break;
      case 836:
      pszName = "Corse";
      break;
      case 837:
      pszName = "Franche-Comte";
      break;
      case 838:
      pszName = "Haute-Normandie";
      break;
      case 839:
      pszName = "Ile-de-France";
      break;
      case 840:
      pszName = "Languedoc-Roussillon";
      break;
      case 875:
      pszName = "Limousin";
      break;
      case 876:
      pszName = "Lorraine";
      break;
      case 877:
      pszName = "Midi-Pyrenees";
      break;
      case 878:
      pszName = "Nord-Pas-de-Calais";
      break;
      case 879:
      pszName = "Pays de la Loire";
      break;
      case 880:
      pszName = "Picardie";
      break;
      case 881:
      pszName = "Poitou-Charentes";
      break;
      case 882:
      pszName = "Provence-Alpes-Cote d'Azur";
      break;
      case 883:
      pszName = "Rhone-Alpes";
      break;
      case 918:
      pszName = "Alsace";
      break;
    }
  }
  if (strcmp(country_code,"GA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Estuaire";
      break;
      case 2:
      pszName = "Haut-Ogooue";
      break;
      case 3:
      pszName = "Moyen-Ogooue";
      break;
      case 4:
      pszName = "Ngounie";
      break;
      case 5:
      pszName = "Nyanga";
      break;
      case 6:
      pszName = "Ogooue-Ivindo";
      break;
      case 7:
      pszName = "Ogooue-Lolo";
      break;
      case 8:
      pszName = "Ogooue-Maritime";
      break;
      case 9:
      pszName = "Woleu-Ntem";
      break;
    }
  }
  if (strcmp(country_code,"GB") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Avon";
      break;
      case 3:
      pszName = "Berkshire";
      break;
      case 7:
      pszName = "Cleveland";
      break;
      case 17:
      pszName = "Greater London";
      break;
      case 18:
      pszName = "Greater Manchester";
      break;
      case 20:
      pszName = "Hereford and Worcester";
      break;
      case 22:
      pszName = "Humberside";
      break;
      case 28:
      pszName = "Merseyside";
      break;
      case 37:
      pszName = "South Yorkshire";
      break;
      case 41:
      pszName = "Tyne and Wear";
      break;
      case 43:
      pszName = "West Midlands";
      break;
      case 45:
      pszName = "West Yorkshire";
      break;
      case 79:
      pszName = "Central";
      break;
      case 82:
      pszName = "Grampian";
      break;
      case 84:
      pszName = "Lothian";
      break;
      case 87:
      pszName = "Strathclyde";
      break;
      case 88:
      pszName = "Tayside";
      break;
      case 90:
      pszName = "Clwyd";
      break;
      case 91:
      pszName = "Dyfed";
      break;
      case 92:
      pszName = "Gwent";
      break;
      case 94:
      pszName = "Mid Glamorgan";
      break;
      case 96:
      pszName = "South Glamorgan";
      break;
      case 97:
      pszName = "West Glamorgan";
      break;
      case 832:
      pszName = "Barking and Dagenham";
      break;
      case 833:
      pszName = "Barnet";
      break;
      case 834:
      pszName = "Barnsley";
      break;
      case 835:
      pszName = "Bath and North East Somerset";
      break;
      case 836:
      pszName = "Bedfordshire";
      break;
      case 837:
      pszName = "Bexley";
      break;
      case 838:
      pszName = "Birmingham";
      break;
      case 839:
      pszName = "Blackburn with Darwen";
      break;
      case 840:
      pszName = "Blackpool";
      break;
      case 875:
      pszName = "Bolton";
      break;
      case 876:
      pszName = "Bournemouth";
      break;
      case 877:
      pszName = "Bracknell Forest";
      break;
      case 878:
      pszName = "Bradford";
      break;
      case 879:
      pszName = "Brent";
      break;
      case 880:
      pszName = "Brighton and Hove";
      break;
      case 881:
      pszName = "Bristol, City of";
      break;
      case 882:
      pszName = "Bromley";
      break;
      case 883:
      pszName = "Buckinghamshire";
      break;
      case 918:
      pszName = "Bury";
      break;
      case 919:
      pszName = "Calderdale";
      break;
      case 920:
      pszName = "Cambridgeshire";
      break;
      case 921:
      pszName = "Camden";
      break;
      case 922:
      pszName = "Cheshire";
      break;
      case 923:
      pszName = "Cornwall";
      break;
      case 924:
      pszName = "Coventry";
      break;
      case 925:
      pszName = "Croydon";
      break;
      case 926:
      pszName = "Cumbria";
      break;
      case 961:
      pszName = "Darlington";
      break;
      case 962:
      pszName = "Derby";
      break;
      case 963:
      pszName = "Derbyshire";
      break;
      case 964:
      pszName = "Devon";
      break;
      case 965:
      pszName = "Doncaster";
      break;
      case 966:
      pszName = "Dorset";
      break;
      case 967:
      pszName = "Dudley";
      break;
      case 968:
      pszName = "Durham";
      break;
      case 969:
      pszName = "Ealing";
      break;
      case 1004:
      pszName = "East Riding of Yorkshire";
      break;
      case 1005:
      pszName = "East Sussex";
      break;
      case 1006:
      pszName = "Enfield";
      break;
      case 1007:
      pszName = "Essex";
      break;
      case 1008:
      pszName = "Gateshead";
      break;
      case 1009:
      pszName = "Gloucestershire";
      break;
      case 1010:
      pszName = "Greenwich";
      break;
      case 1011:
      pszName = "Hackney";
      break;
      case 1012:
      pszName = "Halton";
      break;
      case 1047:
      pszName = "Hammersmith and Fulham";
      break;
      case 1048:
      pszName = "Hampshire";
      break;
      case 1049:
      pszName = "Haringey";
      break;
      case 1050:
      pszName = "Harrow";
      break;
      case 1051:
      pszName = "Hartlepool";
      break;
      case 1052:
      pszName = "Havering";
      break;
      case 1053:
      pszName = "Herefordshire";
      break;
      case 1054:
      pszName = "Hertford";
      break;
      case 1055:
      pszName = "Hillingdon";
      break;
      case 1090:
      pszName = "Hounslow";
      break;
      case 1091:
      pszName = "Isle of Wight";
      break;
      case 1092:
      pszName = "Islington";
      break;
      case 1093:
      pszName = "Kensington and Chelsea";
      break;
      case 1094:
      pszName = "Kent";
      break;
      case 1095:
      pszName = "Kingston upon Hull, City of";
      break;
      case 1096:
      pszName = "Kingston upon Thames";
      break;
      case 1097:
      pszName = "Kirklees";
      break;
      case 1098:
      pszName = "Knowsley";
      break;
      case 1133:
      pszName = "Lambeth";
      break;
      case 1134:
      pszName = "Lancashire";
      break;
      case 1135:
      pszName = "Leeds";
      break;
      case 1136:
      pszName = "Leicester";
      break;
      case 1137:
      pszName = "Leicestershire";
      break;
      case 1138:
      pszName = "Lewisham";
      break;
      case 1139:
      pszName = "Lincolnshire";
      break;
      case 1140:
      pszName = "Liverpool";
      break;
      case 1141:
      pszName = "London, City of";
      break;
      case 1176:
      pszName = "Luton";
      break;
      case 1177:
      pszName = "Manchester";
      break;
      case 1178:
      pszName = "Medway";
      break;
      case 1179:
      pszName = "Merton";
      break;
      case 1180:
      pszName = "Middlesbrough";
      break;
      case 1181:
      pszName = "Milton Keynes";
      break;
      case 1182:
      pszName = "Newcastle upon Tyne";
      break;
      case 1183:
      pszName = "Newham";
      break;
      case 1184:
      pszName = "Norfolk";
      break;
      case 1219:
      pszName = "Northamptonshire";
      break;
      case 1220:
      pszName = "North East Lincolnshire";
      break;
      case 1221:
      pszName = "North Lincolnshire";
      break;
      case 1222:
      pszName = "North Somerset";
      break;
      case 1223:
      pszName = "North Tyneside";
      break;
      case 1224:
      pszName = "Northumberland";
      break;
      case 1225:
      pszName = "North Yorkshire";
      break;
      case 1226:
      pszName = "Nottingham";
      break;
      case 1227:
      pszName = "Nottinghamshire";
      break;
      case 1262:
      pszName = "Oldham";
      break;
      case 1263:
      pszName = "Oxfordshire";
      break;
      case 1264:
      pszName = "Peterborough";
      break;
      case 1265:
      pszName = "Plymouth";
      break;
      case 1266:
      pszName = "Poole";
      break;
      case 1267:
      pszName = "Portsmouth";
      break;
      case 1268:
      pszName = "Reading";
      break;
      case 1269:
      pszName = "Redbridge";
      break;
      case 1270:
      pszName = "Redcar and Cleveland";
      break;
      case 1305:
      pszName = "Richmond upon Thames";
      break;
      case 1306:
      pszName = "Rochdale";
      break;
      case 1307:
      pszName = "Rotherham";
      break;
      case 1308:
      pszName = "Rutland";
      break;
      case 1309:
      pszName = "Salford";
      break;
      case 1310:
      pszName = "Shropshire";
      break;
      case 1311:
      pszName = "Sandwell";
      break;
      case 1312:
      pszName = "Sefton";
      break;
      case 1313:
      pszName = "Sheffield";
      break;
      case 1348:
      pszName = "Slough";
      break;
      case 1349:
      pszName = "Solihull";
      break;
      case 1350:
      pszName = "Somerset";
      break;
      case 1351:
      pszName = "Southampton";
      break;
      case 1352:
      pszName = "Southend-on-Sea";
      break;
      case 1353:
      pszName = "South Gloucestershire";
      break;
      case 1354:
      pszName = "South Tyneside";
      break;
      case 1355:
      pszName = "Southwark";
      break;
      case 1356:
      pszName = "Staffordshire";
      break;
      case 1391:
      pszName = "St. Helens";
      break;
      case 1392:
      pszName = "Stockport";
      break;
      case 1393:
      pszName = "Stockton-on-Tees";
      break;
      case 1394:
      pszName = "Stoke-on-Trent";
      break;
      case 1395:
      pszName = "Suffolk";
      break;
      case 1396:
      pszName = "Sunderland";
      break;
      case 1397:
      pszName = "Surrey";
      break;
      case 1398:
      pszName = "Sutton";
      break;
      case 1399:
      pszName = "Swindon";
      break;
      case 1434:
      pszName = "Tameside";
      break;
      case 1435:
      pszName = "Telford and Wrekin";
      break;
      case 1436:
      pszName = "Thurrock";
      break;
      case 1437:
      pszName = "Torbay";
      break;
      case 1438:
      pszName = "Tower Hamlets";
      break;
      case 1439:
      pszName = "Trafford";
      break;
      case 1440:
      pszName = "Wakefield";
      break;
      case 1441:
      pszName = "Walsall";
      break;
      case 1442:
      pszName = "Waltham Forest";
      break;
      case 1477:
      pszName = "Wandsworth";
      break;
      case 1478:
      pszName = "Warrington";
      break;
      case 1479:
      pszName = "Warwickshire";
      break;
      case 1480:
      pszName = "West Berkshire";
      break;
      case 1481:
      pszName = "Westminster";
      break;
      case 1482:
      pszName = "West Sussex";
      break;
      case 1483:
      pszName = "Wigan";
      break;
      case 1484:
      pszName = "Wiltshire";
      break;
      case 1485:
      pszName = "Windsor and Maidenhead";
      break;
      case 1520:
      pszName = "Wirral";
      break;
      case 1521:
      pszName = "Wokingham";
      break;
      case 1522:
      pszName = "Wolverhampton";
      break;
      case 1523:
      pszName = "Worcestershire";
      break;
      case 1524:
      pszName = "York";
      break;
      case 1525:
      pszName = "Antrim";
      break;
      case 1526:
      pszName = "Ards";
      break;
      case 1527:
      pszName = "Armagh";
      break;
      case 1528:
      pszName = "Ballymena";
      break;
      case 1563:
      pszName = "Ballymoney";
      break;
      case 1564:
      pszName = "Banbridge";
      break;
      case 1565:
      pszName = "Belfast";
      break;
      case 1566:
      pszName = "Carrickfergus";
      break;
      case 1567:
      pszName = "Castlereagh";
      break;
      case 1568:
      pszName = "Coleraine";
      break;
      case 1569:
      pszName = "Cookstown";
      break;
      case 1570:
      pszName = "Craigavon";
      break;
      case 1571:
      pszName = "Down";
      break;
      case 1606:
      pszName = "Dungannon";
      break;
      case 1607:
      pszName = "Fermanagh";
      break;
      case 1608:
      pszName = "Larne";
      break;
      case 1609:
      pszName = "Limavady";
      break;
      case 1610:
      pszName = "Lisburn";
      break;
      case 1611:
      pszName = "Derry";
      break;
      case 1612:
      pszName = "Magherafelt";
      break;
      case 1613:
      pszName = "Moyle";
      break;
      case 1614:
      pszName = "Newry and Mourne";
      break;
      case 1649:
      pszName = "Newtownabbey";
      break;
      case 1650:
      pszName = "North Down";
      break;
      case 1651:
      pszName = "Omagh";
      break;
      case 1652:
      pszName = "Strabane";
      break;
      case 1653:
      pszName = "Aberdeen City";
      break;
      case 1654:
      pszName = "Aberdeenshire";
      break;
      case 1655:
      pszName = "Angus";
      break;
      case 1656:
      pszName = "Argyll and Bute";
      break;
      case 1657:
      pszName = "Scottish Borders, The";
      break;
      case 1692:
      pszName = "Clackmannanshire";
      break;
      case 1693:
      pszName = "Dumfries and Galloway";
      break;
      case 1694:
      pszName = "Dundee City";
      break;
      case 1695:
      pszName = "East Ayrshire";
      break;
      case 1696:
      pszName = "East Dunbartonshire";
      break;
      case 1697:
      pszName = "East Lothian";
      break;
      case 1698:
      pszName = "East Renfrewshire";
      break;
      case 1699:
      pszName = "Edinburgh, City of";
      break;
      case 1700:
      pszName = "Falkirk";
      break;
      case 1735:
      pszName = "Fife";
      break;
      case 1736:
      pszName = "Glasgow City";
      break;
      case 1737:
      pszName = "Highland";
      break;
      case 1738:
      pszName = "Inverclyde";
      break;
      case 1739:
      pszName = "Midlothian";
      break;
      case 1740:
      pszName = "Moray";
      break;
      case 1741:
      pszName = "North Ayrshire";
      break;
      case 1742:
      pszName = "North Lanarkshire";
      break;
      case 1743:
      pszName = "Orkney";
      break;
      case 1778:
      pszName = "Perth and Kinross";
      break;
      case 1779:
      pszName = "Renfrewshire";
      break;
      case 1780:
      pszName = "Shetland Islands";
      break;
      case 1781:
      pszName = "South Ayrshire";
      break;
      case 1782:
      pszName = "South Lanarkshire";
      break;
      case 1783:
      pszName = "Stirling";
      break;
      case 1784:
      pszName = "West Dunbartonshire";
      break;
      case 1785:
      pszName = "Eilean Siar";
      break;
      case 1786:
      pszName = "West Lothian";
      break;
      case 1821:
      pszName = "Isle of Anglesey";
      break;
      case 1822:
      pszName = "Blaenau Gwent";
      break;
      case 1823:
      pszName = "Bridgend";
      break;
      case 1824:
      pszName = "Caerphilly";
      break;
      case 1825:
      pszName = "Cardiff";
      break;
      case 1826:
      pszName = "Ceredigion";
      break;
      case 1827:
      pszName = "Carmarthenshire";
      break;
      case 1828:
      pszName = "Conwy";
      break;
      case 1829:
      pszName = "Denbighshire";
      break;
      case 1864:
      pszName = "Flintshire";
      break;
      case 1865:
      pszName = "Gwynedd";
      break;
      case 1866:
      pszName = "Merthyr Tydfil";
      break;
      case 1867:
      pszName = "Monmouthshire";
      break;
      case 1868:
      pszName = "Neath Port Talbot";
      break;
      case 1869:
      pszName = "Newport";
      break;
      case 1870:
      pszName = "Pembrokeshire";
      break;
      case 1871:
      pszName = "Powys";
      break;
      case 1872:
      pszName = "Rhondda Cynon Taff";
      break;
      case 1907:
      pszName = "Swansea";
      break;
      case 1908:
      pszName = "Torfaen";
      break;
      case 1909:
      pszName = "Vale of Glamorgan, The";
      break;
      case 1910:
      pszName = "Wrexham";
      break;
    }
  }
  if (strcmp(country_code,"GD") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Saint Andrew";
      break;
      case 2:
      pszName = "Saint David";
      break;
      case 3:
      pszName = "Saint George";
      break;
      case 4:
      pszName = "Saint John";
      break;
      case 5:
      pszName = "Saint Mark";
      break;
      case 6:
      pszName = "Saint Patrick";
      break;
    }
  }
  if (strcmp(country_code,"GE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Abashis Raioni";
      break;
      case 2:
      pszName = "Abkhazia";
      break;
      case 3:
      pszName = "Adigenis Raioni";
      break;
      case 4:
      pszName = "Ajaria";
      break;
      case 5:
      pszName = "Akhalgoris Raioni";
      break;
      case 6:
      pszName = "Akhalk'alak'is Raioni";
      break;
      case 7:
      pszName = "Akhalts'ikhis Raioni";
      break;
      case 8:
      pszName = "Akhmetis Raioni";
      break;
      case 9:
      pszName = "Ambrolauris Raioni";
      break;
      case 10:
      pszName = "Aspindzis Raioni";
      break;
      case 11:
      pszName = "Baghdat'is Raioni";
      break;
      case 12:
      pszName = "Bolnisis Raioni";
      break;
      case 13:
      pszName = "Borjomis Raioni";
      break;
      case 14:
      pszName = "Chiat'ura";
      break;
      case 15:
      pszName = "Ch'khorotsqus Raioni";
      break;
      case 16:
      pszName = "Ch'okhatauris Raioni";
      break;
      case 17:
      pszName = "Dedop'listsqaros Raioni";
      break;
      case 18:
      pszName = "Dmanisis Raioni";
      break;
      case 19:
      pszName = "Dushet'is Raioni";
      break;
      case 20:
      pszName = "Gardabanis Raioni";
      break;
      case 21:
      pszName = "Gori";
      break;
      case 22:
      pszName = "Goris Raioni";
      break;
      case 23:
      pszName = "Gurjaanis Raioni";
      break;
      case 24:
      pszName = "Javis Raioni";
      break;
      case 25:
      pszName = "K'arelis Raioni";
      break;
      case 26:
      pszName = "Kaspis Raioni";
      break;
      case 27:
      pszName = "Kharagaulis Raioni";
      break;
      case 28:
      pszName = "Khashuris Raioni";
      break;
      case 29:
      pszName = "Khobis Raioni";
      break;
      case 30:
      pszName = "Khonis Raioni";
      break;
      case 31:
      pszName = "K'ut'aisi";
      break;
      case 32:
      pszName = "Lagodekhis Raioni";
      break;
      case 33:
      pszName = "Lanch'khut'is Raioni";
      break;
      case 34:
      pszName = "Lentekhis Raioni";
      break;
      case 35:
      pszName = "Marneulis Raioni";
      break;
      case 36:
      pszName = "Martvilis Raioni";
      break;
      case 37:
      pszName = "Mestiis Raioni";
      break;
      case 38:
      pszName = "Mts'khet'is Raioni";
      break;
      case 39:
      pszName = "Ninotsmindis Raioni";
      break;
      case 40:
      pszName = "Onis Raioni";
      break;
      case 41:
      pszName = "Ozurget'is Raioni";
      break;
      case 42:
      pszName = "P'ot'i";
      break;
      case 43:
      pszName = "Qazbegis Raioni";
      break;
      case 44:
      pszName = "Qvarlis Raioni";
      break;
      case 45:
      pszName = "Rust'avi";
      break;
      case 46:
      pszName = "Sach'kheris Raioni";
      break;
      case 47:
      pszName = "Sagarejos Raioni";
      break;
      case 48:
      pszName = "Samtrediis Raioni";
      break;
      case 49:
      pszName = "Senakis Raioni";
      break;
      case 50:
      pszName = "Sighnaghis Raioni";
      break;
      case 51:
      pszName = "T'bilisi";
      break;
      case 52:
      pszName = "T'elavis Raioni";
      break;
      case 53:
      pszName = "T'erjolis Raioni";
      break;
      case 54:
      pszName = "T'et'ritsqaros Raioni";
      break;
      case 55:
      pszName = "T'ianet'is Raioni";
      break;
      case 56:
      pszName = "Tqibuli";
      break;
      case 57:
      pszName = "Ts'ageris Raioni";
      break;
      case 58:
      pszName = "Tsalenjikhis Raioni";
      break;
      case 59:
      pszName = "Tsalkis Raioni";
      break;
      case 60:
      pszName = "Tsqaltubo";
      break;
      case 61:
      pszName = "Vanis Raioni";
      break;
      case 62:
      pszName = "Zestap'onis Raioni";
      break;
      case 63:
      pszName = "Zugdidi";
      break;
      case 64:
      pszName = "Zugdidis Raioni";
      break;
    }
  }
  if (strcmp(country_code,"GH") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Greater Accra";
      break;
      case 2:
      pszName = "Ashanti";
      break;
      case 3:
      pszName = "Brong-Ahafo";
      break;
      case 4:
      pszName = "Central";
      break;
      case 5:
      pszName = "Eastern";
      break;
      case 6:
      pszName = "Northern";
      break;
      case 8:
      pszName = "Volta";
      break;
      case 9:
      pszName = "Western";
      break;
      case 10:
      pszName = "Upper East";
      break;
      case 11:
      pszName = "Upper West";
      break;
    }
  }
  if (strcmp(country_code,"GL") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Nordgronland";
      break;
      case 2:
      pszName = "Ostgronland";
      break;
      case 3:
      pszName = "Vestgronland";
      break;
    }
  }
  if (strcmp(country_code,"GM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Banjul";
      break;
      case 2:
      pszName = "Lower River";
      break;
      case 3:
      pszName = "Central River";
      break;
      case 4:
      pszName = "Upper River";
      break;
      case 5:
      pszName = "Western";
      break;
      case 7:
      pszName = "North Bank";
      break;
    }
  }
  if (strcmp(country_code,"GN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Beyla";
      break;
      case 2:
      pszName = "Boffa";
      break;
      case 3:
      pszName = "Boke";
      break;
      case 4:
      pszName = "Conakry";
      break;
      case 5:
      pszName = "Dabola";
      break;
      case 6:
      pszName = "Dalaba";
      break;
      case 7:
      pszName = "Dinguiraye";
      break;
      case 9:
      pszName = "Faranah";
      break;
      case 10:
      pszName = "Forecariah";
      break;
      case 11:
      pszName = "Fria";
      break;
      case 12:
      pszName = "Gaoual";
      break;
      case 13:
      pszName = "Gueckedou";
      break;
      case 15:
      pszName = "Kerouane";
      break;
      case 16:
      pszName = "Kindia";
      break;
      case 17:
      pszName = "Kissidougou";
      break;
      case 18:
      pszName = "Koundara";
      break;
      case 19:
      pszName = "Kouroussa";
      break;
      case 21:
      pszName = "Macenta";
      break;
      case 22:
      pszName = "Mali";
      break;
      case 23:
      pszName = "Mamou";
      break;
      case 25:
      pszName = "Pita";
      break;
      case 27:
      pszName = "Telimele";
      break;
      case 28:
      pszName = "Tougue";
      break;
      case 29:
      pszName = "Yomou";
      break;
      case 30:
      pszName = "Coyah";
      break;
      case 31:
      pszName = "Dubreka";
      break;
      case 32:
      pszName = "Kankan";
      break;
      case 33:
      pszName = "Koubia";
      break;
      case 34:
      pszName = "Labe";
      break;
      case 35:
      pszName = "Lelouma";
      break;
      case 36:
      pszName = "Lola";
      break;
      case 37:
      pszName = "Mandiana";
      break;
      case 38:
      pszName = "Nzerekore";
      break;
      case 39:
      pszName = "Siguiri";
      break;
    }
  }
  if (strcmp(country_code,"GQ") == 0) {
    switch (region_code2) {
      case 3:
      pszName = "Annobon";
      break;
      case 4:
      pszName = "Bioko Norte";
      break;
      case 5:
      pszName = "Bioko Sur";
      break;
      case 6:
      pszName = "Centro Sur";
      break;
      case 7:
      pszName = "Kie-Ntem";
      break;
      case 8:
      pszName = "Litoral";
      break;
      case 9:
      pszName = "Wele-Nzas";
      break;
    }
  }
  if (strcmp(country_code,"GR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Evros";
      break;
      case 2:
      pszName = "Rodhopi";
      break;
      case 3:
      pszName = "Xanthi";
      break;
      case 4:
      pszName = "Drama";
      break;
      case 5:
      pszName = "Serrai";
      break;
      case 6:
      pszName = "Kilkis";
      break;
      case 7:
      pszName = "Pella";
      break;
      case 8:
      pszName = "Florina";
      break;
      case 9:
      pszName = "Kastoria";
      break;
      case 10:
      pszName = "Grevena";
      break;
      case 11:
      pszName = "Kozani";
      break;
      case 12:
      pszName = "Imathia";
      break;
      case 13:
      pszName = "Thessaloniki";
      break;
      case 14:
      pszName = "Kavala";
      break;
      case 15:
      pszName = "Khalkidhiki";
      break;
      case 16:
      pszName = "Pieria";
      break;
      case 17:
      pszName = "Ioannina";
      break;
      case 18:
      pszName = "Thesprotia";
      break;
      case 19:
      pszName = "Preveza";
      break;
      case 20:
      pszName = "Arta";
      break;
      case 21:
      pszName = "Larisa";
      break;
      case 22:
      pszName = "Trikala";
      break;
      case 23:
      pszName = "Kardhitsa";
      break;
      case 24:
      pszName = "Magnisia";
      break;
      case 25:
      pszName = "Kerkira";
      break;
      case 26:
      pszName = "Levkas";
      break;
      case 27:
      pszName = "Kefallinia";
      break;
      case 28:
      pszName = "Zakinthos";
      break;
      case 29:
      pszName = "Fthiotis";
      break;
      case 30:
      pszName = "Evritania";
      break;
      case 31:
      pszName = "Aitolia kai Akarnania";
      break;
      case 32:
      pszName = "Fokis";
      break;
      case 33:
      pszName = "Voiotia";
      break;
      case 34:
      pszName = "Evvoia";
      break;
      case 35:
      pszName = "Attiki";
      break;
      case 36:
      pszName = "Argolis";
      break;
      case 37:
      pszName = "Korinthia";
      break;
      case 38:
      pszName = "Akhaia";
      break;
      case 39:
      pszName = "Ilia";
      break;
      case 40:
      pszName = "Messinia";
      break;
      case 41:
      pszName = "Arkadhia";
      break;
      case 42:
      pszName = "Lakonia";
      break;
      case 43:
      pszName = "Khania";
      break;
      case 44:
      pszName = "Rethimni";
      break;
      case 45:
      pszName = "Iraklion";
      break;
      case 46:
      pszName = "Lasithi";
      break;
      case 47:
      pszName = "Dhodhekanisos";
      break;
      case 48:
      pszName = "Samos";
      break;
      case 49:
      pszName = "Kikladhes";
      break;
      case 50:
      pszName = "Khios";
      break;
      case 51:
      pszName = "Lesvos";
      break;
    }
  }
  if (strcmp(country_code,"GT") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Alta Verapaz";
      break;
      case 2:
      pszName = "Baja Verapaz";
      break;
      case 3:
      pszName = "Chimaltenango";
      break;
      case 4:
      pszName = "Chiquimula";
      break;
      case 5:
      pszName = "El Progreso";
      break;
      case 6:
      pszName = "Esc::u32la";
      break;
      case 7:
      pszName = "Guatemala";
      break;
      case 8:
      pszName = "Huehuetenango";
      break;
      case 9:
      pszName = "Izabal";
      break;
      case 10:
      pszName = "Jalapa";
      break;
      case 11:
      pszName = "Jutiapa";
      break;
      case 12:
      pszName = "Peten";
      break;
      case 13:
      pszName = "Quetzaltenango";
      break;
      case 14:
      pszName = "Quiche";
      break;
      case 15:
      pszName = "Retalhuleu";
      break;
      case 16:
      pszName = "Sacatepequez";
      break;
      case 17:
      pszName = "San Marcos";
      break;
      case 18:
      pszName = "Santa Rosa";
      break;
      case 19:
      pszName = "Solola";
      break;
      case 20:
      pszName = "Suchitepequez";
      break;
      case 21:
      pszName = "Totonicapan";
      break;
      case 22:
      pszName = "Zacapa";
      break;
    }
  }
  if (strcmp(country_code,"GW") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bafata";
      break;
      case 2:
      pszName = "Quinara";
      break;
      case 4:
      pszName = "Oio";
      break;
      case 5:
      pszName = "Bolama";
      break;
      case 6:
      pszName = "Cacheu";
      break;
      case 7:
      pszName = "Tombali";
      break;
      case 10:
      pszName = "Gabu";
      break;
      case 11:
      pszName = "Bissau";
      break;
      case 12:
      pszName = "Biombo";
      break;
    }
  }
  if (strcmp(country_code,"GY") == 0) {
    switch (region_code2) {
      case 10:
      pszName = "Barima-Waini";
      break;
      case 11:
      pszName = "Cuyuni-Mazaruni";
      break;
      case 12:
      pszName = "Demerara-Mahaica";
      break;
      case 13:
      pszName = "East Berbice-Corentyne";
      break;
      case 14:
      pszName = "Essequibo Islands-West Demerara";
      break;
      case 15:
      pszName = "Mahaica-Berbice";
      break;
      case 16:
      pszName = "Pomeroon-Supenaam";
      break;
      case 17:
      pszName = "Potaro-Siparuni";
      break;
      case 18:
      pszName = "Upper Demerara-Berbice";
      break;
      case 19:
      pszName = "Upper Takutu-Upper Essequibo";
      break;
    }
  }
  if (strcmp(country_code,"HN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "ca_antida";
      break;
      case 2:
      pszName = "Choluteca";
      break;
      case 3:
      pszName = "Colon";
      break;
      case 4:
      pszName = "Comayagua";
      break;
      case 5:
      pszName = "Copan";
      break;
      case 6:
      pszName = "Cortes";
      break;
      case 7:
      pszName = "El Paraiso";
      break;
      case 8:
      pszName = "Francisco Morazan";
      break;
      case 9:
      pszName = "Gracias a Dios";
      break;
      case 10:
      pszName = "Intibuca";
      break;
      case 11:
      pszName = "Islas de la Bahia";
      break;
      case 12:
      pszName = "La Paz";
      break;
      case 13:
      pszName = "Lempira";
      break;
      case 14:
      pszName = "Ocotepeque";
      break;
      case 15:
      pszName = "Olancho";
      break;
      case 16:
      pszName = "Santa Barbara";
      break;
      case 17:
      pszName = "Valle";
      break;
      case 18:
      pszName = "Yoro";
      break;
    }
  }
  if (strcmp(country_code,"HR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bjelovarsko-Bilogorska";
      break;
      case 2:
      pszName = "Brodsko-Posavska";
      break;
      case 3:
      pszName = "Dubrovacko-Neretvanska";
      break;
      case 4:
      pszName = "Istarska";
      break;
      case 5:
      pszName = "Karlovacka";
      break;
      case 6:
      pszName = "Koprivnicko-Krizevacka";
      break;
      case 7:
      pszName = "Krapinsko-Zagorska";
      break;
      case 8:
      pszName = "Licko-Senjska";
      break;
      case 9:
      pszName = "Medimurska";
      break;
      case 10:
      pszName = "Osjecko-Baranjska";
      break;
      case 11:
      pszName = "Pozesko-Slavonska";
      break;
      case 12:
      pszName = "Primorsko-Goranska";
      break;
      case 13:
      pszName = "Sibensko-Kninska";
      break;
      case 14:
      pszName = "Sisacko-Moslavacka";
      break;
      case 15:
      pszName = "Splitsko-Dalmatinska";
      break;
      case 16:
      pszName = "Varazdinska";
      break;
      case 17:
      pszName = "Viroviticko-Podravska";
      break;
      case 18:
      pszName = "Vukovarsko-Srijemska";
      break;
      case 19:
      pszName = "Zadarska";
      break;
      case 20:
      pszName = "Zagrebacka";
      break;
      case 21:
      pszName = "Grad Zagreb";
      break;
    }
  }
  if (strcmp(country_code,"HT") == 0) {
    switch (region_code2) {
      case 3:
      pszName = "Nord-Ouest";
      break;
      case 6:
      pszName = "Artibonite";
      break;
      case 7:
      pszName = "Centre";
      break;
      case 9:
      pszName = "Nord";
      break;
      case 10:
      pszName = "Nord-Est";
      break;
      case 11:
      pszName = "Ouest";
      break;
      case 12:
      pszName = "Sud";
      break;
      case 13:
      pszName = "Sud-Est";
      break;
      case 14:
      pszName = "Grand' Anse";
      break;
      case 15:
      pszName = "Nippes";
      break;
    }
  }
  if (strcmp(country_code,"HU") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bacs-Kiskun";
      break;
      case 2:
      pszName = "Baranya";
      break;
      case 3:
      pszName = "Bekes";
      break;
      case 4:
      pszName = "Borsod-Abauj-Zemplen";
      break;
      case 5:
      pszName = "Budapest";
      break;
      case 6:
      pszName = "Csongrad";
      break;
      case 7:
      pszName = "Debrecen";
      break;
      case 8:
      pszName = "Fejer";
      break;
      case 9:
      pszName = "Gyor-Moson-Sopron";
      break;
      case 10:
      pszName = "Hajdu-Bihar";
      break;
      case 11:
      pszName = "Heves";
      break;
      case 12:
      pszName = "Komarom-Esztergom";
      break;
      case 13:
      pszName = "Miskolc";
      break;
      case 14:
      pszName = "Nograd";
      break;
      case 15:
      pszName = "Pecs";
      break;
      case 16:
      pszName = "Pest";
      break;
      case 17:
      pszName = "Somogy";
      break;
      case 18:
      pszName = "Szabolcs-Szatmar-Bereg";
      break;
      case 19:
      pszName = "Szeged";
      break;
      case 20:
      pszName = "Jasz-Nagykun-Szolnok";
      break;
      case 21:
      pszName = "Tolna";
      break;
      case 22:
      pszName = "Vas";
      break;
      case 23:
      pszName = "Veszprem";
      break;
      case 24:
      pszName = "Zala";
      break;
      case 25:
      pszName = "Gyor";
      break;
      case 26:
      pszName = "Bekescsaba";
      break;
      case 27:
      pszName = "Dunaujvaros";
      break;
      case 28:
      pszName = "Eger";
      break;
      case 29:
      pszName = "Hodmezovasarhely";
      break;
      case 30:
      pszName = "Kaposvar";
      break;
      case 31:
      pszName = "Kecskemet";
      break;
      case 32:
      pszName = "Nagykanizsa";
      break;
      case 33:
      pszName = "Nyiregyhaza";
      break;
      case 34:
      pszName = "Sopron";
      break;
      case 35:
      pszName = "Szekesfehervar";
      break;
      case 36:
      pszName = "Szolnok";
      break;
      case 37:
      pszName = "Szombathely";
      break;
      case 38:
      pszName = "Tatabanya";
      break;
      case 39:
      pszName = "Veszprem";
      break;
      case 40:
      pszName = "Zalaegerszeg";
      break;
      case 41:
      pszName = "Salgotarjan";
      break;
      case 42:
      pszName = "Szekszard";
      break;
    }
  }
  if (strcmp(country_code,"ID") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aceh";
      break;
      case 2:
      pszName = "Bali";
      break;
      case 3:
      pszName = "Bengkulu";
      break;
      case 4:
      pszName = "Jakarta Raya";
      break;
      case 5:
      pszName = "Jambi";
      break;
      case 6:
      pszName = "Jawa Barat";
      break;
      case 7:
      pszName = "Jawa Tengah";
      break;
      case 8:
      pszName = "Jawa Timur";
      break;
      case 9:
      pszName = "Papua";
      break;
      case 10:
      pszName = "Yogyakarta";
      break;
      case 11:
      pszName = "Kalimantan Barat";
      break;
      case 12:
      pszName = "Kalimantan Selatan";
      break;
      case 13:
      pszName = "Kalimantan Tengah";
      break;
      case 14:
      pszName = "Kalimantan Timur";
      break;
      case 15:
      pszName = "Lampung";
      break;
      case 16:
      pszName = "Maluku";
      break;
      case 17:
      pszName = "Nusa Tenggara Barat";
      break;
      case 18:
      pszName = "Nusa Tenggara Timur";
      break;
      case 19:
      pszName = "Riau";
      break;
      case 20:
      pszName = "Sulawesi Selatan";
      break;
      case 21:
      pszName = "Sulawesi Tengah";
      break;
      case 22:
      pszName = "Sulawesi Tenggara";
      break;
      case 23:
      pszName = "Sulawesi Utara";
      break;
      case 24:
      pszName = "Sumatera Barat";
      break;
      case 25:
      pszName = "Sumatera Selatan";
      break;
      case 26:
      pszName = "Sumatera Utara";
      break;
      case 28:
      pszName = "Maluku";
      break;
      case 29:
      pszName = "Maluku Utara";
      break;
      case 30:
      pszName = "Jawa Barat";
      break;
      case 31:
      pszName = "Sulawesi Utara";
      break;
      case 32:
      pszName = "Sumatera Selatan";
      break;
      case 33:
      pszName = "Banten";
      break;
      case 34:
      pszName = "Gorontalo";
      break;
      case 35:
      pszName = "Kepulauan Bangka Belitung";
      break;
      case 36:
      pszName = "Papua";
      break;
      case 37:
      pszName = "Riau";
      break;
      case 38:
      pszName = "Sulawesi Selatan";
      break;
      case 39:
      pszName = "Irian Jaya Barat";
      break;
      case 40:
      pszName = "Kepulauan Riau";
      break;
      case 41:
      pszName = "Sulawesi Barat";
      break;
    }
  }
  if (strcmp(country_code,"IE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Carlow";
      break;
      case 2:
      pszName = "Cavan";
      break;
      case 3:
      pszName = "Clare";
      break;
      case 4:
      pszName = "Cork";
      break;
      case 6:
      pszName = "Donegal";
      break;
      case 7:
      pszName = "Dublin";
      break;
      case 10:
      pszName = "Galway";
      break;
      case 11:
      pszName = "Kerry";
      break;
      case 12:
      pszName = "Kildare";
      break;
      case 13:
      pszName = "Kilkenny";
      break;
      case 14:
      pszName = "Leitrim";
      break;
      case 15:
      pszName = "Laois";
      break;
      case 16:
      pszName = "Limerick";
      break;
      case 18:
      pszName = "Longford";
      break;
      case 19:
      pszName = "Louth";
      break;
      case 20:
      pszName = "Mayo";
      break;
      case 21:
      pszName = "Meath";
      break;
      case 22:
      pszName = "Monaghan";
      break;
      case 23:
      pszName = "Offaly";
      break;
      case 24:
      pszName = "Roscommon";
      break;
      case 25:
      pszName = "Sligo";
      break;
      case 26:
      pszName = "Tipperary";
      break;
      case 27:
      pszName = "Waterford";
      break;
      case 29:
      pszName = "Westmeath";
      break;
      case 30:
      pszName = "Wexford";
      break;
      case 31:
      pszName = "Wicklow";
      break;
    }
  }
  if (strcmp(country_code,"IL") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "HaDarom";
      break;
      case 2:
      pszName = "HaMerkaz";
      break;
      case 3:
      pszName = "HaZafon";
      break;
      case 4:
      pszName = "Hefa";
      break;
      case 5:
      pszName = "Tel Aviv";
      break;
      case 6:
      pszName = "Yerushalayim";
      break;
    }
  }
  if (strcmp(country_code,"IN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Andaman and Nicobar Islands";
      break;
      case 2:
      pszName = "Andhra Pradesh";
      break;
      case 3:
      pszName = "Assam";
      break;
      case 5:
      pszName = "Chandigarh";
      break;
      case 6:
      pszName = "Dadra and Nagar Haveli";
      break;
      case 7:
      pszName = "Delhi";
      break;
      case 9:
      pszName = "Gujarat";
      break;
      case 10:
      pszName = "Haryana";
      break;
      case 11:
      pszName = "Himachal Pradesh";
      break;
      case 12:
      pszName = "Jammu and Kashmir";
      break;
      case 13:
      pszName = "Kerala";
      break;
      case 14:
      pszName = "Lakshadweep";
      break;
      case 16:
      pszName = "Maharashtra";
      break;
      case 17:
      pszName = "Manipur";
      break;
      case 18:
      pszName = "Meghalaya";
      break;
      case 19:
      pszName = "Karnataka";
      break;
      case 20:
      pszName = "Nagaland";
      break;
      case 21:
      pszName = "Orissa";
      break;
      case 22:
      pszName = "Puducherry";
      break;
      case 23:
      pszName = "Punjab";
      break;
      case 24:
      pszName = "Rajasthan";
      break;
      case 25:
      pszName = "Tamil Nadu";
      break;
      case 26:
      pszName = "Tripura";
      break;
      case 28:
      pszName = "West Bengal";
      break;
      case 29:
      pszName = "Sikkim";
      break;
      case 30:
      pszName = "Arunachal Pradesh";
      break;
      case 31:
      pszName = "Mizoram";
      break;
      case 32:
      pszName = "Daman and Diu";
      break;
      case 33:
      pszName = "Goa";
      break;
      case 34:
      pszName = "Bihar";
      break;
      case 35:
      pszName = "Madhya Pradesh";
      break;
      case 36:
      pszName = "Uttar Pradesh";
      break;
      case 37:
      pszName = "Chhattisgarh";
      break;
      case 38:
      pszName = "Jharkhand";
      break;
      case 39:
      pszName = "Uttarakhand";
      break;
    }
  }
  if (strcmp(country_code,"IQ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Al Anbar";
      break;
      case 2:
      pszName = "Al Basrah";
      break;
      case 3:
      pszName = "Al Muthanna";
      break;
      case 4:
      pszName = "Al Qadisiyah";
      break;
      case 5:
      pszName = "As Sulaymaniyah";
      break;
      case 6:
      pszName = "Babil";
      break;
      case 7:
      pszName = "Baghdad";
      break;
      case 8:
      pszName = "Dahuk";
      break;
      case 9:
      pszName = "Dhi Qar";
      break;
      case 10:
      pszName = "Diyala";
      break;
      case 11:
      pszName = "Arbil";
      break;
      case 12:
      pszName = "Karbala'";
      break;
      case 13:
      pszName = "At Ta'mim";
      break;
      case 14:
      pszName = "Maysan";
      break;
      case 15:
      pszName = "Ninawa";
      break;
      case 16:
      pszName = "Wasit";
      break;
      case 17:
      pszName = "An Najaf";
      break;
      case 18:
      pszName = "Salah ad Din";
      break;
    }
  }
  if (strcmp(country_code,"IR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Azarbayjan-e Bakhtari";
      break;
      case 2:
      pszName = "Azarbayjan-e Khavari";
      break;
      case 3:
      pszName = "Chahar Mahall va Bakhtiari";
      break;
      case 4:
      pszName = "Sistan va Baluchestan";
      break;
      case 5:
      pszName = "Kohkiluyeh va Buyer Ahmadi";
      break;
      case 7:
      pszName = "Fars";
      break;
      case 8:
      pszName = "Gilan";
      break;
      case 9:
      pszName = "Hamadan";
      break;
      case 10:
      pszName = "Ilam";
      break;
      case 11:
      pszName = "Hormozgan";
      break;
      case 12:
      pszName = "Kerman";
      break;
      case 13:
      pszName = "Bakhtaran";
      break;
      case 15:
      pszName = "Khuzestan";
      break;
      case 16:
      pszName = "Kordestan";
      break;
      case 17:
      pszName = "Mazandaran";
      break;
      case 18:
      pszName = "Semnan Province";
      break;
      case 19:
      pszName = "Markazi";
      break;
      case 21:
      pszName = "Zanjan";
      break;
      case 22:
      pszName = "Bushehr";
      break;
      case 23:
      pszName = "Lorestan";
      break;
      case 24:
      pszName = "Markazi";
      break;
      case 25:
      pszName = "Semnan";
      break;
      case 26:
      pszName = "Tehran";
      break;
      case 27:
      pszName = "Zanjan";
      break;
      case 28:
      pszName = "Esfahan";
      break;
      case 29:
      pszName = "Kerman";
      break;
      case 30:
      pszName = "Khorasan";
      break;
      case 31:
      pszName = "Yazd";
      break;
      case 32:
      pszName = "Ardabil";
      break;
      case 33:
      pszName = "East Azarbaijan";
      break;
      case 34:
      pszName = "Markazi";
      break;
      case 35:
      pszName = "Mazandaran";
      break;
      case 36:
      pszName = "Zanjan";
      break;
      case 37:
      pszName = "Golestan";
      break;
      case 38:
      pszName = "Qazvin";
      break;
      case 39:
      pszName = "Qom";
      break;
      case 40:
      pszName = "Yazd";
      break;
      case 41:
      pszName = "Khorasan-e Janubi";
      break;
      case 42:
      pszName = "Khorasan-e Razavi";
      break;
      case 43:
      pszName = "Khorasan-e Shemali";
      break;
    }
  }
  if (strcmp(country_code,"IS") == 0) {
    switch (region_code2) {
      case 3:
      pszName = "Arnessysla";
      break;
      case 5:
      pszName = "Austur-Hunavatnssysla";
      break;
      case 6:
      pszName = "Austur-Skaftafellssysla";
      break;
      case 7:
      pszName = "Borgarfjardarsysla";
      break;
      case 9:
      pszName = "Eyjafjardarsysla";
      break;
      case 10:
      pszName = "Gullbringusysla";
      break;
      case 15:
      pszName = "Kjosarsysla";
      break;
      case 17:
      pszName = "Myrasysla";
      break;
      case 20:
      pszName = "Nordur-Mulasysla";
      break;
      case 21:
      pszName = "Nordur-Tingeyjarsysla";
      break;
      case 23:
      pszName = "Rangarvallasysla";
      break;
      case 28:
      pszName = "Skagafjardarsysla";
      break;
      case 29:
      pszName = "Snafellsnes- og Hnappadalssysla";
      break;
      case 31:
      pszName = "Sudur-Mulasysla";
      break;
      case 32:
      pszName = "Sudur-Tingeyjarsysla";
      break;
      case 34:
      pszName = "Vestur-Bardastrandarsysla";
      break;
      case 35:
      pszName = "Vestur-Hunavatnssysla";
      break;
      case 36:
      pszName = "Vestur-Isafjardarsysla";
      break;
      case 37:
      pszName = "Vestur-Skaftafellssysla";
      break;
      case 40:
      pszName = "Norourland Eystra";
      break;
      case 41:
      pszName = "Norourland Vestra";
      break;
      case 42:
      pszName = "Suourland";
      break;
      case 43:
      pszName = "Suournes";
      break;
      case 44:
      pszName = "Vestfiroir";
      break;
      case 45:
      pszName = "Vesturland";
      break;
    }
  }
  if (strcmp(country_code,"IT") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Abruzzi";
      break;
      case 2:
      pszName = "Basilicata";
      break;
      case 3:
      pszName = "Calabria";
      break;
      case 4:
      pszName = "Campania";
      break;
      case 5:
      pszName = "Emilia-Romagna";
      break;
      case 6:
      pszName = "Friuli-Venezia Giulia";
      break;
      case 7:
      pszName = "Lazio";
      break;
      case 8:
      pszName = "Liguria";
      break;
      case 9:
      pszName = "Lombardia";
      break;
      case 10:
      pszName = "Marche";
      break;
      case 11:
      pszName = "Molise";
      break;
      case 12:
      pszName = "Piemonte";
      break;
      case 13:
      pszName = "Puglia";
      break;
      case 14:
      pszName = "Sardegna";
      break;
      case 15:
      pszName = "Sicilia";
      break;
      case 16:
      pszName = "Toscana";
      break;
      case 17:
      pszName = "Trentino-Alto Adige";
      break;
      case 18:
      pszName = "Umbria";
      break;
      case 19:
      pszName = "Valle d'Aosta";
      break;
      case 20:
      pszName = "Veneto";
      break;
    }
  }
  if (strcmp(country_code,"JM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Clarendon";
      break;
      case 2:
      pszName = "Hanover";
      break;
      case 4:
      pszName = "Manchester";
      break;
      case 7:
      pszName = "Portland";
      break;
      case 8:
      pszName = "Saint Andrew";
      break;
      case 9:
      pszName = "Saint Ann";
      break;
      case 10:
      pszName = "Saint Catherine";
      break;
      case 11:
      pszName = "Saint Elizabeth";
      break;
      case 12:
      pszName = "Saint James";
      break;
      case 13:
      pszName = "Saint Mary";
      break;
      case 14:
      pszName = "Saint Thomas";
      break;
      case 15:
      pszName = "Trelawny";
      break;
      case 16:
      pszName = "Westmoreland";
      break;
      case 17:
      pszName = "Kingston";
      break;
    }
  }
  if (strcmp(country_code,"JO") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Al Balqa'";
      break;
      case 7:
      pszName = "Ma";
      break;
      case 9:
      pszName = "Al Karak";
      break;
      case 10:
      pszName = "Al Mafraq";
      break;
      case 11:
      pszName = "Amman Governorate";
      break;
      case 12:
      pszName = "At Tafilah";
      break;
      case 13:
      pszName = "Az Zarqa";
      break;
      case 14:
      pszName = "Irbid";
      break;
      case 16:
      pszName = "Amman";
      break;
    }
  }
  if (strcmp(country_code,"JP") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aichi";
      break;
      case 2:
      pszName = "Akita";
      break;
      case 3:
      pszName = "Aomori";
      break;
      case 4:
      pszName = "Chiba";
      break;
      case 5:
      pszName = "Ehime";
      break;
      case 6:
      pszName = "Fukui";
      break;
      case 7:
      pszName = "Fukuoka";
      break;
      case 8:
      pszName = "Fukushima";
      break;
      case 9:
      pszName = "Gifu";
      break;
      case 10:
      pszName = "Gumma";
      break;
      case 11:
      pszName = "Hiroshima";
      break;
      case 12:
      pszName = "Hokkaido";
      break;
      case 13:
      pszName = "Hyogo";
      break;
      case 14:
      pszName = "Ibaraki";
      break;
      case 15:
      pszName = "Ishikawa";
      break;
      case 16:
      pszName = "Iwate";
      break;
      case 17:
      pszName = "Kagawa";
      break;
      case 18:
      pszName = "Kagoshima";
      break;
      case 19:
      pszName = "Kanagawa";
      break;
      case 20:
      pszName = "Kochi";
      break;
      case 21:
      pszName = "Kumamoto";
      break;
      case 22:
      pszName = "Kyoto";
      break;
      case 23:
      pszName = "Mie";
      break;
      case 24:
      pszName = "Miyagi";
      break;
      case 25:
      pszName = "Miyazaki";
      break;
      case 26:
      pszName = "Nagano";
      break;
      case 27:
      pszName = "Nagasaki";
      break;
      case 28:
      pszName = "Nara";
      break;
      case 29:
      pszName = "Niigata";
      break;
      case 30:
      pszName = "Oita";
      break;
      case 31:
      pszName = "Okayama";
      break;
      case 32:
      pszName = "Osaka";
      break;
      case 33:
      pszName = "Saga";
      break;
      case 34:
      pszName = "Saitama";
      break;
      case 35:
      pszName = "Shiga";
      break;
      case 36:
      pszName = "Shimane";
      break;
      case 37:
      pszName = "Shizuoka";
      break;
      case 38:
      pszName = "Tochigi";
      break;
      case 39:
      pszName = "Tokushima";
      break;
      case 40:
      pszName = "Tokyo";
      break;
      case 41:
      pszName = "Tottori";
      break;
      case 42:
      pszName = "Toyama";
      break;
      case 43:
      pszName = "Wakayama";
      break;
      case 44:
      pszName = "Yamagata";
      break;
      case 45:
      pszName = "Yamaguchi";
      break;
      case 46:
      pszName = "Yamanashi";
      break;
      case 47:
      pszName = "Okinawa";
      break;
    }
  }
  if (strcmp(country_code,"KE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Central";
      break;
      case 2:
      pszName = "Coast";
      break;
      case 3:
      pszName = "Eastern";
      break;
      case 5:
      pszName = "Nairobi Area";
      break;
      case 6:
      pszName = "North-Eastern";
      break;
      case 7:
      pszName = "Nyanza";
      break;
      case 8:
      pszName = "Rift Valley";
      break;
      case 9:
      pszName = "Western";
      break;
    }
  }
  if (strcmp(country_code,"KG") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bishkek";
      break;
      case 2:
      pszName = "Chuy";
      break;
      case 3:
      pszName = "Jalal-Abad";
      break;
      case 4:
      pszName = "Naryn";
      break;
      case 5:
      pszName = "Osh";
      break;
      case 6:
      pszName = "Talas";
      break;
      case 7:
      pszName = "Ysyk-Kol";
      break;
      case 8:
      pszName = "Osh";
      break;
      case 9:
      pszName = "Batken";
      break;
    }
  }
  if (strcmp(country_code,"KH") == 0) {
    switch (region_code2) {
      case 0:
      pszName = "Banteay Meanchey";
      break;
      case 1:
      pszName = "Batdambang";
      break;
      case 2:
      pszName = "Kampong Cham";
      break;
      case 3:
      pszName = "Kampong Chhnang";
      break;
      case 4:
      pszName = "Kampong Speu";
      break;
      case 5:
      pszName = "Kampong Thum";
      break;
      case 6:
      pszName = "Kampot";
      break;
      case 7:
      pszName = "Kandal";
      break;
      case 8:
      pszName = "Koh Kong";
      break;
      case 9:
      pszName = "Kracheh";
      break;
      case 10:
      pszName = "Mondulkiri";
      break;
      case 11:
      pszName = "Phnum Penh";
      break;
      case 12:
      pszName = "Pursat";
      break;
      case 13:
      pszName = "Preah Vihear";
      break;
      case 14:
      pszName = "Prey Veng";
      break;
      case 15:
      pszName = "Ratanakiri Kiri";
      break;
      case 16:
      pszName = "Siem Reap";
      break;
      case 17:
      pszName = "Stung Treng";
      break;
      case 18:
      pszName = "Svay Rieng";
      break;
      case 19:
      pszName = "Takeo";
      break;
      case 29:
      pszName = "Batdambang";
      break;
      case 30:
      pszName = "Pailin";
      break;
    }
  }
  if (strcmp(country_code,"KI") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Gilbert Islands";
      break;
      case 2:
      pszName = "Line Islands";
      break;
      case 3:
      pszName = "Phoenix Islands";
      break;
    }
  }
  if (strcmp(country_code,"KM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Anjouan";
      break;
      case 2:
      pszName = "Grande Comore";
      break;
      case 3:
      pszName = "Moheli";
      break;
    }
  }
  if (strcmp(country_code,"KN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Christ Church Nichola Town";
      break;
      case 2:
      pszName = "Saint Anne Sandy Point";
      break;
      case 3:
      pszName = "Saint George Basseterre";
      break;
      case 4:
      pszName = "Saint George Gingerland";
      break;
      case 5:
      pszName = "Saint James Windward";
      break;
      case 6:
      pszName = "Saint John Capisterre";
      break;
      case 7:
      pszName = "Saint John Figtree";
      break;
      case 8:
      pszName = "Saint Mary Cayon";
      break;
      case 9:
      pszName = "Saint Paul Capisterre";
      break;
      case 10:
      pszName = "Saint Paul Charlestown";
      break;
      case 11:
      pszName = "Saint Peter Basseterre";
      break;
      case 12:
      pszName = "Saint Thomas vulkan_land";
      break;
      case 13:
      pszName = "Saint Thomas Middle Island";
      break;
      case 15:
      pszName = "Trinity Palmetto Point";
      break;
    }
  }
  if (strcmp(country_code,"KP") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Chagang-do";
      break;
      case 3:
      pszName = "Hamgyong-namdo";
      break;
      case 6:
      pszName = "Hwanghae-namdo";
      break;
      case 7:
      pszName = "Hwanghae-bukto";
      break;
      case 8:
      pszName = "Kaesong-si";
      break;
      case 9:
      pszName = "Kangwon-do";
      break;
      case 11:
      pszName = "P'yongan-bukto";
      break;
      case 12:
      pszName = "P'yongyang-si";
      break;
      case 13:
      pszName = "Yanggang-do";
      break;
      case 14:
      pszName = "Namp'o-si";
      break;
      case 15:
      pszName = "P'yongan-namdo";
      break;
      case 17:
      pszName = "Hamgyong-bukto";
      break;
      case 18:
      pszName = "Najin Sonbong-si";
      break;
    }
  }
  if (strcmp(country_code,"KR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Cheju-do";
      break;
      case 3:
      pszName = "Cholla-bukto";
      break;
      case 5:
      pszName = "Ch'ungch'ong-bukto";
      break;
      case 6:
      pszName = "Kangwon-do";
      break;
      case 10:
      pszName = "Pusan-jikhalsi";
      break;
      case 11:
      pszName = "Seoul-t'ukpyolsi";
      break;
      case 12:
      pszName = "Inch'on-jikhalsi";
      break;
      case 13:
      pszName = "Kyonggi-do";
      break;
      case 14:
      pszName = "Kyongsang-bukto";
      break;
      case 15:
      pszName = "Taegu-jikhalsi";
      break;
      case 16:
      pszName = "Cholla-namdo";
      break;
      case 17:
      pszName = "Ch'ungch'ong-namdo";
      break;
      case 18:
      pszName = "Kwangju-jikhalsi";
      break;
      case 19:
      pszName = "Taejon-jikhalsi";
      break;
      case 20:
      pszName = "Kyongsang-namdo";
      break;
      case 21:
      pszName = "Ulsan-gwangyoksi";
      break;
    }
  }
  if (strcmp(country_code,"KW") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Al Ahmadi";
      break;
      case 2:
      pszName = "Al Kuwayt";
      break;
      case 5:
      pszName = "Al Jahra";
      break;
      case 7:
      pszName = "Al Farwaniyah";
      break;
      case 8:
      pszName = "Hawalli";
      break;
      case 9:
      pszName = "Mubarak al Kabir";
      break;
    }
  }
  if (strcmp(country_code,"KY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Creek";
      break;
      case 2:
      pszName = "Eastern";
      break;
      case 3:
      pszName = "Midland";
      break;
      case 4:
      pszName = "South Town";
      break;
      case 5:
      pszName = "Spot Bay";
      break;
      case 6:
      pszName = "Stake Bay";
      break;
      case 7:
      pszName = "West End";
      break;
      case 8:
      pszName = "Western";
      break;
    }
  }
  if (strcmp(country_code,"KZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Almaty";
      break;
      case 2:
      pszName = "Almaty City";
      break;
      case 3:
      pszName = "Aqmola";
      break;
      case 4:
      pszName = "Aqtobe";
      break;
      case 5:
      pszName = "Astana";
      break;
      case 6:
      pszName = "Atyrau";
      break;
      case 7:
      pszName = "West Kazakhstan";
      break;
      case 8:
      pszName = "Bayqonyr";
      break;
      case 9:
      pszName = "Mangghystau";
      break;
      case 10:
      pszName = "South Kazakhstan";
      break;
      case 11:
      pszName = "Pavlodar";
      break;
      case 12:
      pszName = "Qaraghandy";
      break;
      case 13:
      pszName = "Qostanay";
      break;
      case 14:
      pszName = "Qyzylorda";
      break;
      case 15:
      pszName = "East Kazakhstan";
      break;
      case 16:
      pszName = "North Kazakhstan";
      break;
      case 17:
      pszName = "Zhambyl";
      break;
    }
  }
  if (strcmp(country_code,"LA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Attapu";
      break;
      case 2:
      pszName = "Champasak";
      break;
      case 3:
      pszName = "Houaphan";
      break;
      case 4:
      pszName = "Khammouan";
      break;
      case 5:
      pszName = "Louang Namtha";
      break;
      case 7:
      pszName = "Oudomxai";
      break;
      case 8:
      pszName = "Phongsali";
      break;
      case 9:
      pszName = "Saravan";
      break;
      case 10:
      pszName = "Savannakhet";
      break;
      case 11:
      pszName = "Vientiane";
      break;
      case 13:
      pszName = "Xaignabouri";
      break;
      case 14:
      pszName = "Xiangkhoang";
      break;
      case 17:
      pszName = "Louangphrabang";
      break;
    }
  }
  if (strcmp(country_code,"LB") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Beqaa";
      break;
      case 3:
      pszName = "Liban-Nord";
      break;
      case 4:
      pszName = "Beyrouth";
      break;
      case 5:
      pszName = "Mont-Liban";
      break;
      case 6:
      pszName = "Liban-Sud";
      break;
      case 7:
      pszName = "Nabatiye";
      break;
      case 8:
      pszName = "Beqaa";
      break;
      case 9:
      pszName = "Liban-Nord";
      break;
      case 10:
      pszName = "Aakk,r";
      break;
      case 11:
      pszName = "Baalbek-Hermel";
      break;
    }
  }
  if (strcmp(country_code,"LC") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Anse-la-Raye";
      break;
      case 2:
      pszName = "Dauphin";
      break;
      case 3:
      pszName = "Castries";
      break;
      case 4:
      pszName = "Choiseul";
      break;
      case 5:
      pszName = "Dennery";
      break;
      case 6:
      pszName = "Gros-Islet";
      break;
      case 7:
      pszName = "Laborie";
      break;
      case 8:
      pszName = "Micoud";
      break;
      case 9:
      pszName = "Soufriere";
      break;
      case 10:
      pszName = "Vieux-Fort";
      break;
      case 11:
      pszName = "Praslin";
      break;
    }
  }
  if (strcmp(country_code,"LI") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Balzers";
      break;
      case 2:
      pszName = "Eschen";
      break;
      case 3:
      pszName = "Gamprin";
      break;
      case 4:
      pszName = "Mauren";
      break;
      case 5:
      pszName = "Planken";
      break;
      case 6:
      pszName = "Ruggell";
      break;
      case 7:
      pszName = "Schaan";
      break;
      case 8:
      pszName = "Schellenberg";
      break;
      case 9:
      pszName = "Triesen";
      break;
      case 10:
      pszName = "Triesenberg";
      break;
      case 11:
      pszName = "Vaduz";
      break;
      case 21:
      pszName = "Gbarpolu";
      break;
      case 22:
      pszName = "River Gee";
      break;
    }
  }
  if (strcmp(country_code,"LK") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Amparai";
      break;
      case 2:
      pszName = "Anuradhapura";
      break;
      case 3:
      pszName = "Badulla";
      break;
      case 4:
      pszName = "Batticaloa";
      break;
      case 6:
      pszName = "Galle";
      break;
      case 7:
      pszName = "Hambantota";
      break;
      case 9:
      pszName = "Kalutara";
      break;
      case 10:
      pszName = "Kandy";
      break;
      case 11:
      pszName = "Kegalla";
      break;
      case 12:
      pszName = "Kurunegala";
      break;
      case 14:
      pszName = "Matale";
      break;
      case 15:
      pszName = "Matara";
      break;
      case 16:
      pszName = "Moneragala";
      break;
      case 17:
      pszName = "Nuwara Eliya";
      break;
      case 18:
      pszName = "Polonnaruwa";
      break;
      case 19:
      pszName = "Puttalam";
      break;
      case 20:
      pszName = "Ratnapura";
      break;
      case 21:
      pszName = "Trincomalee";
      break;
      case 23:
      pszName = "Colombo";
      break;
      case 24:
      pszName = "Gampaha";
      break;
      case 25:
      pszName = "Jaffna";
      break;
      case 26:
      pszName = "Mannar";
      break;
      case 27:
      pszName = "Mullaittivu";
      break;
      case 28:
      pszName = "Vavuniya";
      break;
      case 29:
      pszName = "Central";
      break;
      case 30:
      pszName = "North Central";
      break;
      case 31:
      pszName = "Northern";
      break;
      case 32:
      pszName = "North Western";
      break;
      case 33:
      pszName = "Sabaragamuwa";
      break;
      case 34:
      pszName = "Southern";
      break;
      case 35:
      pszName = "Uva";
      break;
      case 36:
      pszName = "Western";
      break;
    }
  }
  if (strcmp(country_code,"LR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bong";
      break;
      case 4:
      pszName = "Grand Cape Mount";
      break;
      case 6:
      pszName = "Maryland";
      break;
      case 7:
      pszName = "Monrovia";
      break;
      case 9:
      pszName = "Nimba";
      break;
      case 10:
      pszName = "Sino";
      break;
      case 11:
      pszName = "Grand Bassa";
      break;
      case 14:
      pszName = "Montserrado";
      break;
      case 19:
      pszName = "Grand Gedeh";
      break;
      case 20:
      pszName = "Lofa";
      break;
    }
  }
  if (strcmp(country_code,"LS") == 0) {
    switch (region_code2) {
      case 10:
      pszName = "Berea";
      break;
      case 11:
      pszName = "Butha-Buthe";
      break;
      case 12:
      pszName = "Leribe";
      break;
      case 13:
      pszName = "Mafeteng";
      break;
      case 14:
      pszName = "Maseru";
      break;
      case 15:
      pszName = "Mohales Hoek";
      break;
      case 16:
      pszName = "Mokhotlong";
      break;
      case 17:
      pszName = "Qachas Nek";
      break;
      case 18:
      pszName = "Quthing";
      break;
      case 19:
      pszName = "Thaba-Tseka";
      break;
    }
  }
  if (strcmp(country_code,"LT") == 0) {
    switch (region_code2) {
      case 56:
      pszName = "Alytaus Apskritis";
      break;
      case 57:
      pszName = "Kauno Apskritis";
      break;
      case 58:
      pszName = "Klaipedos Apskritis";
      break;
      case 59:
      pszName = "Marijampoles Apskritis";
      break;
      case 60:
      pszName = "Panevezio Apskritis";
      break;
      case 61:
      pszName = "Siauliu Apskritis";
      break;
      case 62:
      pszName = "Taurages Apskritis";
      break;
      case 63:
      pszName = "Telsiu Apskritis";
      break;
      case 64:
      pszName = "Utenos Apskritis";
      break;
      case 65:
      pszName = "Vilniaus Apskritis";
      break;
    }
  }
  if (strcmp(country_code,"LU") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Diekirch";
      break;
      case 2:
      pszName = "Grevenmacher";
      break;
      case 3:
      pszName = "Luxembourg";
      break;
    }
  }
  if (strcmp(country_code,"LV") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aizkraukles";
      break;
      case 2:
      pszName = "Aluksnes";
      break;
      case 3:
      pszName = "Balvu";
      break;
      case 4:
      pszName = "Bauskas";
      break;
      case 5:
      pszName = "Cesu";
      break;
      case 6:
      pszName = "Daugavpils";
      break;
      case 7:
      pszName = "Daugavpils";
      break;
      case 8:
      pszName = "Dobeles";
      break;
      case 9:
      pszName = "Gulbenes";
      break;
      case 10:
      pszName = "Jekabpils";
      break;
      case 11:
      pszName = "Jelgava";
      break;
      case 12:
      pszName = "Jelgavas";
      break;
      case 13:
      pszName = "Jurmala";
      break;
      case 14:
      pszName = "Kraslavas";
      break;
      case 15:
      pszName = "Kuldigas";
      break;
      case 16:
      pszName = "Liepaja";
      break;
      case 17:
      pszName = "Liepajas";
      break;
      case 18:
      pszName = "Limbazu";
      break;
      case 19:
      pszName = "Ludzas";
      break;
      case 20:
      pszName = "Madonas";
      break;
      case 21:
      pszName = "Ogres";
      break;
      case 22:
      pszName = "Preilu";
      break;
      case 23:
      pszName = "Rezekne";
      break;
      case 24:
      pszName = "Rezeknes";
      break;
      case 25:
      pszName = "Riga";
      break;
      case 26:
      pszName = "Rigas";
      break;
      case 27:
      pszName = "Saldus";
      break;
      case 28:
      pszName = "Talsu";
      break;
      case 29:
      pszName = "Tukuma";
      break;
      case 30:
      pszName = "Valkas";
      break;
      case 31:
      pszName = "Valmieras";
      break;
      case 32:
      pszName = "Ventspils";
      break;
      case 33:
      pszName = "Ventspils";
      break;
    }
  }
  if (strcmp(country_code,"LY") == 0) {
    switch (region_code2) {
      case 3:
      pszName = "Al Aziziyah";
      break;
      case 5:
      pszName = "Al Jufrah";
      break;
      case 8:
      pszName = "Al Kufrah";
      break;
      case 13:
      pszName = "Ash Shati'";
      break;
      case 30:
      pszName = "Murzuq";
      break;
      case 34:
      pszName = "Sabha";
      break;
      case 41:
      pszName = "Tarhunah";
      break;
      case 42:
      pszName = "Tubruq";
      break;
      case 45:
      pszName = "Zlitan";
      break;
      case 47:
      pszName = "Ajdabiya";
      break;
      case 48:
      pszName = "Al Fatih";
      break;
      case 49:
      pszName = "Al Jabal al Akhdar";
      break;
      case 50:
      pszName = "Al Khums";
      break;
      case 51:
      pszName = "An Nuqat al Khams";
      break;
      case 52:
      pszName = "Awbari";
      break;
      case 53:
      pszName = "Az Zawiyah";
      break;
      case 54:
      pszName = "Banghazi";
      break;
      case 55:
      pszName = "Darnah";
      break;
      case 56:
      pszName = "Ghadamis";
      break;
      case 57:
      pszName = "Gharyan";
      break;
      case 58:
      pszName = "Misratah";
      break;
      case 59:
      pszName = "Sawfajjin";
      break;
      case 60:
      pszName = "Surt";
      break;
      case 61:
      pszName = "Tarabulus";
      break;
      case 62:
      pszName = "Yafran";
      break;
    }
  }
  if (strcmp(country_code,"MA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Agadir";
      break;
      case 2:
      pszName = "Al Hoceima";
      break;
      case 3:
      pszName = "Azilal";
      break;
      case 4:
      pszName = "Ben Slimane";
      break;
      case 5:
      pszName = "Beni Mellal";
      break;
      case 6:
      pszName = "Boulemane";
      break;
      case 7:
      pszName = "Casablanca";
      break;
      case 8:
      pszName = "Chaouen";
      break;
      case 9:
      pszName = "El Jadida";
      break;
      case 10:
      pszName = "El Kelaa des Srarhna";
      break;
      case 11:
      pszName = "Er Rachidia";
      break;
      case 12:
      pszName = "Essaouira";
      break;
      case 13:
      pszName = "Fes";
      break;
      case 14:
      pszName = "Figuig";
      break;
      case 15:
      pszName = "Kenitra";
      break;
      case 16:
      pszName = "Khemisset";
      break;
      case 17:
      pszName = "Khenifra";
      break;
      case 18:
      pszName = "Khouribga";
      break;
      case 19:
      pszName = "Marrakech";
      break;
      case 20:
      pszName = "Meknes";
      break;
      case 21:
      pszName = "Nador";
      break;
      case 22:
      pszName = "Ouarzazate";
      break;
      case 23:
      pszName = "Oujda";
      break;
      case 24:
      pszName = "Rabat-Sale";
      break;
      case 25:
      pszName = "Safi";
      break;
      case 26:
      pszName = "Settat";
      break;
      case 27:
      pszName = "Tanger";
      break;
      case 29:
      pszName = "Tata";
      break;
      case 30:
      pszName = "Taza";
      break;
      case 32:
      pszName = "Tiznit";
      break;
      case 33:
      pszName = "Guelmim";
      break;
      case 34:
      pszName = "Ifrane";
      break;
      case 35:
      pszName = "Laayoune";
      break;
      case 36:
      pszName = "Tan-Tan";
      break;
      case 37:
      pszName = "Taounate";
      break;
      case 38:
      pszName = "Sidi Kacem";
      break;
      case 39:
      pszName = "Taroudannt";
      break;
      case 40:
      pszName = "Tetouan";
      break;
      case 41:
      pszName = "Larache";
      break;
      case 45:
      pszName = "Grand Casablanca";
      break;
      case 46:
      pszName = "Fes-Boulemane";
      break;
      case 47:
      pszName = "Marrakech-Tensift-Al Haouz";
      break;
      case 48:
      pszName = "Meknes-Tafilalet";
      break;
      case 49:
      pszName = "Rabat-Sale-Zemmour-Zaer";
      break;
      case 50:
      pszName = "Chaouia-Ouardigha";
      break;
      case 51:
      pszName = "Doukkala-Abda";
      break;
      case 52:
      pszName = "Gharb-Chrarda-Beni Hssen";
      break;
      case 53:
      pszName = "Guelmim-Es Smara";
      break;
      case 54:
      pszName = "Oriental";
      break;
      case 55:
      pszName = "Souss-Massa-Dr,a";
      break;
      case 56:
      pszName = "Tadla-Azilal";
      break;
      case 57:
      pszName = "Tanger-Tetouan";
      break;
      case 58:
      pszName = "Taza-Al Hoceima-Taounate";
      break;
      case 59:
      pszName = "La,youne-Boujdour-Sakia El Hamra";
      break;
    }
  }
  if (strcmp(country_code,"MC") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "La Condamine";
      break;
      case 2:
      pszName = "Monaco";
      break;
      case 3:
      pszName = "Monte-Carlo";
      break;
    }
  }
  if (strcmp(country_code,"MD") == 0) {
    switch (region_code2) {
      case 46:
      pszName = "Balti";
      break;
      case 47:
      pszName = "Cahul";
      break;
      case 48:
      pszName = "Chisinau";
      break;
      case 49:
      pszName = "Stinga Nistrului";
      break;
      case 50:
      pszName = "Edinet";
      break;
      case 51:
      pszName = "Gagauzia";
      break;
      case 52:
      pszName = "Lapusna";
      break;
      case 53:
      pszName = "Orhei";
      break;
      case 54:
      pszName = "Soroca";
      break;
      case 55:
      pszName = "Tighina";
      break;
      case 56:
      pszName = "Ungheni";
      break;
      case 58:
      pszName = "Stinga Nistrului";
      break;
      case 59:
      pszName = "Anenii Noi";
      break;
      case 60:
      pszName = "Balti";
      break;
      case 61:
      pszName = "Basarabeasca";
      break;
      case 62:
      pszName = "Bender";
      break;
      case 63:
      pszName = "Briceni";
      break;
      case 64:
      pszName = "Cahul";
      break;
      case 65:
      pszName = "Cantemir";
      break;
      case 66:
      pszName = "Calarasi";
      break;
      case 67:
      pszName = "Causeni";
      break;
      case 68:
      pszName = "Cimislia";
      break;
      case 69:
      pszName = "Criuleni";
      break;
      case 70:
      pszName = "Donduseni";
      break;
      case 71:
      pszName = "Drochia";
      break;
      case 72:
      pszName = "Dubasari";
      break;
      case 73:
      pszName = "Edinet";
      break;
      case 74:
      pszName = "Falesti";
      break;
      case 75:
      pszName = "Floresti";
      break;
      case 76:
      pszName = "Glodeni";
      break;
      case 77:
      pszName = "Hincesti";
      break;
      case 78:
      pszName = "Ialoveni";
      break;
      case 79:
      pszName = "Leova";
      break;
      case 80:
      pszName = "Nisporeni";
      break;
      case 81:
      pszName = "Ocnita";
      break;
      case 83:
      pszName = "Rezina";
      break;
      case 84:
      pszName = "Riscani";
      break;
      case 85:
      pszName = "Singerei";
      break;
      case 86:
      pszName = "Soldanesti";
      break;
      case 87:
      pszName = "Soroca";
      break;
      case 88:
      pszName = "Stefan-Voda";
      break;
      case 89:
      pszName = "Straseni";
      break;
      case 90:
      pszName = "Taraclia";
      break;
      case 91:
      pszName = "Telenesti";
      break;
      case 92:
      pszName = "Ungheni";
      break;
    }
  }
  if (strcmp(country_code,"MG") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Antsiranana";
      break;
      case 2:
      pszName = "Fianarantsoa";
      break;
      case 3:
      pszName = "Mahajanga";
      break;
      case 4:
      pszName = "Toamasina";
      break;
      case 5:
      pszName = "Antananarivo";
      break;
      case 6:
      pszName = "Toliara";
      break;
    }
  }
  if (strcmp(country_code,"MK") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aracinovo";
      break;
      case 2:
      pszName = "Bac";
      break;
      case 3:
      pszName = "Belcista";
      break;
      case 4:
      pszName = "Berovo";
      break;
      case 5:
      pszName = "Bistrica";
      break;
      case 6:
      pszName = "Bitola";
      break;
      case 7:
      pszName = "Blatec";
      break;
      case 8:
      pszName = "Bogdanci";
      break;
      case 9:
      pszName = "Bogomila";
      break;
      case 10:
      pszName = "Bogovinje";
      break;
      case 11:
      pszName = "Bosilovo";
      break;
      case 12:
      pszName = "Brvenica";
      break;
      case 13:
      pszName = "Cair";
      break;
      case 14:
      pszName = "Capari";
      break;
      case 15:
      pszName = "Caska";
      break;
      case 16:
      pszName = "Cegrane";
      break;
      case 17:
      pszName = "Centar";
      break;
      case 18:
      pszName = "Centar Zupa";
      break;
      case 19:
      pszName = "Cesinovo";
      break;
      case 20:
      pszName = "Cucer-Sandevo";
      break;
      case 21:
      pszName = "Debar";
      break;
      case 22:
      pszName = "Delcevo";
      break;
      case 23:
      pszName = "Delogozdi";
      break;
      case 24:
      pszName = "Demir Hisar";
      break;
      case 25:
      pszName = "Demir Kapija";
      break;
      case 26:
      pszName = "Dobrusevo";
      break;
      case 27:
      pszName = "Dolna Banjica";
      break;
      case 28:
      pszName = "Dolneni";
      break;
      case 29:
      pszName = "Dorce Petrov";
      break;
      case 30:
      pszName = "Drugovo";
      break;
      case 31:
      pszName = "Dzepciste";
      break;
      case 32:
      pszName = "Gazi Baba";
      break;
      case 33:
      pszName = "Gevgelija";
      break;
      case 34:
      pszName = "Gostivar";
      break;
      case 35:
      pszName = "Gradsko";
      break;
      case 36:
      pszName = "Ilinden";
      break;
      case 37:
      pszName = "Izvor";
      break;
      case 38:
      pszName = "Jegunovce";
      break;
      case 39:
      pszName = "Kamenjane";
      break;
      case 40:
      pszName = "Karbinci";
      break;
      case 41:
      pszName = "Karpos";
      break;
      case 42:
      pszName = "Kavadarci";
      break;
      case 43:
      pszName = "Kicevo";
      break;
      case 44:
      pszName = "Kisela Voda";
      break;
      case 45:
      pszName = "Klecevce";
      break;
      case 46:
      pszName = "Kocani";
      break;
      case 47:
      pszName = "Konce";
      break;
      case 48:
      pszName = "Kondovo";
      break;
      case 49:
      pszName = "Konopiste";
      break;
      case 50:
      pszName = "Kosel";
      break;
      case 51:
      pszName = "Kratovo";
      break;
      case 52:
      pszName = "Kriva Palanka";
      break;
      case 53:
      pszName = "Krivogastani";
      break;
      case 54:
      pszName = "Krusevo";
      break;
      case 55:
      pszName = "Kuklis";
      break;
      case 56:
      pszName = "Kukurecani";
      break;
      case 57:
      pszName = "Kumanovo";
      break;
      case 58:
      pszName = "Labunista";
      break;
      case 59:
      pszName = "Lipkovo";
      break;
      case 60:
      pszName = "Lozovo";
      break;
      case 61:
      pszName = "Lukovo";
      break;
      case 62:
      pszName = "Makedonska Kamenica";
      break;
      case 63:
      pszName = "Makedonski Brod";
      break;
      case 64:
      pszName = "Mavrovi Anovi";
      break;
      case 65:
      pszName = "Meseista";
      break;
      case 66:
      pszName = "Miravci";
      break;
      case 67:
      pszName = "Mogila";
      break;
      case 68:
      pszName = "Murtino";
      break;
      case 69:
      pszName = "Negotino";
      break;
      case 70:
      pszName = "Negotino-Polosko";
      break;
      case 71:
      pszName = "Novaci";
      break;
      case 72:
      pszName = "Novo Selo";
      break;
      case 73:
      pszName = "Oblesevo";
      break;
      case 74:
      pszName = "Ohrid";
      break;
      case 75:
      pszName = "Orasac";
      break;
      case 76:
      pszName = "Orizari";
      break;
      case 77:
      pszName = "Oslomej";
      break;
      case 78:
      pszName = "Pehcevo";
      break;
      case 79:
      pszName = "Petrovec";
      break;
      case 80:
      pszName = "Plasnica";
      break;
      case 81:
      pszName = "Podares";
      break;
      case 82:
      pszName = "Prilep";
      break;
      case 83:
      pszName = "Probistip";
      break;
      case 84:
      pszName = "Radovis";
      break;
      case 85:
      pszName = "Rankovce";
      break;
      case 86:
      pszName = "Resen";
      break;
      case 87:
      pszName = "Rosoman";
      break;
      case 88:
      pszName = "Rostusa";
      break;
      case 89:
      pszName = "Samokov";
      break;
      case 90:
      pszName = "Saraj";
      break;
      case 91:
      pszName = "Sipkovica";
      break;
      case 92:
      pszName = "Sopiste";
      break;
      case 93:
      pszName = "Sopotnica";
      break;
      case 94:
      pszName = "Srbinovo";
      break;
      case 95:
      pszName = "Staravina";
      break;
      case 96:
      pszName = "Star Dojran";
      break;
      case 97:
      pszName = "Staro Nagoricane";
      break;
      case 98:
      pszName = "Stip";
      break;
      case 99:
      pszName = "Struga";
      break;
      case 832:
      pszName = "Strumica";
      break;
      case 833:
      pszName = "Studenicani";
      break;
      case 834:
      pszName = "Suto Orizari";
      break;
      case 835:
      pszName = "Sveti Nikole";
      break;
      case 836:
      pszName = "Tearce";
      break;
      case 837:
      pszName = "Tetovo";
      break;
      case 838:
      pszName = "Topolcani";
      break;
      case 839:
      pszName = "Valandovo";
      break;
      case 840:
      pszName = "Vasilevo";
      break;
      case 875:
      pszName = "Veles";
      break;
      case 876:
      pszName = "Velesta";
      break;
      case 877:
      pszName = "Vevcani";
      break;
      case 878:
      pszName = "Vinica";
      break;
      case 879:
      pszName = "Vitoliste";
      break;
      case 880:
      pszName = "Vranestica";
      break;
      case 881:
      pszName = "Vrapciste";
      break;
      case 882:
      pszName = "Vratnica";
      break;
      case 883:
      pszName = "Vrutok";
      break;
      case 918:
      pszName = "Zajas";
      break;
      case 919:
      pszName = "Zelenikovo";
      break;
      case 920:
      pszName = "Zelino";
      break;
      case 921:
      pszName = "Zitose";
      break;
      case 922:
      pszName = "Zletovo";
      break;
      case 923:
      pszName = "Zrnovci";
      break;
    }
  }
  if (strcmp(country_code,"ML") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bamako";
      break;
      case 3:
      pszName = "Kayes";
      break;
      case 4:
      pszName = "Mopti";
      break;
      case 5:
      pszName = "Segou";
      break;
      case 6:
      pszName = "Sikasso";
      break;
      case 7:
      pszName = "Koulikoro";
      break;
      case 8:
      pszName = "Tombouctou";
      break;
      case 9:
      pszName = "Gao";
      break;
      case 10:
      pszName = "Kidal";
      break;
    }
  }
  if (strcmp(country_code,"MM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Rakhine State";
      break;
      case 2:
      pszName = "Chin State";
      break;
      case 3:
      pszName = "Irrawaddy";
      break;
      case 4:
      pszName = "Kachin State";
      break;
      case 5:
      pszName = "Karan State";
      break;
      case 6:
      pszName = "Kayah State";
      break;
      case 7:
      pszName = "Magwe";
      break;
      case 8:
      pszName = "Mandalay";
      break;
      case 9:
      pszName = "Pegu";
      break;
      case 10:
      pszName = "Sagaing";
      break;
      case 11:
      pszName = "Shan State";
      break;
      case 12:
      pszName = "Tenasserim";
      break;
      case 13:
      pszName = "Mon State";
      break;
      case 14:
      pszName = "Rangoon";
      break;
      case 17:
      pszName = "Yangon";
      break;
    }
  }
  if (strcmp(country_code,"MN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Arhangay";
      break;
      case 2:
      pszName = "Bayanhongor";
      break;
      case 3:
      pszName = "Bayan-Olgiy";
      break;
      case 5:
      pszName = "Darhan";
      break;
      case 6:
      pszName = "Dornod";
      break;
      case 7:
      pszName = "Dornogovi";
      break;
      case 8:
      pszName = "Dundgovi";
      break;
      case 9:
      pszName = "Dzavhan";
      break;
      case 10:
      pszName = "Govi-Altay";
      break;
      case 11:
      pszName = "Hentiy";
      break;
      case 12:
      pszName = "Hovd";
      break;
      case 13:
      pszName = "Hovsgol";
      break;
      case 14:
      pszName = "Omnogovi";
      break;
      case 15:
      pszName = "Ovorhangay";
      break;
      case 16:
      pszName = "Selenge";
      break;
      case 17:
      pszName = "Suhbaatar";
      break;
      case 18:
      pszName = "Tov";
      break;
      case 19:
      pszName = "Uvs";
      break;
      case 20:
      pszName = "Ulaanbaatar";
      break;
      case 21:
      pszName = "Bulgan";
      break;
      case 22:
      pszName = "Erdenet";
      break;
      case 23:
      pszName = "Darhan-Uul";
      break;
      case 24:
      pszName = "Govisumber";
      break;
      case 25:
      pszName = "Orhon";
      break;
    }
  }
  if (strcmp(country_code,"MO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ilhas";
      break;
      case 2:
      pszName = "Macau";
      break;
    }
  }
  if (strcmp(country_code,"MR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Hodh Ech Chargui";
      break;
      case 2:
      pszName = "Hodh El Gharbi";
      break;
      case 3:
      pszName = "Assaba";
      break;
      case 4:
      pszName = "Gorgol";
      break;
      case 5:
      pszName = "Brakna";
      break;
      case 6:
      pszName = "Trarza";
      break;
      case 7:
      pszName = "Adrar";
      break;
      case 8:
      pszName = "Dakhlet Nouadhibou";
      break;
      case 9:
      pszName = "Tagant";
      break;
      case 10:
      pszName = "Guidimaka";
      break;
      case 11:
      pszName = "Tiris Zemmour";
      break;
      case 12:
      pszName = "Inchiri";
      break;
    }
  }
  if (strcmp(country_code,"MS") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Saint Anthony";
      break;
      case 2:
      pszName = "Saint Georges";
      break;
      case 3:
      pszName = "Saint Peter";
      break;
    }
  }
  if (strcmp(country_code,"MU") == 0) {
    switch (region_code2) {
      case 12:
      pszName = "Black River";
      break;
      case 13:
      pszName = "Flacq";
      break;
      case 14:
      pszName = "Grand Port";
      break;
      case 15:
      pszName = "Moka";
      break;
      case 16:
      pszName = "Pamplemousses";
      break;
      case 17:
      pszName = "Plaines Wilhems";
      break;
      case 18:
      pszName = "Port Louis";
      break;
      case 19:
      pszName = "Riviere du Rempart";
      break;
      case 20:
      pszName = "Savanne";
      break;
      case 21:
      pszName = "Agalega Islands";
      break;
      case 22:
      pszName = "Cargados Carajos";
      break;
      case 23:
      pszName = "Rodrigues";
      break;
    }
  }
  if (strcmp(country_code,"MV") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Seenu";
      break;
      case 2:
      pszName = "Aliff";
      break;
      case 3:
      pszName = "Laviyani";
      break;
      case 4:
      pszName = "Waavu";
      break;
      case 5:
      pszName = "Laamu";
      break;
      case 7:
      pszName = "Haa Aliff";
      break;
      case 8:
      pszName = "Thaa";
      break;
      case 12:
      pszName = "Meemu";
      break;
      case 13:
      pszName = "Raa";
      break;
      case 14:
      pszName = "Faafu";
      break;
      case 17:
      pszName = "Daalu";
      break;
      case 20:
      pszName = "Baa";
      break;
      case 23:
      pszName = "Haa Daalu";
      break;
      case 24:
      pszName = "Shaviyani";
      break;
      case 25:
      pszName = "Noonu";
      break;
      case 26:
      pszName = "Kaafu";
      break;
      case 27:
      pszName = "Gaafu Aliff";
      break;
      case 28:
      pszName = "Gaafu Daalu";
      break;
      case 29:
      pszName = "Naviyani";
      break;
      case 40:
      pszName = "Male";
      break;
    }
  }
  if (strcmp(country_code,"MW") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Chikwawa";
      break;
      case 3:
      pszName = "Chiradzulu";
      break;
      case 4:
      pszName = "Chitipa";
      break;
      case 5:
      pszName = "Thyolo";
      break;
      case 6:
      pszName = "Dedza";
      break;
      case 7:
      pszName = "Dowa";
      break;
      case 8:
      pszName = "Karonga";
      break;
      case 9:
      pszName = "Kasungu";
      break;
      case 11:
      pszName = "Lilongwe";
      break;
      case 12:
      pszName = "Mangochi";
      break;
      case 13:
      pszName = "Mchinji";
      break;
      case 15:
      pszName = "Mzimba";
      break;
      case 16:
      pszName = "Ntcheu";
      break;
      case 17:
      pszName = "Nkhata Bay";
      break;
      case 18:
      pszName = "Nkhotakota";
      break;
      case 19:
      pszName = "Nsanje";
      break;
      case 20:
      pszName = "Ntchisi";
      break;
      case 21:
      pszName = "Rumphi";
      break;
      case 22:
      pszName = "Salima";
      break;
      case 23:
      pszName = "Zomba";
      break;
      case 24:
      pszName = "Blantyre";
      break;
      case 25:
      pszName = "Mwanza";
      break;
      case 26:
      pszName = "Balaka";
      break;
      case 27:
      pszName = "Likoma";
      break;
      case 28:
      pszName = "Machinga";
      break;
      case 29:
      pszName = "Mulanje";
      break;
      case 30:
      pszName = "Phalombe";
      break;
    }
  }
  if (strcmp(country_code,"MX") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aguascalientes";
      break;
      case 2:
      pszName = "Baja California";
      break;
      case 3:
      pszName = "Baja California Sur";
      break;
      case 4:
      pszName = "Campeche";
      break;
      case 5:
      pszName = "Chiapas";
      break;
      case 6:
      pszName = "Chihuahua";
      break;
      case 7:
      pszName = "Coahuila de Zaragoza";
      break;
      case 8:
      pszName = "Colima";
      break;
      case 9:
      pszName = "Distrito Federal";
      break;
      case 10:
      pszName = "Durango";
      break;
      case 11:
      pszName = "Guanajuato";
      break;
      case 12:
      pszName = "Guerrero";
      break;
      case 13:
      pszName = "Hidalgo";
      break;
      case 14:
      pszName = "Jalisco";
      break;
      case 15:
      pszName = "Mexico";
      break;
      case 16:
      pszName = "Michoacan de Ocampo";
      break;
      case 17:
      pszName = "Morelos";
      break;
      case 18:
      pszName = "Nayarit";
      break;
      case 19:
      pszName = "Nuevo Leon";
      break;
      case 20:
      pszName = "Oaxaca";
      break;
      case 21:
      pszName = "Puebla";
      break;
      case 22:
      pszName = "Queretaro de Arteaga";
      break;
      case 23:
      pszName = "Q::u32ana Roo";
      break;
      case 24:
      pszName = "San Luis Potosi";
      break;
      case 25:
      pszName = "Sinaloa";
      break;
      case 26:
      pszName = "Sonora";
      break;
      case 27:
      pszName = "Tabasco";
      break;
      case 28:
      pszName = "Tamaulipas";
      break;
      case 29:
      pszName = "Tlaxcala";
      break;
      case 30:
      pszName = "Veracruz-Llave";
      break;
      case 31:
      pszName = "Yucatan";
      break;
      case 32:
      pszName = "Zacatecas";
      break;
    }
  }
  if (strcmp(country_code,"MY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Johor";
      break;
      case 2:
      pszName = "Kedah";
      break;
      case 3:
      pszName = "Kelantan";
      break;
      case 4:
      pszName = "Melaka";
      break;
      case 5:
      pszName = "Negeri Sembilan";
      break;
      case 6:
      pszName = "Pahang";
      break;
      case 7:
      pszName = "Perak";
      break;
      case 8:
      pszName = "Perlis";
      break;
      case 9:
      pszName = "Pulau Pinang";
      break;
      case 11:
      pszName = "Sarawak";
      break;
      case 12:
      pszName = "Selangor";
      break;
      case 13:
      pszName = "Terengganu";
      break;
      case 14:
      pszName = "Kuala Lumpur";
      break;
      case 15:
      pszName = "Labuan";
      break;
      case 16:
      pszName = "Sabah";
      break;
      case 17:
      pszName = "Putrajaya";
      break;
    }
  }
  if (strcmp(country_code,"MZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Cabo Delgado";
      break;
      case 2:
      pszName = "Gaza";
      break;
      case 3:
      pszName = "Inhambane";
      break;
      case 4:
      pszName = "Maputo";
      break;
      case 5:
      pszName = "Sofala";
      break;
      case 6:
      pszName = "Nampula";
      break;
      case 7:
      pszName = "Niassa";
      break;
      case 8:
      pszName = "Tete";
      break;
      case 9:
      pszName = "Zambezia";
      break;
      case 10:
      pszName = "Manica";
      break;
      case 11:
      pszName = "Maputo";
      break;
    }
  }
  if (strcmp(country_code,"NA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bethanien";
      break;
      case 2:
      pszName = "Caprivi Oos";
      break;
      case 3:
      pszName = "Boesmanland";
      break;
      case 4:
      pszName = "Gobabis";
      break;
      case 5:
      pszName = "Grootfontein";
      break;
      case 6:
      pszName = "Kaokoland";
      break;
      case 7:
      pszName = "Karibib";
      break;
      case 8:
      pszName = "Keetmanshoop";
      break;
      case 9:
      pszName = "Luderitz";
      break;
      case 10:
      pszName = "Maltahohe";
      break;
      case 11:
      pszName = "Okahandja";
      break;
      case 12:
      pszName = "Omaruru";
      break;
      case 13:
      pszName = "Otjiwarongo";
      break;
      case 14:
      pszName = "Outjo";
      break;
      case 15:
      pszName = "Owambo";
      break;
      case 16:
      pszName = "Rehoboth";
      break;
      case 17:
      pszName = "Swakopmund";
      break;
      case 18:
      pszName = "Tsumeb";
      break;
      case 20:
      pszName = "Karasburg";
      break;
      case 21:
      pszName = "Windhoek";
      break;
      case 22:
      pszName = "Damaraland";
      break;
      case 23:
      pszName = "Hereroland Oos";
      break;
      case 24:
      pszName = "Hereroland Wes";
      break;
      case 25:
      pszName = "Kavango";
      break;
      case 26:
      pszName = "Mariental";
      break;
      case 27:
      pszName = "Namaland";
      break;
      case 28:
      pszName = "Caprivi";
      break;
      case 29:
      pszName = "Erongo";
      break;
      case 30:
      pszName = "Hardap";
      break;
      case 31:
      pszName = "Karas";
      break;
      case 32:
      pszName = "Kunene";
      break;
      case 33:
      pszName = "Ohangwena";
      break;
      case 34:
      pszName = "Okavango";
      break;
      case 35:
      pszName = "Omaheke";
      break;
      case 36:
      pszName = "Omusati";
      break;
      case 37:
      pszName = "Oshana";
      break;
      case 38:
      pszName = "Oshikoto";
      break;
      case 39:
      pszName = "Otjozondjupa";
      break;
    }
  }
  if (strcmp(country_code,"NE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Agadez";
      break;
      case 2:
      pszName = "Diffa";
      break;
      case 3:
      pszName = "Dosso";
      break;
      case 4:
      pszName = "Maradi";
      break;
      case 5:
      pszName = "Niamey";
      break;
      case 6:
      pszName = "Tahoua";
      break;
      case 7:
      pszName = "Zinder";
      break;
      case 8:
      pszName = "Niamey";
      break;
    }
  }
  if (strcmp(country_code,"NG") == 0) {
    switch (region_code2) {
      case 5:
      pszName = "Lagos";
      break;
      case 10:
      pszName = "Rivers";
      break;
      case 11:
      pszName = "Federal Capital Territory";
      break;
      case 16:
      pszName = "Ogun";
      break;
      case 17:
      pszName = "Ondo";
      break;
      case 21:
      pszName = "Akwa Ibom";
      break;
      case 22:
      pszName = "Cross River";
      break;
      case 23:
      pszName = "Kaduna";
      break;
      case 24:
      pszName = "Katsina";
      break;
      case 25:
      pszName = "Anambra";
      break;
      case 26:
      pszName = "Benue";
      break;
      case 27:
      pszName = "Borno";
      break;
      case 28:
      pszName = "Imo";
      break;
      case 29:
      pszName = "Kano";
      break;
      case 30:
      pszName = "Kwara";
      break;
      case 31:
      pszName = "Niger";
      break;
      case 32:
      pszName = "Oyo";
      break;
      case 35:
      pszName = "Adamawa";
      break;
      case 36:
      pszName = "Delta";
      break;
      case 37:
      pszName = "Edo";
      break;
      case 39:
      pszName = "Jigawa";
      break;
      case 40:
      pszName = "Kebbi";
      break;
      case 41:
      pszName = "Kogi";
      break;
      case 42:
      pszName = "Osun";
      break;
      case 43:
      pszName = "Taraba";
      break;
      case 44:
      pszName = "Yobe";
      break;
      case 45:
      pszName = "Abia";
      break;
      case 46:
      pszName = "Bauchi";
      break;
      case 47:
      pszName = "Enugu";
      break;
      case 48:
      pszName = "Ondo";
      break;
      case 49:
      pszName = "Plateau";
      break;
      case 50:
      pszName = "Rivers";
      break;
      case 51:
      pszName = "Sokoto";
      break;
      case 52:
      pszName = "Bayelsa";
      break;
      case 53:
      pszName = "Ebonyi";
      break;
      case 54:
      pszName = "Ekiti";
      break;
      case 55:
      pszName = "Gombe";
      break;
      case 56:
      pszName = "Nassarawa";
      break;
      case 57:
      pszName = "Zamfara";
      break;
    }
  }
  if (strcmp(country_code,"NI") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Boaco";
      break;
      case 2:
      pszName = "Carazo";
      break;
      case 3:
      pszName = "Chinandega";
      break;
      case 4:
      pszName = "Chontales";
      break;
      case 5:
      pszName = "Esteli";
      break;
      case 6:
      pszName = "Granada";
      break;
      case 7:
      pszName = "Jinotega";
      break;
      case 8:
      pszName = "Leon";
      break;
      case 9:
      pszName = "Madriz";
      break;
      case 10:
      pszName = "Managua";
      break;
      case 11:
      pszName = "Masaya";
      break;
      case 12:
      pszName = "Matagalpa";
      break;
      case 13:
      pszName = "Nueva Segovia";
      break;
      case 14:
      pszName = "Rio San Juan";
      break;
      case 15:
      pszName = "Rivas";
      break;
      case 16:
      pszName = "Zelaya";
      break;
      case 17:
      pszName = "Autonoma Atlantico Norte";
      break;
      case 18:
      pszName = "Region Autonoma Atlantico Sur";
      break;
    }
  }
  if (strcmp(country_code,"NL") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Drenthe";
      break;
      case 2:
      pszName = "Friesland";
      break;
      case 3:
      pszName = "Gelderland";
      break;
      case 4:
      pszName = "Groningen";
      break;
      case 5:
      pszName = "Limburg";
      break;
      case 6:
      pszName = "Noord-Brabant";
      break;
      case 7:
      pszName = "Noord-Holland";
      break;
      case 8:
      pszName = "Overijssel";
      break;
      case 9:
      pszName = "Utrecht";
      break;
      case 10:
      pszName = "Zeeland";
      break;
      case 11:
      pszName = "Zuid-Holland";
      break;
      case 12:
      pszName = "Dronten";
      break;
      case 13:
      pszName = "Zuidelijke IJsselmeerpolders";
      break;
      case 14:
      pszName = "Lelystad";
      break;
      case 15:
      pszName = "Overijssel";
      break;
      case 16:
      pszName = "Flevoland";
      break;
    }
  }
  if (strcmp(country_code,"NO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Akershus";
      break;
      case 2:
      pszName = "Aust-Agder";
      break;
      case 4:
      pszName = "Buskerud";
      break;
      case 5:
      pszName = "Finnmark";
      break;
      case 6:
      pszName = "Hedmark";
      break;
      case 7:
      pszName = "Hordaland";
      break;
      case 8:
      pszName = "More og Romsdal";
      break;
      case 9:
      pszName = "Nordland";
      break;
      case 10:
      pszName = "Nord-Trondelag";
      break;
      case 11:
      pszName = "Oppland";
      break;
      case 12:
      pszName = "Oslo";
      break;
      case 13:
      pszName = "Ostfold";
      break;
      case 14:
      pszName = "Rogaland";
      break;
      case 15:
      pszName = "Sogn og Fjordane";
      break;
      case 16:
      pszName = "Sor-Trondelag";
      break;
      case 17:
      pszName = "Telemark";
      break;
      case 18:
      pszName = "Troms";
      break;
      case 19:
      pszName = "Vest-Agder";
      break;
      case 20:
      pszName = "Vestfold";
      break;
    }
  }
  if (strcmp(country_code,"NP") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bagmati";
      break;
      case 2:
      pszName = "Bheri";
      break;
      case 3:
      pszName = "Dhawalagiri";
      break;
      case 4:
      pszName = "Gandaki";
      break;
      case 5:
      pszName = "Janakpur";
      break;
      case 6:
      pszName = "Karnali";
      break;
      case 7:
      pszName = "Kosi";
      break;
      case 8:
      pszName = "Lumbini";
      break;
      case 9:
      pszName = "Mahakali";
      break;
      case 10:
      pszName = "Mechi";
      break;
      case 11:
      pszName = "Narayani";
      break;
      case 12:
      pszName = "Rapti";
      break;
      case 13:
      pszName = "Sagarmatha";
      break;
      case 14:
      pszName = "Seti";
      break;
    }
  }
  if (strcmp(country_code,"NR") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Aiwo";
      break;
      case 2:
      pszName = "Anabar";
      break;
      case 3:
      pszName = "Anetan";
      break;
      case 4:
      pszName = "Anibare";
      break;
      case 5:
      pszName = "Baiti";
      break;
      case 6:
      pszName = "Boe";
      break;
      case 7:
      pszName = "Buada";
      break;
      case 8:
      pszName = "Denigomodu";
      break;
      case 9:
      pszName = "Ewa";
      break;
      case 10:
      pszName = "Ijuw";
      break;
      case 11:
      pszName = "Meneng";
      break;
      case 12:
      pszName = "Nibok";
      break;
      case 13:
      pszName = "Uaboe";
      break;
      case 14:
      pszName = "Yaren";
      break;
    }
  }
  if (strcmp(country_code,"NZ") == 0) {
    switch (region_code2) {
      case 10:
      pszName = "Chatham Islands";
      break;
      case 1010:
      pszName = "Auckland";
      break;
      case 1011:
      pszName = "Bay of Plenty";
      break;
      case 1012:
      pszName = "Canterbury";
      break;
      case 1047:
      pszName = "Gisborne";
      break;
      case 1048:
      pszName = "Hawke's Bay";
      break;
      case 1049:
      pszName = "Manawatu-Wanganui";
      break;
      case 1050:
      pszName = "Marlborough";
      break;
      case 1051:
      pszName = "Nelson";
      break;
      case 1052:
      pszName = "Northland";
      break;
      case 1053:
      pszName = "Otago";
      break;
      case 1054:
      pszName = "Southland";
      break;
      case 1055:
      pszName = "Taranaki";
      break;
      case 1090:
      pszName = "Waikato";
      break;
      case 1091:
      pszName = "Wellington";
      break;
      case 1092:
      pszName = "West Coast";
      break;
    }
  }
  if (strcmp(country_code,"OM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ad Dakhiliyah";
      break;
      case 2:
      pszName = "Al Batinah";
      break;
      case 3:
      pszName = "Al Wusta";
      break;
      case 4:
      pszName = "Ash Sharqiyah";
      break;
      case 5:
      pszName = "Az Zahirah";
      break;
      case 6:
      pszName = "Masqat";
      break;
      case 7:
      pszName = "Musandam";
      break;
      case 8:
      pszName = "Zufar";
      break;
    }
  }
  if (strcmp(country_code,"PA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bocas del Toro";
      break;
      case 2:
      pszName = "Chiriqui";
      break;
      case 3:
      pszName = "Cocle";
      break;
      case 4:
      pszName = "Colon";
      break;
      case 5:
      pszName = "Darien";
      break;
      case 6:
      pszName = "Herrera";
      break;
      case 7:
      pszName = "Los Santos";
      break;
      case 8:
      pszName = "Panama";
      break;
      case 9:
      pszName = "San Blas";
      break;
      case 10:
      pszName = "Veraguas";
      break;
    }
  }
  if (strcmp(country_code,"PE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Amazonas";
      break;
      case 2:
      pszName = "Ancash";
      break;
      case 3:
      pszName = "Apurimac";
      break;
      case 4:
      pszName = "Arequipa";
      break;
      case 5:
      pszName = "Ayacucho";
      break;
      case 6:
      pszName = "Cajamarca";
      break;
      case 7:
      pszName = "Callao";
      break;
      case 8:
      pszName = "Cusco";
      break;
      case 9:
      pszName = "Huancavelica";
      break;
      case 10:
      pszName = "Huanuco";
      break;
      case 11:
      pszName = "Ica";
      break;
      case 12:
      pszName = "Junin";
      break;
      case 13:
      pszName = "La Libertad";
      break;
      case 14:
      pszName = "Lambayeque";
      break;
      case 15:
      pszName = "Lima";
      break;
      case 16:
      pszName = "Loreto";
      break;
      case 17:
      pszName = "Madre de Dios";
      break;
      case 18:
      pszName = "Moquegua";
      break;
      case 19:
      pszName = "Pasco";
      break;
      case 20:
      pszName = "Piura";
      break;
      case 21:
      pszName = "Puno";
      break;
      case 22:
      pszName = "San Martin";
      break;
      case 23:
      pszName = "Tacna";
      break;
      case 24:
      pszName = "Tumbes";
      break;
      case 25:
      pszName = "Ucayali";
      break;
    }
  }
  if (strcmp(country_code,"PG") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Central";
      break;
      case 2:
      pszName = "Gulf";
      break;
      case 3:
      pszName = "Milne Bay";
      break;
      case 4:
      pszName = "Northern";
      break;
      case 5:
      pszName = "Southern Highlands";
      break;
      case 6:
      pszName = "Western";
      break;
      case 7:
      pszName = "North Solomons";
      break;
      case 8:
      pszName = "Chimbu";
      break;
      case 9:
      pszName = "Eastern Highlands";
      break;
      case 10:
      pszName = "East New Britain";
      break;
      case 11:
      pszName = "East Sepik";
      break;
      case 12:
      pszName = "Madang";
      break;
      case 13:
      pszName = "Manus";
      break;
      case 14:
      pszName = "Morobe";
      break;
      case 15:
      pszName = "New Ireland";
      break;
      case 16:
      pszName = "Western Highlands";
      break;
      case 17:
      pszName = "West New Britain";
      break;
      case 18:
      pszName = "Sandaun";
      break;
      case 19:
      pszName = "Enga";
      break;
      case 20:
      pszName = "National Capital";
      break;
    }
  }
  if (strcmp(country_code,"PH") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Abra";
      break;
      case 2:
      pszName = "Agusan del Norte";
      break;
      case 3:
      pszName = "Agusan del Sur";
      break;
      case 4:
      pszName = "Aklan";
      break;
      case 5:
      pszName = "Albay";
      break;
      case 6:
      pszName = "Antique";
      break;
      case 7:
      pszName = "Bataan";
      break;
      case 8:
      pszName = "Batanes";
      break;
      case 9:
      pszName = "Batangas";
      break;
      case 10:
      pszName = "Benguet";
      break;
      case 11:
      pszName = "Bohol";
      break;
      case 12:
      pszName = "Bukidnon";
      break;
      case 13:
      pszName = "Bulacan";
      break;
      case 14:
      pszName = "Cagayan";
      break;
      case 15:
      pszName = "Camarines Norte";
      break;
      case 16:
      pszName = "Camarines Sur";
      break;
      case 17:
      pszName = "Camiguin";
      break;
      case 18:
      pszName = "Capiz";
      break;
      case 19:
      pszName = "Catanduanes";
      break;
      case 20:
      pszName = "Cavite";
      break;
      case 21:
      pszName = "Cebu";
      break;
      case 22:
      pszName = "Basilan";
      break;
      case 23:
      pszName = "Eastern Samar";
      break;
      case 24:
      pszName = "Davao";
      break;
      case 25:
      pszName = "Davao del Sur";
      break;
      case 26:
      pszName = "Davao Oriental";
      break;
      case 27:
      pszName = "Ifugao";
      break;
      case 28:
      pszName = "Ilocos Norte";
      break;
      case 29:
      pszName = "Ilocos Sur";
      break;
      case 30:
      pszName = "Iloilo";
      break;
      case 31:
      pszName = "Isabela";
      break;
      case 32:
      pszName = "Kalinga-Apayao";
      break;
      case 33:
      pszName = "Laguna";
      break;
      case 34:
      pszName = "Lanao del Norte";
      break;
      case 35:
      pszName = "Lanao del Sur";
      break;
      case 36:
      pszName = "La Union";
      break;
      case 37:
      pszName = "Leyte";
      break;
      case 38:
      pszName = "Marinduque";
      break;
      case 39:
      pszName = "Masbate";
      break;
      case 40:
      pszName = "Mindoro Occidental";
      break;
      case 41:
      pszName = "Mindoro Oriental";
      break;
      case 42:
      pszName = "Misamis Occidental";
      break;
      case 43:
      pszName = "Misamis Oriental";
      break;
      case 44:
      pszName = "Mountain";
      break;
      case 46:
      pszName = "Negros Oriental";
      break;
      case 47:
      pszName = "Nueva Ecija";
      break;
      case 48:
      pszName = "Nueva Vizcaya";
      break;
      case 49:
      pszName = "Palawan";
      break;
      case 50:
      pszName = "Pampanga";
      break;
      case 51:
      pszName = "Pangasinan";
      break;
      case 53:
      pszName = "Rizal";
      break;
      case 54:
      pszName = "Romblon";
      break;
      case 55:
      pszName = "Samar";
      break;
      case 56:
      pszName = "Maguindanao";
      break;
      case 57:
      pszName = "North Cotabato";
      break;
      case 58:
      pszName = "Sorsogon";
      break;
      case 59:
      pszName = "Southern Leyte";
      break;
      case 60:
      pszName = "Sulu";
      break;
      case 61:
      pszName = "Surigao del Norte";
      break;
      case 62:
      pszName = "Surigao del Sur";
      break;
      case 63:
      pszName = "Tarlac";
      break;
      case 64:
      pszName = "Zambales";
      break;
      case 65:
      pszName = "Zamboanga del Norte";
      break;
      case 66:
      pszName = "Zamboanga del Sur";
      break;
      case 67:
      pszName = "Northern Samar";
      break;
      case 68:
      pszName = "Quirino";
      break;
      case 69:
      pszName = "Siquijor";
      break;
      case 70:
      pszName = "South Cotabato";
      break;
      case 71:
      pszName = "Sultan Kudarat";
      break;
      case 72:
      pszName = "Tawitawi";
      break;
      case 832:
      pszName = "Angeles";
      break;
      case 833:
      pszName = "Bacolod";
      break;
      case 834:
      pszName = "Bago";
      break;
      case 835:
      pszName = "Baguio";
      break;
      case 836:
      pszName = "Bais";
      break;
      case 837:
      pszName = "Basilan City";
      break;
      case 838:
      pszName = "Batangas City";
      break;
      case 839:
      pszName = "Butuan";
      break;
      case 840:
      pszName = "Cabanatuan";
      break;
      case 875:
      pszName = "Cadiz";
      break;
      case 876:
      pszName = "Cagayan de Oro";
      break;
      case 877:
      pszName = "Calbayog";
      break;
      case 878:
      pszName = "Caloocan";
      break;
      case 879:
      pszName = "Canlaon";
      break;
      case 880:
      pszName = "Cavite City";
      break;
      case 881:
      pszName = "Cebu City";
      break;
      case 882:
      pszName = "Cotabato";
      break;
      case 883:
      pszName = "Dagupan";
      break;
      case 918:
      pszName = "Danao";
      break;
      case 919:
      pszName = "Dapitan";
      break;
      case 920:
      pszName = "Davao City";
      break;
      case 921:
      pszName = "Dipolog";
      break;
      case 922:
      pszName = "Dumaguete";
      break;
      case 923:
      pszName = "General Santos";
      break;
      case 924:
      pszName = "Gingoog";
      break;
      case 925:
      pszName = "Iligan";
      break;
      case 926:
      pszName = "Iloilo City";
      break;
      case 961:
      pszName = "Iriga";
      break;
      case 962:
      pszName = "La Carlota";
      break;
      case 963:
      pszName = "Laoag";
      break;
      case 964:
      pszName = "Lapu-Lapu";
      break;
      case 965:
      pszName = "Legaspi";
      break;
      case 966:
      pszName = "Lipa";
      break;
      case 967:
      pszName = "Lucena";
      break;
      case 968:
      pszName = "Mandaue";
      break;
      case 969:
      pszName = "Manila";
      break;
      case 1004:
      pszName = "Marawi";
      break;
      case 1005:
      pszName = "Naga";
      break;
      case 1006:
      pszName = "Olongapo";
      break;
      case 1007:
      pszName = "Ormoc";
      break;
      case 1008:
      pszName = "Oroquieta";
      break;
      case 1009:
      pszName = "Ozamis";
      break;
      case 1010:
      pszName = "Pagadian";
      break;
      case 1011:
      pszName = "Palayan";
      break;
      case 1012:
      pszName = "Pasay";
      break;
      case 1047:
      pszName = "Puerto Princesa";
      break;
      case 1048:
      pszName = "Quezon City";
      break;
      case 1049:
      pszName = "Roxas";
      break;
      case 1050:
      pszName = "San Carlos";
      break;
      case 1051:
      pszName = "San Carlos";
      break;
      case 1052:
      pszName = "San Jose";
      break;
      case 1053:
      pszName = "San Pablo";
      break;
      case 1054:
      pszName = "Silay";
      break;
      case 1055:
      pszName = "Surigao";
      break;
      case 1090:
      pszName = "Tacloban";
      break;
      case 1091:
      pszName = "Tagaytay";
      break;
      case 1092:
      pszName = "Tagbilaran";
      break;
      case 1093:
      pszName = "Tangub";
      break;
      case 1094:
      pszName = "Toledo";
      break;
      case 1095:
      pszName = "Trece Martires";
      break;
      case 1096:
      pszName = "Zamboanga";
      break;
      case 1097:
      pszName = "Aurora";
      break;
      case 1134:
      pszName = "Quezon";
      break;
      case 1135:
      pszName = "Negros Occidental";
      break;
    }
  }
  if (strcmp(country_code,"PK") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Federally Administered Tribal Areas";
      break;
      case 2:
      pszName = "Balochistan";
      break;
      case 3:
      pszName = "North-West Frontier";
      break;
      case 4:
      pszName = "Punjab";
      break;
      case 5:
      pszName = "Sindh";
      break;
      case 6:
      pszName = "Azad Kashmir";
      break;
      case 7:
      pszName = "Northern Areas";
      break;
      case 8:
      pszName = "Islamabad";
      break;
    }
  }
  if (strcmp(country_code,"PL") == 0) {
    switch (region_code2) {
      case 23:
      pszName = "Biala Podlaska";
      break;
      case 24:
      pszName = "Bialystok";
      break;
      case 25:
      pszName = "Bielsko";
      break;
      case 26:
      pszName = "Bydgoszcz";
      break;
      case 27:
      pszName = "Chelm";
      break;
      case 28:
      pszName = "Ciechanow";
      break;
      case 29:
      pszName = "Czestochowa";
      break;
      case 30:
      pszName = "Elblag";
      break;
      case 31:
      pszName = "Gdansk";
      break;
      case 32:
      pszName = "Gorzow";
      break;
      case 33:
      pszName = "Jelenia Gora";
      break;
      case 34:
      pszName = "Kalisz";
      break;
      case 35:
      pszName = "Katowice";
      break;
      case 36:
      pszName = "Kielce";
      break;
      case 37:
      pszName = "Konin";
      break;
      case 38:
      pszName = "Koszalin";
      break;
      case 39:
      pszName = "Krakow";
      break;
      case 40:
      pszName = "Krosno";
      break;
      case 41:
      pszName = "Legnica";
      break;
      case 42:
      pszName = "Leszno";
      break;
      case 43:
      pszName = "Lodz";
      break;
      case 44:
      pszName = "Lomza";
      break;
      case 45:
      pszName = "Lublin";
      break;
      case 46:
      pszName = "Nowy Sacz";
      break;
      case 47:
      pszName = "Olsztyn";
      break;
      case 48:
      pszName = "Opole";
      break;
      case 49:
      pszName = "Ostroleka";
      break;
      case 50:
      pszName = "Pila";
      break;
      case 51:
      pszName = "Piotrkow";
      break;
      case 52:
      pszName = "Plock";
      break;
      case 53:
      pszName = "Poznan";
      break;
      case 54:
      pszName = "Przemysl";
      break;
      case 55:
      pszName = "Radom";
      break;
      case 56:
      pszName = "Rzeszow";
      break;
      case 57:
      pszName = "Siedlce";
      break;
      case 58:
      pszName = "Sieradz";
      break;
      case 59:
      pszName = "Skierniewice";
      break;
      case 60:
      pszName = "Slupsk";
      break;
      case 61:
      pszName = "Suwalki";
      break;
      case 62:
      pszName = "Szczecin";
      break;
      case 63:
      pszName = "Tarnobrzeg";
      break;
      case 64:
      pszName = "Tarnow";
      break;
      case 65:
      pszName = "Torun";
      break;
      case 66:
      pszName = "Walbrzych";
      break;
      case 67:
      pszName = "Warszawa";
      break;
      case 68:
      pszName = "Wloclawek";
      break;
      case 69:
      pszName = "Wroclaw";
      break;
      case 70:
      pszName = "Zamosc";
      break;
      case 71:
      pszName = "Zielona Gora";
      break;
      case 72:
      pszName = "Dolnoslaskie";
      break;
      case 73:
      pszName = "Kujawsko-Pomorskie";
      break;
      case 74:
      pszName = "Lodzkie";
      break;
      case 75:
      pszName = "Lubelskie";
      break;
      case 76:
      pszName = "Lubuskie";
      break;
      case 77:
      pszName = "Malopolskie";
      break;
      case 78:
      pszName = "Mazowieckie";
      break;
      case 79:
      pszName = "Opolskie";
      break;
      case 80:
      pszName = "Podkarpackie";
      break;
      case 81:
      pszName = "Podlaskie";
      break;
      case 82:
      pszName = "Pomorskie";
      break;
      case 83:
      pszName = "Slaskie";
      break;
      case 84:
      pszName = "Swietokrzyskie";
      break;
      case 85:
      pszName = "Warminsko-Mazurskie";
      break;
      case 86:
      pszName = "Wielkopolskie";
      break;
      case 87:
      pszName = "Zachodniopomorskie";
      break;
    }
  }
  if (strcmp(country_code,"PS") == 0) {
    switch (region_code2) {
      case 1131:
      pszName = "Gaza";
      break;
      case 1798:
      pszName = "West Bank";
      break;
    }
  }
  if (strcmp(country_code,"PT") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Aveiro";
      break;
      case 3:
      pszName = "Beja";
      break;
      case 4:
      pszName = "Braga";
      break;
      case 5:
      pszName = "Braganca";
      break;
      case 6:
      pszName = "Castelo Branco";
      break;
      case 7:
      pszName = "Coimbra";
      break;
      case 8:
      pszName = "Evora";
      break;
      case 9:
      pszName = "Faro";
      break;
      case 10:
      pszName = "Madeira";
      break;
      case 11:
      pszName = "Guarda";
      break;
      case 13:
      pszName = "Leiria";
      break;
      case 14:
      pszName = "Lisboa";
      break;
      case 16:
      pszName = "Portalegre";
      break;
      case 17:
      pszName = "Porto";
      break;
      case 18:
      pszName = "Santarem";
      break;
      case 19:
      pszName = "Setubal";
      break;
      case 20:
      pszName = "Viana do Castelo";
      break;
      case 21:
      pszName = "Vila Real";
      break;
      case 22:
      pszName = "Viseu";
      break;
      case 23:
      pszName = "Azores";
      break;
    }
  }
  if (strcmp(country_code,"PY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Alto Parana";
      break;
      case 2:
      pszName = "Amambay";
      break;
      case 3:
      pszName = "Boqueron";
      break;
      case 4:
      pszName = "Caaguazu";
      break;
      case 5:
      pszName = "Caazapa";
      break;
      case 6:
      pszName = "Central";
      break;
      case 7:
      pszName = "Concepcion";
      break;
      case 8:
      pszName = "Cordillera";
      break;
      case 10:
      pszName = "Guaira";
      break;
      case 11:
      pszName = "Itapua";
      break;
      case 12:
      pszName = "Misiones";
      break;
      case 13:
      pszName = "Neembucu";
      break;
      case 15:
      pszName = "Paraguari";
      break;
      case 16:
      pszName = "Presidente Hayes";
      break;
      case 17:
      pszName = "San Pedro";
      break;
      case 19:
      pszName = "Canindeyu";
      break;
      case 20:
      pszName = "Chaco";
      break;
      case 21:
      pszName = "Nueva Asuncion";
      break;
      case 23:
      pszName = "Alto Paraguay";
      break;
    }
  }
  if (strcmp(country_code,"QA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ad Dawhah";
      break;
      case 2:
      pszName = "Al Ghuwariyah";
      break;
      case 3:
      pszName = "Al Jumaliyah";
      break;
      case 4:
      pszName = "Al Khawr";
      break;
      case 5:
      pszName = "Al Wakrah Municipality";
      break;
      case 6:
      pszName = "Ar Rayyan";
      break;
      case 8:
      pszName = "Madinat ach Shamal";
      break;
      case 9:
      pszName = "Umm Salal";
      break;
      case 10:
      pszName = "Al Wakrah";
      break;
      case 11:
      pszName = "Jariyan al Batnah";
      break;
      case 12:
      pszName = "Umm Sa'atom";
      break;
    }
  }
  if (strcmp(country_code,"RO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Alba";
      break;
      case 2:
      pszName = "Arad";
      break;
      case 3:
      pszName = "Arges";
      break;
      case 4:
      pszName = "Bacau";
      break;
      case 5:
      pszName = "Bihor";
      break;
      case 6:
      pszName = "Bistrita-Nasaud";
      break;
      case 7:
      pszName = "Botosani";
      break;
      case 8:
      pszName = "Braila";
      break;
      case 9:
      pszName = "Brasov";
      break;
      case 10:
      pszName = "Bucuresti";
      break;
      case 11:
      pszName = "Buzau";
      break;
      case 12:
      pszName = "Caras-Severin";
      break;
      case 13:
      pszName = "Cluj";
      break;
      case 14:
      pszName = "Constanta";
      break;
      case 15:
      pszName = "Covasna";
      break;
      case 16:
      pszName = "Dambovita";
      break;
      case 17:
      pszName = "Dolj";
      break;
      case 18:
      pszName = "Galati";
      break;
      case 19:
      pszName = "Gorj";
      break;
      case 20:
      pszName = "Harghita";
      break;
      case 21:
      pszName = "Hunedoara";
      break;
      case 22:
      pszName = "Ialomita";
      break;
      case 23:
      pszName = "Iasi";
      break;
      case 25:
      pszName = "Maramures";
      break;
      case 26:
      pszName = "Mehedinti";
      break;
      case 27:
      pszName = "Mures";
      break;
      case 28:
      pszName = "Neamt";
      break;
      case 29:
      pszName = "Olt";
      break;
      case 30:
      pszName = "Prahova";
      break;
      case 31:
      pszName = "Salaj";
      break;
      case 32:
      pszName = "Satu Mare";
      break;
      case 33:
      pszName = "Sibiu";
      break;
      case 34:
      pszName = "Suceava";
      break;
      case 35:
      pszName = "Teleorman";
      break;
      case 36:
      pszName = "Timis";
      break;
      case 37:
      pszName = "Tulcea";
      break;
      case 38:
      pszName = "Vaslui";
      break;
      case 39:
      pszName = "Valcea";
      break;
      case 40:
      pszName = "Vrancea";
      break;
      case 41:
      pszName = "Calarasi";
      break;
      case 42:
      pszName = "Giurgiu";
      break;
      case 43:
      pszName = "Ilfov";
      break;
    }
  }
  if (strcmp(country_code,"RS") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Kosovo";
      break;
      case 2:
      pszName = "Vojvodina";
      break;
    }
  }
  if (strcmp(country_code,"RU") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Adygeya, Republic of";
      break;
      case 2:
      pszName = "Aginsky Buryatsky AO";
      break;
      case 3:
      pszName = "Gorno-Altay";
      break;
      case 4:
      pszName = "Altaisky krai";
      break;
      case 5:
      pszName = "Amur";
      break;
      case 6:
      pszName = "Arkhangel'sk";
      break;
      case 7:
      pszName = "Astrakhan'";
      break;
      case 8:
      pszName = "Bashkortostan";
      break;
      case 9:
      pszName = "Belgorod";
      break;
      case 10:
      pszName = "Bryansk";
      break;
      case 11:
      pszName = "Buryat";
      break;
      case 12:
      pszName = "Chechnya";
      break;
      case 13:
      pszName = "Chelyabinsk";
      break;
      case 14:
      pszName = "Chita";
      break;
      case 15:
      pszName = "Chukot";
      break;
      case 16:
      pszName = "Chuvashia";
      break;
      case 17:
      pszName = "Dagestan";
      break;
      case 18:
      pszName = "Evenk";
      break;
      case 19:
      pszName = "Ingush";
      break;
      case 20:
      pszName = "Irkutsk";
      break;
      case 21:
      pszName = "Ivanovo";
      break;
      case 22:
      pszName = "Kabardin-Balkar";
      break;
      case 23:
      pszName = "Kaliningrad";
      break;
      case 24:
      pszName = "Kalmyk";
      break;
      case 25:
      pszName = "Kaluga";
      break;
      case 26:
      pszName = "Kamchatka";
      break;
      case 27:
      pszName = "Karachay-Cherkess";
      break;
      case 28:
      pszName = "Karelia";
      break;
      case 29:
      pszName = "Kemerovo";
      break;
      case 30:
      pszName = "Khabarovsk";
      break;
      case 31:
      pszName = "Khakass";
      break;
      case 32:
      pszName = "Khanty-Mansiy";
      break;
      case 33:
      pszName = "Kirov";
      break;
      case 34:
      pszName = "Komi";
      break;
      case 35:
      pszName = "Komi-Permyak";
      break;
      case 36:
      pszName = "Koryak";
      break;
      case 37:
      pszName = "Kostroma";
      break;
      case 38:
      pszName = "Krasnodar";
      break;
      case 39:
      pszName = "Krasnoyarsk";
      break;
      case 40:
      pszName = "Kurgan";
      break;
      case 41:
      pszName = "Kursk";
      break;
      case 42:
      pszName = "Leningrad";
      break;
      case 43:
      pszName = "Lipetsk";
      break;
      case 44:
      pszName = "Magadan";
      break;
      case 45:
      pszName = "Mariy-El";
      break;
      case 46:
      pszName = "Mordovia";
      break;
      case 47:
      pszName = "Moskva";
      break;
      case 48:
      pszName = "Moscow City";
      break;
      case 49:
      pszName = "Murmansk";
      break;
      case 50:
      pszName = "Nenets";
      break;
      case 51:
      pszName = "Nizhegorod";
      break;
      case 52:
      pszName = "Novgorod";
      break;
      case 53:
      pszName = "Novosibirsk";
      break;
      case 54:
      pszName = "Omsk";
      break;
      case 55:
      pszName = "Orenburg";
      break;
      case 56:
      pszName = "Orel";
      break;
      case 57:
      pszName = "Penza";
      break;
      case 58:
      pszName = "Perm'";
      break;
      case 59:
      pszName = "Primor'ye";
      break;
      case 60:
      pszName = "Pskov";
      break;
      case 61:
      pszName = "Rostov";
      break;
      case 62:
      pszName = "Ryazan'";
      break;
      case 63:
      pszName = "Sakha";
      break;
      case 64:
      pszName = "Sakhalin";
      break;
      case 65:
      pszName = "Samara";
      break;
      case 66:
      pszName = "Saint Petersburg City";
      break;
      case 67:
      pszName = "Saratov";
      break;
      case 68:
      pszName = "North Ossetia";
      break;
      case 69:
      pszName = "Smolensk";
      break;
      case 70:
      pszName = "Stavropol'";
      break;
      case 71:
      pszName = "Sverdlovsk";
      break;
      case 72:
      pszName = "Tambovskaya oblast";
      break;
      case 73:
      pszName = "Tatarstan";
      break;
      case 74:
      pszName = "Taymyr";
      break;
      case 75:
      pszName = "Tomsk";
      break;
      case 76:
      pszName = "Tula";
      break;
      case 77:
      pszName = "Tver'";
      break;
      case 78:
      pszName = "Tyumen'";
      break;
      case 79:
      pszName = "Tuva";
      break;
      case 80:
      pszName = "Udmurt";
      break;
      case 81:
      pszName = "Ul'yanovsk";
      break;
      case 82:
      pszName = "Ust-Orda Buryat";
      break;
      case 83:
      pszName = "Vladimir";
      break;
      case 84:
      pszName = "Volgograd";
      break;
      case 85:
      pszName = "Vologda";
      break;
      case 86:
      pszName = "Voronezh";
      break;
      case 87:
      pszName = "Yamal-Nenets";
      break;
      case 88:
      pszName = "Yaroslavl'";
      break;
      case 89:
      pszName = "Yevrey";
      break;
      case 90:
      pszName = "Permskiy Kray";
      break;
      case 91:
      pszName = "Krasnoyarskiy Kray";
      break;
      case 942:
      pszName = "Chechnya Republic";
      break;
    }
  }
  if (strcmp(country_code,"RW") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Butare";
      break;
      case 6:
      pszName = "Gitarama";
      break;
      case 9:
      pszName = "Kigali";
      break;
      case 11:
      pszName = "Est";
      break;
      case 12:
      pszName = "Kigali";
      break;
      case 13:
      pszName = "Nord";
      break;
      case 14:
      pszName = "Ouest";
      break;
      case 15:
      pszName = "Sud";
      break;
    }
  }
  if (strcmp(country_code,"SA") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Al Bahah";
      break;
      case 3:
      pszName = "Al Jawf";
      break;
      case 5:
      pszName = "Al Madinah";
      break;
      case 6:
      pszName = "Ash Sharqiyah";
      break;
      case 8:
      pszName = "Al Qasim";
      break;
      case 9:
      pszName = "Al Qurayyat";
      break;
      case 10:
      pszName = "Ar Riyad";
      break;
      case 13:
      pszName = "Ha'il";
      break;
      case 14:
      pszName = "Makkah";
      break;
      case 15:
      pszName = "Al Hudud ash Shamaliyah";
      break;
      case 16:
      pszName = "Najran";
      break;
      case 17:
      pszName = "Jizan";
      break;
      case 19:
      pszName = "Tabuk";
      break;
      case 20:
      pszName = "Al Jawf";
      break;
    }
  }
  if (strcmp(country_code,"SB") == 0) {
    switch (region_code2) {
      case 3:
      pszName = "Malaita";
      break;
      case 6:
      pszName = "Guadalcanal";
      break;
      case 7:
      pszName = "Isabel";
      break;
      case 8:
      pszName = "Makira";
      break;
      case 9:
      pszName = "Temotu";
      break;
      case 10:
      pszName = "Central";
      break;
      case 11:
      pszName = "Western";
      break;
      case 12:
      pszName = "Choiseul";
      break;
      case 13:
      pszName = "Rennell and Bellona";
      break;
    }
  }
  if (strcmp(country_code,"SC") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Anse aux Pins";
      break;
      case 2:
      pszName = "Anse Boileau";
      break;
      case 3:
      pszName = "Anse Etoile";
      break;
      case 4:
      pszName = "Anse Louis";
      break;
      case 5:
      pszName = "Anse Royale";
      break;
      case 6:
      pszName = "Baie Lazare";
      break;
      case 7:
      pszName = "Baie Sainte Anne";
      break;
      case 8:
      pszName = "Beau Vallon";
      break;
      case 9:
      pszName = "Bel Air";
      break;
      case 10:
      pszName = "Bel Ombre";
      break;
      case 11:
      pszName = "Cascade";
      break;
      case 12:
      pszName = "Glacis";
      break;
      case 13:
      pszName = "Grand' Anse";
      break;
      case 14:
      pszName = "Grand' Anse";
      break;
      case 15:
      pszName = "La Digue";
      break;
      case 16:
      pszName = "La Riviere Anglaise";
      break;
      case 17:
      pszName = "Mont Buxton";
      break;
      case 18:
      pszName = "Mont Fleuri";
      break;
      case 19:
      pszName = "Plaisance";
      break;
      case 20:
      pszName = "Pointe La Rue";
      break;
      case 21:
      pszName = "Port Glaud";
      break;
      case 22:
      pszName = "Saint Louis";
      break;
      case 23:
      pszName = "Takamaka";
      break;
    }
  }
  if (strcmp(country_code,"SD") == 0) {
    switch (region_code2) {
      case 27:
      pszName = "Al Wusta";
      break;
      case 28:
      pszName = "Al Istiwa'iyah";
      break;
      case 29:
      pszName = "Al Khartum";
      break;
      case 30:
      pszName = "Ash Shamaliyah";
      break;
      case 31:
      pszName = "Ash Sharqiyah";
      break;
      case 32:
      pszName = "Bahr al Ghazal";
      break;
      case 33:
      pszName = "Darfur";
      break;
      case 34:
      pszName = "Kurdufan";
      break;
      case 35:
      pszName = "Upper Nile";
      break;
      case 40:
      pszName = "Al Wahadah State";
      break;
      case 44:
      pszName = "Central Equatoria State";
      break;
    }
  }
  if (strcmp(country_code,"SE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Alvsborgs Lan";
      break;
      case 2:
      pszName = "Blekinge Lan";
      break;
      case 3:
      pszName = "Gavleborgs Lan";
      break;
      case 4:
      pszName = "Goteborgs och Bohus Lan";
      break;
      case 5:
      pszName = "Gotlands Lan";
      break;
      case 6:
      pszName = "Hallands Lan";
      break;
      case 7:
      pszName = "Jamtlands Lan";
      break;
      case 8:
      pszName = "Jonkopings Lan";
      break;
      case 9:
      pszName = "Kalmar Lan";
      break;
      case 10:
      pszName = "Dalarnas Lan";
      break;
      case 11:
      pszName = "Kristianstads Lan";
      break;
      case 12:
      pszName = "Kronobergs Lan";
      break;
      case 13:
      pszName = "Malmohus Lan";
      break;
      case 14:
      pszName = "Norrbottens Lan";
      break;
      case 15:
      pszName = "Orebro Lan";
      break;
      case 16:
      pszName = "Ostergotlands Lan";
      break;
      case 17:
      pszName = "Skaraborgs Lan";
      break;
      case 18:
      pszName = "Sodermanlands Lan";
      break;
      case 21:
      pszName = "Uppsala Lan";
      break;
      case 22:
      pszName = "Varmlands Lan";
      break;
      case 23:
      pszName = "Vasterbottens Lan";
      break;
      case 24:
      pszName = "Vasternorrlands Lan";
      break;
      case 25:
      pszName = "Vastmanlands Lan";
      break;
      case 26:
      pszName = "Stockholms Lan";
      break;
      case 27:
      pszName = "Skane Lan";
      break;
      case 28:
      pszName = "Vastra Gotaland";
      break;
    }
  }
  if (strcmp(country_code,"SH") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ascension";
      break;
      case 2:
      pszName = "Saint Helena";
      break;
      case 3:
      pszName = "Tristan da Cunha";
      break;
    }
  }
  if (strcmp(country_code,"SI") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ajdovscina";
      break;
      case 2:
      pszName = "Beltinci";
      break;
      case 3:
      pszName = "Bled";
      break;
      case 4:
      pszName = "Bohinj";
      break;
      case 5:
      pszName = "Borovnica";
      break;
      case 6:
      pszName = "Bovec";
      break;
      case 7:
      pszName = "Brda";
      break;
      case 8:
      pszName = "Brezice";
      break;
      case 9:
      pszName = "Brezovica";
      break;
      case 11:
      pszName = "Celje";
      break;
      case 12:
      pszName = "Cerklje na Gorenjskem";
      break;
      case 13:
      pszName = "Cerknica";
      break;
      case 14:
      pszName = "Cerkno";
      break;
      case 15:
      pszName = "Crensovci";
      break;
      case 16:
      pszName = "Crna na Koroskem";
      break;
      case 17:
      pszName = "Crnomelj";
      break;
      case 19:
      pszName = "Divaca";
      break;
      case 20:
      pszName = "Dobrepolje";
      break;
      case 22:
      pszName = "Dol pri Ljubljani";
      break;
      case 24:
      pszName = "Dornava";
      break;
      case 25:
      pszName = "Dravograd";
      break;
      case 26:
      pszName = "Duplek";
      break;
      case 27:
      pszName = "Gorenja Vas-Poljane";
      break;
      case 28:
      pszName = "Gorisnica";
      break;
      case 29:
      pszName = "Gornja Radgona";
      break;
      case 30:
      pszName = "Gornji Grad";
      break;
      case 31:
      pszName = "Gornji Petrovci";
      break;
      case 32:
      pszName = "Grosuplje";
      break;
      case 34:
      pszName = "Hrastnik";
      break;
      case 35:
      pszName = "Hrpelje-Kozina";
      break;
      case 36:
      pszName = "Idrija";
      break;
      case 37:
      pszName = "Ig";
      break;
      case 38:
      pszName = "Ilirska Bistrica";
      break;
      case 39:
      pszName = "Ivancna Gorica";
      break;
      case 40:
      pszName = "Izola-Isola";
      break;
      case 42:
      pszName = "Jursinci";
      break;
      case 44:
      pszName = "Kanal";
      break;
      case 45:
      pszName = "Kidricevo";
      break;
      case 46:
      pszName = "Kobarid";
      break;
      case 47:
      pszName = "Kobilje";
      break;
      case 49:
      pszName = "Komen";
      break;
      case 50:
      pszName = "Koper-Capodistria";
      break;
      case 51:
      pszName = "Kozje";
      break;
      case 52:
      pszName = "Kranj";
      break;
      case 53:
      pszName = "Kranjska Gora";
      break;
      case 54:
      pszName = "Krsko";
      break;
      case 55:
      pszName = "Kungota";
      break;
      case 57:
      pszName = "Lasko";
      break;
      case 61:
      pszName = "Ljubljana";
      break;
      case 62:
      pszName = "Ljubno";
      break;
      case 64:
      pszName = "Logatec";
      break;
      case 66:
      pszName = "Loski Potok";
      break;
      case 68:
      pszName = "Lukovica";
      break;
      case 71:
      pszName = "Medvode";
      break;
      case 72:
      pszName = "Menges";
      break;
      case 73:
      pszName = "Metlika";
      break;
      case 74:
      pszName = "Mezica";
      break;
      case 76:
      pszName = "Mislinja";
      break;
      case 77:
      pszName = "Moravce";
      break;
      case 78:
      pszName = "Moravske Toplice";
      break;
      case 79:
      pszName = "Mozirje";
      break;
      case 80:
      pszName = "Murska Sobota";
      break;
      case 81:
      pszName = "Muta";
      break;
      case 82:
      pszName = "Naklo";
      break;
      case 83:
      pszName = "Nazarje";
      break;
      case 84:
      pszName = "Nova Gorica";
      break;
      case 86:
      pszName = "Odranci";
      break;
      case 87:
      pszName = "Ormoz";
      break;
      case 88:
      pszName = "Osilnica";
      break;
      case 89:
      pszName = "Pesnica";
      break;
      case 91:
      pszName = "Pivka";
      break;
      case 92:
      pszName = "Podcetrtek";
      break;
      case 94:
      pszName = "Postojna";
      break;
      case 97:
      pszName = "Puconci";
      break;
      case 98:
      pszName = "Racam";
      break;
      case 99:
      pszName = "Radece";
      break;
      case 832:
      pszName = "Radenci";
      break;
      case 833:
      pszName = "Radlje ob Dravi";
      break;
      case 834:
      pszName = "Radovljica";
      break;
      case 837:
      pszName = "Rogasovci";
      break;
      case 838:
      pszName = "Rogaska Slatina";
      break;
      case 839:
      pszName = "Rogatec";
      break;
      case 875:
      pszName = "Semic";
      break;
      case 876:
      pszName = "Sencur";
      break;
      case 877:
      pszName = "Sentilj";
      break;
      case 878:
      pszName = "Sentjernej";
      break;
      case 880:
      pszName = "Sevnica";
      break;
      case 881:
      pszName = "Sezana";
      break;
      case 882:
      pszName = "Skocjan";
      break;
      case 883:
      pszName = "Skofja Loka";
      break;
      case 918:
      pszName = "Skofljica";
      break;
      case 919:
      pszName = "Slovenj Gradec";
      break;
      case 921:
      pszName = "Slovenske Konjice";
      break;
      case 922:
      pszName = "Smarje pri Jelsah";
      break;
      case 923:
      pszName = "Smartno ob Paki";
      break;
      case 924:
      pszName = "Sostanj";
      break;
      case 925:
      pszName = "Starse";
      break;
      case 926:
      pszName = "Store";
      break;
      case 961:
      pszName = "Sveti Jurij";
      break;
      case 962:
      pszName = "Tolmin";
      break;
      case 963:
      pszName = "Trbovlje";
      break;
      case 964:
      pszName = "Trebnje";
      break;
      case 965:
      pszName = "Trzic";
      break;
      case 966:
      pszName = "Turnisce";
      break;
      case 967:
      pszName = "Velenje";
      break;
      case 968:
      pszName = "Velike Lasce";
      break;
      case 1004:
      pszName = "Vipava";
      break;
      case 1005:
      pszName = "Vitanje";
      break;
      case 1006:
      pszName = "Vodice";
      break;
      case 1008:
      pszName = "Vrhnika";
      break;
      case 1009:
      pszName = "Vuzenica";
      break;
      case 1010:
      pszName = "Zagorje ob Savi";
      break;
      case 1012:
      pszName = "Zavrc";
      break;
      case 1047:
      pszName = "Zelezniki";
      break;
      case 1048:
      pszName = "Ziri";
      break;
      case 1049:
      pszName = "Zrece";
      break;
      case 1093:
      pszName = "Dobrova-Horjul-Polhov Gradec";
      break;
      case 1096:
      pszName = "Domzale";
      break;
      case 1136:
      pszName = "Jesenice";
      break;
      case 1138:
      pszName = "Kamnik";
      break;
      case 1139:
      pszName = "Kocevje";
      break;
      case 1177:
      pszName = "Kuzma";
      break;
      case 1178:
      pszName = "Lenart";
      break;
      case 1180:
      pszName = "Litija";
      break;
      case 1181:
      pszName = "Ljutomer";
      break;
      case 1182:
      pszName = "Loska Dolina";
      break;
      case 1184:
      pszName = "Luce";
      break;
      case 1219:
      pszName = "Majsperk";
      break;
      case 1220:
      pszName = "Maribor";
      break;
      case 1223:
      pszName = "Miren-Kostanjevica";
      break;
      case 1225:
      pszName = "Novo Mesto";
      break;
      case 1227:
      pszName = "Piran";
      break;
      case 1266:
      pszName = "Preddvor";
      break;
      case 1268:
      pszName = "Ptuj";
      break;
      case 1305:
      pszName = "Ribnica";
      break;
      case 1307:
      pszName = "Ruse";
      break;
      case 1311:
      pszName = "Sentjur pri Celju";
      break;
      case 1312:
      pszName = "Slovenska Bistrica";
      break;
      case 1392:
      pszName = "Videm";
      break;
      case 1393:
      pszName = "Vojnik";
      break;
      case 1395:
      pszName = "Zalec";
      break;
    }
  }
  if (strcmp(country_code,"SK") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Banska Bystrica";
      break;
      case 2:
      pszName = "Bratislava";
      break;
      case 3:
      pszName = "Kosice";
      break;
      case 4:
      pszName = "Nitra";
      break;
      case 5:
      pszName = "Presov";
      break;
      case 6:
      pszName = "Trencin";
      break;
      case 7:
      pszName = "Trnava";
      break;
      case 8:
      pszName = "Zilina";
      break;
    }
  }
  if (strcmp(country_code,"SL") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Eastern";
      break;
      case 2:
      pszName = "Northern";
      break;
      case 3:
      pszName = "Southern";
      break;
      case 4:
      pszName = "Western Area";
      break;
    }
  }
  if (strcmp(country_code,"SM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Acquaviva";
      break;
      case 2:
      pszName = "Chiesanuova";
      break;
      case 3:
      pszName = "Domagnano";
      break;
      case 4:
      pszName = "Faetano";
      break;
      case 5:
      pszName = "Fiorentino";
      break;
      case 6:
      pszName = "Borgo Maggiore";
      break;
      case 7:
      pszName = "San Marino";
      break;
      case 8:
      pszName = "Monte Giardino";
      break;
      case 9:
      pszName = "Serravalle";
      break;
    }
  }
  if (strcmp(country_code,"SN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Dakar";
      break;
      case 3:
      pszName = "Diourbel";
      break;
      case 4:
      pszName = "Saint-Louis";
      break;
      case 5:
      pszName = "Tambacounda";
      break;
      case 7:
      pszName = "Thies";
      break;
      case 9:
      pszName = "Fatick";
      break;
      case 10:
      pszName = "Kaolack";
      break;
      case 11:
      pszName = "Kolda";
      break;
      case 12:
      pszName = "Ziguinchor";
      break;
      case 13:
      pszName = "Louga";
      break;
      case 14:
      pszName = "Saint-Louis";
      break;
      case 15:
      pszName = "Matam";
      break;
    }
  }
  if (strcmp(country_code,"SO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Bakool";
      break;
      case 2:
      pszName = "Banaadir";
      break;
      case 3:
      pszName = "Bari";
      break;
      case 4:
      pszName = "Bay";
      break;
      case 5:
      pszName = "Galguduud";
      break;
      case 6:
      pszName = "Gedo";
      break;
      case 7:
      pszName = "Hiiraan";
      break;
      case 8:
      pszName = "Jubbada Dhexe";
      break;
      case 9:
      pszName = "Jubbada Hoose";
      break;
      case 10:
      pszName = "Mudug";
      break;
      case 11:
      pszName = "Nugaal";
      break;
      case 12:
      pszName = "Sanaag";
      break;
      case 13:
      pszName = "Shabeellaha Dhexe";
      break;
      case 14:
      pszName = "Shabeellaha Hoose";
      break;
      case 16:
      pszName = "Woqooyi Galbeed";
      break;
      case 18:
      pszName = "Nugaal";
      break;
      case 19:
      pszName = "Togdheer";
      break;
      case 20:
      pszName = "Woqooyi Galbeed";
      break;
      case 21:
      pszName = "Awdal";
      break;
      case 22:
      pszName = "Sool";
      break;
    }
  }
  if (strcmp(country_code,"SR") == 0) {
    switch (region_code2) {
      case 10:
      pszName = "Brokopondo";
      break;
      case 11:
      pszName = "Commewijne";
      break;
      case 12:
      pszName = "Coronie";
      break;
      case 13:
      pszName = "Marowijne";
      break;
      case 14:
      pszName = "Nickerie";
      break;
      case 15:
      pszName = "Para";
      break;
      case 16:
      pszName = "Paramaribo";
      break;
      case 17:
      pszName = "Saramacca";
      break;
      case 18:
      pszName = "Sipaliwini";
      break;
      case 19:
      pszName = "Wanica";
      break;
    }
  }
  if (strcmp(country_code,"ST") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Principe";
      break;
      case 2:
      pszName = "Sao Tome";
      break;
    }
  }
  if (strcmp(country_code,"SV") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ahuachapan";
      break;
      case 2:
      pszName = "Cabanas";
      break;
      case 3:
      pszName = "Chalatenango";
      break;
      case 4:
      pszName = "Cuscatlan";
      break;
      case 5:
      pszName = "La Libertad";
      break;
      case 6:
      pszName = "La Paz";
      break;
      case 7:
      pszName = "La Union";
      break;
      case 8:
      pszName = "Morazan";
      break;
      case 9:
      pszName = "San Miguel";
      break;
      case 10:
      pszName = "San Salvador";
      break;
      case 11:
      pszName = "Santa Ana";
      break;
      case 12:
      pszName = "San Vicente";
      break;
      case 13:
      pszName = "Sonsonate";
      break;
      case 14:
      pszName = "Usulutan";
      break;
    }
  }
  if (strcmp(country_code,"SY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Al Hasakah";
      break;
      case 2:
      pszName = "Al Ladhiqiyah";
      break;
      case 3:
      pszName = "Al Qunaytirah";
      break;
      case 4:
      pszName = "Ar Raqqah";
      break;
      case 5:
      pszName = "As Suwayda'";
      break;
      case 6:
      pszName = "Dar";
      break;
      case 7:
      pszName = "Dayr az Zawr";
      break;
      case 8:
      pszName = "Rif Dimashq";
      break;
      case 9:
      pszName = "Halab";
      break;
      case 10:
      pszName = "Hamah";
      break;
      case 11:
      pszName = "Hims";
      break;
      case 12:
      pszName = "Idlib";
      break;
      case 13:
      pszName = "Dimashq";
      break;
      case 14:
      pszName = "Tartus";
      break;
    }
  }
  if (strcmp(country_code,"SZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Hhohho";
      break;
      case 2:
      pszName = "Lubombo";
      break;
      case 3:
      pszName = "Manzini";
      break;
      case 4:
      pszName = "Shiselweni";
      break;
      case 5:
      pszName = "Praslin";
      break;
    }
  }
  if (strcmp(country_code,"TD") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Batha";
      break;
      case 2:
      pszName = "Biltine";
      break;
      case 3:
      pszName = "Borkou-Ennedi-Tibesti";
      break;
      case 4:
      pszName = "Chari-Baguirmi";
      break;
      case 5:
      pszName = "Guera";
      break;
      case 6:
      pszName = "Kanem";
      break;
      case 7:
      pszName = "Lac";
      break;
      case 8:
      pszName = "Logone Occidental";
      break;
      case 9:
      pszName = "Logone Oriental";
      break;
      case 10:
      pszName = "Mayo-Kebbi";
      break;
      case 11:
      pszName = "Moyen-Chari";
      break;
      case 12:
      pszName = "Ouaddai";
      break;
      case 13:
      pszName = "Salamat";
      break;
      case 14:
      pszName = "Tandjile";
      break;
    }
  }
  if (strcmp(country_code,"TG") == 0) {
    switch (region_code2) {
      case 9:
      pszName = "Lama-Kara";
      break;
      case 18:
      pszName = "Tsevie";
      break;
      case 22:
      pszName = "Centrale";
      break;
      case 23:
      pszName = "Kara";
      break;
      case 24:
      pszName = "Maritime";
      break;
      case 25:
      pszName = "Plateaux";
      break;
      case 26:
      pszName = "Savanes";
      break;
    }
  }
  if (strcmp(country_code,"TH") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Mae Hong Son";
      break;
      case 2:
      pszName = "Chiang Mai";
      break;
      case 3:
      pszName = "Chiang Rai";
      break;
      case 4:
      pszName = "Nan";
      break;
      case 5:
      pszName = "Lamphun";
      break;
      case 6:
      pszName = "Lampang";
      break;
      case 7:
      pszName = "Phrae";
      break;
      case 8:
      pszName = "Tak";
      break;
      case 9:
      pszName = "Sukhothai";
      break;
      case 10:
      pszName = "Uttaradit";
      break;
      case 11:
      pszName = "Kamphaeng Phet";
      break;
      case 12:
      pszName = "Phitsanulok";
      break;
      case 13:
      pszName = "Phichit";
      break;
      case 14:
      pszName = "Phetchabun";
      break;
      case 15:
      pszName = "Uthai Thani";
      break;
      case 16:
      pszName = "Nakhon Sawan";
      break;
      case 17:
      pszName = "Nong Khai";
      break;
      case 18:
      pszName = "Loei";
      break;
      case 20:
      pszName = "Sakon Nakhon";
      break;
      case 21:
      pszName = "Nakhon Phanom";
      break;
      case 22:
      pszName = "Khon Kaen";
      break;
      case 23:
      pszName = "Kalasin";
      break;
      case 24:
      pszName = "Maha Sarakham";
      break;
      case 25:
      pszName = "Roi Et";
      break;
      case 26:
      pszName = "Chaiyaphum";
      break;
      case 27:
      pszName = "Nakhon Ratchasima";
      break;
      case 28:
      pszName = "Buriram";
      break;
      case 29:
      pszName = "Surin";
      break;
      case 30:
      pszName = "Sisaket";
      break;
      case 31:
      pszName = "Narathiwat";
      break;
      case 32:
      pszName = "Chai Nat";
      break;
      case 33:
      pszName = "Sing Buri";
      break;
      case 34:
      pszName = "Lop Buri";
      break;
      case 35:
      pszName = "Ang Thong";
      break;
      case 36:
      pszName = "Phra Nakhon Si Ayutthaya";
      break;
      case 37:
      pszName = "Saraburi";
      break;
      case 38:
      pszName = "Nonthaburi";
      break;
      case 39:
      pszName = "Pathum Thani";
      break;
      case 40:
      pszName = "Krung Thep";
      break;
      case 41:
      pszName = "Phayao";
      break;
      case 42:
      pszName = "Samut Prakan";
      break;
      case 43:
      pszName = "Nakhon Nayok";
      break;
      case 44:
      pszName = "Chachoengsao";
      break;
      case 45:
      pszName = "Prachin Buri";
      break;
      case 46:
      pszName = "Chon Buri";
      break;
      case 47:
      pszName = "Rayong";
      break;
      case 48:
      pszName = "Chanthaburi";
      break;
      case 49:
      pszName = "Trat";
      break;
      case 50:
      pszName = "Kanchanaburi";
      break;
      case 51:
      pszName = "Suphan Buri";
      break;
      case 52:
      pszName = "Ratchaburi";
      break;
      case 53:
      pszName = "Nakhon Pathom";
      break;
      case 54:
      pszName = "Samut Songkhram";
      break;
      case 55:
      pszName = "Samut Sakhon";
      break;
      case 56:
      pszName = "Phetchaburi";
      break;
      case 57:
      pszName = "Prachuap Khiri Khan";
      break;
      case 58:
      pszName = "Chumphon";
      break;
      case 59:
      pszName = "Ranong";
      break;
      case 60:
      pszName = "Surat Thani";
      break;
      case 61:
      pszName = "Phangnga";
      break;
      case 62:
      pszName = "Phuket";
      break;
      case 63:
      pszName = "Krabi";
      break;
      case 64:
      pszName = "Nakhon Si Thammarat";
      break;
      case 65:
      pszName = "Trang";
      break;
      case 66:
      pszName = "Phatthalung";
      break;
      case 67:
      pszName = "Satun";
      break;
      case 68:
      pszName = "Songkhla";
      break;
      case 69:
      pszName = "Pattani";
      break;
      case 70:
      pszName = "Yala";
      break;
      case 71:
      pszName = "Ubon Ratchathani";
      break;
      case 72:
      pszName = "Yasothon";
      break;
      case 73:
      pszName = "Nakhon Phanom";
      break;
      case 75:
      pszName = "Ubon Ratchathani";
      break;
      case 76:
      pszName = "Udon Thani";
      break;
      case 77:
      pszName = "Amnat Charoen";
      break;
      case 78:
      pszName = "Mukdahan";
      break;
    }
  }
  if (strcmp(country_code,"TJ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Kuhistoni Badakhshon";
      break;
      case 2:
      pszName = "Khatlon";
      break;
      case 3:
      pszName = "Sughd";
      break;
    }
  }
  if (strcmp(country_code,"TM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ahal";
      break;
      case 2:
      pszName = "Balkan";
      break;
      case 3:
      pszName = "Dashoguz";
      break;
      case 4:
      pszName = "Lebap";
      break;
      case 5:
      pszName = "Mary";
      break;
    }
  }
  if (strcmp(country_code,"TN") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Al Qasrayn";
      break;
      case 3:
      pszName = "Al Qayrawan";
      break;
      case 6:
      pszName = "Jundubah";
      break;
      case 10:
      pszName = "Qafsah";
      break;
      case 14:
      pszName = "Kef";
      break;
      case 15:
      pszName = "Al Mahdiyah";
      break;
      case 16:
      pszName = "Al Munastir";
      break;
      case 17:
      pszName = "Bajah";
      break;
      case 18:
      pszName = "Banzart";
      break;
      case 19:
      pszName = "Nabul";
      break;
      case 22:
      pszName = "Silyanah";
      break;
      case 23:
      pszName = "Susah";
      break;
      case 26:
      pszName = "Chaiyaphum Province";
      break;
      case 27:
      pszName = "Bin";
      break;
      case 28:
      pszName = "Madanin";
      break;
      case 29:
      pszName = "Qabis";
      break;
      case 30:
      pszName = "Qafsah";
      break;
      case 31:
      pszName = "Qibili";
      break;
      case 32:
      pszName = "Safaqis";
      break;
      case 33:
      pszName = "Sidi Bu Zayd";
      break;
      case 34:
      pszName = "Tatawin";
      break;
      case 35:
      pszName = "Tawzar";
      break;
      case 36:
      pszName = "Tunis";
      break;
      case 37:
      pszName = "Zaghwan";
      break;
      case 38:
      pszName = "Ariana";
      break;
      case 39:
      pszName = "Manouba";
      break;
    }
  }
  if (strcmp(country_code,"TO") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Ha";
      break;
      case 2:
      pszName = "Tongatapu";
      break;
      case 3:
      pszName = "Vava";
      break;
    }
  }
  if (strcmp(country_code,"TR") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Adiyaman";
      break;
      case 3:
      pszName = "Afyonkarahisar";
      break;
      case 4:
      pszName = "Agri";
      break;
      case 5:
      pszName = "Amasya";
      break;
      case 7:
      pszName = "Antalya";
      break;
      case 8:
      pszName = "Artvin";
      break;
      case 9:
      pszName = "Aydin";
      break;
      case 10:
      pszName = "Balikesir";
      break;
      case 11:
      pszName = "Bilecik";
      break;
      case 12:
      pszName = "Bingol";
      break;
      case 13:
      pszName = "Bitlis";
      break;
      case 14:
      pszName = "Bolu";
      break;
      case 15:
      pszName = "Burdur";
      break;
      case 16:
      pszName = "Bursa";
      break;
      case 17:
      pszName = "Canakkale";
      break;
      case 19:
      pszName = "Corum";
      break;
      case 20:
      pszName = "Denizli";
      break;
      case 21:
      pszName = "Diyarbakir";
      break;
      case 22:
      pszName = "Edirne";
      break;
      case 23:
      pszName = "Elazig";
      break;
      case 24:
      pszName = "Erzincan";
      break;
      case 25:
      pszName = "Erzurum";
      break;
      case 26:
      pszName = "Eskisehir";
      break;
      case 28:
      pszName = "Giresun";
      break;
      case 31:
      pszName = "Hatay";
      break;
      case 32:
      pszName = "Icel";
      break;
      case 33:
      pszName = "Isparta";
      break;
      case 34:
      pszName = "Istanbul";
      break;
      case 35:
      pszName = "Izmir";
      break;
      case 37:
      pszName = "Kastamonu";
      break;
      case 38:
      pszName = "Kayseri";
      break;
      case 39:
      pszName = "Kirklareli";
      break;
      case 40:
      pszName = "Kirsehir";
      break;
      case 41:
      pszName = "Kocaeli";
      break;
      case 43:
      pszName = "Kutahya";
      break;
      case 44:
      pszName = "Malatya";
      break;
      case 45:
      pszName = "Manisa";
      break;
      case 46:
      pszName = "Kahramanmaras";
      break;
      case 48:
      pszName = "Mugla";
      break;
      case 49:
      pszName = "Mus";
      break;
      case 50:
      pszName = "Nevsehir";
      break;
      case 52:
      pszName = "Ordu";
      break;
      case 53:
      pszName = "Rize";
      break;
      case 54:
      pszName = "Sakarya";
      break;
      case 55:
      pszName = "Samsun";
      break;
      case 57:
      pszName = "Sinop";
      break;
      case 58:
      pszName = "Sivas";
      break;
      case 59:
      pszName = "Tekirdag";
      break;
      case 60:
      pszName = "Tokat";
      break;
      case 61:
      pszName = "Trabzon";
      break;
      case 62:
      pszName = "Tunceli";
      break;
      case 63:
      pszName = "Sanliurfa";
      break;
      case 64:
      pszName = "Usak";
      break;
      case 65:
      pszName = "Van";
      break;
      case 66:
      pszName = "Yozgat";
      break;
      case 68:
      pszName = "Ankara";
      break;
      case 69:
      pszName = "Gumushane";
      break;
      case 70:
      pszName = "Hakkari";
      break;
      case 71:
      pszName = "Konya";
      break;
      case 72:
      pszName = "Mardin";
      break;
      case 73:
      pszName = "Nigde";
      break;
      case 74:
      pszName = "Siirt";
      break;
      case 75:
      pszName = "Aksaray";
      break;
      case 76:
      pszName = "Batman";
      break;
      case 77:
      pszName = "Bayburt";
      break;
      case 78:
      pszName = "Karaman";
      break;
      case 79:
      pszName = "Kirikkale";
      break;
      case 80:
      pszName = "Sirnak";
      break;
      case 81:
      pszName = "Adana";
      break;
      case 82:
      pszName = "Cankiri";
      break;
      case 83:
      pszName = "Gaziantep";
      break;
      case 84:
      pszName = "Kars";
      break;
      case 85:
      pszName = "Zonguldak";
      break;
      case 86:
      pszName = "Ardahan";
      break;
      case 87:
      pszName = "Bartin";
      break;
      case 88:
      pszName = "Igdir";
      break;
      case 89:
      pszName = "Karabuk";
      break;
      case 90:
      pszName = "Kilis";
      break;
      case 91:
      pszName = "Osmaniye";
      break;
      case 92:
      pszName = "Yalova";
      break;
      case 93:
      pszName = "Duzce";
      break;
    }
  }
  if (strcmp(country_code,"TT") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Arima";
      break;
      case 2:
      pszName = "Caroni";
      break;
      case 3:
      pszName = "Mayaro";
      break;
      case 4:
      pszName = "Nariva";
      break;
      case 5:
      pszName = "Port-of-Spain";
      break;
      case 6:
      pszName = "Saint Andrew";
      break;
      case 7:
      pszName = "Saint David";
      break;
      case 8:
      pszName = "Saint George";
      break;
      case 9:
      pszName = "Saint Patrick";
      break;
      case 10:
      pszName = "San Fernando";
      break;
      case 11:
      pszName = "Tobago";
      break;
      case 12:
      pszName = "Victoria";
      break;
    }
  }
  if (strcmp(country_code,"TW") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Fu-chien";
      break;
      case 2:
      pszName = "Kao-hsiung";
      break;
      case 3:
      pszName = "T'ai-pei";
      break;
      case 4:
      pszName = "T'ai-wan";
      break;
    }
  }
  if (strcmp(country_code,"TZ") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Pwani";
      break;
      case 3:
      pszName = "Dodoma";
      break;
      case 4:
      pszName = "Iringa";
      break;
      case 5:
      pszName = "Kigoma";
      break;
      case 6:
      pszName = "Kilimanjaro";
      break;
      case 7:
      pszName = "Lindi";
      break;
      case 8:
      pszName = "Mara";
      break;
      case 9:
      pszName = "Mbeya";
      break;
      case 10:
      pszName = "Morogoro";
      break;
      case 11:
      pszName = "Mtwara";
      break;
      case 12:
      pszName = "Mwanza";
      break;
      case 13:
      pszName = "Pemba North";
      break;
      case 14:
      pszName = "Ruvuma";
      break;
      case 15:
      pszName = "Shinyanga";
      break;
      case 16:
      pszName = "Singida";
      break;
      case 17:
      pszName = "Tabora";
      break;
      case 18:
      pszName = "Tanga";
      break;
      case 19:
      pszName = "Kagera";
      break;
      case 20:
      pszName = "Pemba South";
      break;
      case 21:
      pszName = "Zanzibar Central";
      break;
      case 22:
      pszName = "Zanzibar North";
      break;
      case 23:
      pszName = "Dar es Salaam";
      break;
      case 24:
      pszName = "Rukwa";
      break;
      case 25:
      pszName = "Zanzibar Urban";
      break;
      case 26:
      pszName = "Arusha";
      break;
      case 27:
      pszName = "Manyara";
      break;
    }
  }
  if (strcmp(country_code,"UA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Cherkas'ka Oblast'";
      break;
      case 2:
      pszName = "Chernihivs'ka Oblast'";
      break;
      case 3:
      pszName = "Chernivets'ka Oblast'";
      break;
      case 4:
      pszName = "Dnipropetrovs'ka Oblast'";
      break;
      case 5:
      pszName = "Donets'ka Oblast'";
      break;
      case 6:
      pszName = "Ivano-Frankivs'ka Oblast'";
      break;
      case 7:
      pszName = "Kharkivs'ka Oblast'";
      break;
      case 8:
      pszName = "Khersons'ka Oblast'";
      break;
      case 9:
      pszName = "Khmel'nyts'ka Oblast'";
      break;
      case 10:
      pszName = "Kirovohrads'ka Oblast'";
      break;
      case 11:
      pszName = "Krym";
      break;
      case 12:
      pszName = "Kyyiv";
      break;
      case 13:
      pszName = "Kyyivs'ka Oblast'";
      break;
      case 14:
      pszName = "Luhans'ka Oblast'";
      break;
      case 15:
      pszName = "L'vivs'ka Oblast'";
      break;
      case 16:
      pszName = "Mykolayivs'ka Oblast'";
      break;
      case 17:
      pszName = "Odes'ka Oblast'";
      break;
      case 18:
      pszName = "Poltavs'ka Oblast'";
      break;
      case 19:
      pszName = "Rivnens'ka Oblast'";
      break;
      case 20:
      pszName = "Sevastopol'";
      break;
      case 21:
      pszName = "Sums'ka Oblast'";
      break;
      case 22:
      pszName = "Ternopil's'ka Oblast'";
      break;
      case 23:
      pszName = "Vinnyts'ka Oblast'";
      break;
      case 24:
      pszName = "Volyns'ka Oblast'";
      break;
      case 25:
      pszName = "Zakarpats'ka Oblast'";
      break;
      case 26:
      pszName = "Zaporiz'ka Oblast'";
      break;
      case 27:
      pszName = "Zhytomyrs'ka Oblast'";
      break;
    }
  }
  if (strcmp(country_code,"UG") == 0) {
    switch (region_code2) {
      case 5:
      pszName = "Busoga";
      break;
      case 8:
      pszName = "Karamoja";
      break;
      case 12:
      pszName = "South Buganda";
      break;
      case 18:
      pszName = "Central";
      break;
      case 20:
      pszName = "Eastern";
      break;
      case 21:
      pszName = "Nile";
      break;
      case 22:
      pszName = "North Buganda";
      break;
      case 23:
      pszName = "Northern";
      break;
      case 24:
      pszName = "Southern";
      break;
      case 25:
      pszName = "Western";
      break;
      case 33:
      pszName = "Jinja";
      break;
      case 36:
      pszName = "Kalangala";
      break;
      case 37:
      pszName = "Kampala";
      break;
      case 42:
      pszName = "Kiboga";
      break;
      case 52:
      pszName = "Mbarara";
      break;
      case 56:
      pszName = "Mubende";
      break;
      case 65:
      pszName = "Adjumani";
      break;
      case 66:
      pszName = "Bugiri";
      break;
      case 67:
      pszName = "Busia";
      break;
      case 69:
      pszName = "Katakwi";
      break;
      case 71:
      pszName = "Masaka";
      break;
      case 73:
      pszName = "Nakasongola";
      break;
      case 74:
      pszName = "Sembabule";
      break;
      case 77:
      pszName = "Arua";
      break;
      case 78:
      pszName = "Iganga";
      break;
      case 79:
      pszName = "Kabarole";
      break;
      case 80:
      pszName = "Kaberamaido";
      break;
      case 81:
      pszName = "Kamwenge";
      break;
      case 82:
      pszName = "Kanungu";
      break;
      case 83:
      pszName = "Kayunga";
      break;
      case 84:
      pszName = "Kitgum";
      break;
      case 85:
      pszName = "Kyenjojo";
      break;
      case 86:
      pszName = "Mayuge";
      break;
      case 87:
      pszName = "Mbale";
      break;
      case 88:
      pszName = "Moroto";
      break;
      case 89:
      pszName = "Mpigi";
      break;
      case 90:
      pszName = "Mukono";
      break;
      case 91:
      pszName = "Nakapiripirit";
      break;
      case 92:
      pszName = "Pader";
      break;
      case 93:
      pszName = "Rukungiri";
      break;
      case 94:
      pszName = "Sironko";
      break;
      case 95:
      pszName = "Soroti";
      break;
      case 96:
      pszName = "Wakiso";
      break;
      case 97:
      pszName = "Yumbe";
      break;
    }
  }
  if (strcmp(country_code,"UY") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Artigas";
      break;
      case 2:
      pszName = "Canelones";
      break;
      case 3:
      pszName = "Cerro Largo";
      break;
      case 4:
      pszName = "Colonia";
      break;
      case 5:
      pszName = "Durazno";
      break;
      case 6:
      pszName = "Flores";
      break;
      case 7:
      pszName = "Florida";
      break;
      case 8:
      pszName = "Lavalleja";
      break;
      case 9:
      pszName = "Maldonado";
      break;
      case 10:
      pszName = "Montevideo";
      break;
      case 11:
      pszName = "Paysandu";
      break;
      case 12:
      pszName = "Rio Negro";
      break;
      case 13:
      pszName = "Rivera";
      break;
      case 14:
      pszName = "Rocha";
      break;
      case 15:
      pszName = "Salto";
      break;
      case 16:
      pszName = "San Jose";
      break;
      case 17:
      pszName = "Soriano";
      break;
      case 18:
      pszName = "Tacuarembo";
      break;
      case 19:
      pszName = "Treinta y Tres";
      break;
    }
  }
  if (strcmp(country_code,"UZ") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Andijon";
      break;
      case 2:
      pszName = "Bukhoro";
      break;
      case 3:
      pszName = "Farghona";
      break;
      case 4:
      pszName = "Jizzakh";
      break;
      case 5:
      pszName = "Khorazm";
      break;
      case 6:
      pszName = "Namangan";
      break;
      case 7:
      pszName = "Nawoiy";
      break;
      case 8:
      pszName = "Qashqadaryo";
      break;
      case 9:
      pszName = "Qoraqalpoghiston";
      break;
      case 10:
      pszName = "Samarqand";
      break;
      case 11:
      pszName = "Sirdaryo";
      break;
      case 12:
      pszName = "Surkhondaryo";
      break;
      case 13:
      pszName = "Toshkent";
      break;
      case 14:
      pszName = "Toshkent";
      break;
    }
  }
  if (strcmp(country_code,"VC") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Charlotte";
      break;
      case 2:
      pszName = "Saint Andrew";
      break;
      case 3:
      pszName = "Saint David";
      break;
      case 4:
      pszName = "Saint George";
      break;
      case 5:
      pszName = "Saint Patrick";
      break;
      case 6:
      pszName = "Grenadines";
      break;
    }
  }
  if (strcmp(country_code,"VE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Amazonas";
      break;
      case 2:
      pszName = "Anzoategui";
      break;
      case 3:
      pszName = "Apure";
      break;
      case 4:
      pszName = "Aragua";
      break;
      case 5:
      pszName = "Barinas";
      break;
      case 6:
      pszName = "Bolivar";
      break;
      case 7:
      pszName = "Carabobo";
      break;
      case 8:
      pszName = "Cojedes";
      break;
      case 9:
      pszName = "Delta Amacuro";
      break;
      case 11:
      pszName = "Falcon";
      break;
      case 12:
      pszName = "Guarico";
      break;
      case 13:
      pszName = "Lara";
      break;
      case 14:
      pszName = "Merida";
      break;
      case 15:
      pszName = "Miranda";
      break;
      case 16:
      pszName = "Monagas";
      break;
      case 17:
      pszName = "Nueva Esparta";
      break;
      case 18:
      pszName = "Portuguesa";
      break;
      case 19:
      pszName = "Sucre";
      break;
      case 20:
      pszName = "Tachira";
      break;
      case 21:
      pszName = "Trujillo";
      break;
      case 22:
      pszName = "Yaracuy";
      break;
      case 23:
      pszName = "Zulia";
      break;
      case 24:
      pszName = "Dependencias Federales";
      break;
      case 25:
      pszName = "Distrito Federal";
      break;
      case 26:
      pszName = "Vargas";
      break;
    }
  }
  if (strcmp(country_code,"VN") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "An Giang";
      break;
      case 2:
      pszName = "Bac Thai";
      break;
      case 3:
      pszName = "Ben Tre";
      break;
      case 4:
      pszName = "Binh Tri Thien";
      break;
      case 5:
      pszName = "Cao Bang";
      break;
      case 7:
      pszName = "Dac Lac";
      break;
      case 9:
      pszName = "Dong Thap";
      break;
      case 11:
      pszName = "Ha Bac";
      break;
      case 12:
      pszName = "Hai Hung";
      break;
      case 13:
      pszName = "Hai Phong";
      break;
      case 14:
      pszName = "Ha Nam Ninh";
      break;
      case 16:
      pszName = "Ha Son Binh";
      break;
      case 17:
      pszName = "Ha Tuyen";
      break;
      case 19:
      pszName = "Hoang Lien Son";
      break;
      case 20:
      pszName = "Ho Chi Minh";
      break;
      case 21:
      pszName = "Kien Giang";
      break;
      case 22:
      pszName = "Lai Chau";
      break;
      case 23:
      pszName = "Lam Dong";
      break;
      case 24:
      pszName = "Long An";
      break;
      case 25:
      pszName = "Minh Hai";
      break;
      case 26:
      pszName = "Nghe Tinh";
      break;
      case 27:
      pszName = "Nghia Binh";
      break;
      case 28:
      pszName = "Phu Khanh";
      break;
      case 29:
      pszName = "Quang Nam-Da Nang";
      break;
      case 30:
      pszName = "Quang Ninh";
      break;
      case 31:
      pszName = "Song Be";
      break;
      case 32:
      pszName = "Son La";
      break;
      case 33:
      pszName = "Tay Ninh";
      break;
      case 34:
      pszName = "Thanh Hoa";
      break;
      case 35:
      pszName = "Thai Binh";
      break;
      case 36:
      pszName = "Thuan Hai";
      break;
      case 37:
      pszName = "Tien Giang";
      break;
      case 38:
      pszName = "Vinh Phu";
      break;
      case 39:
      pszName = "Lang Son";
      break;
      case 40:
      pszName = "Dong Nai";
      break;
      case 43:
      pszName = "An Giang";
      break;
      case 44:
      pszName = "Dac Lac";
      break;
      case 45:
      pszName = "Dong Nai";
      break;
      case 46:
      pszName = "Dong Thap";
      break;
      case 47:
      pszName = "Kien Giang";
      break;
      case 48:
      pszName = "Minh Hai";
      break;
      case 49:
      pszName = "Song Be";
      break;
      case 50:
      pszName = "Vinh Phu";
      break;
      case 51:
      pszName = "Ha Noi";
      break;
      case 52:
      pszName = "Ho Chi Minh";
      break;
      case 53:
      pszName = "Ba Ria-Vung Tau";
      break;
      case 54:
      pszName = "Binh Dinh";
      break;
      case 55:
      pszName = "Binh Thuan";
      break;
      case 56:
      pszName = "Can Tho";
      break;
      case 57:
      pszName = "Gia Lai";
      break;
      case 58:
      pszName = "Ha Giang";
      break;
      case 59:
      pszName = "Ha Tay";
      break;
      case 60:
      pszName = "Ha Tinh";
      break;
      case 61:
      pszName = "Hoa Binh";
      break;
      case 62:
      pszName = "Khanh Hoa";
      break;
      case 63:
      pszName = "Kon Tum";
      break;
      case 64:
      pszName = "Quang Tri";
      break;
      case 65:
      pszName = "Nam Ha";
      break;
      case 66:
      pszName = "Nghe An";
      break;
      case 67:
      pszName = "Ninh Binh";
      break;
      case 68:
      pszName = "Ninh Thuan";
      break;
      case 69:
      pszName = "Phu Yen";
      break;
      case 70:
      pszName = "Quang Binh";
      break;
      case 71:
      pszName = "Quang Ngai";
      break;
      case 72:
      pszName = "Quang Tri";
      break;
      case 73:
      pszName = "Soc Trang";
      break;
      case 74:
      pszName = "Thua Thien";
      break;
      case 75:
      pszName = "Tra Vinh";
      break;
      case 76:
      pszName = "Tuyen Quang";
      break;
      case 77:
      pszName = "Vinh Long";
      break;
      case 78:
      pszName = "Da Nang";
      break;
      case 79:
      pszName = "Hai Duong";
      break;
      case 80:
      pszName = "Ha Nam";
      break;
      case 81:
      pszName = "Hung Yen";
      break;
      case 82:
      pszName = "Nam Dinh";
      break;
      case 83:
      pszName = "Phu Tho";
      break;
      case 84:
      pszName = "Quang Nam";
      break;
      case 85:
      pszName = "Thai Nguyen";
      break;
      case 86:
      pszName = "Vinh Puc Province";
      break;
      case 87:
      pszName = "Can Tho";
      break;
      case 88:
      pszName = "Dak Lak";
      break;
      case 89:
      pszName = "Lai Chau";
      break;
      case 90:
      pszName = "Lao Cai";
      break;
      case 91:
      pszName = "Dak Nong";
      break;
      case 92:
      pszName = "Dien Bien";
      break;
      case 93:
      pszName = "Hau Giang";
      break;
    }
  }
  if (strcmp(country_code,"VU") == 0) {
    switch (region_code2) {
      case 5:
      pszName = "Ambrym";
      break;
      case 6:
      pszName = "Aoba";
      break;
      case 7:
      pszName = "Torba";
      break;
      case 8:
      pszName = "Efate";
      break;
      case 9:
      pszName = "Epi";
      break;
      case 10:
      pszName = "Malakula";
      break;
      case 11:
      pszName = "Paama";
      break;
      case 12:
      pszName = "Pentecote";
      break;
      case 13:
      pszName = "Sanma";
      break;
      case 14:
      pszName = "Shepherd";
      break;
      case 15:
      pszName = "Tafea";
      break;
      case 16:
      pszName = "Malampa";
      break;
      case 17:
      pszName = "Penama";
      break;
      case 18:
      pszName = "Shefa";
      break;
    }
  }
  if (strcmp(country_code,"WS") == 0) {
    switch (region_code2) {
      case 2:
      pszName = "Aiga-i-le-Tai";
      break;
      case 3:
      pszName = "Atua";
      break;
      case 4:
      pszName = "Fa";
      break;
      case 5:
      pszName = "Gaga";
      break;
      case 6:
      pszName = "Va";
      break;
      case 7:
      pszName = "Gagaifomauga";
      break;
      case 8:
      pszName = "Palauli";
      break;
      case 9:
      pszName = "Satupa";
      break;
      case 10:
      pszName = "Tuamasaga";
      break;
      case 11:
      pszName = "Vaisigano";
      break;
    }
  }
  if (strcmp(country_code,"YE") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Abyan";
      break;
      case 2:
      pszName = "Adan";
      break;
      case 3:
      pszName = "Al Mahrah";
      break;
      case 4:
      pszName = "Hadramawt";
      break;
      case 5:
      pszName = "Shabwah";
      break;
      case 8:
      pszName = "Al Hudaydah";
      break;
      case 10:
      pszName = "Al Mahwit";
      break;
      case 11:
      pszName = "Dhamar";
      break;
      case 14:
      pszName = "Ma'rib";
      break;
      case 15:
      pszName = "Sa";
      break;
      case 16:
      pszName = "San";
      break;
      case 20:
      pszName = "Al Bayda'";
      break;
      case 21:
      pszName = "Al Jawf";
      break;
      case 22:
      pszName = "Hajjah";
      break;
      case 23:
      pszName = "Ibb";
      break;
      case 24:
      pszName = "Lahij";
      break;
      case 25:
      pszName = "Ta";
      break;
    }
  }
  if (strcmp(country_code,"ZA") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "North-Western Province";
      break;
      case 2:
      pszName = "KwaZulu-Natal";
      break;
      case 3:
      pszName = "Free State";
      break;
      case 5:
      pszName = "Eastern Cape";
      break;
      case 6:
      pszName = "Gauteng";
      break;
      case 7:
      pszName = "Mpumalanga";
      break;
      case 8:
      pszName = "Northern Cape";
      break;
      case 9:
      pszName = "Limpopo";
      break;
      case 10:
      pszName = "North-West";
      break;
      case 11:
      pszName = "Western Cape";
      break;
    }
  }
  if (strcmp(country_code,"ZM") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Western";
      break;
      case 2:
      pszName = "Central";
      break;
      case 3:
      pszName = "Eastern";
      break;
      case 4:
      pszName = "Luapula";
      break;
      case 5:
      pszName = "Northern";
      break;
      case 6:
      pszName = "North-Western";
      break;
      case 7:
      pszName = "Southern";
      break;
      case 8:
      pszName = "Copperbelt";
      break;
      case 9:
      pszName = "Lusaka";
      break;
    }
  }
  if (strcmp(country_code,"ZW") == 0) {
    switch (region_code2) {
      case 1:
      pszName = "Manicaland";
      break;
      case 2:
      pszName = "Midlands";
      break;
      case 3:
      pszName = "Mashonaland Central";
      break;
      case 4:
      pszName = "Mashonaland East";
      break;
      case 5:
      pszName = "Mashonaland West";
      break;
      case 6:
      pszName = "Matabeleland North";
      break;
      case 7:
      pszName = "Matabeleland South";
      break;
      case 8:
      pszName = "Masvingo";
      break;
      case 9:
      pszName = "Bulawayo";
      break;
      case 10:
      pszName = "Harare";
      break;
    }
  }
  return pszName;
}
