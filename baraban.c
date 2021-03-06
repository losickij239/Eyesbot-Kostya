#pragma config(Sensor, S1,     ,               sensorSoundDB)
#pragma config(Sensor, S2,     ,               sensorTouch)
#pragma config(Sensor, S4,     ,               sensorTouch)
#pragma config(Motor,  motorA,          degree,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          rotation,      tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	ubyte joystick[4];
	ubyte value[3];

	nMotorEncoder[degree] = 0;
	nMotorEncoder[rotation] = 0;

	int position = 0; // 0 - open, 1 - close


	while(true)
	{
		// -------- sound --------
		// value[0] - jump
		// value[1] - closed or opened
		// value[2] - start of eye show
		value[0] = 0;
		if (SensorValue[S1] > 60) {
			value[0] = 1;
			PlaySound(soundBlip);
			wait1Msec(300);
		}

		if (SensorValue[S2] == 1) {
			if (position == 0) position = 1;
			else position = 0;
			wait1Msec(300);
		}

		value[1] = position;

		value[2] = 0;
		if (nNxtButtonPressed == 2)
			value[2] = 1;

		cCmdMessageWriteToBluetooth(2, value, 3, mailbox1);
		wait1Msec(1);

		// -------- omni ---------
		int deg = nMotorEncoder[degree];
		int rot = nMotorEncoder[rotation];

		if (rot >= 0) joystick[0] = 1;
		else joystick[0] = 0;
		joystick[1] = abs(rot);

		if (deg >= 0) joystick[2] = 1;
		else joystick[2] = 0;
		joystick[3] = abs(deg);

		if (SensorValue[S4] != 1) {
			joystick[1] = 0;
			joystick[3] = 0;
		}

		cCmdMessageWriteToBluetooth(3, joystick, 4, mailbox1);

		nxtDisplayCenteredBigTextLine(1, "%d", position);
		nxtDisplayCenteredBigTextLine(3, "%d", rot);
		nxtDisplayCenteredBigTextLine(5, "%d", deg);
		wait1Msec(10);
	}
}
