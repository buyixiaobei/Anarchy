// Fill out your copyright notice in the Description page of Project Settings.

#include "AnWeapon.h"
#include "Anarchy.h"
#include "Player/AnCharacter.h"
#include "Particles/ParticleSystemComponent.h"



// ����Ĭ�ϵ�ֵ
AAnWeapon::AAnWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WeaponMesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh1P"));
	WeaponMesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	WeaponMesh1P->bReceivesDecals = false;
	WeaponMesh1P->CastShadow = false;
	WeaponMesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponMesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = WeaponMesh1P;

	WeaponMesh3P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh3P"));
	WeaponMesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	WeaponMesh3P->bReceivesDecals = false;
	WeaponMesh3P->CastShadow = true;
	WeaponMesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponMesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh3P->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponMesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	WeaponMesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	WeaponMesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	//RootComponent = WeaponMesh3P;
	WeaponMesh3P->SetupAttachment(WeaponMesh1P);

	PrimaryActorTick.bCanEverTick = true;

	bLoopedMuzzleFX = false;
	bLoopedFireAnim = false;
	bPlayingFireAnim = false;
	bIsEquipped = false;
	bWantsToFire = false;
	bPendingReload = false;
	bPendingEquip = false;
	CurrentState = EWeaponState::Idle;

	CurrentAmmo = 100;
	CurrentAmmoInClip = 30;
	BurstCounter = 0;
	LastFireTime = 0.0f;
}

//void AAnWeapon::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//}
//
//void AAnWeapon::Destroyed()
//{
//	Super::Destroyed();
//}

/** =================================================== �ӵ�( Ammo ) ============================================== */

void AAnWeapon::GiveAmmo(int AddAmount)
{
	
}

void AAnWeapon::UseAmmo()
{
	
}

/** =================================================== ���( Inventory ) ============================================== */

void AAnWeapon::OnEnterInventory(AAnCharacter* NewOwner)
{

}

void AAnWeapon::OnLeaveInventory()
{

}


/** =================================================== ����װ��( Weapon Equip ) ============================================== */

void AAnWeapon::OnEquip(const AAnWeapon* LastWeapon)
{
	// ��װ����������Pawn��
	AttachMeshToPawn();

	// ����״̬�ĸ���
	bPendingEquip = true;
	DetermineWeaponState();

	// ����л���������Ч���򲥷Ŷ���
	if (LastWeapon)
	{
		// ��ȡװ���������Ķ���ִ��ʱ��
		float Duration = PlayWeaponAnimation(EquipAnim);

		// ��ֹ����Bug������
		if (Duration <= 0.0f)
		{
			Duration = 0.5f;
		}

		EquipStartedTime = GetWorld()->GetTimeSeconds();
		EquipDuration = Duration;

		// ��������װ��ʱ����ɵĶ�ʱ��
		GetWorldTimerManager().SetTimer(TimerHandle_OnEquipFinished, this, &AAnWeapon::OnEquipFinished, Duration, false);
	}
	else
	{
		OnEquipFinished();
	}

	// ����װ������Ч
	if (MyPawn && MyPawn->IsLocallyControlled())
	{
		PlayWeaponSound(EquipSound);
	}
}

void AAnWeapon::OnEquipFinished()
{
	AttachMeshToPawn();
	bIsEquipped = true;
	bPendingEquip = false;

	// ���µ�ǰ����״̬
	DetermineWeaponState();

	if (MyPawn)
	{
		// ���װ����������ǰ����Ϊ�գ�����ȥ���»��ӵ�
		if (MyPawn->IsLocallyControlled() && CurrentAmmoInClip <= 0 && CanReload())
		{
			
		}
	}
}

void AAnWeapon::OnUnEquip()
{
	// ���������Pawn�İ�
	DetachMeshFromPawn();
	bIsEquipped = false;
	//StopFire();

	// ��װ��״̬
	if (bPendingReload)
	{

	}

	// ��װ��״̬
	if (bPendingEquip)
	{

	}

	// ȷ����ǰ����״̬
	DetermineWeaponState();

}

//
void AAnWeapon::OnBurstStarted()
{

}

//
void AAnWeapon::OnBurstFinished()
{

}

// ���µ�ǰ������״̬
void AAnWeapon::SetWeaponState(EWeaponState NewState)
{
	const EWeaponState PreState = CurrentState;

	if (PreState == EWeaponState::Firing && NewState != EWeaponState::Firing)
	{
		// ��������
		OnBurstFinished();
	}

	CurrentState = NewState;

	if (PreState != EWeaponState::Firing && NewState == EWeaponState::Firing)
	{
		// ��ʼ����
		OnBurstStarted();
	}
}

