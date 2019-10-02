// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include <iostream>
#include "String.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

#include <DriveSim-Protocol/Camera.h>

#include <DriveSim-Networking/Buffer.h>
#include <DriveSim-Networking/Factory.h>
#include <DriveSim-Networking/UDPNetwork.h>
#include <DriveSim-Networking/Packet.h>
#include <DriveSim-Networking/Parser.h>
#include <DriveSim-Protocol/Camera.h>


//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

FVector anoter;

AMyProjectCharacter::AMyProjectCharacter()
{

	anoter = MyCharacter;

	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
			
	
}
DriveSim::Library::Networking::UDPNetwork network("127.0.0.1");

struct Parser : public DriveSim::Library::Networking::Parser
{
	Parser()
	{
		DriveSim::Library::Networking::Factory::instance()->addTemplate(new DriveSim::Library::Protocol::Camera);
	}

	virtual DriveSim::Library::Networking::Packet* parse(DriveSim::Library::Networking::Buffer& buffer)
	{
		const unsigned char* opcode = buffer.fetch();

		DriveSim::Library::Networking::Packet* packet = DriveSim::Library::Networking::Factory::instance()->packet(*opcode);
		if (packet)
		{
			packet->read(buffer);
		}
		return packet;
	}

};




struct CameraCallback : public DriveSim::Library::Networking::Packet::Callback
{
	virtual void process(DriveSim::Library::Networking::Packet& packet)
	{
		DriveSim::Library::Protocol::Camera* camera = dynamic_cast<DriveSim::Library::Protocol::Camera*>(&packet);
		if (camera)
		{			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%f %f %f %f %f %f"), camera->x, camera->y, camera->z, camera->h, camera->p, camera->r));
			anoter.X = camera->x;
			anoter.Y = camera->y;
			anoter.Z = camera->z;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%f %f %f"), anoter.X, anoter.Y, anoter.Z));

			// screen log player location
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *MyCharacter.ToString()));
		}
	}
};
void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyProjectCharacter::OnResetVR);
}
int main()
{

	// THIS IN THE PLUGIN
	DriveSim::Library::Networking::UDPNetwork network("127.0.0.1");
	network.setPort(5566);
	network.setParser(new Parser);
	network.addCallback((DriveSim::Library::Networking::Packet::Opcode)OPCODE_CAMERA, new CameraCallback);

	while (true)
	{
		network.process();
	}
	return 0;
}
void AMyProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) {
		network.setPort(5566);
		network.setParser(new Parser);
		network.addCallback((DriveSim::Library::Networking::Packet::Opcode)OPCODE_CAMERA, new CameraCallback);		
	}
}


void AMyProjectCharacter::Tick(float DeltaTime)
{
	
	FVector MyCharacter = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *MyCharacter.ToString()));

	if (GEngine) {
		network.process();
	}
}


void AMyProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMyProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AMyProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AMyProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
