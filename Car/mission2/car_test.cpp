#include "gmock/gmock.h"
#include "Car.h"

using namespace testing;

class MockCar : public Car {
public:
	MOCK_METHOD(void, selectCarType, (int types), ());
	MOCK_METHOD(void, selectEngine, (int types), ());
	MOCK_METHOD(void, selectbrakeSystem, (int types), ());
	MOCK_METHOD(void, selectSteeringSystem, (int types), ());
	MOCK_METHOD(void, selectTypeOrTestMode, (int types), ());
	MOCK_METHOD(int, getSelectStep, (), ());
	MOCK_METHOD(bool, goBackFirst, (int answer), ());
	MOCK_METHOD(bool, goPreviousStep, (int answer), ());
	MOCK_METHOD(bool, isValidCheck, (), ());
	MOCK_METHOD(void, testProducedCar, (), ());
	MOCK_METHOD(void, runProducedCar, (), ());
};

TEST(SelectCarType, SelectCarTypeSedan) {
	MockCar mock;

	EXPECT_CALL(mock, selectCarType(_));
	mock.selectCarType(SEDAN);
}
/*
TEST(SelectCarType, SelectCarTypeSuv) {
	MockCar mock;

	EXPECT_CALL(mock, selectCarType(_));
	mock.selectCarType(SUV);
}

TEST(SelectCarType, SelectCarTypeTruck) {
	MockCar mock;

	EXPECT_CALL(mock, selectCarType(_));
	mock.selectCarType(TRUCK);
}
*/
TEST(SelectEngine, SelectEngineGm) {
	MockCar mock;

	EXPECT_CALL(mock, selectEngine(_));
	mock.selectEngine(GM);
}

TEST(SelectEngine, SelectEngineToyota) {
	MockCar mock;

	EXPECT_CALL(mock, selectEngine(_));
	mock.selectEngine(TOYOTA);
}

TEST(SelectEngine, SelectEngineWia) {
	MockCar mock;

	EXPECT_CALL(mock, selectEngine(_));
	mock.selectEngine(WIA);
}

TEST(SelectbrakeSystem, SelectbrakeSystemMando) {
	MockCar mock;

	EXPECT_CALL(mock, selectbrakeSystem(_));
	mock.selectbrakeSystem(MANDO);
}

TEST(selectSteeringSystem, SelectbrakeSystemBosch) {
	MockCar mock;

	EXPECT_CALL(mock, selectbrakeSystem(_));
	mock.selectbrakeSystem(BOSCH_S);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeCarType) {
	MockCar mock;

	EXPECT_CALL(mock, selectTypeOrTestMode(_));
	mock.selectTypeOrTestMode(0);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeCarTypeValue) {
	Car::getInstance().selectTypeOrTestMode(CarType_Q);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(Engine_Q, ret);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeEngine) {
	MockCar mock;

	EXPECT_CALL(mock, selectTypeOrTestMode(_));
	mock.selectTypeOrTestMode(CarType_Q);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeEngineValue) {
	Car::getInstance().selectTypeOrTestMode(Engine_Q);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(brakeSystem_Q, ret);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeBreak) {
	MockCar mock;

	EXPECT_CALL(mock, selectTypeOrTestMode(_));
	mock.selectTypeOrTestMode(brakeSystem_Q);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeBreakValue) {
	Car::getInstance().selectTypeOrTestMode(brakeSystem_Q);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(SteeringSystem_Q, ret);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeSteer) {
	MockCar mock;

	EXPECT_CALL(mock, selectTypeOrTestMode(_));
	mock.selectTypeOrTestMode(SteeringSystem_Q);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeSteerValue) {
	Car::getInstance().selectTypeOrTestMode(SteeringSystem_Q);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(Run_Test, ret);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeTest) {
	MockCar mock;

	EXPECT_CALL(mock, selectTypeOrTestMode(_));
	mock.selectTypeOrTestMode(Run_Test);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeTestValue) {
	Car::getInstance().selectTypeOrTestMode(1);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(Run_Test, ret);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeTest2) {
	MockCar mock;

	EXPECT_CALL(mock, selectTypeOrTestMode(_));
	mock.selectTypeOrTestMode(Run_Test);
}

TEST(selectTypeOrTestMode, selectTypeOrTestModeTestValue2) {
	Car::getInstance().selectTypeOrTestMode(2);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(Run_Test, ret);
}

TEST(goBackFirst, goBackFirstValue) {
	Car::getInstance().setSelectStep(Run_Test);
	Car::getInstance().goBackFirst(0);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(CarType_Q, ret);
}

TEST(goPreviousStep, goPreviousStepTrue) {
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().goPreviousStep(0);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(CarType_Q, ret);
}

TEST(goPreviousStep, goPreviousStepFalse) {
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().goPreviousStep(1);
	int ret = Car::getInstance().getSelectStep();

	EXPECT_EQ(Engine_Q, ret);
}


TEST(testProducedCar, testProducedCarTruckWia) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(TRUCK);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(WIA);

	Car::getInstance().testProducedCar();
}

TEST(testProducedCar, testProducedCarTruckMando) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(TRUCK);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(GM);
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(MANDO);

	Car::getInstance().testProducedCar();
}

TEST(testProducedCar, testProducedCarBoschBosch) {
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(BOSCH_B);
	Car::getInstance().setSelectStep(SteeringSystem_Q);
	Car::getInstance().selectSteeringSystem(MOBIS);

	Car::getInstance().testProducedCar();
}

TEST(runProducedCar, runProducedCarSedanContinental) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(SEDAN);
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(CONTINENTAL);

	Car::getInstance().runProducedCar();
}

TEST(runProducedCar, runProducedCarTruckWia) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(TRUCK);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(4);

	Car::getInstance().runProducedCar();
}

TEST(testProducedCar, isValidCheckSedanContinental) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(SEDAN);
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(CONTINENTAL);

	Car::getInstance().testProducedCar();
}

TEST(testProducedCar, isValidCheckSuvToyota) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(SUV);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(TOYOTA);

	Car::getInstance().testProducedCar();
}

TEST(isValidCheck, isValidCheckSedanContinental) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(SEDAN);
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(CONTINENTAL);

	bool ret = Car::getInstance().isValidCheck();

	EXPECT_EQ(false, ret);
}

TEST(isValidCheck, isValidCheckSuvToyota) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(SUV);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(TOYOTA);

	bool ret = Car::getInstance().isValidCheck();

	EXPECT_EQ(false, ret);
}

TEST(isValidCheck, isValidCheckTruckWia) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(TRUCK);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(WIA);

	bool ret = Car::getInstance().isValidCheck();

	EXPECT_EQ(false, ret);
}

TEST(isValidCheck, isValidCheckTruckMando) {
	Car::getInstance().setSelectStep(CarType_Q);
	Car::getInstance().selectCarType(TRUCK);
	Car::getInstance().setSelectStep(Engine_Q);
	Car::getInstance().selectEngine(GM);
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(MANDO);

	bool ret = Car::getInstance().isValidCheck();

	EXPECT_EQ(false, ret);
}

TEST(isValidCheck, isValidCheckBoschBosch) {
	Car::getInstance().setSelectStep(brakeSystem_Q);
	Car::getInstance().selectbrakeSystem(BOSCH_B);
	Car::getInstance().setSelectStep(SteeringSystem_Q);
	Car::getInstance().selectSteeringSystem(MOBIS);

	bool ret = Car::getInstance().isValidCheck();

	EXPECT_EQ(false, ret);
}