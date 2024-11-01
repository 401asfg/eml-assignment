// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMessenger.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UAIMessenger::SendMessageToAI(FString modelUrl, FString message, UTextBlock *textBlock)
{
	if (message.IsEmpty()) {
		UAIMessenger::ReceiveMessageFromAI(FString("Error: Message was empty."), textBlock);
		return;
	}

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
			FString content;

			if (connected) content = response->GetContentAsString();
			else switch (request->GetStatus()) {
			case EHttpRequestStatus::Failed_ConnectionError:
				content = FString("Error: Connection failed.");
				break;
			default:
				content = FString("Error: Request failed.");
			}

			UAIMessenger::ReceiveMessageFromAI(content, textBlock);
		}
	);

	request->ProcessRequest();
}

void UAIMessenger::ReceiveMessageFromAI(FString message, UTextBlock *textBlock)
{
	if (textBlock) {
		textBlock->SetText(FText::FromString(message));
	}
}
