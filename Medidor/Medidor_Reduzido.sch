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
Wire Wire Line
	3500 4200 3500 4100
$Comp
L pspice:R R6
U 1 1 60977A06
P 4950 3750
F 0 "R6" H 4882 3704 50  0000 R CNN
F 1 "100k" H 4882 3795 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4950 3750 50  0001 C CNN
F 3 "~" H 4950 3750 50  0001 C CNN
	1    4950 3750
	-1   0    0    1   
$EndComp
$Comp
L pspice:R R7
U 1 1 60978240
P 4950 4300
F 0 "R7" H 4882 4254 50  0000 R CNN
F 1 "10k" H 4882 4345 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4950 4300 50  0001 C CNN
F 3 "~" H 4950 4300 50  0001 C CNN
	1    4950 4300
	-1   0    0    1   
$EndComp
$Comp
L Transformer:TRANSF1 TR1
U 1 1 6098676E
P 5700 4000
F 0 "TR1" H 5700 4381 50  0000 C CNN
F 1 "220/9 V" H 5700 4290 50  0000 C CNN
F 2 "Transformer_THT:Transf_9V_150mA" H 5700 4000 50  0001 C CNN
F 3 "" H 5700 4000 50  0001 C CNN
	1    5700 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4050 4950 4000
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
Wire Wire Line
	2250 4200 3400 4200
$Comp
L pspice:R R8
U 1 1 60A1D619
P 2450 2800
F 0 "R8" H 2382 2754 50  0000 R CNN
F 1 "4.7k" H 2382 2845 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 2450 2800 50  0001 C CNN
F 3 "~" H 2450 2800 50  0001 C CNN
	1    2450 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 3050 2450 3400
Wire Wire Line
	3400 4100 3400 4200
Connection ~ 3400 4200
Wire Wire Line
	3400 4200 3500 4200
Connection ~ 2250 2550
$Comp
L Connector_Generic:Conn_01x03 DS18B20
U 1 1 6097DC10
P 2050 3400
F 0 "DS18B20" H 2166 3429 50  0000 L TNN
F 1 "Conn_01x03" H 1968 3166 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2050 3400 50  0001 C CNN
F 3 "~" H 2050 3400 50  0001 C CNN
	1    2050 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	2250 3500 2250 4200
Wire Wire Line
	2250 2550 2250 3300
Wire Wire Line
	2250 2350 2250 2550
Wire Wire Line
	2250 2350 2750 2350
Connection ~ 2450 3400
Wire Wire Line
	2450 3400 2900 3400
Wire Wire Line
	2250 3400 2450 3400
Wire Wire Line
	2250 2550 2450 2550
$Comp
L Converter_DCDC:MP1584_Module U1
U 1 1 614651F4
P 7550 3950
F 0 "U1" H 7575 4225 50  0000 C CNN
F 1 "MP1584_Module" H 7575 4134 50  0000 C CNN
F 2 "Converter_DCDC:MP1584_BuckModule" H 7550 4200 50  0001 C CNN
F 3 "" H 7550 4200 50  0001 C CNN
	1    7550 3950
	1    0    0    -1  
$EndComp
$Comp
L Converter_ACDC:HLK-PM01 PS1
U 1 1 614331C3
P 6650 4000
F 0 "PS1" H 6650 4325 50  0000 C CNN
F 1 "HLK-PM01" H 6650 4234 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 6650 3700 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=54" H 7050 3650 50  0001 C CNN
	1    6650 4000
	1    0    0    1   
$EndComp
Wire Wire Line
	7150 4100 7150 4050
Wire Wire Line
	2750 1450 3300 1450
Wire Wire Line
	3300 1450 3300 2100
Wire Wire Line
	4800 2800 4800 3100
Connection ~ 4800 2800
Wire Wire Line
	5250 2450 5250 2800
Wire Wire Line
	4800 2800 5250 2800
Wire Wire Line
	5250 2350 5250 2050
$Comp
L Connector_Generic:Conn_01x02 SCT13
U 1 1 6094029A
P 5450 2350
F 0 "SCT13" H 5530 2342 50  0000 L CNN
F 1 "Conn_01x02" H 5530 2251 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5450 2350 50  0001 C CNN
F 3 "~" H 5450 2350 50  0001 C CNN
	1    5450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2650 4800 2800
