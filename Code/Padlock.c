/******************** PADLOCK QC ROBOT *********************/

# include <8052.h>
# include <stdio.h>
# include <stdlib.h>
# include <MORPH.h>

// FUNCTION PROTOTYPES
void OCSfunction();
void MOSfunction(char selection);
void ACSfunction();
void MSDfunction(char selection);

// GLOBAL VARIABLES
unsigned char OMD, ERR1, FFRA, FFRB, samplingTime, dialPositions;
unsigned int feedRate; //set speed in RPM
unsigned int encoderResolution; //set encoder resolution
unsigned int initialPos;
unsigned int increment;
unsigned int combo1, combo2, combo3;

__data __at (0x52) unsigned int speed;
__data __at (0x56) unsigned long distance;
__data __at (0x23) unsigned int counter;

//motion register:: XGO(0th bit), INPOS(1st bit), direction(4th bit)
__data __at (0x21) unsigned char motionRegister;

char string[5];
char *machineMessage, *menuTitle, *action1, *action2, *action3, *action4;

void INZfunction(){
printMode = 0; //Output is routed to the MPS Console
OMD=0;// REM Operation Mode is Idle
ERR1=0;//REM Level 1 Error Flag of System
FFRA=1;//REM SET First Run Flag
FFRB=1;//REM SET Second Run Flag
P1 = 0x00;//Solenoid port initialization
counter = 0; //timer counter initialization 5_16_2014
clrUDCounter();

motionRegister = 0x00; //CW direction, !inPOS, !XGO
encoderResolution = 2048*4;
dialPositions = 40;
combo1=0;
combo2=0;
combo3=0;
samplingTime = 10; //sampling time is 10ms
feedRate = 100;//50; //set motor speed in RPM
speed = (feedRate*samplingTime*(float)encoderResolution)/60000+0.5;//set speed
machineMessage = " ";
initialPos = 0;
increment = 1;

//initialize Real Time System
__asm
lcall 0x9F00
__endasm;
}//INITIALIZATION

void printHeaderAndMenu(){
clrPC();
printf("%s\n", menuTitle);
printf("****************************************\n\n");
printf("1. %s\n", action1);
printf("2. %s\n", action2);
printf("3. %s\n", action3);
printf("4. %s\n", action4);
printf("5. Exit\n\n\n\n");
}// printHeaderAndMenu

void setIdleMenu(){
menuTitle = " OPERATION MENU";
action1 = "Manual Operation";
action2 = "Automatic Operation";
action3 = "Machine Data Set-Up";
action4 = "                         ";
}// Idle Menu

void setManualMenu(){
menuTitle = " MANUAL OPERATION MENU";
action1 = "Move CW";
action2 = "Move CCW";
action3 = "Increase Tick Step Size";
action4 = "Decrease Tick Step Size";
}// Manual Menu

void setAutomaticMenu(){
menuTitle = " AUTOMATIC OPERATION MENU";
action1 = "                         ";
action2 = "                         ";
action3 = "                         ";
action4 = "                         ";
}// Auto Menu

void setMSDMenu(){
menuTitle = " MACHINE DATA SET UP MENU";
action1 = "                         ";
action2 = "                         ";
action3 = "                         ";
action4 = "                         ";
}// Auto Menu

void moveServo(char ticks, char direction){
distance = (float)ticks*(float)(encoderResolution / dialPositions);
//the 0x01 is the XGO bit and 0x10 is the directional bit
//direction 0 & 1 equate CW & CCW, respectively
motionRegister = 0x01+0x10*direction;
}//MOTION CONTROL

int getABSposition(){
__data __at (0x60) unsigned long position;
return position;
}//POSITION FEEDBACK

int diagnostics(){
if (initialPos > dialPositions-1){
ERR1 = 1;
return 0;
}
else
return 1;//successful diagnostics
}//DIG

void ERHfunction(){
if (ERR1 == 1){
setCur(0,24);
printf("Initial dial position must be set within 0 or %u.          ", dialPositions-1);
delay(2000);
initialPos=0;
ERR1=0;
}
}//ERROR CHECK + TREATMENT

void MSSfunction(){
char selection;
selection = key();

if (FFRA) OCSfunction();//skip this for the first run
//Scan Keyboard for input
switch(OMD){
case 1:
MOSfunction(selection);
break;
case 3:
MSDfunction(selection);
break;
case 0:
setCur(0,24);
printf("                                                    ");
switch (selection){
case '1':
if (FFRB) break;
OMD = 1;
setManualMenu();
machineMessage = "Manual Mode Accepted";
printHeaderAndMenu();
break;
case '2':
if (FFRB) break;
OMD = 2;
setAutomaticMenu();
machineMessage = "Automatic Mode Accepted";
printHeaderAndMenu();
break;
case '3':
OMD = 3;
setMSDMenu();
machineMessage = "Machine Data Setup Mode Accepted";
printHeaderAndMenu();
break;
case '5':
OMD = 5;
machineMessage = "Exit Command Accepted";
printHeaderAndMenu();
delay(60);
break;
}
}
}//MACHINE STATUS SUPERVISOR

void MCSfunction(){
if (OMD==1) MOSfunction(0);
if (OMD==2) ACSfunction();
if (OMD==3) MSDfunction(0);
}//MODE CONTROL SUPERVISOR

