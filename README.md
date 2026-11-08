# Pebble 🐾

A small, battery-powered four-legged robot pet. Build one reliable leg, then the base and four legs; add a camera and AI after it can stand and move. This initial repository contains a **servo test tool**, not autonomous walking or a trained robot.

## Start here

1. Read [build and shopping guide](docs/BUILD.md) before buying all eight servos.
2. Identify your ESP32 board and test its 3.3 V I²C pins. The firmware defaults to a classic ESP32 DevKit (GPIO 21/22), **not** every ESP32 variant.
3. Build the first leg, wire one servo to channel 0 and test it with [firmware instructions](firmware/README.md).
4. Measure weight, stand test, and servo temperatures before committing to all eight motors.
5. See [architecture](docs/ARCHITECTURE.md) for future camera, replaceable AI and training data. No cloud AI or training is implemented yet.

Work on a table with the robot supported and away from edges. Servos can move suddenly; disconnect servo power before changing wiring or horns. Mechanical design, motor choice, battery and walking gait require physical validation.
