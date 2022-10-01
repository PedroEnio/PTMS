EESchema Schematic File Version 4
EELAYER 30 0
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
L Converter_ACDC:HLK-PM01 PS1
U 1 1 6093BBD0
P 6100 5400
F 0 "PS1" H 6100 5725 50  0000 C CNN
F 1 "HLK-PM01" H 6100 5634 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 6100 5100 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=54" H 6500 5050 50  0001 C CNN
	1    6100 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	3300 1650 3300 2100
Wire Wire Line
	3500 4200 3500 4100
$Comp
L pspice:R R1
U 1 1 6095A6AB
P 4900 1750
F 0 "R1" H 4832 1704 50  0000 R CNN
F 1 "10k" H 4832 1795 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4900 1750 50  0001 C CNN
F 3 "~" H 4900 1750 50  0001 C CNN
	1    4900 1750
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C1
U 1 1 6095BCAD
P 4550 2400
F 0 "C1" H 4668 2446 50  0000 L CNN
F 1 "10uF" H 4668 2355 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D8.0mm_H11.5mm_P3.50mm" H 4588 2250 50  0001 C CNN
F 3 "~" H 4550 2400 50  0001 C CNN
	1    4550 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1450 4900 1500
Wire Wire Line
	4900 2000 4900 2050
Wire Wire Line
	4550 2250 4550 2050
Wire Wire Line
	4550 2050 4900 2050
Connection ~ 4900 2050
Wire Wire Line
	4900 2050 4900 2150
Wire Wire Line
	4900 4200 4900 2800
Connection ~ 3500 4200
Wire Wire Line
	4550 2550 4550 2800
Wire Wire Line
	4550 2800 4900 2800
Connection ~ 4900 2800
Wire Wire Line
	4900 2800 4900 2650
Wire Wire Line
	5200 2050 5200 2150
$Comp
L pspice:R R2
U 1 1 6095ADFB
P 4900 2400
F 0 "R2" H 4832 2354 50  0000 R CNN
F 1 "10k" H 4832 2445 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4900 2400 50  0001 C CNN
F 3 "~" H 4900 2400 50  0001 C CNN
	1    4900 2400
	-1   0    0    1   
$EndComp
Connection ~ 5200 2050
$Comp
L pspice:R R6
U 1 1 60977A06
P 5550 3450
F 0 "R6" H 5482 3404 50  0000 R CNN
F 1 "100k" H 5482 3495 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 5550 3450 50  0001 C CNN
F 3 "~" H 5550 3450 50  0001 C CNN
	1    5550 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	3500 4200 4550 4200
$Comp
L pspice:R R7
U 1 1 60978240
P 5550 4000
F 0 "R7" H 5482 3954 50  0000 R CNN
F 1 "10k" H 5482 4045 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 5550 4000 50  0001 C CNN
F 3 "~" H 5550 4000 50  0001 C CNN
	1    5550 4000
	-1   0    0    1   
$EndComp
$Comp
L Transformer:TRANSF1 TR1
U 1 1 6098676E
P 6300 3700
F 0 "TR1" H 6300 4081 50  0000 C CNN
F 1 "220/9 V" H 6300 3990 50  0000 C CNN
F 2 "Transformer_THT:Transf_9V_150mA" H 6300 3700 50  0001 C CNN
F 3 "" H 6300 3700 50  0001 C CNN
	1    6300 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2050 6000 2050
$Comp
L Device:CP C2
U 1 1 6099EB5A
P 4800 4700
F 0 "C2" H 4918 4746 50  0000 L CNN
F 1 "10uF" H 4918 4655 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D8.0mm_H11.5mm_P3.50mm" H 4838 4550 50  0001 C CNN
F 3 "~" H 4800 4700 50  0001 C CNN
	1    4800 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4550 4800 4350
Wire Wire Line
	5050 4350 5050 4450
Wire Wire Line
	4800 4850 4800 5100
Wire Wire Line
	5050 5100 5050 4950
$Comp
L pspice:R R4
U 1 1 6099EB64
P 5050 4700
F 0 "R4" H 4982 4654 50  0000 R CNN
F 1 "10k" H 4982 4745 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 5050 4700 50  0001 C CNN
F 3 "~" H 5050 4700 50  0001 C CNN
	1    5050 4700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4800 4350 5050 4350
