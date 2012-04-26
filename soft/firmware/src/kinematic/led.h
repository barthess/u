#ifndef LED_H
#define LED_H


//---------------------------------------------------------------------
// INDIVIDUAL LED/SOUND STATES
//---------------------------------------------------------------------
#define _ON		0xFFFF						//led on
#define _OFF	0x0000						//led off
#define BLINK_SLOW		0b1111000011110000	//slow blink
#define BLINK_FAST		0b1010101010101010	//fast blink
#define BLINK_SLOW_ALT	0b0000111100001111	//slow blink alternate
#define BLINK_FAST_ALT	0b0101010101010101	//fast blink alternate



//---------------------------------------------------------------------
// STATUS (COMBINATION OF LED AND SOUND STATES)
//---------------------------------------------------------------------
#define STATUS_NORMAL			STATUS(_ON,_OFF, _OFF)					//normal operation
//Notification status
#define STATUS_INIT				STATUS(BLINK_SLOW,_OFF, _OFF)			//initializing / calibration
#define STATUS_CALIB_ERR1		STATUS(BLINK_SLOW,_ON, _OFF)			//calibration error: device not still
#define STATUS_CALIB_ERR2		STATUS(BLINK_SLOW,BLINK_FAST,BLINK_FAST)//calibration error: rotate device to a different unique position
#define STATUS_ADJUST			STATUS(BLINK_FAST,_OFF, _OFF)			//adjusting settings
//Panic status
#define STATUS_PANIC_BATTERY	STATUS(_OFF,BLINK_SLOW, BLINK_SLOW)		//problem: low battery
#define STATUS_PANIC_SIGNAL		STATUS(_OFF,BLINK_FAST,BLINK_FAST)		//problem: no signal from RC transmitter
#define STATUS_PANIC_TILT		STATUS(_OFF,_ON, _ON)					//problem: extreme tilt possible crash




unsigned char timerCount; 
unsigned char soundOn = 0;
unsigned int soundPattern = _OFF;
unsigned int ledPattern1 = _ON;
unsigned int ledPattern2 = _ON;
volatile unsigned char patternCounter = 0;

#define STATUS(x1,x2,x3) {ledPattern1 = x1; ledPattern2 = x2; soundPattern = x3; }


//Setup pin port, and timer used for led blinking
void status_init(){
	_TRIS(pinSound) = 0;
	_TRIS(pinLed1) = 0;
	_TRIS(pinLed2) = 0;

	//Configure Timer1 1tick = 8/40 =0.2us (40Mhz FCY, 1:8 prescaler)
 	OpenTimer1(T1_ON & T1_GATE_OFF & T1_IDLE_STOP &
               T1_PS_1_8 & 
               T1_SOURCE_INT, 1250	//interrupt every 1250*0.2 = 250us => 1/(250us*2) => 2kHz sound
	);

	ConfigIntTimer1(T1_INT_ON & T1_INT_PRIOR_3);


}

void beep(unsigned int ms,unsigned int pattern){
	soundPattern = pattern;
	__delay_ms(ms);
	soundPattern = _OFF;
}


unsigned int count250us; 	//this is used in IMU module 


//this interrupt counts timer overflows for each channel
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void){
	timerCount++;
	count250us++;
	if(soundOn)	_LAT(pinSound) = !_LAT(pinSound);
	if(0 == timerCount){		//this is called with 250us * 256 = 64ms interval
		soundOn = (soundPattern >> patternCounter) & 0x01; 
		_LAT(pinLed1) = (ledPattern1 >> patternCounter) & 0x01; 
		_LAT(pinLed2) = (ledPattern2 >> patternCounter) & 0x01;
		patternCounter = (patternCounter + 1) % 16;
	}
    IFS0bits.T1IF = 0;    // Clear Timer interrupt flag
}  


#endif
