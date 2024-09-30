// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class FPSGAME_API AGunActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Gun Functions")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Gun Functions")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Gun Lean")
	void GunLean(float rot_length, float dir);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	bool CanHoldShoot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	bool IsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	bool Reloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float BulletsShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float MagSize = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float spread = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float KickBackForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float AimOffsetSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	float OffsetSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	FRotator CurrentRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Settings")
	FRotator OriginRot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gun Settings")
	FRotator CamCurrentRot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gun Settings")
	FVector AttackPos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gun Settings")
	FVector CurrentGunPos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gun Settings")
	FVector UnrotatedVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gun Lean")
	FRotator LeanRot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gun Lean")
	FRotator CurrentLeanRot;

	UPROPERTY(BlueprintReadWrite, Category = "Gun Pos")
	FVector MouseInput;


private:

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float Range = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float TimeBetweensShots = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float TimeBetweenBullets = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float BulletsPerShot = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float BulletsLeft;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float ReloadTime;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float GunBobFreq;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float GunBobAmp;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float GunBobMulti;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float AimBobFreq;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float AimBobAmp;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float SlowFreq;

	float CurrOffsetSpeed;
	float RunningTime;

	float CurrAmp;
	float CurrFreq;

	float CurrKickBack;

	bool ReadyToShoot = true;
	bool AllowInvoke = true;
	FTimerHandle TimerHandle;
	FTimerHandle ReloadTimerHandle;


	//RECOIL

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	FVector RecoilVector;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	FVector CamRecoilVector;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	FVector AimRecoilVector;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float Snapniness;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float ReturnSpeed;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	float CamSnap;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	FRotator TargetRot;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	FRotator CamTargetRot;

	UPROPERTY(EditAnywhere, Category = "Gun Settings")
	FRotator CamLastTargetRot;




	void PerformLineTrace();

	void Recoil();

	void ResetShot();

	void FinishedReload();
	
	void ActiveGunMovement(float Delta_Time);
};

