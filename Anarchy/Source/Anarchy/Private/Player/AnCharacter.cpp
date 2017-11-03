// Fill out your copyright notice in the Description page of Project Settings.

#include "AnCharacter.h"
#include "Weapon/AnWeapon.h"
#include "Anarchy.h"



// ����Ĭ��ֵ
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

// ����ʱ�������ʼ��
void AAnCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if(Role == ROLE_Authority)
	{
		// �������ֵ
		Health = GetMaxHealth();

		// ����Ĭ�ϵ�װ�����
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

// �������¼�
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


// ǰ���ƶ�
void AAnCharacter::MoveForward(float Val)
{
	if (Controller && Val != 0.f)
	{
		// ���Ƹ���ֵ ������ɫ�������� & ����״̬ʱ��
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

// �����ƶ�
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

// ���һ���
void AAnCharacter::TurnAtRate(float Val)
{
	AddControllerYawInput(Val * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

// ���»���
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

// ֹͣ��Ծ
void AAnCharacter::OnStopJump()
{
	bPressedJump = false;
	StopJumping();
}

// ���������
void AAnCharacter::OnCameraUpdate(const FVector & CameraLocation, const FRotator & CameraRotation)
{
}

// ��ȡ��׼ƫ��ֵ
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

// ���Ŷ�����̫��
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

/** =================================================== ���ݻ�ȡ(Getter) ============================================== */

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

// ��ɫ�Ƿ��ǵ�һ�˳�
bool AAnCharacter::IsFirstPerson() const
{
	return false;
	//return IsAlive() && Controller->IsLocalPlayerController();
}

// ��ȡ��ɫ�������ֵ
int32 AAnCharacter::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AAnCharacter>()->Health;
}

// ��ɫ�Ƿ񻹻���
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

	// ֻ�б��������ߣ��������������Ǳ��ط���ģ������ͻ�����Ҫ����
	DOREPLIFETIME_CONDITION(AAnCharacter, Inventory, COND_OwnerOnly);

	// ���˱���ӵ��������������ˣ���ʶ������Ǳ�����ɵġ�
	DOREPLIFETIME_CONDITION(AAnCharacter, bIsTargeting, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AAnCharacter, bWantsToRun, COND_SkipOwner);
	//DOREPLIFETIME_CONDITION(AAnCharacter, LastTakeHitInfo, COND_Custom);

	// �����˶�ӵ�е�
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

/** =================================================== ����( Weapon ) ============================================== */

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

	// �����һ��װ��������
	if (LocalWeapon)
	{
		LocalWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon;

	// װ���µ�����
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
	// �����ǰ��ɫȨ��С��3���򷵻�
	if (Role < ROLE_Authority)
	{
		return;
	}

	// ��ȡĬ�ϵĿ����
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();

	// ����ÿ������ಢ���ɶ�Ӧ������
	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AAnWeapon* NewWeapon = GetWorld()->SpawnActor<AAnWeapon>(DefaultInventoryClasses[i], SpawnInfo);
		AddWeapon(NewWeapon);
	}

	// װ������еĵ�һ������
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
		// ��ǰ�����洢������
		Weapon->OnEnterInventory(this);
		Inventory.AddUnique(Weapon);
	}
}

void AAnCharacter::RemoveWeapon(AAnWeapon * Weapon)
{
	if (Weapon && Role == ROLE_Authority)
	{
		// �Ƴ���ǰ����е�����
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
