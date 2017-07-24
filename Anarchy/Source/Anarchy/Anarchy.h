// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"


DECLARE_LOG_CATEGORY_EXTERN(LogAnarchyGame, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogAnWeapon, Log, All);

#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PICKUP		ECC_GameTraceChannel3

// 玩家名称最大长度
#define MAX_PLAYER_NAME_LENGTH 16