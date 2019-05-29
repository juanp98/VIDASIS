#include <Servo.h>
#include <MyoController.h>

#define CLOSE   0
#define REST    1
#define OPEN    2

int posServos = 0;
int speed_open_close;
float time_delay = 20;
float read_pot_delay = 10;
float read_pot_step;

MyoController myo = MyoController();
Servo finger1;
Servo finger2;
Servo finger3;
Servo finger4;
Servo finger5;

void setup() {
  Serial.begin(9600);
  myo.initMyo();
  
  finger1.attach(3);
  finger2.attach(5);
  finger3.attach(6);
  finger4.attach(9);
  finger5.attach(10);
  

  finger1.write(170);
  finger2.write(170);
  finger3.write(170);
  finger4.write(170);
  finger5.write(170);
  posServos = 170;

}

void loop()
{
   //read_pot_delay = analogRead(A0);
   read_pot_step = analogRead(A1);

   speed_open_close = map(read_pot_step,0,1023,1,42.5);
   //time_delay = map(read_pot_delay,0,1023,0,1000);
   myo.updatePose();
   Serial.println(myo.getCurrentPose());
   switch ( myo.getCurrentPose() ) {
    case rest:
      posServos+=speed_open_close;
      if(posServos > 170){
        posServos = 170;
      }
      
      finger1.write(posServos);
      finger2.write(posServos);
      finger3.write(posServos);
      finger4.write(posServos);
      finger5.write(posServos);
      delay(time_delay);
     
      break;
      
    case fist:   
      posServos-=speed_open_close;
      if(posServos < 10){
        posServos = 10;
      }
      finger1.write(posServos);
      finger2.write(posServos);
      finger3.write(posServos);
      finger4.write(posServos);
      finger5.write(posServos);
      delay(time_delay);
    
      break;
      
    case waveOut:
      break;
      
    case fingersSpread:
      break;
      
    case doubleTap:
      break;

 }
}
