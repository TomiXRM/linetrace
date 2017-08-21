//Arduino mega2560 SRC14 project

//Arduino mega2560 SRC14 project
#include"Wire.h"
#define Kp 1.2
#define Kd 0.6
#define Rsilver 0
#define Lsilver 1
#define White_Threshold0 680
#define White_Threshold1 680
#define White_Threshold2 680
#define White_Threshold3 680
#define White_Threshold4 680
#define White_Threshold5 680
#define White_Threshold6 680

#define Silver_Threshold0 750
#define Silver_Threshold1 750
#define Silver_Threshold2 750
#define Silver_Threshold3 750
#define Silver_Threshold4 750
#define Silver_Threshold5 750
#define Silver_Threshold6 750

struct{
	int channel[7]= {A0,A1,A2,A3,A4,A5,A6};
	int sensor[7];
	int White_Threshold[7]={
		White_Threshold0,
		White_Threshold1,
		White_Threshold2,
		White_Threshold3,
		White_Threshold4,
		White_Threshold5,
		White_Threshold6
		};
		int Silver_Threshold[7]={
		Silver_Threshold0,
		Silver_Threshold1,
		Silver_Threshold2,
		Silver_Threshold3,
		Silver_Threshold4,
		Silver_Threshold5,
		Silver_Threshold6
		};
	float Origin_Distance;
	bool OnSilver[7];
	bool OnBlack[7];
	bool OnWhite[7];
	int Silver_count[3];
	int Motorleft;
	int Motorright;
}line;

void line_update(){
	for(uint8_t i=0; i<7;i++){
		line.sensor[i] = analogRead(line.channel[i]);
	}
	
	for(uint8_t i=0; i<7;i++){
		if(line.sensor[i] > line.Silver_Threshold[i]){
			line.OnSilver[i] = 1;
		}else{
			line.OnSilver[i] = 0;
		}
	}		
	
		for(uint8_t i=0; i<7;i++){
		if(line.sensor[i] > line.White_Threshold[i]){
			line.OnWhite[i] = 1;
			line.OnBlack[i] = 0;
		}else{
			line.OnWhite[i] = 0;
			line.OnBlack[i] = 1;
		}
	}
}

void distance_from_origin(){
	uint8_t n=0;
	line.Origin_Distance = 0;
	if(line.OnBlack[0] == 1){
		line.Origin_Distance += 50;
		n++;
	}
	if(line.OnBlack[1] == 1){
		line.Origin_Distance += 35;
		n++;
	}
	if(line.OnBlack[2] == 1){
		line.Origin_Distance += 20;
		n++;
	}
	if(line.OnBlack[3] == 1){
		line.Origin_Distance += 0;
		n++;
	}
	if(line.OnBlack[4] == 1){
		line.Origin_Distance += -20;
		n++;
	}
	if(line.OnBlack[5] == 1){
		line.Origin_Distance += -35;
		n++;
	}
	if(line.OnBlack[6] == 1){
		line.Origin_Distance += -50;
		n++;
	}
	if(n!=0){
	        line.Origin_Distance = line.Origin_Distance / n;
	}
}

void linetrace(int mpower,float _KP,float _KD){
	line.Motorleft = mpower+line.Origin_Distance*_KP;
	line.Motorright = mpower-line.Origin_Distance*_KP;
	//MD.motor(line.Motorleft,line.Motorright);
}

void linetrace_onof(){
	if(line.OnWhite[2]&&line.OnWhite[4]){
		//MD.motor(300,300);
	}else if(line.OnBlack[2]){
		//MD.motor(0,200);
	}else if(line.OnBlack[4]){
		//MD.motor(200,0);
	}
}

void miningpit(){
	
}

void moonbase1(){
	
}

void moonbase2(){
	
}

void goto_moonbase3(){
	
}

void moonbase3(){
	
}

void setup(){
	Serial.begin(115200);
	pinMode(13,OUTPUT);//buzzer
	Wire.begin();
	//Serial1.begin(115200);
}
void loop(){
	line_update();
	if(line.OnSilver[3]){
		//MD.motor(0,0);
		delay(1000);
		//MD.motor(400,400);
		delay(300);
	}else if(line.OnSilver[2]||line.OnSilver[1]){
		//right miningpit
	}else if(line.OnSilver[4]||line.OnSilver[5]){
		//left moonbase1,2
	}else{
		distance_from_origin();
		linetrace(80,Kp,Kd);
	}
}

