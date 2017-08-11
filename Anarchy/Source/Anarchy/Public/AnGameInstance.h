// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anarchy.h"
#include "Engine/GameInstance.h"
#include "AnGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANARCHY_API UAnGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	//virtual void Init() override;
	//virtual void Shutdown() override;
	//virtual void StartGameInstance() override;

	//// 主机游戏
	//bool HostGame(ULocalPlayer* LocalPlayer, const FString& GameType, const FString& InTravelURL);

	//// 加入会话
	//bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults);

	//// 加入会话
	//bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult);
	
	
	
};
