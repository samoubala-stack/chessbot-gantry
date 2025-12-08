# Chess Bot Gantry – README

## 1. Overview

This project is a simple “chess move to G-code” bridge for my chess-playing gantry robot.  
The idea is that I can type in a move like `e2e4` on my computer, and this program will:

1. Convert that move into G-code for the X/Y gantry.
2. Tell a second Arduino when to lower/raise a small linear actuator and turn an electromagnet on or off, so the robot can pick up and drop a piece.

There are two Arduinos involved:

- **Arduino #1 with CNC Shield** – runs **GRBL** and controls X and Y motion.
- **Arduino #2 (picker controller)** – runs my custom firmware and controls:
  - the micro linear actuator (Z axis),
  - the electromagnet for grabbing pieces.

The TypeScript program (`index.ts`) connects to both Arduinos over serial ports and sends thew commands to complete the movement of the gantry and linear actuator/magnet.

## 2. Hardware Setup (High Level)

Here’s how I have the hardware wired:

- **Arduino + CNC Shield**
  - Flashed with standard **GRBL**.
  - Stepper motor drivers plugged in for X and Y.
  - Connected to the computer over USB (this is the `moverPort` in the code).

- **Picker Arduino (Z + magnet)**
  - Controls a 4-relay board.
  - Two relays drive the linear actuator up/down.
  - One relay powers the electromagnet.
  - It also connects to the computer over USB (this is the `pickerPort` in the code).

To install the libraries for the code just type from a terminal: 
'npm install'

Note - if your running on windows your ports will be something like "COM3" or "COM4", whereas if you're running on mac or linux your ports will be something like "/dev/tty...", be sure to update the port ids in the file index.ts before running the program.

To list serial ports in macos use the command: ls /dev/tty.*

Then to execute the program just type from a terminal:
'npm start'

Please note that before running the program you need to deploy the firmware on the arduinos. This can be done via their browser based IDE: https://www.arduino.cc/en/software/

The code for each ardunio's firmware is under the folder titled "ardunio".

If you're interested in seeing my CAD design for the gantry assembly, just check the link below:
https://cad.onshape.com/documents/51d0f3b84eea7fc07b3f1cca/w/85c02975dd9b1a8164abf66b/e/5872399e0b1451f6f41b2e4a?renderMode=0&uiState=69364e048171a2be9486bcbe

Finally, below is a link to an unlisted youtube video which serves as the project overview:
https://youtu.be/27eNOatXeEQ