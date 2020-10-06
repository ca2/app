#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "acme/const/id.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"
#include "apex/platform/str_context.h"


#ifdef LINUX
void enum_display_monitors(::aura::session * psession);
#endif // LINUX


#ifdef WINDOWS_DESKTOP



//#include "base/os/windows/windows_system_interaction_impl.h"


#include <HighLevelMonitorConfigurationAPI.h>

DWORD mc_color_kelvin(MC_COLOR_TEMPERATURE e)
{
   switch (e)
   {
   case MC_COLOR_TEMPERATURE_4000K:
      return 4000;
   case MC_COLOR_TEMPERATURE_5000K:
      return 5000;
   case MC_COLOR_TEMPERATURE_6500K:
      return 6500;
   case MC_COLOR_TEMPERATURE_7500K:
      return 7500;
   case MC_COLOR_TEMPERATURE_8200K:
      return 8200;
   case MC_COLOR_TEMPERATURE_9300K:
      return 9300;
   case MC_COLOR_TEMPERATURE_10000K:
      return 10000;
   case MC_COLOR_TEMPERATURE_11500K:
      return 11500;
   default:
      return 0;
   }
}

MC_COLOR_TEMPERATURE kelvin_mc_color(DWORD kelvin)
{
   if (kelvin < 4500)
   {
      return MC_COLOR_TEMPERATURE_4000K;
   }
   else if (kelvin < 5750)
   {
      return MC_COLOR_TEMPERATURE_5000K;
   }
   else if (kelvin < 7000)
   {
      return MC_COLOR_TEMPERATURE_6500K;
   }
   else if (kelvin < 7850)
   {
      return MC_COLOR_TEMPERATURE_7500K;
   }
   else if (kelvin < 8750)
   {
      return MC_COLOR_TEMPERATURE_8200K;
   }
   else if (kelvin < 9650)
   {
      return MC_COLOR_TEMPERATURE_9300K;
   }
   else if (kelvin < 10750)
   {
      return MC_COLOR_TEMPERATURE_10000K;
   }
   else
   {
      return MC_COLOR_TEMPERATURE_11500K;
   }
}




#elif defined(LINUX)


#endif



CLASS_DECL_AURA ::user::interaction * create_system_message_window(::layered * pobject);


#if defined(APPLE_IOS)

#include "aura/node/ios/interaction_impl.h"

#endif


#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)


namespace PLATFORM_NAMESPACE
{


   CLASS_DECL_AURA ::user::interaction * create_host_window();


} // namespace PLATFORM_NAMESPACE


#endif


#ifdef CUBE
extern "C"
::aura::application * cube_get_app();
#endif

void defer_term_ui();


//bool is_verbose();

//extern string_map < __pointer(::apex::library) >* g_pmapLibrary;
//extern ::mutex * &::get_context_system()->m_mutexLibrary;
//extern string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary;

int_bool point_is_window_origin(POINT ptHitTest, oswindow oswindowExclude, int iMargin);

#ifdef _UWP

#include "aura/os/uwp/_uwp.h"

#elif defined(LINUX)

void x11_on_start_session();

#endif


namespace aura
{


   /* colorramp.c -- color temperature calculation source
This file is part of Redshift.
Redshift is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Redshift is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Redshift.  If not, see <http://www.gnu.org/licenses/>.
Copyright (c) 2013-2014  Jon Lund Steffensen <jonlst@gmail.com>
Copyright (c) 2013  Ingo Thies <ithies@astro.uni-bonn.de>
*/

/* Whitepoint values for temperatures at 100K intervals.
These will be interpolated for the actual temperature.
This table was provided by Ingo Thies, 2013. See
the file README-colorramp for more information. */
   static const float g_fa_blackbody_color[] =
   {
      1.00000000f,  0.18172716f,  0.00000000f, /* 1000K */
      1.00000000f,  0.25503671f,  0.00000000f, /* 1100K */
      1.00000000f,  0.30942099f,  0.00000000f, /* 1200K */
      1.00000000f,  0.35357379f,  0.00000000f, /* ...   */
      1.00000000f,  0.39091524f,  0.00000000f,
      1.00000000f,  0.42322816f,  0.00000000f,
      1.00000000f,  0.45159884f,  0.00000000f,
      1.00000000f,  0.47675916f,  0.00000000f,
      1.00000000f,  0.49923747f,  0.00000000f,
      1.00000000f,  0.51943421f,  0.00000000f,
      1.00000000f,  0.54360078f,  0.08679949f,
      1.00000000f,  0.56618736f,  0.14065513f,
      1.00000000f,  0.58734976f,  0.18362641f,
      1.00000000f,  0.60724493f,  0.22137978f,
      1.00000000f,  0.62600248f,  0.25591950f,
      1.00000000f,  0.64373109f,  0.28819679f,
      1.00000000f,  0.66052319f,  0.31873863f,
      1.00000000f,  0.67645822f,  0.34786758f,
      1.00000000f,  0.69160518f,  0.37579588f,
      1.00000000f,  0.70602449f,  0.40267128f,
      1.00000000f,  0.71976951f,  0.42860152f,
      1.00000000f,  0.73288760f,  0.45366838f,
      1.00000000f,  0.74542112f,  0.47793608f,
      1.00000000f,  0.75740814f,  0.50145662f,
      1.00000000f,  0.76888303f,  0.52427322f,
      1.00000000f,  0.77987699f,  0.54642268f,
      1.00000000f,  0.79041843f,  0.56793692f,
      1.00000000f,  0.80053332f,  0.58884417f,
      1.00000000f,  0.81024551f,  0.60916971f,
      1.00000000f,  0.81957693f,  0.62893653f,
      1.00000000f,  0.82854786f,  0.64816570f,
      1.00000000f,  0.83717703f,  0.66687674f,
      1.00000000f,  0.84548188f,  0.68508786f,
      1.00000000f,  0.85347859f,  0.70281616f,
      1.00000000f,  0.86118227f,  0.72007777f,
      1.00000000f,  0.86860704f,  0.73688797f,
      1.00000000f,  0.87576611f,  0.75326132f,
      1.00000000f,  0.88267187f,  0.76921169f,
      1.00000000f,  0.88933596f,  0.78475236f,
      1.00000000f,  0.89576933f,  0.79989606f,
      1.00000000f,  0.90198230f,  0.81465502f,
      1.00000000f,  0.90963069f,  0.82838210f,
      1.00000000f,  0.91710889f,  0.84190889f,
      1.00000000f,  0.92441842f,  0.85523742f,
      1.00000000f,  0.93156127f,  0.86836903f,
      1.00000000f,  0.93853986f,  0.88130458f,
      1.00000000f,  0.94535695f,  0.89404470f,
      1.00000000f,  0.95201559f,  0.90658983f,
      1.00000000f,  0.95851906f,  0.91894041f,
      1.00000000f,  0.96487079f,  0.93109690f,
      1.00000000f,  0.97107439f,  0.94305985f,
      1.00000000f,  0.97713351f,  0.95482993f,
      1.00000000f,  0.98305189f,  0.96640795f,
      1.00000000f,  0.98883326f,  0.97779486f,
      1.00000000f,  0.99448139f,  0.98899179f,
      1.00000000f,  1.00000000f,  1.00000000f, /* 6500K */
      0.98947904f,  0.99348723f,  1.00000000f,
      0.97940448f,  0.98722715f,  1.00000000f,
      0.96975025f,  0.98120637f,  1.00000000f,
      0.96049223f,  0.97541240f,  1.00000000f,
      0.95160805f,  0.96983355f,  1.00000000f,
      0.94303638f,  0.96443333f,  1.00000000f,
      0.93480451f,  0.95923080f,  1.00000000f,
      0.92689056f,  0.95421394f,  1.00000000f,
      0.91927697f,  0.94937330f,  1.00000000f,
      0.91194747f,  0.94470005f,  1.00000000f,
      0.90488690f,  0.94018594f,  1.00000000f,
      0.89808115f,  0.93582323f,  1.00000000f,
      0.89151710f,  0.93160469f,  1.00000000f,
      0.88518247f,  0.92752354f,  1.00000000f,
      0.87906581f,  0.92357340f,  1.00000000f,
      0.87315640f,  0.91974827f,  1.00000000f,
      0.86744421f,  0.91604254f,  1.00000000f,
      0.86191983f,  0.91245088f,  1.00000000f,
      0.85657444f,  0.90896831f,  1.00000000f,
      0.85139976f,  0.90559011f,  1.00000000f,
      0.84638799f,  0.90231183f,  1.00000000f,
      0.84153180f,  0.89912926f,  1.00000000f,
      0.83682430f,  0.89603843f,  1.00000000f,
      0.83225897f,  0.89303558f,  1.00000000f,
      0.82782969f,  0.89011714f,  1.00000000f,
      0.82353066f,  0.88727974f,  1.00000000f,
      0.81935641f,  0.88452017f,  1.00000000f,
      0.81530175f,  0.88183541f,  1.00000000f,
      0.81136180f,  0.87922257f,  1.00000000f,
      0.80753191f,  0.87667891f,  1.00000000f,
      0.80380769f,  0.87420182f,  1.00000000f,
      0.80018497f,  0.87178882f,  1.00000000f,
      0.79665980f,  0.86943756f,  1.00000000f,
      0.79322843f,  0.86714579f,  1.00000000f,
      0.78988728f,  0.86491137f,  1.00000000f, /* 10000K */
      0.78663296f,  0.86273225f,  1.00000000f,
      0.78346225f,  0.86060650f,  1.00000000f,
      0.78037207f,  0.85853224f,  1.00000000f,
      0.77735950f,  0.85650771f,  1.00000000f,
      0.77442176f,  0.85453121f,  1.00000000f,
      0.77155617f,  0.85260112f,  1.00000000f,
      0.76876022f,  0.85071588f,  1.00000000f,
      0.76603147f,  0.84887402f,  1.00000000f,
      0.76336762f,  0.84707411f,  1.00000000f,
      0.76076645f,  0.84531479f,  1.00000000f,
      0.75822586f,  0.84359476f,  1.00000000f,
      0.75574383f,  0.84191277f,  1.00000000f,
      0.75331843f,  0.84026762f,  1.00000000f,
      0.75094780f,  0.83865816f,  1.00000000f,
      0.74863017f,  0.83708329f,  1.00000000f,
      0.74636386f,  0.83554194f,  1.00000000f,
      0.74414722f,  0.83403311f,  1.00000000f,
      0.74197871f,  0.83255582f,  1.00000000f,
      0.73985682f,  0.83110912f,  1.00000000f,
      0.73778012f,  0.82969211f,  1.00000000f,
      0.73574723f,  0.82830393f,  1.00000000f,
      0.73375683f,  0.82694373f,  1.00000000f,
      0.73180765f,  0.82561071f,  1.00000000f,
      0.72989845f,  0.82430410f,  1.00000000f,
      0.72802807f,  0.82302316f,  1.00000000f,
      0.72619537f,  0.82176715f,  1.00000000f,
      0.72439927f,  0.82053539f,  1.00000000f,
      0.72263872f,  0.81932722f,  1.00000000f,
      0.72091270f,  0.81814197f,  1.00000000f,
      0.71922025f,  0.81697905f,  1.00000000f,
      0.71756043f,  0.81583783f,  1.00000000f,
      0.71593234f,  0.81471775f,  1.00000000f,
      0.71433510f,  0.81361825f,  1.00000000f,
      0.71276788f,  0.81253878f,  1.00000000f,
      0.71122987f,  0.81147883f,  1.00000000f,
      0.70972029f,  0.81043789f,  1.00000000f,
      0.70823838f,  0.80941546f,  1.00000000f,
      0.70678342f,  0.80841109f,  1.00000000f,
      0.70535469f,  0.80742432f,  1.00000000f,
      0.70395153f,  0.80645469f,  1.00000000f,
      0.70257327f,  0.80550180f,  1.00000000f,
      0.70121928f,  0.80456522f,  1.00000000f,
      0.69988894f,  0.80364455f,  1.00000000f,
      0.69858167f,  0.80273941f,  1.00000000f,
      0.69729688f,  0.80184943f,  1.00000000f,
      0.69603402f,  0.80097423f,  1.00000000f,
      0.69479255f,  0.80011347f,  1.00000000f,
      0.69357196f,  0.79926681f,  1.00000000f,
      0.69237173f,  0.79843391f,  1.00000000f,
      0.69119138f,  0.79761446f,  1.00000000f, /* 15000K */
      0.69003044f,  0.79680814f,  1.00000000f,
      0.68888844f,  0.79601466f,  1.00000000f,
      0.68776494f,  0.79523371f,  1.00000000f,
      0.68665951f,  0.79446502f,  1.00000000f,
      0.68557173f,  0.79370830f,  1.00000000f,
      0.68450119f,  0.79296330f,  1.00000000f,
      0.68344751f,  0.79222975f,  1.00000000f,
      0.68241029f,  0.79150740f,  1.00000000f,
      0.68138918f,  0.79079600f,  1.00000000f,
      0.68038380f,  0.79009531f,  1.00000000f,
      0.67939381f,  0.78940511f,  1.00000000f,
      0.67841888f,  0.78872517f,  1.00000000f,
      0.67745866f,  0.78805526f,  1.00000000f,
      0.67651284f,  0.78739518f,  1.00000000f,
      0.67558112f,  0.78674472f,  1.00000000f,
      0.67466317f,  0.78610368f,  1.00000000f,
      0.67375872f,  0.78547186f,  1.00000000f,
      0.67286748f,  0.78484907f,  1.00000000f,
      0.67198916f,  0.78423512f,  1.00000000f,
      0.67112350f,  0.78362984f,  1.00000000f,
      0.67027024f,  0.78303305f,  1.00000000f,
      0.66942911f,  0.78244457f,  1.00000000f,
      0.66859988f,  0.78186425f,  1.00000000f,
      0.66778228f,  0.78129191f,  1.00000000f,
      0.66697610f,  0.78072740f,  1.00000000f,
      0.66618110f,  0.78017057f,  1.00000000f,
      0.66539706f,  0.77962127f,  1.00000000f,
      0.66462376f,  0.77907934f,  1.00000000f,
      0.66386098f,  0.77854465f,  1.00000000f,
      0.66310852f,  0.77801705f,  1.00000000f,
      0.66236618f,  0.77749642f,  1.00000000f,
      0.66163375f,  0.77698261f,  1.00000000f,
      0.66091106f,  0.77647551f,  1.00000000f,
      0.66019791f,  0.77597498f,  1.00000000f,
      0.65949412f,  0.77548090f,  1.00000000f,
      0.65879952f,  0.77499315f,  1.00000000f,
      0.65811392f,  0.77451161f,  1.00000000f,
      0.65743716f,  0.77403618f,  1.00000000f,
      0.65676908f,  0.77356673f,  1.00000000f,
      0.65610952f,  0.77310316f,  1.00000000f,
      0.65545831f,  0.77264537f,  1.00000000f,
      0.65481530f,  0.77219324f,  1.00000000f,
      0.65418036f,  0.77174669f,  1.00000000f,
      0.65355332f,  0.77130560f,  1.00000000f,
      0.65293404f,  0.77086988f,  1.00000000f,
      0.65232240f,  0.77043944f,  1.00000000f,
      0.65171824f,  0.77001419f,  1.00000000f,
      0.65112144f,  0.76959404f,  1.00000000f,
      0.65053187f,  0.76917889f,  1.00000000f,
      0.64994941f,  0.76876866f,  1.00000000f, /* 20000K */
      0.64937392f,  0.76836326f,  1.00000000f,
      0.64880528f,  0.76796263f,  1.00000000f,
      0.64824339f,  0.76756666f,  1.00000000f,
      0.64768812f,  0.76717529f,  1.00000000f,
      0.64713935f,  0.76678844f,  1.00000000f,
      0.64659699f,  0.76640603f,  1.00000000f,
      0.64606092f,  0.76602798f,  1.00000000f,
      0.64553103f,  0.76565424f,  1.00000000f,
      0.64500722f,  0.76528472f,  1.00000000f,
      0.64448939f,  0.76491935f,  1.00000000f,
      0.64397745f,  0.76455808f,  1.00000000f,
      0.64347129f,  0.76420082f,  1.00000000f,
      0.64297081f,  0.76384753f,  1.00000000f,
      0.64247594f,  0.76349813f,  1.00000000f,
      0.64198657f,  0.76315256f,  1.00000000f,
      0.64150261f,  0.76281076f,  1.00000000f,
      0.64102399f,  0.76247267f,  1.00000000f,
      0.64055061f,  0.76213824f,  1.00000000f,
      0.64008239f,  0.76180740f,  1.00000000f,
      0.63961926f,  0.76148010f,  1.00000000f,
      0.63916112f,  0.76115628f,  1.00000000f,
      0.63870790f,  0.76083590f,  1.00000000f,
      0.63825953f,  0.76051890f,  1.00000000f,
      0.63781592f,  0.76020522f,  1.00000000f,
      0.63737701f,  0.75989482f,  1.00000000f,
      0.63694273f,  0.75958764f,  1.00000000f,
      0.63651299f,  0.75928365f,  1.00000000f,
      0.63608774f,  0.75898278f,  1.00000000f,
      0.63566691f,  0.75868499f,  1.00000000f,
      0.63525042f,  0.75839025f,  1.00000000f,
      0.63483822f,  0.75809849f,  1.00000000f,
      0.63443023f,  0.75780969f,  1.00000000f,
      0.63402641f,  0.75752379f,  1.00000000f,
      0.63362667f,  0.75724075f,  1.00000000f,
      0.63323097f,  0.75696053f,  1.00000000f,
      0.63283925f,  0.75668310f,  1.00000000f,
      0.63245144f,  0.75640840f,  1.00000000f,
      0.63206749f,  0.75613641f,  1.00000000f,
      0.63168735f,  0.75586707f,  1.00000000f,
      0.63131096f,  0.75560036f,  1.00000000f,
      0.63093826f,  0.75533624f,  1.00000000f,
      0.63056920f,  0.75507467f,  1.00000000f,
      0.63020374f,  0.75481562f,  1.00000000f,
      0.62984181f,  0.75455904f,  1.00000000f,
      0.62948337f,  0.75430491f,  1.00000000f,
      0.62912838f,  0.75405319f,  1.00000000f,
      0.62877678f,  0.75380385f,  1.00000000f,
      0.62842852f,  0.75355685f,  1.00000000f,
      0.62808356f,  0.75331217f,  1.00000000f,
      0.62774186f,  0.75306977f,  1.00000000f, /* 25000K */
      0.62740336f,  0.75282962f,  1.00000000f  /* 25100K */
   };

