# SoulslikeGame

### 개발 요약
+ #### 07-30 ~ 08-30 : 블루프린트로 기본적인 전투시스템(공격, 튕겨내기(가드 패링), 패링(카운터 패링), 처형)을 제작.
+ #### 09-09 ~ 09-23 : 플레이어 스탯 정의 및 UI 구현, 스탯 변경 기능 구현 및 UI 구현(https://youtu.be/nppocoVVKQE)
+ #### 09-24 ~ 10-03 : 플레이어 캐릭터의 이동및 점프, 락온 구현(https://youtu.be/kOW1TFtqouY)
+ #### 10-04 ~ 10-09 : 무기 장착 구현(https://youtu.be/FwmNvM79Gxw)
+ #### 10-10 ~ 10-11 : 무기 장착 오류 해결 및 방패 사용 구현(https://youtu.be/VpMdJ85KKTg)
--------------------------------------------------------------------------------------------------------------------


### 07-30 ~ 08-30까지 블루프린트를 이용하여 알파버전 게임 제작

### 09-09 BaseCharacter 작성
+ #### 게임에서 사용할 SoulslikeAttributeSetBase 및 SoulslikeAbilitySystemComponent를 작성
+ #### BaseCharacter::BeginPlay()에서 AbilitySystemComponent가 유효하면 초기AttributeDataTable을 적용 하도록 구현함.
+ #### AttributeMetaData형식의 DataTable을 작성하여, 기본적인 스탯(체력, 의지, 근력, 재능, 집중)을 적용 함.
+ #### 후에 GameplayEffect를 통해 해당 스탯을 이용하여, HP, SP Mana를 초기화 하고, HP, SP는 Calculationsd을 작성하여 스탯에 따라 변동 하도록 구현 예정

### 09-10 Modifier Magnitude Calculation을 활용하여, Health 및 Will수치에 따라 HP 및 SP 계산 및 적용
+ #### Modifier Magnitude Calculation을 구현하여 GameplayEffect에서 커스텀 계산식을 적용 시킴
+ #### DataTalbe에서 적용된 스탯을 기준으로 HP, SP를 적용함.
+ #### Mana는 스탯에 관련 없이 100으로 고정 되도록 함.
+ #### 작성한 SoulslikeAttributeSetBase에서 PostGameplayEffectExecute 함수에서 변동된 스탯을 Clamp하여 최대값을 넘지 못하도록 추가 구현 함.

### 09-11 스탯 증가 기초 로직 구현
+ #### 스탯 증가용 GameplayEffect을 제작하고 SetByCaller를 통해 수정할 스탯의 증가량을 설정 할수 있도록 구현함.
+ #### BaseCharacter에 StatChangeEffects변수를 추가하여, TMap<FGameplayTag, TSubClassOf<UGameplayEffect>>형식으로 저장함.
+ #### 임시로 키보드L키를 누르면 StatChangeEffects에서 랜덤으로 Key값을 고르고, 해당 키값을 가진 Effect를 Tag와 함께 지정하여, GameplayEffect를 작동 시킴

### 09-12 HP, SP, Mana UI구현 및 연동
+ #### PlayerHUD를 구현하여, BaseCharater의 Attribute값을 가져와서 연동 시킴
+ #### UBlueprintAsyncActionBase을 상속받아 Listen for Attribute Change를 통해, PlayerHUD에서 Attribute의 값이 변경될때마다 HUD를 갱신 함.

### 09-16 StatUI구현
+ #### 플레이어의 현재 스탯 및 스탯을 변경 할 수 있는 UI창을 구현함.
+ #### 키보드 I키를 눌러 UI창을 팝업 시키거나 종료 시킬수 있도록 구현함.
+ #### 추가로 입력을 제한 하기 위해, GameplayTag를 부착하여 제어함. 

### 09-17 StatUI Player와 연동
+ #### UI창이 열릴 때 플레이어 캐릭터를 받아와서 플레이어의 Stat을 표시 하도록 구현함.

