// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "AIMessenger.generated.h"

/**
 * 
 */
UCLASS()
class EML_ASSIGNMENT_API UAIMessenger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString prevMessage;

	UFUNCTION(BlueprintCallable, Category = "AI Messenger")
	static void SendMessageToAI(FString modelUrl, FString message, UTextBlock *textBlock);

	UFUNCTION(BlueprintCallable, Category = "AI Messenger")
	static void ReceiveMessageFromAI(FString message, UTextBlock *textBlock);
};