   static void
      interpolate_color(float a, const float* c1, const float* c2, float* r, float* g, float* b)
   {
      *r = (1.0f - a) * c1[0] + a * c2[0];
      *g = (1.0f - a) * c1[1] + a * c2[1];
      *b = (1.0f - a) * c1[2] + a * c2[2];
   }


   CLASS_DECL_AURA void black_body(float* r, float* g, float* b, DWORD dwTemp)
   {

      int temp_index = ((dwTemp - 1000) / 100) * 3;

      if (temp_index < 0)
      {

         temp_index = 0;

      }
      else if (temp_index > (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3)
      {

         temp_index = (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3;

      }

      float alpha = (dwTemp % 100) / 100.0f;

      interpolate_color(alpha, &g_fa_blackbody_color[temp_index], &g_fa_blackbody_color[temp_index + 3], r, g, b);

   }


   session::session()
   {

      m_paurasession = this;

      m_bAcceptsFirstResponder = true;

      m_bSimpleMessageLoop = false;
      m_bMessageThread = true;
      m_iEdge = -1;
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pcoresession = nullptr;


      create_factory < ::user::user >();
      create_factory < ::aura::session, ::aura::session >();

      //m_strAppId                    = "core_session";
      //m_strAppName                  = "core_session";
      //m_strBaseSupportId            = "core_session";
      //m_strInstallToken             = "core_session";

      m_puiLastUserInputPopup = nullptr;

      //m_pdocs = create_session_docs();

      //m_bLicense				               = false;

      //m_bLicense           = false;
      //m_eexclusiveinstance = ExclusiveInstanceNone;

   }


   session::~session()
   {

      output_debug_string("aura::session::~session()");

   }


   ::estatus session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::aqua::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      m_bSystemSynchronizedScreen      = true;

      m_pimplPendingFocus2             = nullptr;

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_bDrawCursor                    = false;

      m_pappCurrent                    = nullptr;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_iMainMonitor                   = -1;

      __compose_new(m_psavings);

      m_bZipIsDir2                     = true;

      m_iEdge                          = 0;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;


      //m_strAppId = "base_session";
//m_strAppName = "base_session";
//m_strBaseSupportId = "base_session";
//m_strInstallToken = "base_session";

      m_iMainMonitor = -1;

      m_puiCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_ecursorDefault = cursor_arrow;

      m_ecursor = cursor_default;

      m_puiMouseMoveCapture = nullptr;

      estatus = __compose_new(m_psavings);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::user::style* session::get_user_style()
   {

      return nullptr;

   }


   void session::simple_ui_draw_focus_rect(::user::interaction* pinteraction, ::draw2d::graphics_pointer& pgraphics)
   {


   }


   void session::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {


   }


   string session::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   bool session::is_session() const
   {

      return true;

   }




   COLORREF session::get_default_color(u64 ui)
   {

      switch (ui)
      {
      case COLOR_3DFACE:
         return ARGB(127, 192, 192, 184);
      case COLOR_WINDOW:
         return ARGB(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return ARGB(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return ARGB(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return ARGB(127, 90, 90, 80);
      default:
         break;
      }

      return ARGB(127, 0, 0, 0);

   }






   size session::get_window_minimum_size()
   {

      return size(300, 300);

   }


   ::estatus session::init_thread()
   {

      auto estatus = process_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init_session();

      if (!estatus)
      {

         return estatus;

      }

      // // now there is attempt here
      //estatus = defer_initialize_host_window();

      //if(!estatus)
      //{

      //   __throw(::exception::exception(estatus));

      //}


      INFO(".1");

      return true;

      return estatus;

   }


   void session::term_thread()
   {

      try
      {

         term_session();

      }
      catch (...)
      {

      }

      try
      {

         process_term();

      }
      catch(...)
      {

      }

      ::thread::term_thread();

   }


   ::estatus session::process_init()
   {

      INFO("aura::session::process_init");

      auto estatus = ::apex::session::process_init();

      if (!estatus)
      {

         return estatus;

      }


      estatus = __compose_new(m_puserstrcontext);

      if (!estatus)
      {

         INFO("apex::str_context Failed to Allocate!!");

         return estatus;

      }

      auto& system = System;

      if(system.m_bAvoidFirstResponder)
      {

         m_bAcceptsFirstResponder = false;

      }

      INFO("apex::str_context Succeeded to Allocate!!");

      INFO("aura::session::process_init success");

      return ::success;

   }


   ::estatus session::init_session()
   {

      auto estatus = init1();

      if (!estatus)
      {

         message_box("::aura::session::init1 Failed");

         return estatus;

      }

      estatus = init2();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void session::term_session()
   {

      try
      {

         term2();

      }
      catch (...)
      {

      }

      try
      {

         term1();

      }
      catch (...)
      {

      }

      try
      {

         term();

      }
      catch (...)
      {

      }



   }

   //::estatus session::init()
   //{



   //   return true;

   //}


   //void session::term()
   //{

   //   m_paccount.release();






   //}


   void session::term2()
   {

      // __release(m_ptheme);

      //m_mapTheme.remove_all();

#ifdef WINDOWS_DESKTOP

      __release(m_puiSession);

#endif


   }


   void session::term1()
   {


   }


   void session::process_term()
   {

      System.session_remove(m_iEdge);

   }


   bool session::defer_create_session_frame_window()
   {

#ifdef WINDOWS_DESKTOP

      if (m_puiSession)
      {

         return true;

      }

      ::estatus estatus = __compose(m_puiSession, ::move(create_system_message_window(this)));

      if (!estatus)
      {

         return false;

      }

#endif

      return true;

   }


   bool session::on_get_thread_name(string& strThreadName)
   {

      if (get_context_system()->is_console_app())
      {

         return false;

      }

      return ::apex::session::on_get_thread_name(strThreadName);

   }


   void session::on_request(::create * pcreate)
   {

      ::apex::session::on_request(pcreate);

      //// it was here
      ////auto estatus = defer_initialize_host_window();
      ////
      ////if(!estatus)
      ////{
      ////
      ////   __throw(::exception::exception(estatus));
      ////
      ////}

      //if (pcreate->m_ecommand == command_protocol)
      //{

      //   m_pappCurrent->do_request(pcreate);

      //   return;

      //}

      //TRACE("::aura::session::on_request(__pointer(::create)) " + string(type_name()));

      //INFO("::aura::session::on_request(__pointer(::create)) %s ", __c_str(THIS_FRIENDLY_NAME()));

      //if (pcreate->m_strAppId.has_char())
      //{

      //   INFO("m_strAppId = " + pcreate->m_strAppId);

      //   start_application(pcreate->m_strAppId, pcreate, m_strLocale, m_strSchema);

      //   return;

      //}

      //INFO("m_strAppId Is Empty!!");

      //string strApp = pcreate->m_pcommandline->m_strApp;

      //if (strApp == "app/sphere/userstack")
      //{

      //   start_application("app/sphere/userstack", pcreate, m_strLocale, m_strSchema);

      //}

      //m_varCurrentViewFile = pcreate->m_pcommandline->m_varFile;


      ////string strApp;

      ////if ((pcreate->m_pcommandline->m_varQuery["app"].array_get_count() > 1
      ////      || pcreate->m_pcommandline->m_varQuery["show_platform"] == 1 || m_varTopicQuery["show_platform"] == 1)
      ////      && (!(bool)pcreate->m_pcommandline->m_varQuery.has_property("client_only") && !(bool)has_property("client_only"))
      ////      && (!pcreate->m_pcommandline->m_varQuery.has_property("client_only") && !has_property("client_only")))
      ////{
      ////   m_bShowPlatform = true;
      ////}

      //bool bCreate = true;
      //if (pcreate->m_pcommandline->m_strApp.is_empty())
      //{
      //   if (!pcreate->m_pcommandline->m_varFile.is_empty())
      //   {
      //      if (!open_by_file_extension(pcreate))
      //      {
      //         if (m_pappCurrent != nullptr)
      //         {
      //            App(m_pappCurrent).request({pcreate});
      //         }
      //      }
      //   }
      //   else if (m_bShowPlatform)
      //   {
      //      //create_bergedge(pcreate);
      //      //if(get_document() != nullptr && get_document()->get_typed_view < ::bergedge::view >() != nullptr)
      //      //{
      //      //   __pointer(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
      //      //   if(pframe != nullptr)
      //      //   {
      //      //      pframe->display(display_normal);
      //      //      pframe->InitialFramePosition();
      //      //   }
      //      //}
      //   }
      //   if (pcreate->m_pcommandline->m_varQuery["app"].array_get_count() <= 0)
      //   {
      //      bCreate = false;
      //   }
      //}
      //if (bCreate)
      //{
      //   if (pcreate->m_pcommandline->m_strApp == "bergedge")
      //   {
      //      if (pcreate->m_pcommandline->m_varQuery.has_property("session_start"))
      //      {
      //         strApp = pcreate->m_pcommandline->m_varQuery["session_start"];
      //      }
      //      else
      //      {
      //         strApp = "bergedge";
      //      }
      //   }
      //   else
      //   {
      //      strApp = pcreate->m_pcommandline->m_strApp;
      //   }


      //   if (pcreate->m_pcommandline->m_varQuery["app"].stra().find_first_ci(strApp) < 0)
      //   {

      //      pcreate->m_pcommandline->m_varQuery["app"].stra().insert_at(0, strApp);

      //   }

      //   for (i32 i = 0; i < pcreate->m_pcommandline->m_varQuery["app"].stra().get_count(); i++)
      //   {

      //      strApp = pcreate->m_pcommandline->m_varQuery["app"].stra()[i];

      //      if (strApp.is_empty() || strApp == "bergedge")
      //      {

      //         return;

      //      }

      //      if (strApp == "session")
      //      {

      //         continue;

      //      }

      //      ::aura::application * papp = application_get(strApp, true, true, pcreate);

      //      if (papp == nullptr)
      //      {

      //         if(System.has_property("install")
      //               || System.has_property("uninstall"))
      //         {

      //            ::multithreading::set_finish(&System);

      //         }
      //         else
      //         {

      //            message_box("Could not create requested application: \"" + strApp + "\"");

      //            ::count c = System.value("app").array_get_count();

      //            if (c == 1 && System.value("app").at(0) == strApp)
      //            {

      //               ::multithreading::set_finish(&System);

      //            }

      //         }

      //         return;

      //      }

      //      pcreate->m_pcommandline->m_eventReady.ResetEvent();

      //      if (strApp != "bergedge")
      //      {

      //         if(!papp->on_start_application())
      //         {

      //            TRACE("One or more errors occurred during on_start_application execution.");

      //         }

      //         //if (System.is_true("install"))
      //         if (is_true("install"))
      //         {

      //            papp->do_install();

      //            System.finalize();

      //         }
      //         else
      //         {

      //            if (!papp->is_system() && !papp->is_session())
      //            {

      //               System.merge_accumulated_on_open_file(pcreate);

      //            }

      //            papp->request({pcreate});

      //         }

      //         m_pappCurrent = papp;

      //      }

      //   }

      //}

   }


   //__pointer(::user::menu_interaction) session::create_menu_button(::user::style_pointer & pstyle,::user::menu_item * pitem)
   //{

   //   __throw(interface_only_exception());

   //   return nullptr;

   //}


   bool session::open_by_file_extension(const char * pszPathName, ::create * pcreate)
   {

      auto pcreateNew = __create_new < ::create >();

      pcreateNew->m_pcommandline->m_varFile = pszPathName;

      pcreateNew->m_puserinteractionParent = pcreate->m_puserinteractionParent;

      return open_by_file_extension(pcreateNew);

      //return Application.platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      //return Application.platform_open_by_file_extension(m_iEdge, pcc);

      string strId;

      string strOriginalPathName(pcreate->m_pcommandline->m_varFile);

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if (iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if (::str::ends_ci(strPathName, ".ca2"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreate->m_pcommandline->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.extension();

         string_array straApp;

         __throw(todo("filehandler"));

         //System.filehandler().get_extension_app(straApp, strExtension);

         //if (straApp.get_count() == 1)
         //{

         //   strId = straApp[0];

         //}
         //else
         //{

         //   strId = "app/sphere/default_file_handler";

         //}

      }

      ::apex::application* papp = application_get(strId, true, true, pcreate);

      if (papp == nullptr)
      {

         return false;

      }

      papp->do_request(pcreate);

      return true;

   }


   //::aura::application * session::application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate)
   //{

   //   __pointer(::aura::application) papp;

   //   if (m_applicationa.lookup(pszAppId, papp))
   //   {

   //      return papp;

   //   }
   //   else
   //   {

   //      if (!bCreate)
   //      {

   //         return nullptr;

   //      }

   //      papp = nullptr;

   //      try
   //      {

   //         papp = create_application(pszAppId, bSynch, pcreate);

   //      }
   //      catch (::exception_pointer pe)
   //      {

   //         // aura::session, axis::session and ::base::session, could get more specialized handling in aura::application (aura::system)
   //         // Thank you Mummi (em Santos, cuidando do Lucinho e ajudando um monte a Carô e o Lúcio e Eu 2019-01-15) !! Thank you God!! <3tbs

   //         handle_exception(pe);

   //         //if (!Sys(this).on_run_exception(esp))
   //         //{

   //         //   if (!App(this).on_run_exception(esp))
   //         //   {

   //         //      papp = nullptr;

   //         //   }

   //         //}

   //         //papp = nullptr;

   //      }
   //      catch (...)
   //      {

   //         //papp = nullptr;

   //      }

   //      if (!papp)
   //      {

   //         return nullptr;

   //      }

   //      app_add(papp);

   //      return papp;

   //   }

   //}


//   __pointer(::aura::application) session::get_new_application(::layered * pobjectContext, const char * pszAppId)
//   {
//
//      string strAppId(pszAppId);
//
//      __pointer(::aura::application) papp;
//
//      if (!papp)
//      {
//
//         if (System.m_pappcore != nullptr && System.m_pmaindata && System.m_pfnNewAuraApplication != nullptr)
//         {
//
//            papp = System.m_pfnNewAuraApplication();
//
//            if (papp.is_null())
//            {
//
//               return nullptr;
//
//            }
//
//            auto estatus = papp->initialize(pobjectContext);
//
//            if (!estatus)
//            {
//
//               m_result.add(estatus);
//
//               return nullptr;
//
//            }
//
//            papp->m_strLibraryName = strAppId;
//
//
//         }
//         sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//         __pointer(::apex::library) & plibrary = &::get_context_system()->m_mapLibrary[pszAppId];
//
//         if (!plibrary)
//         {
//
//            if (System.m_pappcore != nullptr && System.m_pfnNewAuraLibrary != nullptr)
//            {
//
//               plibrary = __move_transfer(System.m_pfnNewAuraLibrary());
//
//            }
//            else
//            {
//
//               ::aura_app * pauraapp = ::aura_app::get(pszAppId);
//
//               if (pauraapp != nullptr)
//               {
//
//                  if (pauraapp->m_pfnNewAuraLibrary != nullptr)
//                  {
//
//                     plibrary = __move_transfer(pauraapp->m_pfnNewAuraLibrary());
//
//                  }
//                  else if (pauraapp->m_pfnNewAuraApplication != nullptr)
//                  {
//
//                     papp = __move_transfer(pauraapp->m_pfnNewAuraApplication());
//
//                     if (papp.is_null())
//                     {
//
//                        return nullptr;
//
//                     }
//
//                     papp->m_strLibraryName = pszAppId;
//
//                  }
//
//               }
//
//               if (papp.is_null())
//               {
//
//                  if (plibrary)
//                  {
//
//                     plibrary->initialize_aura_library(pobjectContext, 0, nullptr);
//
//                  }
//                  else
//                  {
//
//                     plibrary = __new(::apex::library);
//
//                     plibrary->initialize_aura_library(pobjectContext, 0, nullptr);
//
//                     //g_pmapLibrary[string(pszAppId)] = plibrary;
//
//                     string strLibrary = strAppId;
//
//                     strLibrary.replace("/", "_");
//
//                     strLibrary.replace("-", "_");
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application assembled library path " + strLibrary + "\n\n");
//
//                     }
//
//                     if (!plibrary->open(strLibrary, false))
//                     {
//
//#ifndef _UWP
//
//                        os_message_box(nullptr, "Application \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", MB_ICONERROR);
//
//#endif
//
//                        return nullptr;
//
//                     }
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application Found library : " + strLibrary + "\n\n");
//
//                     }
//
//                     // error anticipation maybe counter-self-healing
//   //               if (!plibrary->is_opened())
//   //               {
//   //
//   //                  ::output_debug_string("\n\n::aura::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
//   //
//   //                  return nullptr;
//   //
//   //               }
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application Opened library : " + strLibrary + "\n\n");
//
//                     }
//
//                     if (!plibrary->open_ca2_library())
//                     {
//
//                        ::output_debug_string("\n\n::aura::session::get_new_application open_ca2_library failed(2) : " + strLibrary + "\n\n");
//
//                        return nullptr;
//
//                     }
//
//                     if (is_verbose())
//                     {
//
//                        ::output_debug_string("\n\n\n|(5)----");
//                        ::output_debug_string("| app : " + strAppId + "\n");
//                        ::output_debug_string("|\n");
//                        ::output_debug_string("|\n");
//                        ::output_debug_string("|----");
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         if (papp.is_null())
//
//         {
//
//            ::apex::library & library = *plibrary;
//
//
//            papp = library.get_new_application(this, strAppId);
//
//            ::output_debug_string("\n\n\n|(4)----");
//            ::output_debug_string("| app : " + strAppId + "(papp=0x" + ::hex::upper_from((uptr)papp.m_p) + ")\n");
//            ::output_debug_string("|\n");
//            ::output_debug_string("|\n");
//            ::output_debug_string("|----");
//
//         }
//
//         if (!papp)
//         {
//
//            return nullptr;
//
//         }
//
//      }
//
//#ifdef WINDOWS_DESKTOP
//
//      WCHAR wsz[1024];
//
//      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
//
//      GetUserNameW(wsz, &dwSize);
//
//      string strUserName = wsz;
//
//#endif // WINDOWS_DESKTOP
//
//      if (is_verbose())
//      {
//
//         ::output_debug_string("\n\n\n|(3)----");
//         ::output_debug_string("| app : " + strAppId + "\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|----");
//
//      }
//
//      if (is_verbose())
//      {
//
//         ::output_debug_string("\n\n\n|(2)----");
//         ::output_debug_string("| app : " + strAppId + "\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|----");
//
//      }
//
//#if !defined(ANDROID)
//
//      if (!papp->is_serviceable() || papp->is_user_service())
//      {
//
//         System.m_spmutexUserAppData = __new(::mutex(e_create_new, false, "Local\\ca2.UserAppData"));
//         System.m_spmutexSystemAppData = __new(::mutex(e_create_new, false, "Local\\ca2.SystemAppData"));
//
//      }
//
//#endif
//
//      if (is_verbose())
//      {
//
//         ::output_debug_string("\n\n\n|(1)----");
//         ::output_debug_string("| app : " + strAppId + "\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|\n");
//         ::output_debug_string("|----");
//
//      }
//
//      papp->m_strAppId = pszAppId;
//
//      set_context_app(papp);
//
//      return papp;
//
//   }


   //void session::interactive_credentials(::account::credentials * pcredentials)
   //{

   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;

   //}


   bool session::is_licensed(const char * pszAppId, bool bInteractive)
   {

      if (has_property("install"))
      {

         return true;

      }

      if (has_property("uninstall"))
      {

         return true;

      }

      return false;

      //if(m_paccount.is_null())
      //{

      //   return false;

      //}

      //return m_paccount->is_licensed(pszAppId, bInteractive);

   }


   //::account::user * session::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   //{

   //   if(m_paccount.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return m_paccount->get_user(pathUrl, bFetch, bInteractive);

   //}


//   ::account::user * session::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->interactive_get_user();
//
//   }
//
//
//   ::account::user * session::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->noninteractive_get_user(pathUrl);
//
//   }


   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      throw 0;

      return false;

      //return account()->get_auth(pszForm, strUsername, strPassword);

   }


   //void session::defer_initialize_user_presence()
   //{


   //}

   //void session::translate_os_key_message(::user::key * pkey)
   //{

   //}


   bool session::set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor)
   {

      m_ecursor = cursor_draw2d;

      m_pcursor = pcursor;

      if (pcursor != nullptr)
      {

         if (!pcursor->set_current(pinteraction, this))
         {

            return false;

         }

      }
      else
      {

         if (!::draw2d::cursor::reset(pinteraction, this))
         {

            return false;

         }

      }

      return true;

   }


   bool session::set_cursor(::user::interaction * pinteraction, e_cursor ecursor)
   {

      m_ecursor = ecursor;

      ::draw2d::cursor * pcursor = get_cursor();

      if (pcursor != nullptr)
      {

         if (!pcursor->set_current(pinteraction, this))
         {

            return false;

         }

      }
      else
      {

         if (!::draw2d::cursor::reset(pinteraction, this))
         {

            return false;

         }

      }

      return true;

   }


   bool session::set_default_cursor(::user::interaction * pinteraction, e_cursor ecursor)
   {

      if (ecursor == cursor_default)
      {

         m_ecursorDefault = cursor_arrow;

      }
      else
      {

         m_ecursorDefault = ecursor;

      }

      return true;

   }


   //bool session::on_create_frame_window()
   //{

   //   defer_create_session_frame_window();

   //   return true;

   //}


   ::user::primitive * session::GetFocus()
   {

      return System.ui_from_handle(::get_focus());

   }


   ::user::primitive * session::GetActiveWindow()
   {

      return System.ui_from_handle(::get_active_window());

   }


   ::user::primitive * session::clear_focus()
   {

      ::user::primitive * pprimitiveFocus = get_keyboard_focus();

      if(::is_null(pprimitiveFocus))
      {

         return nullptr;

      }

      auto puserinteraction = pprimitiveFocus->get_wnd();

      if(!puserinteraction)
      {

         return nullptr;

      }

      puserinteraction->set_focus_primitive(nullptr);

      set_keyboard_focus(nullptr);

      puserinteraction->set_need_redraw();

      puserinteraction->post_redraw();

      return pprimitiveFocus;

   }

   ::user::primitive * session::get_keyboard_focus()
   {

      oswindow oswindowFocus = ::get_focus();

      if (oswindowFocus == nullptr)
      {

         return nullptr;

      }

      oswindow oswindow = oswindowFocus;

      while (oswindow != nullptr)
      {

         ::user::interaction_impl * pimpl = ::oswindow_interaction_impl(oswindow);

         if (pimpl != nullptr)
         {

            if (pimpl->get_focus_primitive() != nullptr)
            {

               return pimpl->get_focus_primitive();

            }

            return pimpl->m_puserinteraction;

         }

#ifdef WINDOWS_DESKTOP

         oswindow = ::GetParent(oswindow);

         if (oswindow != nullptr)
         {

            oswindow = ::get_window(oswindow, GW_OWNER);

         }

#else

         break;

#endif

      }

      return nullptr;

   }


   ::user::keyboard& session::keyboard()
   {

      if (!m_pkeyboard)
      {

         auto estatus = __compose_new(m_pkeyboard);

         if (!m_pkeyboard)
         {

            __throw(::exception::exception("Could not create keyboard"));

         }
//
//#if !defined(WINDOWS) && !defined(__APPLE__)
//
//         if (!m_pkeyboard->initialize())
//         {
//
//            __throw(::exception::exception("Could not initialize keyboard"));
//
//         }
//
//#endif

         //Application.on_create_keyboard();

      }

      return *m_pkeyboard;

   }


   bool session::set_keyboard_focus(::user::primitive * pprimitive)
   {

      if (pprimitive == nullptr)
      {

         m_pimplPendingFocus2 = nullptr;

         ::set_focus(nullptr);

         return false;

      }

      ::user::interaction * pinteraction = pprimitive->get_wnd();

      if (pinteraction == nullptr)
      {

         return false;

      }

      ::user::interaction * puiImpl = pinteraction->get_wnd();

      if (puiImpl == nullptr)
      {

         return false;

      }

      ::user::interaction_impl * pimpl = puiImpl->m_pimpl.cast < ::user::interaction_impl > ();

      if (pimpl == nullptr)
      {

         ASSERT(FALSE);

         return false;

      }

      bool bHasFocus = puiImpl->has_focus();

      if (!pimpl->set_focus_primitive(pprimitive))
      {

         return false;

      }

      if(bHasFocus)
      {

         return true;

      }

#ifdef WINDOWS_DESKTOP
      //if (!IsWindowVisible(pimpl->m_oswindow) || pinteraction->GetExStyle() & WS_EX_LAYERED)
      if (!IsWindowVisible(pimpl->m_oswindow))
      {

         pimpl->set_pending_focus();

      }
      else
#endif
      {

         ::set_focus(pimpl->m_oswindow);

      }

      return true;

      //::user::primitive * pkeyboardfocusParam = pkeyboardfocus;

      //if (pkeyboardfocus == nullptr)
      //{

      //   pkeyboardfocus = (::user::primitive *) (ulong_ptr) 1;

      //}

      //if (m_pkeyboardfocus != nullptr && m_pkeyboardfocus != pkeyboardfocus && m_pkeyboardfocusRequest != pkeyboardfocus)
      //{

      //   ::user::primitive * pkeyboardfocusOld = m_pkeyboardfocus;

      //   m_pkeyboardfocusRequest = pkeyboardfocus;

      //   try
      //   {

      //      if (pkeyboardfocusOld != nullptr)
      //      {

      //         output_debug_string("axis::session::set_keyboard_focus pkeyboardfocusOld->keyboard_focus_OnKillFocus()\n");

      //         if (!pkeyboardfocusOld->keyboard_focus_OnKillFocus( (pkeyboardfocus != nullptr &&
      //               pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1) ?
      //               pkeyboardfocus->get_safe_handle() : nullptr))
      //         {

      //            return;

      //         }

      //         __pointer(::user::interaction) pinteraction = pkeyboardfocusOld;

      //         if (pinteraction.is_set())
      //         {

      //            pinteraction->send_message(WM_KILLFOCUS, (WPARAM) ( (pkeyboardfocus != nullptr &&
      //                              pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1 )?
      //                              pkeyboardfocus->get_safe_handle() : nullptr));

      //         }

      //      }

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      //if (pkeyboardfocus == (::user::primitive *) (ulong_ptr) 1)
      //{

      //   pkeyboardfocus = nullptr;

      //}

      //if (pkeyboardfocus != nullptr)
      //{

      //   if (!pkeyboardfocus->keyboard_focus_OnSetFocus())
      //   {

      //      return;

      //   }

      //   if (pkeyboardfocus->get_wnd() != nullptr)
      //   {

      //      if (!pkeyboardfocus->get_wnd_primitive()->on_keyboard_focus(pkeyboardfocus))
      //      {

      //         return;

      //      }

      //   }

      //}

      //m_pkeyboardfocus = pkeyboardfocus;

      //on_finally_focus_set(pkeyboardfocus);

   }


   //void session::on_finally_focus_set(::user::primitive * pprimitiveFocus)
   //{



   //}

   ::user::primitive * session::get_active_ui()
   {

      return nullptr;

   }


   ::user::primitive * session::get_focus_ui()
   {

      auto window = ::get_focus();

      if (!window)
      {

         return nullptr;

      }

      auto puserinteraction = System.ui_from_handle(window);

      if (!puserinteraction)
      {

         return nullptr;

      }

      auto puserinteractionFocus = puserinteraction->get_focus_primitive();

      if (!puserinteractionFocus)
      {

         return puserinteraction;

      }

      return puserinteractionFocus;

   }


   void session::on_finally_focus_set(::user::primitive * pprimitiveFocus)
   {

      user()->set_mouse_focus_LButtonDown(pprimitiveFocus);

      if (pprimitiveFocus == nullptr)
      {

         return;

      }

      __pointer(::user::interaction) puiFocus = pprimitiveFocus;

      if (puiFocus.is_set())
      {

         if (!puiFocus->get_wnd()->is_active())
         {

            if (puiFocus->get_wnd() != nullptr)
            {

               puiFocus->get_wnd()->SetActiveWindow();

            }

         }

         if (puiFocus->GetFocus() != puiFocus->get_wnd())
         {

            if (puiFocus->get_wnd() != nullptr)
            {

               puiFocus->get_wnd()->SetFocus();

            }

         }

#if defined(APPLE_IOS)

         main_async([this]()
         {

            __pointer(::ios::interaction_impl) pimpl = Session.m_puiHost->m_pimpl;

            if (pimpl.is_set())
            {

               pimpl->defer_update_text_view();

            }

         });

#endif

      }


   }


   bool session::on_ui_mouse_message(::message::mouse * pmouse)
   {


      //::axis::session::on_ui_mouse_message(pmouse);

      if (pmouse->m_point == pmouse->m_pointDesired)
      {

         m_pointCursor = pmouse->m_point;

      }

      i64 iMessage = pmouse->m_id;

      if(iMessage == WM_LBUTTONDOWN
       //|| iMessage == WM_LBUTTONUP
       || iMessage == WM_RBUTTONDOWN
       //|| iMessage == WM_RBUTTONUP
       || iMessage == WM_MBUTTONDOWN
       //|| iMessage == WM_MBUTTONUP
       )
       {

         if(m_uiptraToolWindow.has_element())
         {

            __pointer_array(::user::interaction) uiptraToolWindow;

            {

               sync_lock sl(mutex());

               ::papaya::array::copy(uiptraToolWindow, m_uiptraToolWindow);

            }

            for(auto & pinteraction : uiptraToolWindow.ptra())
            {

               if(pinteraction != pmouse->userinteraction())
               {

                  if(pinteraction->m_bFocus)
                  {

                     pinteraction->post_message(WM_KILLFOCUS);

                  }

               }

            }

         }

       }

      //if (m_puserpresence.is_set())
      //{

      //   m_puserpresence->on_ui_mouse_message(pmouse);

      //}
      return true;

   }


   ::draw2d::cursor * session::get_cursor()
   {

      if (m_ecursor == cursor_none)
      {

         return nullptr;

      }
      else if (m_ecursor == cursor_default)
      {

         return System.draw2d().get_cursor(m_ecursorDefault);

      }
      else
      {

         return System.draw2d().get_cursor(m_ecursor);

      }

   }


   //::draw2d::cursor * session::get_default_cursor()
   //{

   //   return nullptr;

   //}


   void session::get_cursor_pos(LPPOINT ppoint)
   {

#if defined(WINDOWS_DESKTOP)

      if (m_bSystemSynchronizedCursor)
      {

         POINT point;

         ::get_cursor_pos(&point);

         m_pointCursor = point;

      }

#endif

      if (ppoint != nullptr)
      {

         *ppoint = m_pointCursor;

      }

   }


   oswindow session::get_capture()
   {

      return ::get_capture();

   }


   void session::set_cursor_pos(const ::point & point)
   {

#ifdef WINDOWS_DESKTOP

      ::SetCursorPos(point.x, point.y);

#endif

   }


   bool session::ReleaseCapture()
   {

      // oswindow oswindowCapture = ::get_capture();

      // if (oswindowCapture == nullptr)
      // {

      //    return false;

      // }

      ::release_capture();

      m_puiCapture = nullptr;

      return true;


   }


   __pointer(::user::interaction) session::GetCapture()
   {

      oswindow oswindowCapture = ::get_capture();

      if (oswindowCapture == nullptr)
      {

         return nullptr;

      }

      __pointer(::user::interaction) pinteraction = System.ui_from_handle(oswindowCapture);

      if (pinteraction.is_null())
      {

         return nullptr;

      }

      return pinteraction->GetCapture();

   }


   ::user::copydesk& session::copydesk()
   {

      if (!m_pcopydesk)
      {

         __compose(m_pcopydesk);

      }

      return *m_pcopydesk;

   }


   //index session::get_main_wkspace(RECT * prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      if (m_iMainWkspace >= 0 && m_iMainWkspace < get_monitor_count())
   //      {

   //         return get_main_wkspace(prect);

   //      }
   //      else
   //      {

   //         if (get_monitor_rect(m_iMainWkspace, prect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            get_wkspace_rect(0, prect);


   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      index iMainWkspace = m_iMainWkspace;

   //      if (iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
   //      {

   //         iMainWkspace = 0;

   //      }

   //      if (m_rectaWkspace.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      if(prect != nullptr)
   //      {

   //         *prect = m_rectaWkspace[iMainWkspace];

   //      }

   //      return iMainWkspace;

   //   }

   //}


   bool session::set_main_wkspace(index iWkspace)
   {

      if (iWkspace == -1)
      {

         m_iMainWkspace = -1;

         return true;

      }
      else if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }
      else
      {

         m_iMainWkspace = iWkspace;

         return true;

      }

   }


#ifdef WINDOWS_DESKTOP

   BOOL CALLBACK session::monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, RECT* prcMonitor, LPARAM dwData)

   {

      ::aura::session* psystem = (::aura::session*) dwData;

      psystem->monitor_enum(hmonitor, hdcMonitor, prcMonitor);


      return TRUE; // to enumerate all

   }

   void session::monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, RECT* prcMonitor)

   {

      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(prcMonitor);


      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      xxf_zero(m_monitorinfoa.last());

      m_hmonitora.add(hmonitor);

      m_monitorinfoa.last().cbSize = sizeof(MONITORINFO);

      ::GetMonitorInfo(hmonitor, &m_monitorinfoa.last());

      MONITORINFO mi = m_monitorinfoa.last();

      TRACE("session::monitor_enum\n");
      TRACE("upper_bound %d\n", m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);

   }


#endif


   void session::enum_display_monitors()
   {

#ifdef WINDOWS_DESKTOP

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(nullptr, nullptr, &session::monitor_enum_proc, (LPARAM)(dynamic_cast <::aura::session*> (this)));

#elif defined(LINUX)

      ::enum_display_monitors(this);

#endif

   }



   index session::get_main_monitor(RECT* prect)
   {

      index iMainMonitor = 0;

#ifdef WINDOWS_DESKTOP

      HMONITOR hmonitorPrimary = GetPrimaryMonitorHandle();

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         if (m_hmonitora[iMonitor] == hmonitorPrimary)
         {

            iMainMonitor = iMonitor;

            break;

         }

      }


#endif

      if (prect != nullptr)

      {

         get_monitor_rect(iMainMonitor, prect);


      }

      return iMainMonitor;

   }


   ::count session::get_monitor_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#elif defined(MACOS)

      return GetScreenCount();

#elif defined(LINUX)

      sync_lock sl(mutex());

      return m_rectaMonitor.get_count();

#else

      return 1;

#endif

   }


   bool session::get_monitor_rect(index iMonitor, RECT* prect)
   {

#ifdef _UWP

      return false;

#elif MOBILE_PLATFORM

      GetMainScreenRect(prect);

      return true;

#elif defined(WINDOWS_DESKTOP)

      if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      *prect = m_monitorinfoa[iMonitor].rcMonitor;


#elif defined(_UWP)


      return false;


#elif defined(LINUX)

      sync_lock sl(mutex());

      if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      *prect = m_rectaMonitor[iMonitor];


#elif defined(__APPLE__)

      if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      GetScreenRect(prect, (int)iMonitor);


#else

      prect->left = 0;

      prect->top = 0;

      prect->right = oslocal().m_iScreenWidth;

      prect->bottom = oslocal().m_iScreenHeight;


#endif

      return true;

   }


   ::count session::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool session::get_desk_monitor_rect(index iMonitor, RECT* prect)

   {

      return get_monitor_rect(iMonitor, prect);


   }


   index session::get_main_wkspace(RECT* prect)

   {

      index iMainWkspace = 0;

#ifdef WINDOWS_DESKTOP

      HMONITOR hwkspacePrimary = GetPrimaryMonitorHandle();

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         if (m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }


#endif

      if (prect != nullptr)

      {

         get_wkspace_rect(iMainWkspace, prect);


      }

      return iMainWkspace;

   }


   ::count session::get_wkspace_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#else

      return get_monitor_count();

#endif

   }


