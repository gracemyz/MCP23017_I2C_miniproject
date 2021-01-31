  // MCP23017 Example: Interrupt operation.
//
// This code sends an interrupt from the MCP23017
// to an Arduino external interrupt pin when an
// MCP23017 input button press is detected.
// At the same time MCP LEDs are toggled on button
// release.
//
// Copyright : John Main
// Free for non commercial use.

#include <Wire.h>
#include <Adafruit_MCP23017.h>

// MCP23017 setup
#define LED1 7
#define LED2 4
#define LED3 5

// Use input pullup: connect pin directly to GRD
#define PB1 10
#define PB2 14

// Register bits
#define MCP_INT_MIRROR true  // Mirror inta to intb.
#define MCP_INT_ODR    false // Open drain.

// Arduino pins
#define INTPIN 3   // Interrupt on this Arduino Uno pin.


Adafruit_MCP23017 mcp;

//////////////////////////////////////////////
void setup(){

  mcp.begin();      // use default address 0

  pinMode(INTPIN,INPUT);

  mcp.pinMode(LED1, OUTPUT);  // Toggle LED 1
  mcp.pinMode(LED2, OUTPUT);  // Toggle LED 2
  mcp.pinMode(LED3, OUTPUT);     // LED output

  // This Input pin provides the interrupt source.
  mcp.pinMode(PB1,INPUT);   // Button i/p to GND
  mcp.pullUp(PB1,HIGH);     // Puled high ~100k

  // Show a different value for interrupt capture data register = debug.
  mcp.pinMode(PB2,INPUT);   // Button i/p to GND
  mcp.pullUp(PB2,HIGH);     // Puled high ~100k

  // On interrupt, polarity is set HIGH/LOW (last parameter).
  // true, false, low
  mcp.setupInterrupts(MCP_INT_MIRROR, MCP_INT_ODR, LOW); // The mcp output interrupt pin.
  mcp.setupInterruptPin(PB1,CHANGE); // The mcp  action that causes an interrupt.

  mcp.readGPIOAB(); // Initialise for interrupts.
  
  attachInterrupt(digitalPinToInterrupt(INTPIN),isr,FALLING);


}

//////////////////////////////////////////////
// The interrupt routine handles LED1
// This is the button press since this is the only active interrupt.
void isr(){
  uint8_t p,v;
  static uint16_t ledState=0;

  Serial.println("in isr");

   noInterrupts();

   // Debounce. Slow I2C: extra debounce between interrupts anyway.
   // Can not use delay() in interrupt code.
   delayMicroseconds(1000);

   // Stop interrupts from external pin.
   detachInterrupt(digitalPinToInterrupt(INTPIN));
   interrupts(); // re-start interrupts for mcp

   p = mcp.getLastInterruptPin();
   // This one resets the interrupt state as it reads from reg INTCAPA(B).
   v = mcp.getLastInterruptPinValue();

   // Here either the button has been pushed or released.
   if ( p==PB1 && v == 1) { //  Test for release - pin pulled high
      if ( ledState ) {
         mcp.digitalWrite(LED3, LOW);
      } else {
         mcp.digitalWrite(LED3, HIGH);
      }

      ledState = ! ledState;
   }

   attachInterrupt(digitalPinToInterrupt(INTPIN),isr,FALLING);
}


//////////////////////////////////////////////
void loop(){

  delay(300);

  mcp.digitalWrite(LED1, HIGH);
  mcp.digitalWrite(LED2, LOW);

  delay(300);

  mcp.digitalWrite(LED1, LOW);
  mcp.digitalWrite(LED2, HIGH);

}
