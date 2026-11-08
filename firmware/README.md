# Single-servo tester

This is a serial-only bench test. It does not generate a gait. Designed for a classic ESP32 DevKit, PCA9685 at I²C address 0x40, SDA GPIO21, SCL GPIO22; verify your actual board. A different ESP32 may require different pins and a different PlatformIO board.

Install VS Code and PlatformIO, open the `firmware` directory, connect ESP32 over USB, build/upload the `esp32dev` environment, and open its serial monitor at 115200 baud with newline enabled. Disconnect the battery/servo supply while connecting wires. Use a stable 5 V current-limited bench supply for the first one-servo test. PCA9685 VCC = 3.3 V, SDA = 21, SCL = 22, GND = common ground; V+ = separate regulated servo supply (see build guide). Verify servo plug polarity before applying power.

With the servo detached from the leg mechanism, apply servo power, then enter:

```
help
arm
set 0 90
set 0 85
set 0 95
off
```

Only channels 0–7 and nominal angles 45–135 are allowed. The actual angles and safe limits depend on the servo. Stop if it buzzes, jams or overheats. Remove the horn, center at 90, then fit the horn in its intended neutral position; turn off power before attaching or adjusting it. Never force a servo to a mechanical end stop.

Outputs switch off at startup, on `off`, and after 30 seconds without an accepted `set` command or `arm`. The servo power rail remains live, and switching signals off releases holding torque, so support the robot. A hardware power switch is necessary. Use a proper emergency power cutoff; this serial tool is not a safety controller. A reset or I²C failure may not immediately remove servo power. Disconnect the supply if anything behaves unexpectedly. Commands and calibration are not persistent; tune individual limits before use.
