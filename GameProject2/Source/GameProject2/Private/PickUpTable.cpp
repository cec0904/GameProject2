// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpTable.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APickUpTable::APickUpTable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//DefaultSceneRoot ���� �� ����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	// Cube ���� �� ����
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetupAttachment(DefaultSceneRoot); // CapsuleComponent�� ����
	Cube->SetRelativeLocation(FVector(0.f, 0.f, -50.f)); // ������ ��ġ

}

// Called when the game starts or when spawned
void APickUpTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