   bool session::get_wkspace_rect(index iWkspace, RECT* prect)
   {

#ifdef WINDOWS_DESKTOP

      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
         return false;

      *prect = m_monitorinfoa[iWkspace].rcWork;


#elif defined(_UWP)

      return get_monitor_rect(iWkspace, prect);


      //#elif defined(LINUX)
      //
      //return false;
      //
#elif defined(__APPLE__)

      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }

      GetWkspaceRect(prect, (int)iWkspace);


      //      prect->top += ::mac::get_system_main_menu_bar_height();

      //    prect->bottom -= ::mac::get_system_dock_height();

#elif defined(LINUX)

      sync_lock sl(mutex());

      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }

      *prect = m_rectaWork[iWkspace];


      return true;

#else

      //__throw(todo());

      //::get_window_rect(::get_desktop_window(),prect);


      get_monitor_rect(iWkspace, prect);


#endif

      return true;

   }


   ::count session::get_desk_wkspace_count()
   {

      return get_wkspace_count();

   }


   bool session::get_desk_wkspace_rect(index iWkspace, RECT* prect)

   {

      return get_wkspace_rect(iWkspace, prect);


   }

   //   index session::get_ui_wkspace(::user::interaction * pinteraction)
   //   {
   //
   //      index iMainWkspace = 0;
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      HMONITOR hwkspacePrimary = GetUiMonitorHandle(pinteraction->get_handle());
   //
   //      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
   //      {
   //
   //         if (m_hmonitora[iWkspace] == hwkspacePrimary)
   //         {
   //
   //            iMainWkspace = iWkspace;
   //
   //            break;
   //
   //         }
   //
   //      }
   //
   //#endif
   //
   //      return iMainWkspace;
   //
   //   }

   //index session::get_main_monitor(RECT * prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      if (m_iMainMonitor < 0 || m_iMainMonitor >= System.get_monitor_count())
   //      {

   //         return System.get_main_monitor(prect);

   //      }
   //      else
   //      {

   //         if (System.get_monitor_rect(m_iMainMonitor, prect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            System.get_monitor_rect(0, prect);

   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      index iMainMonitor = m_iMainMonitor;

   //      if (iMainMonitor < 0 || iMainMonitor >= m_rectaMonitor.get_count())
   //      {

   //         iMainMonitor = 0;

   //      }

   //      if (m_rectaMonitor.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      *prect = m_rectaMonitor[iMainMonitor];

   //      return iMainMonitor;

   //   }

   //}


   bool session::set_main_monitor(index iMonitor)
   {

      if (iMonitor == -1)
      {

         m_iMainMonitor = -1;

         return true;

      }
      else if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }
      else
      {

         m_iMainMonitor = iMonitor;

         return true;

      }

   }


   //::count session::get_wkspace_count()
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_wkspace_count();

   //   }
   //   else
   //   {

   //      return m_rectaWkspace.get_count();

   //   }

   //}


   //::count session::get_monitor_count()
   //{

   //   //if (get_document() != nullptr && get_view() != nullptr)
   //   //{

   //   //   return 1;

   //   //}


   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_monitor_count();

   //   }
   //   else
   //   {

   //      return m_rectaMonitor.get_count();

   //   }

   //}


   //bool session::get_monitor_rect(index iMonitor, RECT * prect)
   //{

   //   //if (get_document() != nullptr && get_view() != nullptr)
   //   //{

   //   //   get_view()->get_window_rect(prect);


   //   //   return true;

   //   //}


   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_monitor_rect(iMonitor, prect);


   //   }
   //   else
   //   {

   //      if (iMonitor < 0 || iMonitor >= m_rectaMonitor.get_count())
   //      {

   //         return false;

   //      }

   //      *prect = m_rectaMonitor[iMonitor];

   //      return true;

   //   }

   //}


   bool session::wkspace_to_monitor(RECT * prect, index iMonitor, index iWkspace)
   {

      ::rect rect(*prect);

      ::rect rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
      {

         return false;

      }

      rect -= rectWkspace.top_left();

      ::rect rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
      {

         return false;

      }

      rect += rectMonitor.top_left();

      *prect = rect;


      return true;

   }


   bool session::wkspace_to_monitor(RECT * prect)
   {

      index iWkspace = get_best_wkspace(nullptr, rect(prect));

      return wkspace_to_monitor(prect, iWkspace, iWkspace);

   }


   bool session::monitor_to_wkspace(RECT * prect)
   {

      index iMonitor = get_best_monitor(nullptr, rect(prect));

      return monitor_to_wkspace(prect, iMonitor, iMonitor);

   }


   bool session::monitor_to_wkspace(RECT * prect, index iWkspace, index iMonitor)
   {

      ::rect rect(prect);

      ::rect rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
      {

         return false;

      }

      rect -= rectMonitor.top_left();

      ::rect rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
      {

         return false;

      }

      rect += rectWkspace.top_left();

      *prect = rect;

      return true;

   }


   //bool session::get_wkspace_rect(index iWkspace, RECT * prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_wkspace_rect(iWkspace, prect);

   //   }
   //   else
   //   {

   //      if (iWkspace < 0 || iWkspace >= m_rectaWkspace.get_count())
   //      {

   //         return false;

   //      }

   //      *prect = m_rectaWkspace[iWkspace];

   //      return true;

   //   }

   //}


   //::count session::get_desk_monitor_count()
   //{

   //   return get_monitor_count();

   //}


   //bool session::get_desk_monitor_rect(index iMonitor, RECT * prect)
   //{

   //   return get_monitor_rect(iMonitor, prect);

   //}


   //void session::get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const rect & rectParam)
   //{

   //   for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
   //   {

   //      ::rect rectIntersect;

   //      ::rect rectMonitor;

   //      if (get_monitor_rect(iMonitor, rectMonitor))
   //      {

   //         if (rectIntersect.top_left_null_intersect(&rectParam, rectMonitor))
   //         {

   //            if (rectIntersect.area() >= 0)
   //            {

   //               rectaMonitor.add(rectMonitor);

   //               rectaIntersect.add(rectIntersect);

   //            }

   //         }

   //      }

   //   }

   //}


   //index session::get_main_wkspace(RECT* prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      if (m_iMainWkspace >= 0 && m_iMainWkspace < System.get_monitor_count())
   //      {

   //         return System.get_main_wkspace(prect);

   //      }
   //      else
   //      {

   //         if (System.get_monitor_rect(m_iMainWkspace, prect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            System.get_wkspace_rect(0, prect);


   //            return 0;

   //         }

   //      }

   //}
   //   else
   //   {

   //      index iMainWkspace = m_iMainWkspace;

   //      if (iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
   //      {

   //         iMainWkspace = 0;

   //      }

   //      if (m_rectaWkspace.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      if (prect != nullptr)
   //      {

   //         *prect = m_rectaWkspace[iMainWkspace];

   //      }

   //      return iMainWkspace;

   //   }

   //}


   //bool session::set_main_wkspace(index iWkspace)
   //{

   //   if (iWkspace == -1)
   //   {

   //      m_iMainWkspace = -1;

   //      return true;

   //   }
   //   else if (iWkspace < 0 || iWkspace >= get_wkspace_count())
   //   {

   //      return false;

   //   }
   //   else
   //   {

   //      m_iMainWkspace = iWkspace;

   //      return true;

   //   }

   //}


   //index session::get_main_monitor(RECT* prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      if (m_iMainMonitor < 0 || m_iMainMonitor >= System.get_monitor_count())
   //      {

   //         return System.get_main_monitor(prect);

   //      }
   //      else
   //      {

   //         if (System.get_monitor_rect(m_iMainMonitor, prect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            System.get_monitor_rect(0, prect);

   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      index iMainMonitor = m_iMainMonitor;

   //      if (iMainMonitor < 0 || iMainMonitor >= m_rectaMonitor.get_count())
   //      {

   //         iMainMonitor = 0;

   //      }

   //      if (m_rectaMonitor.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      *prect = m_rectaMonitor[iMainMonitor];

   //      return iMainMonitor;

   //   }

   //}


   //bool session::set_main_monitor(index iMonitor)
   //{

   //   if (iMonitor == -1)
   //   {

   //      m_iMainMonitor = -1;

   //      return true;

   //   }
   //   else if (iMonitor < 0 || iMonitor >= get_monitor_count())
   //   {

   //      return false;

   //   }
   //   else
   //   {

   //      m_iMainMonitor = iMonitor;

   //      return true;

   //   }

   //}


   //::count session::get_wkspace_count()
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_wkspace_count();

   //   }
   //   else
   //   {

   //      return m_rectaWkspace.get_count();

   //   }

   //}


   //::count session::get_monitor_count()
   //{

   //   //if (get_document() != nullptr && get_view() != nullptr)
   //   //{

   //   //   return 1;

   //   //}


   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_monitor_count();

   //   }
   //   else
   //   {

   //      return m_rectaMonitor.get_count();

   //   }

   //}


   //bool session::get_monitor_rect(index iMonitor, RECT* prect)
   //{

   //   //if (get_document() != nullptr && get_view() != nullptr)
   //   //{

   //   //   get_view()->get_window_rect(prect);


   //   //   return true;

   //   //}


   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_monitor_rect(iMonitor, prect);


   //   }
   //   else
   //   {

   //      if (iMonitor < 0 || iMonitor >= m_rectaMonitor.get_count())
   //      {

   //         return false;

   //      }

   //      *prect = m_rectaMonitor[iMonitor];

   //      return true;

   //   }

   //}


   //bool session::wkspace_to_monitor(RECT* prect, index iMonitor, index iWkspace)
   //{

   //   ::rect rect(*prect);

   //   ::rect rectWkspace;

   //   if (!get_wkspace_rect(iWkspace, rectWkspace))
   //   {

   //      return false;

   //   }

   //   rect -= rectWkspace.top_left();

   //   ::rect rectMonitor;

   //   if (!get_monitor_rect(iMonitor, rectMonitor))
   //   {

   //      return false;

   //   }

   //   rect += rectMonitor.top_left();

   //   *prect = rect;


   //   return true;

   //}


   //bool session::wkspace_to_monitor(RECT* prect)
   //{

   //   index iWkspace = get_best_wkspace(nullptr, rect(prect));

   //   return wkspace_to_monitor(prect, iWkspace, iWkspace);

   //}


   //bool session::monitor_to_wkspace(RECT* prect)
   //{

   //   index iMonitor = get_best_monitor(nullptr, rect(prect));

   //   return monitor_to_wkspace(prect, iMonitor, iMonitor);

   //}


   //bool session::monitor_to_wkspace(RECT* prect, index iWkspace, index iMonitor)
   //{

   //   ::rect rect(prect);

   //   ::rect rectMonitor;

   //   if (!get_monitor_rect(iMonitor, rectMonitor))
   //   {

   //      return false;

   //   }

   //   rect -= rectMonitor.top_left();

   //   ::rect rectWkspace;

   //   if (!get_wkspace_rect(iWkspace, rectWkspace))
   //   {

   //      return false;

   //   }

   //   rect += rectWkspace.top_left();

   //   *prect = rect;

   //   return true;

   //}


   //bool session::get_wkspace_rect(index iWkspace, RECT* prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_wkspace_rect(iWkspace, prect);

   //   }
   //   else
   //   {

   //      if (iWkspace < 0 || iWkspace >= m_rectaWkspace.get_count())
   //      {

   //         return false;

   //      }

   //      *prect = m_rectaWkspace[iWkspace];

   //      return true;

   //   }

   //}


   //::count session::get_desk_monitor_count()
   //{

   //   return get_monitor_count();

   //}


   //bool session::get_desk_monitor_rect(index iMonitor, RECT* prect)
   //{

   //   return get_monitor_rect(iMonitor, prect);

   //}


   void session::get_monitor(rect_array& rectaMonitor, rect_array& rectaIntersect, const rect& rectParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(&rectParam, rectMonitor))
            {

               if (rectIntersect.area() >= 0)
               {

                  rectaMonitor.add(rectMonitor);

                  rectaIntersect.add(rectIntersect);

               }

            }

         }

      }

   }


   DWORD session::get_monitor_color_temperature(index iMonitor)
   {

#ifdef _UWP

      return 0;

#elif defined(LINUX)

      return 0;

#elif defined(MACOS)

      return 0;

#elif defined(APPLE_IOS)

      return 0;

#elif defined(ANDROID)

      return 0;

#else

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      MC_COLOR_TEMPERATURE e;

      if (!GetMonitorColorTemperature(m_hmonitora[iMonitor], &e))
      {

         return 0;

      }

      return mc_color_kelvin(e);

#endif

   }

   ::mutex g_monitor_adjust;

   bool session::adjust_monitor(index iMonitor, DWORD dwTemperature, double dBrightness, double dGamma)
   {

#ifdef _UWP

      return true;

#elif defined(LINUX)

      return true;

#elif defined(MACOS)

      return true;

#elif defined(APPLE_IOS)

      return true;

#elif defined(ANDROID)

      return true;

#else

      sync_lock sl(&g_monitor_adjust);

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      if (dBrightness <= 0.0)
      {

         dBrightness = 0.1;

      }

      if (dBrightness >= 1.0)
      {

         dBrightness = 1.0;

      }

      if (dGamma <= 0.1)
      {

         dGamma = 0.1;

      }

      if (dGamma >= 10.0)
      {

         dGamma = 10.0;

      }


      DWORD dwMinDriveR;
      DWORD dwCurDriveR;
      DWORD dwMaxDriveR;
      DWORD dwMinDriveG;
      DWORD dwCurDriveG;
      DWORD dwMaxDriveG;
      DWORD dwMinDriveB;
      DWORD dwCurDriveB;
      DWORD dwMaxDriveB;
      DWORD dwMinGainR;
      DWORD dwCurGainR;
      DWORD dwMaxGainR;
      DWORD dwMinGainG;
      DWORD dwCurGainG;
      DWORD dwMaxGainG;
      DWORD dwMinGainB;
      DWORD dwCurGainB;
      DWORD dwMaxGainB;

      float fR;
      float fG;
      float fB;

      //dwTemperature = 4000;

      black_body(&fR, &fG, &fB, dwTemperature);

      MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);

      HMONITOR hMonitor = nullptr;
      DWORD cPhysicalMonitors;
      LPPHYSICAL_MONITOR pPhysicalMonitors = nullptr;

      // Get the number of physical monitors.
      BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
         m_hmonitora[iMonitor],
         &cPhysicalMonitors
      );

      if (!bSuccess || cPhysicalMonitors <= 0)
      {

         return 0;

      }

      PHYSICAL_MONITOR monitor;

      bSuccess = GetPhysicalMonitorsFromHMONITOR(m_hmonitora[iMonitor], 1, &monitor);

      Sleep(500);

      //MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);



      //if (!SetMonitorColorTemperature(monitor.hPhysicalMonitor, e))
      //{

      //   return false;

      //}
      //return true;


      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         DWORD dwLastError = get_last_error();

         TRACELASTERROR();

         goto error;

      }

      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
      {

         return false;

      }


      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMinGainR);
      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMinGainG);
      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMinGainB);
            //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, (DWORD)(dwMinDriveR + (dwMaxDriveR - dwMinDriveR) * r));
            //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, (DWORD)(dwMinDriveG + (dwMaxDriveG - dwMinDriveG) * g));
            //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, (DWORD)(dwMinDriveB + (dwMaxDriveB - dwMinDriveB) * b));
            //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMaxGainR);
            //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMaxGainG);
            //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMaxGainB);
      bool bDifferent = false;
      if (dwMaxDriveR != dwCurDriveR)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
         bDifferent = true;
      }
      if (dwMaxDriveG != dwCurDriveG)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
         bDifferent = true;
      }
      if (dwMaxDriveB != dwCurDriveB)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
         bDifferent = true;
      }


      /* Helper macro used in the fill functions */
