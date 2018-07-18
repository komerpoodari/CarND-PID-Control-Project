#include <ctime>
#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    
    p_error = 0.;
    i_error = 0.;
    d_error = 0.;
    
    time_last = time_init = clock();
    //time_init = clock();
    min_speed =  500.0; // limit
    max_speed = -500.0; // limit
    sum_speed = 0.0;
    heart_beat = 0;
}

void PID::UpdateError(double cte, double speed) {
    double time_curr, dt;
    
    time_curr = clock();
    dt = (time_curr - time_last);
    //cout << "time_last: " << time_last << "; time_curr: " << time_curr << "; dt: " << dt << endl;   
    if (dt == 0)
        dt = 1.0;
    time_last = time_curr;

    d_error = (cte - p_error);
    //d_error = (cte - p_error) / dt;
    //cout << "dt: " << dt << "; d_error: " << d_error << endl;
    p_error = cte;
    i_error += cte;
    
    heart_beat++;
    cout << "heart_beat: " << heart_beat << endl;
    /**
    **
    if (min_speed > speed)
        min_speed = speed;
    if (max_speed < speed)
        max_speed = speed;
    sum_speed += speed;

    
    if (heart_beat % 10 == 0)
        cout << "speed min: " << min_speed << "; max: " << max_speed <<"; avg: " << sum_speed/heart_beat << endl;
    **/
}

double PID::TotalError() {
    double steer = Kp*p_error + Kd*d_error + Ki*i_error;
    
    //std::cout << "steer: " << steer << endl;
    if (steer > 1.0)
        steer = 1.0;
    else if (steer < -1.0)
        steer = -1.0;
    
    return steer;
}

