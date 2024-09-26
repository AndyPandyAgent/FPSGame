// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CustomCameraComponent.generated.h"

UCLASS()
class FPSGAME_API UCustomCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public: 

	UCustomCameraComponent();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector CamOffsetPos;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector CurCamPos;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head Bob")
    float BobAmplitude = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head Bob")
    float BobFrequency = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head Bob")
    float BobSpeedMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head Bob")
    float WalkBobFrequency = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head Bob")
    float WalkBobAmplitude = 50;
    
    UFUNCTION(BlueprintCallable, Category = "Lean")
    void Lean(float dir, float delta_time, float lean_length, float lean_height, float rot_length);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lean")
    FRotator LeanRot;



    FVector InitialCameraPosition;

    void HandleHeadBob(float DeltaTime);

private:

    float RunningTime;

};
