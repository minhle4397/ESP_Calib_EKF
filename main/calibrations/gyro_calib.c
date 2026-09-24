#include "gyro_calib.h"
#include "mpu6050.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "gyro_calib";
static vec3_f gyro_bias = {0.0f, 0.0f, 0.0f}; //đơn vị °/s

esp_err_t gyro_calib_run(int num_samples){
    ESP_LOGI(TAG, "Bắt đầu calib gyro (%d mau) - GIỮ CẢM BIẾN NẰM YÊN TUYỆT ĐỐI...", num_samples);

    double sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;
    imu_raw_t sample;
    int ok_count = 0;
    for(int i=0; i<num_samples; i++){
        if(mpu6050_read_raw(&sample) == ESP_OK){
            sum_x += sample.gx;
            sum_y += sample.gy;
            sum_z += sample.gz;
            ok_count++;
        }
        vTaskDelay(pdMS_TO_TICKS(5)); //delay 5ms để lấy mẫu ~200Hz
    }
    if(ok_count == 0){
        ESP_LOGE(TAG, "Không lấy được mẫu nào từ MPU6050");
        return ESP_FAIL;
    }
    bias.x = (float)(sum_x / ok_count);
    bias.y = (float)(sum_y / ok_count);
    bias.z = (float)(sum_z / ok_count);

    ESP_LOGI(TAG, "Calib gyro x=%.2f, y=%.2f, z=%.2f (đơn vị raw)", bias.x, bias.y, bias.z);
    return ESP_OK;
}

vec3_f gyro_calib_get_bias(void){
    return bias;
}