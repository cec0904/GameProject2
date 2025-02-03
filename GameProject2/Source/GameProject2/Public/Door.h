// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class GAMEPROJECT2_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class USceneComponent* DefaultSceneRoot;

	// 앞박스 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* FrontBoxComponent;

	// 뒷박스 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* BackBoxComponent;


	// Door 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* Door;

	// DoorFrame 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* DoorFrame;


	void Pull();
	void Push();

private:
	bool bIsOpening = false;
	FRotator InitialRotation;
	FRotator TargetRotation;
	float CurrentLerpTime = 0.f;
	float LerpDuration = 1.0f; // 부드럽게 여는 데 걸리는 시간


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
