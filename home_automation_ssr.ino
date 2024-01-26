#include "DFRobot_DF2301Q.h"
#define relay1 2 // relay is connected to the digital pin D2
#define relay2 3 // relay is connected to the digital pin D3
#define relay3 4 // relay is connected to the digital pin D4
#define relay4 5 // relay is connected to the digital pin D5

//I2C communication
DFRobot_DF2301Q_I2C asr; // activates the I2C mode of the voice recognition module


void setup() {
  Serial.begin(115200);  
  
  pinMode(relay1, OUTPUT);    //Init relay pin to output mode
  pinMode(relay2, OUTPUT); 
  pinMode(relay3, OUTPUT); 
  pinMode(relay4, OUTPUT); 

  digitalWrite(relay1, LOW);  //Set light pin to low 
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  
  // Init the sensor
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");
 
  /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(7);
 
  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);
 
  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(20);
 
  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);
 
   asr.playByCMDID(1);   // Wake-up command
 
  /**
     @brief Play the corresponding reply audio according to the ID
     @param CMDID - command word ID
  */
  //asr.playByCMDID(23);  // Command word ID
}
 
void loop() {
  /**
     @brief Get the ID corresponding to the command word 
     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
  */
  uint8_t CMDID = asr.getCMDID();
  Serial.println(CMDID);
  switch (CMDID) {
    //relay1 for fan
    case 75:   // turn on the fan
      digitalWrite(relay1, HIGH);  
      break;
 
    case 76:  // turn off the fan
      digitalWrite(relay1, LOW);  
      break;
      
     //relay2 for light
    case 103:  // turn on the light 
      digitalWrite(relay2, HIGH);  
      break;
     
    case 104: // turn off the light
      digitalWrite(relay2, LOW);  
      break;
      
      //relay3 for ac 
      //(max limit 100-200watt mini cooling system can run)
    case 124:     // turn on ac
      digitalWrite(relay3, HIGH);  
      break;
 
    case 125:  // turn off ac 
      digitalWrite(relay3, LOW);  
      break;
      
      //relay4 for mini home theater system 
    case 90:   // turn on the speaker
      digitalWrite(relay4, HIGH);  
      break;
 
    case 91:  // turn off the speaker
      digitalWrite(relay4, LOW);  
      break;
 
           
    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");  //Printing command ID
        Serial.println(CMDID);
      }
  }
  delay(300);
}
