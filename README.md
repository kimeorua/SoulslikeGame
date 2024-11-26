# SoulslikeGame

## 목차
+ ### [1.개요](#1-개요)
+ ### [2.개발 툴 및 언어](#2-개발-툴-및-언어)
+ ### [3.기능 구현 영상](#3-기능-구현-영상)
+ ### [4.핵심 개발 기술](#4-핵심-개발-기술)
+ ### [5.후기](5-후기)

## 1 개요
+ ### 장르: 액션RPG, 소울라이크
+ ### 컨셉1. 높은 난이도의 보스와의 전투를 통한 성취감을 느끼는 게임
+ ### 컨셉2. 보스의 패턴에 맞춰서 대응하는 공략하는 게임
+ ### 컨셉3. 여러 타입의 플레이어 캐릭터를 만들어 다 회차를 진행 
+ ### 플랫폼: PC
  
## 2 개발 툴 및 언어
+ ### 개발 툴: 언리얼엔진5.4
+ ### 언어: C++ 및 블루프린트
+ ### 플러그인: GameplayAbilitySystem

## 3 기능 구현 영상
+ #### 07-30 ~ 08-30 : 블루프린트로 기본적인 전투시스템(공격, 튕겨내기(가드 패링), 패링(카운터 패링), 처형)을 제작.
+ #### 09-09 ~ 09-23 : 플레이어 스탯 정의 및 UI 구현, 스탯 변경 기능 구현 및 UI 구현(https://youtu.be/nppocoVVKQE)
+ #### 09-24 ~ 10-03 : 플레이어 캐릭터의 이동및 점프, 락온 구현(https://youtu.be/kOW1TFtqouY)
+ #### 10-04 ~ 10-09 : 무기 장착 구현(https://youtu.be/FwmNvM79Gxw)
+ #### 10-10 ~ 10-11 : 무기 장착 오류 해결 및 방패 사용 구현(https://youtu.be/VpMdJ85KKTg)
+ #### 10-14 ~ 10-16 : 검 및 도끼 공격 및 점프 공격 구현(https://youtu.be/CLQeAyv8LkI)
+ #### 10-17 ~ 11-04 : 공격 및 피격 판정 구현 & UI 연동(https://youtu.be/Ykx8qRxx2Oo)
  + ##### 특이사항: 10/21 ~ 10/26 까지 넥토리얼 인턴쉽 코테를 위한 준비로 인해 일정 밀림
+ #### 11-04 ~ 11-8 : 가드 및 가드 패링 구현(https://youtu.be/7dTXDuX5-h8?si=WTamFMH-SpJXsUpW)
+ #### 11-11 ~ 11-18 : 카운터 패링 및 처형 공격 구현(https://youtu.be/oacIC3TUKlg)
+ #### 11-19 ~ 11-21 : 회피 판정 및 스태미나 감소 구현(https://youtu.be/5YQTNSGQ0lY)
--------------------------------------------------------------------------------------------------------------------

## 4 핵심 개발 기술
### MagnitudeCalculation을 통해 Health, Will스탯에 따라 HP, 및 SP 계산 Class 작성

```cpp

#include "InitHPMagnitudeCalculation.h"
#include "SoulslikeAttributeSetBase.h"

UInitHPMagnitudeCalculation::UInitHPMagnitudeCalculation()
{
	HealthDef.AttributeToCapture = USoulslikeAttributeSetBase::GetHealthAttribute();
	HealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HealthDef.bSnapshot = false;

	MaxStatDef.AttributeToCapture = USoulslikeAttributeSetBase::GetMaxStatAttribute();
	MaxStatDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MaxStatDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(MaxStatDef);
}

float UInitHPMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* Source = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* Target = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Source;
	EvaluateParameters.TargetTags = Target;

	float Health = 0.0f;
	GetCapturedAttributeMagnitude(HealthDef, Spec, EvaluateParameters, Health);

	float MaxStat = 0.0f;
	GetCapturedAttributeMagnitude(MaxStatDef, Spec, EvaluateParameters, MaxStat);

	Health = FMath::Clamp(Health, 0.0f, MaxStat);

	return Base + (Health * Rate);
}

```

### 코드 설명
+ #### HP가 Health스탯의 여향을 받도록 AttributeSet에서 Health 스탯과, 최대 스탯인 MaxStat을 받아와서 각각 HealthDef, MaxStatDef에 저장함.
+ #### CalculateBaseMagnitude_Implementation() 함수에서 계산에서 사용할 Health 와 MaxStat을 초기화 하고, 각각 GetCapturedAttributeMagnitude를 통해 현재 Attribute의 값을 가져와 저장 해 줌
+ #### 계산된 Health가 최소0, 최대MaxStat을 가지도록 FMath::Clamp()를 통해 범위를 지정 함.
+ #### 이후 블루프린트에서 지정한 Base 값과, Rate 값을 통해 계산하여 반환 함.
+ #### SP계산식도 위와 동일하게 작동 하도록 추가 구현 함.

### GameplayEffectExecutionCalculation을 활용하여 스탯에 따른 데미지 계산식 구현

