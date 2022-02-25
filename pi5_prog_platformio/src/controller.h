#ifndef _Controller_H_
#define _Controller_H_

#include <Arduino.h>

class Controller
{
public:
    double Desired_temperature, Desired_humidity, pin_value_humidity, pin_value_temperature;
    int pin_state_temp, pin_state_humitidy, pin_state_fans;
    bool temp_control_state, humidity_control_state;
    int Temp_PWM_FREQUENCY, Temp_PWM_CHANNEL, Temp_PWM_RESOLUTION;
    int humidity_PWM_FREQUENCY, humidity_PWM_CHANNEL, humidity_PWM_RESOLUTION;

public:
    Controller();
    void Set_temp_pwm_config(int, int, int, int);
    void Set_hum_pwm_config(int, int, int, int);
    void Set_desired_temperature(float);
    void Set_desired_humidity(float);
    void Control_temp(float);
    void Control_humidity(float);
    void PID_CONTROLL(double, double);
    int func_PID_TEST(double, double);
};
#endif