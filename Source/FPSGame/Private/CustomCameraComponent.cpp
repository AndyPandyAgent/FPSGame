// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCameraComponent.h"

UCustomCameraComponent::UCustomCameraComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	RunningTime = 0.0f;

}

// Called when the game starts or when spawned
void UCustomCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CameraComponent)
	{
		InitialCameraPosition = CameraComponent->GetRelativeLocation();
	}
}

// Called every frame
void UCustomCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleHeadBob(DeltaTime);
}

void UCustomCameraComponent::HandleHeadBob(float DeltaTime)
{
	RunningTime += DeltaTime * BobSpeedMultiplier;

	if (Speed > 0) 
	{
		float BobOffsetZ = FMath::Sin(RunningTime * (WalkBobFrequency)) * WalkBobAmplitude;
		float BobOffsetY = FMath::Sin(RunningTime * WalkBobFrequency / 2) * (WalkBobAmplitude);

		if (CameraComponent)
		{
			CameraComponent->SetRelativeLocation(FMath::Lerp(CameraComponent->GetRelativeLocation(),
				InitialCameraPosition + FVector(0.0f, BobOffsetY, BobOffsetZ), DeltaTime));
		}
	}
	else 
	{
		float BobOffsetZ = FMath::Sin(RunningTime * (BobFrequency)) * BobAmplitude;
		float BobOffsetY = FMath::Sin(RunningTime * BobFrequency) * (BobAmplitude / 2.0f);

		if (CameraComponent)
		{
			CameraComponent->SetRelativeLocation(FMath::Lerp(CameraComponent->GetRelativeLocation(), 
				InitialCameraPosition + FVector(0.0f, BobOffsetY, BobOffsetZ), DeltaTime));
		}
	}
}

void UCustomCameraComponent::Lean(float dir, float delta_time, float lean_lenght, float lean_height, float rot_length) 
{
	float Value = 2000 * dir;

	SetRelativeLocation(FMath::Lerp(GetRelativeLocation(), FVector(0, lean_lenght * dir, lean_height), 0.1));
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

	LeanRot = FRotator( FQuat::Slerp(GetRelativeRotation().Quaternion(), (FRotator(0, 0, rot_length * dir)).Quaternion(), 0.2) );
}