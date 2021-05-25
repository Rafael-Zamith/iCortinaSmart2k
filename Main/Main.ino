
#include <WiFi.h>
#include <PubSubClient.h>
#include <Stepper.h>
// Update these with values suitable for your network.
const char* ssid = "F - IoT";//put your wifi ssid here
const char* password = "wFKHrQu7Ty2g";//put your wifi password here
const char* mqtt_server = "192.168.15.10";
const char* clientId = "cortinaRafa";
const char* userName = "mqtt";
const char* passWord = "1234";

float luz = 0;
int value = 0;
long lastMsg = 0;
int last = 0;

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// initialize the stepper library on D1,D2,D5,D6
Stepper myStepper(stepsPerRevolution, 5, 19, 17, 18);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Command from MQTT broker is: [");
  Serial.print(topic);
  int p =(char)payload[0]-'0';
  int stepperLoop = 0;
  // step one revolution  in one direction:
  if(p==1) 
  {
    if (last != 1){
      myStepper.step(+stepsPerRevolution);
      }
    if (digitalRead(13) == HIGH){
    myStepper.step(stepsPerRevolution);
    Serial.print("  clockwise]" );
    
    last = 1;}
   }
  // step one revolution in the other direction:
  else if(p==2)
  {if (last != 2){
      myStepper.step(-stepsPerRevolution);
      }
    if (digitalRead(13) == HIGH){
    myStepper.step(-stepsPerRevolution);
    Serial.print("  counterclockwise]" );
    last = 2;}
  }
  else if(p==3)
  {
    if (last != 1){
      myStepper.step(+stepsPerRevolution);
      }
    Serial.print("  clockwise loop: " );
    while (digitalRead(13) == HIGH){
      myStepper.step(+stepsPerRevolution);
      Serial.print(stepperLoop);
      Serial.print(" ");
      delay(50);
      
    }
    last = 1;
    Serial.print("]");
  }
  else if(p==4)
  {
    Serial.print("  counterclockwise loop: " );
    if (last != 2){
      myStepper.step(-stepsPerRevolution);
      }
    while (digitalRead(13) == HIGH) {
      myStepper.step(-stepsPerRevolution);
      Serial.print(stepperLoop);
      Serial.print(" ");
      delay(50);
      
    }
    last = 2;
    Serial.print("]");
  }
  else if(p==0)
  {
    digitalWrite (5,LOW);
    digitalWrite (19,LOW);
    digitalWrite (18,LOW);
    digitalWrite (17,LOW); 
    Serial.print("  off]" );
  }
  Serial.println();
   
}
 
//  Serial.println();
 //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(clientId,userName,passWord))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("cortina");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()

void setup() {
  pinMode(13, INPUT_PULLUP);
  pinMode(34, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  // set the speed at 80 rpm:
  myStepper.setSpeed(80);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  
  if (now - lastMsg > 20000) {
    lastMsg = now;
    ++value;
    char dat[6];
    luz = analogRead(34);
   int result = map(luz, 0, 4000, 0, 255);
   char *msg = dtostrf(result, 6, 2, dat);
   Serial.println(msg);
   client.publish("luz", msg);
   Serial.print(last);
   if (digitalRead(13) == LOW)
   {
     if (last == 1)
     {
       client.publish("cortina", "Aberto");
     }
     if (last == 2)
     {
       client.publish("cortina", "Fechado");
     }
    }
  }
}
