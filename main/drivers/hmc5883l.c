#include "hmc5883l.h"
#include "i2c_bus.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#define HMC5883L_ADDR 0x1E //A0 = GND, A1 = GND, A2 = GND

#define REG_CONFIG_A 0x00
#define REG_CONFIG_B 0x01
#define REG_MODE     0x02
#define REG_DATA_X_MSB 0x03

static const char *TAG = "hmc5883l";
static i2c_master_dev_handle_t dev = NULL;

static esp_err_t write_reg(uint8_t reg, uint8_t val) {
    uint8_t buf[2] = {reg, val};
    return i2c_master_transmit(dev, buf, sizeof(buf), 100);
}

esp_err_t hmc5883l_init(void){
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = HMC5883L_ADDR,
        .scl_speed_hz = 400000,
    };
    esp_err_t err = i2c_master_bus_add_device(i2c_bus1, &dev_cfg, &dev);
    if(err != ESP_OK) return err;

    //8-sample average, 15Hz output rate, normal measurement mode
    ESP_ERROR_CHECK(write_reg(REG_CONFIG_A, 0x70));
    //Gain = 1090 LSB/Gauss
    ESP_ERROR_CHECK(write_reg(REG_CONFIG_B, 0x20));
    //Continous measurement mode
    ESP_ERROR_CHECK(write_reg(REG_MODE, 0x00));

    ESP_LOG(TAG, "HMC5883L ready on bus1, addr 0x%02X", HMC5883L_ADDR);
    return ESP_OK;
}

esp_err_t hmc5883l_read_raw(mag_raw_t *out){
    uint8_t reg = REG_DATA_X_MSB;
    uint8_t buf[6]; //X(2) + Z(2) + Y(2)
    esp_err_t err = i2c_master_transmit_receive(dev, &reg, 1, buf, sizeof(buf), 100);
    if(err != ESP_OK) return err;
    //Thứ tự thanh ghi của HMC là X, Z, Y
    out->mx = (int16_t)((buf[0] << 8) | buf[1]);
    out->mz = (int16_t)((buf[2] << 8) | buf[3]);
    out->my = (int16_t)((buf[4] << 8) | buf[5]);
    return ESP_OK;
}