$Comp
L pspice:R R3
U 1 1 609A4FC3
P 5050 4000
F 0 "R3" H 4982 3954 50  0000 R CNN
F 1 "10k" H 4982 4045 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 5050 4000 50  0001 C CNN
F 3 "~" H 5050 4000 50  0001 C CNN
	1    5050 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 4350 5050 4250
Connection ~ 5050 4350
Wire Wire Line
	4550 5100 4550 4200
Connection ~ 4800 5100
Connection ~ 4550 4200
Wire Wire Line
	4550 4200 4900 4200
Wire Wire Line
	5550 3750 5550 3700
Wire Wire Line
	5050 4350 5550 4350
Wire Wire Line
	5550 4350 5550 4250
Wire Wire Line
	6100 3500 6000 3500
Wire Wire Line
	6000 3500 6000 3200
Wire Wire Line
	6000 3200 5550 3200
Wire Wire Line
	6100 4350 5550 4350
Connection ~ 5550 4350
Connection ~ 5550 3700
Wire Wire Line
	6700 3650 6650 3650
Wire Wire Line
	6500 3650 6500 3500
Wire Wire Line
	6700 3750 6500 3750
Wire Wire Line
	6500 3750 6500 3900
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 60935FAC
P 3400 3100
F 0 "A1" H 3400 2011 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 3400 1920 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 3400 3100 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3400 3100 50  0001 C CNN
	1    3400 3100
	1    0    0    -1  
$EndComp
$Comp
L pspice:R R5
U 1 1 609727C3
P 5200 2400
F 0 "R5" H 5132 2354 50  0000 R CNN
F 1 "50k" H 5132 2445 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 5200 2400 50  0001 C CNN
F 3 "~" H 5200 2400 50  0001 C CNN
	1    5200 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6650 3650 6650 5300
Wire Wire Line
	6650 5300 6500 5300
Connection ~ 6650 3650
Wire Wire Line
	6650 3650 6500 3650
Wire Wire Line
	2450 1650 3300 1650
Wire Wire Line
	6500 5500 6700 5500
Wire Wire Line
	4900 2050 5200 2050
Wire Wire Line
	6000 2550 6700 2550
Wire Wire Line
	5200 2650 6700 2650
Connection ~ 6700 3750
$Comp
L Connector_Generic:Conn_01x02 TP1
U 1 1 6093F3CB
P 6900 3650
F 0 "TP1" H 6980 3642 50  0000 L CNN
F 1 "Conn_01x02" H 6980 3551 50  0000 L CNN
F 2 "TerminalBlock_Altech:Altech_AK300_1x02_P5.00mm_45-Degree" H 6900 3650 50  0001 C CNN
F 3 "~" H 6900 3650 50  0001 C CNN
	1    6900 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 SCT13
U 1 1 6094029A
P 6900 2550
F 0 "SCT13" H 6980 2542 50  0000 L CNN
F 1 "Conn_01x02" H 6980 2451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6900 2550 50  0001 C CNN
F 3 "~" H 6900 2550 50  0001 C CNN
	1    6900 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 DS18B20
U 1 1 6097DC10
P 2050 3450
F 0 "DS18B20" H 1968 3125 50  0000 C CNN
F 1 "Conn_01x03" H 1968 3216 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2050 3450 50  0001 C CNN
F 3 "~" H 2050 3450 50  0001 C CNN
	1    2050 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2250 3350 2250 2550
Wire Wire Line
	2250 3550 2250 4200
Wire Wire Line
	2450 5500 5350 5500
Wire Wire Line
	2450 1650 2450 2350
Wire Wire Line
	3500 5300 3500 4200
Wire Wire Line
	6100 4350 6100 3900
Wire Wire Line
	2250 3450 2350 3450
Wire Wire Line
	2850 3450 2850 3400
Wire Wire Line
	2850 3400 2900 3400
Wire Wire Line
	5200 3100 3900 3100
Wire Wire Line
	2250 4200 3400 4200
Wire Wire Line
	5350 5500 5350 3750
Wire Wire Line
	5350 3750 5050 3750
Connection ~ 5350 5500
Wire Wire Line
	5350 5500 5700 5500
$Comp
L pspice:R R8
U 1 1 60A1D619
P 2350 2800
F 0 "R8" H 2282 2754 50  0000 R CNN
F 1 "4.7k" H 2282 2845 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 2350 2800 50  0001 C CNN
F 3 "~" H 2350 2800 50  0001 C CNN
	1    2350 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2250 2550 2350 2550
Wire Wire Line
	2350 3050 2350 3450
