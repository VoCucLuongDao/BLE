#include <Arduino.h>
#include <bluefruit.h>

#if 0
void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
  
  Serial.println("--------------------------------------------------");
  Serial.println("ProMicro / SuperMini nRF52840 hardware information");
  Serial.println("--------------------------------------------------");

  // Device ID
  Serial.printf("Device ID: %08lX%08lX\n", NRF_FICR->DEVICEID[1], NRF_FICR->DEVICEID[0]);
  
  // Part (Should always be "00052840" for nRF52840 boards)
  Serial.printf("Part: %08lX\n", NRF_FICR->INFO.PART);

  // Variant
  uint32_t variant = NRF_FICR->INFO.VARIANT;
  char variantStr[5] = {
    (char)(variant >> 24),
    (char)(variant >> 16),
    (char)(variant >> 8),
    (char)(variant >> 0), // Yes, shifting by zero is redundant, but it is easier to read!
    '\0'
  };
  Serial.printf("Variant: %s\n", variantStr);

  // Package
  uint32_t pkg = NRF_FICR->INFO.PACKAGE;
  const char* pkg_type;
  switch (pkg) {
    case 0x2004: pkg_type = "QIxx - 7x7 73-pin aQFN"; break;
    case 0x2000: pkg_type = "QFxx - 6x6 48-pin QFN"; break;
    case 0x2005: pkg_type = "CKxx - 3.544 x 3.607 WLCSP"; break;
    default:   pkg_type = "Unknown";
  }
  Serial.printf("Package: %08lX (%s)\n", pkg, pkg_type);

  // RAM
  uint32_t ram_kb = NRF_FICR->INFO.RAM;
  Serial.printf("RAM: %lu KB (%lu bytes)\n", ram_kb, ram_kb * 1024);

  // Flash
  uint32_t flash_kb = NRF_FICR->INFO.FLASH;
  Serial.printf("Flash: %lu KB (%.1f MB)\n", flash_kb, flash_kb / 1024.0); // Show MB with 1 decimal

  // BLE MAC address
  uint8_t mac[6] = {
    (uint8_t)((NRF_FICR->DEVICEADDR[1] >> 8) & 0xFF),
    (uint8_t)((NRF_FICR->DEVICEADDR[1] >> 0) & 0xFF), // Yes, shifting by zero is redundant, but it is easier to read!
    (uint8_t)((NRF_FICR->DEVICEADDR[0] >> 24) & 0xFF),
    (uint8_t)((NRF_FICR->DEVICEADDR[0] >> 16) & 0xFF),
    (uint8_t)((NRF_FICR->DEVICEADDR[0] >> 8) & 0xFF),
    (uint8_t)((NRF_FICR->DEVICEADDR[0] >> 0) & 0xFF) // Yes, shifting by zero is redundant, but it is easier to read!
  };
  Serial.printf("BLE MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  // Internal temperature
  NRF_TEMP->TASKS_START = 1;
  while (!NRF_TEMP->EVENTS_DATARDY);
  int32_t temp = NRF_TEMP->TEMP;
  NRF_TEMP->TASKS_STOP = 1;
  Serial.printf("Internal temperature: %.2f°C\n", temp / 4.0);

  // Bootloader version
  Serial.printf("Bootloader version: %s\n", getBootloaderVersion());
}

void loop() {}
#else

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
  pinMode(22, OUTPUT);
}

void loop() {
  digitalWrite(22, HIGH);
   Serial.println("Led on 11");
  delay(5000);
  digitalWrite(22, LOW);
  Serial.println("Led off 22");
  delay(5000);
}
#endif