#include "GenericCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"

AGenericCharacter::AGenericCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("First Person Camera"); 
	CameraComponent->SetupAttachment(GetRootComponent());
	
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->bAutoActivate = true;
	CameraComponent->bUsePawnControlRotation = true;
}

void AGenericCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGenericCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* InputCmp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem =	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(
			PlayerController->GetLocalPlayer()
		);
	if (!IsValid(InputCmp) || !IsValid(PlayerController) || !IsValid(Subsystem))
	{
		return;
	}
	
	Subsystem->AddMappingContext(DefaultMappingContext,0);
// Esto bindea las teclas de moverse
	InputCmp->BindAction(WalkAction, ETriggerEvent::Triggered, this, &AGenericCharacter::Walk);
// Esto bindea el ratón para la camara
	InputCmp->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGenericCharacter::Look);
// Esto bindea el control de salto
	InputCmp->BindAction(JumpAction, ETriggerEvent::Started, this, &AGenericCharacter::Jump);
	InputCmp->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGenericCharacter::StopJumping);
	
}

void AGenericCharacter::Walk(const FInputActionValue& Instance)
{
	const FVector2d Value = Instance.Get<FVector2d>();
	if (!IsValid(GetMovementComponent()) || Value.IsNearlyZero())
	{
		return;
	}

	AddMovementInput(GetActorRightVector()  , Value.X);
	AddMovementInput(GetActorForwardVector(), Value.Y);
}

void AGenericCharacter::Look(const FInputActionValue& Instance)
{
	const FVector2d Value = Instance.Get<FVector2d>();
	if (!IsValid(GetMovementComponent()) || Value.IsNearlyZero())
	{
		return;
	}
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void AGenericCharacter::Jump(const FInputActionValue& Instance)
{
	Super::Jump();
}