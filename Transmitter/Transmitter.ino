
#include<esp_now.h>
#include<WiFi.h>
#include<cvzone.h>

SerialData serialdata('COM6',115200)


//Varibles for send data

int data_send;

// MAC address of receiver

uint8_t receiver[] = {}



//define the data structure
typedef struct struct_message{
  int a[1];
} struct_message;

struct_message myData;


//peer info

esp_now_peer_info_t peerInfo;

//callback function called when data is sent

void OnDataSent(const uint8_t *mac_adrr, esp_now_send_status_t status){
  serial.print("\r\nLast Packet send :\t");
  serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery success" : "Delivery Fail");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //initialize ESP-NOW
  if (esp_now_init() != ESP_OK){
    Serial.println("Error initializing ESP_NOW")
    return;
  }
  //Register the send callbakc
  esp_now_register_send_cb(OnDataSent);

  //register peer
  memcpy(peerInfo.peer_addr, receiver,6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
  Serial.println("Failed to add peer")}
  return;

}

void loop() {
  // put your main code here, to run repeatedly:

  serialData.get(valRec);
  myData.a = valRec[0];

  //send data
  esp_err_t result = esp_now_send(receiver, (uint8_t *) &myData, sizeof (myData));
  delay(10)



}
