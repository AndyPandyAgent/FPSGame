// Fill out your copyright notice in the Description page of Project Settings.


#include "Tagger.h"

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
	Tag->Tagged = false;
	Taggables.Remove(Tag);
}

void UTagger::SetTags() 
{
	UE_LOG(LogTemp, Warning, TEXT("Started thing"));

	for (int32 i = 0; i < Taggables.Num(); i++)
	{
		UTaggable* TaggedIndexer = Taggables[i];
		TaggedIndexer->Tagged = true;
		UE_LOG(LogTemp, Warning, TEXT("Did thing"));
	}
}

void UTagger::TagEnemy(float Range) 
{


	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Range);

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewPointLocation, LineTraceEnd, ECC_Visibility);

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, HitResult.Location, FColor::Green, false, 2.0f, 0, 2.0f);


	if (HitResult.GetActor()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("GotActor"));

		if (HitResult.GetActor()->ActorHasTag("Enemy"))
		{
			UE_LOG(LogTemp, Warning, TEXT("IsEnemy"));

			UTaggable* Taggable = Cast<UTaggable>(HitResult.GetActor()->GetComponentByClass(UTaggable::StaticClass()));

			AddTag(Taggable);
		}
	}

}
