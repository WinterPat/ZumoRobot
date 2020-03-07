int slower(int spd);
int hasChanged(struct sensors_ prev, struct sensors_ current);
void copySensorStruct(struct sensors_ original, struct sensors_ copy);
struct sensors_ copySensorStruct1(struct sensors_ original);


#if 0
//prod
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;
    
    int previous = 1;
    bool enable = false;
    
    int spd = 150;
    int turnFast = 150;
    int turnSlow = 75;
    

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000

    for(;;)
    {
        if (SW1_Read() == 0 && previous == 1) {
            if (!enable) {
                enable = true;
            } else {
                enable = false;
            }
        }
        
        previous = SW1_Read();
       
            
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        
        
        if (enable) {
            motor_start();
            if ((dig.l1 || dig.r1) && !(dig.l3 || dig.l2 || dig.r2 || dig.r3)) {
                motor_forward(spd, 1);
            } else if ((dig.r2 || dig.r3) && !(dig.l2 && dig.l3)) {
                motor_forward(spd, 1);
                motor_turn(turnFast, turnSlow, 1);
            } else if ((dig.l2 || dig.l3) && !(dig.r2 && dig.r3)) {
                motor_forward(spd, 1);
                motor_turn(turnSlow, turnFast, 1);
            } else if (!dig.l3 && !dig.l2 && !dig.l1 && !dig.r1 && !dig.r2 && !dig.r3) {
                motor_backward(75, 1);
            } else {
                motor_forward(0, 1);
            }
        } else {
            motor_stop();
        }
    }
   
}
#endif 

#if 0
    void zmain(void) {
        int enable = 0;
        int previous = 1;
        while(1) {
            if (enable) {
                motor_start();
                motor_tankTurn_left(100, 1000);
                motor_forward(100, 1000);
                motor_tankTurn_right(100, 1000);
                motor_forward(100, 1000);
            }
            
            if (SW1_Read() == 0 && previous == 1) {
                vTaskDelay(1000);
            if (!enable) {
                enable = true;
            } else {
                enable = false;
            }
        }
            previous = SW1_Read();
        }
    }
#endif

#if 0
//dev
void zmain(void)
{
    struct sensors_ dig;
    struct sensors_ prev;
    
    int previous = 1;
    bool enable = false;
    
    
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000

    for(;;)
    {
        if (SW1_Read() == 0 && previous == 1) {
            if (!enable) {
                enable = true;
            } else {
                enable = false;
            }
        }
        
        previous = SW1_Read();
       
            
        reflectance_digital(&dig);
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);  
        vTaskDelay(200);
        
        if (hasChanged(prev, dig)) {
            printf("yo\n");
        }
        
        copySensorStruct(dig, prev);
        
    }
   
}
#endif

//struct sensors_ copySensorStruct1(struct sensors_ original) {
//    struct sensors_ copy;
//    copy.l1 = original.l1;
//    copy.l2 = original.l2;
//    copy.l3 = original.l3;
//    copy.r1 = original.r1;
//    copy.r2 = original.r2;
//    copy.r3 = original.r3;
//    return copy;
//}

void copySensorStruct(struct sensors_ original, struct sensors_ copy) {
    copy.l1 = original.l1;
    copy.l2 = original.l2;
    copy.l3 = original.l3;
    copy.r1 = original.r1;
    copy.r2 = original.r2;
    copy.r3 = original.r3;
}

int hasChanged(struct sensors_ prev, struct sensors_ current) {
    if (prev.l1 != current.l1
        || prev.l2 != current.l2
        || prev.l3 != current.l3
        || prev.r1 != current.r1
        || prev.r2 != current.r2
        || prev.r3 != current.r3) {
         return 1;
    }
    return 0;
}

int forward(int spd) {
    return spd;
}

int slower(int spd) {
    int min = 50;
    if (spd > min) {
        return spd - 50;
    }
    
    return min;
}

#if 0
    //week 1 assignment 1
void zmain(void) {
    while(1) {
        while (SW1_Read() == 1) {
            vTaskDelay(100);
        }
        
        for (int i = 0; i < 3; i++) {
            BatteryLed_Write(1);
            vTaskDelay(500);
            BatteryLed_Write(0);
            vTaskDelay(500);
        }

        for (int i = 0; i < 3; i++) {
            BatteryLed_Write(1);
            vTaskDelay(1500);
            BatteryLed_Write(0);
            vTaskDelay(500);
        }
        
        for (int i = 0; i < 3; i++) {
            BatteryLed_Write(1);
            vTaskDelay(500);
            BatteryLed_Write(0);
            vTaskDelay(500);
        }
    }
}
#endif

