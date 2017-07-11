// Fill out your copyright notice in the Description page of Project Settings.

#include "AnCharacter.h"


// Sets default values
AAnCharacter::AAnCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//// 开始销毁
//void AAnCharacter::BeginDestroy()
//{
//}
//
//// 生成时的组件初始化
//void AAnCharacter::PostInitializeComponents()
//{
//}
//
//void AAnCharacter::PawnClientRestart()
//{
//}
//
//void AAnCharacter::PossessedBy(AController * C)
//{
//}
//
//void AAnCharacter::OnRep_PlayerState()
//{
//}
//
//bool AAnCharacter::IsReplicationPausedForConnection(const FNetViewer & ConnectionOwnerNetViewer)
//{
//	return false;
//}
//
//void AAnCharacter::OnReplicationPausedChanged(bool bIsReplicationPaused)
//{
//}
//
//// Called every frame
//void AAnCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void AAnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
//
//void AAnCharacter::OnCameraUpdate(const FVector & CameraLocation, const FRotator & CameraRotation)
//{
//}
//
//FRotator AAnCharacter::GetAimOffsets() const
//{
//	return FRotator();
//}
//
//bool AAnCharacter::IsEnemyFor(AController * TempController) const
//{
//	return false;
//}
//
//void AAnCharacter::AddWeapon(AShooterWeapon * Weapon)
//{
//}
//
//void AAnCharacter::RemoveWeapon(AShooterWeapon * Weapon)
//{
//}
//
//AShooterWeapon * AAnCharacter::FindWeapon(TSubclassOf<class AShooterWeapon> WeaponClass)
//{
//	return nullptr;
//}
//
//void AAnCharacter::EquipWeapon(AShooterWeapon * Weapon)
//{
//}
//
//void AAnCharacter::StartWeaponFire()
//{
//}
//
//void AAnCharacter::StopWeaponFire()
//{
//}
//
//bool AAnCharacter::CanFire() const
//{
//	return false;
//}
//
//bool AAnCharacter::CanReload() const
//{
//	return false;
//}
//
//void AAnCharacter::SetTargeting(bool bNewTargeting)
//{
//}

