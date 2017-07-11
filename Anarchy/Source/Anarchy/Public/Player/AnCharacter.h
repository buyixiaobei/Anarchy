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
	// Sets default values for this character's properties
	AAnCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	///** =================================================== ��д ============================================== */
	///** ��ʼ���� */
	//virtual void BeginDestroy() override;

	///** ����ʱ�������ʼ�� */
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

	///** =================================================== �������� ============================================== */
	//
	///**
	//*	��ӵ�һ�˳Ƶ����������ֵ
	//*
	//*	@param	CameraLocation	�����λ��.
	//*	@param	CameraRotation	�������ת.
	//*/
	//void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	///** ��ȡ��׼��ƫ����תֵ */
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//FRotator GetAimOffsets() const;

	///**
	//* ���ָ���������µĽ�ɫ�Ƿ��ǵ���
	//*
	//* @param	TempController	��Ҫ���Ŀ�����
	//*/
	//bool IsEnemyFor(AController* TempController) const;

	///** =================================================== ���ϵͳ ============================================== */

	///** [������] ������������ */
	//void AddWeapon(class AShooterWeapon* Weapon);

	///** [������] �Ƴ������ָ�������� */
	//void RemoveWeapon(class AShooterWeapon* Weapon);

	///** �ڿ�����ҵ�ָ�������� */
	//class AShooterWeapon* FindWeapon(TSubclassOf<class AShooterWeapon> WeaponClass);

	///** [������ + ����] �ӿ����ѡ������װ�� */
	//void EquipWeapon(class AShooterWeapon* Weapon);

	///** =================================================== ����ϵͳ ============================================== */

	///** [����] ������ʼ����*/
	//void StartWeaponFire();

	///** [����] ����ֹͣ���� */
	//void StopWeaponFire();

	///** �������Ƿ���Կ��� */
	//bool CanFire() const;

	///** �������Ƿ���Ը������� */
	//bool CanReload() const;

	///** [������ + ����] Ŀ��״̬�ĸı� */
	//void SetTargeting(bool bNewTargeting);

};
