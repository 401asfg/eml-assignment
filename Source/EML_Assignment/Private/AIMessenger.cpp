// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMessenger.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UAIMessenger::SendMessageToAI(FString modelUrl, FString message, UTextBlock *textBlock)
{
	// TODO: check if message is empty or white space

	FHttpModule &httpModule = FHttpModule::Get();
	FHttpRequestRef request = httpModule.CreateRequest();

	TSharedRef<FJsonObject> json = MakeShared<FJsonObject>();
	json->SetStringField("model", "llama3.2");
	json->SetStringField("prompt", message);

	FString body;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&body);
	FJsonSerializer::Serialize(json, writer);

	request->SetContentAsString(body);
	request->SetURL(modelUrl);
	request->SetVerb("POST");
	request->SetHeader("Content-Type", "application/json");

	request->OnProcessRequestComplete().BindLambda(
		[&](FHttpRequestPtr request,
			FHttpResponsePtr response,
			bool connected) mutable
		{
			if (!connected) {
				// TODO: handle errors
				return;
			}

			UAIMessenger::ReceiveMessageFromAI(response->GetContentAsString(), textBlock);
		}
	);

	request->ProcessRequest();
}

void UAIMessenger::ReceiveMessageFromAI(FString message, UTextBlock *textBlock)
{
	textBlock->SetText(FText::FromString(message));
}
