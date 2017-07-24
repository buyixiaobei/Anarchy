// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnCharacter.generated.h"

UCLASS()
class ANARCHY_API AAnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 设置这个类的属性的默认值。
	AAnCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	///** 开始销毁 */
	//virtual void BeginDestroy() override;

	///** 这个类生成时的组件初始化 */
	//virtual void PostInitializeComponents() override;

	///** 跟新第一人称的Mesh */
	//virtual void PawnClientRestart() override;

	///** [服务器] 执行PlayerState的设置 */
	//virtual void PossessedBy(class AController* C) override;

	///** [客户端] 执行PlayerState的设置 */
	//virtual void OnRep_PlayerState() override;

	///** [服务器] 通过调用这个来确定是否暂停复制这个Actor为特定的玩家 */
	//virtual bool IsReplicationPausedForConnection(const FNetViewer& ConnectionOwnerNetViewer) override;

	///** [客户端] 当复制这个Actor暂停时调用 */
	//virtual void OnReplicationPausedChanged(bool bIsReplicationPaused) override;

	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//// 调用输入的绑定功能
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** =================================================== 公共方法(Common) ============================================== */
	
	/**
	*	添加第一人称的摄像机俯仰值
	*
	*	@param	CameraLocation	摄像机位置.
	*	@param	CameraRotation	摄像机旋转.
	*/
	void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	/** 获取瞄准的偏移旋转值 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FRotator GetAimOffsets() const;

	/**
	* 检查指定控制器下的角色是否是敌人
	*
	* @param	TempController	需要检查的控制器
	*/
	bool IsEnemyFor(AController* TempController) const;

	/** =================================================== 库存系统(Inventory) ============================================== */

	///** [服务器] 添加武器到库存 */
	//void AddWeapon(class AnWeapon* Weapon);

	///** [服务器] 移除库存中指定的武器 */
	//void RemoveWeapon(class AnWeapon* Weapon);

	///** 在库存中找到指定的武器 */
	//class AnWeapon* FindWeapon(TSubclassOf<class AnWeapon> WeaponClass);

	///** [服务器 + 本地] 从库存中选择武器装备 */
	//void EquipWeapon(class AnWeapon* Weapon);

	///** 设置当前的武器 */
	//void SetCurrentWeapon(class AnWeapon* NewWeapon, class AnWeapon* LastWeapon = NULL);

	///** 当前武器的复制处理 */
	//UFUNCTION()
	//void OnRep_CurrentWeapon(class AnWeapon* LastWeapon);

	/** [服务器] 生成默认的库存 */
	void SpawnDefaultInventory();

	/** [服务器] 从库存中取出所有武器并销毁它们。 */
	void DestroyInventory();

	/** [服务器] 装备武器 */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerEquipWeapon(class AShooterWeapon* NewWeapon);

	///** [服务器] 跟新目标状态 */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerSetTargeting(bool bNewTargeting);

	///** [服务器] 跟新状态 */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerSetRunning(bool bNewRunning, bool bToggle);

	/** 构建检查连接暂停复制的点的列表。*/
	void BuildPauseReplicationCheckPoints(TArray<FVector>& RelevancyCheckPoints);

	/** =================================================== 武器系统(Weapon) ============================================== */

	///** [本地] 武器开始开火*/
	void StartWeaponFire();

	///** [本地] 武器停止开火 */
	void StopWeaponFire();

	///** 检查玩家是否可以开火 */
	bool CanFire() const;

	///** 检查玩家是否可以跟换弹夹 */
	bool CanReload() const;

	///** [服务器 + 本地] 目标状态的改变 */
	void SetTargeting(bool bNewTargeting);

	/** =================================================== 移动(Movement) ============================================== */
	/** [服务器 + 本地] 改变角色运动的状态 */
	void SetRunning(bool bNewRunning, bool bToggle);


	/** =================================================== 动画(Animations) ============================================== */
	/** 播放蒙太奇动画 */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/** 停止播放蒙太奇动画 */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/** 停止播放所有的蒙太奇 */
	void StopAllAnimMontages();


	/** =================================================== 输入(Input Handle) ============================================== */

	/** 设置特定的Pawn的输入处理 */
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	/** =================================================== 获取数据(Data) ============================================== */

	/** 获取PawnMesh组件 */
	USkeletalMeshComponent* GetPawnMesh() const;

	/** 获取当前装备的武器 */
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//class AShooterWeapon* GetWeapon() const;

	/** 获取武器绑定插槽名称 */
	FName GetWeaponAttachName() const;

	/** 获取库存总数 */
	int32 GetInventoryCount() const;

	/**
	* 从索引中获取武器。索引有效性未检查。
	*
	* @param Index 库存序号
	*/
	//class AShooterWeapon* GetInventoryWeapon(int32 index) const;

	/** 获取武器目标修正速度	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float GetTargetingSpeedModifier() const;

	/** 获取目标状态 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsTargeting() const;

	/** 获取开火状态 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsFiring() const;

	/** 获取运行速度的修正值 */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	float GetRunningSpeedModifier() const;

	/** 获取角色当前运动状态 */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsRunning() const;

	/** 获取当前摄像机的类型（1P / 3P） */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

	/** 获取最大生命值 */
	int32 GetMaxHealth() const;

	/** 检查角色是否还存活~ */
	bool IsAlive() const;

	/** 返回低生命值时的百分比 */
	float GetLowHealthPercentage() const;

	/*
	* Get either first or third person mesh.
	*
	* @param	WantFirstPerson		If true returns the first peron mesh, else returns the third
	*/
	//USkeletalMeshComponent* GetSpecifcPawnMesh(bool WantFirstPerson) const;

	/** 更新所有玩家角色的团队颜色。 */
	void UpdateTeamColorsAllMIDs();