Wire Wire Line
	4500 2050 4800 2050
$Comp
L pspice:R R5
U 1 1 609727C3
P 4800 2400
F 0 "R5" H 4732 2354 50  0000 R CNN
F 1 "50k" H 4732 2445 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4800 2400 50  0001 C CNN
F 3 "~" H 4800 2400 50  0001 C CNN
	1    4800 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4800 2050 5250 2050
Connection ~ 4800 2050
$Comp
L pspice:R R2
U 1 1 6095ADFB
P 4500 2400
F 0 "R2" H 4432 2354 50  0000 R CNN
F 1 "10k" H 4432 2445 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4500 2400 50  0001 C CNN
F 3 "~" H 4500 2400 50  0001 C CNN
	1    4500 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4800 2050 4800 2150
Wire Wire Line
	4500 2800 4500 2650
Wire Wire Line
	4150 2800 4500 2800
Wire Wire Line
	4150 2550 4150 2800
Wire Wire Line
	4500 2050 4500 2150
Connection ~ 4500 2050
Wire Wire Line
	4150 2050 4500 2050
Wire Wire Line
	4150 2250 4150 2050
Wire Wire Line
	4500 2000 4500 2050
$Comp
L Device:CP C1
U 1 1 6095BCAD
P 4150 2400
F 0 "C1" H 4268 2446 50  0000 L CNN
F 1 "10uF" H 4268 2355 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D8.0mm_H11.5mm_P3.50mm" H 4188 2250 50  0001 C CNN
F 3 "~" H 4150 2400 50  0001 C CNN
	1    4150 2400
	1    0    0    -1  
$EndComp
$Comp
L pspice:R R1
U 1 1 6095A6AB
P 4500 1750
F 0 "R1" H 4432 1704 50  0000 R CNN
F 1 "10k" H 4432 1795 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4500 1750 50  0001 C CNN
F 3 "~" H 4500 1750 50  0001 C CNN
	1    4500 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 1450 2750 2350
Wire Wire Line
	3900 3300 7350 3300
$Comp
L pspice:R R10
U 1 1 614EC58D
P 6900 2950
F 0 "R10" H 6832 2904 50  0000 R CNN
F 1 "10k" H 6832 2995 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 6900 2950 50  0001 C CNN
F 3 "~" H 6900 2950 50  0001 C CNN
	1    6900 2950
	0    -1   1    0   
$EndComp
Wire Wire Line
	4800 3100 3900 3100
Wire Wire Line
	3300 1450 4500 1450
Wire Wire Line
	4500 1450 4500 1500
Connection ~ 3300 1450
Wire Wire Line
	6050 4200 6050 4900
Wire Wire Line
	4750 4600 4750 4700
Connection ~ 4400 4700
Wire Wire Line
	4400 4750 4400 4700
$Comp
L pspice:R R4
U 1 1 6099EB64
P 4400 4450
F 0 "R4" H 4332 4404 50  0000 R CNN
F 1 "10k" H 4332 4495 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4400 4450 50  0001 C CNN
F 3 "~" H 4400 4450 50  0001 C CNN
	1    4400 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 6099EB5A
P 4750 4450
F 0 "C2" H 4868 4496 50  0000 L CNN
F 1 "10uF" H 4868 4405 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D8.0mm_H11.5mm_P3.50mm" H 4788 4300 50  0001 C CNN
F 3 "~" H 4750 4450 50  0001 C CNN
	1    4750 4450
	-1   0    0    1   
$EndComp
$Comp
L pspice:R R3
U 1 1 609A4FC3
P 4400 5000
F 0 "R3" H 4332 4954 50  0000 R CNN
F 1 "10k" H 4332 5045 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 4400 5000 50  0001 C CNN
F 3 "~" H 4400 5000 50  0001 C CNN
	1    4400 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4750 4700 4950 4700
Connection ~ 4950 4700
Wire Wire Line
	4950 4550 4950 4700
