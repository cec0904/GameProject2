// Fill out your copyright notice in the Description page of Project Settings.


#include "CutMeat.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "MyPlayer.h"

// Sets default values
ACutMeat::ACutMeat()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //DefaultSceneRoot 생성 및 설정
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    SetRootComponent(DefaultSceneRoot);

    // CapsuleComponent 생성 및 설정
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

    //RootComponent = CapsuleComponent; // 캡슐을 루트 컴포넌트로 설정
    CapsuleComponent->InitCapsuleSize(42.f, 96.f); // 캡슐 크기 설정
    CapsuleComponent->SetupAttachment(DefaultSceneRoot);

    // FixedCamera 생성 및 설정
    FixedCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FixedCamera"));
    FixedCamera->SetupAttachment(CapsuleComponent); // 캡슐 컴포넌트에 종속
    // FixedCamera의 상대 위치 설정
    FixedCamera->SetRelativeLocation(FVector(-24.f, 0.f, 54.f)); // 위치: X=-24, Y=0, Z=54

    // FixedCamera의 상대 회전 설정
    FixedCamera->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f)); // 회전: Pitch=0, Yaw=-60, Roll=0

    // FixedCamera의 상대 스케일 설정
    FixedCamera->SetRelativeScale3D(FVector(0.3f)); // 스케일: X=0.3, Y=0.3, Z=0.3설정

    // Cube 생성 및 설정
    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    Cube->SetupAttachment(CapsuleComponent); // CapsuleComponent에 종속
    Cube->SetRelativeLocation(FVector(0.f, 0.f, -50.f)); // 적절한 위치


    GuideLineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GuideLine"));
    GuideLineMesh->SetupAttachment(Cube);
    GuideLineMesh->SetVisibility(false); // 기본적으로 숨김

    bIsCutting = false;
    bIsCutComplete = false;
    bCanPickup = false;
    CutProgress = 0.0f;
}

// Called when the game starts or when spawned
void ACutMeat::BeginPlay()
{
    Super::BeginPlay();
    PlayerRef = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

//  시점 변경 시 안내선 표시
void ACutMeat::StartCutting()
{
    if (bIsCutComplete) return;

    UE_LOG(LogTemp, Warning, TEXT("Cutting Mode Activated!"));

    bIsCutting = true;
    GuideLineMesh->SetVisibility(true);
}

// 마우스 드래그로 절단 진행
void ACutMeat::UpdateCutting(FVector2D MousePosition)
{
    if (!bIsCutting || bIsCutComplete) return;

    // 마우스 이동량을 CutProgress 값에 반영
    CutProgress += MousePosition.Y * 0.1f;

    // 절단 완료 체크
    if (CutProgress >= 100.0f)
    {
        bIsCutComplete = true;
        bIsCutting = false;
        bCanPickup = true;
        GuideLineMesh->SetVisibility(false);
        UE_LOG(LogTemp, Warning, TEXT("Cutting Complete! You can now pick up the meat."));
    }
}

//  절단 중지
void ACutMeat::StopCutting()
{
    if (!bIsCutting) return;

    bIsCutting = false;
    UE_LOG(LogTemp, Warning, TEXT("Cutting Stopped."));
}

//  잘라진 고기 들기
void ACutMeat::PickupCutMeat()
{
    if (bCanPickup && PlayerRef)
    {
        Cube->AttachToComponent(PlayerRef->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_socket"));
        bCanPickup = false;
        UE_LOG(LogTemp, Warning, TEXT("Picked up the cut meat!"));
    }
}





// Called every frame
void ACutMeat::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

