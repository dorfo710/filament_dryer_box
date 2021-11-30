
#include <iostream>
#include <Arduino.h>

using namespace std;
class Controller {

public:

    float Desired_temperature;
    float Desired_humidity;

    int pin_state_temp;
    int pin_state_humitidy;
    int pin_state_fans;

    bool temp_control_state;
    bool humidity_control_state;

    int Temp_PWM_FREQUENCY;
    int Temp_PWM_CHANNEL;
    int Temp_PWM_RESOLUTION;

    int humidity_PWM_FREQUENCY;
    int humidity_PWM_CHANNEL;
    int humidity_PWM_RESOLUTION;

    Controller(int Temp_PWM_FREQUENCY, int Temp_PWM_CHANNEL, int Temp_PWM_RESOLUTION, int humidity_PWM_FREQUENCY, int humidity_PWM_CHANNEL, int humidity_PWM_RESOLUTION){
    Desired_temperature = 0;
    Desired_humidity = 0;

    pin_state_temp = 0;
    pin_state_humitidy = 0;
    pin_state_fans = 0;

    temp_control_state = 0;
    humidity_control_state = 0;

    this->Temp_PWM_FREQUENCY = Temp_PWM_FREQUENCY;
    this->Temp_PWM_CHANNEL = Temp_PWM_CHANNEL;
    this->Temp_PWM_RESOLUTION = Temp_PWM_RESOLUTION;

    this->humidity_PWM_FREQUENCY = humidity_PWM_FREQUENCY;
    this->humidity_PWM_CHANNEL = humidity_PWM_CHANNEL;
    this->humidity_PWM_RESOLUTION = humidity_PWM_RESOLUTION;
    }

    void Set_temp_pwm_config(int GPIO_pin, int Frequency, int Channel, int Resolution)
    {
    humidity_PWM_FREQUENCY = Frequency;
    humidity_PWM_CHANNEL = Channel;
    humidity_PWM_RESOLUTION = Resolution;
    ledcAttachPin(GPIO_pin, Channel);
    ledcSetup(Channel, Frequency, Resolution);
    }

    void Set_hum_pwm_config(int Frequency, int Channel, int Resolution)
    {
    Temp_PWM_FREQUENCY = Frequency;
    Temp_PWM_CHANNEL = Channel;
    Temp_PWM_RESOLUTION = Resolution;
    }

    void Set_desired_temperature(float DT)
    {
        Desired_temperature = DT;
    }

    void Set_desired_humidity(float hm)
    {
        Desired_humidity = hm;
    }

    void Control_temp(float curr_temp) // controls the temperature of the sistem
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

    void Control_humidity(float curr_humidity)
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

};
