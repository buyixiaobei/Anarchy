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
	// �������������Ե�Ĭ��ֵ��
	AAnCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	///** ��ʼ���� */
	//virtual void BeginDestroy() override;

	///** ���������ʱ�������ʼ�� */
	//virtual void PostInitializeComponents() override;

	///** ���µ�һ�˳Ƶ�Mesh */
	//virtual void PawnClientRestart() override;

	///** [������] ִ��PlayerState������ */
	//virtual void PossessedBy(class AController* C) override;

	///** [�ͻ���] ִ��PlayerState������ */
	//virtual void OnRep_PlayerState() override;

	///** [������] ͨ�����������ȷ���Ƿ���ͣ�������ActorΪ�ض������ */
	//virtual bool IsReplicationPausedForConnection(const FNetViewer& ConnectionOwnerNetViewer) override;

	///** [�ͻ���] ���������Actor��ͣʱ���� */
	//virtual void OnReplicationPausedChanged(bool bIsReplicationPaused) override;

	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//// ��������İ󶨹���
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** =================================================== ��������(Common) ============================================== */
	
	/**
	*	��ӵ�һ�˳Ƶ����������ֵ
	*
	*	@param	CameraLocation	�����λ��.
	*	@param	CameraRotation	�������ת.
	*/
	void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	/** ��ȡ��׼��ƫ����תֵ */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FRotator GetAimOffsets() const;

	/**
	* ���ָ���������µĽ�ɫ�Ƿ��ǵ���
	*
	* @param	TempController	��Ҫ���Ŀ�����
	*/
	bool IsEnemyFor(AController* TempController) const;

	/** =================================================== ���ϵͳ(Inventory) ============================================== */

	///** [������] ������������ */
	//void AddWeapon(class AnWeapon* Weapon);

	///** [������] �Ƴ������ָ�������� */
	//void RemoveWeapon(class AnWeapon* Weapon);

	///** �ڿ�����ҵ�ָ�������� */
	//class AnWeapon* FindWeapon(TSubclassOf<class AnWeapon> WeaponClass);

	///** [������ + ����] �ӿ����ѡ������װ�� */
	//void EquipWeapon(class AnWeapon* Weapon);

	///** ���õ�ǰ������ */
	//void SetCurrentWeapon(class AnWeapon* NewWeapon, class AnWeapon* LastWeapon = NULL);

	///** ��ǰ�����ĸ��ƴ��� */
	//UFUNCTION()
	//void OnRep_CurrentWeapon(class AnWeapon* LastWeapon);

	/** [������] ����Ĭ�ϵĿ�� */
	void SpawnDefaultInventory();

	/** [������] �ӿ����ȡ�������������������ǡ� */
	void DestroyInventory();

	/** [������] װ������ */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerEquipWeapon(class AShooterWeapon* NewWeapon);

	///** [������] ����Ŀ��״̬ */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerSetTargeting(bool bNewTargeting);

	///** [������] ����״̬ */
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerSetRunning(bool bNewRunning, bool bToggle);

	/** �������������ͣ���Ƶĵ���б�*/
	void BuildPauseReplicationCheckPoints(TArray<FVector>& RelevancyCheckPoints);

	/** =================================================== ����ϵͳ(Weapon) ============================================== */

	///** [����] ������ʼ����*/
	void StartWeaponFire();

	///** [����] ����ֹͣ���� */
	void StopWeaponFire();

	///** �������Ƿ���Կ��� */
	bool CanFire() const;

	///** �������Ƿ���Ը������� */
	bool CanReload() const;

	///** [������ + ����] Ŀ��״̬�ĸı� */
	void SetTargeting(bool bNewTargeting);

	/** =================================================== �ƶ�(Movement) ============================================== */
	/** [������ + ����] �ı��ɫ�˶���״̬ */
	void SetRunning(bool bNewRunning, bool bToggle);


	/** =================================================== ����(Animations) ============================================== */
	/** ������̫�涯�� */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/** ֹͣ������̫�涯�� */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/** ֹͣ�������е���̫�� */
	void StopAllAnimMontages();


	/** =================================================== ����(Input Handle) ============================================== */

	/** �����ض���Pawn�����봦�� */
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	/** =================================================== ��ȡ����(Data) ============================================== */

	/** ��ȡPawnMesh��� */
	USkeletalMeshComponent* GetPawnMesh() const;

	/** ��ȡ��ǰװ�������� */
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//class AShooterWeapon* GetWeapon() const;

	/** ��ȡ�����󶨲������ */
	FName GetWeaponAttachName() const;

	/** ��ȡ������� */
	int32 GetInventoryCount() const;

	/**
	* �������л�ȡ������������Ч��δ��顣
	*
	* @param Index ������
	*/
	//class AShooterWeapon* GetInventoryWeapon(int32 index) const;

	/** ��ȡ����Ŀ�������ٶ�	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float GetTargetingSpeedModifier() const;

	/** ��ȡĿ��״̬ */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsTargeting() const;

	/** ��ȡ����״̬ */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool IsFiring() const;

	/** ��ȡ�����ٶȵ�����ֵ */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	float GetRunningSpeedModifier() const;

	/** ��ȡ��ɫ��ǰ�˶�״̬ */
	UFUNCTION(BlueprintCallable, Category = Pawn)
	bool IsRunning() const;

	/** ��ȡ��ǰ����������ͣ�1P / 3P�� */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

	/** ��ȡ�������ֵ */
	int32 GetMaxHealth() const;

	/** ����ɫ�Ƿ񻹴��~ */
	bool IsAlive() const;

	/** ���ص�����ֵʱ�İٷֱ� */
	float GetLowHealthPercentage() const;

	/*
	* Get either first or third person mesh.
	*
	* @param	WantFirstPerson		If true returns the first peron mesh, else returns the third
	*/
	//USkeletalMeshComponent* GetSpecifcPawnMesh(bool WantFirstPerson) const;

	/** ����������ҽ�ɫ���Ŷ���ɫ�� */
	void UpdateTeamColorsAllMIDs();