protected:

	/** 绑定武器插槽的名称 */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachName;

	/** 默认的库存 */
	//UPROPERTY(EditDefaultsOnly, Category = Inventory)
	//TArray<TSubclassOf<class AShooterWeapon> > DefaultInventoryClasses;

	/** 库存中的武器 */
	//UPROPERTY(Transient, Replicated)
	//TArray<class AShooterWeapon*> Inventory;

	/** 当前装备的武器 */
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_CurrentWeapon)
	//class AShooterWeapon* CurrentWeapon;

	/** 复制最后一次被击中和伤害的信息 */
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_LastTakeHitInfo)
	//struct FTakeHitInfo LastTakeHitInfo;

	/** 最后一次为玩家获取信息的时间超时，不会被复制；用于停止屏幕上的进度影响。 */
	float LastTakeHitTimeTimeout;

	/** 修改目标最大速度 */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	float TargetingSpeedModifier;

	/** 当前目标状态 */
	UPROPERTY(Transient, Replicated)
	uint8 bIsTargeting : 1;

	/** 修改最大移动速度 */
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	float RunningSpeedModifier;

	/** 当前运动的状态 */
	UPROPERTY(Transient, Replicated)
	uint8 bWantsToRun : 1;

	/** 从运行切换手柄 */
	uint8 bWantsToRunToggled : 1;

	/** 当前开火状态 */
	uint8 bWantsToFire : 1;

	/** 第生命值的百分比值 */
	float LowHealthPercentage;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate.基本转弯速率，在摄氏度/秒。其他缩放可能会影响最终转弯速率。 */
	float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate.基本查找率，在摄氏度/秒。其他缩放可能会影响最终查找率。 */
	float BaseLookUpRate;

	/** 在Mesh中设置团队颜色的材质实例（第三人称视图） */
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> MeshMIDs;

	/** 角色死亡时的蒙太奇动画 */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DeathAnim;

	/** 玩家死亡音效，仅用于本地玩家 */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* DeathSound;

	/** 玩家重生粒子特效 */
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UParticleSystem* RespawnFX;

	/** 玩家重生音效 */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RespawnSound;

	/** 玩家第生命值时的音效 */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* LowHealthSound;

	/** 玩家持续奔跑的音效 */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RunLoopSound;

	/** 玩家停止奔跑的音效 */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RunStopSound;

	/** 针对状态变化时的音效 */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* TargetingSound;

	///** used to manipulate with run loop sound */
	//UPROPERTY()
	//UAudioComponent* RunLoopAC;

	///** hook to looped low health sound used to stop/adjust volume */
	//UPROPERTY()
	//UAudioComponent* LowHealthWarningPlayer;

	/** 处理运动中的音效 */
	void UpdateRunSounds();

	/** 处理Mesh可见性和更新 */
	void UpdatePawnMeshes();

	/** 在指定材质实例上处理Mesh颜色。 */
	void UpdateTeamColors(UMaterialInstanceDynamic* UseMID);

	/** 负责清理客户端的尸体。 */
	virtual void TornOff();

private:

	/** 角色是否移动（基于运动输入） */
	bool IsMoving();


	///** =================================================== 伤害 & 死亡 (Damage & Die) ============================================== */

	/** 是否处于垂死状态。 */
	uint32 bIsDying : 1;

	/** 是否处于流血状态。 */
	uint32 bIsBleeding : 1;

	/** 是否处于受伤状态。 */
	uint32 bIsWounded : 1;

public:

	/** 当前玩家生命值 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
	float Health;

	// 玩家受伤阈值，玩家受伤情况下，移动速度 & 视觉 & 听觉全都下降
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float WoundedThreshold;

	// 玩家流血阈值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float BleedThreshold;

	// 玩家受到伤害的流血阈值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float DamageBleedThreshold;

	// 可以直接完全杀死玩家的伤害阈值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float KilDamageThreshold;

	// 玩家受伤情况下的生命值丢失速率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float WoundedHealthLossRate;

	// 玩家流血情况下的生命值丢失速率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float BleedingHealthLossRate;

	// 绷带包扎恢复生命值速率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "BandagedHealthRate(Sec)", Category = Health)
	float BandagedHealthRate;

	// 玩家在受伤倒地情况下，苏醒所需要的生命值阈值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "WoundedToReviveHealthThreshold" , Category = Health)
	float ToReviveHealthThreshold;

	/** 重写处理伤害值 */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	/** Pawn自杀 */
	virtual void Suicide();

	/** 这个Pawn被谁杀死 */
	virtual void KilledBy(class APawn* EventInstigator);

	/** 如果当前状态为死亡状态，则返回Ture */
	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const;

	/**
	* 杀死玩家 ，仅 服务器 / 拥有权限 的OP
	* @param KillingDamage - 击杀伤害量
	* @param DamageEvent - 致命一击的伤害事件
	* @param Killer - 杀手，也就时谁杀死了这个Pawn
	* @param DamageCauser - 直接造成伤害的对象（即爆炸的炮弹、发射的武器等）
	* @returns 如果允许死亡，则返回Ture
	*/
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	/** 当玩家丢失于世界时死亡 */
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	/** Called on the actor right before replication occurs 在复制发生之前调用对象为正确。 */
	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;

protected:

	/** 当玩家死亡时通知服务器 & 客户端 */
	virtual void OnDeath(float KillingDamage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser);

	/** 发生碰撞时生成碰撞特效 */
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	/** 切换到布娃娃状态 */
	void SetRagdollPhysics();

	/** sets up the replication for taking a hit - 设置用于捕获的复制 */
	void ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser, bool bKilled);

	/** 在客户端上播放Hit特效 或者 死亡 */
	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	/** Returns Mesh1P subobject **/
	//FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
};
