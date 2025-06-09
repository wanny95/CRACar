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
		printf("���̹���\n");
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
		printf("� ���� Ÿ���� �����ұ��?\n");
		printf("1. Sedan\n");
		printf("2. SUV\n");
		printf("3. Truck\n");
	}
	else if (selectionStep == Engine_Q) {
		printf(CLEAR_SCREEN);
		printf("� ������ ž���ұ��?\n");
		printf("0. �ڷΰ���\n");
		printf("1. GM\n");
		printf("2. TOYOTA\n");
		printf("3. WIA\n");
		printf("4. ���峭 ����\n");
	}
	else if (selectionStep == brakeSystem_Q) {
		printf(CLEAR_SCREEN);
		printf("� ������ġ�� �����ұ��?\n");
		printf("0. �ڷΰ���\n");
		printf("1. MANDO\n");
		printf("2. CONTINENTAL\n");
		printf("3. BOSCH\n");
	}
	else if (selectionStep == SteeringSystem_Q) {
		printf(CLEAR_SCREEN);
		printf("� ������ġ�� �����ұ��?\n");
		printf("0. �ڷΰ���\n");
		printf("1. BOSCH\n");
		printf("2. MOBIS\n");
	}
	else if (selectionStep == Run_Test) {
		printf(CLEAR_SCREEN);
		printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
		printf("� ������ �ұ��?\n");
		printf("0. ó�� ȭ������ ���ư���\n");
		printf("1. RUN\n");
		printf("2. Test\n");
	}

	printf("===============================\n");
}

bool checkInputValidity(int selectionStep, int answer, char* checkNumber)
{
	//�Է¹��� ���ڰ� ���ڰ� �ƴ϶��
	if (*checkNumber != '\0') {
		printf("ERROR :: ���ڸ� �Է� ����\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == CarType_Q && !(answer >= 1 && answer <= 3)) {
		printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
		delay(800);
		return false;
	}

	if (selectionStep == Engine_Q && !(answer >= 0 && answer <= 4)) {
		printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == brakeSystem_Q && !(answer >= 0 && answer <= 3)) {
		printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == SteeringSystem_Q && !(answer >= 0 && answer <= 2)) {
		printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	if (selectionStep == Run_Test && !(answer >= 0 && answer <= 2)) {
		printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
		delay(MENU_SELECT_DELAY);
		return false;
	}

	return true;
}

#endif