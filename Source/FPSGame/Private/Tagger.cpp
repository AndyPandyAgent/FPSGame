// Fill out your copyright notice in the Description page of Project Settings.


#include "Tagger.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTagger::UTagger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTagger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTagger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTagger::AddTag(UTaggable* Tag) 
{
	Taggables.Add(Tag);
	SetTags();
}

void UTagger::RemoveTag(UTaggable* Tag) 
{
	Taggables.Remove(Tag);
}

void UTagger::SetTags() 
{
	for (int32 i = 0; i < Taggables.Num(); i++)
	{
		UTaggable* TaggedIndexer = Taggables[i];
		TaggedIndexer->Tagged = true;
	}
}

void UTagger::TagEnemy(float Range) 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	const FQuat ShapeRotation = PlayerViewPointRotation.Quaternion();

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Range);

	FHitResult HitResult;

	//GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility);

	//Start to a capsue collision for better tag precision
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(5000, 50, 50));

	GetWorld()->SweepMultiByChannel(HitResult, PlayerViewPointLocation, LineTraceEnd, ShapeRotation, ECC_Visibility, Shape);

	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, HitResult.Location, FColor::Green, false, 2.0f, 0, 2.0f);

	DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5000, 50, 50), ShapeRotation, FColor::Red, false, 2.0f);
	

	if (HitResult.GetActor()) 
	{
		if (HitResult.GetActor()->ActorHasTag("Enemy"))
		{
			UTaggable* Taggable = Cast<UTaggable>(HitResult.GetActor()->GetComponentByClass(UTaggable::StaticClass()));

			if (!Taggable->Tagged) 
			{
				Taggable->ChangeMat();

				AddTag(Taggable);
			}
		}
	}
}
