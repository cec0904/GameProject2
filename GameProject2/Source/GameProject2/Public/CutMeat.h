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

	// ĸ�� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class UCapsuleComponent* CapsuleComponent;

	// FixedCamera ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FixedCamera;

	// Cube ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* Cube;



	// �ȳ����� Mesh (���� ���·� ���̵� ǥ��)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
	class UStaticMeshComponent* GuideLineMesh;

	// �߷��� ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cut")
	TArray<UStaticMeshComponent*> CutPieces;

	// ���� ���� Ȯ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCutting;

	// ���� �Ϸ� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCutComplete;

	// �÷��̾ �� �� �ִ� �������� üũ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanPickup;

	// ���� ���� �Լ�
	void StartCutting();
	void StopCutting();
	void UpdateCutting(FVector2D MousePosition);

	// �߶��� ��⸦ ���
	void PickupCutMeat();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	class AMyPlayer* PlayerRef;

	// ���� ���൵
	float CutProgress;
};
