// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericCharacter.generated.h"

class UInputMappingContext;
struct FInputActionValue;
class UCameraComponent;
class UInputAction;
class UinputComponent;


UCLASS()
class POLISYCACOS_API AGenericCharacter : public ACharacter
{
	GENERATED_BODY()

	// Input Elements
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Input Actions", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Input Actions", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> WalkAction;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Input Actions", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction; 

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Input Actions", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction; 

	// Camera Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

protected:
	virtual void BeginPlay() override;

public:	
	AGenericCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Input Functions
	void Walk(const FInputActionValue& Instance);
	void Look(const FInputActionValue& Instance);

};
