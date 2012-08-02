#ifndef CALIBRATE_H
#define CALIBRATE_H


#define ADC_NOISE	8			//maximum acceptable variation of ADC values while in idle/still position max(adcMax-adcMin)
								//if device is not moving and you get calibration FAULTs consider increasing ADC_NOISE constant
								//other alternatives are bypassing adc inputs and power with capacitors


#define MAX_CALIB_ERR  1.5		//acceptable calibration resulting error in percents


#define POSITION_COUNT	12
#define UNIQUE_POSITION_DISTANCE (ADC_NOISE*10) // factor 10 is chosen randomly but minimum factor should be at least sqrt(3)

#define COLLECT_COUNT	200						// collect time 200 * 7.056ms ~ 1.4s

typedef struct {
	unsigned int adcMin[6];
	unsigned int adcMax[6];
	double adcAvg[6];
} Collect;

Collect collect;

//this functions collects ADC samples while device is not moved 
//collects COLLECT_COUNT adc samples so that (adcMax-adcMin) <= ADC_NOISE
void collect_still_samples(){
	unsigned char w;
	unsigned char fault = 1;
	int counter;	

	while(fault){
		counter = 0;
		STATUS_INIT;
		for(w=0;w<6;w++){
			collect.adcAvg[w] = 0;
			collect.adcMax[w] = 0;
			collect.adcMin[w] = 1023;
		}

		while(counter < COLLECT_COUNT){
			while(!adc_new_data());		//wait for new adc data
			fault = 0;
			for(w=0;w<6;w++){
				collect.adcAvg[w] += adcAvg[w];
				collect.adcMin[w] = MIN(adcMin[w],collect.adcMin[w]);
 				collect.adcMax[w] = MAX(adcMax[w],collect.adcMax[w]);

				if(collect.adcMax[w] - collect.adcMin[w] > ADC_NOISE){	
					fault = 1;
					STATUS_CALIB_ERR1;
					printf("***COLLECT FAULT - KEEP DEVICE STILL***  Axis:%d adcMin:%d adcMax:%d \n", w, collect.adcMin[w] , collect.adcMax[w]);
					//adc_debug_dump1();
					__delay_ms(500);
				}
			}

			if(!fault)
				counter++;
			else{
				counter = COLLECT_COUNT; //start over at while(fault)...
			}
		}
	}	

	for(w=0;w<6;w++) collect.adcAvg[w] /= COLLECT_COUNT;
}

Collect collects[POSITION_COUNT];

/*********** GYRO CALIBRATION ********/
#define GYRO_COLECTS 3
//Calibrate gyro offsets (not sensibility)
void calibrate_gyro(){
	unsigned char i,w;
	for(i=0;i<GYRO_COLECTS;i++){
		collect_still_samples();
		for(w=0;w<3;w++){
			if(0==i) config.gyroOffs[w] = 0;
			config.gyroOffs[w] += collect.adcAvg[3+w];	
		}
	}
	for(w=0;w<3;w++) config.gyroOffs[w] /= GYRO_COLECTS;
}



unsigned char collect_check_uniqness(unsigned char n){
	unsigned char i,w;
	double distance = 0;

	for(i=0;i<n;i++){
		//compute distance between 3D ponts given by collect.adcAvg[0..2]  and collects[i].adcAvg[0..2]
		for(w=0;w<3;w++){
			printf("(%.2f - %.2f) ",collect.adcAvg[w], collects[i].adcAvg[w]);
			distance += squared(collect.adcAvg[w]- collects[i].adcAvg[w]);
		}

		distance = sqrt(distance);

		printf("\nDISTANCE FROM POS %d IS %f\n",i+1,distance);


		if(distance <  UNIQUE_POSITION_DISTANCE){	
			printf("***TOO SIMILAR TO POSITION %d. ROTATE TO A DIFFERNT POSITION\n", i+1);
			return 0;
		}
	}
	return 1;	

}

