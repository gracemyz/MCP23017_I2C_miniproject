/*
 * Demonstrate reading/writing capabilities of MCP. 
 * Flashes two LEDs in synchronicity, while polling normally open pushbutton
 * When button press detected, third LED turns on.
 * This sketch does not use interrupts, so the third LED's behaviour is laggy and unreliable.
 */

#include <Wire.h>
#include <Adafruit_MCP23017.h>

// Connect MCP pins to positive end of LED, through 10K resister to GRD
#define MCP_LED1 7
#define MCP_LED2 5
#define MCP_LED3 4

// Use input pullup: connect pin directly to GRD
#define PUSH_BUTTON 10

Adafruit_MCP23017 mcp;

void setup() {
  
  Serial.begin(9600);
  Wire.begin();
  mcp.begin();      // Default device address 0

  mcp.pinMode(MCP_LED1, OUTPUT);  
  mcp.pinMode(MCP_LED2, OUTPUT);  
  mcp.pinMode(MCP_LED3, OUTPUT);  

  mcp.pinMode(PUSH_BUTTON, INPUT);
  mcp.pullUp(PUSH_BUTTON,HIGH);     // Pulled high to ~100k
  
  Serial.println("plz");
}


void loop() {
  
  mcp.digitalWrite(MCP_LED1, HIGH);
  mcp.digitalWrite(MCP_LED3, HIGH);
  delay(300);
  mcp.digitalWrite(MCP_LED1, LOW);
  mcp.digitalWrite(MCP_LED3, LOW);

  delay(300);

   // internal pullup -- pressing the button connects input to ground.
   if (mcp.digitalRead(PUSH_BUTTON)) {
     mcp.digitalWrite(MCP_LED2,LOW);
   } else {
     mcp.digitalWrite(MCP_LED2, HIGH);
   }

}
