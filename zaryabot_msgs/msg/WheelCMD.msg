# Wheel constant
uint8 LF_Wheel = 0
uint8 RF_Wheel = 1
uint8 LB_Wheel = 2
uint8 RB_Wheel = 3

#Whell Mode
uint8 MODE_CW    = 0
uint8 MODE_CCW   = 1
uint8 MODE_STOP  = 2
uint8 MODE_BRAKE = 3

#Wheel Status
float64[] position
float64[] velocity
uint8[] mode
uint8[] jointid
