#include <ctime>
#include <iostream>
#include <math.h>
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
    heart_beat = 0;
    
#ifdef TWIDDLE
    //Twiddle delta parameters; initialized based on respective sensitivies.
    d_kp = 0.050;
    d_ki = 0.0005;
    d_kd = 0.10;
    
    cte_sum = 0.0;
    cte_best = 500.0; // does not matter as this is initialized at the end of first lap.
    beats_per_lap = 2000;  // approximation for every lap of the course.
    this_lap = 0;
    last_state = init;
#endif // TWIDDLE
}

void PID::UpdateError(double cte, double speed) {


    d_error = (cte - p_error);
    p_error = cte;
    i_error += cte;
 
 #ifdef TWIDDLE
    cte_sum += (cte*cte); //update cte sum over the lap;
 #endif //TWIDDLE
 
    heart_beat++;
    //cout << "heart_beat: " << heart_beat << endl;
      if ((heart_beat % beats_per_lap) == 0)
        i_error = 0;  // reset integration error after every lap to avoid outsized influence.
    
#ifdef TWIDDLE
    //implement twiddle
    if ((heart_beat % beats_per_lap) == 0) {
    
        double cte_ave = sqrt(cte_sum) / beats_per_lap;
        cte_sum = 0;  //reset sum for every lap.  Every lap is basically robot run in lessons.
        i_error = 0;  // reset integration error after every lap to avoid outsized influence.
        if (this_lap == 0) {  //First Lap completed
            cte_best = cte_ave;
            last_state = init;
            cout << "lap: " << this_lap << "; Kp: " << Kp << "; Ki:" << Ki << "; Kd: " << Kd << "; cte_best:" << cte_best << endl;
        }
        
        cout << "lap: " << this_lap << "; cte_ave: " << cte_ave << "; cte_best:" << cte_best << endl;

        switch (last_state) {
                case init:  // adjust Kp
                    Kp += d_kp;
                    last_state = kp_inc;
                    break;
                case kp_inc:  // decide to keep the last increment or decrease
                    if (cte_ave < cte_best) {
                        cte_best = cte_ave;
                        d_kp *= 1.1;
                        
                        // adjust Ki parameter
                        Ki += d_ki;
                        last_state = ki_inc;
                    }
                    else {
                        Kp -= 2 * d_kp;
                        last_state = kp_dec;
                    }
                    break;
                    
                case kp_dec :  // Kp got decremented 
                    if (cte_ave < cte_best) {
                        cte_best = cte_ave;
                        d_kp *= 1.1;

                    } 
                    else {
                        Kp += d_kp;
                        d_kp *=0.9;
                    }
                    
                    // adjust Ki parameter
                    Ki += d_ki;
                    last_state = ki_inc; 
                    break;

                case ki_inc:  // proceed with adjusting Ki
                   if (cte_ave < cte_best) {
                        cte_best = cte_ave;
                        d_ki *= 1.1;
                        
                        // adjust Kd parameter
                        Kd += d_kd;
                        last_state = kd_inc;
                    }
                    else {
                        Ki -= 2 * d_ki;
                        last_state = ki_dec;
                    }
                    break;

                case ki_dec :  // Ki got decremented 
                    if (cte_ave < cte_best) {
                        cte_best = cte_ave;
                        d_ki *= 1.1;

                    } 
                    else {
                        Ki += d_ki;
                        d_ki *=0.9;
                    }
                    
                    // adjust Kd parameter
                    Kd += d_kd;
                    last_state = kd_inc; 
                    break;
 
                case kd_inc:  // proceed with adjusting Kd
                   if (cte_ave < cte_best) {
                        cte_best = cte_ave;
                        d_kd *= 1.1;
                        
                        // adjust Kd parameter
                        Kp += d_kp;
                        last_state = kp_inc;
                    }
                    else {
                        Kd -= 2 * d_kd;
                        last_state = kd_dec;
                    }
                    break;

                case kd_dec :  // Kd got decremented 
                    if (cte_ave < cte_best) {
                        cte_best = cte_ave;
                        d_kd *= 1.1;

                    } 
                    else {
                        Kd += d_kd;
                        d_kd *=0.9;
                    }
                    
                    // adjust Kd parameter
                    Kp += d_kp;
                    last_state = kp_inc; 
                    break; 
                    
                default:
                    cout << "control should not reach" << endl;
            }
            
        this_lap++;
        cout << "lap: " << this_lap << "; Kp: " << Kp << "; Ki:" << Ki << "; Kd: " << Kd << "; cte_best:" << cte_best << endl;
    } // twiddle end
#endif //TWIDDLE
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