### 09-23 UI에서 버튼을 이용하여 스탯 투자 및 적용 구현
+ #### 플레이어 캐릭터의 스탯을 받아온 후 구조체(F_UI_Stat)에 저장함.
+ #### 저장 할 때 OriginStat 과 NewStat에 같은 값을 우선 저장함.
+ #### 증가 버튼을 클릭 시 남아있는 투자 가능한 Point를 확인후, 최대 스탯값을 넘지 않았으면 NewStat값에 + 1 감소시에는 -1을 함.
+ #### 스탯을 투자 한 후 Apply버튼을 클릭하면 NewStat - Origin을 하예 해당 값을 받아 GameplayEffect를 작동 시킴.
+ #### 추가로 스탯 투자 후 플레이어의 HP, SP, Mana를 초기화 시켜, 가득 채우도록 구현 함.
+ #### 필요없어진 StatChangeEffects변수를제거함.
  
### 09-24 Player Character Class 작성
+ #### BaseCharacter를 상속 받아 Player Character를 작성함.
+ #### Player Character에 입력을 통해 이동 및 점프, 마우스 카메라 회전을 구현 함.
+ #### 사용할 캐릭터 메쉬 에셋 탐색 및 임포트

### 09-25 사용할 애니메이션 리타겟팅 및 GAS Component 반환 함수 구현
+ #### 사용할 애니메이션 에셋을 탐색후, 사용할 캐릭터에 맞게 리타겟팅 함.
+ #### GAS Component를 반환하는 함수를 작성 함.

### 09-26 애님인스턴스 작성
+ #### 공통적으로 사용할 SoulslikeAnimInstance class를 작성함.
+ #### 기본적으로 속도(Speed) 방향(Direction) 가속 여부(IsAccelerating)과, Character, 및 GASComponent와 MovementComponent를 변수로 가짐.
+ #### 속도를 계산하여, 속도에따라 걷기/달리기 애니메이션이 출력되도록 구현 함.

### 09-27 GitHub 연동 해제 및 
+ #### Git LFS 용량 부족으로 Git Hub 연동을 해제함.
+ #### 후에 SVN이나 다른 방식으로 버전컨트롤 진행 예정
+ #### c++ 코드는 Source 폴더에 남겨 두기로 함.
+ #### 점프 애니메이션 출력 구현
+ #### 스패이스바를 누르고 있으면 점프가, 빠르게 눌럿다가 떼면 회피가 작동 되도록 구현 함.

### 09-30 회피 구현
+ #### 현재 락온 여부에 따라 1방향 회피, 8방향 회피를 하도록 구현함.
+ #### 회피 애니메이션은 RootMotion을 끄고, Root강제 잠금을 활성화 하여, 제자리에서 구르도록 함.
+ #### 구르는 애니메이션이 나오는 동안 Apply Root Motion Constant Force() 함수를 통하여, 일정 거리만큼 이동 하도록 구현 함.
+ #### 회피 애니메이션은 데이터 에셋을 생성하여, 해당 데이터 에셋에 배열로 추가하여 관리함.

### 10-01 점프 딜레이 및 회피 개선, UI버그 수정, LockOnComponent 작성

+ #### 점프 착지 이후 바로 점프가 할수 없도록 JumpLock == true 일때만 점프를 할수 있도록 구현하고, Timer를 이용하여, JumpLock변수를 변경하여 딜레이를 구현 함.
 ```cpp
    void APlayerCharacter::JumpLockReSet()
    {
	FTimerHandle JumpTimerHandle;
	GetWorldTimerManager().SetTimer(JumpTimerHandle, FTimerDelegate::CreateLambda([this]() {JumpLock = false; }), JumpDelay, false);
    }
```
+ #### Player Character로 Default Pawn Class를 변경후, UI가 제대로 작동하지 않는 것을 확인, 디버깅 결과, 플레이어 캐릭터를 받아오는 Player 변수가 BP_Test_BaeCharater(Test용 캐릭터)로 되어있는것을 확인, 해당 변수형을 BaeCharater(c++ 클래스)로 변경 함.
+ #### LockOnComponent를 작성하여, C++로 SphereTraceMultiForObjects()를 작성하고, LockOn에 활용할 새로운 오브젝트 채널을 추가함, BaeCharater Class에는 CapsuleCollision을 추가함.
+ #### Trac결과 해당 콜리전이 충돌되는 것을 확인 함.

