#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Car.h"
#include "Utils.h"

Car::Car() : selectStep(CarType_Q)
{
	/*
	carModules.clear();

	CarModule* moduleType = new CarModule("���� Ÿ��");
	carModules.push_back(moduleType);

	CarModule* moduleEngine = new CarModule("����");
	carModules.push_back(moduleEngine);

	CarModule* moduleBreak = new CarModule("������ġ");
	carModules.push_back(moduleBreak);

	CarModule* moduleSteer = new CarModule("������ġ");
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
	if (types == 1) printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
	if (types == 2) printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
	if (types == 3) printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void Car::selectEngine(int types)
{
	carModuleStack[Engine_Q] = types;
	if (types == 1) printf("GM ������ �����ϼ̽��ϴ�.\n");
	if (types == 2) printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
	if (types == 3) printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void Car::selectbrakeSystem(int types)
{
	carModuleStack[brakeSystem_Q] = types;
	if (types == 1) printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
	if (types == 2) printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
	if (types == 3) printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void Car::selectSteeringSystem(int types)
{
	carModuleStack[SteeringSystem_Q] = types;
	if (types == 1) printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
	if (types == 2) printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
		printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
	}
	else {
		if (carModuleStack[Engine_Q] == 4) {
			printf("������ ���峪�ֽ��ϴ�.\n");
			printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

			printf("�ڵ����� ���۵˴ϴ�.\n");
		}
	}
}

void Car::testProducedCar() {
	if (carModuleStack[CarType_Q] == SEDAN && carModuleStack[brakeSystem_Q] == CONTINENTAL) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Sedan���� Continental������ġ ��� �Ұ�\n");
	}
	else if (carModuleStack[CarType_Q] == SUV && carModuleStack[Engine_Q] == TOYOTA) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("SUV���� TOYOTA���� ��� �Ұ�\n");
	}
	else if (carModuleStack[CarType_Q] == TRUCK && carModuleStack[Engine_Q] == WIA) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Truck���� WIA���� ��� �Ұ�\n");
	}
	else if (carModuleStack[CarType_Q] == TRUCK && carModuleStack[brakeSystem_Q] == MANDO) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Truck���� Mando������ġ ��� �Ұ�\n");
	}
	else if (carModuleStack[brakeSystem_Q] == BOSCH_B && carModuleStack[SteeringSystem_Q] != BOSCH_S) {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
		printf("Bosch ������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
	}
	else {
		printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
	}
}