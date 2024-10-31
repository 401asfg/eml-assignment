// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIMessenger.generated.h"

/**
 * 
 */
UCLASS()
class EML_ASSIGNMENT_API UAIMessenger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AI Messenger")
	void SendMessageToAI(FString message);

	UFUNCTION(BlueprintCallable, Category = "AI Messenger")
	void ReceiveMessageFromAI(FHttpRequestPtr request, FHttpResponsePtr response, bool connected);
};