Wire Wire Line
	5500 4200 5500 4700
Connection ~ 3500 4200
Wire Wire Line
	4800 3500 4800 4000
Wire Wire Line
	4800 4000 4950 4000
Wire Wire Line
	3900 3500 4800 3500
Connection ~ 4950 4000
Wire Wire Line
	3500 4200 4400 4200
Wire Wire Line
	4950 4700 5500 4700
Wire Wire Line
	4500 4200 4750 4200
Wire Wire Line
	4750 4200 4750 4300
Connection ~ 4500 4200
Connection ~ 4500 2800
Wire Wire Line
	4500 2800 4500 2950
Wire Wire Line
	4500 2950 4500 4200
Connection ~ 4500 2950
Wire Wire Line
	5500 3500 5500 3800
Wire Wire Line
	4950 3500 5500 3500
Wire Wire Line
	5900 3800 6150 3800
Wire Wire Line
	6050 4200 5900 4200
Wire Wire Line
	6250 3900 6150 3900
Wire Wire Line
	6150 3800 6150 3900
Connection ~ 6150 3900
Wire Wire Line
	6150 3900 6150 4900
Wire Wire Line
	6050 4200 6250 4200
Wire Wire Line
	6250 4200 6250 4100
Connection ~ 6050 4200
$Comp
L Connector_Generic:Conn_01x02 REDE1
U 1 1 6093F3CB
P 6150 5100
F 0 "REDE1" V 6230 5053 50  0000 C TNN
F 1 "Conn_01x02" V 6230 5001 50  0001 R TNN
F 2 "TerminalBlock_Altech:Altech_AK300_1x02_P5.00mm_45-Degree" H 6150 5100 50  0001 C CNN
F 3 "~" H 6150 5100 50  0001 C CNN
	1    6150 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 4100 7100 4100
Connection ~ 2750 2350
Wire Wire Line
	2750 2350 2750 5350
Wire Wire Line
	7100 5350 7100 4100
Wire Wire Line
	4400 5250 4400 5350
Wire Wire Line
	4500 2950 6150 2950
$Comp
L pspice:R R9
U 1 1 614EC593
P 6400 2950
F 0 "R9" H 6332 2904 50  0000 R CNN
F 1 "20k" H 6332 2995 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0414_L11.9mm_D4.5mm_P15.24mm_Horizontal" H 6400 2950 50  0001 C CNN
F 3 "~" H 6400 2950 50  0001 C CNN
	1    6400 2950
	0    -1   1    0   
$EndComp
Connection ~ 4400 4200
Wire Wire Line
	4400 4200 4500 4200
Wire Wire Line
	4400 4700 4750 4700
Connection ~ 4750 4700
Connection ~ 4400 5350
Wire Wire Line
	4400 5350 2750 5350
Wire Wire Line
	4400 5350 7100 5350
$Comp
L Connector_Generic:Conn_01x05 SIM800L
U 1 1 618096E3
P 8550 3300
F 0 "SIM800L" H 8783 3363 50  0000 C CNN
F 1 "Conn_01x05" H 8468 3626 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 8550 3300 50  0001 C CNN
F 3 "~" H 8550 3300 50  0001 C CNN
	1    8550 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3300 7350 3200
Wire Wire Line
	3900 3400 8350 3400
Wire Wire Line
	7350 3200 8350 3200
Wire Wire Line
	7050 3900 7150 3900
Wire Wire Line
	7100 4100 7150 4100
Connection ~ 7100 4100
Wire Wire Line
	6650 3200 6650 2950
Wire Wire Line
	3900 3200 6650 3200
Connection ~ 6650 2950
Wire Wire Line
	8000 2950 8000 3300
Wire Wire Line
	8000 3300 8350 3300
Wire Wire Line
	7150 2950 8000 2950
Wire Wire Line
	8000 3900 8050 3900
Wire Wire Line
	8050 3900 8050 3500
Wire Wire Line
	8050 3500 8350 3500
Wire Wire Line
	8000 4050 8200 4050
Wire Wire Line
	8200 4050 8200 3100
Wire Wire Line
	8200 3100 8350 3100
$EndSCHEMATC
