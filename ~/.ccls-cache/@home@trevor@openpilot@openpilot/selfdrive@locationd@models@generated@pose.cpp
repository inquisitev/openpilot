#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.13.3                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3215194707115345059) {
   out_3215194707115345059[0] = delta_x[0] + nom_x[0];
   out_3215194707115345059[1] = delta_x[1] + nom_x[1];
   out_3215194707115345059[2] = delta_x[2] + nom_x[2];
   out_3215194707115345059[3] = delta_x[3] + nom_x[3];
   out_3215194707115345059[4] = delta_x[4] + nom_x[4];
   out_3215194707115345059[5] = delta_x[5] + nom_x[5];
   out_3215194707115345059[6] = delta_x[6] + nom_x[6];
   out_3215194707115345059[7] = delta_x[7] + nom_x[7];
   out_3215194707115345059[8] = delta_x[8] + nom_x[8];
   out_3215194707115345059[9] = delta_x[9] + nom_x[9];
   out_3215194707115345059[10] = delta_x[10] + nom_x[10];
   out_3215194707115345059[11] = delta_x[11] + nom_x[11];
   out_3215194707115345059[12] = delta_x[12] + nom_x[12];
   out_3215194707115345059[13] = delta_x[13] + nom_x[13];
   out_3215194707115345059[14] = delta_x[14] + nom_x[14];
   out_3215194707115345059[15] = delta_x[15] + nom_x[15];
   out_3215194707115345059[16] = delta_x[16] + nom_x[16];
   out_3215194707115345059[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9204099396150886653) {
   out_9204099396150886653[0] = -nom_x[0] + true_x[0];
   out_9204099396150886653[1] = -nom_x[1] + true_x[1];
   out_9204099396150886653[2] = -nom_x[2] + true_x[2];
   out_9204099396150886653[3] = -nom_x[3] + true_x[3];
   out_9204099396150886653[4] = -nom_x[4] + true_x[4];
   out_9204099396150886653[5] = -nom_x[5] + true_x[5];
   out_9204099396150886653[6] = -nom_x[6] + true_x[6];
   out_9204099396150886653[7] = -nom_x[7] + true_x[7];
   out_9204099396150886653[8] = -nom_x[8] + true_x[8];
   out_9204099396150886653[9] = -nom_x[9] + true_x[9];
   out_9204099396150886653[10] = -nom_x[10] + true_x[10];
   out_9204099396150886653[11] = -nom_x[11] + true_x[11];
   out_9204099396150886653[12] = -nom_x[12] + true_x[12];
   out_9204099396150886653[13] = -nom_x[13] + true_x[13];
   out_9204099396150886653[14] = -nom_x[14] + true_x[14];
   out_9204099396150886653[15] = -nom_x[15] + true_x[15];
   out_9204099396150886653[16] = -nom_x[16] + true_x[16];
   out_9204099396150886653[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_9102264402289458033) {
   out_9102264402289458033[0] = 1.0;
   out_9102264402289458033[1] = 0.0;
   out_9102264402289458033[2] = 0.0;
   out_9102264402289458033[3] = 0.0;
   out_9102264402289458033[4] = 0.0;
   out_9102264402289458033[5] = 0.0;
   out_9102264402289458033[6] = 0.0;
   out_9102264402289458033[7] = 0.0;
   out_9102264402289458033[8] = 0.0;
   out_9102264402289458033[9] = 0.0;
   out_9102264402289458033[10] = 0.0;
   out_9102264402289458033[11] = 0.0;
   out_9102264402289458033[12] = 0.0;
   out_9102264402289458033[13] = 0.0;
   out_9102264402289458033[14] = 0.0;
   out_9102264402289458033[15] = 0.0;
   out_9102264402289458033[16] = 0.0;
   out_9102264402289458033[17] = 0.0;
   out_9102264402289458033[18] = 0.0;
   out_9102264402289458033[19] = 1.0;
   out_9102264402289458033[20] = 0.0;
   out_9102264402289458033[21] = 0.0;
   out_9102264402289458033[22] = 0.0;
   out_9102264402289458033[23] = 0.0;
   out_9102264402289458033[24] = 0.0;
   out_9102264402289458033[25] = 0.0;
   out_9102264402289458033[26] = 0.0;
   out_9102264402289458033[27] = 0.0;
   out_9102264402289458033[28] = 0.0;
   out_9102264402289458033[29] = 0.0;
   out_9102264402289458033[30] = 0.0;
   out_9102264402289458033[31] = 0.0;
   out_9102264402289458033[32] = 0.0;
   out_9102264402289458033[33] = 0.0;
   out_9102264402289458033[34] = 0.0;
   out_9102264402289458033[35] = 0.0;
   out_9102264402289458033[36] = 0.0;
   out_9102264402289458033[37] = 0.0;
   out_9102264402289458033[38] = 1.0;
   out_9102264402289458033[39] = 0.0;
   out_9102264402289458033[40] = 0.0;
   out_9102264402289458033[41] = 0.0;
   out_9102264402289458033[42] = 0.0;
   out_9102264402289458033[43] = 0.0;
   out_9102264402289458033[44] = 0.0;
   out_9102264402289458033[45] = 0.0;
   out_9102264402289458033[46] = 0.0;
   out_9102264402289458033[47] = 0.0;
   out_9102264402289458033[48] = 0.0;
   out_9102264402289458033[49] = 0.0;
   out_9102264402289458033[50] = 0.0;
   out_9102264402289458033[51] = 0.0;
   out_9102264402289458033[52] = 0.0;
   out_9102264402289458033[53] = 0.0;
   out_9102264402289458033[54] = 0.0;
   out_9102264402289458033[55] = 0.0;
   out_9102264402289458033[56] = 0.0;
   out_9102264402289458033[57] = 1.0;
   out_9102264402289458033[58] = 0.0;
   out_9102264402289458033[59] = 0.0;
   out_9102264402289458033[60] = 0.0;
   out_9102264402289458033[61] = 0.0;
   out_9102264402289458033[62] = 0.0;
   out_9102264402289458033[63] = 0.0;
   out_9102264402289458033[64] = 0.0;
   out_9102264402289458033[65] = 0.0;
   out_9102264402289458033[66] = 0.0;
   out_9102264402289458033[67] = 0.0;
   out_9102264402289458033[68] = 0.0;
   out_9102264402289458033[69] = 0.0;
   out_9102264402289458033[70] = 0.0;
   out_9102264402289458033[71] = 0.0;
   out_9102264402289458033[72] = 0.0;
   out_9102264402289458033[73] = 0.0;
   out_9102264402289458033[74] = 0.0;
   out_9102264402289458033[75] = 0.0;
   out_9102264402289458033[76] = 1.0;
   out_9102264402289458033[77] = 0.0;
   out_9102264402289458033[78] = 0.0;
   out_9102264402289458033[79] = 0.0;
   out_9102264402289458033[80] = 0.0;
   out_9102264402289458033[81] = 0.0;
   out_9102264402289458033[82] = 0.0;
   out_9102264402289458033[83] = 0.0;
   out_9102264402289458033[84] = 0.0;
   out_9102264402289458033[85] = 0.0;
   out_9102264402289458033[86] = 0.0;
   out_9102264402289458033[87] = 0.0;
   out_9102264402289458033[88] = 0.0;
   out_9102264402289458033[89] = 0.0;
   out_9102264402289458033[90] = 0.0;
   out_9102264402289458033[91] = 0.0;
   out_9102264402289458033[92] = 0.0;
   out_9102264402289458033[93] = 0.0;
   out_9102264402289458033[94] = 0.0;
   out_9102264402289458033[95] = 1.0;
   out_9102264402289458033[96] = 0.0;
   out_9102264402289458033[97] = 0.0;
   out_9102264402289458033[98] = 0.0;
   out_9102264402289458033[99] = 0.0;
   out_9102264402289458033[100] = 0.0;
   out_9102264402289458033[101] = 0.0;
   out_9102264402289458033[102] = 0.0;
   out_9102264402289458033[103] = 0.0;
   out_9102264402289458033[104] = 0.0;
   out_9102264402289458033[105] = 0.0;
   out_9102264402289458033[106] = 0.0;
   out_9102264402289458033[107] = 0.0;
   out_9102264402289458033[108] = 0.0;
   out_9102264402289458033[109] = 0.0;
   out_9102264402289458033[110] = 0.0;
   out_9102264402289458033[111] = 0.0;
   out_9102264402289458033[112] = 0.0;
   out_9102264402289458033[113] = 0.0;
   out_9102264402289458033[114] = 1.0;
   out_9102264402289458033[115] = 0.0;
   out_9102264402289458033[116] = 0.0;
   out_9102264402289458033[117] = 0.0;
   out_9102264402289458033[118] = 0.0;
   out_9102264402289458033[119] = 0.0;
   out_9102264402289458033[120] = 0.0;
   out_9102264402289458033[121] = 0.0;
   out_9102264402289458033[122] = 0.0;
   out_9102264402289458033[123] = 0.0;
   out_9102264402289458033[124] = 0.0;
   out_9102264402289458033[125] = 0.0;
   out_9102264402289458033[126] = 0.0;
   out_9102264402289458033[127] = 0.0;
   out_9102264402289458033[128] = 0.0;
   out_9102264402289458033[129] = 0.0;
   out_9102264402289458033[130] = 0.0;
   out_9102264402289458033[131] = 0.0;
   out_9102264402289458033[132] = 0.0;
   out_9102264402289458033[133] = 1.0;
   out_9102264402289458033[134] = 0.0;
   out_9102264402289458033[135] = 0.0;
   out_9102264402289458033[136] = 0.0;
   out_9102264402289458033[137] = 0.0;
   out_9102264402289458033[138] = 0.0;
   out_9102264402289458033[139] = 0.0;
   out_9102264402289458033[140] = 0.0;
   out_9102264402289458033[141] = 0.0;
   out_9102264402289458033[142] = 0.0;
   out_9102264402289458033[143] = 0.0;
   out_9102264402289458033[144] = 0.0;
   out_9102264402289458033[145] = 0.0;
   out_9102264402289458033[146] = 0.0;
   out_9102264402289458033[147] = 0.0;
   out_9102264402289458033[148] = 0.0;
   out_9102264402289458033[149] = 0.0;
   out_9102264402289458033[150] = 0.0;
   out_9102264402289458033[151] = 0.0;
   out_9102264402289458033[152] = 1.0;
   out_9102264402289458033[153] = 0.0;
   out_9102264402289458033[154] = 0.0;
   out_9102264402289458033[155] = 0.0;
   out_9102264402289458033[156] = 0.0;
   out_9102264402289458033[157] = 0.0;
   out_9102264402289458033[158] = 0.0;
   out_9102264402289458033[159] = 0.0;
   out_9102264402289458033[160] = 0.0;
   out_9102264402289458033[161] = 0.0;
   out_9102264402289458033[162] = 0.0;
   out_9102264402289458033[163] = 0.0;
   out_9102264402289458033[164] = 0.0;
   out_9102264402289458033[165] = 0.0;
   out_9102264402289458033[166] = 0.0;
   out_9102264402289458033[167] = 0.0;
   out_9102264402289458033[168] = 0.0;
   out_9102264402289458033[169] = 0.0;
   out_9102264402289458033[170] = 0.0;
   out_9102264402289458033[171] = 1.0;
   out_9102264402289458033[172] = 0.0;
   out_9102264402289458033[173] = 0.0;
   out_9102264402289458033[174] = 0.0;
   out_9102264402289458033[175] = 0.0;
   out_9102264402289458033[176] = 0.0;
   out_9102264402289458033[177] = 0.0;
   out_9102264402289458033[178] = 0.0;
   out_9102264402289458033[179] = 0.0;
   out_9102264402289458033[180] = 0.0;
   out_9102264402289458033[181] = 0.0;
   out_9102264402289458033[182] = 0.0;
   out_9102264402289458033[183] = 0.0;
   out_9102264402289458033[184] = 0.0;
   out_9102264402289458033[185] = 0.0;
   out_9102264402289458033[186] = 0.0;
   out_9102264402289458033[187] = 0.0;
   out_9102264402289458033[188] = 0.0;
   out_9102264402289458033[189] = 0.0;
   out_9102264402289458033[190] = 1.0;
   out_9102264402289458033[191] = 0.0;
   out_9102264402289458033[192] = 0.0;
   out_9102264402289458033[193] = 0.0;
   out_9102264402289458033[194] = 0.0;
   out_9102264402289458033[195] = 0.0;
   out_9102264402289458033[196] = 0.0;
   out_9102264402289458033[197] = 0.0;
   out_9102264402289458033[198] = 0.0;
   out_9102264402289458033[199] = 0.0;
   out_9102264402289458033[200] = 0.0;
   out_9102264402289458033[201] = 0.0;
   out_9102264402289458033[202] = 0.0;
   out_9102264402289458033[203] = 0.0;
   out_9102264402289458033[204] = 0.0;
   out_9102264402289458033[205] = 0.0;
   out_9102264402289458033[206] = 0.0;
   out_9102264402289458033[207] = 0.0;
   out_9102264402289458033[208] = 0.0;
   out_9102264402289458033[209] = 1.0;
   out_9102264402289458033[210] = 0.0;
   out_9102264402289458033[211] = 0.0;
   out_9102264402289458033[212] = 0.0;
   out_9102264402289458033[213] = 0.0;
   out_9102264402289458033[214] = 0.0;
   out_9102264402289458033[215] = 0.0;
   out_9102264402289458033[216] = 0.0;
   out_9102264402289458033[217] = 0.0;
   out_9102264402289458033[218] = 0.0;
   out_9102264402289458033[219] = 0.0;
   out_9102264402289458033[220] = 0.0;
   out_9102264402289458033[221] = 0.0;
   out_9102264402289458033[222] = 0.0;
   out_9102264402289458033[223] = 0.0;
   out_9102264402289458033[224] = 0.0;
   out_9102264402289458033[225] = 0.0;
   out_9102264402289458033[226] = 0.0;
   out_9102264402289458033[227] = 0.0;
   out_9102264402289458033[228] = 1.0;
   out_9102264402289458033[229] = 0.0;
   out_9102264402289458033[230] = 0.0;
   out_9102264402289458033[231] = 0.0;
   out_9102264402289458033[232] = 0.0;
   out_9102264402289458033[233] = 0.0;
   out_9102264402289458033[234] = 0.0;
   out_9102264402289458033[235] = 0.0;
   out_9102264402289458033[236] = 0.0;
   out_9102264402289458033[237] = 0.0;
   out_9102264402289458033[238] = 0.0;
   out_9102264402289458033[239] = 0.0;
   out_9102264402289458033[240] = 0.0;
   out_9102264402289458033[241] = 0.0;
   out_9102264402289458033[242] = 0.0;
   out_9102264402289458033[243] = 0.0;
   out_9102264402289458033[244] = 0.0;
   out_9102264402289458033[245] = 0.0;
   out_9102264402289458033[246] = 0.0;
   out_9102264402289458033[247] = 1.0;
   out_9102264402289458033[248] = 0.0;
   out_9102264402289458033[249] = 0.0;
   out_9102264402289458033[250] = 0.0;
   out_9102264402289458033[251] = 0.0;
   out_9102264402289458033[252] = 0.0;
   out_9102264402289458033[253] = 0.0;
   out_9102264402289458033[254] = 0.0;
   out_9102264402289458033[255] = 0.0;
   out_9102264402289458033[256] = 0.0;
   out_9102264402289458033[257] = 0.0;
   out_9102264402289458033[258] = 0.0;
   out_9102264402289458033[259] = 0.0;
   out_9102264402289458033[260] = 0.0;
   out_9102264402289458033[261] = 0.0;
   out_9102264402289458033[262] = 0.0;
   out_9102264402289458033[263] = 0.0;
   out_9102264402289458033[264] = 0.0;
   out_9102264402289458033[265] = 0.0;
   out_9102264402289458033[266] = 1.0;
   out_9102264402289458033[267] = 0.0;
   out_9102264402289458033[268] = 0.0;
   out_9102264402289458033[269] = 0.0;
   out_9102264402289458033[270] = 0.0;
   out_9102264402289458033[271] = 0.0;
   out_9102264402289458033[272] = 0.0;
   out_9102264402289458033[273] = 0.0;
   out_9102264402289458033[274] = 0.0;
   out_9102264402289458033[275] = 0.0;
   out_9102264402289458033[276] = 0.0;
   out_9102264402289458033[277] = 0.0;
   out_9102264402289458033[278] = 0.0;
   out_9102264402289458033[279] = 0.0;
   out_9102264402289458033[280] = 0.0;
   out_9102264402289458033[281] = 0.0;
   out_9102264402289458033[282] = 0.0;
   out_9102264402289458033[283] = 0.0;
   out_9102264402289458033[284] = 0.0;
   out_9102264402289458033[285] = 1.0;
   out_9102264402289458033[286] = 0.0;
   out_9102264402289458033[287] = 0.0;
   out_9102264402289458033[288] = 0.0;
   out_9102264402289458033[289] = 0.0;
   out_9102264402289458033[290] = 0.0;
   out_9102264402289458033[291] = 0.0;
   out_9102264402289458033[292] = 0.0;
   out_9102264402289458033[293] = 0.0;
   out_9102264402289458033[294] = 0.0;
   out_9102264402289458033[295] = 0.0;
   out_9102264402289458033[296] = 0.0;
   out_9102264402289458033[297] = 0.0;
   out_9102264402289458033[298] = 0.0;
   out_9102264402289458033[299] = 0.0;
   out_9102264402289458033[300] = 0.0;
   out_9102264402289458033[301] = 0.0;
   out_9102264402289458033[302] = 0.0;
   out_9102264402289458033[303] = 0.0;
   out_9102264402289458033[304] = 1.0;
   out_9102264402289458033[305] = 0.0;
   out_9102264402289458033[306] = 0.0;
   out_9102264402289458033[307] = 0.0;
   out_9102264402289458033[308] = 0.0;
   out_9102264402289458033[309] = 0.0;
   out_9102264402289458033[310] = 0.0;
   out_9102264402289458033[311] = 0.0;
   out_9102264402289458033[312] = 0.0;
   out_9102264402289458033[313] = 0.0;
   out_9102264402289458033[314] = 0.0;
   out_9102264402289458033[315] = 0.0;
   out_9102264402289458033[316] = 0.0;
   out_9102264402289458033[317] = 0.0;
   out_9102264402289458033[318] = 0.0;
   out_9102264402289458033[319] = 0.0;
   out_9102264402289458033[320] = 0.0;
   out_9102264402289458033[321] = 0.0;
   out_9102264402289458033[322] = 0.0;
   out_9102264402289458033[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7197250978786250178) {
   out_7197250978786250178[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7197250978786250178[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7197250978786250178[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7197250978786250178[3] = dt*state[12] + state[3];
   out_7197250978786250178[4] = dt*state[13] + state[4];
   out_7197250978786250178[5] = dt*state[14] + state[5];
   out_7197250978786250178[6] = state[6];
   out_7197250978786250178[7] = state[7];
   out_7197250978786250178[8] = state[8];
   out_7197250978786250178[9] = state[9];
   out_7197250978786250178[10] = state[10];
   out_7197250978786250178[11] = state[11];
   out_7197250978786250178[12] = state[12];
   out_7197250978786250178[13] = state[13];
   out_7197250978786250178[14] = state[14];
   out_7197250978786250178[15] = state[15];
   out_7197250978786250178[16] = state[16];
   out_7197250978786250178[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4362570687790572879) {
   out_4362570687790572879[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4362570687790572879[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4362570687790572879[2] = 0;
   out_4362570687790572879[3] = 0;
   out_4362570687790572879[4] = 0;
   out_4362570687790572879[5] = 0;
   out_4362570687790572879[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4362570687790572879[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4362570687790572879[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4362570687790572879[9] = 0;
   out_4362570687790572879[10] = 0;
   out_4362570687790572879[11] = 0;
   out_4362570687790572879[12] = 0;
   out_4362570687790572879[13] = 0;
   out_4362570687790572879[14] = 0;
   out_4362570687790572879[15] = 0;
   out_4362570687790572879[16] = 0;
   out_4362570687790572879[17] = 0;
   out_4362570687790572879[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4362570687790572879[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4362570687790572879[20] = 0;
   out_4362570687790572879[21] = 0;
   out_4362570687790572879[22] = 0;
   out_4362570687790572879[23] = 0;
   out_4362570687790572879[24] = 0;
   out_4362570687790572879[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4362570687790572879[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4362570687790572879[27] = 0;
   out_4362570687790572879[28] = 0;
   out_4362570687790572879[29] = 0;
   out_4362570687790572879[30] = 0;
   out_4362570687790572879[31] = 0;
   out_4362570687790572879[32] = 0;
   out_4362570687790572879[33] = 0;
   out_4362570687790572879[34] = 0;
   out_4362570687790572879[35] = 0;
   out_4362570687790572879[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4362570687790572879[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4362570687790572879[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4362570687790572879[39] = 0;
   out_4362570687790572879[40] = 0;
   out_4362570687790572879[41] = 0;
   out_4362570687790572879[42] = 0;
   out_4362570687790572879[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4362570687790572879[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4362570687790572879[45] = 0;
   out_4362570687790572879[46] = 0;
   out_4362570687790572879[47] = 0;
   out_4362570687790572879[48] = 0;
   out_4362570687790572879[49] = 0;
   out_4362570687790572879[50] = 0;
   out_4362570687790572879[51] = 0;
   out_4362570687790572879[52] = 0;
   out_4362570687790572879[53] = 0;
   out_4362570687790572879[54] = 0;
   out_4362570687790572879[55] = 0;
   out_4362570687790572879[56] = 0;
   out_4362570687790572879[57] = 1;
   out_4362570687790572879[58] = 0;
   out_4362570687790572879[59] = 0;
   out_4362570687790572879[60] = 0;
   out_4362570687790572879[61] = 0;
   out_4362570687790572879[62] = 0;
   out_4362570687790572879[63] = 0;
   out_4362570687790572879[64] = 0;
   out_4362570687790572879[65] = 0;
   out_4362570687790572879[66] = dt;
   out_4362570687790572879[67] = 0;
   out_4362570687790572879[68] = 0;
   out_4362570687790572879[69] = 0;
   out_4362570687790572879[70] = 0;
   out_4362570687790572879[71] = 0;
   out_4362570687790572879[72] = 0;
   out_4362570687790572879[73] = 0;
   out_4362570687790572879[74] = 0;
   out_4362570687790572879[75] = 0;
   out_4362570687790572879[76] = 1;
   out_4362570687790572879[77] = 0;
   out_4362570687790572879[78] = 0;
   out_4362570687790572879[79] = 0;
   out_4362570687790572879[80] = 0;
   out_4362570687790572879[81] = 0;
   out_4362570687790572879[82] = 0;
   out_4362570687790572879[83] = 0;
   out_4362570687790572879[84] = 0;
   out_4362570687790572879[85] = dt;
   out_4362570687790572879[86] = 0;
   out_4362570687790572879[87] = 0;
   out_4362570687790572879[88] = 0;
   out_4362570687790572879[89] = 0;
   out_4362570687790572879[90] = 0;
   out_4362570687790572879[91] = 0;
   out_4362570687790572879[92] = 0;
   out_4362570687790572879[93] = 0;
   out_4362570687790572879[94] = 0;
   out_4362570687790572879[95] = 1;
   out_4362570687790572879[96] = 0;
   out_4362570687790572879[97] = 0;
   out_4362570687790572879[98] = 0;
   out_4362570687790572879[99] = 0;
   out_4362570687790572879[100] = 0;
   out_4362570687790572879[101] = 0;
   out_4362570687790572879[102] = 0;
   out_4362570687790572879[103] = 0;
   out_4362570687790572879[104] = dt;
   out_4362570687790572879[105] = 0;
   out_4362570687790572879[106] = 0;
   out_4362570687790572879[107] = 0;
   out_4362570687790572879[108] = 0;
   out_4362570687790572879[109] = 0;
   out_4362570687790572879[110] = 0;
   out_4362570687790572879[111] = 0;
   out_4362570687790572879[112] = 0;
   out_4362570687790572879[113] = 0;
   out_4362570687790572879[114] = 1;
   out_4362570687790572879[115] = 0;
   out_4362570687790572879[116] = 0;
   out_4362570687790572879[117] = 0;
   out_4362570687790572879[118] = 0;
   out_4362570687790572879[119] = 0;
   out_4362570687790572879[120] = 0;
   out_4362570687790572879[121] = 0;
   out_4362570687790572879[122] = 0;
   out_4362570687790572879[123] = 0;
   out_4362570687790572879[124] = 0;
   out_4362570687790572879[125] = 0;
   out_4362570687790572879[126] = 0;
   out_4362570687790572879[127] = 0;
   out_4362570687790572879[128] = 0;
   out_4362570687790572879[129] = 0;
   out_4362570687790572879[130] = 0;
   out_4362570687790572879[131] = 0;
   out_4362570687790572879[132] = 0;
   out_4362570687790572879[133] = 1;
   out_4362570687790572879[134] = 0;
   out_4362570687790572879[135] = 0;
   out_4362570687790572879[136] = 0;
   out_4362570687790572879[137] = 0;
   out_4362570687790572879[138] = 0;
   out_4362570687790572879[139] = 0;
   out_4362570687790572879[140] = 0;
   out_4362570687790572879[141] = 0;
   out_4362570687790572879[142] = 0;
   out_4362570687790572879[143] = 0;
   out_4362570687790572879[144] = 0;
   out_4362570687790572879[145] = 0;
   out_4362570687790572879[146] = 0;
   out_4362570687790572879[147] = 0;
   out_4362570687790572879[148] = 0;
   out_4362570687790572879[149] = 0;
   out_4362570687790572879[150] = 0;
   out_4362570687790572879[151] = 0;
   out_4362570687790572879[152] = 1;
   out_4362570687790572879[153] = 0;
   out_4362570687790572879[154] = 0;
   out_4362570687790572879[155] = 0;
   out_4362570687790572879[156] = 0;
   out_4362570687790572879[157] = 0;
   out_4362570687790572879[158] = 0;
   out_4362570687790572879[159] = 0;
   out_4362570687790572879[160] = 0;
   out_4362570687790572879[161] = 0;
   out_4362570687790572879[162] = 0;
   out_4362570687790572879[163] = 0;
   out_4362570687790572879[164] = 0;
   out_4362570687790572879[165] = 0;
   out_4362570687790572879[166] = 0;
   out_4362570687790572879[167] = 0;
   out_4362570687790572879[168] = 0;
   out_4362570687790572879[169] = 0;
   out_4362570687790572879[170] = 0;
   out_4362570687790572879[171] = 1;
   out_4362570687790572879[172] = 0;
   out_4362570687790572879[173] = 0;
   out_4362570687790572879[174] = 0;
   out_4362570687790572879[175] = 0;
   out_4362570687790572879[176] = 0;
   out_4362570687790572879[177] = 0;
   out_4362570687790572879[178] = 0;
   out_4362570687790572879[179] = 0;
   out_4362570687790572879[180] = 0;
   out_4362570687790572879[181] = 0;
   out_4362570687790572879[182] = 0;
   out_4362570687790572879[183] = 0;
   out_4362570687790572879[184] = 0;
   out_4362570687790572879[185] = 0;
   out_4362570687790572879[186] = 0;
   out_4362570687790572879[187] = 0;
   out_4362570687790572879[188] = 0;
   out_4362570687790572879[189] = 0;
   out_4362570687790572879[190] = 1;
   out_4362570687790572879[191] = 0;
   out_4362570687790572879[192] = 0;
   out_4362570687790572879[193] = 0;
   out_4362570687790572879[194] = 0;
   out_4362570687790572879[195] = 0;
   out_4362570687790572879[196] = 0;
   out_4362570687790572879[197] = 0;
   out_4362570687790572879[198] = 0;
   out_4362570687790572879[199] = 0;
   out_4362570687790572879[200] = 0;
   out_4362570687790572879[201] = 0;
   out_4362570687790572879[202] = 0;
   out_4362570687790572879[203] = 0;
   out_4362570687790572879[204] = 0;
   out_4362570687790572879[205] = 0;
   out_4362570687790572879[206] = 0;
   out_4362570687790572879[207] = 0;
   out_4362570687790572879[208] = 0;
   out_4362570687790572879[209] = 1;
   out_4362570687790572879[210] = 0;
   out_4362570687790572879[211] = 0;
   out_4362570687790572879[212] = 0;
   out_4362570687790572879[213] = 0;
   out_4362570687790572879[214] = 0;
   out_4362570687790572879[215] = 0;
   out_4362570687790572879[216] = 0;
   out_4362570687790572879[217] = 0;
   out_4362570687790572879[218] = 0;
   out_4362570687790572879[219] = 0;
   out_4362570687790572879[220] = 0;
   out_4362570687790572879[221] = 0;
   out_4362570687790572879[222] = 0;
   out_4362570687790572879[223] = 0;
   out_4362570687790572879[224] = 0;
   out_4362570687790572879[225] = 0;
   out_4362570687790572879[226] = 0;
   out_4362570687790572879[227] = 0;
   out_4362570687790572879[228] = 1;
   out_4362570687790572879[229] = 0;
   out_4362570687790572879[230] = 0;
   out_4362570687790572879[231] = 0;
   out_4362570687790572879[232] = 0;
   out_4362570687790572879[233] = 0;
   out_4362570687790572879[234] = 0;
   out_4362570687790572879[235] = 0;
   out_4362570687790572879[236] = 0;
   out_4362570687790572879[237] = 0;
   out_4362570687790572879[238] = 0;
   out_4362570687790572879[239] = 0;
   out_4362570687790572879[240] = 0;
   out_4362570687790572879[241] = 0;
   out_4362570687790572879[242] = 0;
   out_4362570687790572879[243] = 0;
   out_4362570687790572879[244] = 0;
   out_4362570687790572879[245] = 0;
   out_4362570687790572879[246] = 0;
   out_4362570687790572879[247] = 1;
   out_4362570687790572879[248] = 0;
   out_4362570687790572879[249] = 0;
   out_4362570687790572879[250] = 0;
   out_4362570687790572879[251] = 0;
   out_4362570687790572879[252] = 0;
   out_4362570687790572879[253] = 0;
   out_4362570687790572879[254] = 0;
   out_4362570687790572879[255] = 0;
   out_4362570687790572879[256] = 0;
   out_4362570687790572879[257] = 0;
   out_4362570687790572879[258] = 0;
   out_4362570687790572879[259] = 0;
   out_4362570687790572879[260] = 0;
   out_4362570687790572879[261] = 0;
   out_4362570687790572879[262] = 0;
   out_4362570687790572879[263] = 0;
   out_4362570687790572879[264] = 0;
   out_4362570687790572879[265] = 0;
   out_4362570687790572879[266] = 1;
   out_4362570687790572879[267] = 0;
   out_4362570687790572879[268] = 0;
   out_4362570687790572879[269] = 0;
   out_4362570687790572879[270] = 0;
   out_4362570687790572879[271] = 0;
   out_4362570687790572879[272] = 0;
   out_4362570687790572879[273] = 0;
   out_4362570687790572879[274] = 0;
   out_4362570687790572879[275] = 0;
   out_4362570687790572879[276] = 0;
   out_4362570687790572879[277] = 0;
   out_4362570687790572879[278] = 0;
   out_4362570687790572879[279] = 0;
   out_4362570687790572879[280] = 0;
   out_4362570687790572879[281] = 0;
   out_4362570687790572879[282] = 0;
   out_4362570687790572879[283] = 0;
   out_4362570687790572879[284] = 0;
   out_4362570687790572879[285] = 1;
   out_4362570687790572879[286] = 0;
   out_4362570687790572879[287] = 0;
   out_4362570687790572879[288] = 0;
   out_4362570687790572879[289] = 0;
   out_4362570687790572879[290] = 0;
   out_4362570687790572879[291] = 0;
   out_4362570687790572879[292] = 0;
   out_4362570687790572879[293] = 0;
   out_4362570687790572879[294] = 0;
   out_4362570687790572879[295] = 0;
   out_4362570687790572879[296] = 0;
   out_4362570687790572879[297] = 0;
   out_4362570687790572879[298] = 0;
   out_4362570687790572879[299] = 0;
   out_4362570687790572879[300] = 0;
   out_4362570687790572879[301] = 0;
   out_4362570687790572879[302] = 0;
   out_4362570687790572879[303] = 0;
   out_4362570687790572879[304] = 1;
   out_4362570687790572879[305] = 0;
   out_4362570687790572879[306] = 0;
   out_4362570687790572879[307] = 0;
   out_4362570687790572879[308] = 0;
   out_4362570687790572879[309] = 0;
   out_4362570687790572879[310] = 0;
   out_4362570687790572879[311] = 0;
   out_4362570687790572879[312] = 0;
   out_4362570687790572879[313] = 0;
   out_4362570687790572879[314] = 0;
   out_4362570687790572879[315] = 0;
   out_4362570687790572879[316] = 0;
   out_4362570687790572879[317] = 0;
   out_4362570687790572879[318] = 0;
   out_4362570687790572879[319] = 0;
   out_4362570687790572879[320] = 0;
   out_4362570687790572879[321] = 0;
   out_4362570687790572879[322] = 0;
   out_4362570687790572879[323] = 1;
}
void h_4(double *state, double *unused, double *out_5306387973489054380) {
   out_5306387973489054380[0] = state[6] + state[9];
   out_5306387973489054380[1] = state[7] + state[10];
   out_5306387973489054380[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_400118005362272241) {
   out_400118005362272241[0] = 0;
   out_400118005362272241[1] = 0;
   out_400118005362272241[2] = 0;
   out_400118005362272241[3] = 0;
   out_400118005362272241[4] = 0;
   out_400118005362272241[5] = 0;
   out_400118005362272241[6] = 1;
   out_400118005362272241[7] = 0;
   out_400118005362272241[8] = 0;
   out_400118005362272241[9] = 1;
   out_400118005362272241[10] = 0;
   out_400118005362272241[11] = 0;
   out_400118005362272241[12] = 0;
   out_400118005362272241[13] = 0;
   out_400118005362272241[14] = 0;
   out_400118005362272241[15] = 0;
   out_400118005362272241[16] = 0;
   out_400118005362272241[17] = 0;
   out_400118005362272241[18] = 0;
   out_400118005362272241[19] = 0;
   out_400118005362272241[20] = 0;
   out_400118005362272241[21] = 0;
   out_400118005362272241[22] = 0;
   out_400118005362272241[23] = 0;
   out_400118005362272241[24] = 0;
   out_400118005362272241[25] = 1;
   out_400118005362272241[26] = 0;
   out_400118005362272241[27] = 0;
   out_400118005362272241[28] = 1;
   out_400118005362272241[29] = 0;
   out_400118005362272241[30] = 0;
   out_400118005362272241[31] = 0;
   out_400118005362272241[32] = 0;
   out_400118005362272241[33] = 0;
   out_400118005362272241[34] = 0;
   out_400118005362272241[35] = 0;
   out_400118005362272241[36] = 0;
   out_400118005362272241[37] = 0;
   out_400118005362272241[38] = 0;
   out_400118005362272241[39] = 0;
   out_400118005362272241[40] = 0;
   out_400118005362272241[41] = 0;
   out_400118005362272241[42] = 0;
   out_400118005362272241[43] = 0;
   out_400118005362272241[44] = 1;
   out_400118005362272241[45] = 0;
   out_400118005362272241[46] = 0;
   out_400118005362272241[47] = 1;
   out_400118005362272241[48] = 0;
   out_400118005362272241[49] = 0;
   out_400118005362272241[50] = 0;
   out_400118005362272241[51] = 0;
   out_400118005362272241[52] = 0;
   out_400118005362272241[53] = 0;
}
void h_10(double *state, double *unused, double *out_1644909465278790549) {
   out_1644909465278790549[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1644909465278790549[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1644909465278790549[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5642347525539270318) {
   out_5642347525539270318[0] = 0;
   out_5642347525539270318[1] = 9.8100000000000005*cos(state[1]);
   out_5642347525539270318[2] = 0;
   out_5642347525539270318[3] = 0;
   out_5642347525539270318[4] = -state[8];
   out_5642347525539270318[5] = state[7];
   out_5642347525539270318[6] = 0;
   out_5642347525539270318[7] = state[5];
   out_5642347525539270318[8] = -state[4];
   out_5642347525539270318[9] = 0;
   out_5642347525539270318[10] = 0;
   out_5642347525539270318[11] = 0;
   out_5642347525539270318[12] = 1;
   out_5642347525539270318[13] = 0;
   out_5642347525539270318[14] = 0;
   out_5642347525539270318[15] = 1;
   out_5642347525539270318[16] = 0;
   out_5642347525539270318[17] = 0;
   out_5642347525539270318[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5642347525539270318[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5642347525539270318[20] = 0;
   out_5642347525539270318[21] = state[8];
   out_5642347525539270318[22] = 0;
   out_5642347525539270318[23] = -state[6];
   out_5642347525539270318[24] = -state[5];
   out_5642347525539270318[25] = 0;
   out_5642347525539270318[26] = state[3];
   out_5642347525539270318[27] = 0;
   out_5642347525539270318[28] = 0;
   out_5642347525539270318[29] = 0;
   out_5642347525539270318[30] = 0;
   out_5642347525539270318[31] = 1;
   out_5642347525539270318[32] = 0;
   out_5642347525539270318[33] = 0;
   out_5642347525539270318[34] = 1;
   out_5642347525539270318[35] = 0;
   out_5642347525539270318[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5642347525539270318[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5642347525539270318[38] = 0;
   out_5642347525539270318[39] = -state[7];
   out_5642347525539270318[40] = state[6];
   out_5642347525539270318[41] = 0;
   out_5642347525539270318[42] = state[4];
   out_5642347525539270318[43] = -state[3];
   out_5642347525539270318[44] = 0;
   out_5642347525539270318[45] = 0;
   out_5642347525539270318[46] = 0;
   out_5642347525539270318[47] = 0;
   out_5642347525539270318[48] = 0;
   out_5642347525539270318[49] = 0;
   out_5642347525539270318[50] = 1;
   out_5642347525539270318[51] = 0;
   out_5642347525539270318[52] = 0;
   out_5642347525539270318[53] = 1;
}
void h_13(double *state, double *unused, double *out_3857481709679275462) {
   out_3857481709679275462[0] = state[3];
   out_3857481709679275462[1] = state[4];
   out_3857481709679275462[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3433637457940251783) {
   out_3433637457940251783[0] = 0;
   out_3433637457940251783[1] = 0;
   out_3433637457940251783[2] = 0;
   out_3433637457940251783[3] = 1;
   out_3433637457940251783[4] = 0;
   out_3433637457940251783[5] = 0;
   out_3433637457940251783[6] = 0;
   out_3433637457940251783[7] = 0;
   out_3433637457940251783[8] = 0;
   out_3433637457940251783[9] = 0;
   out_3433637457940251783[10] = 0;
   out_3433637457940251783[11] = 0;
   out_3433637457940251783[12] = 0;
   out_3433637457940251783[13] = 0;
   out_3433637457940251783[14] = 0;
   out_3433637457940251783[15] = 0;
   out_3433637457940251783[16] = 0;
   out_3433637457940251783[17] = 0;
   out_3433637457940251783[18] = 0;
   out_3433637457940251783[19] = 0;
   out_3433637457940251783[20] = 0;
   out_3433637457940251783[21] = 0;
   out_3433637457940251783[22] = 1;
   out_3433637457940251783[23] = 0;
   out_3433637457940251783[24] = 0;
   out_3433637457940251783[25] = 0;
   out_3433637457940251783[26] = 0;
   out_3433637457940251783[27] = 0;
   out_3433637457940251783[28] = 0;
   out_3433637457940251783[29] = 0;
   out_3433637457940251783[30] = 0;
   out_3433637457940251783[31] = 0;
   out_3433637457940251783[32] = 0;
   out_3433637457940251783[33] = 0;
   out_3433637457940251783[34] = 0;
   out_3433637457940251783[35] = 0;
   out_3433637457940251783[36] = 0;
   out_3433637457940251783[37] = 0;
   out_3433637457940251783[38] = 0;
   out_3433637457940251783[39] = 0;
   out_3433637457940251783[40] = 0;
   out_3433637457940251783[41] = 1;
   out_3433637457940251783[42] = 0;
   out_3433637457940251783[43] = 0;
   out_3433637457940251783[44] = 0;
   out_3433637457940251783[45] = 0;
   out_3433637457940251783[46] = 0;
   out_3433637457940251783[47] = 0;
   out_3433637457940251783[48] = 0;
   out_3433637457940251783[49] = 0;
   out_3433637457940251783[50] = 0;
   out_3433637457940251783[51] = 0;
   out_3433637457940251783[52] = 0;
   out_3433637457940251783[53] = 0;
}
void h_14(double *state, double *unused, double *out_3523901321347933816) {
   out_3523901321347933816[0] = state[6];
   out_3523901321347933816[1] = state[7];
   out_3523901321347933816[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2682670426933100055) {
   out_2682670426933100055[0] = 0;
   out_2682670426933100055[1] = 0;
   out_2682670426933100055[2] = 0;
   out_2682670426933100055[3] = 0;
   out_2682670426933100055[4] = 0;
   out_2682670426933100055[5] = 0;
   out_2682670426933100055[6] = 1;
   out_2682670426933100055[7] = 0;
   out_2682670426933100055[8] = 0;
   out_2682670426933100055[9] = 0;
   out_2682670426933100055[10] = 0;
   out_2682670426933100055[11] = 0;
   out_2682670426933100055[12] = 0;
   out_2682670426933100055[13] = 0;
   out_2682670426933100055[14] = 0;
   out_2682670426933100055[15] = 0;
   out_2682670426933100055[16] = 0;
   out_2682670426933100055[17] = 0;
   out_2682670426933100055[18] = 0;
   out_2682670426933100055[19] = 0;
   out_2682670426933100055[20] = 0;
   out_2682670426933100055[21] = 0;
   out_2682670426933100055[22] = 0;
   out_2682670426933100055[23] = 0;
   out_2682670426933100055[24] = 0;
   out_2682670426933100055[25] = 1;
   out_2682670426933100055[26] = 0;
   out_2682670426933100055[27] = 0;
   out_2682670426933100055[28] = 0;
   out_2682670426933100055[29] = 0;
   out_2682670426933100055[30] = 0;
   out_2682670426933100055[31] = 0;
   out_2682670426933100055[32] = 0;
   out_2682670426933100055[33] = 0;
   out_2682670426933100055[34] = 0;
   out_2682670426933100055[35] = 0;
   out_2682670426933100055[36] = 0;
   out_2682670426933100055[37] = 0;
   out_2682670426933100055[38] = 0;
   out_2682670426933100055[39] = 0;
   out_2682670426933100055[40] = 0;
   out_2682670426933100055[41] = 0;
   out_2682670426933100055[42] = 0;
   out_2682670426933100055[43] = 0;
   out_2682670426933100055[44] = 1;
   out_2682670426933100055[45] = 0;
   out_2682670426933100055[46] = 0;
   out_2682670426933100055[47] = 0;
   out_2682670426933100055[48] = 0;
   out_2682670426933100055[49] = 0;
   out_2682670426933100055[50] = 0;
   out_2682670426933100055[51] = 0;
   out_2682670426933100055[52] = 0;
   out_2682670426933100055[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_3215194707115345059) {
  err_fun(nom_x, delta_x, out_3215194707115345059);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9204099396150886653) {
  inv_err_fun(nom_x, true_x, out_9204099396150886653);
}
void pose_H_mod_fun(double *state, double *out_9102264402289458033) {
  H_mod_fun(state, out_9102264402289458033);
}
void pose_f_fun(double *state, double dt, double *out_7197250978786250178) {
  f_fun(state,  dt, out_7197250978786250178);
}
void pose_F_fun(double *state, double dt, double *out_4362570687790572879) {
  F_fun(state,  dt, out_4362570687790572879);
}
void pose_h_4(double *state, double *unused, double *out_5306387973489054380) {
  h_4(state, unused, out_5306387973489054380);
}
void pose_H_4(double *state, double *unused, double *out_400118005362272241) {
  H_4(state, unused, out_400118005362272241);
}
void pose_h_10(double *state, double *unused, double *out_1644909465278790549) {
  h_10(state, unused, out_1644909465278790549);
}
void pose_H_10(double *state, double *unused, double *out_5642347525539270318) {
  H_10(state, unused, out_5642347525539270318);
}
void pose_h_13(double *state, double *unused, double *out_3857481709679275462) {
  h_13(state, unused, out_3857481709679275462);
}
void pose_H_13(double *state, double *unused, double *out_3433637457940251783) {
  H_13(state, unused, out_3433637457940251783);
}
void pose_h_14(double *state, double *unused, double *out_3523901321347933816) {
  h_14(state, unused, out_3523901321347933816);
}
void pose_H_14(double *state, double *unused, double *out_2682670426933100055) {
  H_14(state, unused, out_2682670426933100055);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
