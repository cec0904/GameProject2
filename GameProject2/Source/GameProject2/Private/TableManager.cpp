// Fill out your copyright notice in the Description page of Project Settings.


#include "TableManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Customer.h"

ATableManager::ATableManager()
{
	PrimaryActorTick.bCanEverTick = true;

	sm_table = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sm_table"));
	arrowLeftDown = CreateDefaultSubobject<UArrowComponent>(TEXT("arrowLeftDown"));
	arrowLeftUp = CreateDefaultSubobject<UArrowComponent>(TEXT("arrowLeftUp"));
	arrowRightDown = CreateDefaultSubobject<UArrowComponent>(TEXT("arrowRightDown"));
	arrowRightUp = CreateDefaultSubobject<UArrowComponent>(TEXT("arrowRightUp"));

	SetRootComponent(sm_table);
	sm_table->SetRelativeScale3D(FVector(1, 0.7, 0.05));

	leftBoxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("leftBoxColl"));
	leftBoxColl->SetupAttachment(sm_table);
	leftBoxColl->SetBoxExtent(FVector(107.135426, 32, 32));
	leftBoxColl->SetRelativeLocation(FVector(0, -162, 0));

	arrowLeftDown->SetupAttachment(sm_table);
	arrowLeftUp->SetupAttachment(sm_table);
	arrowRightDown->SetupAttachment(sm_table);
	arrowRightUp->SetupAttachment(sm_table);

	arrowLeftDown->SetRelativeLocationAndRotation(FVector(-74, -90, 0), FRotator(0, 90, 0));
	arrowLeftUp->SetRelativeLocationAndRotation(FVector(58, -90, 0), FRotator(0, 90, 0));
	arrowRightDown->SetRelativeLocationAndRotation(FVector(-74, 270, 0), FRotator(0, -90, 0));
	arrowRightUp->SetRelativeLocationAndRotation(FVector(58, 270, 0), FRotator(0, -90, 0));
}

void ATableManager::BeginPlay()
{
	Super::BeginPlay();
	
	/**오버랩시 실행할시 호출 함수 */
	//leftBoxColl->OnComponentBeginOverlap.AddDynamic(this, &ATableManager::TableLeftSideBeginOverlap);
}

// Called every frame
void ATableManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ATableManager::TableLeftSideBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	ACustomer* customer = Cast<ACustomer>(OtherActor);
//
//	if (customer)
//	{
//		FRotator leftRot = FRotator(0.0f, 90.0f, 0.0f); // 왼쪽 (-90도);
//		customer->SetActorRotation(arrowLeftDown->GetComponentRotation());
//		UE_LOG(LogTemp, Warning, TEXT("arrowLeftDown->GetComponentRotation() : %f %f %f"), arrowLeftDown->GetComponentRotation().Roll, arrowLeftDown->GetComponentRotation().Pitch, arrowLeftDown->GetComponentRotation().Yaw);
//		customer->customerState = ECustomerState::ORDER;
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Table Manager::No customer"));
//	}
//}
