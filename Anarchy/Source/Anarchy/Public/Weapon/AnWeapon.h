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

UENUM()
enum EWeaponState
{
	Idle,
	Firing,
	Reloading,
	Equipping,
};

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
	AAnWeapon(const FObjectInitializer& ObjectInitializer);

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

	/** [服务器] 武器已经被添加进入库存 */
	virtual void OnEnterInventory(AAnCharacter* NewOwner);

	/** [服务器] 武器已经从库存中移除 */
	virtual void OnLeaveInventory();

	/** 检查当前要装备的东西是否已装备 */
	bool IsEquipped() const;

	/** 检查Mesh是否已经绑定到Pawn上 */
	bool IsAttachedToPawn() const;

	/** 绑定武器 */
	void AttachMeshToPawn();

	/** 解除武器绑定 */
	void DetachMeshFromPawn();


	//////////////////////////////////////////////////////////////////////////
	// Input

	///** [local + server] start weapon fire */
	//virtual void StartFire();

	///** [local + server] stop weapon fire */
	//virtual void StopFire();

	/** [all] start weapon reload */
	virtual void StartReload(bool bFromReplication = false);

	///** [local + server] interrupt weapon reload */
	//virtual void StopReload();

	///** [server] performs actual reload */
	//virtual void ReloadWeapon();

	///** trigger reload from server */
	//UFUNCTION(reliable, client)
	//void ClientStartReload();

	//////////////////////////////////////////////////////////////////////////
	// Control

	/** check if weapon can fire */
	bool CanFire() const;

	/** 检查武器是否可以换子弹 */
	bool CanReload() const;

	/** =================================================== 获取数据( GETTER ) ============================================== */

	/** get current weapon state */
	EWeaponState GetCurrentState() const;

	/** get current ammo amount (total) */
	int32 GetCurrentAmmo() const;

	/** get current ammo amount (clip) */
	int32 GetCurrentAmmoInClip() const;

	/** get clip size */
	int32 GetAmmoPerClip() const;

	/** get max ammo amount */
	int32 GetMaxAmmo() const;

	/** 获取武器Mesh */
	USkeletalMeshComponent* GetWeaponMesh() const;

	/** 获取角色Pawn的拥有者 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	class AAnCharacter* GetPawnOwner() const;

	/** icon displayed on the HUD when weapon is equipped as primary */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	FCanvasIcon PrimaryIcon;

	/** icon displayed on the HUD when weapon is secondary */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	FCanvasIcon SecondaryIcon;

	/** bullet icon used to draw current clip (left side) */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	FCanvasIcon PrimaryClipIcon;

	/** bullet icon used to draw secondary clip (left side) */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	FCanvasIcon SecondaryClipIcon;

	/** how many icons to draw per clip */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	float AmmoIconsCount;

	/** defines spacing between primary ammo icons (left side) */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	int32 PrimaryClipIconOffset;

	/** defines spacing between secondary ammo icons (left side) */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	int32 SecondaryClipIconOffset;

	/** crosshair parts icons (left, top, right, bottom and center) */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	FCanvasIcon Crosshair[5];

	/** crosshair parts icons when targeting (left, top, right, bottom and center) */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	FCanvasIcon AimingCrosshair[5];

	/** only use red colored center part of aiming crosshair */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	bool UseLaserDot;

	/** false = default crosshair */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	bool UseCustomCrosshair;

	/** false = use custom one if set, otherwise default crosshair */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	bool UseCustomAimingCrosshair;

	/** true - crosshair will not be shown unless aiming with the weapon */
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	bool bHideCrosshairWhileNotAiming;

	/** check if weapon has infinite ammo (include owner's cheats) */
	bool HasInfiniteAmmo() const;

	/** check if weapon has infinite clip (include owner's cheats) */
	bool HasInfiniteClip() const;

	/** set the weapon's owning pawn */
	void SetOwningPawn(AAnCharacter* AAnCharacter);

	/** gets last time when this weapon was switched to */
	float GetEquipStartedTime() const;

	/** gets the duration of equipping weapon*/
	float GetEquipDuration() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** 角色 */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_MyPawn)
	class AAnCharacter* MyPawn;

	/** 武器数据 */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponData WeaponConfig;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/** firing audio (bLoopedFireSound set) */
	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	/** name of bone/socket for muzzle in weapon mesh */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	FName MuzzleAttachPoint;

	/** FX for muzzle flash */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* MuzzleFX;

	/** spawned component for muzzle FX */
	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	/** spawned component for second muzzle FX (Needed for split screen) */
	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSCSecondary;

	/** camera shake on firing */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	TSubclassOf<UCameraShake> FireCameraShake;

	/** force feedback effect to play when the weapon is fired */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UForceFeedbackEffect *FireForceFeedback;

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireSound;

	/** looped fire sound (bLoopedFireSound set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireLoopSound;

	/** finished burst sound (bLoopedFireSound set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireFinishSound;

	/** out of ammo sound */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* OutOfAmmoSound;

	/** reload sound */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* ReloadSound;

	/** reload animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	FWeaponAnim ReloadAnim;

	/** equip sound */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* EquipSound;

	/** equip animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	FWeaponAnim EquipAnim;

	/** fire animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	FWeaponAnim FireAnim;

	/** is muzzle FX looped? */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	uint32 bLoopedMuzzleFX : 1;

	/** is fire sound looped? */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	uint32 bLoopedFireSound : 1;

	/** is fire animation looped? */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	uint32 bLoopedFireAnim : 1;

	/** is fire animation playing? */
	uint32 bPlayingFireAnim : 1;

	/** is weapon currently equipped? */
	uint32 bIsEquipped : 1;

	/** is weapon fire active? */
	uint32 bWantsToFire : 1;

	/** is reload animation playing? */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Reload)
	uint32 bPendingReload : 1;

	/** is equip animation playing? */
	uint32 bPendingEquip : 1;

	/** weapon is refiring */
	uint32 bRefiring;

	/** 当前的武器状态 */
	EWeaponState CurrentState;

	/** 武器最后成功射击的时间 */
	float LastFireTime;

	/** 当这个武器被切换的时间 */
	float EquipStartedTime;

	/** 装备这个武器需要多少时间？ */
	UPROPERTY(EditDefaultsOnly, Category = Equip)
	float EquipDuration;

	/** 当前子弹数 */
	UPROPERTY(Transient, Replicated)
	int32 CurrentAmmo;

	/** current ammo - inside clip */
	UPROPERTY(Transient, Replicated)
	int32 CurrentAmmoInClip;

	/** burst counter, used for replicating fire events to remote clients */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_BurstCounter)
	int32 BurstCounter;

	/** Handle for efficient management of OnEquipFinished timer */
	FTimerHandle TimerHandle_OnEquipFinished;

	/** Handle for efficient management of StopReload timer */
	FTimerHandle TimerHandle_StopReload;

	/** Handle for efficient management of ReloadWeapon timer */
	FTimerHandle TimerHandle_ReloadWeapon;

	/** Handle for efficient management of HandleFiring timer */
	FTimerHandle TimerHandle_HandleFiring;


	//////////////////////////////////////////////////////////////////////////
	// Replication & effects

	UFUNCTION()
	void OnRep_MyPawn();

	UFUNCTION()
	void OnRep_BurstCounter();

	UFUNCTION()
	void OnRep_Reload();


	//////////////////////////////////////////////////////////////////////////
	// Weapon usage

	///** [local] weapon specific fire implementation */
	//virtual void FireWeapon() PURE_VIRTUAL(AShooterWeapon::FireWeapon, );

	///** [server] fire & update ammo */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerHandleFiring();

	///** [local + server] handle weapon fire */
	//void HandleFiring();

	/** [local + server] firing started */
	virtual void OnBurstStarted();

	/** [local + server] firing finished */
	virtual void OnBurstFinished();

	/** 跟新武器当前状态 */
	void SetWeaponState(EWeaponState NewState);

	/** 决定当前武器的状态 */
	void DetermineWeaponState();


	//////////////////////////////////////////////////////////////////////////
	// Weapon usage helpers - 使用武器的帮手

	/** 播放武器音效 */
	UAudioComponent* PlayWeaponSound(USoundCue* Sound);

	/** 播放武器动画 */
	float PlayWeaponAnimation(const FWeaponAnim& Animation);

	/** stop playing weapon animations */
	void StopWeaponAnimation(const FWeaponAnim& Animation);

	/** Get the aim of the weapon, allowing for adjustments to be made by the weapon */
	//virtual FVector GetAdjustedAim() const;

	/** Get the aim of the camera */
	FVector GetCameraAim() const;

	/** get the originating location for camera damage */
	FVector GetCameraDamageStartLocation(const FVector& AimDir) const;

	/** get the muzzle location of the weapon */
	FVector GetMuzzleLocation() const;

	/** get direction of weapon's muzzle */
	FVector GetMuzzleDirection() const;

	/** find hit */
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const;

private:
	/** weapon mesh: 1st person view */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* WeaponMesh1P;

	/** weapon mesh: 3rd person view */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* WeaponMesh3P;
	
};
