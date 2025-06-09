#ifdef _DEBUG
#include "gmock/gmock.h"

int main()
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Car.h"
#include "Utils.h"

#define CLEAR_SCREEN "\033[H\033[2J"

void displayCarTypeAndTestMode(int selectionStep);
bool checkInputValidity(int selectionStep, int answer, char* checkNumber);
bool getUserInput(char** buf);

int main() {
	char buf[100];

	while (true) {
		displayCarTypeAndTestMode(Car::getInstance().getSelectStep());

		printf("INPUT > ");

		char* buffer = buf;
		if (!getUserInput(&buffer)) {
			break;
		}

		char* checkNumber;
		int answer = strtol(buf, &checkNumber, 10); // convert character string to number

		if (!checkInputValidity(Car::getInstance().getSelectStep(), answer, checkNumber)) {
			continue;
		}

		// Go back the first Menu
		if (Car::getInstance().goBackFirst(answer)) {
			continue;
		}

		// Go back the previouse Menu
		if (Car::getInstance().goPreviousStep(answer)) {
			continue;
		}

		// select type and test mode
		Car::getInstance().selectTypeOrTestMode(answer);
	}
}

bool getUserInput(char** buf)
{
	fgets(*buf, sizeof(*buf), stdin);

	//remove enter charactor
	char* context = nullptr;
	strtok_s(*buf, "\r", &context);
	strtok_s(*buf, "\n", &context);

	if (!strcmp(*buf, "exit")) {
		printf("바이바이\n");
		return false;
	}

	return true;
}

void displayCarTypeAndTestMode(int selectionStep)
{
	if (selectionStep == CarType_Q) {
		printf(CLEAR_SCREEN);


		printf("        ______________\n");
		printf("       /|            | \n");
		printf("  ____/_|_____________|____\n");
		printf(" |                      O  |\n");
		printf(" '-(@)----------------(@)--'\n");
		printf("===============================\n");
		printf("어떤 차량 타입을 선택할까요?\n");
		printf("1. Sedan\n");
		printf("2. SUV\n");
		printf("3. Truck\n");
	}
	else if (selectionStep == Engine_Q) {
		printf(CLEAR_SCREEN);
		printf("어떤 엔진을 탑재할까요?\n");
		printf("0. 뒤로가기\n");
		printf("1. GM\n");
		printf("2. TOYOTA\n");
		printf("3. WIA\n");
		printf("4. 고장난 엔진\n");
	}
	else if (selectionStep == brakeSystem_Q) {
		printf(CLEAR_SCREEN);
		printf("어떤 제동장치를 선택할까요?\n");
		printf("0. 뒤로가기\n");
		printf("1. MANDO\n");
		printf("2. CONTINENTAL\n");
		printf("3. BOSCH\n");
	}
	else if (selectionStep == SteeringSystem_Q) {
		printf(CLEAR_SCREEN);
		printf("어떤 조향장치를 선택할까요?\n");
		printf("0. 뒤로가기\n");
		printf("1. BOSCH\n");
		printf("2. MOBIS\n");
	}
	else if (selectionStep == Run_Test) {
		printf(CLEAR_SCREEN);
		printf("멋진 차량이 완성되었습니다.\n");
		printf("어떤 동작을 할까요?\n");
		printf("0. 처음 화면으로 돌아가기\n");
		printf("1. RUN\n");
		printf("2. Test\n");
	}

	printf("===============================\n");
}

bool checkInputValidity(int selectionStep, int answer, char* checkNumber)
{
	//입력받은 문자가 숫자가 아니라면
	if (*checkNumber != '\0') {
		printf("ERROR :: 숫자만 입력 가능\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == CarType_Q && !(answer >= 1 && answer <= 3)) {
		printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
		delay(800);
		return false;
	}

	if (selectionStep == Engine_Q && !(answer >= 0 && answer <= 4)) {
		printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == brakeSystem_Q && !(answer >= 0 && answer <= 3)) {
		printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) {
		printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == Run_Test && !(answer >= 0 && answer <= 2)) {
		printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	return true;
}

#endif