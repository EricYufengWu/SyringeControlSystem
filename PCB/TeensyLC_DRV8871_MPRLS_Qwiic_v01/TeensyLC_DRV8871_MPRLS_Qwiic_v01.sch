EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L symbol_library_all:Teensy_LC U1
U 1 1 5E937CBD
P 4500 3600
F 0 "U1" H 4475 4765 50  0000 C CNN
F 1 "Teensy_LC" H 4475 4674 50  0000 C CNN
F 2 "footprint__library_all:Teensy_LC" H 4500 3600 50  0001 C CNN
F 3 "" H 4500 3600 50  0001 C CNN
	1    4500 3600
	1    0    0    -1  
$EndComp
$Comp
L symbol_library_all:Adafruit_DRV8871 U2
U 1 1 5E93B641
P 7900 3100
F 0 "U2" H 8178 3263 50  0000 L CNN
F 1 "Adafruit_DRV8871" H 8178 3172 50  0000 L CNN
F 2 "footprint__library_all:Adafruit_DRV8871" H 7900 3100 50  0001 C CNN
F 3 "" H 7900 3100 50  0001 C CNN
	1    7900 3100
	1    0    0    -1  
$EndComp
$Comp
L symbol_library_all:Adafruit_MPRLS U3
U 1 1 5E93C62D
P 7950 4000
F 0 "U3" H 8378 4188 50  0000 L CNN
F 1 "Adafruit_MPRLS" H 8378 4097 50  0000 L CNN
F 2 "footprint__library_all:Adafruit MPRLS" H 7950 4000 50  0001 C CNN
F 3 "" H 7950 4000 50  0001 C CNN
	1    7950 4000
	1    0    0    -1  
$EndComp
$Comp
L symbol_library_all:Sparkfun_Qwiic_Adapter U4
U 1 1 5E93E539
P 7950 4750
F 0 "U4" H 8278 4863 50  0000 L CNN
F 1 "Sparkfun_Qwiic_Adapter" H 8278 4772 50  0000 L CNN
F 2 "footprint__library_all:Sparkfun_Qwiic_Breakout" H 7950 4750 50  0001 C CNN
F 3 "" H 7950 4750 50  0001 C CNN
	1    7950 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_US RV1
U 1 1 5E9431BE
P 6700 2400
F 0 "RV1" H 6633 2446 50  0000 R CNN
F 1 "R_POT_US" H 6633 2355 50  0000 R CNN
F 2 "footprint__library_all:Linear_POT" H 6700 2400 50  0001 C CNN
F 3 "~" H 6700 2400 50  0001 C CNN
	1    6700 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5E943CF9
P 2550 4250
F 0 "D1" V 2589 4133 50  0000 R CNN
F 1 "LED" V 2498 4133 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 2550 4250 50  0001 C CNN
F 3 "~" H 2550 4250 50  0001 C CNN
	1    2550 4250
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5E944988
P 2900 4250
F 0 "D2" V 2939 4133 50  0000 R CNN
F 1 "LED" V 2848 4133 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 2900 4250 50  0001 C CNN
F 3 "~" H 2900 4250 50  0001 C CNN
	1    2900 4250
	0    -1   -1   0   
$EndComp
Text Label 8000 5100 1    50   ~ 0
VIN
Text Label 7800 5100 1    50   ~ 0
SCL1
Text Label 7900 5100 1    50   ~ 0
SDA1
Text Label 8100 5100 1    50   ~ 0
GND
Wire Wire Line
	7800 4850 7800 5100
Wire Wire Line
	7900 4850 7900 5100
Wire Wire Line
	8000 4850 8000 5100
Wire Wire Line
	8100 4850 8100 5100
Text Label 5900 3600 2    50   ~ 0
3V3
Text Label 5900 3400 2    50   ~ 0
VIN
Text Label 5900 3500 2    50   ~ 0
GND
Text Label 8000 4400 1    50   ~ 0
SCL0
Text Label 8100 4400 1    50   ~ 0
SDA0
Text Label 7900 4400 1    50   ~ 0
GND
Text Label 7700 4400 1    50   ~ 0
3V3
Wire Wire Line
	7700 4150 7700 4400
Wire Wire Line
	7900 4150 7900 4400
Wire Wire Line
	8000 4150 8000 4400
Wire Wire Line
	8100 4150 8100 4400
Text Label 7750 3450 1    50   ~ 0
PWM2
Text Label 7850 3450 1    50   ~ 0
PWM1
Text Label 8050 3450 1    50   ~ 0
GND
Wire Wire Line
	8050 3200 8050 3450
Wire Wire Line
	7850 3200 7850 3450
Wire Wire Line
	7750 3200 7750 3450
Text Label 3050 3100 0    50   ~ 0
PWM2
Text Label 3050 3200 0    50   ~ 0
PWM1
Wire Wire Line
	3300 3200 3050 3200
Wire Wire Line
	3300 3100 3050 3100
Text Label 5900 4100 2    50   ~ 0
SCL0
Text Label 5900 4200 2    50   ~ 0
SDA0
Wire Wire Line
	5650 3500 5900 3500
