#include <ps2.h>
/*
 * an arduino sketch to interface with a ps/2 mouse.
 * Also uses serial protocol to talk back to the host
 * and report what it finds.
 */

/*
 * Pin 5 is the mouse data pin, pin 6 is the clock pin
 * Feel free to use whatever pins are convenient.
 */
PS2 mouse(6, 5);
int x, y;
unsigned long time;
/*
 * initialize the mouse. Reset it, and place it into remote
 * mode, so we can get the encoder data on demand.
 */
void mouse_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
}

void mouse_setResolution(){
  mouse.write(0xe8);
  unsigned char ack = 0x00;
  while(ack != 0xfa){
    ack = mouse.read(); //ack byte
  } 
  mouse.write(0x00);
  ack = 0x00;
  while(ack != 0xfa){
    ack = mouse.read(); //ack byte
  }
  delayMicroseconds(100);
}

void mouse_status(){
  mouse.write(0xe9);
  unsigned char ack = 0x00;
  while(ack != 0xfa){
    ack = mouse.read(); //ack byte
  }
  unsigned char b1 = mouse.read();
  unsigned char b2 = mouse.read();
  unsigned char b3 = mouse.read();
  Serial.print(b1, BIN);
  Serial.print("\tResolution=");
  Serial.print(b2, DEC);
  Serial.print("\tSample Rate=");
  Serial.print(b3, DEC);
  Serial.println();
  delayMicroseconds(100);
}

void setup()
{
  Serial.begin(115200);
  mouse_init();
  mouse_setResolution();
  x = y = 0;
  mouse_status();
}

/*
 * get a reading from the mouse and report it back to the
 * host via the serial line.
 */
void loop()
{
  time = micros();
  unsigned char mstat;
  char mx;
  char my;

  /* get a reading from the mouse */
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();

  /*
  int x = 0, y = 0;
  if(mstat & 0x10){
    x = mx | (1 << 8);
  }else{
    x = mx;
  }

  if(mstat & 0x20){
    y = my | (1 << 8);
  }else{
    y = my;
  }*/
  x += mx;
  y += my;
  /* send the data back up */
  Serial.print(mstat, BIN);
  Serial.print("\tX=");
  Serial.print(mx, DEC);
  Serial.print("\tY=");
  Serial.print(my, DEC);
  Serial.println();
  unsigned long t = micros() - time;
  Serial.println(t);
//  delay(20);  /* twiddle */
}
