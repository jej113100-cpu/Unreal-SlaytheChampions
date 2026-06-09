#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "CardVFXDataAsset.generated.h"

/**
 * UCardVFXDataAsset
 *
 * 카드 사용 시 재생할 나이아가라 VFX 를 태그 기반으로 매핑하는 DataAsset.
 * 에디터에서 DA_CardVFX 로 생성하고 CombatManager 에 할당한다.
 *
 * [사용법]
 * 1. DT_Cards 의 EffectTag 컬럼에 태그 입력 (예: "Attack_Slash")
 * 2. DA_CardVFX 의 EffectMap 에 동일한 태그 → 나이아가라 에셋 매핑
 * 3. CombatManager 디테일 패널에서 DA_CardVFX 할당
 *
 * [장점]
 * - DT_Cards 에 나이아가라 에셋 직접 참조 없음 → DataTable 가볍게 유지
 * - 새 이펙트 추가 시 DA_CardVFX 만 수정 (코드 변경 불필요)
 * - 여러 카드가 같은 태그 공유 가능 (예: 모든 공격 카드 → "Attack_Slash")
 */
UCLASS(BlueprintType)
class SLAYTHECHAMPIONS_API UCardVFXDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    /**
     * EffectTag → NiagaraSystem 매핑 테이블.
     * 키  : FCardDataRow::EffectTag 값 (예: "Attack_Slash", "Magic_Fire")
     * 값  : 재생할 나이아가라 시스템 (소프트 레퍼런스 - 사용 시점에만 로드)
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TMap<FName, TSoftObjectPtr<UNiagaraSystem>> EffectMap;

    /**
     * EffectTag 로 나이아가라 시스템을 반환한다.
     * 태그가 없거나 매핑이 없으면 nullptr 반환.
     *
     * @param EffectTag  FCardDataRow::EffectTag 값
     * @return 매핑된 UNiagaraSystem (없으면 nullptr)
     */
    UFUNCTION(BlueprintPure, Category = "VFX")
    UNiagaraSystem* GetEffect(FName EffectTag) const;
};
