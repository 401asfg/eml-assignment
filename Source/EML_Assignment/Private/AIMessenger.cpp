// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMessenger.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#define MODEL_URL "http://localhost:11434/api/generate"

void UAIMessenger::SendMessageToAI(FString message)
{
	FHttpModule &httpModule = FHttpModule::Get();
	FHttpRequestRef request = httpModule.CreateRequest();

	request->SetVerb("POST");
	request->SetHeader("Content-Type", "application/json");

	TSharedRef<FJsonObject> json = MakeShared<FJsonObject>();
	json->SetStringField("model", "llama3.2");
	json->SetStringField("prompt", message);

	FString body;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&body);
	FJsonSerializer::Serialize(json, writer);

	request->SetContentAsString(body);
	request->SetURL(MODEL_URL);

	// TODO: write callback for handling HTTP response

	request->ProcessRequest();
}

FString UAIMessenger::ReceiveMessageFromAI()
{
	// TODO: implement
	return FString();
}
