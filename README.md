# BlueStaq-Challenge
Developed a Elevator Simulator in C++.

This project includes two C++ elevator simulators: Simple and Collective Control.
The Simple version processes requests in the order they arrive (FIFO). The Collective version uses a smarter approach—continuing in its current direction to serve all requests along the way before reversing, choosing the nearest pending floor when idle. Both run over 10 floors and simulate movement tick-by-tick, logging elevator actions to the console.

Assumptions

The elevator operates between floors 1–10 and starts on floor 1.
Each tick represents one time step, during which the elevator either moves one floor or stops to open its doors. Invalid floors are ignored, and all requests are treated equally (no distinction between hall or car calls). New requests are added before each movement step.

Unimplemented Features

This simulation omits real-world details like multiple elevators, door timing, capacity limits, or passenger behavior. It doesn’t model up/down hall buttons, energy use, or advanced dispatching. The goal is to demonstrate elevator logic and scheduling, not full system realism.