### 10-02 락온 구현
+ #### SphereTraceByObjrect에서 충돌된 객체를 저장하여, 카메라의 회전값을 조정하여, 락온을 구현함.
+ #### 타이머와 RInterTo를 활용하여 자연스러운 카메라 무브를 구현함.

### 10-03 락온 시 애니메이션 변경
+ #### 플레이어의 락온 여부에따라 GameplayTag를 부착하여, 애님인스턴스에서 IsLockOn을 통해 블랜드 스페이스를 변경함.
+ #### 락온 사용 중일 경우 전방을 바라보면 이동하는 애니메이션이, 락온 중이 아니면 진행방향에따라 회전하는 애니메이션이 나오도록 구현 함.

### 10-04 무기 제어용 컴포넌트 및 무기 작성
+ #### 무기의 정보를 담을 DataAsset과, 무기 Class를 작성함
+ #### 무기 Class는 기본적인 장비를 담당하는 Prop Class를 상속받아서 Weapon Class를 작성함, Prop에서 기본적인 장착, 해제 등을 구현할 예정
+ #### 무기류를 전반적으로 제어할 WeaponComponent를 작성하고, TMap을 활용하여 EeaponType과, DataAsset을 묶어서 관리함.
+ #### WeaponComponent에서 테스트용으로 Sword객체를 스폰 시키는 것을 구현 함.

### 10-05 무기 및 방패에 메쉬 적용 및 장착 구현
+ #### 무기 및 방패에 각각 스켈레탈 메쉬와 스태틱 메쉬를 적용함.
+ #### 게임 시작 시, 무기들과 방패를 스폰 하고, DataAsset에 지정된 소켓에 부착되도록 구현 함.

### 10-07 무기 장착 및 중단 로직 구현
+ #### 무기를 장착 할 시 CurrentWeapon과 CurrentWeaponDataAsset을 설정하는 함수를 WeaponComponnet에 작성함.
+ #### 플레이어 캐릭터는 입력을 받을경우, 해당 입력에 맞는 WeaponType을 매개변수로 전달하여, 제어함.
+ #### 이때 현재 장착한 무기가 없으면 바로 적용 되지만, 이미 장착한 무기가 있으면, 해당무기를 OldWeapon DataAsset을 OldWeaponDataAsset에 저장함.
+ #### OldWeapon 및 DataAsset은 무기 변경 중 중단 되었을 경우(피격 받음, 회피 함)이전 상태로 Current Weapon과 DataAsset을 변경 해줌.
+ #### WeaponDataAsset Class에 무기의 장착 및 장착 해제 AnimMontage를 가지는 구조체를 변수로 추가하고, 각 DatAsset에서 Montage를 생성및 적용 함.
+ #### 후에 무기가 실제로 장착되도록 부착 및 탈착을 구현 예정

### 10-08 무기 장착 및 장착 해제 애니메이션 추가
+ #### 무기가 장착 및 장착해제되는 애님 몽타주를 재생시키는 Ability를 작성함
+ #### 해당 Ability에서 PlayMontageAndWait을 통해 중단시 원래 무기로 CurrentDataAsset및 CurrentWeapon을 복구하는 기능을 부여함.
+ #### 후에 애님 몽타주에 Notify를실행하여 알맞는 위치에 부착하는 기능을 추가 예정

### 10-09 애님 몽타주에서 적절한 타이밍에 무기 부착 구현 & 무기에 따라 걷기 / 달리기 애니메이션 변경
+ #### 애님몽타주에서 Nofity를 통해 무기를 실제로 부착하는 기능을 구현 함.
+ #### WeaponType을 AnimIntance에서 변수로 저장하여, 현재 무기 타입에따라 다른 애니메이션이 나오도록구현 함.

