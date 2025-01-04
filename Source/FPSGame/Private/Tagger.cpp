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

void UTagger::TagEnemy(FVector BoxSize) 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	const FQuat ShapeRotation = PlayerViewPointRotation.Quaternion();

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * BoxSize.X/2);

	FHitResult HitResult;

	TArray<FHitResult> SweepResult;

	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(BoxSize.X, BoxSize.Y, BoxSize.Z));

	GetWorld()->SweepMultiByChannel(SweepResult, PlayerViewPointLocation, LineTraceEnd, ShapeRotation, ECC_Visibility, Shape);

	
	for (int32 i = 0; i < SweepResult.Num(); i++)
	{
		if (SweepResult[i].GetActor())
		{
			if (SweepResult[i].GetActor()->ActorHasTag("Enemy"))
			{
				UTaggable* Taggable = Cast<UTaggable>(SweepResult[i].GetActor()->GetComponentByClass(UTaggable::StaticClass()));

				if (!Taggable->Tagged)
				{
					Taggable->ChangeMat();

					AddTag(Taggable);
				}
			}
		}
	}
}
