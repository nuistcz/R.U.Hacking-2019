#include <CurieBLE.h>
#include <CurieIMU.h>

BLEService customService( "BEEF0000-0000-0000-0000-00000000ACCE" );
BLETypedCharacteristic<bool> ledChar( "BEEF0001-0000-0000-0000-0000000001ED", BLERead | BLEWrite );
BLECharacteristic accelChar( "BEEF0001-0000-0000-0000-00000000ACCE", BLERead | BLENotify, "0,0,0" );

int sensorPin = A1;    // select the input pin for the potentiometer
int ledPin = A0;      // select the pin for the LED
int sensorValue,sensor2Value,sensor3Value = 0;  // variable to store the value coming from the sensor
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println( "Starting up..." );
  pinMode( ledPin, OUTPUT );

  CurieIMU.begin( );
  CurieIMU.setAccelerometerRange( 2 );
  Serial.println( "IMU started." );

  BLE.begin( );

  BLE.setLocalName( "BTDemo" );
  BLE.setAdvertisedService(customService);

  customService.addCharacteristic(accelChar);
  customService.addCharacteristic(ledChar);

  // Add our service.
  BLE.addService(customService);
  // These do nothing other than provide some debug logging.
  BLE.setEventHandler(BLEConnected, logCentralConnect);
  BLE.setEventHandler(BLEDisconnected, logCentralDisconnect);

  ledChar.setEventHandler(BLEWritten, ledCharChanged);
  ledChar.setValue(false);

  // Advertise.
  BLE.advertise( );

  Serial.println( "BLE waiting for central connection." );

  
}

void loop() {
  sensorValue = analogRead(A0);
  sensor2Value = analogRead(A1);
  sensor3Value = analogRead(A2);
  Serial.print("sensor1 = ");
  Serial.print(sensorValue);
  Serial.print("\t   sensor2 = ");
  Serial.print(sensor2Value);
  Serial.print("\t sensor3 = ");
  Serial.println(sensor3Value);
  delay(200);
  static unsigned long lastWrite = 0;
  while ( BLE.central( ) ) {
    unsigned long now = millis( );
    BLE.poll( );
    if ( now - lastWrite > 100 ) {
      lastWrite = now;
      float x, y, z;
      CurieIMU.readAccelerometerScaled(x, y, z);
      String packedData = String(x, 3) + "," + String(y, 3) + "," + String(z, 3);
      accelChar.setValue( packedData.c_str( ) );
    }
  }
}

void logCentralConnect(BLEDevice central) {
  Serial.println( "Central connected: " + central.address( ) );
}

void logCentralDisconnect(BLEDevice central) {
  Serial.print( "Central disconnected: " + central.address( ) );
}

void ledCharChanged(BLEDevice central, BLECharacteristic characteristic) {
  bool value = static_cast<bool>(*characteristic.value( ));
  Serial.println( "Led value updated to: " + String(value) );
  digitalWrite( ledPin, value );
}
