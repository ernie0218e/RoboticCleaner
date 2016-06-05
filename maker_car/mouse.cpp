#include "mouse.h"

PS2 mouse(MOUSE_CLK_PIN, MOUSE_DATA_PIN);
Timer mtimer;
volatile char mx, my;

void mouse_init(){
	mouse.write(0xff);  // reset
	mouse.read();  // ack byte
	mouse.read();  // blank */
	mouse.read();  // blank */
	mouse.write(0xf0);  // remote mode
	mouse.read();  // ack
	delayMicroseconds(100);

	mtimer.every(10, checkMouse);
}

void mouseTimerUpdate(){
	mtimer.update();
}

void checkMouse(){
	char mstat;

	/* get a reading from the mouse */
	mouse.write(0xeb);  // give me data!
	mouse.read();      // ignore ack
	mstat = mouse.read();
	mx = mouse.read();
	my = mouse.read();

	/* send the data back up */
	/*Serial.print(mstat, BIN);
	Serial.print("\tX=");
	Serial.print(mx, DEC);
	Serial.print("\tY=");
	Serial.print(my, DEC);
	Serial.println();*/
}
