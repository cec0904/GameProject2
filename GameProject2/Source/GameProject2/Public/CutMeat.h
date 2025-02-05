// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CutMeat.generated.h"

UCLASS()
class GAMEPROJECT2_API ACutMeat : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACutMeat();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class USceneComponent* DefaultSceneRoot;

	// 캡슐 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class UCapsuleComponent* CapsuleComponent;

	// FixedCamera 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FixedCamera;

	// Cube 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* Cube;



	// 안내선용 Mesh (선의 형태로 가이드 표시)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* GuideLineMesh;

	// 잘려진 고기 조각
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cut")
	TArray<UStaticMeshComponent*> CutPieces;

	// 절단 상태 확인
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCutting;

	// 절단 완료 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCutComplete;

	// 플레이어가 들 수 있는 상태인지 체크
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanPickup;

	// 절단 진행 함수
	void StartCutting();
	void StopCutting();
	void UpdateCutting(FVector2D MousePosition);

	// 잘라진 고기를 들기
	void PickupCutMeat();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	class AMyPlayer* PlayerRef;

	// 절단 진행도
	float CutProgress;
};
