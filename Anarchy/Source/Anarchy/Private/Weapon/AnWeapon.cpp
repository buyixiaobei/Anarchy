// Fill out your copyright notice in the Description page of Project Settings.

#include "AnWeapon.h"
#include "Anarchy.h"
#include "Particles/ParticleSystemComponent.h"



// ����Ĭ�ϵ�ֵ
AAnWeapon::AAnWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
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

void AAnWeapon::OnEquip(const AAnWeapon* LastWeapon)
{

}

void AAnWeapon::OnEquipFinished()
{

}

void AAnWeapon::OnUnEquip()
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
	
}

