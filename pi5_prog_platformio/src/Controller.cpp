
#include <iostream>
#include <Arduino.h>
#include <PID_v1.h>
#include <Controller.h>

using namespace std;

    double Desired_temperature;
    double Desired_humidity;

    //double real_temperature;
    //double real_humidity;
    double pin_value_humidity;
    double pin_value_temperature;

    double Kp_t=2, Ki_t=5, Kd_t=1;
    double Kp_h=2, Ki_h=5, Kd_h=1;

    int pin_state_temp;
    int pin_state_humidity;
    int pin_state_fans;

    bool temp_control_state;
    bool humidity_control_state;

    int Temp_PWM_FREQUENCY;
    int Temp_PWM_CHANNEL;
    int Temp_PWM_RESOLUTION;

    int humidity_PWM_FREQUENCY;
    int humidity_PWM_CHANNEL;
    int humidity_PWM_RESOLUTION;

    Controller::Controller()
    {
    Desired_temperature = 0;
    Desired_humidity = 0;

    pin_state_temp = 0;
    pin_state_humidity = 0;
    pin_state_fans = 0;

    temp_control_state = 0;
    humidity_control_state = 0;

    Temp_PWM_FREQUENCY = 5000;
    Temp_PWM_CHANNEL = 0;
    Temp_PWM_RESOLUTION = 8;

    humidity_PWM_FREQUENCY = 5000;
    humidity_PWM_CHANNEL = 0;
    humidity_PWM_RESOLUTION = 8;
    }

    void Controller::Set_temp_pwm_config(int GPIO_pin, int Frequency, int Channel, int Resolution)
    {
    humidity_PWM_FREQUENCY = Frequency;
    humidity_PWM_CHANNEL = Channel;
    humidity_PWM_RESOLUTION = Resolution;
    ledcAttachPin(GPIO_pin, Channel);
    ledcSetup(Channel, Frequency, Resolution);
    }

    void Controller::Set_hum_pwm_config(int GPIO_pin, int Frequency, int Channel, int Resolution)
    {
    Temp_PWM_FREQUENCY = Frequency;
    Temp_PWM_CHANNEL = Channel;
    Temp_PWM_RESOLUTION = Resolution;
    ledcAttachPin(GPIO_pin, Channel);
    ledcSetup(Channel, Frequency, Resolution);
    }

    void Controller::Set_desired_temperature(float DT)
    {
        Desired_temperature = DT;
    }

    void Controller::Set_desired_humidity(float hm)
    {
        Desired_humidity = hm;
    }

    void Controller::Control_temp(float curr_temp) // controls the temperature of the sistem
    {
        if (temp_control_state==0) // returns if the control temp state is set to 0
        {
        printf("Temperature control state turned OFF");
        ledcWrite(Temp_PWM_CHANNEL, 0); // sets the dutycicle to 0
        return;
        }
        else
        {
            int dummy_DutyCycle = 5;
            ledcWrite(Temp_PWM_CHANNEL, dummy_DutyCycle);
        }
    }

    void Controller::Control_humidity(float curr_humidity)
    {
        if (humidity_control_state==0) // returns if the control humidity state is set to 0
        {
        printf("humidity control state turned OFF");
        ledcWrite(humidity_PWM_CHANNEL, 0); // sets the dutycicle to 0
        return;
        }
        else
        {
            int dummy_DutyCycle = 5;
            if (curr_humidity < Desired_humidity)
            {
            ledcWrite(humidity_PWM_CHANNEL, dummy_DutyCycle);
            }
            else
            {
            ledcWrite(humidity_PWM_CHANNEL, 0);
            }
        }
    }

    void Controller::PID_CONTROLL(double real_temperature, double real_humidity)
    {
        PID myPID_humidity(&real_humidity, &pin_value_humidity, &Desired_humidity, Kp_h, Ki_h, Kd_h, DIRECT);
        PID myPID_temperature(&real_temperature, &pin_value_temperature, &Desired_temperature, Kp_t, Ki_t, Kd_t, DIRECT);
        //real_temperature = analogRead(PIN_INPUT); // atualisar real temperature
        Desired_temperature = 100;  // set the target (dummy)
        Desired_humidity = 30;      // set the target (dummy)

        //turn the PID on
        myPID_temperature.SetMode(AUTOMATIC);
        myPID_humidity.SetMode(AUTOMATIC);

        myPID_temperature.Compute();
        ledcWrite(Temp_PWM_FREQUENCY, pin_value_temperature);

        myPID_humidity.Compute();
        ledcWrite(humidity_PWM_FREQUENCY, pin_value_humidity);
    }


        // PID myPID_temperature(&real_temperature, &pin_value_temperature, &Desired_temperature, Kp_t, Ki_t, Kd_t, DIRECT);