//#define F(Y, C)  pow(dBrightness * C, 1.0 / dGamma)
#define F(C)  pow(dBrightness * C, 1.0 / dGamma)

      DWORD dwR = (DWORD)(dwMinGainR + (dwMaxGainR - dwMinGainR) * F(fR));
      DWORD dwG = (DWORD)(dwMinGainG + (dwMaxGainG - dwMinGainG) * F(fG));
      DWORD dwB = (DWORD)(dwMinGainB + (dwMaxGainB - dwMinGainB) * F(fB));

      if (dwR != dwCurGainR)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
         bDifferent = true;
      }
      if (dwG != dwCurGainG)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
         bDifferent = true;
      }
      if (dwB != dwCurGainB)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
         bDifferent = true;
      }

#undef F

      if (!bDifferent)
      {

         goto finalize;

      }

      int iRepeat = 0;
   repeat:

      bDifferent = false;

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
      {

         if (dwCurDriveR != dwMaxDriveR)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
      {

         if (dwCurDriveG != dwMaxDriveG)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
      {

         if (dwCurDriveB != dwMaxDriveB)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         if (dwCurGainR != dwR)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
            Sleep(500);
            bDifferent = true;
         }


      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         if (dwCurGainG != dwG)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         if (dwCurGainB != dwB)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (bDifferent)
      {

         iRepeat++;

         if (iRepeat < 3)
         {

            goto repeat;

         }

      }
      Sleep(500);
   finalize:
      ;
      DestroyPhysicalMonitors(1, &monitor);
      return true;
   error:
      ;
      Sleep(500);
      // Close the monitor handles.
      DestroyPhysicalMonitors(1, &monitor);
      return false;

#endif

   }


#define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;

   index session::_get_best_zoneing(edisplay * pedisplay, ::rect * prect, const ::rect & rectRequest, bool bPreserveSize)
   {

      ::rect rect(rectRequest);

      ::rect rectWkspace;

      index iBestWkspace = get_best_wkspace(&rectWkspace, rect);

      edisplay edisplay;

      ::edisplay edisplayPrevious = *pedisplay;

      double dMargin = System.m_dpi;

      if (ZONEING_COMPARE::is_equal(rect.top, rectWkspace.top, dMargin, !(edisplayPrevious & display_top)))
      {

         edisplay |= display_top;

         if (bPreserveSize)
         {

            rect.move_top_to(rectWkspace.top);

         }
         else
         {

            rect.top = rectWkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rect.bottom, rectWkspace.bottom, dMargin, !(edisplayPrevious & display_bottom)))
      {

         edisplay |= display_bottom;

         if (bPreserveSize)
         {

            rect.move_bottom_to(rectWkspace.bottom);

         }
         else
         {

            rect.bottom = rectWkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectRequest.left, rectWkspace.left, dMargin, !(edisplayPrevious & display_left)))
      {

         edisplay |= display_left;

         if (bPreserveSize)
         {

            rect.move_left_to(rectWkspace.left);

         }
         else
         {

            rect.left = rectWkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectRequest.right, rectWkspace.right, dMargin, !(edisplayPrevious & display_right)))
      {

         edisplay |= display_right;

         if (bPreserveSize)
         {

            rect.move_right_to(rectWkspace.right);

         }
         else
         {

            rect.right = rectWkspace.right;

         }

      }

      if (!(edisplay & display_top || edisplay & display_bottom)
         && is_different(edisplay & display_left, edisplay & display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.top, rect.top, rect.bottom, rectWkspace.bottom))
         {

            edisplay |= display_bottom;

            edisplay |= display_top;

            rect.bottom = rectWkspace.bottom;

            rect.top = rectWkspace.top;

         }

      }

      if (!(edisplay & display_left || edisplay & display_right)
         && is_different(edisplay & display_top, edisplay & display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.left, rect.left, rect.right, rectWkspace.right))
         {

            edisplay |= display_left;

            edisplay |= display_right;

            rect.left = rectWkspace.left;

            rect.right = rectWkspace.right;

         }

      }

      bool bLeftXorRight = is_different(edisplay & display_left, edisplay & display_right);

      bool bTopXorBottom = is_different(edisplay & display_top, edisplay & display_bottom);

      bool bTopAndBottom = edisplay & display_top && edisplay & display_bottom;

      bool bLeftAndRight = edisplay & display_left && edisplay & display_right;

      if (bLeftXorRight && bTopXorBottom)
      {

      }
      else if (bTopAndBottom && bLeftAndRight)
      {

         edisplay = display_zoomed;

      }
      else
      {

         if (bLeftXorRight && !bTopAndBottom)
         {

            edisplay = display_none;

         }

         if (bTopXorBottom && !bLeftAndRight)
         {

            edisplay = display_none;

         }

         if (bTopAndBottom)
         {

            edisplay -= display_top;

            edisplay -= display_bottom;

         }

         if (bLeftAndRight)
         {

            edisplay -= display_left;

            edisplay -= display_right;

         }

      }

      if (edisplay == display_none)
      {

         edisplay = display_normal;

      }

      if (is_docking_appearance(edisplay))
      {

         *prect = rect;

      }
      else if (edisplay == display_zoomed)
      {

         *prect = rectWkspace;

      }
      else
      {

         *prect = rectRequest;

      }

      if (pedisplay)
      {

         *pedisplay = edisplay;

      }

      //if (g_i_get_best_zoneing % 10 == 0)
      //{

      //   string strE("e");
      //   if (edisplay & display_left)
      //      strE += "L";
      //   if (edisplay & display_top)
      //      strE += "T";
      //   if (edisplay & display_right)
      //      strE += "R";
      //   if (edisplay & display_bottom)
      //      strE += "B";

      //   string strP("p");
      //   if (edisplayPrevious & display_left)
      //      strP += "L";
      //   if (edisplayPrevious & display_top)
      //      strP += "T";
      //   if (edisplayPrevious & display_right)
      //      strP += "R";
      //   if (edisplayPrevious & display_bottom)
      //      strP += "B";

      //   ::output_debug_string(
      //      "w" + ::str::from(rectWkspace.left) + ","
      //      + ::str::from(rectWkspace.top) + ","
      //      + ::str::from(rectWkspace.right) + ","
      //      + ::str::from(rectWkspace.bottom) + " " +
      //      "r" + ::str::from(prect->left) + ","
      //      + ::str::from(prect->top) + ","
      //      + ::str::from(prect->right) + ","
      //      + ::str::from(prect->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectWkspace.left,
      //   rectWkspace.top,
      //   rectWkspace.right,
      //   rectWkspace.bottom,
      //   (edisplay & display_left)?'L':' ',
      //   (edisplay & display_top) ? 'T':' ',
      //   (edisplay & display_right) ? 'R':' ',
      //   (edisplay & display_bottom) ? 'B':' ',
      //   (edisplayPrevious & display_left) ? 'L':' ',
      //   (edisplayPrevious & display_top) ? 'T':' ',
      //   (edisplayPrevious & display_right) ? 'R':' ',
      //   (edisplayPrevious & display_bottom) ? 'B':' ');

      return iBestWkspace;

   }


   index session::get_best_monitor(RECT * prect, const rect & rectParam, ::eactivation eactivation)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rect rectMatch;

      ::rect rect(rectParam);

      if (eactivation & activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = get_cursor_pos();

         rect.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rect, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rect))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prect != nullptr)
         {

            *prect = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(prect);

      return iMatchingMonitor;

   }


   index session::get_best_wkspace(::rect * prect, const rect & rectParam, ::eactivation eactivation)
   {

      index iMatchingWkspace = -1;

      i64 iBestArea = -1;

      ::rect rectMatch;

      ::rect rect(rectParam);

      if (eactivation & activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = get_cursor_pos();

         rect.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_wkspace_rect(iWkspace, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rect, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rect))
            {

               iMatchingWkspace = iWkspace;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingWkspace >= 0)
      {

         if(prect != nullptr)
         {

            *prect = rectMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_wkspace(prect);

      return iMatchingWkspace;

   }


   index session::get_good_iconify(RECT * prect, const rect & rectParam)
   {

      ::rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      prect->left = rectMonitor.left;

      prect->top = rectMonitor.top;

      prect->right = rectMonitor.left;

      prect->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }


   index session::initial_frame_position(RECT * prect, const rect & rectParam, bool bMove, ::user::interaction * pinteraction)
   {

      ::rect rectRestore(rectParam);

      ::rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      ::size sizeMin;

      if (pinteraction != nullptr)
      {

         sizeMin  = pinteraction->get_window_minimum_size();

      }
      else
      {

         sizeMin = get_window_minimum_size();

      }

      ::rect rectIntersect;

      if (bMove)
      {

         rect_array rectaMonitor;

         rect_array rectaIntersect;

         get_monitor(rectaMonitor, rectaIntersect, rectParam);

         rectaIntersect.get_box(rectIntersect);

      }
      else
      {

         rectIntersect.intersect(rectMonitor, &rectParam);

      }

      auto sizeMax = rectMonitor.size() * 0.9;

      if (rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy
         || rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy )
      {

         if (rectMonitor.width() / 7 + max(sizeMin.cx, rectMonitor.width() * 2 / 5) > rectMonitor.width()
               || rectMonitor.height() / 7 + max(sizeMin.cy, rectMonitor.height() * 2 / 5) > rectMonitor.width())
         {

            rectRestore = rectMonitor;

         }
         else
         {

            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

            rectRestore.right = rectRestore.left + max(sizeMin.cx, rectMonitor.width() * 2 / 5);

            rectRestore.bottom = rectRestore.top + max(sizeMin.cy, rectMonitor.height() * 2 / 5);

            if (rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
            {

               rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right, 0);

            }

            if (rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
            {

               rectRestore.offset(0, rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

            }

         }

         *prect = rectRestore;

         return iMatchingMonitor;

      }
      else
      {

         if (!bMove)
         {

            *prect = rectIntersect;

         }

         return -1;

      }

   }


   index session::get_window_restore_1(RECT * prect, const rect & rectParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   {

      ::rect rectRestore(rectParam);

      ::rect rectWkspace;

      ::size sizeMin;

      index iMatchingWkspace;

      ::size sizeBroad;

      ::size sizeCompact;

      if (pinteraction != nullptr)
      {

         sizeMin = pinteraction->get_window_minimum_size();

         iMatchingWkspace = pinteraction->calculate_broad_and_compact_restore(rectWkspace, sizeMin, rectParam);

         sizeBroad = pinteraction->m_sizeRestoreBroad;

         sizeCompact = pinteraction->m_sizeRestoreCompact;

      }
      else
      {

         sizeMin = get_window_minimum_size();

         iMatchingWkspace = get_best_wkspace(&rectWkspace, rectParam);

         sizeBroad = sizeMin.max(rectWkspace.size() * 4 / 5);

         sizeCompact = sizeMin.max(rectWkspace.size() * 2 / 5);

      }

      auto rectIntersect = rectWkspace & rectParam;

      auto rectTolerance(rectWkspace);

      auto sizeMax = rectWkspace.size();

      bool b1 = !rectTolerance.contains(rectRestore);
      bool b2 = rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy;
      bool b3 = rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy;
      bool b4 = (edisplayRestore == display_compact && rectRestore.size() != sizeCompact);
      bool b5 = (edisplayRestore == display_broad && rectRestore.size() != sizeBroad);
      bool b6 = (rectRestore.size() == sizeCompact || rectRestore.size() == sizeBroad);
      bool b66 = !(edisplayRestore == display_compact || edisplayRestore == display_broad);

      bool bNotHappyWithTheSizeAndOrPosition = b1 || b2 || b3 || b4 || b5 || (b6 && b66);

      if (bNotHappyWithTheSizeAndOrPosition)
      {

         if (edisplayRestore == display_broad || sizeCompact == rectRestore.size())
         {

            rectRestore.set_size(sizeBroad);

         }
         else
         {

            rectRestore.set_size(sizeCompact);

         }

         ::rect rectWkspaceBitSmaller(rectWkspace);

         rectWkspaceBitSmaller.deflate(5);

         if (!rectWkspaceBitSmaller.contains(rectRestore))
         {

            rectRestore.move_to(rectWkspace.origin() + rectWkspace.size() / 10);

         }

         *prect = rectRestore;

         return iMatchingWkspace;

      }
      else
      {

         return -1;

      }

   }


   index session::get_window_restore_2(RECT* prect, const rect& rectParam, ::user::interaction* pinteraction, edisplay edisplayRestore)
   {

      ::rect rect(rectParam);

      index iBestWkspace = get_window_restore_1(prect, rect, pinteraction, edisplayRestore);

      bool bChangedSize = ::size(prect) != rectParam.size();

      if (iBestWkspace < 0 && !bChangedSize)
      {

         return -1;

      }

      ::rect rectWkspace;

      ::rect rectStart(prect);

      ::point pointLineStart(::top_left(prect));

      get_wkspace_rect(iBestWkspace, rectWkspace);

      if (rectStart > pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectWkspace.origin();

         pointLineStart.offset(49, 49);

         rect.move_to(pointLineStart);

      }

      if(::is_window(pinteraction->get_handle()))
      {

         do
         {

            if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
            {

               return iBestWkspace;

            }

            rect = *prect;

            if (rect > pinteraction->m_sizeRestoreCompact)
            {

               rect.offset(49, 0);

               if (!rectWkspace.contains(rect))
               {

                  pointLineStart.offset(0, 49);

                  rect.move_to(pointLineStart);

                  if (!rectWkspace.contains(rect))
                  {

                     break;

                  }

               }

            }
            else
            {

               rect.offset(49, 49);

            }

            *prect = rect;

         }
         while (rectWkspace.contains(rect));

      }

      if (rect.size() >= pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectWkspace.origin();

         pointLineStart.offset(49, 49);

         rect.move_to(pointLineStart);

         *prect = rect;

         return iBestWkspace;

      }

      rect = rectStart;

      rect.set_size(pinteraction->m_sizeRestoreCompact);

      if(::is_window(pinteraction->get_handle()))
      {

         do
         {

            if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
            {

               return iBestWkspace;

            }

            rect = *prect;

            rect.offset(49, 49);

            *prect = rect;

         } while (rectWkspace.contains(rect));

      }

      pointLineStart = rectWkspace.origin();

      pointLineStart.offset(49, 49);

      rect.move_to(pointLineStart);

      if(::is_window(pinteraction->get_handle()))
      {

         do
         {

            if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
            {

               return iBestWkspace;

            }

            rect = *prect;

            rect.offset(49, 0);

            if (!rectWkspace.contains(rect))
            {

               pointLineStart.offset(0, 49);

               rect.move_to(pointLineStart);

               if (!rectWkspace.contains(rect))
               {

                  break;

               }

            }

            *prect = rect;

         } while (rectWkspace.contains(rect));

      }

      pointLineStart = rectWkspace.origin();

      pointLineStart.offset(49, 49);

      rect.move_to(pointLineStart);

      *prect = rect;

      return iBestWkspace;

   }


   index session::get_good_move(RECT * prect, const rect & rectParam, ::user::interaction * pinteraction)
   {

      index iMatchingMonitor = initial_frame_position(prect, rectParam, true, pinteraction);

      if (__memcmp(prect, &rectParam, sizeof(const rect &)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }

   }


   index session::get_ui_wkspace(::user::interaction * pinteraction)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return get_ui_wkspace(pinteraction);

      }
      else
      {

         ::rect rect;

         pinteraction->layout().sketch().screen_rect(rect);

         return get_best_wkspace(nullptr, rect);

      }

   }


   bool session::is_key_pressed(::user::e_key ekey)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      bool bPressed = false;
      if (ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->lookup(::user::key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_command)
      {
         m_pmapKeyPressed->lookup(::user::key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lcommand, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rcommand, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_control)
      {
         m_pmapKeyPressed->lookup(::user::key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->lookup(::user::key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_ralt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->lookup(ekey, bPressed);

      }

ret:

      return bPressed;

   }


   void session::set_key_pressed(::user::e_key ekey, bool bPressed)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }


   //::user::theme_pointer session::get_user_theme(const char * pszExperienceLibrary, ::aura::application * papp)
   //{

   //   auto &  ptheme = m_mapTheme[pszExperienceLibrary];

   //   if (!ptheme)
   //   {

   //      auto pthemeNew = instantiate_user_theme(pszExperienceLibrary, papp);

   //      __compose(ptheme, pthemeNew);

   //   }

   //   return ptheme;

   //}


//   ::user::theme_pointer session::instantiate_user_theme(const char * pszExperienceLibrary, ::aura::application * papp)
//   {
//
//      INFO("aura::session::instantiate_user_theme");
//
//      if (papp == nullptr)
//      {
//
//         papp = get_context_application();
//
//      }
//
//      string_array straLibrary;
//
//      {
//
//         string strId(pszExperienceLibrary);
//
//         if (strId.has_char())
//         {
//
//            straLibrary.add(strId);
//
//         }
//
//      }
//
//      {
//
//         string strId(App(papp).preferred_experience());
//
//         if (strId.has_char())
//         {
//
//            straLibrary.add(strId);
//
//         }
//
//      }
//
//      {
//
//         string strConfig;
//
//         if (has_property("experience"))
//         {
//
//            strConfig = value("experience");
//
//         }
//
//         if (strConfig.has_char())
//         {
//
//            string strLibrary = string("experience_") + strConfig;
//
//            straLibrary.add(strConfig);
//
//         }
//
//      }
//
//      {
//
//         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / App(papp).m_strAppName / "experience.txt");
//
//         if (strWndFrm.has_char())
//         {
//
//            straLibrary.add(strWndFrm);
//
//         }
//
//      }
//
//      {
//
//         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / ::file::path(App(papp).m_strAppName).folder() / "experience.txt");
//
//         if (strWndFrm.has_char())
//         {
//
//            straLibrary.add(strWndFrm);
//
//         }
//
//      }
//
//      {
//
//         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / ::file::path(App(papp).m_strAppName).name() / "experience.txt");
//
//         if (strWndFrm.has_char())
//         {
//
//            straLibrary.add(strWndFrm);
//
//         }
//
//      }
//
//      {
//
//         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / "system/experience.txt");
//
//         if (strWndFrm.has_char())
//         {
//
//            straLibrary.add(strWndFrm);
//
//         }
//
//      }
//
//      straLibrary.add("experience_core");
//
//      straLibrary.add("experience_metro");
//
//      straLibrary.add("experience_rootkiller");
//
//      straLibrary.add("experience_hyper");
//
//      ::user::theme_pointer ptheme;
//
//      for (string strLibrary : straLibrary)
//      {
//
//         strLibrary.replace("-", "_");
//
//         strLibrary.replace("/", "_");
//
//         if (!::str::begins_ci(strLibrary, "experience_"))
//         {
//
//            strLibrary = "experience_" + strLibrary;
//
//         }
//
//         auto plibrary = System.get_library(strLibrary, true);
//
//         if (::is_null(plibrary))
//         {
//
//            ERR("Failed to Load %s", strLibrary.c_str());
//
//            continue;
//
//         }
//
//         ptheme = plibrary->create_object(papp, "user_theme");
//
//         if (ptheme.is_null())
//         {
//
//            INFO("could not create user_style from ", strLibrary.c_str());
//
//            continue;
//
//         }
//
//         sync_lock sl(&::get_context_system()->m_mutexLibrary);
//
//         ::get_context_system()->m_mapLibrary[strLibrary] = plibrary;
//
//         ptheme->m_plibrary = plibrary;
//
//         m_puserstyle = ptheme;
//
//         break;
//
//      }
//
//      if (ptheme.is_null())
//      {
//
////         message_box(nullptr, "Failed to find/open 'experience' library.\n\nSome reasons:\n   - No 'experience' library present;\n   - Failure to open any suitable 'experience' library.",nullptr, MB_OK);
//
//         __throw(exit_exception(get_context_system()));
//
//      }
//
//      if (ptheme.is_set())
//      {
//
//         ptheme->initialize_theme();
//
//
//      }
//
//      return ptheme;
//
//   }


   //void session::defer_instantiate_user_theme(const char * pszUiInteractionLibrary)
   //{

   //   if (m_ptheme.is_null())
   //   {

   //      __compose(m_ptheme, get_user_theme(pszUiInteractionLibrary));

   //      if (m_ptheme.is_null())
   //      {

   //         ERR("aura::session::defer_instantiate_user_theme");

   //         __throw(resource_exception());

   //      }

   //   }

   //}


   void session::set_bound_ui(::id idView, ::user::interaction * pinteraction)
   {

      m_mapboundui.set_at(idView, pinteraction);

   }


   ::user::primitive * session::get_bound_ui(::id idView)
   {

      auto p = m_mapboundui.plookup(idView);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2;

   }


   void session::on_show_user_input_popup(::user::interaction * pinteraction)
   {

      sync_lock sl(mutex());

      try
      {

         if (m_puiLastUserInputPopup != nullptr
               && m_puiLastUserInputPopup != pinteraction)
         {

            m_puiLastUserInputPopup->display(display_none);

         }

      }
      catch (...)
      {

      }

      m_puiLastUserInputPopup = pinteraction;

   }


//   void session::on_user_logon(::account::user * puser)
//   {
//
//      // Remember:
//      // (Implement items below here or at derived class 'on_user_logon'
//      //  virtual member overload)
//      //
//      // - userpresence
//      // - intelligent file system (ifs)
//      //
//
//
//      //if(puser->m_strPathPrefix.is_empty())
//      //{
//
//      //   puser->m_strPathPrefix = Context.dir().default_os_user_path_prefix();
//
//      //}
//
//      //auto puser = get_user22();
//
////      if(::is_null(puser))
////      {
////
////         return;
////
////      }
//
//      puser->m_pathFolder = Context.dir().appdata() / "profile" / puser->m_strLogin;
//
//      Context.dir().mk(puser->m_pathFolder);
//
//      for (auto & papp : m_applicationa)
//      {
//
//         if (papp.is_set())
//         {
//
//            papp->call_update(id_change_user);
//
//         }
//
//      }
//
//   }
//
//
//   void session::on_remove_user(::account::user * puser)
//   {
//
//   }


   ::user::interaction * session::get_session_window()
   {

#ifdef WINDOWS_DESKTOP

      return m_puiSession;

#else

      return nullptr;

#endif

   }


   ::estatus session::init1()
   {

      auto estatus = __compose_new(m_pfs);

      if (!estatus)
      {

         m_result.add(estatus);

         return false;

      }

      if (System.m_bUser)
      {

         bool bCreateSessionWindow = defer_create_session_frame_window();

         if (!bCreateSessionWindow)
         {

            WARN("Could not create session window");

         }

      }

      //estatus = __compose_new(m_puserpresence);

      //if (!estatus)
      //{

      //   m_result.add(estatus);

      //   TRACE("Failed to create new User Presence");

      //   return false;

      //}

      if (!m_pifs)
      {

         estatus = __compose(m_pifs, __new(ifs("")));

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create ifs");

         }

      }

      if (!m_premotefs)
      {

         estatus = __compose(m_premotefs, __new(::fs::remote_native("")));

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create remotefs");

         }

      }

      //if (!m_pftpfs)
      //{

      //   auto pftpfs = __new(ftpfs);

      //   auto estatus = pftpfs->initialize_ftpfs(this, "");

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create ftpfs");

      //   }

      //   __compose(m_pftpfs, pftpfs);

      //}

      if (!m_pfsdata)
      {

         auto pset = __create_new<::fs::set>();

         auto plink = __create_new < ::fs::link>();

         plink->fill_os_user();

         pset->m_spafsdata.add(plink);

         pset->m_spafsdata.add(__create_new < ::fs::native>());

         estatus = __compose(m_pfsdata, pset);

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create fsdata");

         }


      }

      INFO(".2");

      if (System.m_bUser)
      {

         //if (!::axis::application::process_init())
         //{

         //   ERR(".2");

         //   return false;

         //}

         //fill_locale_schema(*str_context()->m_plocaleschema);

         INFO("success");

         auto psetup = static_setup::get_first(::static_setup::flag_object_user);

         if (psetup)
         {

            estatus = __compose(m_puser, psetup->create_new_object());

         }

         if (!estatus)
         {

            estatus = __compose_new(m_puser);

         }

         if (!estatus || !m_puser)
         {

            ERR(".4");

            return false;

         }

         INFO("end");



         if (!m_puser->init1())
            return false;

         if (!m_puser->init2())
            return false;

      //   if (System.m_bUserEx)
      //   {

      //      estatus = __compose(m_puserex);

      //      if (!estatus)
      //      {

      //         return false;

      //      }

      //      if (!m_puserex->init())
      //      {

      //         WARN("userex::init Failed");

      //         return false;

      //      }

      //      if (!m_puserex->init1())
      //      {

      //         WARN("userex::init1 Failed");

      //         return false;

      //      }

      //      if (!m_puserex->init2())
      //      {

      //         WARN("userex::init2 Failed");

      //         return false;

      //      }

      //   }

      }

      if (System.m_bDraw2d)
      {

         System.draw2d().enum_draw2d_fonts(m_fontenumitema);

      }

      enum_display_monitors();

      return true;

   }


   ::estatus session::defer_initialize_host_window(LPCRECT lpcrect)
   {

#if !defined(APPLE_IOS) && !defined(_UWP) && !defined(ANDROID)

      return ::success;

#else

      if(m_puiHost)
      {

         return ::success;

      }

      auto puserinteraction = ::PLATFORM_NAMESPACE::create_host_window();

      if(!puserinteraction)
      {

         return ::error_failed;

      }

      auto estatus = puserinteraction->initialize(get_context_system());

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_puiHost, puserinteraction);

      if (!estatus)
      {

         return estatus;

      }

      rect rectScreen(lpcrect);

//      if(::is_null(lprect))
//      {
//
//         get_main_monitor(rectScreen);
//
//      }
//      else
//      {
//
//         rectScreen = *lprect;
//
//      }

      ::user::create_struct cs(0, nullptr, nullptr, WS_VISIBLE, rectScreen);

      auto puiHost = __user_interaction(m_puiHost);

      if (!puiHost->create_window_ex(cs))
      {

         return ::error_failed;

      }

//      puserinteraction->place(rectScreen);
//
//      puserinteraction->display(display_normal);
//
//      puserinteraction->set_need_layout();
//
//      puserinteraction->set_need_redraw();
//
//      puserinteraction->post_redraw();

      return true;

#endif

   }


   ::estatus session::init2()
   {

      ::estatus estatus;

      INFO("aura::session::init2 .1");

      if (System.m_bUser)
      {

         //if (!m_paccount)
         //{

         //   estatus = __compose_new(m_paccount);

         //   if (!estatus)
         //   {

         //      FATAL("aura::session::init2 Failed to create account department");

         //      return false;

         //   }

         //}

         //if (!m_paccount->init_instance())
         //{

         //   return false;

         //}

         if(System.m_bDraw2d)
         {

            m_pfontCopyDesk = ::draw2d::point_font(FONT_SANS, 14.0);

         }

      }

      //initialize_bergedge_application_interface();

      //SetRegistryKey("ca2core");

      if (!InitializeLocalDataCentral())
      {

         message_box("Could not initialize Local data central");

         return false;

      }

      //initialize_bergedge_application_interface();

      if (is_remote_session())
      {

         //Session.savings().save(::e_resource_display_bandwidth);
         //Session.savings().save(::e_resource_blur_background);
         //Session.savings().save(::e_resource_blurred_text_embossing);
         //Session.savings().save(::e_resource_translucent_background);

      }

      //if (userex())
      //{

      //   auto estatus = initialize_filemanager_component(this);

      //   if(!estatus && estatus != error_not_implemented)
      //   {

      //      return false;

      //   }

      //}

      return true;

   }


   ::estatus session::init()
   {

      ::estatus estatus = ::success;

      __pointer(::fs::set) pfsset = m_pfsdata;

      if (m_bIfs)
      {

         if (m_pfsdata.is_null())
         {

            __compose(m_pfsdata, __new(::fs::set));

         }

         pfsset = m_pfsdata;

         if (pfsset.is_null())
         {

            pfsset->m_spafsdata.add_unique(m_pifs);

            pfsset->m_spafsdata.add_unique(m_premotefs);

         }

         ::file::listing patha;

         m_pfsdata->root_ones(patha);

      }

      if (m_puser)
      {

         estatus = m_puser->init();

         if (!estatus)
         {

            return estatus;

         }

      }

      return estatus;

   }


   void session::term()
   {

      if (m_puser)
      {

         try
         {

            m_puser->term();

         }
         catch (...)
         {

         }

         __release(m_puser);

      }

      //if (m_puserex)
      //{

      //   try
      //   {

      //      if (m_puserex.is_set())
      //      {

      //         m_puserex->term();

      //      }

      //   }
      //   catch (...)
      //   {

      //   }

      //   __release(m_puserex);

      //}

      //filemanager_finalize();

      try
      {

         if (m_pcopydesk.is_set())
         {

            m_pcopydesk->finalize();

            __release(m_pcopydesk);

         }

      }
      catch (...)
      {

      }

      try
      {

         ::acme::del(m_pmapKeyPressed);

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

      //try
      //{

      //   __release(m_paccount);

      //}
      //catch (...)
      //{

      //   m_result.add(error_failed);

      //}

//      __release(m_pkeyboard);

      defer_term_ui();

   }


   DWORD session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}


   bool session::on_create_frame_window()
   {

      return true;

   }


   void session::translate_os_key_message(::user::key * pkey)
   {

      keyboard().translate_os_key_message(pkey);

   }


   void session::pre_translate_message(::message::message * pmessage)
   {

      if (::is_set(m_pappCurrent))
      {

         m_pappCurrent->pre_translate_message(pmessage);

      }

   }


} // namespace aura


#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace aura
{






   //::estatus session::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::aura::session::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   void session::install_message_routing(::channel* pchannel)
   {

      ::thread::install_message_routing(pchannel);

   //   //aura::application::install_message_routing(pchannel);
   //   aura::session::install_message_routing(pchannel);

   }


   //::estatus session::process_init()
   //{

   //   /*if(!::aura::application::process_init())
   //      return false;*/

   //   if (!::aura::session::process_init())
   //      return false;

   //   //auto estatus = process_init_userex();

   //   //if(!estatus)
   //   //{

   //   //   return estatus;

   //   //}
   //   auto estatus = __construct(m_puser);

   //   if (!estatus || !m_puser)
   //   {

   //      ERR(".4");

   //      return false;

   //   }

   //   INFO("end");
   //   return true;

   //}


   //::estatus session::init1()
   //{

   //   //if (!::aura::application::init1())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init1())
   //   {

   //      return false;

   //   }



   //   if (!::aura::session::init1())
   //      return false;

   //   //if (!::aura::application::init1())
   //     // return false;

   //   //if (pstyle.is_null())
   //   //{
   //   //
   //   //   defer_create_user_style(preferred_experience());
   //   //
   //   //}

   //   if (!m_puser->init1())
   //      return false;

   //   if (!m_puser->init2())
   //      return false;



   //   auto estatus = __compose_new(m_puserex);

   //   if (!estatus)
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init())
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init1())
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init2())
   //   {

   //      return false;

   //   }

   //   return true;


   //}


   //::estatus session::init()
   //{

   //   //if (!::aura::application::init())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init())
   //   {

   //      return false;

   //   }



   //   return true;

   //}


   //::estatus session::init2()
   //{

   //   //if (!::aura::application::init2())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init2())
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   //::estatus session::init_session()
   //{

   //   //if (!::aura::application::init_application())
   //   //{

   //   //   return false;

   //   //}

   //   if (!::aura::session::init_session())
   //   {

   //      return false;

   //   }

   //   initialize_bergedge_application_interface();

   //   //SetRegistryKey("ca2core");

   //   if (!InitializeLocalDataCentral())
   //   {

   //      message_box("Could not initialize Local data central");

   //      return false;

   //   }

   //   initialize_bergedge_application_interface();

   //   if (is_remote_session())
   //   {

   //      //Session.savings().save(::e_resource_display_bandwidth);
   //      //Session.savings().save(::e_resource_blur_background);
   //      //Session.savings().save(::e_resource_blurred_text_embossing);
   //      //Session.savings().save(::e_resource_translucent_background);

   //   }

   //   if (!initialize_filemanager_component(this))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void session::term_session()
   //{


   //   try
   //   {

   //      ::aura::session::term_session();

   //   }
   //   catch (...)
   //   {

   //   }
   //   try
   //   {

   //      m_puser->term();

   //   }
   //   catch (...)
   //   {

   //   }


   //   m_puser.release();

   //   try
   //   {

   //      if (m_puserex.is_set())
   //      {

   //         m_puserex->term();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   //__releasem_puserex.release();




   //   filemanager_finalize();

   //}


   //void session::term()
   //{

   //   try
   //   {

   //      ::aura::session::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //   //try
   //   //{

   //   //   ::aura::application::term();

   //   //}
   //   //catch(...)
   //   //{

   //   //   m_result.add(error_failed);

   //   //}

   //}


   //::estatus session::bergedge_start()
   //{

   //   return true;

   //}


   void session::_001OnFileNew()
   {

   }


   //void session::route_command_message(::user::command * pcommand)
   //{

   //   return application::route_command_message(pcommand);

   //}


   //void session::load_string_table()
   //{

   //   application::load_string_table();
   //   application::load_string_table("plane", "");
   //   application::load_string_table();
   //   application::load_string_table("session", "");

   //}


   void session::launch_app(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   ::estatus     session::do_request(::create* pcreate)
   {

      return ::thread::do_request(pcreate);

   }




   void session::request_topic_file(var& varQuery)
   {

      request_file(Session.m_varTopicFile, varQuery);

   }


   void session::request_topic_file()
   {

      request_file(Session.m_varTopicFile);

   }


   __pointer(::aura::application) session::get_current_application()
   {

      return Session.m_pappCurrent;

   }

   bool session::is_remote_session()
   {


      return Context.os().is_remote_session();


   }


   bool session::is_mouse_button_pressed(::user::e_mouse emouse)
   {

      if (emouse == ::user::mouse_left_button)
      {
         return Session.is_key_pressed(::user::key_lbutton);
      }
      else if (emouse == ::user::mouse_right_button)
      {
         return Session.is_key_pressed(::user::key_rbutton);
      }
      else if (emouse == ::user::mouse_middle_button)
      {
         return Session.is_key_pressed(::user::key_mbutton);
      }
      else
      {
         __throw(::exception::exception("not expected e_mouse value"));
      }


   }






   bool session::open_file(::filemanager::data* pdata, ::file::item_array& itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      if (itema.get_size() > 0)
      {

         return true;

      }

      return false;

   }








   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = new nature::database(this);

      //if(m_pdatabase == nullptr)
      //{
      //   TRACE("VmpLightApp::init_instance failed to instatiate LightDB\n");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   TRACE("VmpLightApp::init_instance failed to initialize LightDB\n");
      //   return false;
      //}

      return true;

   }


   void session::check_topic_file_change()
   {

      if (Session.m_varCurrentViewFile != Session.m_varTopicFile && !Session.m_varTopicFile.is_empty())
      {

         Session.m_varCurrentViewFile = Session.m_varTopicFile;

         request_topic_file();

      }

   }


   //::user::place_holder_ptra session::get_place_holder(__pointer(::user::frame_window) pmainframe, ::create * pcreate)
   //{

   //   UNREFERENCED_PARAMETER(pcreate);

   //   ::user::place_holder_ptra holderptra;


   //   ::aura::application & app = App(pmainframe->get_context_application());

   //   string strAppName = app.m_strAppName;

   //   //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
   //   //{

   //   //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName)));

   //   //}
   //   //else
   //   //{

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::view >());

   //   //}

   //   return holderptra;

   //}

   bool session::place(::user::main_frame* pmainframe, ::create* pcreate)
   {

      //get_place_holder(pmainframe, pcreate).hold(pmainframe);

      return true;

   }





   void session::set_app_title(const char* pszAppId, const char* pszTitle)
   {

      __pointer(::apex::application) papp;

      if (m_applicationa.lookup(pszAppId, papp) && papp)
      {

         //__pointer(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         //if(ppaneview != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

         //   if(ppane != nullptr)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneview->on_layout(::draw2d::graphics_pointer & pgraphics);

         //   }

         //}

      }

   }


   __pointer(::apex::session) session::get_context_session()
   {

      return this;

   }


   //   bool session::is_serviceable() const
   //   {
   //
   //
   ////      return ::session::application::is_serviceable();
   //      return false;
   //
   //
   //   }


      //bool session::on_uninstall()
      //{


      //   bool bOk1 = true;
      //   bool bOk2 = true;

      //   try
      //   {

      //      bOk1 = ::aura::session::on_uninstall();

      //   }
      //   catch(...)
      //   {
      //      bOk1 = false;
      //   }




      //   return bOk1 && bOk2;


      //}


      //::estatus session::os_native_bergedge_start()
      //{

      //   if (!::aura::application::os_native_bergedge_start())
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //service_base * session::allocate_new_service()
      //{


      //   return ::aura::application::allocate_new_service();


      //}





   ::draw2d::cursor* session::get_default_cursor()
   {

      return System.draw2d().get_cursor(m_ecursorDefault);

   }


   ::estatus     session::main()
   {

      //return ::aura::session::main();
      return ::thread::main();

   }


   //::aura::session * session::query_bergedge()
   //{

   //   ::aura::session * psession = nullptr;

   //   if(System.m_pbergedgemap == nullptr)
   //      return nullptr;

   //   if(!System.m_pbergedgemap->lookup(0,psession))
   //   {
   //      return nullptr;
   //   }

   //   return psession;

   //}


   //void session::on_user_logon(::account::user* puser)
   //{

   //   ::aura::session::on_user_logon(puser);

   //}


