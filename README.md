# SoulslikeGame

Developed with Unreal Engine 5

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
