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
	///** =================================================== 重写 ============================================== */
	///** 开始销毁 */
	//virtual void BeginDestroy() override;

	///** 生成时的组件初始化 */
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

	///** =================================================== 公共方法 ============================================== */
	//
	///**
	//*	添加第一人称的摄像机俯仰值
	//*
	//*	@param	CameraLocation	摄像机位置.
	//*	@param	CameraRotation	摄像机旋转.
	//*/
	//void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	///** 获取瞄准的偏移旋转值 */
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//FRotator GetAimOffsets() const;

	///**
	//* 检查指定控制器下的角色是否是敌人
	//*
	//* @param	TempController	需要检查的控制器
	//*/
	//bool IsEnemyFor(AController* TempController) const;

	///** =================================================== 库存系统 ============================================== */

	///** [服务器] 添加武器到库存 */
	//void AddWeapon(class AShooterWeapon* Weapon);

	///** [服务器] 移除库存中指定的武器 */
	//void RemoveWeapon(class AShooterWeapon* Weapon);

	///** 在库存中找到指定的武器 */
	//class AShooterWeapon* FindWeapon(TSubclassOf<class AShooterWeapon> WeaponClass);

	///** [服务器 + 本地] 从库存中选择武器装备 */
	//void EquipWeapon(class AShooterWeapon* Weapon);

	///** =================================================== 武器系统 ============================================== */

	///** [本地] 武器开始开火*/
	//void StartWeaponFire();

	///** [本地] 武器停止开火 */
	//void StopWeaponFire();

	///** 检查玩家是否可以开火 */
	//bool CanFire() const;

	///** 检查玩家是否可以跟换弹夹 */
	//bool CanReload() const;

	///** [服务器 + 本地] 目标状态的改变 */
	//void SetTargeting(bool bNewTargeting);

};
