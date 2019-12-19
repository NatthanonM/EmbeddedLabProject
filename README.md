## EmbbedLabProject
# Project description
Objective of this project is to invent automatical watering plants system in greenhouse for controling and monitoring the humidity's greenhouse by communication thruogh the internet. The system can be used for reducing cost of the labors by the notifications and user's setting.
# Sensors
Input: 1 Humidity Sensor
Output: 1 Water Pump
# Boards
1. ESP8266-Node-MCU
2. STM32F407G-Disc1 (STM32F4DISCOVERY)
# Brief description of processes of the system
1. User input perferred humidity through website of the system.
2. Humidity sensor send humidity to system controllers.
3. The system controllers calculate the difference of current humidity and input fron user.
4. The system controllers control output of water pump.
5. The system controllers send current humidity every peroid of time to the website.
