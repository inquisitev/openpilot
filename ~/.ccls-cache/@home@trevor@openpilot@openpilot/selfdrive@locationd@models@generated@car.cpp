#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.13.3                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_42078160199344570) {
   out_42078160199344570[0] = delta_x[0] + nom_x[0];
   out_42078160199344570[1] = delta_x[1] + nom_x[1];
   out_42078160199344570[2] = delta_x[2] + nom_x[2];
   out_42078160199344570[3] = delta_x[3] + nom_x[3];
   out_42078160199344570[4] = delta_x[4] + nom_x[4];
   out_42078160199344570[5] = delta_x[5] + nom_x[5];
   out_42078160199344570[6] = delta_x[6] + nom_x[6];
   out_42078160199344570[7] = delta_x[7] + nom_x[7];
   out_42078160199344570[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_334059058333874913) {
   out_334059058333874913[0] = -nom_x[0] + true_x[0];
   out_334059058333874913[1] = -nom_x[1] + true_x[1];
   out_334059058333874913[2] = -nom_x[2] + true_x[2];
   out_334059058333874913[3] = -nom_x[3] + true_x[3];
   out_334059058333874913[4] = -nom_x[4] + true_x[4];
   out_334059058333874913[5] = -nom_x[5] + true_x[5];
   out_334059058333874913[6] = -nom_x[6] + true_x[6];
   out_334059058333874913[7] = -nom_x[7] + true_x[7];
   out_334059058333874913[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8912300271056785572) {
   out_8912300271056785572[0] = 1.0;
   out_8912300271056785572[1] = 0.0;
   out_8912300271056785572[2] = 0.0;
   out_8912300271056785572[3] = 0.0;
   out_8912300271056785572[4] = 0.0;
   out_8912300271056785572[5] = 0.0;
   out_8912300271056785572[6] = 0.0;
   out_8912300271056785572[7] = 0.0;
   out_8912300271056785572[8] = 0.0;
   out_8912300271056785572[9] = 0.0;
   out_8912300271056785572[10] = 1.0;
   out_8912300271056785572[11] = 0.0;
   out_8912300271056785572[12] = 0.0;
   out_8912300271056785572[13] = 0.0;
   out_8912300271056785572[14] = 0.0;
   out_8912300271056785572[15] = 0.0;
   out_8912300271056785572[16] = 0.0;
   out_8912300271056785572[17] = 0.0;
   out_8912300271056785572[18] = 0.0;
   out_8912300271056785572[19] = 0.0;
   out_8912300271056785572[20] = 1.0;
   out_8912300271056785572[21] = 0.0;
   out_8912300271056785572[22] = 0.0;
   out_8912300271056785572[23] = 0.0;
   out_8912300271056785572[24] = 0.0;
   out_8912300271056785572[25] = 0.0;
   out_8912300271056785572[26] = 0.0;
   out_8912300271056785572[27] = 0.0;
   out_8912300271056785572[28] = 0.0;
   out_8912300271056785572[29] = 0.0;
   out_8912300271056785572[30] = 1.0;
   out_8912300271056785572[31] = 0.0;
   out_8912300271056785572[32] = 0.0;
   out_8912300271056785572[33] = 0.0;
   out_8912300271056785572[34] = 0.0;
   out_8912300271056785572[35] = 0.0;
   out_8912300271056785572[36] = 0.0;
   out_8912300271056785572[37] = 0.0;
   out_8912300271056785572[38] = 0.0;
   out_8912300271056785572[39] = 0.0;
   out_8912300271056785572[40] = 1.0;
   out_8912300271056785572[41] = 0.0;
   out_8912300271056785572[42] = 0.0;
   out_8912300271056785572[43] = 0.0;
   out_8912300271056785572[44] = 0.0;
   out_8912300271056785572[45] = 0.0;
   out_8912300271056785572[46] = 0.0;
   out_8912300271056785572[47] = 0.0;
   out_8912300271056785572[48] = 0.0;
   out_8912300271056785572[49] = 0.0;
   out_8912300271056785572[50] = 1.0;
   out_8912300271056785572[51] = 0.0;
   out_8912300271056785572[52] = 0.0;
   out_8912300271056785572[53] = 0.0;
   out_8912300271056785572[54] = 0.0;
   out_8912300271056785572[55] = 0.0;
   out_8912300271056785572[56] = 0.0;
   out_8912300271056785572[57] = 0.0;
   out_8912300271056785572[58] = 0.0;
   out_8912300271056785572[59] = 0.0;
   out_8912300271056785572[60] = 1.0;
   out_8912300271056785572[61] = 0.0;
   out_8912300271056785572[62] = 0.0;
   out_8912300271056785572[63] = 0.0;
   out_8912300271056785572[64] = 0.0;
   out_8912300271056785572[65] = 0.0;
   out_8912300271056785572[66] = 0.0;
   out_8912300271056785572[67] = 0.0;
   out_8912300271056785572[68] = 0.0;
   out_8912300271056785572[69] = 0.0;
   out_8912300271056785572[70] = 1.0;
   out_8912300271056785572[71] = 0.0;
   out_8912300271056785572[72] = 0.0;
   out_8912300271056785572[73] = 0.0;
   out_8912300271056785572[74] = 0.0;
   out_8912300271056785572[75] = 0.0;
   out_8912300271056785572[76] = 0.0;
   out_8912300271056785572[77] = 0.0;
   out_8912300271056785572[78] = 0.0;
   out_8912300271056785572[79] = 0.0;
   out_8912300271056785572[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8055160154345736891) {
   out_8055160154345736891[0] = state[0];
   out_8055160154345736891[1] = state[1];
   out_8055160154345736891[2] = state[2];
   out_8055160154345736891[3] = state[3];
   out_8055160154345736891[4] = state[4];
   out_8055160154345736891[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8055160154345736891[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8055160154345736891[7] = state[7];
   out_8055160154345736891[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1213249844648869015) {
   out_1213249844648869015[0] = 1;
   out_1213249844648869015[1] = 0;
   out_1213249844648869015[2] = 0;
   out_1213249844648869015[3] = 0;
   out_1213249844648869015[4] = 0;
   out_1213249844648869015[5] = 0;
   out_1213249844648869015[6] = 0;
   out_1213249844648869015[7] = 0;
   out_1213249844648869015[8] = 0;
   out_1213249844648869015[9] = 0;
   out_1213249844648869015[10] = 1;
   out_1213249844648869015[11] = 0;
   out_1213249844648869015[12] = 0;
   out_1213249844648869015[13] = 0;
   out_1213249844648869015[14] = 0;
   out_1213249844648869015[15] = 0;
   out_1213249844648869015[16] = 0;
   out_1213249844648869015[17] = 0;
   out_1213249844648869015[18] = 0;
   out_1213249844648869015[19] = 0;
   out_1213249844648869015[20] = 1;
   out_1213249844648869015[21] = 0;
   out_1213249844648869015[22] = 0;
   out_1213249844648869015[23] = 0;
   out_1213249844648869015[24] = 0;
   out_1213249844648869015[25] = 0;
   out_1213249844648869015[26] = 0;
   out_1213249844648869015[27] = 0;
   out_1213249844648869015[28] = 0;
   out_1213249844648869015[29] = 0;
   out_1213249844648869015[30] = 1;
   out_1213249844648869015[31] = 0;
   out_1213249844648869015[32] = 0;
   out_1213249844648869015[33] = 0;
   out_1213249844648869015[34] = 0;
   out_1213249844648869015[35] = 0;
   out_1213249844648869015[36] = 0;
   out_1213249844648869015[37] = 0;
   out_1213249844648869015[38] = 0;
   out_1213249844648869015[39] = 0;
   out_1213249844648869015[40] = 1;
   out_1213249844648869015[41] = 0;
   out_1213249844648869015[42] = 0;
   out_1213249844648869015[43] = 0;
   out_1213249844648869015[44] = 0;
   out_1213249844648869015[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1213249844648869015[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1213249844648869015[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1213249844648869015[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1213249844648869015[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1213249844648869015[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1213249844648869015[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1213249844648869015[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1213249844648869015[53] = -9.8000000000000007*dt;
   out_1213249844648869015[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1213249844648869015[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1213249844648869015[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1213249844648869015[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1213249844648869015[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1213249844648869015[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1213249844648869015[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1213249844648869015[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1213249844648869015[62] = 0;
   out_1213249844648869015[63] = 0;
   out_1213249844648869015[64] = 0;
   out_1213249844648869015[65] = 0;
   out_1213249844648869015[66] = 0;
   out_1213249844648869015[67] = 0;
   out_1213249844648869015[68] = 0;
   out_1213249844648869015[69] = 0;
   out_1213249844648869015[70] = 1;
   out_1213249844648869015[71] = 0;
   out_1213249844648869015[72] = 0;
   out_1213249844648869015[73] = 0;
   out_1213249844648869015[74] = 0;
   out_1213249844648869015[75] = 0;
   out_1213249844648869015[76] = 0;
   out_1213249844648869015[77] = 0;
   out_1213249844648869015[78] = 0;
   out_1213249844648869015[79] = 0;
   out_1213249844648869015[80] = 1;
}
void h_25(double *state, double *unused, double *out_8780181214935844004) {
   out_8780181214935844004[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4117469428128916463) {
   out_4117469428128916463[0] = 0;
   out_4117469428128916463[1] = 0;
   out_4117469428128916463[2] = 0;
   out_4117469428128916463[3] = 0;
   out_4117469428128916463[4] = 0;
   out_4117469428128916463[5] = 0;
   out_4117469428128916463[6] = 1;
   out_4117469428128916463[7] = 0;
   out_4117469428128916463[8] = 0;
}
void h_24(double *state, double *unused, double *out_2468352857406425660) {
   out_2468352857406425660[0] = state[4];
   out_2468352857406425660[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1944819829123416897) {
   out_1944819829123416897[0] = 0;
   out_1944819829123416897[1] = 0;
   out_1944819829123416897[2] = 0;
   out_1944819829123416897[3] = 0;
   out_1944819829123416897[4] = 1;
   out_1944819829123416897[5] = 0;
   out_1944819829123416897[6] = 0;
   out_1944819829123416897[7] = 0;
   out_1944819829123416897[8] = 0;
   out_1944819829123416897[9] = 0;
   out_1944819829123416897[10] = 0;
   out_1944819829123416897[11] = 0;
   out_1944819829123416897[12] = 0;
   out_1944819829123416897[13] = 0;
   out_1944819829123416897[14] = 1;
   out_1944819829123416897[15] = 0;
   out_1944819829123416897[16] = 0;
   out_1944819829123416897[17] = 0;
}
void h_30(double *state, double *unused, double *out_5142731686681821654) {
   out_5142731686681821654[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6635802386636165090) {
   out_6635802386636165090[0] = 0;
   out_6635802386636165090[1] = 0;
   out_6635802386636165090[2] = 0;
   out_6635802386636165090[3] = 0;
   out_6635802386636165090[4] = 1;
   out_6635802386636165090[5] = 0;
   out_6635802386636165090[6] = 0;
   out_6635802386636165090[7] = 0;
   out_6635802386636165090[8] = 0;
}
void h_26(double *state, double *unused, double *out_4199221833780159219) {
   out_4199221833780159219[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7421995397889717064) {
   out_7421995397889717064[0] = 0;
   out_7421995397889717064[1] = 0;
   out_7421995397889717064[2] = 0;
   out_7421995397889717064[3] = 0;
   out_7421995397889717064[4] = 0;
   out_7421995397889717064[5] = 0;
   out_7421995397889717064[6] = 0;
   out_7421995397889717064[7] = 1;
   out_7421995397889717064[8] = 0;
}
void h_27(double *state, double *unused, double *out_6629776807329374927) {
   out_6629776807329374927[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4461039074835740179) {
   out_4461039074835740179[0] = 0;
   out_4461039074835740179[1] = 0;
   out_4461039074835740179[2] = 0;
   out_4461039074835740179[3] = 1;
   out_4461039074835740179[4] = 0;
   out_4461039074835740179[5] = 0;
   out_4461039074835740179[6] = 0;
   out_4461039074835740179[7] = 0;
   out_4461039074835740179[8] = 0;
}
void h_29(double *state, double *unused, double *out_6904970869613880816) {
   out_6904970869613880816[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7146033730950557274) {
   out_7146033730950557274[0] = 0;
   out_7146033730950557274[1] = 1;
   out_7146033730950557274[2] = 0;
   out_7146033730950557274[3] = 0;
   out_7146033730950557274[4] = 0;
   out_7146033730950557274[5] = 0;
   out_7146033730950557274[6] = 0;
   out_7146033730950557274[7] = 0;
   out_7146033730950557274[8] = 0;
}
void h_28(double *state, double *unused, double *out_2796423853939700247) {
   out_2796423853939700247[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2063634713881026700) {
   out_2063634713881026700[0] = 1;
   out_2063634713881026700[1] = 0;
   out_2063634713881026700[2] = 0;
   out_2063634713881026700[3] = 0;
   out_2063634713881026700[4] = 0;
   out_2063634713881026700[5] = 0;
   out_2063634713881026700[6] = 0;
   out_2063634713881026700[7] = 0;
   out_2063634713881026700[8] = 0;
}
void h_31(double *state, double *unused, double *out_9055375277220349893) {
   out_9055375277220349893[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6795787295656365588) {
   out_6795787295656365588[0] = 0;
   out_6795787295656365588[1] = 0;
   out_6795787295656365588[2] = 0;
   out_6795787295656365588[3] = 0;
   out_6795787295656365588[4] = 0;
   out_6795787295656365588[5] = 0;
   out_6795787295656365588[6] = 0;
   out_6795787295656365588[7] = 0;
   out_6795787295656365588[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_42078160199344570) {
  err_fun(nom_x, delta_x, out_42078160199344570);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_334059058333874913) {
  inv_err_fun(nom_x, true_x, out_334059058333874913);
}
void car_H_mod_fun(double *state, double *out_8912300271056785572) {
  H_mod_fun(state, out_8912300271056785572);
}
void car_f_fun(double *state, double dt, double *out_8055160154345736891) {
  f_fun(state,  dt, out_8055160154345736891);
}
void car_F_fun(double *state, double dt, double *out_1213249844648869015) {
  F_fun(state,  dt, out_1213249844648869015);
}
void car_h_25(double *state, double *unused, double *out_8780181214935844004) {
  h_25(state, unused, out_8780181214935844004);
}
void car_H_25(double *state, double *unused, double *out_4117469428128916463) {
  H_25(state, unused, out_4117469428128916463);
}
void car_h_24(double *state, double *unused, double *out_2468352857406425660) {
  h_24(state, unused, out_2468352857406425660);
}
void car_H_24(double *state, double *unused, double *out_1944819829123416897) {
  H_24(state, unused, out_1944819829123416897);
}
void car_h_30(double *state, double *unused, double *out_5142731686681821654) {
  h_30(state, unused, out_5142731686681821654);
}
void car_H_30(double *state, double *unused, double *out_6635802386636165090) {
  H_30(state, unused, out_6635802386636165090);
}
void car_h_26(double *state, double *unused, double *out_4199221833780159219) {
  h_26(state, unused, out_4199221833780159219);
}
void car_H_26(double *state, double *unused, double *out_7421995397889717064) {
  H_26(state, unused, out_7421995397889717064);
}
void car_h_27(double *state, double *unused, double *out_6629776807329374927) {
  h_27(state, unused, out_6629776807329374927);
}
void car_H_27(double *state, double *unused, double *out_4461039074835740179) {
  H_27(state, unused, out_4461039074835740179);
}
void car_h_29(double *state, double *unused, double *out_6904970869613880816) {
  h_29(state, unused, out_6904970869613880816);
}
void car_H_29(double *state, double *unused, double *out_7146033730950557274) {
  H_29(state, unused, out_7146033730950557274);
}
void car_h_28(double *state, double *unused, double *out_2796423853939700247) {
  h_28(state, unused, out_2796423853939700247);
}
void car_H_28(double *state, double *unused, double *out_2063634713881026700) {
  H_28(state, unused, out_2063634713881026700);
}
void car_h_31(double *state, double *unused, double *out_9055375277220349893) {
  h_31(state, unused, out_9055375277220349893);
}
void car_H_31(double *state, double *unused, double *out_6795787295656365588) {
  H_31(state, unused, out_6795787295656365588);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
