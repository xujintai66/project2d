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

	//输入
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Jump();
	void Climb(const FInputActionValue& Value);
	void Attack();

	bool IsAttack = false;
	float Timer = 0.f;

	//移动
	void ChangeMovement();
	
	//边界检查
	void CheckBoundary();

	//创建枚举变量声明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyEnum)
	StateEnum NowEnum;

	//是否攀爬
	bool CanClimb;
	bool IsClimbing;
	FVector ClimbPosition;
	bool IsSet = false;
	bool CanStop = false;
	bool IsUp = false;

	// 攀爬函数
	void StartClimbing();
	void StopClimbing();
	void ChangeCollisionBlock();
	void ChangeCollisionIgnore();

	//摩擦系数
	float FlyingFrictionCoefficient;

	//被攻击
	void BeAttacked(float Damge,FVector EnemyForwardVector);
	void SetHitedVelocity(FVector EnemyForwardVector);

	//闪烁
	void Hit_Blink();

	//生命
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	// 血量改变的委托
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;
	

protected:
	void AddForceWhenFlying(float DeltaTime);
private:
	//组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;

	//输入
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

	//动画
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

	//音频
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	TObjectPtr<USoundBase> JumpSound;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	TObjectPtr<USoundBase> HitSound;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
	TObjectPtr<USoundBase> BeHitedSound;

	//边界
	float LeftBoundary = -620.f;
	float RightBoundary = -1100.f;

	//伤害
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damge, meta = (AllowPrivateAccess = "true"))
	float AttackDamge;
	bool CanBeHit = true;

	//无敌时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damge, meta = (AllowPrivateAccess = "true"))
	float GodTime;

	//生命
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	//闪烁材质
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Material, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> StartMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Material, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> ShineMaterial;

	// 定时器句柄
	FTimerHandle TimerHandleOfHit;
	void TimerCallbackOfHit();
	FTimerHandle TimerHandleOfShine;
	void TimerCallbackOfShine();
	FTimerHandle TimerHandleOfDeath;
	void TimerCallbackeOfDeath();
	void RemoveTimer();


	//状态
	bool IsShine = false;
	bool IsDeath = false;
};
