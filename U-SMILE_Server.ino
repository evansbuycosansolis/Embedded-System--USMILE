
#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
    int id;
    int x;
} struct_message;

struct_message myData;
struct_message board1;
struct_message board2;

struct_message boardsStruct[2] = {board1, board2};

void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  boardsStruct[myData.id-1].x = myData.x;
  Serial.printf("x value: %d \n", boardsStruct[myData.id-1].x);
  Serial.println();
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
// Access the variables for each board
 int board1X = boardsStruct[0].x;
 int board2X = boardsStruct[1].x;
}
