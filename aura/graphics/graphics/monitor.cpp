﻿#include "framework.h"




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
interpolate_color(float a, const float * c1, const float * c2, float * r, float * g, float * b)
{
   *r = (1.0f - a) * c1[0] + a * c2[0];
   *g = (1.0f - a) * c1[1] + a * c2[1];
   *b = (1.0f - a) * c1[2] + a * c2[2];
}



CLASS_DECL_AURA void black_body(float * r, float * g, float * b, ::u32 dwTemp)
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



