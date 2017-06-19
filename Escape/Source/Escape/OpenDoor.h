// Jan Aleksandrov 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OperateDoor(float);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = -120.f;
	UPROPERTY(EditAnywhere)
		float ClosedAngle = -50.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume * PressurePlate;

	AActor * TriggeringActor;//Pawn inhgerits from actor
	float LastDoorOpen;
	AActor * Owner;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5f;


};