Connection ~ 2350 3450
Wire Wire Line
	2350 3450 2850 3450
Connection ~ 5700 5500
$Comp
L Connector_Generic:Conn_01x05 SIM800L1
U 1 1 60E67DB0
P 2800 6350
F 0 "SIM800L1" H 2718 6767 50  0000 C CNN
F 1 "Conn_01x05" H 2718 6676 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 2800 6350 50  0001 C CNN
F 3 "~" H 2800 6350 50  0001 C CNN
	1    2800 6350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3000 6450 4350 6450
$Comp
L pspice:R R9
U 1 1 60E6595A
P 3950 4900
F 0 "R9" H 3882 4854 50  0000 R CNN
F 1 "10k" H 3882 4945 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 3950 4900 50  0001 C CNN
F 3 "~" H 3950 4900 50  0001 C CNN
	1    3950 4900
	1    0    0    -1  
$EndComp
$Comp
L pspice:R R10
U 1 1 60E6E1B9
P 4150 4900
F 0 "R10" H 4082 4854 50  0000 R CNN
F 1 "20k" H 4082 4945 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4150 4900 50  0001 C CNN
F 3 "~" H 4150 4900 50  0001 C CNN
	1    4150 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3950 4650 3950 4550
Wire Wire Line
	3950 4550 4050 4550
Wire Wire Line
	4150 4550 4150 4650
Wire Wire Line
	4050 4550 4050 4050
Wire Wire Line
	4050 4050 4300 4050
Connection ~ 4050 4550
Wire Wire Line
	4050 4550 4150 4550
Wire Wire Line
	3950 5150 3950 6350
Wire Wire Line
	3950 6350 3000 6350
Wire Wire Line
	3400 4100 3400 4200
Connection ~ 3400 4200
Wire Wire Line
	3400 4200 3500 4200
Wire Wire Line
	4550 5100 4800 5100
Wire Wire Line
	5200 2650 5200 3100
Connection ~ 5200 2650
Wire Wire Line
	6000 2050 6000 2550
Connection ~ 4150 5300
Wire Wire Line
	4150 5300 3500 5300
Wire Wire Line
	3850 3950 3850 6250
Wire Wire Line
	3000 6250 3850 6250
Wire Wire Line
	3850 3950 4200 3950
$Comp
L Converter_DCDC:MP1584_Module U3
U 1 1 60E85003
P 4850 6000
F 0 "U3" H 4875 6275 50  0000 C CNN
F 1 "MP1584_Module" H 4875 6184 50  0000 C CNN
F 2 "Converter_DCDC:MP1584_BuckModule" H 4850 6250 50  0001 C CNN
F 3 "" H 4850 6250 50  0001 C CNN
	1    4850 6000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5700 6100 5700 5500
Connection ~ 5550 5300
Wire Wire Line
	5550 5300 4150 5300
Wire Wire Line
	5700 5300 5550 5300
Wire Wire Line
	5550 5950 5550 5300
Wire Wire Line
	5550 5950 5250 5950
Wire Wire Line
	5700 6100 5250 6100
Wire Wire Line
	4400 6100 4150 6100
Wire Wire Line
	4800 5100 5050 5100
Wire Wire Line
	4150 5150 4150 5300
Wire Wire Line
	6700 3750 6700 5500
Wire Wire Line
	2250 2550 2250 2350
Wire Wire Line
	2250 2350 2450 2350
Connection ~ 2250 2550
Connection ~ 2450 2350
Wire Wire Line
	2450 2350 2450 5500
Wire Wire Line
	3300 1650 3300 1450
Wire Wire Line
	3300 1450 4900 1450
Connection ~ 3300 1650
Wire Wire Line
	4100 3700 4100 3500
Wire Wire Line
	4100 3500 3900 3500
Wire Wire Line
	4100 3700 5550 3700
Wire Wire Line
	4350 6450 4350 3400
Wire Wire Line
	3900 3400 4350 3400
Wire Wire Line
	4300 4050 4300 3200
Wire Wire Line
	4300 3200 3900 3200
Wire Wire Line
	4200 3300 3900 3300
Wire Wire Line
	4200 3300 4200 3950
Wire Wire Line
	3200 5950 3200 6150
Wire Wire Line
	3200 6150 3000 6150
Wire Wire Line
	3200 5950 4400 5950
Wire Wire Line
	4150 6550 3000 6550
Wire Wire Line
	4150 6100 4150 6550
$EndSCHEMATC
