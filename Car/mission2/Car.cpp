#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Car.h"
#include "Utils.h"

Car::Car() : selectStep(CarType_Q)
{
	/*
	carModules.clear();

	CarModule* moduleType = new CarModule("차량 타입");
	carModules.push_back(moduleType);

	CarModule* moduleEngine = new CarModule("엔진");
	carModules.push_back(moduleEngine);

	CarModule* moduleBreak = new CarModule("제동장치");
	carModules.push_back(moduleBreak);

	CarModule* moduleSteer = new CarModule("조향장치");
	carModules.push_back(moduleSteer);
	*/
}

Car::~Car()
{
	/*
	for (auto carModule : carModules) {
		delete carModule;
	}

	carModules.clear();
	*/
}

Car& Car::getInstance()
{
	static Car instance;
	return instance;
}

void Car::selectTypeOrTestMode(int answer)
{
	if (selectStep == CarType_Q) {
		selectCarType(answer);
		delay(MENU_SELECT_DELAY);
		selectStep = Engine_Q;
	}
	else if (selectStep == Engine_Q) {
		selectEngine(answer);
		delay(MENU_SELECT_DELAY);
		selectStep = brakeSystem_Q;
	}
	else if (selectStep == brakeSystem_Q) {
		selectbrakeSystem(answer);
		delay(MENU_SELECT_DELAY);
		selectStep = SteeringSystem_Q;
	}
	else if (selectStep == SteeringSystem_Q) {
		selectSteeringSystem(answer);
		delay(MENU_SELECT_DELAY);
		selectStep = Run_Test;
	}
	else if (selectStep == Run_Test && answer == 1) {
		runProducedCar();
		delay(TEST_AFTER_DELAY);
	}
	else if (selectStep == Run_Test && answer == 2) {
		printf("Test...\n");
		delay(TEST_BEFORE_DELAY);
		testProducedCar();
		delay(TEST_AFTER_DELAY);
	}
}

void Car::selectCarType(int types)
{
	carModuleStack[CarType_Q] = types;
	if (types == 1) printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
	if (types == 2) printf("차량 타입으로 SUV을 선택하셨습니다.\n");
	if (types == 3) printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void Car::selectEngine(int types)
{
	carModuleStack[Engine_Q] = types;
	if (types == 1) printf("GM 엔진을 선택하셨습니다.\n");
	if (types == 2) printf("TOYOTA 엔진을 선택하셨습니다.\n");
	if (types == 3) printf("WIA 엔진을 선택하셨습니다.\n");
}

void Car::selectbrakeSystem(int types)
{
	carModuleStack[brakeSystem_Q] = types;
	if (types == 1) printf("MANDO 제동장치를 선택하셨습니다.\n");
	if (types == 2) printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
	if (types == 3) printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void Car::selectSteeringSystem(int types)
{
	carModuleStack[SteeringSystem_Q] = types;
	if (types == 1) printf("BOSCH 조향장치를 선택하셨습니다.\n");
	if (types == 2) printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

bool Car::goBackFirst(int answer)
{
	if (answer == 0 && selectStep == Run_Test) {
		selectStep = CarType_Q;
		true;
	}
	return false;
}

bool Car::goPreviousStep(int answer)
{
	if (answer == 0 && selectStep >= 1) {
		selectStep -= 1;
		return true;
	}
	return false;
}

int Car::isValidCheck() {
	if (carModuleStack[CarType_Q] == SEDAN && carModuleStack[brakeSystem_Q] == CONTINENTAL) {
		return false;
	}
	else if (carModuleStack[CarType_Q] == SUV && carModuleStack[Engine_Q] == TOYOTA) {
		return false;
	}
	else if (carModuleStack[CarType_Q] == TRUCK && carModuleStack[Engine_Q] == WIA) {
		return false;
	}
	else if (carModuleStack[CarType_Q] == TRUCK && carModuleStack[brakeSystem_Q] == MANDO) {
		return false;
	}
	else if (carModuleStack[brakeSystem_Q] == BOSCH_B && carModuleStack[SteeringSystem_Q] != BOSCH_S) {
		return false;
	}
	return true;
}

void Car::runProducedCar() {
	if (isValidCheck() == false) {
		printf("자동차가 동작되지 않습니다\n");
	}
	else {
		if (carModuleStack[Engine_Q] == 4) {
			printf("엔진이 고장나있습니다.\n");
			printf("자동차가 움직이지 않습니다.\n");
		}
		else {
			if (carModuleStack[CarType_Q] == 1) printf("Car Type : Sedan\n");
			if (carModuleStack[CarType_Q] == 2) printf("Car Type : SUV\n");
			if (carModuleStack[CarType_Q] == 3) printf("Car Type : Truck\n");
			if (carModuleStack[Engine_Q] == 1) printf("Engine : GM\n");
			if (carModuleStack[Engine_Q] == 2) printf("Engine : TOYOTA\n");
			if (carModuleStack[Engine_Q] == 3) printf("Engine : WIA\n");
			if (carModuleStack[brakeSystem_Q] == 1) printf("Brake System : Mando");
			if (carModuleStack[brakeSystem_Q] == 2) printf("Brake System : Continental\n");
			if (carModuleStack[brakeSystem_Q] == 3) printf("Brake System : Bosch\n");
			if (carModuleStack[SteeringSystem_Q] == 1) printf("SteeringSystem : Bosch\n");
			if (carModuleStack[SteeringSystem_Q] == 2) printf("SteeringSystem : Mobis\n");

			printf("자동차가 동작됩니다.\n");
		}
	}
}

void Car::testProducedCar() {
	if (carModuleStack[CarType_Q] == SEDAN && carModuleStack[brakeSystem_Q] == CONTINENTAL) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Sedan에는 Continental제동장치 사용 불가\n");
	}
	else if (carModuleStack[CarType_Q] == SUV && carModuleStack[Engine_Q] == TOYOTA) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("SUV에는 TOYOTA엔진 사용 불가\n");
	}
	else if (carModuleStack[CarType_Q] == TRUCK && carModuleStack[Engine_Q] == WIA) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Truck에는 WIA엔진 사용 불가\n");
	}
	else if (carModuleStack[CarType_Q] == TRUCK && carModuleStack[brakeSystem_Q] == MANDO) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Truck에는 Mando제동장치 사용 불가\n");
	}
	else if (carModuleStack[brakeSystem_Q] == BOSCH_B && carModuleStack[SteeringSystem_Q] != BOSCH_S) {
		printf("자동차 부품 조합 테스트 결과 : FAIL\n");
		printf("Bosch 제동장치에는 Bosch조향장치 이외 사용 불가\n");
	}
	else {
		printf("자동차 부품 조합 테스트 결과 : PASS\n");
	}
}