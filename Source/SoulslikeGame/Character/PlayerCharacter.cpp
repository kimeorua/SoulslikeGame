// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Components/LockOnComponent.h"
#include "../Components/WeaponComponent.h"
#include "../GAS/SoluslikeAbilitySystemComponent.h"
#include "../Weapons/Weapon.h"
#include "../DataAsset/WeaponDataAsset.h"


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//게임 시작시 이동속도 초기화
	GetCharacterMovement()->MaxWalkSpeed = GetMinSpeed();
}


APlayerCharacter::APlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));

	TeamId = FGenericTeamId(0);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::JumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::JumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(DashAndAvoidAction, ETriggerEvent::Triggered, this, &APlayerCharacter::DashStart);
		EnhancedInputComponent->BindAction(DashAndAvoidAction, ETriggerEvent::Completed, this, &APlayerCharacter::DashEnd);
		EnhancedInputComponent->BindAction(DashAndAvoidAction, ETriggerEvent::Canceled, this, &APlayerCharacter::Avoid);

		EnhancedInputComponent->BindAction(FristWeaponSelectAction, ETriggerEvent::Started, this, &APlayerCharacter::SelectFristWeapon);
		EnhancedInputComponent->BindAction(SecondWeaponSelectAction, ETriggerEvent::Started, this, &APlayerCharacter::SelectSecondWeapon);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);

		EnhancedInputComponent->BindAction(CounterParryAction, ETriggerEvent::Started, this, &APlayerCharacter::CounterParry);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
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
		if (TagCountCheak("Action.Avoid") && TagCountCheak("Action.Attack.Jump") && TagCountCheak("Action.GuardBreak") && TagCountCheak("State.Hit.Guard"))
		{
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
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

void APlayerCharacter::DashStart()
{
	//최대속도 달리기 속도로 변경
	GetCharacterMovement()->MaxWalkSpeed = GetMaxSpeed();
}

void APlayerCharacter::DashEnd()
{
	//최대 속도 걷기 속도로 변경
	GetCharacterMovement()->MaxWalkSpeed = GetMinSpeed();
}

void APlayerCharacter::JumpStart()
{
	AbilityActivateWithTag("Action.Jump");
}

void APlayerCharacter::JumpEnd()
{
	StopJumping();
}

void APlayerCharacter::Avoid()
{
	AbilityActivateWithTag("Action.Avoid");
}

void APlayerCharacter::SelectFristWeapon()
{
	if (IsValid(GetWeaponComponent())) 
	{
		GetWeaponComponent()->WeaponSelect(EWeaponType::Sword);

		Equip();
	}
}

void APlayerCharacter::SelectSecondWeapon()
{
	if (IsValid(GetWeaponComponent()))
	{
		GetWeaponComponent()->WeaponSelect(EWeaponType::Axe);

		Equip();
	}
}

void APlayerCharacter::Equip()
{
	AbilityActivateWithTag("Action.Equip");
}

void APlayerCharacter::Attack()
{
	Super::Attack();
}

void APlayerCharacter::SetBoss(AEnemyCharacter* Boss)
{
	if (Boss != nullptr)
	{
		CombetBoss = Boss;
		SetBossUI(CombetBoss);
	}
}

void APlayerCharacter::GuardBreak()
{
	if (!(TagCountCheak("Action.Shield")))
	{
		Super::GuardBreak();
	}
}

void APlayerCharacter::CounterParry()
{
	Super::CounterParry();
}