protected:

	/** ��������۵����� */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachName;

	/** Ĭ�ϵĿ�� */
	//UPROPERTY(EditDefaultsOnly, Category = Inventory)
	//TArray<TSubclassOf<class AShooterWeapon> > DefaultInventoryClasses;

	/** ����е����� */
	//UPROPERTY(Transient, Replicated)
	//TArray<class AShooterWeapon*> Inventory;

	/** ��ǰװ�������� */
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_CurrentWeapon)
	//class AShooterWeapon* CurrentWeapon;

	/** �������һ�α����к��˺�����Ϣ */
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_LastTakeHitInfo)
	//struct FTakeHitInfo LastTakeHitInfo;

	/** ���һ��Ϊ��һ�ȡ��Ϣ��ʱ�䳬ʱ�����ᱻ���ƣ�����ֹͣ��Ļ�ϵĽ���Ӱ�졣 */
	float LastTakeHitTimeTimeout;

	/** �޸�Ŀ������ٶ� */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	float TargetingSpeedModifier;

	/** ��ǰĿ��״̬ */
	UPROPERTY(Transient, Replicated)
	uint8 bIsTargeting : 1;

	/** �޸�����ƶ��ٶ� */
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	float RunningSpeedModifier;

	/** ��ǰ�˶���״̬ */
	UPROPERTY(Transient, Replicated)
	uint8 bWantsToRun : 1;

	/** �������л��ֱ� */
	uint8 bWantsToRunToggled : 1;

	/** ��ǰ����״̬ */
	uint8 bWantsToFire : 1;

	/** ������ֵ�İٷֱ�ֵ */
	float LowHealthPercentage;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate.����ת�����ʣ������϶�/�롣�������ſ��ܻ�Ӱ������ת�����ʡ� */
	float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate.���������ʣ������϶�/�롣�������ſ��ܻ�Ӱ�����ղ����ʡ� */
	float BaseLookUpRate;

	/** ��Mesh�������Ŷ���ɫ�Ĳ���ʵ���������˳���ͼ�� */
	UPROPERTY(Transient)
	TArray<UMaterialInstanceDynamic*> MeshMIDs;

	/** ��ɫ����ʱ����̫�涯�� */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DeathAnim;

	/** ���������Ч�������ڱ������ */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* DeathSound;

	/** �������������Ч */
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UParticleSystem* RespawnFX;

	/** ���������Ч */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RespawnSound;

	/** ��ҵ�����ֵʱ����Ч */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* LowHealthSound;

	/** ��ҳ������ܵ���Ч */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RunLoopSound;

	/** ���ֹͣ���ܵ���Ч */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RunStopSound;

	/** ���״̬�仯ʱ����Ч */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* TargetingSound;

	///** used to manipulate with run loop sound */
	//UPROPERTY()
	//UAudioComponent* RunLoopAC;

	///** hook to looped low health sound used to stop/adjust volume */
	//UPROPERTY()
	//UAudioComponent* LowHealthWarningPlayer;

	/** �����˶��е���Ч */
	void UpdateRunSounds();

	/** ����Mesh�ɼ��Ժ͸��� */
	void UpdatePawnMeshes();

	/** ��ָ������ʵ���ϴ���Mesh��ɫ�� */
	void UpdateTeamColors(UMaterialInstanceDynamic* UseMID);

	/** ��������ͻ��˵�ʬ�塣 */
	virtual void TornOff();

