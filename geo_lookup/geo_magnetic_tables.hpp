/****************************************************************************
 *
 *   Copyright (c) 2020 Estimation and Control Library (ECL). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name ECL nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.3507,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26017, 24272, 22526, 20781, 19035, 17290, 15545, 13799, 12054, 10309,  8564,  6818,  5073,  3328,  1582,  -163, -1908, -3653, -5399, -7144, -8889,-10635,-12380,-14125,-15871,-17616,-19361,-21107,-22852,-24597,-26343,-28088,-29833, 31253, 29508, 27762, 26017, },
/* LAT: -80 */ {  22587, 20451, 18507, 16731, 15088, 13548, 12084, 10671,  9295,  7945,  6612,  5293,  3984,  2679,  1372,    53, -1286, -2656, -4064, -5513, -7005, -8539,-10114,-11731,-13393,-15109,-16892,-18762,-20742,-22858,-25131,-27564,-30133, 30057, 27434, 24922, 22587, },
/* LAT: -70 */ {  14967, 13571, 12448, 11490, 10626,  9797,  8958,  8073,  7122,  6104,  5034,  3940,  2853,  1795,   772,  -239, -1274, -2376, -3571, -4865, -6240, -7665, -9110,-10549,-11973,-13388,-14814,-16295,-17912,-19815,-22315,-26085, 30829, 24195, 19628, 16840, 14967, },
/* LAT: -60 */ {   8379,  8142,  7869,  7603,  7356,  7109,  6806,  6378,  5767,  4951,  3953,  2841,  1718,   684,  -205,  -968, -1698, -2515, -3509, -4694, -6014, -7377, -8695, -9905,-10971,-11873,-12591,-13087,-13259,-12809,-10722, -3604,  4772,  7569,  8364,  8504,  8379, },
/* LAT: -50 */ {   5453,  5493,  5443,  5360,  5292,  5260,  5230,  5108,  4769,  4113,  3108,  1839,   495,  -695, -1581, -2159, -2563, -2999, -3669, -4661, -5887, -7155, -8295, -9202, -9809,-10059, -9877, -9131, -7633, -5280, -2380,   365,  2474,  3897,  4771,  5246,  5453, },
/* LAT: -40 */ {   3931,  4025,  4038,  3999,  3945,  3915,  3924,  3917,  3748,  3222,  2209,   774,  -793, -2120, -3002, -3471, -3669, -3735, -3892, -4430, -5378, -6443, -7332, -7883, -8006, -7647, -6773, -5396, -3681, -1971,  -506,   717,  1758,  2619,  3272,  3700,  3931, },
/* LAT: -30 */ {   2963,  3051,  3086,  3079,  3026,  2952,  2896,  2865,  2741,  2272,  1251,  -258, -1868, -3136, -3896, -4258, -4354, -4162, -3732, -3480, -3803, -4534, -5240, -5607, -5500, -4930, -3980, -2772, -1552,  -598,    85,   687,  1307,  1904,  2408,  2766,  2963, },
/* LAT: -20 */ {   2321,  2368,  2393,  2402,  2366,  2277,  2175,  2101,  1957,  1470,   429, -1048, -2531, -3610, -4165, -4301, -4115, -3576, -2722, -1905, -1594, -1926, -2573, -3054, -3107, -2760, -2131, -1311,  -524,   -26,   243,   547,   983,  1454,  1869,  2171,  2321, },
/* LAT: -10 */ {   1927,  1923,  1909,  1913,  1892,  1814,  1710,  1623,  1441,   897,  -152, -1522, -2803, -3652, -3944, -3738, -3177, -2403, -1557,  -792,  -309,  -322,  -780, -1290, -1514, -1432, -1122,  -621,  -116,   134,   190,   352,   718,  1146,  1531,  1812,  1927, },
/* LAT:   0 */ {   1715,  1683,  1634,  1633,  1628,  1566,  1469,  1361,  1110,   494,  -538, -1764, -2829, -3436, -3460, -2979, -2218, -1434,  -776,  -235,   185,   310,    44,  -373,  -634,  -694,  -596,  -331,   -36,    61,     7,    99,   434,   867,  1277,  1590,  1715, },
/* LAT:  10 */ {   1582,  1592,  1555,  1578,  1609,  1567,  1454,  1274,   901,   186,  -832, -1911, -2751, -3111, -2928, -2335, -1561,  -845,  -322,    63,   391,   548,   396,    75,  -164,  -272,  -292,  -208,   -99,  -135,  -267,  -238,    58,   503,   976,  1376,  1582, },
/* LAT:  20 */ {   1405,  1555,  1620,  1716,  1807,  1793,  1645,  1350,   808,   -48, -1092, -2051, -2663, -2790, -2477, -1883, -1174,  -520,   -53,   262,   523,   674,   591,   348,   146,    29,   -57,  -116,  -191,  -376,  -609,  -667,  -438,     2,   537,  1051,  1405, },
/* LAT:  30 */ {   1114,  1482,  1744,  1970,  2132,  2146,  1965,  1547,   822,  -208, -1332, -2222, -2652, -2604, -2214, -1639,  -984,  -363,   105,   416,   650,   801,   787,   640,   489,   365,   215,    12,  -265,  -635, -1003, -1164, -1009,  -588,   -15,   593,  1114, },
/* LAT:  40 */ {    768,  1356,  1850,  2242,  2492,  2537,  2324,  1794,   883,  -349, -1599, -2482, -2816, -2674, -2233, -1643,  -989,  -357,   158,   527,   802,  1005,  1105,  1097,  1021,   875,   614,   213,  -317,  -920, -1444, -1692, -1581, -1167,  -569,   106,   768, },
/* LAT:  50 */ {    492,  1241,  1921,  2476,  2840,  2945,  2716,  2061,   915,  -594, -2034, -2964, -3269, -3083, -2595, -1949, -1238,  -538,    83,   593,  1016,  1377,  1663,  1838,  1860,  1679,  1245,   549,  -335, -1237, -1922, -2217, -2097, -1656, -1017,  -278,   492, },
/* LAT:  60 */ {    315,  1172,  1977,  2669,  3168,  3376,  3155,  2335,   802, -1184, -2924, -3916, -4171, -3910, -3336, -2587, -1758,  -913,  -101,   655,  1352,  1987,  2535,  2937,  3105,  2931,  2309,  1211,  -193, -1517, -2398, -2717, -2554, -2056, -1354,  -543,   315, },
/* LAT:  70 */ {    117,  1059,  1959,  2756,  3366,  3651,  3383,  2212,   -92, -2870, -4840, -5657, -5652, -5155, -4375, -3432, -2400, -1327,  -247,   817,  1847,  2818,  3691,  4404,  4861,  4908,  4323,  2882,   714, -1394, -2706, -3158, -2999, -2461, -1700,  -819,   117, },
/* LAT:  80 */ {   -467,   460,  1318,  2013,  2394,  2184,   892, -1930, -5325, -7455, -8148, -7965, -7298, -6353, -5241, -4027, -2749, -1434,  -102,  1231,  2549,  3835,  5064,  6203,  7200,  7961,  8310,  7890,  6048,  2440, -1081, -2821, -3218, -2908, -2240, -1392,  -467, },
/* LAT:  90 */ { -30287,-28541,-26796,-25050,-23305,-21559,-19814,-18069,-16324,-14578,-12833,-11088, -9343, -7597, -5852, -4107, -2362,  -617,  1128,  2874,  4619,  6364,  8109,  9855, 11600, 13345, 15091, 16836, 18581, 20327, 22072, 23818, 25563, 27309, 29054, 30800,-30287, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.3507,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579,-12579, },
/* LAT: -80 */ { -13666,-13532,-13372,-13191,-12997,-12795,-12591,-12390,-12198,-12022,-11865,-11730,-11619,-11533,-11470,-11428,-11409,-11412,-11439,-11493,-11576,-11690,-11835,-12008,-12205,-12422,-12651,-12884,-13112,-13325,-13512,-13663,-13767,-13820,-13817,-13764,-13666, },
/* LAT: -70 */ { -14116,-13797,-13478,-13155,-12822,-12478,-12122,-11764,-11419,-11109,-10854,-10669,-10556,-10503,-10490,-10495,-10504,-10515,-10540,-10596,-10703,-10876,-11121,-11433,-11804,-12220,-12667,-13131,-13597,-14050,-14469,-14816,-15009,-14959,-14729,-14432,-14116, },
/* LAT: -60 */ { -13524,-13172,-12835,-12502,-12159,-11786,-11370,-10915,-10446,-10013, -9679, -9499, -9492, -9627, -9832,-10029,-10160,-10210,-10202,-10189,-10235,-10390,-10674,-11078,-11573,-12126,-12711,-13307,-13896,-14457,-14954,-15245,-15075,-14693,-14288,-13896,-13524, },
/* LAT: -50 */ { -12498,-12158,-11828,-11507,-11183,-10837,-10437, -9965, -9433, -8909, -8513, -8379, -8572, -9028, -9593,-10111,-10480,-10654,-10636,-10491,-10348,-10347,-10559,-10966,-11503,-12093,-12680,-13221,-13669,-13969,-14078,-14006,-13803,-13521,-13193,-12847,-12498, },
/* LAT: -40 */ { -11240,-10894,-10549,-10205, -9866, -9527, -9165, -8738, -8215, -7647, -7213, -7158, -7603, -8420, -9343,-10178,-10846,-11294,-11451,-11299,-10963,-10685,-10665,-10934,-11390,-11894,-12343,-12670,-12833,-12840,-12749,-12610,-12430,-12197,-11911,-11585,-11240, },
/* LAT: -30 */ {  -9601, -9227, -8852, -8463, -8071, -7694, -7335, -6941, -6426, -5813, -5351, -5413, -6161, -7353, -8606, -9709,-10632,-11354,-11772,-11783,-11425,-10919,-10574,-10562,-10807,-11128,-11389,-11508,-11449,-11274,-11097,-10958,-10809,-10600,-10319, -9975, -9601, },
/* LAT: -20 */ {  -7369, -6937, -6527, -6101, -5656, -5225, -4830, -4412, -3842, -3154, -2693, -2927, -4009, -5608, -7240, -8622, -9702,-10493,-10950,-11003,-10655,-10049, -9486, -9232, -9274, -9435, -9580, -9603, -9434, -9161, -8963, -8869, -8758, -8547, -8231, -7821, -7369, },
/* LAT: -10 */ {  -4412, -3888, -3444, -3011, -2554, -2102, -1683, -1221,  -587,   123,   501,   103, -1196, -3098, -5078, -6707, -7825, -8478, -8758, -8710, -8316, -7642, -6977, -6624, -6579, -6671, -6792, -6819, -6634, -6336, -6176, -6174, -6123, -5901, -5518, -4995, -4412, },
/* LAT:   0 */ {   -902,  -293,   162,   559,   976,  1394,  1789,  2243,  2838,  3425,  3643,  3171,  1903,    10, -2038, -3710, -4745, -5194, -5266, -5106, -4678, -3974, -3269, -2891, -2828, -2900, -3027, -3103, -2974, -2737, -2674, -2804, -2852, -2659, -2235, -1611,  -902, },
/* LAT:  10 */ {   2566,  3178,  3603,  3940,  4293,  4661,  5018,  5415,  5877,  6257,  6305,  5835,  4773,  3222,  1530,   137,  -691,  -957,  -877,  -649,  -247,   381,  1014,  1356,  1418,  1369,  1265,  1174,  1218,  1324,  1257,  1004,   827,   905,  1257,  1853,  2566, },
/* LAT:  20 */ {   5419,  5938,  6311,  6603,  6915,  7260,  7606,  7962,  8304,  8512,  8434,  7984,  7161,  6073,  4945,  4026,  3482,  3349,  3489,  3727,  4052,  4511,  4970,  5227,  5281,  5259,  5208,  5151,  5143,  5128,  4961,  4640,  4352,  4267,  4439,  4857,  5419, },
/* LAT:  30 */ {   7569,  7938,  8252,  8533,  8842,  9190,  9551,  9898, 10181, 10301, 10163,  9749,  9126,  8417,  7753,  7236,  6935,  6885,  7020,  7227,  7470,  7766,  8053,  8227,  8282,  8291,  8290,  8281,  8262,  8183,  7967,  7621,  7271,  7054,  7038,  7230,  7569, },
/* LAT:  40 */ {   9266,  9485,  9740, 10026, 10352, 10715, 11086, 11428, 11685, 11772, 11627, 11271, 10799, 10324,  9926,  9638,  9484,  9474,  9580,  9738,  9910, 10092, 10263, 10388, 10464, 10522, 10574, 10607, 10593, 10487, 10250,  9903,  9539,  9256,  9113,  9124,  9266, },
/* LAT:  50 */ {  10801, 10923, 11125, 11396, 11720, 12076, 12433, 12752, 12977, 13039, 12902, 12605, 12239, 11892, 11615, 11425, 11329, 11321, 11384, 11484, 11596, 11710, 11825, 11940, 12057, 12178, 12290, 12363, 12356, 12235, 11993, 11667, 11329, 11044, 10854, 10774, 10801, },
/* LAT:  60 */ {  12318, 12393, 12545, 12765, 13037, 13340, 13644, 13912, 14090, 14118, 13982, 13731, 13441, 13168, 12945, 12787, 12694, 12660, 12674, 12719, 12785, 12869, 12974, 13104, 13262, 13437, 13601, 13712, 13721, 13605, 13382, 13104, 12824, 12587, 12417, 12326, 12318, },
/* LAT:  70 */ {  13759, 13804, 13901, 14046, 14227, 14433, 14643, 14826, 14930, 14908, 14767, 14563, 14344, 14139, 13964, 13828, 13733, 13677, 13657, 13668, 13709, 13780, 13882, 14017, 14182, 14369, 14553, 14695, 14744, 14675, 14515, 14317, 14122, 13957, 13837, 13770, 13759, },
/* LAT:  80 */ {  15002, 15017, 15056, 15117, 15196, 15283, 15364, 15408, 15386, 15302, 15186, 15060, 14936, 14821, 14721, 14638, 14576, 14535, 14516, 14519, 14545, 14593, 14664, 14756, 14867, 14993, 15128, 15259, 15366, 15412, 15377, 15293, 15200, 15117, 15053, 15015, 15002, },
/* LAT:  90 */ {  15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, 15391, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.3507,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, 5458, },
/* LAT: -80 */ {  6065, 6002, 5924, 5832, 5730, 5619, 5501, 5379, 5257, 5137, 5023, 4917, 4823, 4743, 4680, 4634, 4610, 4607, 4628, 4673, 4743, 4836, 4950, 5082, 5225, 5374, 5524, 5667, 5798, 5912, 6005, 6074, 6119, 6139, 6135, 6110, 6065, },
/* LAT: -70 */ {  6309, 6177, 6028, 5865, 5687, 5495, 5290, 5076, 4856, 4641, 4438, 4255, 4096, 3965, 3860, 3783, 3736, 3722, 3750, 3825, 3951, 4130, 4357, 4624, 4918, 5225, 5528, 5812, 6062, 6267, 6419, 6515, 6557, 6551, 6502, 6419, 6309, },
/* LAT: -60 */ {  6194, 6003, 5803, 5596, 5378, 5144, 4888, 4610, 4317, 4027, 3759, 3531, 3350, 3215, 3115, 3042, 2991, 2971, 2996, 3084, 3251, 3500, 3824, 4209, 4630, 5063, 5485, 5869, 6195, 6444, 6609, 6689, 6692, 6630, 6518, 6368, 6194, },
/* LAT: -50 */ {  5850, 5621, 5391, 5161, 4930, 4686, 4416, 4113, 3784, 3452, 3148, 2907, 2744, 2652, 2603, 2569, 2537, 2511, 2516, 2586, 2756, 3042, 3435, 3903, 4409, 4915, 5391, 5811, 6151, 6393, 6533, 6575, 6534, 6425, 6265, 6068, 5850, },
/* LAT: -40 */ {  5397, 5153, 4909, 4671, 4437, 4201, 3947, 3663, 3349, 3023, 2723, 2499, 2380, 2353, 2372, 2395, 2401, 2391, 2380, 2407, 2533, 2802, 3213, 3724, 4270, 4795, 5264, 5654, 5948, 6136, 6226, 6230, 6161, 6032, 5852, 5635, 5397, },
/* LAT: -30 */ {  4881, 4641, 4404, 4171, 3945, 3727, 3508, 3278, 3022, 2747, 2489, 2304, 2232, 2255, 2321, 2394, 2461, 2513, 2538, 2551, 2614, 2806, 3160, 3643, 4174, 4673, 5094, 5414, 5619, 5720, 5747, 5721, 5642, 5511, 5332, 5116, 4881, },
/* LAT: -20 */ {  4322, 4111, 3904, 3700, 3505, 3322, 3154, 2991, 2815, 2617, 2426, 2291, 2246, 2287, 2375, 2485, 2614, 2745, 2837, 2876, 2900, 2990, 3222, 3600, 4048, 4476, 4828, 5067, 5175, 5183, 5153, 5106, 5024, 4896, 4731, 4534, 4322, },
/* LAT: -10 */ {  3791, 3632, 3480, 3334, 3199, 3079, 2976, 2885, 2790, 2677, 2555, 2454, 2405, 2425, 2508, 2636, 2792, 2953, 3080, 3146, 3161, 3185, 3303, 3549, 3872, 4194, 4461, 4628, 4666, 4614, 4547, 4482, 4393, 4268, 4120, 3957, 3791, },
/* LAT:   0 */ {  3412, 3321, 3238, 3166, 3111, 3073, 3048, 3031, 3009, 2962, 2884, 2789, 2705, 2670, 2707, 2808, 2940, 3077, 3194, 3271, 3304, 3324, 3396, 3549, 3756, 3968, 4149, 4258, 4266, 4200, 4112, 4019, 3907, 3775, 3642, 3519, 3412, },
/* LAT:  10 */ {  3283, 3253, 3234, 3231, 3256, 3304, 3361, 3417, 3454, 3445, 3377, 3262, 3134, 3035, 3004, 3043, 3122, 3220, 3321, 3407, 3471, 3533, 3619, 3735, 3868, 4005, 4125, 4197, 4201, 4140, 4032, 3889, 3727, 3568, 3434, 3338, 3283, },
/* LAT:  20 */ {  3400, 3404, 3432, 3487, 3580, 3703, 3833, 3952, 4035, 4048, 3975, 3833, 3664, 3521, 3441, 3426, 3459, 3530, 3626, 3722, 3813, 3910, 4020, 4131, 4238, 4348, 4449, 4516, 4528, 4471, 4336, 4135, 3909, 3700, 3537, 3437, 3400, },
/* LAT:  30 */ {  3723, 3732, 3789, 3890, 4035, 4207, 4384, 4542, 4651, 4679, 4606, 4450, 4258, 4090, 3981, 3933, 3934, 3982, 4068, 4165, 4261, 4365, 4481, 4599, 4718, 4843, 4962, 5049, 5077, 5021, 4867, 4629, 4355, 4102, 3903, 3776, 3723, },
/* LAT:  40 */ {  4223, 4224, 4292, 4418, 4586, 4775, 4960, 5117, 5222, 5248, 5179, 5029, 4840, 4662, 4531, 4453, 4425, 4445, 4503, 4581, 4666, 4762, 4877, 5010, 5160, 5321, 5472, 5582, 5624, 5572, 5418, 5181, 4907, 4648, 4438, 4294, 4223, },
/* LAT:  50 */ {  4831, 4828, 4887, 5000, 5148, 5308, 5459, 5579, 5652, 5661, 5596, 5468, 5303, 5137, 4998, 4898, 4841, 4828, 4850, 4899, 4967, 5057, 5176, 5325, 5500, 5684, 5851, 5970, 6017, 5975, 5845, 5650, 5424, 5207, 5027, 4899, 4831, },
/* LAT:  60 */ {  5392, 5383, 5415, 5480, 5568, 5662, 5749, 5814, 5846, 5836, 5780, 5684, 5562, 5432, 5312, 5214, 5146, 5111, 5108, 5135, 5190, 5276, 5393, 5539, 5706, 5875, 6023, 6129, 6175, 6154, 6072, 5945, 5798, 5654, 5531, 5442, 5392, },
/* LAT:  70 */ {  5726, 5708, 5708, 5722, 5745, 5772, 5795, 5809, 5807, 5786, 5746, 5687, 5615, 5538, 5463, 5398, 5350, 5321, 5315, 5335, 5379, 5448, 5539, 5648, 5765, 5880, 5980, 6054, 6094, 6098, 6069, 6015, 5947, 5877, 5813, 5761, 5726, },
/* LAT:  80 */ {  5789, 5772, 5759, 5747, 5738, 5728, 5718, 5706, 5691, 5672, 5649, 5623, 5595, 5567, 5542, 5521, 5507, 5501, 5505, 5520, 5546, 5581, 5623, 5671, 5721, 5769, 5812, 5847, 5872, 5885, 5888, 5881, 5867, 5849, 5828, 5808, 5789, },
/* LAT:  90 */ {  5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, 5679, },
};
