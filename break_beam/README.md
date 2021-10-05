## buzzer

### Purpose

- Used to verify noise level of buzzer

### Function

- Provides an audible cue for the ticket checker, signaling whether or not a valid ticket has been scanned

## triple_beam

### Purpose

- Used to check if 3 IR LEDs can run on the same GPIO PWM pin without issue

- Used to measure maximum reliable distance between IR LED and receiver

### Function

- Assists with managing access control, in lieu of a gate or physical barrier

- Once broken, the first 2 beams will trigger the RFID scanner to verify guests ticket

- If a valid ticket is scanned, the third beam is shut off and buzzer will chime accordingly

- If no/invalid ticket is scanned, the third beam will be broken (instead of shut off) and buzzer will chime accordingly
