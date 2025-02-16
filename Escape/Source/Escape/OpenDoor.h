// Jan Aleksandrov 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnCloseRequest;
private:
	UPROPERTY(EditAnywhere)
		float TriggerWeight = 50.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume * PressurePlate = nullptr;

	AActor * Owner = nullptr;

	float GetMassOnPlate();

};
