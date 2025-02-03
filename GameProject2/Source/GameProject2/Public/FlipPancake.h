// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlipPancake.generated.h"

UCLASS()
class GAMEPROJECT2_API AFlipPancake : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlipPancake();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class USceneComponent* DefaultSceneRoot;

	// Ä¸½¶ ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class UCapsuleComponent* CapsuleComponent;

	// FixedCamera ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FixedCamera;

	// Cube ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* Cube;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


};
