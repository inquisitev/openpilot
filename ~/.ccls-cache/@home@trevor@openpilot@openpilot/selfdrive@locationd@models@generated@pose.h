#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3215194707115345059);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9204099396150886653);
void pose_H_mod_fun(double *state, double *out_9102264402289458033);
void pose_f_fun(double *state, double dt, double *out_7197250978786250178);
void pose_F_fun(double *state, double dt, double *out_4362570687790572879);
void pose_h_4(double *state, double *unused, double *out_5306387973489054380);
void pose_H_4(double *state, double *unused, double *out_400118005362272241);
void pose_h_10(double *state, double *unused, double *out_1644909465278790549);
void pose_H_10(double *state, double *unused, double *out_5642347525539270318);
void pose_h_13(double *state, double *unused, double *out_3857481709679275462);
void pose_H_13(double *state, double *unused, double *out_3433637457940251783);
void pose_h_14(double *state, double *unused, double *out_3523901321347933816);
void pose_H_14(double *state, double *unused, double *out_2682670426933100055);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}