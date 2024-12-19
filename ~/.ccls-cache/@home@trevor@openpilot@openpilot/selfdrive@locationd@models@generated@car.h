#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_42078160199344570);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_334059058333874913);
void car_H_mod_fun(double *state, double *out_8912300271056785572);
void car_f_fun(double *state, double dt, double *out_8055160154345736891);
void car_F_fun(double *state, double dt, double *out_1213249844648869015);
void car_h_25(double *state, double *unused, double *out_8780181214935844004);
void car_H_25(double *state, double *unused, double *out_4117469428128916463);
void car_h_24(double *state, double *unused, double *out_2468352857406425660);
void car_H_24(double *state, double *unused, double *out_1944819829123416897);
void car_h_30(double *state, double *unused, double *out_5142731686681821654);
void car_H_30(double *state, double *unused, double *out_6635802386636165090);
void car_h_26(double *state, double *unused, double *out_4199221833780159219);
void car_H_26(double *state, double *unused, double *out_7421995397889717064);
void car_h_27(double *state, double *unused, double *out_6629776807329374927);
void car_H_27(double *state, double *unused, double *out_4461039074835740179);
void car_h_29(double *state, double *unused, double *out_6904970869613880816);
void car_H_29(double *state, double *unused, double *out_7146033730950557274);
void car_h_28(double *state, double *unused, double *out_2796423853939700247);
void car_H_28(double *state, double *unused, double *out_2063634713881026700);
void car_h_31(double *state, double *unused, double *out_9055375277220349893);
void car_H_31(double *state, double *unused, double *out_6795787295656365588);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}