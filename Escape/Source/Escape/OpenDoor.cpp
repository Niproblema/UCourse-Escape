// Jan Aleksandrov 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
	Super::BeginPlay();
	Owner = GetOwner();
	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();


}



void UOpenDoor::OperateDoor(float Angle) {
	Owner->SetActorRotation(FRotator(0.f, Angle, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the TriggerVolume for the triggering Actor
	if (PressurePlate->IsOverlappingActor(TriggeringActor)) {
		OperateDoor(OpenAngle);
		LastDoorOpen = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpen >= DoorCloseDelay) {
		OperateDoor(ClosedAngle);
	}

	
}

