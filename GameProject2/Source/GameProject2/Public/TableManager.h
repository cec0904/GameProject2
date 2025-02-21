// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TableManager.generated.h"

UCLASS()
class GAMEPROJECT2_API ATableManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATableManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UStaticMeshComponent* sm_table;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* arrowLeftDown;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* arrowLeftUp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* arrowRightDown;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UArrowComponent* arrowRightUp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UBoxComponent* leftBoxColl;

	//UFUNCTION()
	//void TableLeftSideBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
