// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlayer.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "FlipPancake.h"
#include "StirPot.h"
#include "CutMeat.h"
#include "Door.h"
#include "Kismet/GameplayStatics.h"



DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProject1Character

AMyPlayer::AMyPlayer()
{

	// 기본값: FollowCamera 사용 중
	bIsUsingFixedCamera = false;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}





void AMyPlayer::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AMyPlayer::Tick(float DeltaTime)
{
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);

		// Cook
		EnhancedInputComponent->BindAction(CookAction, ETriggerEvent::Started, this, &AMyPlayer::Cook);


		// PullDoor
		EnhancedInputComponent->BindAction(PullDoorAction, ETriggerEvent::Started, this, &AMyPlayer::PullDoor);

		// PushDoor
		EnhancedInputComponent->BindAction(PushDoorAction, ETriggerEvent::Started, this, &AMyPlayer::PushDoor);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyPlayer::Cook()
{
	UE_LOG(LogTemp, Warning, TEXT("요리를 시작합니다."));

	// FixedCamera 사용 중인지 확인
	if (bIsUsingFixedCamera)
	{
		// FollowCamera로 시점 복귀
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->SetViewTargetWithBlend(this, 0.5f); // 부드럽게 FollowCamera로 전환
		}

		bIsUsingFixedCamera = false; // 상태 업데이트
		UE_LOG(LogTemp, Warning, TEXT("Switched back to FollowCamera"));
	}

	else
	{
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);

		// 처리할 클래스들을 배열에 추가
		TArray<UClass*> InteractableClasses = { AFlipPancake::StaticClass(), AStirPot::StaticClass(), ACutMeat::StaticClass() };

		bool bInteracted = false;

		for (AActor* Actor : OverlappingActors)
		{
			AStirPot* StirPot = Cast<AStirPot>(Actor);
			if (StirPot && StirPot->FixedCamera)
			{
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->SetViewTargetWithBlend(StirPot, 0.5f); // FixedCamera로 전환
				}

				bIsUsingFixedCamera = true; // 상태 업데이트
				UE_LOG(LogTemp, Warning, TEXT("Switched to FixedCamera"));
				return;
			}
		}
		for (AActor* Actor : OverlappingActors)
		{
			AFlipPancake* FlipPancake = Cast<AFlipPancake>(Actor);
			if (FlipPancake && FlipPancake->FixedCamera)
			{
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->SetViewTargetWithBlend(FlipPancake, 0.5f); // FixedCamera로 전환
				}

				bIsUsingFixedCamera = true; // 상태 업데이트
				UE_LOG(LogTemp, Warning, TEXT("Switched to FixedCamera"));
				return;
			}
		}

		for (AActor* Actor : OverlappingActors)
		{
			ACutMeat* CutMeat = Cast<ACutMeat>(Actor);
			if (CutMeat && CutMeat->FixedCamera)
			{
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->SetViewTargetWithBlend(CutMeat, 0.5f); // FixedCamera로 전환
				}

				bIsUsingFixedCamera = true; // 상태 업데이트
				UE_LOG(LogTemp, Warning, TEXT("Switched to FixedCamera"));
				return;
			}
		}
	}






	//for (AActor* Actor : OverlappingActors)
	//{

	//	// AStirPot 클래스인지 확인
	//	AStirPot* StirPot = Cast<AStirPot>(Actor);
	//	if (StirPot && StirPot->FixedCamera)
	//	{
	//		// FixedCamera로 시점 변경
	//		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//		if (PlayerController)
	//		{
	//			PlayerController->SetViewTargetWithBlend(StirPot, 0.5f); // 부드럽게 카메라 전환
	//		}

	//		bInteracted = true;
	//		break; // AStirPot이 감지되면 반복 종료


	//	//AFixedCameraActor* FixedCameraActor = Cast<AFixedCameraActor>(Actor);
	//	//if (FixedCameraActor && FixedCameraActor->FixedCamera)
	//	//{
	//	//	// FixedCamera로 시점 변경
	//	//	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//	//	if (PlayerController)
	//	//	{
	//	//		PlayerController->SetViewTargetWithBlend(FixedCameraActor, 0.5f); // 부드럽게 카메라 전환
	//	//	}

	//	//	bInteracted = true;
	//	//	break; // 감지된 경우 반복 종료
	//	//}
	//	}


	//	for (UClass* InteractableClass : InteractableClasses)
	//	{
	//		if (Actor->IsA(InteractableClass))
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Interacted with %s!"), *InteractableClass->GetName());

	//			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//			if (PlayerController)
	//			{
	//				PlayerController->SetViewTargetWithBlend(this, 0.5f);
	//				CameraBoom->TargetArmLength = 0.0f;
	//				
	//				CameraBoom->bUsePawnControlRotation = true;
	//			}

	//			bInteracted = true;
	//			break;
	//		}
	//	}

	//	if (bInteracted)
	//	{
	//		break;
	//	}
	//}

	//if (!bInteracted)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("No interactable actor in range."));
	//}
}

//T
void AMyPlayer::PullDoor()
{

	/*TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);


	for (AActor * Actor : OverlappingActors)
	{
		ADoor* Door = Cast<ADoor>(Actor);
		if(Door)
		{
			Door->AddActorLocalRotation(FRotator(0.f, 90.f, 0.f));
			return;
		}
	}*/

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ADoor::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		ADoor* Door = Cast<ADoor>(Actor);
		if (Door)
		{
			Door->Pull();
			return;
		}
	}

}

//E
void AMyPlayer::PushDoor()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ADoor::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		ADoor* Door = Cast<ADoor>(Actor);
		if (Door)
		{
			Door->Push();
			return;
		}
	}

}

