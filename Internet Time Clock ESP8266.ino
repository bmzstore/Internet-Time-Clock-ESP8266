#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <time.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0,14,13,15,16); 

const char* ssid     = "xxxxxxxxx";
const char* password = "xxxxxxxxx";
int timezone = 7 * 3600;
int dst = 0;
void setup() {
  u8g2.begin();
  Serial.begin(115200);
  Serial.println("Wifi connecting to ");
  Serial.println( ssid );
  WiFi.begin(ssid,password);
  Serial.println("\nConnecting");
  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");       
  }
  Serial.println("Wifi Connected!");
  Serial.print("IP:");
  Serial.println(WiFi.localIP() );
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for NTP...");

  while(!time(nullptr)){
     Serial.print("*");
     
     delay(1000);
  }
  Serial.println("\nTime response....OK"); 
  delay(1000);

}

void loop() {

  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  
  u8g2.clearBuffer();  
  
  //Frame utama
  u8g2.drawFrame(0,0,128,64);
  
  //Jam Utama
  u8g2.setFont(u8g2_font_timB24_tf); 
  u8g2.setCursor(5,41);
  if( p_tm->tm_hour<10)
  u8g2.print("0");
  u8g2.print(p_tm->tm_hour); 
  u8g2.print(":");
  if( p_tm->tm_min <10)
  u8g2.print("0");
  u8g2.print(p_tm->tm_min);
  u8g2.print(":");
  if( p_tm->tm_sec <10)
  u8g2.print("0");
  u8g2.print(p_tm->tm_sec);
  
  //Hari
  u8g2.drawLine(3, 15, 45,15);
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(9,12,"B_Mz");  
  
  
  //Tanggal
  u8g2.drawLine(52, 15, 124,15);
  u8g2.setFont(u8g2_font_ncenB10_tr); 
  u8g2.setCursor(52,14);
  if( p_tm->tm_mday <10)
  u8g2.print("0");
  u8g2.print(p_tm->tm_mday);
  u8g2.print("/");
  if( p_tm->tm_mon <10)
  u8g2.print("0");
  u8g2.print(p_tm->tm_mon + 1);
  u8g2.print("/");
  u8g2.print(p_tm->tm_year + 1900);

  
  //Weather
  u8g2.setFont(u8g2_font_chikita_tf); 
  u8g2.drawStr(3,48,"Temp");  
  u8g2.drawStr(3,55,"Hum");  
  u8g2.drawStr(3,62,"Wind");  
  u8g2.drawStr(26,48,":31"); 
  u8g2.drawStr(26,55,":47");  
  u8g2.drawStr(26,62,":23");  
  u8g2.drawStr(41,48,"C ");  
  u8g2.drawStr(41,55,"%");  
  u8g2.drawStr(41,62,"km/h");  

  //tombol OK
  u8g2.drawFrame(73,45,21,16);
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(75,57,"OK");  
  
  //Tombol panah Kiri
  u8g2.drawLine(96,53,108,45);
  u8g2.drawLine(96,53,108,61);
  u8g2.drawLine(108,46,108,60);
  
  //Tombol panah Kanan
  u8g2.drawLine(112,45,124,53);
  u8g2.drawLine(112,61,124,53);
  u8g2.drawLine(112,60,112,46);
  u8g2.sendBuffer();         
  delay(1000);  

}
