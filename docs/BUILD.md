# First build: body and one leg

## Structure without a 3D printer

Make a lightweight sandwich body from two pieces of 3 mm plywood or 3 mm PVC foam board, about 150 × 90 mm. These are initial dimensions, not a proven cut template; leave room for the actual motors and battery. Plywood is stiffer; PVC foam board is easy to cut but reinforce motor screws with small plywood washers. Make spacers from wood blocks or aluminium standoffs. You can use corrugated cardboard for a quick size mockup, but it can crush or flex around servos; laminate and reinforce it for temporary tests. Avoid sharp wire or using unsupported wire as a load-bearing leg.

For one experimental leg use two positional 180° micro servos: hip servo fixed to body, knee servo fixed to an upper link driven by the hip, lower link attached to the knee horn. Both output shafts point sideways, perpendicular to the robot's forward direction, so the leg moves forward/back and bends in the same vertical plane. This 2-DOF arrangement has no sideways joint. Make short, stiff links of plywood, aluminium flat strip, or craft sticks laminated together; start near 35–45 mm between joint centers and 35–45 mm knee to foot. Use screws through servo mounting tabs and supplied horns, lock nuts, and a rubber foot. Build attachment so wires cannot foul rotating joints; knee servo wiring must have a loose loop. Use horn screws and match mounting holes to the servo actually bought. Do not rely on glue to hold a loaded servo horn. Exact hole positions depend on purchased parts.

Cut four identical legs only after the first operates without binding. Fit all four at the body's corners, two joints each. Keep the battery low and central, and the payload light. Short links reduce torque demand, but the total weight and torque are unknown until measured. Four legs with only pitch joints may be difficult to balance while lifting a leg: a successful standing test does not guarantee walking. Build and tune a slow, supported crawl later; consider revised mechanics if it cannot keep its center of mass over support feet.

## What to buy first

- Two **180° positional** MG90S metal-gear micro servos with horns and screws for one leg; not continuous rotation. Quality and torque vary. Buy six more after the test. At 4.8 V a commonly listed MG90S stall torque is about 1.8 kg·cm; do not design for stall torque as a continuous load. Mechanical friction and dynamic motion need margin.
- One PCA9685 I²C 16-channel servo driver (check it has headers/terminal blocks).
- Thin plywood or PVC foam board; small M2/M3 screws, nuts, washers, cable ties, servo extension wires, small rubber pads and suitable hand tools. Use a drill and eye protection.
- A regulated 5 V bench supply for initial testing, with sufficient current for the test and shared ground. Do not power servo motors from the ESP32 3.3 V pin or a small breadboard supply.
- After one-leg success: six matching servos and a battery/power system. Size it after measuring actual weight, stall current and peak current. For eight servos, plan initially around a regulated 5 V supply capable of at least 8–10 A **if compatible with the chosen servos and distributor**, then measure and revise. Neither servo load nor supply capability has been validated. Ensure battery, converter, wiring, connectors, switch and fuse are rated for measured load. A protected 2S pack with an appropriate 2S charger/BMS and a rated 5 V high-current UBEC is one option. Never connect a 2S pack directly to a 5 V servo, ESP32 or PCA9685 servo rail. A USB power bank is generally a poor assumption for large simultaneous servo peaks.
- Camera later: exact choice depends on your ESP32 model. A separate ESP32-CAM can stream frames over Wi-Fi to a laptop/phone/server; it is another board, requires appropriate programming/power, and is not yet integrated. Some ESP32 variants need different camera wiring.

## Power and connections

Battery → correctly rated protection, fuse and switch → 5 V high-current regulator → PCA9685 servo V+ and servo ground. Use a separately regulated clean supply suitable for your exact ESP32 board; use a common ground between supplies, ESP32 and PCA9685. PCA9685 VCC goes to ESP32 3.3 V, SDA to GPIO21 and SCL to GPIO22 on a classic DevKit. Check breakout pull-ups go to 3.3 V; never put 5 V on ESP32 GPIO. Servos plug into PCA9685 channels with correct signal/V+/ground orientation. Check voltage with a multimeter before connecting. A PCA9685 breakout's traces and terminals may not safely carry total stall current: use a properly rated power distribution harness and check each connector's rating.

1. Test ESP32 and PCA9685 with servo supply disconnected.
2. Measure 5 V at servo rail and verify polarity; power off and attach one servo.
3. Suspend the servo/leg, use the serial tester, fit the horn at neutral, and check slow small movements.
4. Repeat for each motor and record each safe direction and limits. Add load gradually; stop for excessive heat, buzzing, resets or flexing.
5. Assemble four legs and verify supported standing before attempting walking; never leave battery charging unattended.
