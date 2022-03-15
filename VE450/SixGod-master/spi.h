//
// Created by Qian Xinyu on 2020/10/10.
//

#ifndef SIXGOD_SPI_H
#define SIXGOD_SPI_H
    void spi_transfer(int fd, int servo_pwm, int motor_pwm);
    int spi_initialize(const char *device);
#endif //SIXGOD_SPI_H
