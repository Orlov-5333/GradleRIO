#include "WPILib.h"
#include "MyHeader.h"

using namespace frc;

// From MyHeader.h
int add(int a, int b) {
    return a + b;
}

class Robot: public IterativeRobot {
public:
  Talon *left_motor;//create pointer
  Talon *right_motor;
  RobotDrive *my_robot;
  int left_motor_port = 1, right_motor_port = 2;

  Joystick *stick;
  int stick_port = 3;
  double direction = 0;
  double mag = 0;
  double leftPow = 0;
  double rightPow = 0;
  int clockPolarity = -1;
  int forwardAngle = 90;
  double angle = 0;

    Robot() { }

    void RobotInit() {
      left_motor = new Talon(left_motor_port);//use constructor
      right_motor = new Talon(right_motor_port);
      my_robot = new RobotDrive(left_motor, right_motor);

      stick = new Joystick(stick_port);
     }

    void TestPeriodic() {
      while(true){
        direction = stick->GetDirectionDegrees();
        mag = stick->GetMagnitude();

        angle = (direction - forwardAngle)*clockPolarity;
        if(angle<-180){
          angle = angle+360;
        }
        if(angle>180){
          angle = angle-360;
        }

        if(angle>=-180 && angle<-60){
          rightPow = angle/60 + 2;
        }

        if(angle>=-60 && angle<=0){
          rightPow = 1;
        }

        if(angle>0 && angle<120){
          rightPow = angle/60*-1 + 1;
        }

        if(angle>=120 && angle<=180){
          rightPow = -1;
        }

        if(angle>=-180 && angle<=-90){
          leftPow = -1;
        }

        if(angle>-90 && angle <0){
          leftPow = angle/60 + 1;
        }

        if(angle>=0 && angle <=60){
          leftPow = 1;
        }

        if(angle>60 && angle<=180){
          leftPow = -angle/60 + 2;
        }

        leftPow = leftPow*mag;
        rightPow = rightPow*mag;
        my_robot->TankDrive(leftPow,rightPow);


      }
    }
};

START_ROBOT_CLASS(Robot)
