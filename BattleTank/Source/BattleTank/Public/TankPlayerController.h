// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Tank.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// Must be the last include



/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333;


private:

	// Start the tank moving the barrel so that a shot would hit where the
	// crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	

	ATank* ControlledTank;


};
