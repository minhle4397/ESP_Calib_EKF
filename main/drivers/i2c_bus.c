#include "i2c_bus.h"
#include "esp_log.h"

#define I2C0_SDA_GPIO 21 //MPU6050
#define I2C0_SCL_GPIO 22
#define I2C1_SDA_GPIO 18 //HMC5883L
#define I2C1_SCL_GPIO 19

static const char *TAG = "i2c_bus";

i2c_master_bus_handle_t i2c_bus0 = NULL;
i2c_master_bus_handle_t i2c_bus1 = NULL;

esp_err_t i2c_bus_init(void){
    i2c_master_bus_config_t bus0_cfg = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C0_SDA_GPIO,
        .scl_io_num = I2C0_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    esp_err_t err = i2c_new_master_bus(&bus0_cfg, &i2c_bus0);
    if(err != ESP_OK){
        ESP_LOGE(TAG, "Failed to init bus0 (MPU6050): %s", esp_err_to_name(err));
        return err;
    }
    i2c_master_bus_config_t bus1_cfg = {
        .i2c_port = I2C_NUM_1,
        .sda_io_num = I2C1_SDA_GPIO,
        .scl_io_num = I2C1_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    }
    err = i2c_new_master_bus(&bus1_cfg, &i2c_bus1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init bus1 (HMC5883L): %s", esp_err_to_name(err));
        return err;
    }
 
    ESP_LOGI(TAG, "bus0 (MPU6050) on GPIO%d/%d, bus1 (HMC5883L) on GPIO%d/%d ready",
             I2C0_SDA_GPIO, I2C0_SCL_GPIO, I2C1_SDA_GPIO, I2C1_SCL_GPIO);
    return ESP_OK;

}
