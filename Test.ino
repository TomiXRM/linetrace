//Arduino mega2560 SRC14 project

#define Kp
#define Kd
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
	int Motorleft;
	int Motorright;
}line;

void setup(){
	Serial.begin(115200);
	//Serial1.begin(115200);
}
void loop(){
	line_update();
	distance_from_origin();
	linetrace();
}

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

