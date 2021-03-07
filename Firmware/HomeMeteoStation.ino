// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       HomeMeteoStation.ino
    Created:	18.02.2021 11:58:41
    Author:     DESKTOP-ANDREW\Andrew
*/

// Define User Types below here or use a .h file
//
#include <Adafruit_CCS811.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <U8glib.h>
#include <Adafruit_Si7021.h>
#include "BME280.h"
#include <Wire.h>

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST);	// Dev 0, Fast I2C / TWI
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0);	// Dev 0, Fast I2C / TWI

Adafruit_Si7021 Si7021;
Adafruit_BMP280 BMP280;
Adafruit_CCS811 CCS811;

void setup()
{
	Serial.begin(9600);	

	Si7021.begin();
	BMP280.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
	CCS811.begin();

	Si7021.setHeatLevel(SI_HEATLEVEL_HIGH);
	Si7021.heater(false);
	//CCS811.setBaseline(0u);
	//CCS811.setDriveMode(2);
}

// Add the main program code into the continuous loop() function
void loop()
{
	float temperature1 = Si7021.readTemperature();
	float humidity = Si7021.readHumidity();

	float temperature2 = BMP280.readTemperature();
	float pressure = BMP280.readPressure() / 100;
	float altitude = BMP280.readAltitude();

	while (CCS811.readData());

	float co2 = CCS811.geteCO2();
	float tvoc = CCS811.getTVOC();
	uint16_t baseline = CCS811.getBaseline();

	Serial.print("Temp 1: " + String(temperature1) + " | ");
	Serial.print("Temp 2: " + String(temperature2) + " | ");
	Serial.print("Pressure: " + String(pressure) + " | ");
	Serial.print("ALT: " + String(altitude) + " | ");
	Serial.print("CO2: " + String(co2) + " | ");
	Serial.print("TVOC: " + String(tvoc) + " | ");
	Serial.print("Baseline: " + String(baseline) + " | ");
	Serial.print("RH: " + String(humidity) + " | \n");

	SendToDisplay(temperature1, temperature2, pressure, altitude, co2, tvoc, humidity, baseline);

	delay(1000);
}

void SendToDisplay(float temperature1, float temperature2, float pressure, float altitude, float co2, float tvoc, float humidity, uint16_t baseline)
{
	u8g.firstPage();
	do {
		char temperatureDisplay[50];
		char humidityDisplay[50];
		char pressureDisplay[50];
		char altitudeDisplay[50];
		char co2Display[50];
		char tvocDisplay[50];
		char baselineDisplay[50];

		("t 1/2: " + String(temperature1) + "/"+ String(temperature2) + " *C").toCharArray(temperatureDisplay, 50);
		("RH: " + String(humidity) + " %").toCharArray(humidityDisplay, 50);

		("P: " + String(pressure) + " hPa").toCharArray(pressureDisplay, 50);
		("ALT: " + String(altitude) + " m").toCharArray(altitudeDisplay, 50);

		("C02: " + String(co2)).toCharArray(co2Display, 50);
		("TVOC: " + String(tvoc)).toCharArray(tvocDisplay, 50);
		("B: " + String(baseline)).toCharArray(baselineDisplay, 50);

		u8g.setFont(u8g_font_courR08);
		u8g.drawStr(0, 10, temperatureDisplay);
		u8g.drawStr(0, 20, humidityDisplay);
		u8g.drawStr(0, 30, pressureDisplay);
		u8g.drawStr(0, 40, altitudeDisplay);
		u8g.drawStr(0, 50, co2Display);
		u8g.drawStr(0, 60, tvocDisplay);
		u8g.drawStr(70, 20, baselineDisplay);

	} while (u8g.nextPage());
}
