// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMessenger.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

constexpr auto MODEL_URL = "http://localhost:11434/api/generate";

void UAIMessenger::SendMessageToAI(FString message)
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
	request->SetURL(MODEL_URL);
	request->SetVerb("POST");
	request->SetHeader("Content-Type", "application/json");
	request->OnProcessRequestComplete().BindUObject(this, &UAIMessenger::ReceiveMessageFromAI);
	request->ProcessRequest();
}

void UAIMessenger::ReceiveMessageFromAI(FHttpRequestPtr request, FHttpResponsePtr response, bool connected)
{
	if (!connected) {
		// TODO: handle errors
	}

	// TODO: implement
}