// ����������ǰ��״̬
void AAnWeapon::DetermineWeaponState()
{
	EWeaponState NewState = EWeaponState::Idle;

	if (bIsEquipped)//��װ��
	{
		if (bPendingReload)//��װ��
		{
			if (CanReload() == false)//����װ��
			{
				NewState = CurrentState;
			}
			else//��װ��
			{
				NewState = EWeaponState::Reloading;
			}
		}
		// �ɿ���
		else if ((bPendingReload == false) && (bWantsToFire == true) && (CanFire() == true))
		{
			NewState = EWeaponState::Firing;
		}
	}
	// ��װ��
	else if (bPendingEquip)
	{
		NewState = EWeaponState::Equipping;
	}

	// ����������ǰ״̬
	SetWeaponState(NewState);
}

// ��������Pawn��
void AAnWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		// �Ƴ���ǰ�Ѿ��󶨵�����װ��
		//DetachMeshFromPawn();

		// ��ȡָ���İ󶨲�����ƣ�Ȼ��󶨵�Pawn��
		FName AttachName = MyPawn->GetWeaponAttachName();
		//if (MyPawn->IsLocallyControlled() == true)
		//{
			//USkeletalMeshComponent* PawnMesh1P = MyPawn->GetSpecifcPawnMesh(true);
			USkeletalMeshComponent* PawnMesh3P = MyPawn->GetSpecifcPawnMesh(false);
			//WeaponMesh1P->SetHiddenInGame(false);
			WeaponMesh3P->SetHiddenInGame(false);
			//WeaponMesh1P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, AttachName);
			WeaponMesh3P->AttachToComponent(PawnMesh3P, FAttachmentTransformRules::KeepRelativeTransform, AttachName);
		//}
		//// ��������
		//else 
		//{ 
		//	USkeletalMeshComponent* UseWeaponMesh = GetWeaponMesh();
		//	USkeletalMeshComponent* UsePawnMesh = MyPawn->GetPawnMesh();
		//	UseWeaponMesh->AttachToComponent(UsePawnMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachName);
		//	UseWeaponMesh->SetHiddenInGame(false);
		//}
	}
}

// ���������
void AAnWeapon::DetachMeshFromPawn()
{
	WeaponMesh1P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh1P->SetHiddenInGame(true);

	WeaponMesh3P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh3P->SetHiddenInGame(true);
}

void AAnWeapon::OnRep_MyPawn()
{

}

void AAnWeapon::OnRep_BurstCounter()
{

}

void AAnWeapon::OnRep_Reload()
{

}


// Called when the game starts or when spawned
void AAnWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnWeapon::SetOwningPawn(AAnCharacter* AnCharacter)
{
	if (MyPawn != AnCharacter)
	{
		Instigator = AnCharacter;
		MyPawn = AnCharacter;
		SetOwner(AnCharacter);
	}
}

/** =================================================== ����( Input ) ============================================== */

// ��ʼ������
void AAnWeapon::StartReload(bool bFromReplication) 
{

}

/** =================================================== ����( Control ) ============================================== */

// �Ƿ�ɿ���
bool AAnWeapon::CanFire() const
{
	return true;
}

// �Ƿ�ɻ�����
bool AAnWeapon::CanReload() const
{
	return true;
}


/** =================================================== ��ȡ����( GETTER ) ============================================== */

USkeletalMeshComponent* AAnWeapon::GetWeaponMesh() const
{
	return (MyPawn != NULL && MyPawn->IsFirstPerson()) ? WeaponMesh1P : WeaponMesh3P;
}

AAnCharacter* AAnWeapon::GetPawnOwner() const
{
	return MyPawn;
}

/** =================================================== ����ʹ��( Weapon Use ) ============================================== */

// ����������Ч
UAudioComponent* AAnWeapon::PlayWeaponSound(USoundCue* Sound)
{
	UAudioComponent* Audio = NULL;
	if (Sound && MyPawn)
	{
		Audio = UGameplayStatics::SpawnSoundAttached(Sound, MyPawn->GetRootComponent());
	}
	return Audio;
}

// ������������
float AAnWeapon::PlayWeaponAnimation(const FWeaponAnim& Animation)
{
	float Duration = 0.5f;
	if (MyPawn)
	{
		UAnimMontage* UseAnim = MyPawn->IsFirstPerson() ? Animation.Pawn1P : Animation.Pawn3P;
		if (UseAnim)
		{
			Duration = MyPawn->PlayAnimMontage(UseAnim);
		}
	}

	return Duration;
}

// ֹͣ�������ڲ��ŵĶ���
void AAnWeapon::StopWeaponAnimation(const FWeaponAnim& Animation)
{

}



/** =================================================== ��������( Replicated ) ============================================== */

void AAnWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAnWeapon, MyPawn);

	DOREPLIFETIME_CONDITION(AAnWeapon, CurrentAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AAnWeapon, CurrentAmmoInClip, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AAnWeapon, BurstCounter, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AAnWeapon, bPendingReload, COND_SkipOwner);
}