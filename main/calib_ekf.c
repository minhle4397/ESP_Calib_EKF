#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "drivers/i2c_bus.h"
#include "drivers/mpu6050.h"
#include "drivers/hmc5883l.h"
//File này test layer 1. Sau đó modify để test layer 4 
void app_main(void)
{
    ESP_ERROR_CHECK(i2c_bus_init());
    ESP_ERROR_CHECK(mpu6050_init());
    ESP_ERROR_CHECK(hmc5883l_init());

    imu_raw_t imu;
    mag_raw_t mag;

    while(1){
        if(mpu6050_read_raw(&imu) == ESP_OK &&
           hmc5883l_read_raw(&mag) == ESP_OK){
            printf("Accel: %d, %d, %d | Gyro: %d, %d, %d | Mag: %d, %d, %d\n",
                   imu.ax, imu.ay, imu.az,
                   imu.gx, imu.gy, imu.gz,
                   mag.mx, mag.my, mag.mz);
        } 
        vTaskDelay(pdMS_TO_TICKS(10)); //~100Hz
    }

}
