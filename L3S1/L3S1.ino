// Lab3_minLEDredSWpress.ino

#define LED_DATA_PIN 12
#define LED_CLOCK_PIN 11
#define SW1_PIN 5

boolean isSwPressed=false;
     
void setup() {
  Serial.begin(9600);  
  Serial.println("Lab3_minLEDredSWpress.ino");
  pinMode(SW1_PIN, INPUT_PULLUP);
  pinMode(LED_DATA_PIN, OUTPUT);
  pinMode(LED_CLOCK_PIN, OUTPUT);
  digitalWrite(LED_DATA_PIN, LOW);
  digitalWrite(LED_CLOCK_PIN, LOW);
} //setup

// =======================================================================
void loop() {
  isSwPressed = !digitalRead(SW1_PIN); 
  if (isSwPressed) {
    //display_color_on_RGB_led(0xFF0000); //red
    //display_color_on_RGB_led(0x00FF00); //blue
    display_color_on_RGB_led(0x0000FF); //green
    
    //Unfortunately, the strip we have is RBG.
    
  }
  else {
    display_color_on_RGB_led(0x000000); // all leds off
  }
}//loop()

// =======================================================================
void display_color_on_RGB_led(unsigned long color) {
  unsigned long bitmask=0UL; // UL unsigned long literal (forces compiler to use long data type)
  unsigned long masked_color_result=0UL;
  
  digitalWrite(LED_CLOCK_PIN,LOW); //start with clock low.
  
  for(int i=23; i>=0; i--) { // clock out one data bit at a time, starting with the MSB first
    bitmask= (1UL<<i);    // build bit mask. Note must use "1UL" unsigned long literal, not "1"
    masked_color_result = color & bitmask; // reveals just one bit of color at time
    boolean data_bit=!(masked_color_result==0); // this is the bit of data to be clocked out.
    digitalWrite(LED_DATA_PIN,data_bit);
    digitalWrite(LED_CLOCK_PIN,HIGH);  
    digitalWrite(LED_CLOCK_PIN,LOW);  
  }
  digitalWrite(LED_CLOCK_PIN,HIGH);  
  delay(1); // after writing data to LED driver, must hold clock line  
            // high for 1 ms to latch color data in led shift register.
}//display_color_on_RGB_led()
