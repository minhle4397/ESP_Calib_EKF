#pragma once

#include "esp_err.h"
#include "stdint.h"

// Dữ liệu thô, chưa calib (chưa trữ hard-iron, chưa nhận soft-iron)

typedef struct
{
    int16_t mx, my, mz; //magnetometer qui đổi dữ liệu thô sang giá trị vât lí 1090LSB/Gauss range 1.3Gauss
} mag_raw_t;

esp_err_t hmc5883l_init(void);
esp_err_t hmc5883l_read_raw(mag_raw_t *out);