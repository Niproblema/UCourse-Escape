// Jan Aleksandrov 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	//Reach of Grabb!
	float GrabReach = 150.f;
	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	UInputComponent * InputComponent = nullptr;
	
	//Find attached physics
	void FindPhysicsHandleComponent();
	//Setup attached InputComponent
	void SetupInputComponent();
	//Ray-Cast and grab/release what's in reach
	void Grab();
	void Release();

	//Return hit for first physicsBody in reach
	FHitResult GetFirstPB() const;
	//Get ReachLine
	FVector GetReachLineStart() const;
	FVector GetReachLineEnd() const;
};