```cpp

// 캡처할 정보를 구조체로 선언함.

struct DamageCature
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(HP);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SP);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Concentration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxStat);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Mana);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxMana);

	DamageCature()
	{
		// 공격을 받은 캐릭터의 스탯 정보
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, HP, Target, false); 
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, SP, Target, false);

		공격을 한 캐릭터의 스탯 정보
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Strength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Concentration, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, MaxStat, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, Mana, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USoulslikeAttributeSetBase, MaxMana, Source, false);
	}
};

static DamageCature& GetDamageCature()
{
	static DamageCature DamageCature;
	return DamageCature;
}

```

```cpp

UExec_Cal_ApplyDamamge::UExec_Cal_ApplyDamamge()
{
	RelevantAttributesToCapture.Add(GetDamageCature().HPDef);
	RelevantAttributesToCapture.Add(GetDamageCature().SPDef);

	RelevantAttributesToCapture.Add(GetDamageCature().StrengthDef);
	RelevantAttributesToCapture.Add(GetDamageCature().ConcentrationDef);
	RelevantAttributesToCapture.Add(GetDamageCature().MaxStatDef);

	RelevantAttributesToCapture.Add(GetDamageCature().ManaDef);
	RelevantAttributesToCapture.Add(GetDamageCature().MaxManaDef);
}

void UExec_Cal_ApplyDamamge::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParms, FGameplayEffectCustomExecutionOutput& OutExecutionOutPut) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParms.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParms.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParms.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// 공격 받은 캐릭터의 HP
	float HP = 0.0f; 
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().HPDef, EvaluateParameters, HP);

	// 공격 받은 캐릭터 SP
	float SP = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().SPDef, EvaluateParameters, SP);

	// 공격한 객체의 Strength 스탯
	float Strength = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().StrengthDef, EvaluateParameters, Strength);

	// 공격한 객체의 Concentration 스탯
	float Concentration = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().ConcentrationDef, EvaluateParameters, Concentration);

	// 공격한 객체의 MaxStat 수치
	float MaxStat = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().MaxStatDef, EvaluateParameters, MaxStat);

	// 공격한 객체의 Mana 스탯
	float Mana = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().ManaDef, EvaluateParameters, Mana);

	// 공격한 객체의 MaxMana 스탯
	float MaxMana = 0.0f;
	ExecutionParms.AttemptCalculateCapturedAttributeMagnitude(GetDamageCature().MaxManaDef, EvaluateParameters, MaxMana);

	// 치명타 확률 = 기본 치명타 확률 + Concentration(집중)
	float CriticalPersent = BaseCriticalChance + FMath::Clamp(Concentration, 0.0f, MaxStat);

	// 치명타 피해 배율 = 기본 치명타 피해 배률 + (Concentration(집중) * 0.02f)
	float CriticalRate = BaseCriticalRate + FMath::Clamp(Concentration, 0.0f, MaxStat) * 0.02f;

	// 무기의 기본 데미지 가져 오기
	float WeaponBaseDamage = Cast<ABaseCharacter>(SourceActor)->GetWeaponBaseDamage();

	// 계산된 총 데미지 정의
	float Damage = 0.0f;

	// Strength(힘)의 스탯에 따른 배율 조정
	// Strength(힘) 스탯이 StrengthCap을 넘어가면 효율이 감소함.
	// 데미지 = 무기 기본 데미지 + (Strength(힘) * 데미지 배율)
	if (Strength >= StrengthCap)
	{
		// Strength(힘) 이 StrengthCap 이상이면 배율이 감소함. 
		Damage = WeaponBaseDamage + (((StrengthCap - 1) * DamageRateMax) + (FMath::Clamp(Strength, 0.0f, MaxStat) - (StrengthCap - 1)) * DamageRateMin);
	}
	else
	{
		Damage = WeaponBaseDamage + FMath::Clamp(Strength, 0.0f, MaxStat) * DamageRateMax;
	}

	// 치명타 계산용 랜덤
	float Random = FMath::RandRange(0, 100);

	// 감소될 HP
	float TargetHPDawn;

	// 마나 획득 -> 플레이어 전용임으로 BP에서 플레이어 전용과 보스 전용으로 나눠 적용 시킬 것.
	float SourceManaUp = ManaGain;

	// 치명타가 발생 하면 데미지 *= 치명타 피해 배율
	if (Random <= CriticalPersent)
	{
		TargetHPDawn = FMath::CeilToInt(Damage * CriticalRate);
	}
	else
	{
		TargetHPDawn = FMath::CeilToInt(Damage);
	}


	//각 스탯 적용
	if (Mana + SourceManaUp >= MaxMana)
	{
		SourceAbilitySystemComponent->ApplyModToAttribute(USoulslikeAttributeSetBase::GetManaAttribute(), EGameplayModOp::Override, MaxMana);
	}
	else
	{
		SourceAbilitySystemComponent->ApplyModToAttribute(USoulslikeAttributeSetBase::GetManaAttribute(), EGameplayModOp::Additive, SourceManaUp);
	}

	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCature().HPProperty, EGameplayModOp::Additive, -TargetHPDawn));
	OutExecutionOutPut.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCature().SPProperty, EGameplayModOp::Additive, -TargetHPDawn * SPDawnRate));
}

```

### 코드 설명
+ #### 데미지 GameplayEffect가 작동되면, 해당 수식을 통해 계산 함
+ #### 공격 한 객체의 각 스탯을 가져와 치명타 여부와, 총 데미지를 계산함.
+ #### 공격 받은 객체의 HP를 감소 시키고 보스 캐릭터는 추가로 SP를 받은 데미지에 비례하여 감소 시킴.
