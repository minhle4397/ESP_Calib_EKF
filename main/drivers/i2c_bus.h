#pragma once
#include "driver/i2c_master.h"
//bus0 -> MPU6050 (GPIO21/22)
//bus1 -> HMC5883L (GPIO18/19)
extern i2c_master_bus_handle_t i2c_bus0;
extern i2c_master_bus_handle_t i2c_bus1;

esp_err_t i2c_bus_init(void); //trả về ESP_OK nếu khởi tạo thành công, ngược lại trả về mã lỗi