#if 0
    //week 1 assignment 2
void zmain(void) {
    while(1) {
        int age;
        printf("What is your age?");
        TickType_t first = xTaskGetTickCount();
        scanf("%d", &age);
        TickType_t second = xTaskGetTickCount();
        
        int diff = second - first;
        
        if (age <= 21) {
            if (diff < 3000) {
                printf("Super fast dude!");
            } else if (diff > 3000 && diff < 5000) {
                printf("So mediocre.");
            } else if (diff > 5000) {
                printf("My granny is faster than you! ");
            }
        } else if (age >= 22 && age <= 50) {
            if (diff < 3000) {
                printf("Be quick or be dead");
            } else if (diff > 3000 && diff < 5000) {
                printf("You\'re so average.");
            } else if (diff > 5000) {
                printf("Have you been smoking something illegal? ");
            }
        } else if (age > 50) {
            if (diff < 3000) {
                printf("Still going strong ");
            } else if (diff > 3000 && diff < 5000) {
                printf("You are doing ok for your age.");
            } else if (diff > 5000) {
                printf("Do they still allow you to drive?");
            }
        }
        
        printf("\n");
    }
}

#endif

#if 0
//week 1 assignment 3
void zmain(void) {
    ADC_Battery_Start();        

    int16 adcresult = 0;
    float volts = 0.0;

    printf("\nBoot\n");


    for(;;)
    {
        ADC_Battery_StartConvert(); // start sampling
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            volts = adcresult * (4.8 / 4095);
            
            if (volts < 3.0) {
                while(SW1_Read() == 1) {
                    BatteryLed_Write(1);
                    vTaskDelay(200);
                    BatteryLed_Write(0);
                    vTaskDelay(200);
                }
            }
            printf("%d %f\r\n",adcresult, volts);
        }
        vTaskDelay(500);
    }
}
#endif

#if 0
    //week 3 assignment 2
void zmain(void) {
    Ultra_Start();
    motor_start();
    while(1) {
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        if (d < 10) {
            Beep(500, 100);
            motor_backwardTurn(50, 100, 2500);
        } else {
            motor_forward(100, 1);
         
        }
        
                
        vTaskDelay(100);
    }
}
#endif   


#if 0
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{
    struct accData_ data;
    struct accData_ biggest;
    struct accData_ end;
    motor_start();
    
    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    LSM303D_Read_Acc(&data);
    vTaskDelay(100);
    for(;;)
    {
        LSM303D_Read_Acc(&data);
        motor_forward(100, 1);
        printf("%8d %8d %8d\n",end.accX, end.accY, end.accZ);
        if (data.accX > biggest.accX) {
            biggest.accX = data.accX;
        }
        
        if (data.accY > biggest.accY) {
            biggest.accY = data.accY;
        }
        
        if (data.accZ > biggest.accZ) {
            biggest.accZ = data.accZ;
        }
        vTaskDelay(50);
        if (SW1_Read() == 0) {
            motor_stop();
            end.accX = biggest.accX;
            end.accY = biggest.accY;
            end.accZ = biggest.accZ;
        }
    }
 }   
#endif   
#if 0
//week 3 assignment 1
void zmain(void)
{
    motor_start();
    TickType_t first;
    TickType_t second;
    time_t t;
    uint limit;
    struct accData_ data;
    
    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    LSM303D_Read_Acc(&data);
    vTaskDelay(50);
    
    srand((unsigned) time(&t));
    
    first = xTaskGetTickCount();
    limit = (rand() % 3 + 1) * 1000;
    for(;;) {
        LSM303D_Read_Acc(&data);
        motor_forward(100,1);
        second = xTaskGetTickCount();
        if ((second - first) > limit) {
            int dir = rand() % 2;
            if (dir == 1) {
                motor_tankTurn_left(100, 750);
            } else {
                motor_tankTurn_right(100, 750);
            }
            limit = (rand() % 3 + 1) * 1000;
            first = xTaskGetTickCount();
        }
        
        if (data.accX > 15000) {
            motor_backward(100, 1500);
            int dir = rand() % 2;
            if (dir == 1) {
                motor_tankTurn_left(100, 750);
            } else {
                motor_tankTurn_right(100, 750);
            }
        }
        
        if (SW1_Read() == 0) {
            motor_stop();
        }
    }
 }   
#endif   

#if 1
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    IR_Start();
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    bool led = false;
    // Toggle led when IR signal is received
    for(;;)
    {
        IR_wait();  // wait for IR command
        led = !led;
        BatteryLed_Write(led);
        if(led) printf("Led is ON\n");
        else printf("Led is OFF\n");
    }    
 }   
#endif