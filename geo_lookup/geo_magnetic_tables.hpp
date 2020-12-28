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
// Date: 2020.989,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26026, 24281, 22535, 20790, 19045, 17299, 15554, 13809, 12063, 10318,  8573,  6827,  5082,  3337,  1592,  -154, -1899, -3644, -5390, -7135, -8880,-10625,-12371,-14116,-15861,-17607,-19352,-21097,-22843,-24588,-26334,-28079,-29824, 31262, 29517, 27771, 26026, },
/* LAT: -80 */ {  22597, 20460, 18515, 16738, 15095, 13555, 12089, 10677,  9301,  7950,  6617,  5298,  3989,  2684,  1377,    59, -1280, -2650, -4057, -5505, -6996, -8530,-10104,-11720,-13382,-15097,-16880,-18749,-20729,-22844,-25116,-27549,-30118, 30071, 27447, 24934, 22597, },
/* LAT: -70 */ {  14964, 13569, 12447, 11490, 10627,  9799,  8961,  8076,  7126,  6108,  5037,  3943,  2856,  1798,   773,  -237, -1272, -2372, -3566, -4858, -6232, -7656, -9099,-10538,-11962,-13375,-14801,-16281,-17896,-19795,-22291,-26052, 30863, 24210, 19630, 16838, 14964, },
/* LAT: -60 */ {   8368,  8133,  7863,  7598,  7353,  7107,  6806,  6379,  5770,  4955,  3957,  2845,  1721,   686,  -205,  -971, -1701, -2516, -3507, -4689, -6006, -7367, -8684, -9894,-10960,-11862,-12581,-13078,-13250,-12800,-10716, -3633,  4735,  7545,  8347,  8490,  8368, },
/* LAT: -50 */ {   5444,  5486,  5437,  5355,  5289,  5258,  5229,  5109,  4772,  4117,  3114,  1845,   500,  -693, -1582, -2165, -2571, -3006, -3671, -4657, -5878, -7143, -8283, -9191, -9800,-10053, -9875, -9132, -7637, -5286, -2388,   357,  2465,  3888,  4762,  5237,  5444, },
/* LAT: -40 */ {   3925,  4020,  4033,  3996,  3943,  3915,  3924,  3918,  3751,  3227,  2216,   783,  -784, -2115, -3002, -3477, -3678, -3747, -3901, -4429, -5368, -6429, -7320, -7874, -8002, -7648, -6779, -5403, -3687, -1975,  -509,   715,  1755,  2615,  3267,  3694,  3925, },
/* LAT: -30 */ {   2958,  3046,  3083,  3077,  3026,  2953,  2898,  2868,  2745,  2278,  1260,  -245, -1856, -3129, -3894, -4261, -4362, -4176, -3747, -3486, -3796, -4522, -5229, -5602, -5500, -4935, -3989, -2779, -1557,  -599,    86,   688,  1307,  1902,  2405,  2762,  2958, },
/* LAT: -20 */ {   2316,  2364,  2389,  2401,  2367,  2279,  2178,  2105,  1961,  1476,   440, -1034, -2519, -3602, -4164, -4305, -4125, -3591, -2739, -1916, -1595, -1919, -2566, -3051, -3108, -2765, -2138, -1316,  -526,   -25,   246,   550,   986,  1454,  1867,  2167,  2316, },
/* LAT: -10 */ {   1922,  1918,  1906,  1912,  1893,  1816,  1715,  1629,  1446,   905,  -141, -1509, -2792, -3647, -3946, -3747, -3190, -2418, -1571,  -803,  -315,  -321,  -776, -1287, -1515, -1436, -1127,  -624,  -116,   136,   194,   358,   722,  1147,  1530,  1808,  1922, },
/* LAT:   0 */ {   1710,  1679,  1631,  1632,  1629,  1569,  1474,  1368,  1117,   502,  -528, -1753, -2821, -3434, -3465, -2990, -2231, -1446,  -787,  -243,   178,   308,    45,  -372,  -635,  -696,  -598,  -333,   -35,    64,    13,   105,   439,   868,  1276,  1587,  1710, },
/* LAT:  10 */ {   1578,  1588,  1553,  1577,  1611,  1570,  1460,  1281,   909,   194,  -823, -1903, -2747, -3112, -2935, -2346, -1573,  -855,  -330,    56,   385,   545,   396,    75,  -165,  -274,  -293,  -207,   -97,  -131,  -261,  -231,    63,   505,   975,  1373,  1578, },
/* LAT:  20 */ {   1403,  1554,  1619,  1717,  1809,  1796,  1651,  1357,   815,   -41, -1086, -2047, -2663, -2795, -2486, -1894, -1185,  -530,   -60,   255,   517,   670,   588,   346,   143,    26,   -58,  -115,  -188,  -372,  -603,  -660,  -433,     5,   537,  1050,  1403, },
/* LAT:  30 */ {   1115,  1483,  1745,  1972,  2135,  2150,  1970,  1554,   829,  -202, -1328, -2221, -2656, -2611, -2224, -1650,  -995,  -373,    97,   409,   644,   797,   784,   637,   486,   362,   214,    14,  -260,  -630,  -997, -1158, -1005,  -586,   -14,   594,  1115, },
/* LAT:  40 */ {    773,  1361,  1855,  2247,  2496,  2542,  2330,  1800,   889,  -345, -1599, -2485, -2824, -2684, -2244, -1654, -1001,  -368,   148,   519,   795,  1000,  1101,  1094,  1018,   872,   614,   217,  -311,  -913, -1437, -1687, -1577, -1164,  -566,   110,   773, },
/* LAT:  50 */ {    501,  1251,  1930,  2484,  2848,  2952,  2722,  2066,   919,  -594, -2039, -2974, -3282, -3096, -2609, -1963, -1252,  -551,    71,   583,  1007,  1369,  1656,  1833,  1856,  1677,  1246,   555,  -326, -1228, -1915, -2212, -2094, -1653, -1012,  -271,   501, },
/* LAT:  60 */ {    330,  1188,  1993,  2684,  3181,  3386,  3164,  2339,   801, -1193, -2940, -3936, -4192, -3930, -3354, -2605, -1775,  -929,  -116,   641,  1339,  1975,  2525,  2929,  3100,  2929,  2312,  1220,  -181, -1506, -2390, -2711, -2550, -2050, -1345,  -530,   330, },
/* LAT:  70 */ {    143,  1087,  1987,  2784,  3392,  3675,  3400,  2217,  -111, -2909, -4885, -5698, -5687, -5186, -4403, -3457, -2423, -1349,  -267,   799,  1830,  2801,  3675,  4391,  4851,  4902,  4324,  2893,   733, -1375, -2690, -3144, -2985, -2444, -1681,  -796,   143, },
/* LAT:  80 */ {   -403,   526,  1386,  2082,  2463,  2244,   919, -1981, -5443, -7572, -8243, -8041, -7360, -6405, -5287, -4068, -2786, -1469,  -134,  1200,  2520,  3806,  5035,  6175,  7172,  7933,  8283,  7870,  6053,  2495,  -998, -2743, -3147, -2843, -2177, -1329,  -403, },
/* LAT:  90 */ { -30420,-28674,-26929,-25183,-23438,-21692,-19947,-18202,-16456,-14711,-12966,-11221, -9476, -7730, -5985, -4240, -2495,  -750,   996,  2741,  4486,  6231,  7976,  9722, 11467, 13212, 14958, 16703, 18449, 20194, 21939, 23685, 25430, 27176, 28921, 30667,-30420, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.989,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581,-12581, },
/* LAT: -80 */ { -13669,-13535,-13375,-13194,-13000,-12798,-12593,-12392,-12201,-12024,-11867,-11732,-11621,-11535,-11472,-11430,-11411,-11414,-11441,-11495,-11578,-11692,-11836,-12009,-12207,-12423,-12652,-12885,-13113,-13326,-13513,-13664,-13769,-13822,-13820,-13766,-13669, },
/* LAT: -70 */ { -14119,-13801,-13481,-13158,-12826,-12481,-12124,-11766,-11421,-11111,-10856,-10670,-10556,-10503,-10490,-10495,-10505,-10517,-10542,-10599,-10706,-10878,-11122,-11434,-11804,-12220,-12667,-13131,-13597,-14050,-14469,-14817,-15011,-14962,-14732,-14435,-14119, },
/* LAT: -60 */ { -13526,-13174,-12837,-12505,-12161,-11788,-11373,-10917,-10447,-10014, -9679, -9498, -9490, -9624, -9830,-10027,-10160,-10212,-10206,-10194,-10239,-10393,-10676,-11078,-11572,-12125,-12709,-13305,-13894,-14455,-14951,-15243,-15075,-14694,-14290,-13898,-13526, },
/* LAT: -50 */ { -12499,-12159,-11830,-11508,-11185,-10838,-10439, -9966, -9434, -8909, -8511, -8375, -8566, -9021, -9586,-10106,-10478,-10655,-10640,-10497,-10355,-10352,-10560,-10965,-11500,-12090,-12677,-13218,-13667,-13967,-14077,-14005,-13803,-13520,-13193,-12847,-12499, },
/* LAT: -40 */ { -11240,-10895,-10551,-10207, -9868, -9528, -9166, -8739, -8215, -7646, -7210, -7151, -7593, -8407, -9330,-10168,-10839,-11290,-11452,-11305,-10971,-10690,-10667,-10933,-11387,-11890,-12340,-12669,-12833,-12840,-12749,-12610,-12429,-12196,-11911,-11584,-11240, },
/* LAT: -30 */ {  -9601, -9228, -8854, -8466, -8073, -7696, -7336, -6941, -6426, -5812, -5347, -5403, -6145, -7334, -8587, -9693,-10618,-11345,-11768,-11786,-11432,-10925,-10578,-10562,-10804,-11125,-11388,-11509,-11451,-11276,-11098,-10958,-10808,-10598,-10317, -9974, -9601, },
/* LAT: -20 */ {  -7368, -6939, -6530, -6106, -5661, -5228, -4833, -4413, -3842, -3153, -2688, -2913, -3987, -5582, -7215, -8602, -9686,-10482,-10944,-11004,-10660,-10056, -9492, -9235, -9275, -9435, -9581, -9606, -9438, -9165, -8965, -8869, -8756, -8544, -8227, -7819, -7368, },
/* LAT: -10 */ {  -4411, -3890, -3449, -3017, -2560, -2108, -1688, -1223,  -587,   125,   508,   119, -1170, -3067, -5049, -6684, -7810, -8468, -8754, -8710, -8320, -7650, -6985, -6629, -6582, -6675, -6796, -6825, -6640, -6342, -6179, -6174, -6119, -5896, -5513, -4991, -4411, },
/* LAT:   0 */ {   -900,  -296,   156,   552,   969,  1387,  1783,  2240,  2838,  3428,  3651,  3188,  1928,    41, -2008, -3688, -4732, -5187, -5263, -5106, -4683, -3983, -3278, -2897, -2834, -2906, -3035, -3111, -2982, -2744, -2679, -2803, -2847, -2652, -2228, -1606,  -900, },
/* LAT:  10 */ {   2567,  3176,  3598,  3933,  4286,  4655,  5013,  5413,  5878,  6261,  6314,  5849,  4794,  3247,  1554,   156,  -680,  -952,  -876,  -650,  -252,   374,  1006,  1350,  1411,  1361,  1257,  1165,  1209,  1317,  1252,  1004,   832,   913,  1264,  1858,  2567, },
/* LAT:  20 */ {   5420,  5936,  6307,  6598,  6910,  7255,  7603,  7961,  8306,  8517,  8442,  7995,  7176,  6090,  4962,  4039,  3490,  3352,  3489,  3726,  4049,  4506,  4965,  5222,  5276,  5252,  5200,  5143,  5135,  5123,  4958,  4640,  4355,  4272,  4443,  4860,  5420, },
/* LAT:  30 */ {   7570,  7937,  8250,  8531,  8840,  9188,  9550,  9898, 10183, 10306, 10170,  9758,  9137,  8428,  7764,  7244,  6941,  6887,  7020,  7226,  7468,  7762,  8049,  8223,  8277,  8285,  8283,  8275,  8256,  8179,  7964,  7620,  7273,  7057,  7040,  7231,  7570, },
/* LAT:  40 */ {   9265,  9485,  9740, 10025, 10352, 10715, 11086, 11430, 11688, 11777, 11634, 11278, 10806, 10332,  9932,  9643,  9487,  9476,  9580,  9737,  9908, 10089, 10260, 10384, 10461, 10517, 10569, 10602, 10589, 10484, 10248,  9903,  9539,  9257,  9113,  9124,  9265, },
/* LAT:  50 */ {  10801, 10923, 11125, 11396, 11721, 12077, 12435, 12755, 12981, 13044, 12907, 12610, 12245, 11897, 11619, 11428, 11330, 11322, 11384, 11483, 11594, 11707, 11822, 11937, 12054, 12174, 12285, 12358, 12353, 12233, 11991, 11666, 11328, 11043, 10854, 10774, 10801, },
/* LAT:  60 */ {  12318, 12393, 12546, 12767, 13040, 13342, 13647, 13916, 14094, 14122, 13986, 13735, 13444, 13171, 12948, 12788, 12695, 12660, 12673, 12718, 12784, 12867, 12971, 13101, 13259, 13433, 13597, 13708, 13718, 13603, 13381, 13103, 12824, 12586, 12416, 12325, 12318, },
/* LAT:  70 */ {  13759, 13804, 13903, 14048, 14231, 14437, 14648, 14830, 14934, 14911, 14770, 14565, 14345, 14139, 13965, 13828, 13733, 13677, 13656, 13667, 13708, 13778, 13879, 14014, 14179, 14365, 14550, 14692, 14742, 14674, 14514, 14316, 14121, 13956, 13836, 13770, 13759, },
/* LAT:  80 */ {  15004, 15018, 15059, 15121, 15200, 15288, 15369, 15413, 15390, 15304, 15187, 15060, 14936, 14821, 14720, 14637, 14575, 14533, 14514, 14517, 14543, 14591, 14662, 14754, 14865, 14991, 15125, 15256, 15363, 15410, 15375, 15292, 15199, 15117, 15054, 15015, 15004, },
/* LAT:  90 */ {  15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, 15390, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.989,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5461, 5461, 5461, 5461, 5461, 5461, 5461, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5460, 5461, 5461, 5461, 5461, 5461, 5461, 5461, 5461, 5461, 5461, },
/* LAT: -80 */ {  6067, 6004, 5926, 5835, 5733, 5622, 5504, 5382, 5260, 5140, 5026, 4920, 4826, 4746, 4682, 4637, 4612, 4609, 4630, 4675, 4745, 4838, 4952, 5083, 5226, 5375, 5525, 5668, 5799, 5913, 6006, 6075, 6120, 6140, 6137, 6112, 6067, },
/* LAT: -70 */ {  6311, 6180, 6031, 5868, 5690, 5499, 5294, 5079, 4860, 4644, 4441, 4258, 4099, 3968, 3863, 3786, 3738, 3725, 3752, 3826, 3953, 4131, 4358, 4624, 4918, 5225, 5528, 5812, 6062, 6267, 6419, 6515, 6558, 6552, 6504, 6421, 6311, },
/* LAT: -60 */ {  6196, 6006, 5806, 5599, 5381, 5148, 4892, 4613, 4321, 4030, 3762, 3533, 3353, 3217, 3117, 3044, 2993, 2973, 2998, 3086, 3252, 3500, 3824, 4208, 4628, 5062, 5483, 5868, 6193, 6443, 6608, 6688, 6692, 6631, 6519, 6370, 6196, },
/* LAT: -50 */ {  5851, 5623, 5393, 5164, 4933, 4689, 4419, 4116, 3787, 3455, 3151, 2909, 2746, 2653, 2605, 2571, 2539, 2514, 2518, 2588, 2757, 3042, 3433, 3901, 4407, 4913, 5389, 5809, 6149, 6392, 6532, 6575, 6534, 6425, 6265, 6069, 5851, },
/* LAT: -40 */ {  5398, 5154, 4911, 4673, 4440, 4204, 3950, 3666, 3352, 3026, 2726, 2501, 2381, 2354, 2373, 2396, 2403, 2394, 2383, 2409, 2534, 2801, 3211, 3721, 4266, 4792, 5261, 5652, 5946, 6135, 6225, 6229, 6161, 6032, 5852, 5636, 5398, },
/* LAT: -30 */ {  4882, 4643, 4406, 4173, 3947, 3729, 3511, 3280, 3025, 2750, 2491, 2306, 2233, 2255, 2322, 2395, 2462, 2515, 2541, 2554, 2616, 2805, 3158, 3640, 4170, 4669, 5092, 5413, 5618, 5719, 5746, 5720, 5642, 5510, 5332, 5117, 4882, },
/* LAT: -20 */ {  4323, 4112, 3906, 3702, 3506, 3324, 3156, 2993, 2817, 2620, 2429, 2293, 2247, 2287, 2374, 2485, 2614, 2745, 2839, 2879, 2902, 2990, 3220, 3597, 4044, 4472, 4825, 5065, 5174, 5183, 5153, 5105, 5023, 4896, 4730, 4534, 4323, },
/* LAT: -10 */ {  3791, 3632, 3481, 3336, 3200, 3080, 2978, 2887, 2792, 2679, 2558, 2456, 2407, 2425, 2508, 2635, 2791, 2953, 3081, 3148, 3163, 3186, 3302, 3547, 3869, 4191, 4459, 4626, 4665, 4614, 4546, 4482, 4393, 4268, 4119, 3957, 3791, },
/* LAT:   0 */ {  3412, 3321, 3239, 3167, 3112, 3074, 3050, 3033, 3011, 2965, 2887, 2791, 2707, 2671, 2707, 2807, 2939, 3076, 3194, 3272, 3304, 3325, 3395, 3548, 3753, 3966, 4147, 4257, 4265, 4199, 4111, 4019, 3906, 3775, 3641, 3519, 3412, },
/* LAT:  10 */ {  3283, 3253, 3234, 3232, 3257, 3306, 3363, 3419, 3457, 3449, 3380, 3265, 3136, 3037, 3005, 3042, 3122, 3220, 3321, 3406, 3471, 3532, 3618, 3733, 3866, 4003, 4122, 4195, 4199, 4139, 4031, 3888, 3727, 3568, 3433, 3338, 3283, },
/* LAT:  20 */ {  3400, 3405, 3433, 3489, 3582, 3705, 3835, 3955, 4038, 4052, 3979, 3837, 3667, 3523, 3442, 3426, 3459, 3530, 3625, 3722, 3812, 3909, 4018, 4129, 4236, 4345, 4446, 4513, 4526, 4469, 4334, 4134, 3908, 3699, 3537, 3437, 3400, },
/* LAT:  30 */ {  3723, 3733, 3790, 3892, 4037, 4210, 4388, 4546, 4655, 4683, 4610, 4453, 4262, 4093, 3983, 3933, 3934, 3982, 4066, 4163, 4259, 4363, 4479, 4596, 4715, 4840, 4958, 5045, 5074, 5019, 4865, 4627, 4354, 4101, 3902, 3776, 3723, },
/* LAT:  40 */ {  4223, 4225, 4293, 4420, 4589, 4779, 4963, 5121, 5226, 5252, 5183, 5032, 4842, 4664, 4532, 4454, 4425, 4444, 4502, 4579, 4664, 4760, 4874, 5007, 5158, 5318, 5468, 5579, 5621, 5570, 5417, 5180, 4906, 4647, 4437, 4293, 4223, },
/* LAT:  50 */ {  4831, 4829, 4889, 5003, 5151, 5312, 5462, 5583, 5656, 5664, 5599, 5470, 5305, 5138, 4998, 4898, 4841, 4826, 4849, 4897, 4965, 5055, 5173, 5322, 5497, 5681, 5848, 5968, 6015, 5974, 5845, 5649, 5423, 5206, 5026, 4898, 4831, },
/* LAT:  60 */ {  5392, 5384, 5417, 5483, 5571, 5666, 5752, 5817, 5849, 5838, 5782, 5686, 5563, 5433, 5312, 5214, 5146, 5110, 5107, 5133, 5188, 5274, 5390, 5537, 5703, 5872, 6021, 6127, 6174, 6153, 6071, 5944, 5796, 5652, 5530, 5441, 5392, },
/* LAT:  70 */ {  5726, 5709, 5710, 5724, 5748, 5774, 5798, 5811, 5809, 5788, 5746, 5687, 5615, 5538, 5463, 5398, 5348, 5320, 5314, 5333, 5377, 5446, 5537, 5645, 5763, 5878, 5978, 6052, 6092, 6097, 6068, 6014, 5946, 5876, 5812, 5760, 5726, },
/* LAT:  80 */ {  5789, 5772, 5759, 5748, 5738, 5729, 5719, 5707, 5691, 5672, 5649, 5623, 5595, 5567, 5541, 5520, 5506, 5500, 5504, 5519, 5544, 5579, 5622, 5670, 5720, 5768, 5811, 5846, 5870, 5884, 5886, 5880, 5866, 5848, 5827, 5807, 5789, },
/* LAT:  90 */ {  5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, 5678, },
};
