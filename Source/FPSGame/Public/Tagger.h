// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Taggable.h"
#include "Tagger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSGAME_API UTagger : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTagger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TArray<UTaggable*> Taggables;

	void AddTag(UTaggable* Tag);
	void RemoveTag(UTaggable* Tag);
	void SetTags();
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void TagEnemy(FVector BoxSize);


		
};
