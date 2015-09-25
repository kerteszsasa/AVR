@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\SASA\Attiny13_v-tail\labels.tmp" -fI -W+ie -o "C:\SASA\Attiny13_v-tail\vtail.hex" -d "C:\SASA\Attiny13_v-tail\vtail.obj" -e "C:\SASA\Attiny13_v-tail\vtail.eep" -m "C:\SASA\Attiny13_v-tail\vtail.map" "C:\SASA\Attiny13_v-tail\vtail.asm"
