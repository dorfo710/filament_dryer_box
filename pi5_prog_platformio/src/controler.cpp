
#include <iostream>
using namespace std;
class Controler {

public:
    float curr_temperature;
    float curr_humidity;

    float Desired_temperature;
    float Desired_humidity;

    int pin_state_temp;
    int pin_state_humitidy;
    int pin_state_fans;

    bool temp_control_state;
    bool humidity_control_state;

    void Set_desired_temperature(float DT)
    {
        Desired_temperature = DT;
    }

    void Set_desired_humidity(float hm)
    {
        Desired_humidity = hm;
    }

    void Get_curr_temperature() // calls the respective monitor funtioning to return the current state of the temperature in the sistem
    {

    }

    void Get_curr_humidity() // calls the respective monitor funtioning to return the current state of the humidity in the sistem
    {
        
    }

    void Control_temp() // controls the temperature of the sistem
    {
        if (temp_control_state==0) // returns if the control temp state is set to 0
        {
        printf("Temperature control state turned OFF");
        return;
        }
        else
        {

        }
    }

    void Control_humidity()
    {
        if (humidity_control_state==0) // returns if the control humidity state is set to 0
        {
        printf("humidity control state turned OFF");
        return;
        }
        else
        {

        }
    }

};