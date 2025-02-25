// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerBase.h"
#include "Delegates/Delegate.h"
#include <Enum/StateEnum.h>
#include "PlayerCharcter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UPaperFlipbook;
class USoundBase;
struct FInputActionValue;
class UMaterialInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

/**
 * 
 */
UCLASS()
class PROJECT2D_API APlayerCharcter : public APlayerBase
{
	GENERATED_BODY()
	
public:
	APlayerCharcter();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	//����
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Jump();
	void Climb(const FInputActionValue& Value);
	void Attack();

	bool IsAttack = false;
	float Timer = 0.f;

	//�ƶ�
	void ChangeMovement();
	
	//�߽���
	void CheckBoundary();

	//����ö�ٱ�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyEnum)
	StateEnum NowEnum;

	//�Ƿ�����
	bool CanClimb;
	bool IsClimbing;
	FVector ClimbPosition;
	bool IsSet = false;
	bool CanStop = false;
	bool IsUp = false;

	// ��������
	void StartClimbing();
	void StopClimbing();
	void ChangeCollisionBlock();
	void ChangeCollisionIgnore();

	//Ħ��ϵ��
	float FlyingFrictionCoefficient;

	//������
	void BeAttacked(float Damge,FVector EnemyForwardVector);
	void SetHitedVelocity(FVector EnemyForwardVector);

	//��˸
	void Hit_Blink();

	//����
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	// Ѫ���ı��ί��
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;
	

protected:
	void AddForceWhenFlying(float DeltaTime);
private:
	//���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;

	//����
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMapping;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> ClimbAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	//����
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> RunFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> IdleFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> JumpFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> ClimbFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> ClimbIdleFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> AttackFilpBook;
	UPROPERTY(EditDefaultsOnly, Category = Animate)
	TObjectPtr<UPaperFlipbook> DeathFilpBook;

	//��Ƶ
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	TObjectPtr<USoundBase> JumpSound;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	TObjectPtr<USoundBase> HitSound;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	TObjectPtr<USoundBase> BeHitedSound;

	//�߽�
	float LeftBoundary = -620.f;
	float RightBoundary = -1100.f;

	//�˺�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damge, meta = (AllowPrivateAccess = "true"))
	float AttackDamge;
	bool CanBeHit = true;

	//�޵�ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damge, meta = (AllowPrivateAccess = "true"))
	float GodTime;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	//��˸����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Material, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> StartMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Material, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> ShineMaterial;

	// ��ʱ�����
	FTimerHandle TimerHandleOfHit;
	void TimerCallbackOfHit();
	FTimerHandle TimerHandleOfShine;
	void TimerCallbackOfShine();
	FTimerHandle TimerHandleOfDeath;
	void TimerCallbackeOfDeath();
	void RemoveTimer();


	//״̬
	bool IsShine = false;
	bool IsDeath = false;
};
