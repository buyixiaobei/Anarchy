// Fill out your copyright notice in the Description page of Project Settings.

#include "AnCharacter.h"
#include "Weapon/AnWeapon.h"
#include "Anarchy.h"



// 设置默认值
AAnCharacter::AAnCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAnMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PawnMesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("PawnMesh1P"));
	PawnMesh1P->SetupAttachment(GetCapsuleComponent());
	PawnMesh1P->bOnlyOwnerSee = true;
	PawnMesh1P->bOwnerNoSee = false;
	PawnMesh1P->bCastDynamicShadow = false;
	PawnMesh1P->bReceivesDecals = false;
	PawnMesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	PawnMesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	PawnMesh1P->SetCollisionObjectType(ECC_Pawn);
	PawnMesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PawnMesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = true;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

	PrimaryActorTick.bCanEverTick = true;
	TargetingSpeedModifier = 0.5f;
	bIsTargeting = false;
	RunningSpeedModifier = 1.5f;
	bWantsToRun = false;
	bWantsToFire = false;

	LowHealthPercentage = 0.5f;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AAnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// 生成时的组件初始化
void AAnCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if(Role == ROLE_Authority)
	{
		// 最大生命值
		Health = GetMaxHealth();

		// 生成默认的装备库存
		SpawnDefaultInventory();
	}
}

void AAnCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
}

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

void AAnCharacter::BeginDestroy()
{
	Super::BeginDestroy();
}

// 绑定输入事件
void AAnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAnCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAnCharacter::MoveRight);

	PlayerInputComponent->BindAxis("MoveUp", this, &AAnCharacter::MoveUp);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAnCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAnCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAnCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAnCharacter::OnStopJump);

	//PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AAnCharacter::OnStartRunning);
	//PlayerInputComponent->BindAction("RunToggle", IE_Pressed, this, &AAnCharacter::OnStartRunningToggle);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &AAnCharacter::OnStopRunning);


	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::OnStartFire);
	//PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShooterCharacter::OnStopFire);

	//PlayerInputComponent->BindAction("Targeting", IE_Pressed, this, &AShooterCharacter::OnStartTargeting);
	//PlayerInputComponent->BindAction("Targeting", IE_Released, this, &AShooterCharacter::OnStopTargeting);

	//PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &AShooterCharacter::OnNextWeapon);
	//PlayerInputComponent->BindAction("PrevWeapon", IE_Pressed, this, &AShooterCharacter::OnPrevWeapon);

	//PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AShooterCharacter::OnReload);



}


// 前后移动
void AAnCharacter::MoveForward(float Val)
{
	if (Controller && Val != 0.f)
	{
		// 限制俯仰值 （当角色处于行走 & 掉落状态时）
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

// 左右移动
void AAnCharacter::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		const FQuat Rotation = GetActorQuat();
		const FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}

void AAnCharacter::MoveUp(float Val)
{
	if (Val != 0.f)
	{
		// Not when walking or falling.
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			return;
		}
		AddMovementInput(FVector::UpVector, Val);
	}
}

