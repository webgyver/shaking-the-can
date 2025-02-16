#include "I2Cdev.h"
#include "MPU6050.h"
#include <BleGamepad.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mex = 0;
int16_t mey = 0;
int16_t mez = 0;

int16_t mix = 0;
int16_t miy = 0;
int16_t miz = 0;
#define BUTTONPIN 19

BleGamepad bleGamepad("ShakeIT One", "MakerAustria", 100);
BleGamepadConfiguration bleGamepadConfig;
#define numOfButtons 1
#define numOfHatSwitches 0
#define enableX true
#define enableY true
#define enableZ true
#define enableRX false
#define enableRY false
#define enableRZ false
#define enableSlider1 false
#define enableSlider2 false
#define enableRudder false
#define enableThrottle false
#define enableAccelerator false
#define enableBrake false
#define enableSteering false

#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
int previousButton1State = HIGH;
void setup()
{
    pinMode(BUTTONPIN, INPUT_PULLUP);
    bleGamepadConfig.setAutoReport(true);
    bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD);
    bleGamepadConfig.setButtonCount(numOfButtons);
    bleGamepadConfig.setWhichAxes(enableX, enableY, enableZ, enableRX, enableRY, enableRZ, enableSlider1, enableSlider2);
    bleGamepadConfig.setWhichSimulationControls(enableRudder, enableThrottle, enableAccelerator, enableBrake, enableSteering);
    bleGamepadConfig.setHatSwitchCount(numOfHatSwitches);
    bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
    bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
    bleGamepad.begin(&bleGamepadConfig); // Begin gamepad with configuration options
    bleGamepad.setX(0);
    bleGamepad.setY(0);
    bleGamepad.setZ(0);
    bleGamepad.setRX(0);
    bleGamepad.setRY(0);
    bleGamepad.setRZ(0);

// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // use the code below to change accel/gyro offset values

    Serial.println("Updating internal sensor offsets...");
    // -76	-2359	1688	0	0	0
    Serial.print(accelgyro.getXAccelOffset());
    Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset());
    Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset());
    Serial.print("\t"); // 1688
    Serial.print("\n");

    accelgyro.setXAccelOffset(-3023);
    accelgyro.setYAccelOffset(-1601);
    accelgyro.setZAccelOffset(800);

    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
  

    Serial.print(accelgyro.getXAccelOffset());
    Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset());
    Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset());
    Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset());
    Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset());
    Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset());
    Serial.print("\t"); // 0
    Serial.print("\n");

    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    Serial.print(ax);
    Serial.print("\t");
    Serial.print(ay);
    Serial.print("\t");
    Serial.print(az);
    Serial.print("\t");

    /*Serial.print(gx);
    Serial.print("\t");
    Serial.print(gy);
    Serial.print("\t");
    Serial.print(gz);
    Serial.print("\t");

    Serial.print(35000);
    Serial.print("\t");
    Serial.print(-35000);
    Serial.print("\t");*/

    Serial.println();
    if (bleGamepad.isConnected())
    {
        int adjustedValueX = map(ax, -35000, 35000, -32767, 32767);
        bleGamepad.setX(adjustedValueX);
        int adjustedValueY = map(ay, -35000, 35000, -32767, 32767);
        bleGamepad.setY(adjustedValueY);
        int adjustedValueZ = map(az, -35000, 35000, -32767, 32767);
        bleGamepad.setZ(adjustedValueZ);
        /*int adjustedValueRX = map(gx, -1024, 1024, -32767, 32767);
        bleGamepad.setRX(adjustedValueRX);
        int adjustedValueRY = map(gy, -1024, 1024, -32767, 32767);
        bleGamepad.setRY(adjustedValueRY);
        int adjustedValueRZ = map(gz, -1024, 1024, -32767, 32767);
        bleGamepad.setRZ(adjustedValueRZ);*/

        int currentButton1State = digitalRead(BUTTONPIN);
        if (currentButton1State != previousButton1State)
        {
            if (currentButton1State == LOW)
            {
                bleGamepad.press(BUTTON_1);
                Serial.println("press");
            }
            else
            {
                bleGamepad.release(BUTTON_1);
                Serial.println("release");
            }
        }
        previousButton1State = currentButton1State;
    }
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
