// Fill out your copyright notice in the Description page of Project Settings.

#include "AnCharacter.h"


// 设置默认值
AAnCharacter::AAnCharacter()
{
	//GetMesh()->bOnlyOwnerSee = false;
	//GetMesh()->bOwnerNoSee = true;
	//GetMesh()->bReceivesDecals = false;
	//GetMesh()->SetCollisionObjectType(ECC_Pawn);
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	//GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	//GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//PrimaryActorTick.bCanEverTick = true;
	//TargetingSpeedModifier = 0.5f;
	//bIsTargeting = false;
	//RunningSpeedModifier = 1.5f;
	//bWantsToRun = false;
	//bWantsToFire = false;
	//LowHealthPercentage = 0.5f;
	//BaseTurnRate = 45.f;
	//BaseLookUpRate = 45.f;

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
FRotator AAnCharacter::GetAimOffsets() const
{
	return FRotator();
}

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


//float AAnCharacter::PlayAnimMontage(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
//{
//	return 0.0f;
//}
//
//void AAnCharacter::StopAnimMontage(UAnimMontage * AnimMontage)
//{
//}
//
//void AAnCharacter::StopAllAnimMontages()
//{
//}
//
//void AAnCharacter::SetupPlayerInputComponent(UInputComponent * InputComponent)
//{
//}

//USkeletalMeshComponent * AAnCharacter::GetPawnMesh() const
//{
//	return nullptr;
//}
//
//FName AAnCharacter::GetWeaponAttachName() const
//{
//	return FName();
//}
//
//int32 AAnCharacter::GetInventoryCount() const
//{
//	return int32();
//}
//
//AShooterWeapon * AAnCharacter::GetInventoryWeapon(int32 index) const
//{
//	return nullptr;
//}
//
//float AAnCharacter::GetTargetingSpeedModifier() const
//{
//	return 0.0f;
//}
//
//bool AAnCharacter::IsTargeting() const
//{
//	return false;
//}
//
//bool AAnCharacter::IsFiring() const
//{
//	return false;
//}
//
//float AAnCharacter::GetRunningSpeedModifier() const
//{
//	return 0.0f;
//}
//
//void AAnCharacter::SetRunning(bool bNewRunning, bool bToggle)
//{
//}

bool AAnCharacter::IsRunning() const
{
	if (!GetCharacterMovement()) 
	{
		return false;
	}
	return false;
}

//bool AAnCharacter::IsFirstPerson() const
//{
//	return false;
//}
//
//int32 AAnCharacter::GetMaxHealth() const
//{
//	return int32();
//}
//
//bool AAnCharacter::IsAlive() const
//{
//	return false;
//}
//
//float AAnCharacter::GetLowHealthPercentage() const
//{
//	return 0.0f;
//}
//
//void AAnCharacter::UpdateTeamColorsAllMIDs()
//{
//}
//
//void AAnCharacter::UpdateRunSounds()
//{
//}
//
//void AAnCharacter::UpdatePawnMeshes()
//{
//}
//
//void AAnCharacter::UpdateTeamColors(UMaterialInstanceDynamic * UseMID)
//{
//}
//
//void AAnCharacter::TornOff()
//{
//}
//
//bool AAnCharacter::IsMoving()
//{
//	return false;
//}

//float AAnCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
//{
//	return 0.0f;
//}

//void AAnCharacter::Suicide()
//{
//}
//
//void AAnCharacter::KilledBy(APawn * EventInstigator)
//{
//}
//
//bool AAnCharacter::CanDie(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser) const
//{
//	return false;
//}
//
//bool AAnCharacter::Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser)
//{
//	return false;
//}

//void AAnCharacter::FellOutOfWorld(const UDamageType & dmgType)
//{
//}
//
//void AAnCharacter::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
//{
//}

//void AAnCharacter::OnDeath(float KillingDamage, FDamageEvent const & DamageEvent, APawn * InstigatingPawn, AActor * DamageCauser)
//{
//}
//
//void AAnCharacter::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser)
//{
//}
//
//void AAnCharacter::SetRagdollPhysics()
//{
//}
//
//void AAnCharacter::ReplicateHit(float Damage, FDamageEvent const & DamageEvent, APawn * InstigatingPawn, AActor * DamageCauser, bool bKilled)
//{
//}
//
//void AAnCharacter::OnRep_LastTakeHitInfo()
//{
//}

/*oid AAnCharacter::SetCurrentWeapon(AShooterWeapon * NewWeapon, AShooterWeapon * LastWeapon)
{
}*/

/*oid AAnCharacter::OnRep_CurrentWeapon(AShooterWeapon * LastWeapon)
{
}*/

//void AAnCharacter::SpawnDefaultInventory()
//{
//}
//
//void AAnCharacter::DestroyInventory()
//{
//}

//oid AAnCharacter::ServerEquipWeapon(AShooterWeapon * NewWeapon)
//{
//}

//void AAnCharacter::ServerSetTargeting(bool bNewTargeting)
//{
//}

//void AAnCharacter::ServerSetRunning(bool bNewRunning, bool bToggle)
//{
//}

//void AAnCharacter::BuildPauseReplicationCheckPoints(TArray<FVector>& RelevancyCheckPoints)
//{
//}