// 左右环顾
void AAnCharacter::TurnAtRate(float Val)
{
	AddControllerYawInput(Val * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

// 上下环顾
void AAnCharacter::LookUpAtRate(float Val)
{
	AddControllerPitchInput(Val * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAnCharacter::OnStartJump()
{
	AAnPlayerController* PC = Cast<AAnPlayerController>(Controller);
	if(PC)
	{
		bPressedJump = true;
	}
}

// 停止跳跃
void AAnCharacter::OnStopJump()
{
	bPressedJump = false;
	StopJumping();
}

// 摄像机更新
void AAnCharacter::OnCameraUpdate(const FVector & CameraLocation, const FRotator & CameraRotation)
{
}

// 获取瞄准偏移值
FRotator AAnCharacter::GetAimOffsets() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}


bool AAnCharacter::IsEnemyFor(AController * TempController) const
{
	return false;
}


void AAnCharacter::StartWeaponFire()
{
}

void AAnCharacter::StopWeaponFire()
{
}

bool AAnCharacter::CanFire() const
{
	return false;
}

bool AAnCharacter::CanReload() const
{
	return false;
}

void AAnCharacter::SetTargeting(bool bNewTargeting)
{
}

// 播放动画蒙太奇
float AAnCharacter::PlayAnimMontage(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* UseMesh = GetPawnMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}

	return 0.0f;
}

void AAnCharacter::StopAnimMontage(UAnimMontage * AnimMontage)
{
}

void AAnCharacter::StopAllAnimMontages()
{
}

//void AAnCharacter::SetupPlayerInputComponent(UInputComponent * InputComponent)
//{
//}

/** =================================================== 数据获取(Getter) ============================================== */

USkeletalMeshComponent * AAnCharacter::GetPawnMesh() const
{
	return IsFirstPerson() ? PawnMesh1P : GetPawnMesh();
}

AAnWeapon * AAnCharacter::GetWeapon() const
{
	return CurrentWeapon;
}

FName AAnCharacter::GetWeaponAttachName() const
{
	return WeaponAttachName;
}

int32 AAnCharacter::GetInventoryCount() const
{
	return int32();
}

//AShooterWeapon * AAnCharacter::GetInventoryWeapon(int32 index) const
//{
//	return nullptr;
//}

float AAnCharacter::GetTargetingSpeedModifier() const
{
	return 0.0f;
}

bool AAnCharacter::IsTargeting() const
{
	return false;
}

bool AAnCharacter::IsFiring() const
{
	return false;
}

float AAnCharacter::GetRunningSpeedModifier() const
{
	return 0.0f;
}


bool AAnCharacter::IsRunning() const
{
	if (!GetCharacterMovement()) 
	{
		return false;
	}
	return  (!GetVelocity().IsZero() && (GetVelocity().GetSafeNormal2D() | GetActorForwardVector()) > -0.1);
}

// 角色是否是第一人称
bool AAnCharacter::IsFirstPerson() const
{
	return false;
	//return IsAlive() && Controller->IsLocalPlayerController();
}

// 获取角色最大生命值
int32 AAnCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AAnCharacter>()->Health;
}

// 角色是否还活着
bool AAnCharacter::IsAlive() const
{
	return Health > 0 ? true : false;
}

float AAnCharacter::GetLowHealthPercentage() const
{
	return 0.0f;
}

USkeletalMeshComponent * AAnCharacter::GetSpecifcPawnMesh(bool WantFirstPerson) const
{
	return WantFirstPerson == true ? PawnMesh1P : GetMesh();
}

void AAnCharacter::UpdateTeamColorsAllMIDs()
{
}

void AAnCharacter::UpdateRunSounds()
{
}

void AAnCharacter::UpdatePawnMeshes()
{
}

void AAnCharacter::UpdateTeamColors(UMaterialInstanceDynamic * UseMID)
{
}

void AAnCharacter::TornOff()
{
}

bool AAnCharacter::IsMoving()
{
	return false;
}

float AAnCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

void AAnCharacter::Suicide()
{
}

void AAnCharacter::KilledBy(APawn * EventInstigator)
{
}

bool AAnCharacter::CanDie(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser) const
{
	return false;
}

bool AAnCharacter::Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser)
{
	return false;
}

void AAnCharacter::FellOutOfWorld(const UDamageType & dmgType)
{
}


/** =================================================== Replication ============================================== */

void AAnCharacter::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
{

}

void AAnCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 只有本地所有者：武器更改请求是本地发起的，其他客户不需要它。
	DOREPLIFETIME_CONDITION(AAnCharacter, Inventory, COND_OwnerOnly);

	// 除了本地拥有者以外的所有人：标识变更都是本地造成的。
	DOREPLIFETIME_CONDITION(AAnCharacter, bIsTargeting, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AAnCharacter, bWantsToRun, COND_SkipOwner);
	//DOREPLIFETIME_CONDITION(AAnCharacter, LastTakeHitInfo, COND_Custom);

	// 所有人都拥有的
	DOREPLIFETIME(AAnCharacter, CurrentWeapon);
	DOREPLIFETIME(AAnCharacter, Health);
}


void AAnCharacter::OnDeath(float KillingDamage, FDamageEvent const & DamageEvent, APawn * InstigatingPawn, AActor * DamageCauser)
{
}

