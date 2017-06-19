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

	///UE_LOG(LogTemp, Warning, TEXT("GrabberWorking"));
	//Look for physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		///Found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *(GetOwner()->GetName()));
	}
	//Look For Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("InputComponent Found"));
		//Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *(GetOwner()->GetName()));
	}
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

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Triggered!"))

}

