/******************************/
/* Proyecto de grado - UCUDAL */
/* LDR + GSM lab              */
/*                            */
/* Santiago Caamano - 2014    */
/******************************/

#include <GSM.h>

#define PINNUMBER "6045"
#define INPUTPIN A0

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

// mobile number where the msg will be sent
char mobileNumber[20] = "+59898365370";  
char txtMessage[20] = "Vehicle detected!";

void setup()
{ 
  // initialize serial communications
  Serial.begin(9600);

  Serial.println("LDR + GSM lab - UCUDAL 2014");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    }
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized correctly");
}

void loop()
{
  int analogValue = analogRead(INPUTPIN);
  //Serial.println(analogRead); // For debugging purposes only
  if (analogValue < 100) { //Please adapt the value according to light conditions in the room
    Serial.print("\n\nVehicle detected, sending SMS to: ");
    Serial.print(mobileNumber);
    sendSMS(mobileNumber, txtMessage);
  }
}

void sendSMS(char* number, char* message){
  sms.beginSMS(number);
  sms.print(message);
  sms.endSMS(); 
  Serial.println("\nMessage sent!");  
}
