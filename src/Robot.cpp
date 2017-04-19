#include <WPILib.h>
#include "XboxJoystickMap.h"

class Robot: public frc::IterativeRobot {
public:

  VictorSP* frontLeft;
  VictorSP* frontRight;
  VictorSP* backLeft;
  VictorSP* backRight;

  Solenoid* fire0;
  Solenoid* fire1;
  Solenoid* fire2;
  Solenoid* fire3;

  Joystick* joystick;
  Joystick* override;

  RobotDrive* driveTrain;

  Relay* flashlight;

  DoubleSolenoid* moveIntakeMech;
  Spark* intakeRoller;

  DoubleSolenoid *shifter;

	void RobotInit() {
	  frontLeft = new VictorSP(0);
	  frontRight = new VictorSP(2);
	  backLeft = new VictorSP(1);
	  backRight = new VictorSP(3);

	  fire0 = new Solenoid(0);
	  fire1 = new Solenoid(1);
	  fire2 = new Solenoid(2);
	  fire3 = new Solenoid(3);

	  joystick = new Joystick(0);
	  driveTrain = new RobotDrive(frontLeft, backLeft, frontRight, backRight);

	  override = new Joystick(1);

	  flashlight = new Relay(1);

	  moveIntakeMech = new DoubleSolenoid(6, 7);
	  intakeRoller = new Spark(4);

	  shifter = new DoubleSolenoid(4, 5);
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */



	void AutonomousInit() override {
	}

	void AutonomousPeriodic() {}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

	  double left, right;
	  if(override->GetRawButton(XboxButtonLeftBumper)){
	    left = override->GetRawAxis(XboxAxisLeftStickY);
      right = override->GetRawAxis(XboxAxisRightStickX);
	  } else {
	    left = joystick->GetRawAxis(XboxAxisLeftStickY);
	    right = joystick->GetRawAxis(XboxAxisRightStickX);
	  }
    driveTrain->ArcadeDrive(left, right);

    shifter->Set(override->GetRawAxis(XboxAxisRightTrigger) > 0.5 ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);

	  if(override->GetRawButton(XboxButtonX)){
      moveIntakeMech->Set(DoubleSolenoid::kReverse);
      intakeRoller->Set(-0.5);
    } else {
      moveIntakeMech->Set(DoubleSolenoid::kForward);
      intakeRoller->Set(0);
    }

	  if(override->GetRawButton(XboxButtonRightBumper)){
      bool fire = joystick->GetRawButton(XboxButtonRightBumper);
      fire0->Set(fire);
      fire1->Set(fire);
      fire2->Set(fire);
      fire3->Set(fire);

      if(joystick->GetRawButton(XboxButtonLeftBumper)){
        flashlight->Set(Relay::kOn);
      }else{
        flashlight->Set(Relay::kOff);
      }
	  }else{
	    fire0->Set(0);
	    fire1->Set(0);
	    fire2->Set(0);
	    fire3->Set(0);
	  }
	}
	void TestPeriodic() {}

};

START_ROBOT_CLASS(Robot)
