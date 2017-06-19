// Jan Aleksandrov 2017

#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GrabberWorking"));

}


/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	//Logging
	//UE_LOG(LogTemp, Warning, TEXT("Location %s, Position %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())

	///Draw red Line
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * GrabReach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	///Line trace - Ray-cast
		//Setup Query parame
	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	///Logg Hit object
	AActor * ActorHit = Hit.GetActor();
	if (ActorHit)
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(ActorHit->GetName()))


}

