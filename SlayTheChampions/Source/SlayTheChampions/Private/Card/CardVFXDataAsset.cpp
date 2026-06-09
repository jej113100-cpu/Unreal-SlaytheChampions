#include "Card/CardVFXDataAsset.h"

UNiagaraSystem* UCardVFXDataAsset::GetEffect(FName EffectTag) const
{
    if (EffectTag.IsNone()) return nullptr;

    const TSoftObjectPtr<UNiagaraSystem>* Found = EffectMap.Find(EffectTag);
    if (!Found || Found->IsNull()) return nullptr;

    // 사용 시점에 동기 로드 (소프트 레퍼런스)
    return Found->LoadSynchronous();
}
