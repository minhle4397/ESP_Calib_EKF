#pragma once

#include "esp_err.h"
#include "stdint.h"

//raw data
typedef struct
{
    int16_t ax, ay, az; //accelerometer qui đổi dữ liệu thô sang giá trị vât lí 8192LSB/g range 4g
    int16_t gx, gy, gz; //gyroscope qui đổi dữ liệu thô sang giá trị vât lí 65.5LSB/°/s range 500°/s
} imu_raw_t;

esp_err_t mpu6050_init(void);
esp_err_t mpu6050_read_raw(imu_raw_t *out);
