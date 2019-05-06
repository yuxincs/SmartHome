# SmartHome

A SmartHome Simulation For Interface Course Project, Includes Upper and Lower Machine.

<p align="center">
  <img alt="SmartHome screenshot" src="https://user-images.githubusercontent.com/10323518/30979553-f4eb835e-a44b-11e7-83d3-8515fe76a33b.gif"></img>
</p>

## Overall
The SmartHome system is basically a simulation which includes following factors:

Temperature\Brightness is simulated by slide rhostat value.

Light is simulated by an LED.

Air conditioning is simulated by a motor.

## Chips Used

8251 - Serial Communicator

8253 - Counter

8255 - Parallel I/0

0809 - A/D Converter

## Upper Machine
The upper machine is responsible for receiving the collected information about temperature and brightness, analyze them and give the corresponding command back to the lower machine.

## Lower Machine
The lower macine is responsible for receiving the command from the upper machine and write the command to the port to control the corresponding models. Meanwhile collect the temperature and brightness information uninterruptedly and send the information back to upper machine. Note that temperature and brightness is simulated by the slide rhostat.

## FPGA
The code for FPGA is responsible for converting a 3-bit number into corresponding 7-seg byte for the 7-segment LED to display the fan speed.

## License
[MIT](https://github.com/yxwangcs/SmartHome/blob/master/LICENSE).
