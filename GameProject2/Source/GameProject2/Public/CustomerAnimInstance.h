// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Customer.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CustomerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT2_API UCustomerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	class ACustomer* customer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	ECustomerState currentState;
};
