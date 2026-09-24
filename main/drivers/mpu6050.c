#include "mpu6050.h"
#include "i2c_bus.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#define MPU6050_ADDR 0x68 //AD0 = GND 

#define REG_PWR_MGMT_1      0x6B //Power management 1
#define REG_SMPLRT_DIV      0x19 //Sample rate divider
#define REG_CONFIG          0x1A //Digital low-pass filter
#define REG_GYRO_CONFIG     0x1B //Gyro configuration
#define REG_ACCEL_CONFIG    0x1C //Accelerometer configuration
#define REG_ACCEL_XOUT_H    0x3B //Accelerometer X-axis high byte

static const char *TAG = "mpu6050";
static i2c_master_dev_handle_t dev =  NULL;

esp_err_t mpu6050_init(void){
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .dev_addr = MPU6050_ADDR,
        .scl_speed_hz = 400000,
    };
    esp_error_t err = i2c_master_bus_add_device(i2c_bus0, &dev_cfg, &dev);
    if(err != ESP_OK) return err;

    //Thoát chế độ sleep, chọn gyro X lam clock source (ổn định hơn internal RC)
    ESP_ERROR_CHECK(write_reg(REG_PWR_MGMT_1, 0x01));
    //Sample rate = 1kHz /(1+9)= 100Hz
    ESP_ERROR_CHECK(write_reg(REG_SMPLRT_DIV, 0x09));
    //Digital low-pass filter ~44Hz (Giảm nhiễu rung tần số cao)
    ESP_ERROR_CHECK(write_reg(RED_CONFIG, 0x03));
    //Gyro full scale  = ±500°/s
    ESP_ERROR_CHECK(write_reg(REG_GYRO_CONFIG, 0x08));
    //Accel full scale = ±4g
    ESP_ERROR_CHECK(write_reg(REG_ACCEL_CONFIG, 0x08));

    ESP_LOGI(TAG, "MPU6050 ready on bus0, addr 0x%02X", MPU6050_ADDR);
    return ESP_OK;
}
esp_err_t mpu6050_read_raw(imu_raw_t *out){
   uint8_t reg = REG_ACCEL_XOUT_H;
   uint8_t buf[14]; //accel(6) + temp(2) + gyro(6)  
   esp_err_t err = i2c_master_transmit_receive(dev, &reg, 1, buf, sizeof(buf), 100);
}




