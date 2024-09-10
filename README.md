# SoulslikeGame

Developed with Unreal Engine 5

### 07-30 ~ 08-30까지 블루프린트를 이용하여 알파버전 게임 제작

### 09-09 BaseCharacter 작성
+ #### 게임에서 사용할 AttributeSet 및 AbilitySystemComponent를 작성
+ #### BaseCharacter::BeginPlay()에서 AbilitySystemComponent가 유효하면 초기AttributeDataTable을 적용 하도록 구현함.
+ #### AttributeMetaData형식의 DataTable을 작성하여, 기본적인 스탯(체력, 의지, 근력, 재능, 집중)을 적용 함.
+ #### 후에 GameplayEffect를 통해 해당 스탯을 이용하여, HP, SP Mana를 초기화 하고, HP, SP는 Calculationsd을 작성하여 스탯에 따라 변동 하도록 구현 예정
