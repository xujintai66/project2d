// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyBase.generated.h"

class UPaperFlipbook;
class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class PROJECT2D_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void ChangeFilpBook();

	//������
	TObjectPtr<UCapsuleComponent> EnemyCapsule;

	//overlap�¼�
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual float DamgePass();

	//����������
	void BeAttacked(float Damge);
	bool IsHit = false;
	bool IsDeath = false;

	
protected:
	//�˺�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damge, meta = (AllowPrivateAccess = "true"))
	float AttackDamge;
private:
	//����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	//����
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> RunFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> IdleFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> HitedFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> DeathFilpBook;

	float Timer = 0;
	bool IsSet = false;

	// ��ʱ�����
	FTimerHandle TimerHandle;
	// ��ʱ���ص�����
	void TimerCallback();

	

};