//   void session::interactive_credentials(::account::credentials* pcredentials)
//   {
//
//
//      //if (!USER)
//      //{
//
//      //   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;
//
//      //   return;
//
//      //}
//      pcredentials->m_estatus = error_failed;
//
//      manual_reset_event ev;
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      //if (m_pmainpane != nullptr && m_pmainpane == nullptr)
//      //{
//
//      //   try
//      //   {
//
//      //      m_pmainpane->interactive_credentials(pcredentials);
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
//      if (pcredentials->m_estatus == ::success_credentials ||
//         ::failed(pcredentials->m_estatus, STATUS_RANGE_AUTHENTICATION))
//      {
//
//         return;
//
//      }
//
//#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)
//      //attach_thread_input_to_main_thread(false);
//#endif
//
//      ::aura::session::interactive_credentials(pcredentials);
//
//      if (pcredentials->m_estatus == ::success_credentials)
//      {
//
//         return;
//
//      }
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      auto puser = pcredentials->m_puser;
//
//      //auto pdialog = ::__create_new<::account::dialog>();
//
//      //pdialog->initialize_account_dialog(pcredentials);
//
//      //pdialog->get_credentials();
//
//      //pdialog->DestroyWindow();
//
//
//   }


   //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText)
   //{

   //   string_array& straTitle = pane.m_straTitle;

   //   pgraphics->set(brushText);

   //   if (straTitle.get_count() <= 1)
   //   {

   //      pgraphics->_DrawText(pane.get_title(), rect, DT_LEFT | DT_BOTTOM | DT_NOPREFIX);

   //   }
   //   else
   //   {

   //      ::rect rectText(rect);


   //      ::draw2d::font_pointer font;
   //      font = pgraphics->get_current_font();
   //      size sSep = ptab->get_data()->m_sizeSep;
   //      ::rect rectEmp;
   //      for (index i = 0; i < straTitle.get_size(); i++)
   //      {
   //         string str = straTitle[i];
   //         size s = pane.m_sizeaText[i];
   //         rectText.right = rectText.left + s.cx;
   //         pgraphics->_DrawText(str, rectText, DT_LEFT | DT_BOTTOM | DT_NOPREFIX);
   //         rectText.left += s.cx;
   //         if (i < straTitle.get_upper_bound())
   //         {
   //            rectText.right = rectText.left + sSep.cx;
   //            rectEmp = rectText;
   //            rectEmp.deflate(1, 1);
   //            ::draw2d::e_alpha_mode emode = pgraphics->m_ealphamode;
   //            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
   //            if (ptab->m_itemHover == (::user::e_element)(::user::element_split + i))
   //            {
   //               pgraphics->fill_rect(rectEmp, ARGB(128, 150, 184, 255));
   //               pgraphics->set(ptab->get_data()->m_brushTextHover);
   //            }
   //            else
   //            {
   //               //pgraphics->fill_rect(rectEmp,ARGB(128,208,223,233));
   //               pgraphics->set(ptab->get_data()->m_brushText);
   //            }
   //            pgraphics->set(ptab->m_pfontTab);
   //            pgraphics->set_alpha_mode(emode);
   //            pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectText, DT_CENTER | DT_VCENTER | DT_NOPREFIX);
   //            rectText.left += sSep.cx;
   //            pgraphics->set(font);
   //            pgraphics->set(brushText);
   //         }
   //      }

   //   }

   //}


   string_array session::get_user_wallpaper()
   {

      string_array stra;

      //string_array straSource = Session.userex()->get_wallpaper();

      //for (string str : straSource)
      //{

      //   if (::str::begins_eat_ci(str, "file://"))
      //   {

      //      str = System.url().url_decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }


   //__pointer(::user::menu_interaction) session::create_menu_button(::user::style_pointer & pstyle,::user::menu_item* pitem)
   //{

   //   auto pinteraction = __new(::user::menu_button(pitem));

   //   if (pitem->m_pimage->is_set())
   //   {

   //      pinteraction->set_button_style(::user::button::style_image_and_text);

   //      e_image eimage = (e_image)pitem->m_pmenu->value("image_transform").i32();

   //      ::image_pointer pimage = pitem->m_pimage + eimage;

   //      pinteraction->LoadBitmaps(pimage);

   //   }

   //   return pinteraction;

   //}


   //bool session::initialize_filemanager()
   //{

   //   if (m_pfilemanager == nullptr)
   //   {

   //      m_pfilemanager = __new(::filemanager::department(this));

   //      m_pfilemanager->construct(this);

   //      if (!m_pfilemanager->initialize())
   //      {

   //         return false;

   //      }



   //   }

   //   return true;

   //}


   //__pointer(::user::document) session::create_form(::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   //{

   //   auto puserex = Sess(this).userex();

   //   ::object* pobject = nullptr;

   //   if (::is_set(pcallback))
   //   {

   //      pobject = pcallback;

   //   }
   //   else if (::is_set(pwndParent))
   //   {

   //      pobject = pwndParent;

   //   }

   //   return puserex->create_form(
   //      pobject,
   //      pcallback, pwndParent, var, varArgs);

   //}


   //__pointer(::user::document) session::create_form(::type point, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   //{

   //   return Sess(this).userex()->create_form(this, point, pwndParent, var, varArgs);

   //}


   //__pointer(::user::document) session::create_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   //{

   //   return Sess(this).userex()->create_form(this, pview, pcallback, pwndParent, var, varArgs);

   //}


   //__pointer(::user::document) session::create_child_form(::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   //{

   //   return Sess(this).userex()->create_child_form(
   //      pcallback ? pcallback : pwndParent ? pwndParent : this,
   //      pcallback, pwndParent, var, varArgs);


   //}


   //__pointer(::user::document) session::create_child_form(::type point, __pointer(::user::interaction) pwndParent, var var)
   //{

   //   return Sess(this).userex()->create_child_form(this, point, pwndParent, var);

   //}


   //__pointer(::user::document) session::create_child_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, var var)
   //{

   //   return Sess(this).userex()->create_child_form(this, pview, pcallback, pwndParent, var);

   //}




   //session::session()
   //{

   //}


   //session::~session()
   //{


   //}


   //::estatus session::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::aura::session::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   //m_strAppId = "base_session";
   //   //m_strAppName = "base_session";
   //   //m_strBaseSupportId = "base_session";
   //   //m_strInstallToken = "base_session";

   //   m_iMainMonitor = -1;

   //   m_puiCapture = nullptr;

   //   m_puiMouseMoveCapture = nullptr;

   //   m_ecursorDefault = cursor_arrow;

   //   m_ecursor = cursor_default;

   //   m_puiMouseMoveCapture = nullptr;

   //   m_psavings = __new(class ::aura::savings(this));

   //   m_pcopydesk = nullptr;

   //   return estatus;

   //}


   //::estatus session::process_init()
   //{

   //   //m_himc = ImmCreateContext();

   //   INFO(".1");

   //   if (!::aura::session::process_init())
   //   {

   //      ERR(".2");

   //      return false;

   //   }

   //   //if (!::aura::application::process_init())
   //   //{

   //   //   ERR(".3");

   //   //   return false;

   //   //}

   //   //m_puser = create_user();

   //   //if (m_puser == nullptr)
   //   //{

   //   //   ERR(".4");

   //   //   return false;

   //   //}

   //   //m_puser->add_ref(OBJ_REF_DBG_ARGS);

   //   auto estatus = __construct(m_puser);

   //   if (!estatus || !m_puser)
   //   {

   //      ERR(".4");

   //      return false;

   //   }

   //   INFO("end");

   //   return true;

   //}


   //::estatus session::init1()
   //{


   //   if (!::aura::session::init1())
   //      return false;

   //   //if (!::aura::application::init1())
   //     // return false;

   //   //if (pstyle.is_null())
   //   //{
   //   //
   //   //   defer_create_user_style(preferred_experience());
   //   //
   //   //}

   //   if (!m_puser->init1())
   //      return false;

   //   if (!m_puser->init2())
   //      return false;


   //   return true;

   //}


   //::estatus session::init()
   //{

   //   if (!::aura::session::init())
   //   {

   //      return false;

   //   }

   //   //if (!::aura::application::init())
   //   //{

   //   //   return false;

   //   //}

   //   if (!m_puser->init())
   //   {

   //      return false;

   //   }

   //   ::set_message_box(&::simple_ui_message_box);

   //   return true;

   //}


   //void session::term_session()
   //{

   //   //::aura::application::term_application();

   //   ::aura::session::term_session();

   //   try
   //   {

   //      m_puser->term();

   //   }
   //   catch (...)
   //   {

   //   }


   //   m_puser.release();

   //}




   //bool session::prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item* pitem)
   //{

   //   __pointer(::user::button) pbutton = pitem->m_puserinteraction;

   //   if (pbutton->m_id == "close_menu")
   //   {

   //      pbutton->descriptor().set_control_type(::user::control_type_menu_button_close);

   //      pbutton->set_stock_icon(stock_icon_close);

   //      pbutton->resize_to_fit(pgraphics);

   //      return true;

   //   }
   //   else
   //   {

   //      pbutton->descriptor().set_control_type(::user::control_type_menu_button);

   //      int cx = pbutton->width();

   //      int cy = pbutton->height();

   //      pbutton->m_pmenuitemThis = pitem;

   //      ::rect rectMargin(1, 1, 1, 1);

   //      int iCheckBoxSize = 16;

   //      int iElementPadding = 4;

   //      auto& rectCheckBox = pbutton->m_rectCheckBox;

   //      rectCheckBox.left = rectMargin.left;
   //      rectCheckBox.top = rectMargin.top;
   //      rectCheckBox.bottom = cy - rectMargin.bottom;
   //      rectCheckBox.right = rectCheckBox.left + iCheckBoxSize;

   //      auto& rectText = pbutton->m_rectText;

   //      rectText.left = rectCheckBox.right + iElementPadding;
   //      rectText.top = rectMargin.top;
   //      rectText.bottom = cy - rectMargin.bottom;
   //      rectText.right = cx - rectMargin.right;

   //   }

   //   return true;

   //}

   ::color session::get_color(::user::e_element eelement, ::user::estate estate)
   {

      if (eelement == ::user::element_background)
      {

         COLORREF crBk;

         if (::user::is_app_dark_mode())
         {

            crBk = ARGB(255, 0x40, 0x40, 0x40);

         }
         else
         {

            crBk = ARGB(255, 255, 255, 255);

         }

         return crBk;

      }
      else if (eelement == ::user::element_face)
      {

         COLORREF crBk;

         if (::user::is_app_dark_mode())
         {

            crBk = ARGB(255, 127, 127, 127);

         }
         else
         {

            crBk = ARGB(255, 192, 192, 192);

         }

         return crBk;

      }
      else if (eelement == ::user::element_text)
      {

         COLORREF crText;

         if (::user::is_app_dark_mode())
         {

            crText = ARGB(255, 255, 255, 255);

         }
         else
         {

            crText = ARGB(255, 49, 50, 42);

         }

         return crText;

      }

      return ::color();

   }


   void session::frame_pre_translate_message(::message::message* pmessage)
   {

      if (pmessage->m_id == WM_GETTEXT
         || pmessage->m_id == WM_GETTEXTLENGTH
         )
      {

         pmessage->m_uiMessageFlags |= 3; // message considered pre translated
         pmessage->m_uiMessageFlags |= 16384; //  by early optmization

         return;

      }
      //else if (pmessage->m_id == WM_MOUSEMOVE)
      //{

      //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
      //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   return;

      //}

      //try
      //{

      //   __pointer(::user::interaction) pinteraction;

      //   while (get_frame(pinteraction))
      //   {

      //      try
      //      {

      //         if (pinteraction != nullptr)
      //         {

      //            pinteraction->pre_translate_message(pmessage);

      //            if (pmessage->m_bRet)
      //               return;

      //         }

      //      }
      //      catch (::exception_pointer pe)
      //      {

      //         if (e.is < ::exit_exception>())
      //         {

      //            __rethrow(::move(e));

      //         }

      //      }
      //      catch (...)
      //      {
      //      }

      //   }

      //}
      //catch (::exception_pointer pe)
      //{

      //   if (e.is < ::exit_exception>())
      //   {

      //      __rethrow(::move(e));

      //   }

      //}
      //catch (...)
      //{

      //   pmessage->m_bRet = true;

      //}

   }


   /*void session::interactive_credentials(::account::credentials* pcredentials)
   {

      ::aura::session::interactive_credentials(pcredentials);

      if (pcredentials->m_estatus == ::success_credentials)
      {

         return;

      }

      if (!pcredentials->m_bInteractive)
      {

         pcredentials->m_estatus = error_credentials_non_interactive;

         return;

      }

      auto puser = pcredentials->m_puser;

      auto pdialog = ::__create_new<::account::dialog>();

      pdialog->initialize_account_dialog(pcredentials);

      pdialog->get_credentials();

      pdialog->DestroyWindow();

   }*/


   //__pointer(::user::impact) session::get_view()
   //{

   //   return nullptr;

   //}


   //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText)

   //{

   //   __throw(interface_only_exception());

   //}


   //void session::on_finally_focus_set(::user::primitive* pelementalFocus)
   //{

   //   user()->set_mouse_focus_LButtonDown(pelementalFocus);

   //   aura::session::on_finally_focus_set(pelementalFocus);

   //}


   //bool session::on_ui_mouse_message(::message::mouse* pmouse)
   //{

   //   ::aura::session::on_ui_mouse_message(pmouse);

   //   if (m_puserpresence.is_set())
   //   {

   //      m_puserpresence->on_ui_mouse_message(pmouse);

   //   }

   //   return true;

   //}


   void session::finalize()
   {

      ::apex::context_thread::finalize();

   }


   __namespace_session_factory(session);


} // namespace aura




void os_on_finish_launching()
{

   auto psystem = ::get_context_system();

   auto psession = psystem->get_context_session();

   auto puiHost = __user_interaction(psession->m_puiHost);

   puiHost->display(display_full_screen);

   puiHost->set_need_layout();

   puiHost->set_need_redraw();

   puiHost->post_redraw();

}



