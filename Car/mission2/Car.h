#pragma once
#include <vector>

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

class Car {
public:
	Car();
	virtual ~Car();
	void selectCarType(int types);
	void selectEngine(int types);
	void selectbrakeSystem(int types);
	void selectSteeringSystem(int types);
	void selectTypeOrTestMode(int answer);
	void setSelectStep(int step) { selectStep = step; }
	int getSelectStep() { return selectStep; }
	bool goBackFirst(int answer);
	bool goPreviousStep(int answer);
	void runProducedCar();
	void testProducedCar();
	int isValidCheck();

	static Car& getInstance();
private:
	//std::vector<CarModule*> carModules;
	int selectStep;
	int carModuleStack[10];
};