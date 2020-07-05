/*
 * Here is the code to make Arduino control 14 potentiometers.
 * Potentiometers don't give a stable value so we need to make it a little bit more stable.
 * You will see more details down below the code.
 */

int sensorValue = 0;

/*
Let's declare some variables as int - Arduino reads values from 0 to 1023. 
MIDI CC accetps values from 0 to 127 so the value we read from potentiometers (pots) needs to be
divided by 8 later on
*/ 

int ledBright = 0;
int firstRun = 0;
int potValue0cur = 0;
int potValue1cur = 0;
int potValue2cur = 0;
int potValue3cur = 0;
int potValue4cur = 0;
int potValue5cur = 0;
int potValue6cur = 0;
int potValue7cur = 0;
int potValue8cur = 0;
int potValue9cur = 0;
int potValue10cur = 0;
int potValue11cur = 0;
int potValue12cur = 0;
int potValue13cur = 0;

int midiChan = 176;

void setup()
{
  /*
  Here we are declaring INPUTS and OUTPUTS
  */
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  pinMode(A15, OUTPUT); //this is just for a cool blue LED tha could have been a digital out but hey, let's use just one side of the board.
  
/*
 * There are different ways to send MIDI to your DAW: you can use Hairless MIDI Serial 
 * (a software that will run on your laptop) OR flashing Arduino USB controller.
 * I decided to go for Hairless - is a little simpler but, most important, is way more convenient to use and debug.
 * If you decide to flash your USB Controller, set Serial.begin(31250)*/
  
  Serial.begin(9600); /* Don't forget to set Hairless to 9600 too!*/ 
}

void loop()
{
  /*
   * We want to send the signal only when the pot changes its value so what I do is:
   * - reading the previous value from a potentiometer
   * - reading the current value using analogRead()
   */
  int potValue0prev = potValue0cur; 
  potValue0cur = analogRead(A0);
  
  int potValue1prev = potValue1cur; 
  potValue1cur = analogRead(A1);
  
  int potValue2prev = potValue2cur; 
  potValue2cur = analogRead(A2);
  
  int potValue3prev = potValue3cur; 
  potValue3cur = analogRead(A3);
  
  int potValue4prev = potValue4cur; 
  potValue4cur = analogRead(A4);
  
  int potValue5prev = potValue5cur; 
  potValue5cur = analogRead(A5);
  
  int potValue6prev = potValue6cur; 
  potValue6cur = analogRead(A6);

  int potValue7prev = potValue7cur; 
  potValue7cur = analogRead(A7);

  int potValue8prev = potValue8cur; 
  potValue8cur = analogRead(A8);

  int potValue9prev = potValue9cur; 
  potValue9cur = analogRead(A9);

  int potValue10prev = potValue10cur; 
  potValue10cur = analogRead(A10);

  int potValue11prev = potValue11cur; 
  potValue11cur = analogRead(A11);

  int potValue12prev = potValue12cur; 
  potValue12cur = analogRead(A12);

  int potValue13prev = potValue13cur; 
  potValue13cur = analogRead(A13);

/*
 * Now that I have all the values from all the pots, I'm gonna send the values to a function.
 * 
 * analogPinMidiTX needs 3 arguments:
 * - the channel of the CC you want to send
 * - current value we collected before
 * - previous value we collected before
 * 
 * At the beginning I wanted to avoid to send ANY CC signal by just reading the values not a big problem, just due diligence.
 * 
 * jump to the next block to see what the function does
*/
if (firstRun > 0){
  analogPinMidiTX(1,potValue0cur,potValue0prev);
  analogPinMidiTX(2,potValue1cur,potValue1prev);
  analogPinMidiTX(3,potValue2cur,potValue2prev);
  analogPinMidiTX(4,potValue3cur,potValue3prev);
  analogPinMidiTX(5,potValue4cur,potValue4prev);
  analogPinMidiTX(6,potValue5cur,potValue5prev);
  analogPinMidiTX(7,potValue6cur,potValue6prev);
  analogPinMidiTX(8,potValue7cur,potValue7prev);
  analogPinMidiTX(9,potValue8cur,potValue8prev);
  analogPinMidiTX(10,potValue9cur,potValue9prev);
  analogPinMidiTX(11,potValue10cur,potValue10prev);
  analogPinMidiTX(12,potValue11cur,potValue11prev);
  analogPinMidiTX(13,potValue12cur,potValue12prev);
  analogPinMidiTX(14,potValue13cur,potValue13prev);
}
  delay(100);
  firstRun = 1;

}

/*
 * This funcion checks the two values we pass (to check if they have changed from the previous read).
 * If it changed and the value of the difference |mod| is bigger than 1 (~4mV) we will will check if
 * if the midi value is the same as before so that we don't send the same value twice.
 * Not a problem but it avoids to flood the DAW.
*/

void analogPinMidiTX(int control, int iVal, int iValPrev)
{  
  if(iValPrev != iVal){
    if(abs(iValPrev - iVal) > 1){
      if (iValPrev/8 != iVal/8){ 
        midiSend(midiChan, control, iVal/8);
      }
     }
   }
}

/* 
 *  This function is a pure sender: it needs which MIDI (NOT CC!!) - 176 means you are sending a CC and not a NOTE, for example.
 *  - then we send which CC channel we want to use
 *  - finally the value we want to send.
 *  the last three lines 
*/
void midiSend(byte cc_code, byte control_num, byte value)
{
   Serial.flush();
   Serial.write(cc_code);
   Serial.write(control_num);
   Serial.write(value);
   blinkLed();
}

void blinkLed(){
   analogWrite(A15,255);
   delay(50);
   analogWrite(A15,0);
  }
