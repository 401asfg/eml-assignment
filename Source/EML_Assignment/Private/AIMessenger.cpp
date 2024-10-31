// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMessenger.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#define MODEL_URL "http://localhost:11434/api/generate"

void UAIMessenger::SendMessageToAI(FString message)
{
	FHttpModule &httpModule = FHttpModule::Get();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> request = httpModule.CreateRequest();
	request->SetVerb(TEXT("POST"));
	request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	FString json = TEXT("{ \"model\": \"llama3.2\", \"prompt\": \"") + message + TEXT("\" }");
	request->SetContentAsString(json);
	request->SetURL(TEXT(MODEL_URL));

	// TODO: write callback for handling HTTP response

	request->ProcessRequest();
}

FString UAIMessenger::ReceiveMessageFromAI()
{
	// TODO: implement
	return FString();
}
