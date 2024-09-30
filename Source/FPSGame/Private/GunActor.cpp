

#include "GunActor.h"

AGunActor::AGunActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RunningTime = 0.0f;
}

void AGunActor::BeginPlay()
{
	Super::BeginPlay();

	BulletsLeft = MagSize;
}

void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActiveGunMovement(DeltaTime);

	FRotator NewTargetRot = FRotator(FQuat(TargetRot) * FQuat(LeanRot));

	TargetRot = FMath::Lerp(NewTargetRot, OriginRot, ReturnSpeed * DeltaTime);
	CurrentRot = FMath::RInterpTo(CurrentRot, NewTargetRot, DeltaTime, Snapniness);

	CamTargetRot = FMath::Lerp(CamTargetRot, OriginRot, ReturnSpeed * DeltaTime);
	CamCurrentRot = FMath::RInterpTo(CamCurrentRot, CamTargetRot, DeltaTime, CamSnap);

	spread = FMath::Lerp(spread, 0, DeltaTime * 10);

}

void AGunActor::Shoot() 
{
	if (ReadyToShoot && BulletsLeft > 0 && !Reloading)
	{
		for (int i = 0; i < BulletsPerShot && BulletsLeft > 0; ++i)
		{
			PerformLineTrace();
			Recoil();

			BulletsShot += 1;
			BulletsLeft -= 1;

			CurrKickBack = KickBackForce;

			if (BulletsLeft <= 0) break;
		}

		ReadyToShoot = false;

		if (AllowInvoke)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGunActor::ResetShot, TimeBetweensShots, false);
			AllowInvoke = false;
		}
	}
}

void AGunActor::ActiveGunMovement(float Delta_Time) //Weapon sway and weapon bob
{
	FVector CurrentActivePos;
	RunningTime += Delta_Time * CurrFreq;
	float ZOffset = 0.0f;
	float OffsetDiv = 150;
	float MouseDiv = 1;

	if (IsAiming) 
	{
		CurrOffsetSpeed = AimOffsetSpeed;
		CurrAmp = AimBobAmp;
		OffsetDiv = 600;
		MouseDiv = 2;
	}
	else 
	{
		CurrOffsetSpeed = OffsetSpeed;
		CurrAmp = GunBobAmp;
		OffsetDiv = 150;
		MouseDiv = 1;
	}

	if (Speed > 0) 
	{
		CurrFreq = FMath::Lerp(CurrFreq, GunBobFreq, Delta_Time * 5);
	}
	else 
	{
		CurrFreq = FMath::Lerp(CurrFreq, SlowFreq, Delta_Time * 5);
	}

	ZOffset = FMath::Sin((RunningTime * GunBobMulti)) * CurrAmp;

	CurrentActivePos = (UnrotatedVelocity / OffsetDiv) * -1;

	//Kickback

	CurrKickBack = FMath::Lerp(CurrKickBack, 0, 0.2f);

	MouseInput /= MouseDiv;

	SetActorRelativeLocation(FVector(CurrentActivePos.X - CurrKickBack , CurrentActivePos.Y + MouseInput.X, CurrentActivePos.Z - MouseInput.Y + ZOffset));
}

void AGunActor::PerformLineTrace() //The shooting trace
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetActorEyesViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	float y = FMath::RandRange(-spread, spread);
	float x = FMath::RandRange(-spread, spread);

	spread = spread +  0.01f;
	spread = FMath::Clamp(spread, 0, 0.06);

	FVector Start = AttackPos;
	FVector End = Start + ((PlayerViewPointRotation.Vector() + FVector(0, x, y)) * Range);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHit) 
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) 
		{
			//Deal damage here
			UE_LOG(LogTemp, Warning, TEXT("Bang!"));
		}
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 2.0f, 0, 2.0f);
	}
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);

}

void AGunActor::Recoil() //Recoil, lol
{
	if (IsAiming) 
	{
		CamRecoilVector / 10;

		TargetRot += FRotator(AimRecoilVector.X, FMath::RandRange(-AimRecoilVector.Y, AimRecoilVector.Y), FMath::RandRange(-AimRecoilVector.Z, AimRecoilVector.Z));

		CamTargetRot += FRotator(CamRecoilVector.X, FMath::RandRange(-CamRecoilVector.Y, CamRecoilVector.Y), FMath::RandRange(-CamRecoilVector.Z, CamRecoilVector.Z));
	}
	else 
	{
		TargetRot += FRotator(RecoilVector.X, FMath::RandRange(-RecoilVector.Y, RecoilVector.Y), FMath::RandRange(-RecoilVector.Z, RecoilVector.Z));

		CamTargetRot += FRotator(CamRecoilVector.X, FMath::RandRange(-CamRecoilVector.Y, CamRecoilVector.Y), FMath::RandRange(-CamRecoilVector.Z, CamRecoilVector.Z));
	}
}

void AGunActor::ResetShot() 
{
	ReadyToShoot = true;
	AllowInvoke = true;
}

void AGunActor::Reload() 
{
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AGunActor::FinishedReload, ReloadTime, false);
	Reloading = true;
}

void AGunActor::FinishedReload() 
{
	BulletsLeft = MagSize;
	Reloading = false;
}

void AGunActor::GunLean(float rot_length, float dir)
{
	//SetActorRelativeRotation(FRotator(FQuat::Slerp(CurrentLeanRot.Quaternion(), (FRotator(0, 0, rot_length * dir)).Quaternion(), 0.2)));

	LeanRot == FRotator(0, rot_length * dir, 0);

	UE_LOG(LogTemp, Log, TEXT("Rotation: Pitch = %f, Yaw = %f, Roll = %f"), CurrentLeanRot.Pitch, CurrentLeanRot.Yaw, CurrentLeanRot.Roll);


}