void AAnCharacter::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser)
{
}

void AAnCharacter::SetRagdollPhysics()
{
}

void AAnCharacter::ReplicateHit(float Damage, FDamageEvent const & DamageEvent, APawn * InstigatingPawn, AActor * DamageCauser, bool bKilled)
{
}

void AAnCharacter::OnRep_LastTakeHitInfo()
{
}

/** =================================================== 武器( Weapon ) ============================================== */

void AAnCharacter::SetCurrentWeapon(AAnWeapon * NewWeapon, AAnWeapon * LastWeapon)
{
	AAnWeapon* LocalWeapon = NULL;
	if (LastWeapon != NULL) 
	{
		LocalWeapon = LastWeapon;
	}
	else if(NewWeapon != CurrentWeapon)
	{
		LocalWeapon = CurrentWeapon;
	}

	// 解除上一次装备的武器
	if (LocalWeapon)
	{
		LocalWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon;

	// 装备新的武器
	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void AAnCharacter::OnRep_CurrentWeapon(AAnWeapon * LastWeapon)
{
	SetCurrentWeapon(CurrentWeapon, LastWeapon);
}

void AAnCharacter::SpawnDefaultInventory()
{
	// 如果当前角色权限小于3，则返回
	if (Role < ROLE_Authority)
	{
		return;
	}

	// 获取默认的库存数
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();

	// 遍历每个库存类并生成对应的武器
	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AAnWeapon* NewWeapon = GetWorld()->SpawnActor<AAnWeapon>(DefaultInventoryClasses[i], SpawnInfo);
		AddWeapon(NewWeapon);
	}

	// 装备库存中的第一个武器
	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}

void AAnCharacter::DestroyInventory()
{
}

void AAnCharacter::AddWeapon(AAnWeapon * Weapon)
{
	if (Weapon && Role == ROLE_Authority)
	{
		// 当前武器存储入库存中
		Weapon->OnEnterInventory(this);
		Inventory.AddUnique(Weapon);
	}
}

void AAnCharacter::RemoveWeapon(AAnWeapon * Weapon)
{
	if (Weapon && Role == ROLE_Authority)
	{
		// 移除当前库存中的武器
		Weapon->OnLeaveInventory();
		Inventory.RemoveSingle(Weapon);
	}
}

//AShooterWeapon * AAnCharacter::FindWeapon(TSubclassOf<class AShooterWeapon> WeaponClass)
//{
//	return nullptr;
//}

void AAnCharacter::EquipWeapon(AAnWeapon * Weapon)
{
	if (Weapon)
	{
		if (Role == ROLE_Authority)
		{
			SetCurrentWeapon(Weapon, CurrentWeapon);
		}
		else
		{
			//ServerEquipWeapon(Weapon);
		}
	}

}

bool AAnCharacter::ServerEquipWeapon_Validate(AAnWeapon* Weapon)
{
	return true;
}

void AAnCharacter::ServerEquipWeapon_Implementation(AAnWeapon* Weapon)
{
	EquipWeapon(Weapon);
}

//bool AAnCharacter::ServerSetTargeting_Validate(bool bNewTargeting)
//{
//	return true;
//}
//
//void AAnCharacter::ServerSetTargeting_Implementation(bool bNewTargeting)
//{
//	SetTargeting(bNewTargeting);
//}


/** =================================================== Movement ============================================== */

void AAnCharacter::SetRunning(bool bNewRunning, bool bToggle)
{
}

//bool AAnCharacter::ServerSetRunning_Validate(bool bNewRunning, bool bToggle)
//{
//	return true;
//}
//
//void AAnCharacter::ServerSetRunning_Implementation(bool bNewRunning, bool bToggle)
//{
//	SetRunning(bNewRunning, bToggle);
//}


//void AAnCharacter::ServerSetTargeting(bool bNewTargeting)
//{
//}
//
//void AAnCharacter::ServerSetRunning(bool bNewRunning, bool bToggle)
//{
//}

void AAnCharacter::BuildPauseReplicationCheckPoints(TArray<FVector>& RelevancyCheckPoints)
{
}
