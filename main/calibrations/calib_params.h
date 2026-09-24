#pragma once
#include "calib_types.h" 

//File này để tune sau khi có giá trị output được tính từ việc chạy tool python

//Model: accel_calibrated[i] = (accel_raw[i] - ACCEL_BIAS[i])*ACCEL_SCALE[i]
static const vec3_f ACCEL_BIAS = {0.0f, 0.0f, 0.0f}; //đơn vị g
static const vec3_f ACCEL_SCALE = {1.0f, 1.0f, 1.0f}; //đơn vị g

//Model: mag_calibrated[i] = (mag_raw[i] - MAG_BIAS[i]*MAG_SCALE[i])
static const vec3_f MAG_BIAS = {0.0f, 0.0f, 0.0f}; //đơn vị Gauss
static const vec3_f MAG_SCALE = {1.0f, 1.0f, 1.0f}; //đơn vị Gauss