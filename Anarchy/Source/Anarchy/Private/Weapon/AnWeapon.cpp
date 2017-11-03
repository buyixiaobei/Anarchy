// Fill out your copyright notice in the Description page of Project Settings.

#include "AnWeapon.h"
#include "Anarchy.h"
#include "Player/AnCharacter.h"
#include "Particles/ParticleSystemComponent.h"



// 设置默认的值
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

/** =================================================== 子弹( Ammo ) ============================================== */

void AAnWeapon::GiveAmmo(int AddAmount)
{
	
}

void AAnWeapon::UseAmmo()
{
	
}

/** =================================================== 库存( Inventory ) ============================================== */

void AAnWeapon::OnEnterInventory(AAnCharacter* NewOwner)
{

}

void AAnWeapon::OnLeaveInventory()
{

}


/** =================================================== 武器装备( Weapon Equip ) ============================================== */

void AAnWeapon::OnEquip(const AAnWeapon* LastWeapon)
{
	// 绑定装备的武器到Pawn上
	AttachMeshToPawn();

	// 武器状态的跟新
	bPendingEquip = true;
	DetermineWeaponState();

	// 如果切换的武器有效，则播放动画
	if (LastWeapon)
	{
		// 获取装备该武器的动画执行时间
		float Duration = PlayWeaponAnimation(EquipAnim);

		// 防止出现Bug的设置
		if (Duration <= 0.0f)
		{
			Duration = 0.5f;
		}

		EquipStartedTime = GetWorld()->GetTimeSeconds();
		EquipDuration = Duration;

		// 开启武器装备时间完成的定时器
		GetWorldTimerManager().SetTimer(TimerHandle_OnEquipFinished, this, &AAnWeapon::OnEquipFinished, Duration, false);
	}
	else
	{
		OnEquipFinished();
	}

	// 播放装备的音效
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

	// 更新当前武器状态
	DetermineWeaponState();

	if (MyPawn)
	{
		// 如果装备的武器当前弹夹为空，尝试去重新换子弹
		if (MyPawn->IsLocallyControlled() && CurrentAmmoInClip <= 0 && CanReload())
		{
			
		}
	}
}

void AAnWeapon::OnUnEquip()
{
	// 解除武器和Pawn的绑定
	DetachMeshFromPawn();
	bIsEquipped = false;
	//StopFire();

	// 待装弹状态
	if (bPendingReload)
	{

	}

	// 待装备状态
	if (bPendingEquip)
	{

	}

	// 确定当前武器状态
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

// 跟新当前武器的状态
void AAnWeapon::SetWeaponState(EWeaponState NewState)
{
	const EWeaponState PreState = CurrentState;

	if (PreState == EWeaponState::Firing && NewState != EWeaponState::Firing)
	{
		// 结束开火
		OnBurstFinished();
	}

	CurrentState = NewState;

	if (PreState != EWeaponState::Firing && NewState == EWeaponState::Firing)
	{
		// 开始开火
		OnBurstStarted();
	}
}

// 决定武器当前的状态
void AAnWeapon::DetermineWeaponState()
{
	EWeaponState NewState = EWeaponState::Idle;

	if (bIsEquipped)//已装备
	{
		if (bPendingReload)//待装弹
		{
			if (CanReload() == false)//不可装弹
			{
				NewState = CurrentState;
			}
			else//可装弹
			{
				NewState = EWeaponState::Reloading;
			}
		}
		// 可开火
		else if ((bPendingReload == false) && (bWantsToFire == true) && (CanFire() == true))
		{
			NewState = EWeaponState::Firing;
		}
	}
	// 待装备
	else if (bPendingEquip)
	{
		NewState = EWeaponState::Equipping;
	}

	// 设置武器当前状态
	SetWeaponState(NewState);
}

// 绑定武器到Pawn上
void AAnWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		// 移除当前已经绑定的武器装备
		//DetachMeshFromPawn();

		// 获取指定的绑定插槽名称，然后绑定到Pawn上
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
		//// 联网处理
		//else 
		//{ 
		//	USkeletalMeshComponent* UseWeaponMesh = GetWeaponMesh();
		//	USkeletalMeshComponent* UsePawnMesh = MyPawn->GetPawnMesh();
		//	UseWeaponMesh->AttachToComponent(UsePawnMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachName);
		//	UseWeaponMesh->SetHiddenInGame(false);
		//}
	}
}

// 解除武器绑定
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

/** =================================================== 输入( Input ) ============================================== */

// 开始换弹夹
void AAnWeapon::StartReload(bool bFromReplication) 
{

}

/** =================================================== 控制( Control ) ============================================== */

// 是否可开火
bool AAnWeapon::CanFire() const
{
	return true;
}

// 是否可换弹夹
bool AAnWeapon::CanReload() const
{
	return true;
}


/** =================================================== 获取数据( GETTER ) ============================================== */

USkeletalMeshComponent* AAnWeapon::GetWeaponMesh() const
{
	return (MyPawn != NULL && MyPawn->IsFirstPerson()) ? WeaponMesh1P : WeaponMesh3P;
}

AAnCharacter* AAnWeapon::GetPawnOwner() const
{
	return MyPawn;
}

/** =================================================== 武器使用( Weapon Use ) ============================================== */

// 播放武器音效
UAudioComponent* AAnWeapon::PlayWeaponSound(USoundCue* Sound)
{
	UAudioComponent* Audio = NULL;
	if (Sound && MyPawn)
	{
		Audio = UGameplayStatics::SpawnSoundAttached(Sound, MyPawn->GetRootComponent());
	}
	return Audio;
}

// 播放武器动画
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

// 停止武器正在播放的动画
void AAnWeapon::StopWeaponAnimation(const FWeaponAnim& Animation)
{

}



/** =================================================== 联网复制( Replicated ) ============================================== */

void AAnWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAnWeapon, MyPawn);

	DOREPLIFETIME_CONDITION(AAnWeapon, CurrentAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AAnWeapon, CurrentAmmoInClip, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AAnWeapon, BurstCounter, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AAnWeapon, bPendingReload, COND_SkipOwner);
}