// Calibrate acc offset and sensibility
// User is asked to rotate device in <POSITION_COUNT> different positions
// and hold device still untill beep is heard
// Uppon <POSITION_COUNT> successful calls to collect_still_samples()
// calculations are made
#define CALIBRATE_ACC_DEBUG 
void calibrate_acc(){
	unsigned char i,w;

	/*********** DATA COLLECTION ********/

#ifdef CALIBRATE_ACC_DEBUG
	//debug data can be run instead of below loop
	collects[0].adcAvg[3]=383.188446;collects[0].adcAvg[4]=385.673126;collects[0].adcAvg[5]=516.209351;
	collects[1].adcAvg[3]=383.988434;collects[1].adcAvg[4]=384.504364;collects[1].adcAvg[5]=516.233154;
	collects[2].adcAvg[3]=382.494049;collects[2].adcAvg[4]=385.230927;collects[2].adcAvg[5]=516.767822;
	collects[3].adcAvg[3]=383.768738;collects[3].adcAvg[4]=384.926880;collects[3].adcAvg[5]=516.465637;
	collects[4].adcAvg[3]=382.960632;collects[4].adcAvg[4]=385.126862;collects[4].adcAvg[5]=516.787476;
	collects[5].adcAvg[3]=383.020630;collects[5].adcAvg[4]=385.890015;collects[5].adcAvg[5]=516.331848;
	collects[6].adcAvg[3]=383.506866;collects[6].adcAvg[4]=385.448120;collects[6].adcAvg[5]=516.510315;
	collects[7].adcAvg[3]=382.444702;collects[7].adcAvg[4]=386.231567;collects[7].adcAvg[5]=515.925293;
	collects[8].adcAvg[3]=381.203430;collects[8].adcAvg[4]=385.474701;collects[8].adcAvg[5]=516.728455;
	collects[9].adcAvg[3]=384.216248;collects[9].adcAvg[4]=385.110321;collects[9].adcAvg[5]=515.913147;
	collects[10].adcAvg[3]=383.609375;collects[10].adcAvg[4]=386.874054;collects[10].adcAvg[5]=516.015930;
	collects[11].adcAvg[3]=383.353424;collects[11].adcAvg[4]=386.361572;collects[11].adcAvg[5]=516.634705;
	collects[0].adcAvg[0]=516.147217;collects[0].adcAvg[1]=658.059082;collects[0].adcAvg[2]=485.228119;
	collects[1].adcAvg[0]=512.661865;collects[1].adcAvg[1]=603.153137;collects[1].adcAvg[2]=392.942505;
	collects[2].adcAvg[0]=430.130615;collects[2].adcAvg[1]=527.642212;collects[2].adcAvg[2]=390.834381;
	collects[3].adcAvg[0]=594.327820;collects[3].adcAvg[1]=525.189697;collects[3].adcAvg[2]=384.623138;
	collects[4].adcAvg[0]=516.509033;collects[4].adcAvg[1]=434.303741;collects[4].adcAvg[2]=382.245300;
	collects[5].adcAvg[0]=376.282806;collects[5].adcAvg[1]=481.118134;collects[5].adcAvg[2]=466.477814;
	collects[6].adcAvg[0]=438.328125;collects[6].adcAvg[1]=393.985931;collects[6].adcAvg[2]=451.228424;
	collects[7].adcAvg[0]=380.568115;collects[7].adcAvg[1]=481.661865;collects[7].adcAvg[2]=561.103760;
	collects[8].adcAvg[0]=535.098450;collects[8].adcAvg[1]=392.734375;collects[8].adcAvg[2]=596.289673;
	collects[9].adcAvg[0]=399.993439;collects[9].adcAvg[1]=572.015930;collects[9].adcAvg[2]=571.250916;
	collects[10].adcAvg[0]=475.290924;collects[10].adcAvg[1]=605.955627;collects[10].adcAvg[2]=608.998108;
	collects[11].adcAvg[0]=455.715942;collects[11].adcAvg[1]=437.814056;collects[11].adcAvg[2]=621.777527;
#else
	for(i=0;i<POSITION_COUNT;i++){
		printf("***POSITION %d of %d*** Collecting samples...\n",i+1,POSITION_COUNT);
		collect_still_samples();
		if(collect_check_uniqness(i)){
			//signal successful collect and pause to allow time for next position
			beep(500,_ON);		//continous beep signals position accepted
			collects[i] = collect;
		}else{
			i = i - 1;				//repeat this step
			STATUS_CALIB_ERR2;		//alternating beep and led2 blink signals position rejected
		};
		__delay_ms(700);			//allow time for position change
	}

	//dump data assignment so we can debug later
	for(i=0;i<POSITION_COUNT;i++){
		for(w=0;w<3;w++){
		 	printf("collects[%d].adcAvg[%d]=%f;",i,3+w,collects[i].adcAvg[3+w]);
		}
		printf("\n");
	}

#endif	

	/*********** ACCC CALIBRATION ********/
	//now calculate accelerometer offsets and sensitivity using least-square methong
	//Implementing algorithm http://www.sparkfun.com/datasheets/Sensors/Magneto/Tilt%20Compensated%20Compass.pdf, page 28
	float W[POSITION_COUNT][1];
	float H[POSITION_COUNT][6];
	//Populate W and H matrix
	for(i=0;i<POSITION_COUNT;i++){
		//dump data assignment so we can debug later
		for(w=0;w<3;w++) printf("collects[%d].adcAvg[%d]=%f;",i,w,collects[i].adcAvg[w]);printf("\n");
		
		W[i][0] = collects[i].adcAvg[0]*collects[i].adcAvg[0]; 	// x^2
		H[i][0] = collects[i].adcAvg[0]; 						// x
		H[i][1] = collects[i].adcAvg[1]; 						// y
		H[i][2] = collects[i].adcAvg[2]; 						// z
		H[i][3] = -collects[i].adcAvg[1]*collects[i].adcAvg[1]; // -y^2
		H[i][4] = -collects[i].adcAvg[2]*collects[i].adcAvg[2]; // -z^2
		H[i][5] = 1; 											// 1
	}


	// Solving overdetermined equation   W = H . X  using least squares method 
	// X =  Pseudoinverse[H]. W =  Inverse( Transpose(H) . H ). Transpose(H) . W
	

	printf("H=\n");matrix_print(POSITION_COUNT,6, (float*)H);

	float Ht[6][POSITION_COUNT];
	matrix_transpose(POSITION_COUNT,6,(float*)H,(float*)Ht);

	printf("Ht=\n");matrix_print(6,POSITION_COUNT, (float*)Ht);
	
	float HtH[6][6];	// HtH =  Transpose(H) . H
	matrix_multiply(6,POSITION_COUNT, 6,(float*)Ht,(float*)H,(float*)HtH);

	printf("HtH=\n");matrix_print(6,6, (float*)HtH);


	//now compute inverse of HtH
	float HtHi[6][6];
	matrix_copy(6,6,(float*)HtH,(float*)HtHi);
	int result = matrix_inverse(6,(float*)HtHi);

	if(result != 0){
	
		printf("result=%d HtHi=\n",result);matrix_print(6,6, (float*)HtHi);
		
		float P[6][POSITION_COUNT];	//pseudoinverse of H
		matrix_multiply(6,6,POSITION_COUNT, (float*)HtHi, (float*)Ht, (float*)P);
	
		printf("P=\n");matrix_print(6,POSITION_COUNT, (float*)P);
		
		float X[6][1];		//result
		matrix_multiply(6,POSITION_COUNT,1, (float*)P,(float*)W,(float*)X);
	
		printf("X=\n");	matrix_print(6,1, (float*)X);
	
	
		config.accOffs[0] = X[0][0]/2;
		config.accOffs[1] = X[1][0]/2 / X[3][0];
		config.accOffs[2] = X[2][0]/2 / X[4][0];
	
		config.accSens[0] = sqrt(X[5][0] + squared(config.accOffs[0]) +  X[3][0] *  squared(config.accOffs[1])  + X[4][0] *  squared(config.accOffs[2]));
		config.accSens[1] = config.accSens[0] / sqrt(X[3][0]);
		config.accSens[2] = config.accSens[0] / sqrt( X[4][0]);
	
	
	
		double err = 0;	//compute calibration error
		for(i=0;i<POSITION_COUNT;i++){
			err += fabs(sqrt(
				squared((collects[i].adcAvg[0]-config.accOffs[0])/config.accSens[0])+ 
				squared((collects[i].adcAvg[1]-config.accOffs[1])/config.accSens[1])+ 
				squared((collects[i].adcAvg[2]-config.accOffs[2])/config.accSens[2]) 
			)-1);
			
		}
	
		err = 100.0 * err / POSITION_COUNT;
	
		printf("Calibration Error: %.6f%%\n",err);

		if(err < MAX_CALIB_ERR){
			printf("Calibration succeded\n");
#ifndef CALIBRATE_ACC_DEBUG
		config_save();
#endif
		}else{
			printf("Calibration failed (Max error reached)\n");
			config_load();
		}
	}else{
		printf("Calibration failed (No matrix inverse)\n");
		config_load();
	}





}

#endif
