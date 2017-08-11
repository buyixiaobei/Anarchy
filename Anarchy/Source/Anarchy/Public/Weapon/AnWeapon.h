// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Canvas.h" // for FCanvasIcon
#include "AnWeapon.generated.h"

class UAnimMontage;
class AAnCharacter;
class UAudioComponent;
class UParticleSystemComponent;
class UCameraShake;
class UForceFeedbackEffect;
class USoundCue;

// 武器状态枚举
//namespace EWeaponState
//{
//	enum Type
//	{
//		Idle,
//		Firing,
//		Reloading,
//		Equipping,
//	};
//}

//UENUM()
//enum EWeaponState
//{
//	Idle,
//	Firing,
//	Reloading,
//	Equipping,
//};

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** 无限子弹开关 */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteAmmo;

	/** infinite ammo in clip, no reload required */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteClip;

	/** 最大子弹数 */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 MaxAmmo;

	/** 记录当前弹夹子弹数 */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 AmmoPerClip;

	/** 初始化当前弹夹子弹数 */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 InitialClips;

	/** 射击频率 */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float TimeBetweenShots;

	/** 如果武器不会对它有任何动画的安全加载时间 */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float NoAnimReloadDuration;

	/** 武器默认设置 */
	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteClip = false;
		MaxAmmo = 100;
		AmmoPerClip = 20;
		InitialClips = 4;
		TimeBetweenShots = 0.2f;
		NoAnimReloadDuration = 1.0f;
	}
};

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

	/** animation played on pawn (1st person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* Pawn1P;

	/** animation played on pawn (3rd person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* Pawn3P;
};


UCLASS()
class ANARCHY_API AAnWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAnWeapon();

	/** 平台的初始化设置 */
	//virtual void PostInitializeComponents() override;

	//virtual void Destroyed() override;

	/** =================================================== 子弹( Ammo ) ============================================== */

	// 子弹类型枚举
	enum class EAmmoType
	{
		EBullet,
		ERocket,
		EMax,
	};

	/** [服务器] 添加子弹 */
	void GiveAmmo(int AddAmount);

	/** 消耗子弹 */
	void UseAmmo();

	/** 查询弹药类型 */
	virtual EAmmoType GetAmmoType() const
	{
		return EAmmoType::EBullet;
	}

	/** =================================================== 库存( Inventory ) ============================================== */

	/** 武器开始被指定的玩家装备 */
	virtual void OnEquip(const AAnWeapon* LastWeapon);

	/** 武器已被指定的玩家装备 */
	virtual void OnEquipFinished();

	/** 武器被指定的玩家解除装备 */
	virtual void OnUnEquip();

	///** [服务器] 武器已经被添加进入库存 */
	//virtual void OnEnterInventory(AAnCharacter* NewOwner);

	///** [服务器] 武器已经从库存中移除 */
	//virtual void OnLeaveInventory();

	/** 检查当前要装备的东西是否已装备 */
	bool IsEquipped() const;

	/** 检查Mesh是否已经绑定到Pawn上 */
	bool IsAttachedToPawn() const;


	/** 设置这个武器的拥有者 */
	void SetOwningPawn(AAnCharacter* AnCharacter);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
