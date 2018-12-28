# Introduction

Take me to the [Code](https://github.com/AMoazeni/Real-Time-Robotics/blob/master/Code/main.cpp) for Real Time Robotics!


<br></br>
Robotics is a branch of Science that combines Mechanical, Electrical, and Software Engineering. This article will show you how to make your Control System software as robust as possible. We will first look at the simple software design approach and then learn about the robust Fault Tolerant Real-Time architecture.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/01%20-%20Robot%20Arm.gif" width=50% alt="Robot-Arm"></div>




<br></br>

# Sense-Think-Act Loop

This is the simple software architecture you find in most interactive devices like this [Line Following Robot](https://circuitdigest.com/microcontroller-projects/raspberry-pi-line-follower-robot) and [Obstacle Avoiding Robot](https://www.youtube.com/watch?v=coAmKyqGyeY). The computer measures the distance ahead and makes small adjustments to stay on track. The code is run line by line as fast as possible.


<br></br>
The problem here is that you have no control over the speed of code execution, a 10MHz CPU runs the code ten million times per second, and a 1GHz CPU runs the code one billion times a second. This can be problematic for time-critical applications, as discussed in the next sections.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/02%20-%20Sense%20Think%20Act.png" width=50% alt="Sense-Think-Act-Loop"></div>



```python

# Sense-Think-Act Infinite Loop
while True:
  
  # Measure Ultrasonic Sensor Distance
  distance = read(sensor)
  
  # Drive Straight if Distance Ahead is Large (No Obstacles)
  if distance > 10:
    Drive(Straight)
  
  # Otherwise Turn (Obstacle Detected)
  else:
    Drive(Right)

```



<br></br>
<div align="center">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/03%20-%20Obstacle%20Avoid.gif" width=40% alt="Obstacle-Avoid">

<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/04%20-%20Line%20Follow.gif" width=40% alt="Line-Follow">

</div>



<br></br>

# Real-Time Fault Tolerant Software Architecture

As Robotic systems become more sophisticated and have to deal with huge amounts of sensor input, make quick decisions, and continue operation if components break; you need highly robust software for successful operation. [Fault Tolerant](https://en.wikipedia.org/wiki/Fault_tolerance) means that a system continues operating properly in the event of the failure of components.


<br></br>
That's why NASA's spaceships and rovers have redundant systems built in (multiple copies of the same sensors and actuators), if something breaks in space you need multiple system backups that can take over immediately. Publisher-Subscriber software architecture and Real-Time parallel execution of code becomes really important.



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

A good way to visualize [Pub-Sub](https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern) architecture is shown below. A piece of code can be set up as a Transmitter (Publisher), Receiver (Subscriber), or Transceiver (can both Publish and Subscribe). These pieces of code (functions) are completely independent of one another and don't know of each other's existence. The functions can communicate if they are placed on the same channel (Topic). This allows highly scalable architecture and robustness of execution since the functions are loosely coupled.


<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/09%20-%20Publisher%20Subscriber.png" width=75% alt="Publisher-Subscriber"></div>


<br></br>
For example one function can read sensor values (Publisher), another function can process these reading and come up with an action (Publisher-Subscriber), and a third function can control the wheels (Subscriber). If a component breaks, the code running the other components will not be affected. Functions can send each other numbers and text messages to communicate, they can also be written in any language (pthon, C++, Javascript, etc). Robot Operating System ([ROS](http://www.ros.org/)) is a popular platform that runs the Pub-Sub architecture.



<br></br>

# Real-Time Computing

interrupts, aliasing, pub-sub timing, safety brakes, fan meltdown,

<br></br>
<div align="center"><img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/10%20-%20Real%20Time%20Software.png" alt="Real-Time-Software"></div>




# Language Speed Comparison

Assembly, c, c++, python, Julia, Matlab



<br></br>

# Real-Time Project

Padlock opener project code

Use the keyboard to turn the dial, automatically open the lock given the combination




```C


// Main Function
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



# Code


<br></br>
```shell
$ git clone https://github.com/AMoazeni/Real-Time-Robotics.git
$ cd Real-Time-Robotics
```



<br></br>

# Happy Coding!

Check out [AMoazeni's Github](https://github.com/AMoazeni/) for more Data Science, Machine Learning, and Robotics repositories.


<br></br>
<img src="https://raw.githubusercontent.com/AMoazeni/Real-Time-Robotics/master/Jupyter%20Notebook/Images/11%20-%20Robot%20Soccer.gif" width=40% alt="Robot-Soccer">



