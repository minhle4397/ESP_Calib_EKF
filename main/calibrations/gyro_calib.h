#pragma once
#include "calib_types.h"
#include "esp_err.h"

//Chạy khi cảm biến nằm yên tuyệt đối, lấy num_sample mẫu để tính bias
//Nên gọi 1 lần trong app_main() trước khi vào while(1)
esp_err_t gyro_calib_run(int num_samples);

//Lấy bias đã tinh (mặc định {0,0,0} nếu chưa chạy gyro_calib_run())
vec3_f gyro_calib_get_bias(void);