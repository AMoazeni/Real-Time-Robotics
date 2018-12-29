# Introduction

<br></br>
Take me to the Real-Time Fault Tolerant [Padlock Quality Control Robot Code](https://github.com/AMoazeni/Real-Time-Robotics/blob/master/Code/Padlock.c)!


<br></br>
Robotics is a branch of Science that combines Mechanical, Electrical, and Software Engineering. This article will show you how to design your Control System software to be as robust as possible. We will first look at a simple software approach and then learn about robust Fault Tolerant Real-Time Software Architecture.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/01%20-%20Robot%20Arm.gif" width=50% alt="Robot-Arm"></div>




<br></br>

# Simple Sense-Think-Act Loop

This is the simple software architecture you find in most interactive device project tutorials like this [Obstacle Avoiding Robot](https://www.youtube.com/watch?v=coAmKyqGyeY) and [Line Following Robot](https://circuitdigest.com/microcontroller-projects/raspberry-pi-line-follower-robot). The computer measures the distance ahead and makes small adjustments to stay on track. The code is run line by line, as fast as possible.


<br></br>
<div align="center">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/03%20-%20Obstacle%20Avoid.gif" width=40% alt="Obstacle-Avoid">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/04%20-%20Line%20Follow.gif" width=40% alt="Line-Follow">

</div>


<br></br>
The problem is that you have no control over the speed of code execution, a 10MHz CPU runs ten million lines of code per second, and a 1GHz CPU runs one billion lines of code per second. This can be problematic for time-critical applications, as discussed in the next sections.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/02%20-%20Sense%20Think%20Act.png" width=50% alt="Sense-Think-Act-Loop"></div>



```python

# Python Sense-Think-Act Loop
while True:
  
  # Measure Ultrasonic Sensor Distance
  distance = Read(sensor)
  
  # No Obstacle - Drive Straight If Measured Distance Is Large
  if distance > 10:
    Drive(Straight)
  
  # Obstacle Detected - Turn Right If Measured Distance Is Small
  else:
    Drive(Right)

```



<br></br>

# Real-Time Fault Tolerant Software Architecture

As Robotic systems become more sophisticated and have to deal with huge amounts of sensor input, make quick decisions, and continue operation if components break; you need highly robust software for successful operation. [Fault Tolerant](https://en.wikipedia.org/wiki/Fault_tolerance) means that a system continues operating properly in the event of the failure of components.


<br></br>
That's why NASA's spaceships and rovers have redundant systems built in (multiple versions of the same sensors and actuators), if something breaks in space you need multiple system backups that can take over immediately. Tools like Publisher-Subscriber architecture and Real-Time parallel execution of code become really important.



<br></br>
<div align="center">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/05%20-%20Self%20Driving%20Car.gif" width=40% height=300 alt="Self-Driving-Car">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/06%20-%20SpaceX.gif" width=40% height=300 alt="SpaceX">

</div>


<div align="center">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/07%20-%20Robot%20Dance.gif" width=40% height=300 alt="Robot-Dance">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/08%20-%20Power%20Plant.gif" width=40% height=300 alt="Power-Plant">

</div>



<br></br>

# Publisher-Subscriber Software Architecture

A good way to visualize [Pub-Sub](https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern) architecture is shown below. A piece of code can be set up as a Transmitter (Publisher), Receiver (Subscriber), or Transceiver (can both Publish and Subscribe). These pieces of code (functions) are completely independent of one another and don't know of each other's existence. The functions can however communicate if they are placed on the same channel (Topic). Functions can send each other numbers and text messages to communicate, they can also be written in any language (Python, C++, Javascript, etc). This allows highly scalable architecture and robustness of execution since the functions are loosely coupled.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/09%20-%20Publisher%20Subscriber.png" width=75% alt="Publisher-Subscriber"></div>


<br></br>
For example one function can read sensor values (Publisher), another function can process these reading and come up with an action (Subscriber-Publisher), and a third function can control the wheels (Subscriber). If a component breaks, the code running other components will not be affected. Robot Operating System ([ROS](http://www.ros.org/)) is a popular platform that runs the Pub-Sub architecture.



<br></br>

# Real-Time Computing

Timing is the key difference between Real-Time systems (embedded software in high performance robotics), versus other software (web applications and personal computer operating systems). In Real-Time systems, correctness depends on both the accuracy of response, as well as the timing of that response. If a Real-Time system responds too late or misses a deadline, it has failed the Real-Time system criteria and considered incorrect. Most embedded systems run continuously when powered on, and must do a specific task robustly.


<br></br>
High performance is really important in production level products, versus prototypes and single projects. You tend to get the best performance with code that is as short and low-level as possible, removing the unnecessary overhead that comes with high-level functions, APIs, and operating systems. Each embedded platform chip has its own data sheet and operation manual, but concepts like Interrupts and Timers remain universal.


<br></br>
Registers, Interrupts and Timers are the tools required to set up Real-Time systems. The following diagram demonstrates how to set up your Real-Time Fault Tolerant software architecture. The Free Time System (FTS) contains code that is not time-critical and can run at arbitrary speeds (eg. User Interface, etc). The Real Time System (RTS) contains the really important time-critical functions that take priority over everything else (eg. safety shutoff, automatic braking, accurate position control, overheat protection, anti-aliasing sensor measurements etc). The RTS is typically written in low level Assembly language and optimized for performance, time complexity, and space complexity. FTS and RTS systems can communicate using shared memory locations (registers).


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/10%20-%20Real%20Time%20Software.png" alt="Real-Time-Software"></div>



```C

// C Language Real-Time Fault Tolerant Software Architecture
void main(){

  // Initialize Function
  INZfunction();

  // Control System Loop - Stop Operation With Software or E-Button Hardware
  while(OperationMode != 0  &&  !EmergencyButton){

      // If Diagnostics Succeed
      if (diagnostics()){

          MSSfunction();  // Machine Status Scan
          MCSfunction();  // Mode Control Supervisor
          OCSfunction();  // User Interface Output

      }


      // If Diagnostics Fail - Run Error Treatment
      else{

          ERHfunction();  // Error Treatment
          OCSfunction();  // User Interface Output

      } // End Diagnostics

    } // End Control System Loop

} // End Main


```


<br></br>

# Interrupts

Typical single core CPUs run code sequentially, but high priority Real-Time systems need instant response to stimuli. That's why interrupts are really useful. Interrupts stop whatever is happening in the Free Time System (FTS), run the time critical code, and resume FTS computation. This can also be achieved with the use of multiple processors. Typically there are two types of Interrupts: Time-Driven Interrupts, and Event-Driven Interrupts.


<br></br>
- Event-Driven Interrupts: Trigger when some event happens (eg. Emergency shutoff button pressed, or Temperature threshold is passed and a fan is activated).

- Time-Driven Interrupts: Run continuously at a certain time interval (eg. motor position is adjusted to the correct position every 50ms)


<br></br>
Always test your code in the real world, and use an Oscilloscope to measure the timing that you designed for. You can use an output PIN to do this. Set the output pin to HIGH (ON) at the beginning of your Real-Time code, and set the same pin to LOW (OFF) at the end of your Real-Time code. This "pin pulse" can be detected on the oscilloscope and used to measure the actual performance of your code. Take a look at the following oscilloscope measurements for a Real-Time system.


<br></br>
Important Note: Make sure that your code runtime is shorter than the timer interrupt interval. So if you want your Real-Time code to fire every 50ms, make sure that your code can run in 49ms or less. A minimum 20% margin is ideal, so the code should take less than 40ms to run.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/11%20-%20RTS%20Oscilloscope.png" alt="RTS-Oscilloscope"></div>



<br></br>

# Timers and Counter-Overflow

Accurate time keeping is mandatory for Real-Time systems, you don't want your system time to drift after a while. Most Micro-controllers have dedicated Timer chips built in. Here is the Arduino [ATmega328P Microcontroller Datasheet](http://ww1.microchip.com/downloads/en/devicedoc/atmel-8271-8-bit-avr-microcontroller-atmega48a-48pa-88a-88pa-168a-168pa-328-328p_datasheet_complete.pdf) you need to look at the data sheet of YOUR system for configuration instructions. You've probably seen 'delay( )' functions in Arduino code, but they're not useful in Real-Time applications because they force the CPU to do nothing for a time period and clog up computation cycles. Use counter-overflow timers instead for Real-Time Applications, this keeps the main loop responsive to other inputs.


<br></br>
Timers have a built-in crystal which is an electrical device that emits pulses at a fixed frequency when electricity is applied. One can find crystals of virtually any frequency depending on the application requirements, its frequency depends on the crystal shape and geometry. Crystals are used to synchronize machine cycles. The Arduino timer crystal features a frequency of 16MHz. So the Arduino timer chip can increment a counting variable 16 million times per second.


<br></br>
If you use a 16-bit timer, the timer counts up to 2^16 = 65536 before resetting back to 0 and counting up again. It adds '1' to the count every clock cycle (16MHz), when the counter overflows, a flag is activated. You can calibrate the timing of the interrupt by adjusting the starting value of the counter. GreatScott has a great [Timer Setup Tutorial](https://www.youtube.com/watch?v=IdL0_ZJ7V2s) to get you started. Sparkfun also has good videos explaining [Timer Interrupts](https://www.youtube.com/watch?v=2kr5A350H7E) and [External Interrupts](https://www.youtube.com/watch?v=J61_PKyWjxU&index=2&list=PLBcrWxTa5CS0u-rQNkGtLMg1yA7h56r6).


<br></br>
If this is the first time you learn about Timers and Interrupts, it can seem overwhelming. But don't be discouraged because this is a skill that can vastly improve your product's performance and keep your customers very happy!



<br></br>

# RTOS and Language Speed Comparison

Here is a list of [Real-Time Operating Systems (RTOS)](https://en.wikipedia.org/wiki/Comparison_of_real-time_operating_systems) for your next embedded project. ARM Architecture chips have really good built quality, popular [Open Source development](https://os.mbed.com/) community, and have been designing chip architectures for over 30 years.


<br></br>
Python is great for prototyping and quick development due to its simple syntax. Julia is a new open source language designed for Engineering and technical calculations (similar to expensive and closed source MATLAB). Production level code is generally written in C, with Real-Time functions written in Assembly (hardware specific language). Python developers can use 'Cython' and 'Micro-Python' Libraries to improve their code performance.


<br></br>
Fastest to Slowest runtime: Assembly, c, c++, Julia, Python, JavaScript



<br></br>

# Padlock Quality Control Robot Project

This device was designed to test Padlocks. A stepper motor turns the dial and a linear solenoid actuator is used to open the lock. A keyboard is used to operate the user interface, you can electronically turn the dial with manual steps, or automatically open the lock given the correct combination. It's designed with all the Fault Tolerant Real-Time principled discussed in this article.



<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/12%20-%20Padlock%20QC.png" width=40% alt="Padlock-QC"></div>


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/13%20-%20Padlock%20Control.png" width=80% alt="Padlock-Control"></div>



<br></br>

# Code Download


<br></br>
```shell
$ git clone https://github.com/AMoazeni/Real-Time-Robotics.git
$ cd Real-Time-Robotics
```



<br></br>

# Happy Coding!

Check out [AMoazeni's Github](https://github.com/AMoazeni/) for more Data Science, Machine Learning, and Robotics repositories.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/14%20-%20Robot%20Soccer.gif" width=40% alt="Robot-Soccer"></div>



