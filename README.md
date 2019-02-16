# R.U.Hacking-2019
IoT Arduino+DragonBoard 

## Introduction
To use the energy more efficiently, the work has been designed to collect and spare the solar energy clearly and automatically.

## Usage

Arduino part includes light sensor, temp sensor (optional), etc. It read the value and return through UART.

DragonBoard performs as a control center, collect every sensors' value and do the calculation. All of the fianl data will be send to server.

The server uses *MQTT* as the solution, it update the data real-time. All of the data can be visualised at https://thingspeak.com/channels/705365

## Acknowledgments 

With the provided API, other excellent works including a APP are done by my teammates. Thank you! @TibiGG @ZarkChen @RaduZervi.

