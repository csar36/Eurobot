CC=g++
FLAGS=-Wall -Wextra -Wno-unused -std=c++11 -pedantic -lpthread
OBJS=stdafx.o gpio.o Pwm.o Motor.o AnalogInput.o Timer.o Ecu.o Odometry.o InfraredSensor.o Servo.o
OUT=Robot

$(OUT): $(OBJS) main.cpp
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $<  -o $@

clean:
	rm -f $(OUT)
	rm -f *.o

.PHONY: clean
