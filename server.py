#!/usr/bin/env python
# encoding = utf-8
from requests_html import HTMLSession
import serial, time
import requests
 
# r = requests.get('http://cuiqingcai.com')

session = HTMLSession()


ser = serial.Serial('/dev/cu.usbmodem1431',9600,timeout = 60)
while True:
	line = ser.readline()
	sensor1 = int(line.split()[2])
	sensor2 = int(line.split()[5])
	sensor3 = int(line.split()[8])
	print(session.get('https://api.thingspeak.com/update?api_key=OR7JTEY0731XSPBW&field1='+str(sensor1)+'&field2='+str(sensor2)+'&field3='+str(sensor3)))
	time.sleep(1)


ser.close()