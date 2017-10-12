//pin definitions
int buttonPin1 = D2;
int buttonPin2 = D3;

int val1 = 0;//int pin1State = LOW;
int val2 = 0;//int pin2State = LOW;
//setup
void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);//pullup resistor in spark
  pinMode(buttonPin2, INPUT_PULLUP);
  Serial.begin(9600);
  Particle.subscribe("pikafeed", feed,"430053001151353338363333"); //communicate with Yuchen's photon
}
// the loop routine runs over and over again forever
void loop() {

  val1 = digitalRead(buttonPin1);
  val2 = digitalRead(buttonPin2);

  if((val1 == LOW) && (val2 == LOW)){
    Spark.publish("pikachu_status","Pikachu is eating too much!", 60);
    delay(5000); 
    }//buttonPin1&2 detected at the sametime 
  else if((val1 == LOW) && (val2 == HIGH)){
  	Spark.publish("pikachu_status", "Pikachu is HAPPY because you are healthy!", 60);
    delay(5000); 
    Particle.publish("pika", "430053001151353338363333"); 
  	} //buttonPin1 detects "healthy food" so LEDPin2 is turned on
  else if((val2 == LOW) && (val1 == HIGH)){
   	Spark.publish("pikachu_status", "Pikachu is SAD because you are eating junk food", 60);
   	Particle.publish("pika2", "430053001151353338363333"); //buttonPin2 detects "junk food" and turn off LEDPin2 on Yuchen's photon
   	delay(5000); 
   	}//buttonPin2 detects "unhealthy food"
  else {
    delay(5000);//nothing happens
   }
  
  val1 = 0;
  val2 = 0;

}

void feed(const char *event, const char *data) {
   	Spark.publish("pikachu_feed", "Good Morning, Pikachu needs to EAT!", 60); // The sun is up and detected and light is turned on so a message is sent to the Pikachu to wake up
}
