# SoulslikeGame

## 목차
+ ### [1.개요](#1-개요)
+ ### [2.개발 툴 및 언어](#3-개발-툴-및-언어)
+ ### [3.기능 구현 영상](3-기능-구현-영상)
+ ### [4.핵심 개발 기술](4-핵심-개발-기술)
+ ### [5.후기](5-후기)

## 1 개요
+ ### 장르: 액션RPG, 소울라이크
+ ### 컨셉1. 높은 난이도의 보스와의 전투를 통한 성취감을 느끼는 게임
+ ### 컨셉2. 보스의 패턴에 맞춰서 대응하는 공략하는 게임
+ ### 컨셉3. 여러 타입의 플레이어 캐릭터를 만들어 다 회차를 진행 
+ ### 플랫폼: PC
  
## 2. 개발 툴 및 언어
+ ### 개발 툴: 언리얼엔진5.4
+ ### 언어: C++ 및 블루프린트
+ ### 플러그인: GameplayAbilitySystem

## 3. 기능 구현 영상
+ #### 07-30 ~ 08-30 : 블루프린트로 기본적인 전투시스템(공격, 튕겨내기(가드 패링), 패링(카운터 패링), 처형)을 제작.
+ #### 09-09 ~ 09-23 : 플레이어 스탯 정의 및 UI 구현, 스탯 변경 기능 구현 및 UI 구현(https://youtu.be/nppocoVVKQE)
+ #### 09-24 ~ 10-03 : 플레이어 캐릭터의 이동및 점프, 락온 구현(https://youtu.be/kOW1TFtqouY)
+ #### 10-04 ~ 10-09 : 무기 장착 구현(https://youtu.be/FwmNvM79Gxw)
+ #### 10-10 ~ 10-11 : 무기 장착 오류 해결 및 방패 사용 구현(https://youtu.be/VpMdJ85KKTg)
+ #### 10-14 ~ 10-16 : 검 및 도끼 공격 및 점프 공격 구현(https://youtu.be/CLQeAyv8LkI)
+ #### 10-17 ~ 11-04 : 공격 및 피격 판정 구현 & UI 연동(https://youtu.be/Ykx8qRxx2Oo)
  + ##### 특이사항: 10/21 ~ 10/26 까지 넥토리얼 인턴쉽 코테를 위한 준비로 인해 일정 밀림
  
--------------------------------------------------------------------------------------------------------------------

## 4. 핵심 개발 기술
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
