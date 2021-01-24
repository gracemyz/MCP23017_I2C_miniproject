
#include <Wire.h>
#include <Adafruit_MCP23017.h>

#define MCP_LED1 3

Adafruit_MCP23017 mcp;

void setup() {
  
  Serial.begin(9600);
  Wire.begin();
  mcp.begin();      // Default device address 0

  mcp.pinMode(MCP_LED1, OUTPUT);  
  mcp.digitalWrite(MCP_LED1, HIGH);

  // mcp.pinMode(5,INPUT);   // Button i/p to GND
  // mcp.pullUp(5,HIGH);     // Pulled high to ~100k
  
  Serial.println("plz");
}


void loop() {
  mcp.digitalWrite(MCP_LED1, HIGH);
  delay(300);
  mcp.digitalWrite(MCP_LED1, LOW);
  delay(300);
  
  //Serial.println(mcp.digitalRead(0));
  // Serial.print("test");
  // mcp.digitalWrite(MCP_LEDTOG2, LOW);

  // delay(300);

  // mcp.digitalWrite(MCP_LEDTOG1, LOW);
  // mcp.digitalWrite(MCP_LEDTOG2, HIGH);

  // // Transfer input pin state to LED1
  // if (mcp.digitalRead(MCP_INPUTPIN)) {
  //   mcp.digitalWrite(MCP_LED1,HIGH);
  // } else {
  //   mcp.digitalWrite(MCP_LED1,LOW);
  // }

}
