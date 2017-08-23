// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Classes/Engine/World.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank)
	{
		return;
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(OUT HitLocation)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}

	//Get World location of linetrace thru corsshair
	//If it hits the landscape
		//Tell controlled tank to aim at this point
}

// Line Tracing
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{

	/// Get Viewport size
	int32 ViewPortX, ViewPortY;
	GetViewportSize(OUT ViewPortX, OUT ViewPortY);

	FVector2D ScreenLocation(ViewPortX * CrossHairXLocation, ViewPortY * CrossHairYLocation);

	/// 1. Get player view point information
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	/// 2. Get line trace end
	FVector LineTraceEnd = PlayerViewPointLocation + 1000.f * PlayerViewPointRotation.Vector();

	FCollisionQueryParams TraceParam(FName(TEXT("SimpleTrace")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParam
	);

	if (!Hit.GetComponent())
	{
		return false;
	}
	HitLocation = Hit.Location;
	return true;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}