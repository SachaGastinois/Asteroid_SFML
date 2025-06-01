#pragma once
#include "Singleton.h"
#include "CanvasWidget.h"
#include "LabelWidget.h"
#include "MainMenuLevel.h"

struct FPlayerData
{
	string name;
	int score;

	FPlayerData() = default;
	FPlayerData(const string& _name, const int _score)
	{
		name = _name;
		score = _score;
	}

	bool operator == (const FPlayerData& _playerData) const
	{
		return name == _playerData.name
			&& score == _playerData.score;
	}
};

class ULeaderBoardManager : public Singleton<ULeaderBoardManager>
{
	vector<FPlayerData> playersData = vector<FPlayerData>();
	vector<ALabelWidget*> playersLabel = vector<ALabelWidget*>();

	int maxPosition = 15;

public:
	FORCEINLINE void AddPlayerData(const FPlayerData& _playerData)
	{
		if (Contain(_playerData)) return;

		playersData.push_back(_playerData);
		CocktailSort();
		UpdatePlayersLabel();
	}
	FORCEINLINE void RemovePlayerData(const FPlayerData& _playerData)
	{
		if (!Contain(_playerData)) return;

		//playersData.erase(_playerData);
	}
	FORCEINLINE void SetPlayersLabel(vector<ALabelWidget*> _playersLabel)
	{
		playersLabel = _playersLabel;
	}
	FORCEINLINE vector<FPlayerData> GetPlayersData()
	{
		return playersData;
	}
	FORCEINLINE int GetMaxPosition()
	{
		return maxPosition;
	}
	FORCEINLINE bool Contain(const FPlayerData& _playerDataToVerify)
	{
		if (IsEmpty()) return false;

		for (const FPlayerData& _playerData : playersData)
		{
			if (_playerData == _playerDataToVerify)
			{
				return true;
			}
		}
		return false;
	}
	FORCEINLINE bool IsEmpty()
	{
		return playersData.empty();
	}

public:
	ULeaderBoardManager() = default;

public:
	void CocktailSort();
	void Swap(const int _firstIndex, const int _secondIndex);
	void UpdatePlayersLabel();
};