Wire Wire Line
	5650 3400 5900 3400
Text Label 5900 3700 2    50   ~ 0
SDA1
Text Label 5900 3800 2    50   ~ 0
SCL1
Wire Wire Line
	5650 3700 5900 3700
Wire Wire Line
	5650 3800 5900 3800
$Comp
L Device:R R2
U 1 1 5E952D80
P 2900 4700
F 0 "R2" H 2970 4746 50  0000 L CNN
F 1 "220Ω" H 2970 4655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2830 4700 50  0001 C CNN
F 3 "~" H 2900 4700 50  0001 C CNN
	1    2900 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E954CA3
P 2550 4700
F 0 "R1" H 2620 4746 50  0000 L CNN
F 1 "220Ω" H 2620 4655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2480 4700 50  0001 C CNN
F 3 "~" H 2550 4700 50  0001 C CNN
	1    2550 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3800 2900 3800
Wire Wire Line
	2900 3800 2900 4100
Wire Wire Line
	2900 4400 2900 4550
Wire Wire Line
	3300 3700 2550 3700
Wire Wire Line
	2550 3700 2550 4100
Wire Wire Line
	2550 4400 2550 4550
$Comp
L power:GND #PWR01
U 1 1 5E95AA80
P 2550 5150
F 0 "#PWR01" H 2550 4900 50  0001 C CNN
F 1 "GND" H 2555 4977 50  0000 C CNN
F 2 "" H 2550 5150 50  0001 C CNN
F 3 "" H 2550 5150 50  0001 C CNN
	1    2550 5150
	1    0    0    -1  
$EndComp
Text Label 2550 5050 1    50   ~ 0
GND
Wire Wire Line
	2550 4850 2550 5050
Wire Wire Line
	2900 4850 2900 5050
Wire Wire Line
	2900 5050 2550 5050
Connection ~ 2550 5050
Wire Wire Line
	2550 5050 2550 5150
$Comp
L symbol_library_all:Push_SW S1
U 1 1 5E93EE3A
P 6950 4250
F 0 "S1" H 6950 4525 50  0000 C CNN
F 1 "Push_SW" H 6950 4434 50  0000 C CNN
F 2 "footprint__library_all:Push_SW" H 6950 4250 50  0001 C CNN
F 3 "" H 6950 4250 50  0001 C CNN
	1    6950 4250
	0    -1   -1   0   
$EndComp
$Comp
L symbol_library_all:Push_SW S2
U 1 1 5E96528B
P 7300 4250
F 0 "S2" H 7300 4525 50  0000 C CNN
F 1 "Push_SW" H 7300 4434 50  0000 C CNN
F 2 "footprint__library_all:Push_SW" H 7300 4250 50  0001 C CNN
F 3 "" H 7300 4250 50  0001 C CNN
	1    7300 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 3600 6950 4050
Wire Wire Line
	6950 3600 7300 3600
Wire Wire Line
	7300 3600 7300 4050
Connection ~ 6950 3600
Wire Wire Line
	6950 4450 6950 4500
Wire Wire Line
	7300 4450 7300 4600
$Comp
L Device:R R3
U 1 1 5E970DF4
P 6050 3950
F 0 "R3" H 6120 3996 50  0000 L CNN
F 1 "4.7kΩ" H 6120 3905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5980 3950 50  0001 C CNN
F 3 "~" H 6050 3950 50  0001 C CNN
	1    6050 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5E974AB6
P 6400 3950
F 0 "R4" H 6470 3996 50  0000 L CNN
F 1 "4.7kΩ" H 6470 3905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6330 3950 50  0001 C CNN
F 3 "~" H 6400 3950 50  0001 C CNN
	1    6400 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3600 6050 3600
Wire Wire Line
	5650 4500 6950 4500
Wire Wire Line
	5650 4600 7300 4600
Wire Wire Line
	5650 4100 6050 4100
Wire Wire Line
	6400 4200 6400 4100
Wire Wire Line
	5650 4200 6400 4200
Wire Wire Line
	6050 3800 6050 3600
Connection ~ 6050 3600
Wire Wire Line
	6050 3600 6400 3600
Wire Wire Line
	6400 3800 6400 3600
Connection ~ 6400 3600
Wire Wire Line
	6400 3600 6950 3600
Text Label 6700 2000 3    50   ~ 0
3V3
Text Label 7100 2400 2    50   ~ 0
POT
Text Label 5900 4400 2    50   ~ 0
POT
Wire Wire Line
	5900 4400 5650 4400
Wire Wire Line
	7100 2400 6850 2400
Wire Wire Line
	6700 2250 6700 2000
$Comp
L power:GND #PWR02
U 1 1 5E97E410
P 6700 2800
F 0 "#PWR02" H 6700 2550 50  0001 C CNN
F 1 "GND" H 6705 2627 50  0000 C CNN
F 2 "" H 6700 2800 50  0001 C CNN
F 3 "" H 6700 2800 50  0001 C CNN
	1    6700 2800
	1    0    0    -1  
$EndComp
Text Label 6700 2750 1    50   ~ 0
GND
Wire Wire Line
	6700 2550 6700 2800
$EndSCHEMATC