void MOSfunction(char selection){
if (selection){
switch (selection){
case '1': //Move one tick CCW
moveServo(increment,1); //move increment of ticks CCW
if (initialPos < increment)
initialPos = 40 - (increment-initialPos);
else initialPos -= increment;
break;
case '2': //Move one tick CW
moveServo(increment,0); //zero is CW
if (initialPos+increment > 39)
initialPos = increment+initialPos-40;
else initialPos += increment;
break;
case '3': //Increase Tick Step Size
if (increment<40) increment++;
break;
case '4': //Increase Tick Step Size
if (increment>1) increment--;
break;
case '5': //Exit
setIdleMenu();
printHeaderAndMenu();
OMD = 0;
}
}
setCur(0,24);
printf("Increment Size = %u \n", increment);
printf("Tick = %u \n", initialPos);
}//MANUAL OPERATION SUPERVISOR


void ACSfunction(){
char str[5];
char go1, go2, go3;
setCur(0,24);
printf("Please Enter The First Lock Combination\n");
gets(str);
combo1 = atoi(str);
if (combo1>39)
{
while(combo1>39)
{
printf(">> Please Enter a Lock Combination From 0 to 39\n");
setCur(0,25);
gets(str);
combo1 = atoi(str);
}
}
if(initialPos>combo1) go1 = 80+initialPos-combo1;
if(initialPos<combo1) go1 = 80+40-(combo1-initialPos);
if(initialPos==combo1) go1 = 80;
printf("Please Enter The Second Lock Combination\n");
gets(str);
combo2 = atoi(str);
if (combo2>39)
{
while(combo2>39)
{
printf(">> Please Enter a Lock Combination From 0 to 39\n");
gets(str);
combo1 = atoi(str);
}
}
if(combo1>combo2) go2 = 40+40-(combo1-combo2);
if(combo1<combo2) go2 = 40+combo2-combo1;
if(combo1==combo2) go2 = 40;
printf("Please Enter The Third Lock Combination\n");
gets(str);
combo3 = atoi(str);
if (combo3>39)
{
while(combo3>39)
{
printf(">> Please Enter a Lock Combination From 0 to 39\n");
gets(str);
combo1 = atoi(str);
}
}
if(combo2>combo3) go3 = combo2-combo3;
if(combo2<combo3) go3 = 40-(combo3-combo2);
//prompt before starting ACS
printf("Press Enter to Begin Automatic Mode\n");
gets(string);
counter = 0;

   printf("Moving to First Number: %d Ticks CW! \n", go1);
   moveServo(go1,1); //move CCW motor, CW Dial

   //while not in position
   while (!(motionRegister & 02));
   printf("Moving to First Number: %d Ticks CCW! \n", go2);
   moveServo(go2,0); //move CW motor, CCW Dial

   //while not in position
   while (!(motionRegister & 02));

   printf("Moving to First Number: %d Ticks CW! \n", go3);
   moveServo(go3,1); //move CCW motor, CW Dial

   //while not in position
   while (!(motionRegister & 02));

   //pop the lock with the solenoid connected to port 1
   printf("\n\n\n\nPress Enter to Release Solenoid\n");
   P1 = 0xFF;
printf("Time in ms: %u", 10*counter);
   gets(string);
   P1 = 0x00;

   //no longer in automatic mode
   setIdleMenu();
   printHeaderAndMenu();
   OMD = 0;
   initialPos=combo3;
}//Automatic Control Supervisor

void MSDfunction(char selection){
char input[8];

selection = key();

//Initial Position
setCur(0,24);
printf("Initial Dial Position = ");
gets(input);
initialPos = atoi(input);

//Speed
setCur(0,25);
printf("Speed (RPM) = ");
gets(input);
feedRate = atoi(input);
speed = (feedRate*samplingTime*(float)encoderResolution)/60000+0.5;//set speed

//Exit
setIdleMenu();
printHeaderAndMenu();
OMD = 0;
FFRB = 0;


}//MACHINE DATA SETUP

char *getCurrentMode(){
switch (OMD){
case 1:
return "Manual";
case 2:
return "Automatic";
case 3:
return "Machine Data Setup";
case 5:
return "System Turned Off";
default:
return "Idle Mode";
}
}//Used for OCS

char *getServoStatus(){
if (motionRegister & 02)
return "Stopped ";
else
return "Moving... ";
}// Servo Status

void OCSfunction(){
if(FFRA) {
FFRA = 0;//Clear first run flag
setIdleMenu();
printHeaderAndMenu();
}
else{
setCur(0,21);
printf("%s \n", machineMessage);
printf("Servo Status: %s     %u         \n", getServoStatus(), getABSposition());
printf("Current Mode: %s\n\n", getCurrentMode());

if (OMD == 0){
setCur(0,24);
printf("                                   \n");
printf("                                   \n");
}
setCur(0,24);
if (FFRB) printf("Please set the initial position.");
}
}//OUTPUT CONTROL SUPERVISOR

void main(){
INZfunction();

while(OMD != 5 && !microButtons){
//run diagnostics
if (diagnostics()){
//if diagnostics succeed
MSSfunction();
MCSfunction();
OCSfunction();
}
else{
//go to ERH if diagnostics fail
ERHfunction();
OCSfunction();
}
}// While
}// Main
