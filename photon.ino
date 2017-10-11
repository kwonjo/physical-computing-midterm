
//pin definitions
int buttonPin1 = D2;
int buttonPin2 = D3;
int LEDPin2 = D4;
void lightup(const char *, const char *);
//int pin1State = LOW;
//int pin2State = LOW;
int val1 = 0;
int val2 = 0;

//setup
void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(LEDPin2, OUTPUT);
  Particle.subscribe("pika", lightup, MY_DEVICES);
  
  Serial.begin(9600);
}
// the loop routine runs over and over again forever
void loop() {

  val1 = digitalRead(buttonPin1);
  val2 = digitalRead(buttonPin2);

  if((val1 == LOW) && (val2 == LOW)){
    Spark.publish("pikachu_status","Pikachu is eating too much!", 60, PRIVATE);
    delay(5000); 
    }//PIR1&2 detected at the sametime 
  else if((val1 == LOW) && (val2 == HIGH)){
  	Spark.publish("pikachu_status", "Pikachu is HAPPY because you are healthy!", 60, PRIVATE);
    delay(5000); 
  	} //button1 detects "healthy food"
  else if((val2 == LOW) && (val1 == HIGH)){
   	Spark.publish("pikachu_status", "Pikachu is SAD because you are eating junk food", 60, PRIVATE);
   	delay(5000); 
   	}//button2 detects "unhealthy food"
  else {
    Particle.publish("pika", "light", PRIVATE);
    delay(5000);
   }
  
  val1 = 0;
  val2 = 0;

}

void lightup(const char *event, const char *data) {
    
  if(strcmp(data,"light")==0){
    digitalWrite(LEDPin2, HIGH);
  }
  else{
    digitalWrite(LEDPin2, LOW);
  }
}

