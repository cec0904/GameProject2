// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Customer.generated.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	IDLE,
	ENTRY,
	ORDER,
	WAIT,
	CHECK,
	EXIT
};

UCLASS()
class GAMEPROJECT2_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	ECustomerState customerState = ECustomerState::IDLE;

	// 주문할 음식
	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<FString> menu = {TEXT("Bossam"), TEXT("Cockle"), TEXT("Jeon")};

	// 음식 재주문 시간(60, 90, 180)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<float> reorderTime = { 5, 7, 10 };

	// 음식 재주문 시간 배열 값을 받을 변수
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float v_reorderTime;

	// 술 재주문 시간(30, 60, 90)
	// 주문횟수(1~3 랜덤값)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	int32 orderCnt;

	// 손님이 메뉴 기다리는 시간
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float waitingTime = 0;

	// 먹을 동안 재주문까지 기다리는 시간
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float reorderWaitingTime = 0;

	// 손님이 서빙받아야하는 시간(손님 타이머)
	UPROPERTY(EditAnywhere, Category = "MySettings")
	float servingTime = 20;

	// 서빙됐는지 확인 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	bool bServed = false;

	// 손님 시작 위치
	UPROPERTY(EditAnywhere, Category = "MySettings")
	FVector startLoc;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class ATableManager* tm;

	FRotator leftRot;

private:
	void Idle();
	void Entry(float _DeltaTime);
	void Order();
	void Wait(float _DeltaTime);
	void Check(float _DeltaTime);
	void Exit();
};
