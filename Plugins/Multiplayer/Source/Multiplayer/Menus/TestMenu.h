// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TestMenu.generated.h"

/**
 * Test class to test online functionallity with the Multiplayer Subsystem plugin
 */

class UMultiplayerSubsystem;

UCLASS()
class MULTIPLAYER_API UTestMenu : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> HostSessionButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> JoinSessionButton; 
	
	
	int32 NumPublicConnections = 3; 
	FString MatchType{"FREEFORALL"};
	
	/**
	 * Triggered when the "Join Session" button is clicked in the game menu.
	 *
	 * This method handles the event raised by clicking the Join Session button. It displays a debug message on the screen
	 * to indicate that the button has been successfully pressed. Additional behavior related to joining a session can be
	 * implemented here.
	 */
	UFUNCTION()
	void OnJoinSessionButtonClicked();
	
	/**
	 * Triggered when the "Host Session" button is clicked in the game menu.
	 *
	 * This method handles the event raised by clicking the Host Session button. It displays a debug message on the screen
	 * to indicate that the button has been successfully pressed. Additional behavior related to hosting a session can be
	 * implemented here.
	 */
	UFUNCTION()
	void OnHostSessionButtonClicked();

	UPROPERTY()
	UMultiplayerSubsystem* MultiplayerSubsystem;
	
protected:
	/**
	 * Class called when initializing the UserWidgets. Similar to constructor or Begin Play but for Widgets
	 * @return if the class was successfully initialized
	 */
	virtual bool Initialize() override;
	/**
	 * Custom destructor for this class (not a destructor perse, just a function manually called when destructing)
	 */
	void MenuTearDown();
	/**
	 * Cleans up resources and performs necessary teardown operations for the UTestMenu widget.
	 *
	 * This method is automatically invoked when the UTestMenu widget is being destroyed,
	 * ensuring proper cleanup of the widget's state and its associated resources.
	 * It calls the parent class's NativeDestruct method to handle additional destruction logic defined at a higher level.
	 */
	virtual void NativeDestruct() override;

	/**
	 * Callbacks triggered when Delegates are broadcasted from Multiplayer Subsystem
	 * IMPORTANT: This functions should have UFUNCTION(). You never know
	 */	
	
	UFUNCTION()
	void CreateSessionCompleteCallback(bool bSuccess);
	
	// Por ahora dejo el FName SessionName comentado, porque no lo estoy usando desde el callback pero por sis en un futuro lo necesitamos
	void JoinSessionCompleteCallback(/*FName SessionName,*/ EOnJoinSessionCompleteResult::Type Result);

	void FindSessionCompleteCallback(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	
	UFUNCTION()
	void StartSessionCompleteCallback(bool bSuccess);
	
	UFUNCTION()
	void DestroySessionCompleteCallback(bool bSuccess);
	
public:
	/**
	 * Configures and displays the game menu on the user's screen, enabling interaction through input handling.
	 *
	 * This method performs the following steps:
	 * - Adds the widget to the viewport.
	 * - Sets the visibility of the menu to visible and enables it to gain focus.
	 * - Configures the user input mode for UI-only operation by locking
	 *   the input to the viewport and enabling the mouse cursor visibility.
	 *
	 * It ensures that the menu is properly set up for interaction by the player.
	 */
	UFUNCTION(BlueprintCallable)
	void MenuSetup(const int32 NumberPublicConnections = 4, const FString& TypeOfMatch = FString(TEXT("FreeForAll")));
	
	/**
	 * Getters for the buttons
	 */
	FORCEINLINE UButton* GetJoinSessionButton() const { return JoinSessionButton; }
	FORCEINLINE UButton* GetHostSessionButton() const { return HostSessionButton; }
	
};
