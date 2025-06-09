#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int carModuleStack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

void doSecondDelay(int ms);
void displayCarTypeAndTestMode(int selectionStep);
bool checkInputValidity(int selectionStep, int answer, char* checkNumber);
int selectTypeOrTestMode(int selectionStep, int answer);
bool isGoBackFirst(int selectionStep, int answer);
bool isPreviousStep(int selectionStep, int answer);
bool getUserInput(char** buf);

enum QuestionType {
	CarType_Q,
	Engine_Q,
	brakeSystem_Q,
	SteeringSystem_Q,
	Run_Test,
};

enum CarType {
	SEDAN = 1,
	SUV,
	TRUCK
};

enum Engine {
	GM = 1,
	TOYOTA,
	WIA
};

enum brakeSystem {
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B
};

enum SteeringSystem {
	BOSCH_S = 1,
	MOBIS
};

enum delayType {
	MENU_SELECT_DELAY = 800,
	TEST_BEFORE_DELAY = 1500,
	TEST_AFTER_DELAY = 2000
};

void doSecondDelay(int ms) {
	volatile int sum = 0;
	for (int j = 0; j < 1000; j++) {
		for (int t = 0; t < ms; t++) {
			sum++;
		}
	}
}

void delay(int ms) {
	for (int i = 0; i < 1000; i++) {
		doSecondDelay(ms);
	}
}

int main() {
	char buf[100];
	int selectionStep = CarType_Q;

	while (true) {
		displayCarTypeAndTestMode(selectionStep);

		printf("INPUT > ");

		char* buffer = buf;
		if (!getUserInput(&buffer)) {
			break;
		}

		char* checkNumber;
		int answer = strtol(buf, &checkNumber, 10); // convert character string to number

		if (!checkInputValidity(selectionStep, answer, checkNumber)) {
			continue;
		}

		// Go back the first Menu
		if (isGoBackFirst(selectionStep, answer)) {
			continue;
		}

		// Go back the previouse Menu
		if (isPreviousStep(selectionStep, answer)) {
			selectionStep -= 1;
			continue;
		}

		// select type and test mode
		selectionStep = selectTypeOrTestMode(selectionStep, answer);
	}
}

bool getUserInput(char **buf)
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

int selectTypeOrTestMode(int selectionStep, int answer)
{
	if (selectionStep == CarType_Q) {
		selectCarType(answer);
		delay(MENU_SELECT_DELAY);
		selectionStep = Engine_Q;
	}
	else if (selectionStep == Engine_Q) {
		selectEngine(answer);
		delay(MENU_SELECT_DELAY);
		selectionStep = brakeSystem_Q;
	}
	else if (selectionStep == brakeSystem_Q) {
		selectbrakeSystem(answer);
		delay(MENU_SELECT_DELAY);
		selectionStep = SteeringSystem_Q;
	}
	else if (selectionStep == SteeringSystem_Q) {
		selectSteeringSystem(answer);
		delay(MENU_SELECT_DELAY);
		selectionStep = Run_Test;
	}
	else if (selectionStep == Run_Test && answer == 1) {
		runProducedCar();
		delay(TEST_AFTER_DELAY);
	}
	else if (selectionStep == Run_Test && answer == 2) {
		printf("Test...\n");
		delay(TEST_BEFORE_DELAY);
		testProducedCar();
		delay(TEST_AFTER_DELAY);
	}

	return selectionStep;
}

void selectCarType(int answer) {
	carModuleStack[CarType_Q] = answer;
	if (answer == 1) printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
	if (answer == 2) printf("차량 타입으로 SUV을 선택하셨습니다.\n");
	if (answer == 3) printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer) {
	carModuleStack[Engine_Q] = answer;
	if (answer == 1) printf("GM 엔진을 선택하셨습니다.\n");
	if (answer == 2) printf("TOYOTA 엔진을 선택하셨습니다.\n");
	if (answer == 3) printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer) {
	carModuleStack[brakeSystem_Q] = answer;
	if (answer == 1) printf("MANDO 제동장치를 선택하셨습니다.\n");
	if (answer == 2) printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
	if (answer == 3) printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer) {
	carModuleStack[SteeringSystem_Q] = answer;
	if (answer == 1) printf("BOSCH 장치를 선택하셨습니다.\n");
	if (answer == 2) printf("MOBIS 제동장치를 선택하셨습니다.\n");
}

int isValidCheck() {
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

void runProducedCar() {
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

void testProducedCar() {
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

bool isGoBackFirst(int selectionStep, int answer)
{
	if (answer == 0 && selectionStep == Run_Test) {
		selectionStep = CarType_Q;
		true;
	}
	return false;
}

bool isPreviousStep(int selectionStep, int answer)
{
	return (answer == 0 && selectionStep >= 1);
}