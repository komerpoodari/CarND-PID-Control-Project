# CarND-Controls-PID
## Self-Driving Car Engineer Nanodegree Program, Term-2

---
**This file is updated based on the assignment submission.**

[//]: # (Image References)
[image1]: ./state.png
[image2]: ./twiddle.png

# Assignment Implementation
The relevant functions mentioned below are implemented in `main.cpp`.
1. `main()` 
    Important were the initializaton of gain parameter values for Proportional gain (`Kp_ini`),
    Integral gain (`Ki_ini`) and Derivative gain (`Kd_ini`). I used a combination of manual tuning
    and *TWIDDLE* covered in lesson lectures. The *TWIDDLE* tuning algorithm is implemented using
    a state machine in `pid.cpp`.
    

The relevant functions mentioned below are implemented in `pid.cpp` and relevant changes 
made in `pid.h'    
2. `PID::Init()`
    Most impotantly, the tuned gain parameters are initialized in this initialization function.
    
3. `PID::UpdateError()`
    The error terms are updated in this function for proportional, integral and deriverative
    aspects.  The integral error is reset at the beginning of each lap, to avoid relatively 
    excessive influence on steering value computation.
    
    The *TWIDDLE* related state machine is implemented. The state machine updates one of the gain
    parameters for each lap (equivalent to one robot run in lectures). The *TWIDDLE* is only enabled
    under a compile time macro. The following Figure illustrates high-level state diagram.
    
    ![alt text][image1]
    
    The following snapshot illustrate typical *TWIDDLE* console output, which describes the 
    algorithm seach for optimized error value.
    ![alt text][image2]
    
4. `PID::TotalError()`
    This functon simply computes steering value and with appropriate boundaries.

   
# Observations and Reflections
Though the main implementation is simple, fine-tuning of gain values is time consuming.
I followed an iterative approach with a combination of manual and *TWIDDLE*.
- First I identified the approximate gain values manually starting in the order Kp, Kd and Ki.
- Then engaged *TWIDDLE* to fine tune.
- Another dimension is throttle schedule. Because of this some times, even though error is best value,
  the car behavior was not the best. I had to make manual decision.
The following are the observations with gain parameters.
## Proportional Gain (Kp)
This is fundamentally important. In my case, I settled on **Kp = -0.6405**. 
Using `Kp` alone, I could observe the oscillating behavior as observed in the video at the link, 
https://youtu.be/Ip1jwMwHsUw .  In absence of appropriate amount of derivative feedback 
instability (oscillation behavior) is expected.

## Derivative Gain (Kd) Addition
This is very important. In my case, I settled on **Kd = -16.00**. The derivative feedback
offers stability to the output.

Using `Kp and Kd`, I could observe reasonably stable behavior as captured in the video at 
the link, https://youtu.be/TOHkzHEoH5U . Basically derivative feedback smoothens the output.

## Integral Gain (Ki) Addition
In my observation, `Ki` impact was minor, as expected, since simulator seems to have no constant
bias. I had reset `i_error to zero` for every lap to avoid relatively excessive accumulation of
influence over multiple laps. In my case, I settled on **Ki = -0.00016**. The integral feedback
nullifies any constant equipment bias feeding into to the output.

Using `Kp, Kd and Ki`, I could observe stable behavior as captured in the video at 
the link, https://youtu.be/9118E5b3k2U . 

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

