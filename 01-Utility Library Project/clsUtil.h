#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include "clsDate.h"

class clsUtil
{
enum enCharacterTypes { SmallLettersChracter = 1, CapitalLettersCharcters = 2, SpecialChracters = 3, Digits = 4,MixLetter=5 };
 public:
	static void PrintLine(char LineChar = '-')
	{
		for (size_t i = 0; i < 40; i++)
		{
			cout << LineChar;
		}
		cout << endl;
	}

	static void SwapTwoNumbers(int& Num1, int& Num2)
	{
		int Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static void SwapTwoNumbers(float& Num1, float& Num2)
	{
		float Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static void SwapTwoNumbers(double& Num1, double& Num2)
	{
		double Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static string EncryptAText(string Text, int EncryptionKey) {
		for (int i = 0; i < Text.length(); i++) {
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}
	static string DecryptAText(string Text, int EncryptionKey) {
		for (int i = 0; i < Text.length(); i++) {
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}
	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To) {
		int result = rand() % (To - From + 1) + From;
		return result;
	}
	static char GetRandomCharacter(enCharacterTypes CharacterType) {
		switch (CharacterType)
		{
		case enCharacterTypes::SmallLettersChracter:
			return char(RandomNumber(97, 122));
			break;
		case enCharacterTypes::CapitalLettersCharcters:
			return char(RandomNumber(65, 90));
			break;
		case enCharacterTypes::SpecialChracters:
			return char(RandomNumber(33, 47));
			break;
		case enCharacterTypes::Digits:
			return char(RandomNumber(48, 57));
			break;
		default:
			return char(RandomNumber(97, 122));
			break;
		}
		return '\0';

	}
	static string GetVerificationKey() {
		string Key = "";

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				Key += GetRandomCharacter(enCharacterTypes::CapitalLettersCharcters);
			}
			if (i < 4) {
				Key += "-";
			}
		}
		return Key;
	}
	static void FillAnArrayWithRandomNums(int Numbers[], int Size) {


		for (int i = 0; i < Size; i++) {
			Numbers[i] = RandomNumber(1, 100);
		}
	}

	static void FillAnArrayWithKeys(string Array[], int Number) {
		for (int i = 1; i <= Number; i++) {
			Array[i] = GetVerificationKey();
		}
	}


	static void SwapTwoWords(string& Word1, string& Word2)
	{
		string Temp;
		Temp = Word1;
		Word1 = Word2;
		Word2 = Temp;

	}
	static void SwapTwoValues(bool& Value1, bool& Value2)
	{
		bool Temp;
		Temp = Value1;
		Value1 = Value2;
		Value2 = Temp;

	}
	static void SwapTwoDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate::SwapDates(Date1, Date2);	

	}
	static void ShuffleAnArray(int Numbers[], int Size) {
		for (int i = 0; i < Size; i++) {
			int RandomIndex = RandomNumber(0, Size - 1);
			SwapTwoNumbers(Numbers[i], Numbers[RandomIndex]);
		}
	}
	static void ShuffleAnArray(string Words[], int Size) {
		for (int i = 0; i < Size; i++) {
			int RandomIndex = RandomNumber(0, Size - 1);
			SwapTwoWords(Words[i], Words[RandomIndex]);
		}
	}

};