### 10-10 무기 장착 오류 해결
+ #### 무기 장착과, 해제가 몽타주와 일치하지 않는 버그를 발견함.
+ #### WeaponComponent Class 의 WeaponSelect함수를 수정하여, 변경할 무기의 BP와 DataAsset을 RequestWeapon 변수에 저장함.
+ #### 무기가 실제로 장착이되는 EqiopWeapon함수를 통해, 장착 여부와 현재 무기가 있는지 등 여러 상황을 고려하여, 적절하게 부착 되도록 구현 함.

```cpp
void UWeaponComponent::WeaponSelect(EWeaponType Type)
{
	if (IsValid(Weapons.FindRef(Type)))
	{
		if (CurrentWeapon.Weapon == nullptr || CurrentWeapon.DataAsset == nullptr)
		{
			RequestWeapon.DataAsset = WeaponDatas.FindRef(Type); //현재 장착중인 무기가 없으면 바로 적용
			RequestWeapon.Weapon = Weapons.FindRef(Type);
		}
		else
		{
			if (CurrentWeapon.DataAsset->GetWeaponType() == Type)
			{
				RequestWeapon.DataAsset = nullptr; //이미 장착된 무기가 있고, 요청된 무기의 Type 동일 -> 같은버튼은 한번더 누름 -> 무기 장착 해제
				RequestWeapon.Weapon = nullptr;
			}
			else
			{
				OldWeapon.DataAsset = CurrentWeapon.DataAsset; // 좀더 자연스럽게 변경하기 위해 이전 무기 저장
				OldWeapon.Weapon = CurrentWeapon.Weapon;

				RequestWeapon.DataAsset = WeaponDatas.FindRef(Type); // 이미 장착된 무기가 있고 Type이 다름 -> 다른 무기로 교체
				RequestWeapon.Weapon = Weapons.FindRef(Type);
			}
		}
	}
}

void UWeaponComponent::EquipWeapon(bool IsEquip)
{
	if (IsEquip)
	{
		if (CurrentWeapon.DataAsset == nullptr && CurrentWeapon.Weapon == nullptr)
		{
			CurrentWeapon.DataAsset = RequestWeapon.DataAsset; // 현재무기에 요청 무기 저장
			CurrentWeapon.Weapon = RequestWeapon.Weapon;

			CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetEquipSokcet()); // 해당 위치에 부착
		}
		else
		{
			CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetUnequipSokcet()); //이미 장착된 무기를 부착 해제

			CurrentWeapon.DataAsset = RequestWeapon.DataAsset; // 현재무기에 요청 무기 저장
			CurrentWeapon.Weapon = RequestWeapon.Weapon;

			CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetEquipSokcet()); //무기 부착
		}
	}
	else
	{
		CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetUnequipSokcet()); // 무기 장착 해제
		CurrentWeapon.DataAsset = RequestWeapon.DataAsset; //현재무기에 요청 무기 저장
		CurrentWeapon.Weapon = RequestWeapon.Weapon;
	}
}
```

### 10-10 무기 장착 오류 해결, 방패 작동 구현
+ #### 다른 무기를 장착 할 시 무기 해제가 무기 장착 애니메이션 시작과 동시에 작동 되도록 WeaponComponent Class에 UnequipWeapon 함수를 작성함.
 
```cpp

void UWeaponComponent::UnequipWeapon()
{
	if (CurrentWeapon.DataAsset != nullptr && CurrentWeapon.Weapon != nullptr)
	{
		CurrentWeapon.Weapon->Attach(CurrentWeapon.DataAsset->GetUnequipSokcet());

		CurrentWeapon.Weapon = nullptr;
		CurrentWeapon.DataAsset = nullptr;
	}
}

```

+ #### 방패를 들어올리는 GA_Shield 어빌리티를 작성하고 플레이어 캐릭터가 마우스 우클릭을 누르면 작동 하도록 구현 함
+ #### 추가로 방패를 들어 올릴때 방패가 펴지는 효과를 주기위해 방패 Mesh의 Sclae크기를 변경하여 구현 함

```cpp

void AShield::ShieldSizeChange(bool isActivate)
{
	if (isActivate)
	{
		Mesh->SetWorldScale3D(ActivateSize);
	}
	else
	{
		Mesh->SetWorldScale3D(DeactivateSize);
	}
}

```