private:

	/** ��ɫ�Ƿ��ƶ��������˶����룩 */
	bool IsMoving();


	///** =================================================== �˺� & ���� (Damage & Die) ============================================== */

	/** �Ƿ��ڴ���״̬�� */
	uint32 bIsDying : 1;

	/** �Ƿ�����Ѫ״̬�� */
	uint32 bIsBleeding : 1;

	/** �Ƿ�������״̬�� */
	uint32 bIsWounded : 1;

public:

	/** ��ǰ�������ֵ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
	float Health;

	// ���������ֵ�������������£��ƶ��ٶ� & �Ӿ� & ����ȫ���½�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float WoundedThreshold;

	// �����Ѫ��ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float BleedThreshold;

	// ����ܵ��˺�����Ѫ��ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float DamageBleedThreshold;

	// ����ֱ����ȫɱ����ҵ��˺���ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float KilDamageThreshold;

	// �����������µ�����ֵ��ʧ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float WoundedHealthLossRate;

	// �����Ѫ����µ�����ֵ��ʧ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float BleedingHealthLossRate;

	// ���������ָ�����ֵ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "BandagedHealthRate(Sec)", Category = Health)
	float BandagedHealthRate;

	// ��������˵�������£���������Ҫ������ֵ��ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "WoundedToReviveHealthThreshold" , Category = Health)
	float ToReviveHealthThreshold;

	/** ��д�����˺�ֵ */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	/** Pawn��ɱ */
	virtual void Suicide();

	/** ���Pawn��˭ɱ�� */
	virtual void KilledBy(class APawn* EventInstigator);

	/** �����ǰ״̬Ϊ����״̬���򷵻�Ture */
	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const;

	/**
	* ɱ����� ���� ������ / ӵ��Ȩ�� ��OP
	* @param KillingDamage - ��ɱ�˺���
	* @param DamageEvent - ����һ�����˺��¼�
	* @param Killer - ɱ�֣�Ҳ��ʱ˭ɱ�������Pawn
	* @param DamageCauser - ֱ������˺��Ķ��󣨼���ը���ڵ�������������ȣ�
	* @returns ��������������򷵻�Ture
	*/
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	/** ����Ҷ�ʧ������ʱ���� */
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	/** Called on the actor right before replication occurs �ڸ��Ʒ���֮ǰ���ö���Ϊ��ȷ�� */
	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;

protected:

	/** ���������ʱ֪ͨ������ & �ͻ��� */
	virtual void OnDeath(float KillingDamage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser);

	/** ������ײʱ������ײ��Ч */
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	/** �л���������״̬ */
	void SetRagdollPhysics();

	/** sets up the replication for taking a hit - �������ڲ���ĸ��� */
	void ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser, bool bKilled);

	/** �ڿͻ����ϲ���Hit��Ч ���� ���� */
	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	/** Returns Mesh1P subobject **/
	//FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
};
