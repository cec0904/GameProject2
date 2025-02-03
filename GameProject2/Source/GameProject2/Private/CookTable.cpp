// Fill out your copyright notice in the Description page of Project Settings.


#include "CookTable.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACookTable::ACookTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//DefaultSceneRoot 생성 및 설정
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	// Cube 생성 및 설정
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetupAttachment(DefaultSceneRoot); // CapsuleComponent에 종속
	Cube->SetRelativeLocation(FVector(0.f, 0.f, -50.f)); // 적절한 위치

}

// Called when the game starts or when spawned
void ACookTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACookTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

