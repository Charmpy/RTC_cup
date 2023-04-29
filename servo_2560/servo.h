typedef struct servo_type {
	unsigned char ID_TYPE;//id 0-253
	unsigned int speed;//speed rotation 0-1024
	unsigned char torque_en;// on/off
	unsigned int CW;//Clockwise angle limit
	unsigned int CWW;//Counter-clockwise angle limit
	unsigned int goal_pos;//get position
	unsigned int present_pos;//present position
	unsigned int present_load;//percent of max torque
	unsigned int max_torque;
	unsigned char led_en;
	unsigned char uart_number;
	unsigned char NUMBER_BUF_SERVO;
	unsigned int midle_pos;
	unsigned char angle_free;
} servo_type;

servo_type S1;
servo_type S2;

//void init_servo()
#define NUMBER_BUF 5

#define Model_Number 0X00
//#define 0X01 Model_Number(H)
#define Version_of_Firmware 0X02 
#define ID_Addres 0X03
#define Baud_Rate 0X04
#define Return_Delay_Time 0X05
#define CW_Angle_Limit 0X06
//#define 0X07 CW_Angle_Limit(H)
#define CCW_Angle_Limit 0x08
//#define 0X09 CCW_Angle_Limit(H)
/*
0X0B Highest_Limit_Temperature
0X0C the Lowest Limit Voltage
0X0D the Highest Limit Voltage*/
#define MaxTorque 0X0E
//#define 0X0F MaxTorque(H)
#define StatusReturnLevel 0X10
/*
0X11 Alarm LED
0X12 Alarm Shutdown
0X14 Multi Turn Offset(L)
0X12 Multi Turn Offset(H)*/
#define ResolutionDivider 0X12
#define TorqueEnable 0X18
#define LED_ADDR 0X19
#define D_Gain 0X1A
#define I_Gain 0X1B
#define P_Gain 0X1C
#define Goal_Position 0X1E/*
#define 0X1F Goal_Position(H)*/
#define Moving_Speed 0X20/*
#define 0X21 Moving_Speed(H)*/
#define Torque_Limit 0X22/*
#define 0X23 Torque_Limit(H)*/
#define Present_Position 0X24/*
#define 0X25 Present_Position(H)*/
#define Present_Speed 0x26/*
#define 0X27 Present_Speed(H)*/
#define Present_Load 0X28/*
#define 0X29 Present_Load(H)*/
#define Present_Voltage 0X2A
#define Present_Temperature 0X2B
#define Registered 0X2C
#define Moving 0X2E
#define Lock 0X2F
#define Punch 0X30/*
#define 0X31 Punch(H)*/
#define Goal_Acceleration 0X49