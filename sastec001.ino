
#include <UIPEthernet.h> // Ethernet Kutuphanesi
#include <OneWire.h> // Sensor icin OneWire Kutuphanesi
// #define DEBUG
// **** ETHERNET ****
// Arduino Uno pin: 10 = CS, 11 = MOSI, 12 = MISO, 13 = SCK
// Ethernet MAC adresi
byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };
EthernetClient client;
char server[] = “192.168.1.100”; // sunucu ip (localhost yazmayin, kod arduinoya yuklendiginde localhost arduinoyu isaret edecektir)
unsigned long PreviousMillis = 0;
unsigned long interval = 300000; // Bekleme suresi (1 dakika)
unsigned long intervalTime;
// **** Sicaklik Sensoru ****
// Sensor data pini (pin 2 olarak ayarlandi)
OneWire ds(2);
void setup() {
#ifdef DEBUG
Serial.begin(9600);
#endif
Ethernet.begin(mac);
intervalTime = millis();
#ifdef DEBUG
Serial.println(“Teknotezgah.com – Sicaklik Olcumu”);
Serial.println(“-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n”);
Serial.print(“IP Adresi : “);
Serial.println(Ethernet.localIP());
Serial.print(“Alt Ag Maskesi : “);
Serial.println(Ethernet.subnetMask());
Serial.print(“Varsayilan Ag Gecidi: “);
Serial.println(Ethernet.gatewayIP());
Serial.print(“DNS Server IP : “);
Serial.println(Ethernet.dnsServerIP());
#endif
}
void loop() {
unsigned long CurrentMillis = millis();
if ( CurrentMillis < PreviousMillis )
{
intervalTime = CurrentMillis+interval;
}
if ( CurrentMillis > intervalTime )
{
intervalTime = CurrentMillis + interval;
if (!client.connect(server, 80)) {
#ifdef DEBUG
Serial.println(“-> Baglanti Hatasi: Reset ENC!”);
#endif
Enc28J60.init(mac);
} else {
client.stop();
}
if (client.connect(server, 80))
{
#ifdef DEBUG
Serial.println(“-> Baglandi”);
#endif
client.print( “GET /veriekle.php?”);
TemperaturesToGetVariables();
client.println( ” HTTP/1.1″);
client.println( “Host: 192.168.1.100″ );
client.print(” Host: “);
client.println(server);
client.println( “Connection: close” );
client.println();
client.println();
client.stop();
}
else
{
#ifdef DEBUG
Serial.println(“–> Baglanti Hatasi !!”);
#endif
//Enc28J60.init(mac);
}
}
else
{
Ethernet.maintain();
}
}
void TemperaturesToGetVariables(void)
{
byte counter;
byte present = 0;
byte sensor_type;
byte data[12];
byte addr[8];
float celsius;
byte sensorcounter;
ds.reset_search();
sensorcounter = 1;
while ( ds.search(addr) )
{
if (sensorcounter>1) client.print(“&”);
client.print(“serial”);
client.print(sensorcounter);
client.print(“=”);
#ifdef DEBUG
Serial.print(” Sensor : “);
Serial.println(sensorcounter);
Serial.print(” Serial : “);
#endif
for( counter = 0; counter < 8; counter++)
{
if (addr[counter]<10) client.print(“0”);
client.print(String(addr[counter], HEX));
if (counter<7) client.print(“%20”);
#ifdef DEBUG
if (addr[counter]<10) Serial.print(“0″);
Serial.print(String(addr[counter], HEX));
if (counter<7) Serial.print(” “);
#endif
}
#ifdef DEBUG
Serial.println();
#endif
client.print(“&temperature”);
client.print(sensorcounter);
client.print(“=”);
// Check CRC
if (OneWire::crc8(addr, 7) != addr[7])
{
client.println(“ERROR”);
}
else
{
ds.reset();
ds.select(addr);
ds.write(0x44);
delay(750);
present = ds.reset();
ds.select(addr);
ds.write(0xBE);
for ( counter = 0; counter < 9; counter++)
{
data[counter] = ds.read();
}
int16_t raw = (data[1] << 8) | data[0];
byte cfg = (data[4] & 0x60);
if (cfg == 0x00) raw = raw & ~7;
else if (cfg == 0x20) raw = raw & ~3;
else if (cfg == 0x40) raw = raw & ~1;
celsius = (float)raw / 16.0;
client.print(celsius);
#ifdef DEBUG
Serial.print(” Temperature: “);
Serial.print(celsius);
Serial.println(” C”);
#endif
}
sensorcounter++;
}
return;
}
