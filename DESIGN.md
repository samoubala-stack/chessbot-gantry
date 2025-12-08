# DESIGN.md

## Overview and Project Pivot

My original project idea was a small “vision duck” robot that would track an object using a Raspberry Pi and a camera. Unfortunately, during early testing the robot drove off my desk and the camera broke. Since I didn’t have time to replace it and rebuild the vision pipeline in time for the deadline, I decided to switch to another personal robotics project I had already been working on, a chess robot gantry system. This ended up being a much more complete and stable system to show for the final project anyway.  

The rest of this document explains how the chess gantry works under the hood and why I made the design choices I did.


## High-Level System Architecture

The robot is basically made up of four parts working together:

1. **Mechanical Gantry**
   - X and Y movement comes from belt-driven stepper motors running on aluminum rails with v-groove wheels.
   - Z movement is handled by a small linear actuator with an electromagnet attached.
   - Most of the brackets and mounts are custom 3D-printed.

2. **Electronics**
   - One Arduino with a CNC shield runs GRBL and controls the X/Y steppers.
   - Another Arduino controls the linear actuator and electromagnet through a 4 relay module.
   - Everything runs off a 24V supply with a power converter for the Z-axis parts.

3. **Software Pipeline**
   - A TypeScript program reads a chess move and turns it into G-code for the gantry.
   - The same program sends simple text commands to the second Arduino for Z-axis actions.

4. **Piece Manipulation**
   - Each chess piece has a small steel disk so the electromagnet can pick it up.
   - The general sequence is: lower, magnet on, lift, move, lower, magnet off, lift, re-home.


## Key Design Decisions

### 1. Using a gantry instead of a robotic arm
A gantry was much easier for me to build from scratch. Linear motion is simpler to control, and it’s easier to keep things square and consistent. The main mechanical challenge was keeping the X-axis straight since it’s driven from one side, but after a few redesigns of the carriage, I got it running smoothly.

### 2. Electromagnet over a claw
I experimented with the idea of a claw, but it required too much precision and would likely bump into nearby pieces. An electromagnet is much more forgiving. I standardized the heights of all the pieces and added metal disks so pickup and placement became very reliable.

### 3. Splitting control between two Arduinos
GRBL is great at motion control, so I didn’t want to overload it with extra tasks. Separating the Z-axis onto a second Arduino made debugging easier and kept the timing predictable on both ends. Also I had a hardware constrains since the CNC shield took up all the ports on the ardunio.

### 4. Converting chess notation into real movement
The TypeScript program does most of the brainwork. It:
1. Converts squares (like `a1` or `e4`) into coordinates,
2. Generates the right G-code to move between them,
3. Sends the G-code to GRBL,
4. Sends pickup/drop commands to the other Arduino at the right moments.

It took some trial and error to tune the step size and timing so the magnet always lined up with each piece.

---

## Reliability and Iterations

As I developed the system, I had to fix a few issues:

- Stepper drift, solved by adding a consistent “return to origin” approach.
- Piece height inconsistencies, redesigned and reprinted pieces.
- Some 3D-printed parts flexed, strengthened them with thicker walls.
- Belt tension drifted, redesigned idler brackets.

Each change made the robot noticeably more repeatable and predictable.

---

## Breakdown of Software Responsibilities

### GRBL Arduino
- Reads and executes G-code.
- Handles X/Y stepper motion, acceleration, and timing.

### TypeScript Program
- Parses the move input.
- Calculates the required movement.
- Sends commands to both Arduinos.
- Coordinates all timing and state for a full move cycle.

### Second Arduino (Picker Controller)
- Runs timed sequences for the actuator.
- Controls the electromagnet.
- Listens for simple commands like `AS_PICK`, `AT_DROP`, etc.


## Why This Fits CS50

Even though this project involves hardware, the core challenge was writing software that could reliably interact with the real world. I had to manage:

- Parsing and converting input,
- Serial communication with two devices at once,
- Synchronizing motion and timing,
- Handling errors that come from mechanical issues, not just code.

These kinds of interactions between hardware and software made the project feel like a very natural fit for CS50, especially in terms of systems thinking and problem-solving.


## Future Improvements

If I keep working on this, I’d like to:

- Add computer vision so the robot can “see” the board state,
- Use a real chess engine,
- Replace the actuator with a stepper-driven Z stage,
- Machine the moving parts out of aluminum for stiffness,
- Add proper sensors and endstops for closed-loop control.


## Closing Notes

Even though I had to pivot from the original plan, this gantry project represents a complete system I’ve been building and improving over time. It combines mechanical design, electronics, and software programming into one working robot. For this class, the TypeScript program and the coordination logic are the main “CS50” components, but the whole system comes together to create something that feels meaningful and fun to use.
