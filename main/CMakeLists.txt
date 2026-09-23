idf_component_register(SRCS "calib_ekf.c"
                        "drivers/i2c_bus.c"
                        "drivers/mpu6050.c"
                        "drivers/hmc5883l.c"
                    INCLUDE_DIRS "."
                    "drivers")
