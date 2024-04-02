#include<cvzone.h>
#include<WiFi.h>
#include<esp_now.h>

int case;

//data structure
typedef struct struct_message{
  int a;
} struct_message;


//create an object for struct data
struct_message myData;


//Callback function 
void OnDataRec(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&myData,incomingData,sizeof(myData));


  // here we can set teh data values received
  // case = myData.a 
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
