
/*
*************************This program is written to test the Flysky FS-i6 transmitter and Flysky FS-iA6B receiver module***********************

Note: This code is used to capture PWM signals from the transmitter for the first four channels


connections :-
D8 -- Ch1 // Roll
D9 -- Ch2 // Pitch
D10 -- Ch3 // Gas
D11 -- Ch4 // Yaw
5V -- +ve
GND -- -ve


*/
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
int receiver_input[5];
unsigned long timer_1, timer_2, timer_3, timer_4, current_time;


void setup()
{
  Serial.begin(9600);
  PCICR |= (1 << PCIE0);                                                    //Set PCIE0 to enable PCMSK0 scan.
  PCMSK0 |= (1 << PCINT0);                                                  //Set PCINT0 (digital input 8) to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT1);                                                  //Set PCINT1 (digital input 9)to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT2);                                                  //Set PCINT2 (digital input 10)to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT3);                                                  //Set PCINT3 (digital input 11)to trigger an interrupt on state change.

}

void loop()
{
  delay(250);
  print_signals();

}

ISR(PCINT0_vect)
{
  current_time = micros();
  //Channel 1=========================================
  if (PINB & B00000001) {                                                   //Is input 8 high?
    if (last_channel_1 == 0) {                                              //Input 8 changed from 0 to 1.
      last_channel_1 = 1;                                                   //Remember current input state.
      timer_1 = current_time;                                               //Set timer_1 to current_time.
    }
  }
  else if (last_channel_1 == 1) {                                           //Input 8 is not high and changed from 1 to 0.
    last_channel_1 = 0;                                                     //Remember current input state.
    receiver_input[1] = current_time - timer_1;                             //Channel 1 is current_time - timer_1.
  }
  //Channel 2=========================================
  if (PINB & B00000010 ) {                                                  //Is input 9 high?
    if (last_channel_2 == 0) {                                              //Input 9 changed from 0 to 1.
      last_channel_2 = 1;                                                   //Remember current input state.
      timer_2 = current_time;                                               //Set timer_2 to current_time.
    }
  }
  else if (last_channel_2 == 1) {                                           //Input 9 is not high and changed from 1 to 0.
    last_channel_2 = 0;                                                     //Remember current input state.
    receiver_input[2] = current_time - timer_2;                             //Channel 2 is current_time - timer_2.
  }
  //Channel 3=========================================
  if (PINB & B00000100 ) {                                                  //Is input 10 high?
    if (last_channel_3 == 0) {                                              //Input 10 changed from 0 to 1.
      last_channel_3 = 1;                                                   //Remember current input state.
      timer_3 = current_time;                                               //Set timer_3 to current_time.
    }
  }
  else if (last_channel_3 == 1) {                                           //Input 10 is not high and changed from 1 to 0.
    last_channel_3 = 0;                                                     //Remember current input state.
    receiver_input[3] = current_time - timer_3;                             //Channel 3 is current_time - timer_3.

  }
  //Channel 4=========================================
  if (PINB & B00001000 ) {                                                  //Is input 11 high?
    if (last_channel_4 == 0) {                                              //Input 11 changed from 0 to 1.
      last_channel_4 = 1;                                                   //Remember current input state.
      timer_4 = current_time;                                               //Set timer_4 to current_time.
    }
  }
  else if (last_channel_4 == 1) {                                           //Input 11 is not high and changed from 1 to 0.
    last_channel_4 = 0;                                                     //Remember current input state.
    receiver_input[4] = current_time - timer_4;                             //Channel 4 is current_time - timer_4.
  }
}




void print_signals() {

  Serial.print("Roll:");
  if (receiver_input[1] - 1480 < 0)Serial.print("<<<");
  else if (receiver_input[1] - 1520 > 0)Serial.print(">>>");
  else Serial.print("--+--");
  Serial.print(receiver_input[1]);


  Serial.print("  Pitch:");
  if (receiver_input[2] - 1480 < 0)Serial.print("^^^");
  else if (receiver_input[2] - 1520 > 0)Serial.print("vvv");
  else Serial.print("--+--");
  Serial.print(receiver_input[2]);


  Serial.print("  Gas:");
  if (receiver_input[3] - 1480 < 0)Serial.print("vvv");
  else if (receiver_input[3] - 1520 > 0)Serial.print("^^^");
  else Serial.print("--+--");
  Serial.print(receiver_input[3]);



  Serial.print("  Yaw:");
  if (receiver_input[4] - 1480 < 0)Serial.print("<<<");
  else if (receiver_input[4] - 1520 > 0)Serial.print(">>>");
  else Serial.print("--+--");
  Serial.println(receiver_input[4]);



}
