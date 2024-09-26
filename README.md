# SoulslikeGame

### 개발 요약
+ #### 07-30 ~ 08-30 : 블루프린트로 기본적인 전투시스템(공격, 튕겨내기(가드 패링), 패링(카운터 패링), 처형)을 제작.
+ #### 09-09 ~ 09-23 : 플레이어 스탯 정의 및 UI 구현, 스탯 변경 기능 구현 및 UI 구현(https://youtu.be/nppocoVVKQE)

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
