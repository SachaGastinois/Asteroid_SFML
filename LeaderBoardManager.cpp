#include "LeaderBoardManager.h"
#include "LevelManager.h"

void ULeaderBoardManager::CocktailSort()
{
    const int _playersCount = static_cast<int>(playersData.size());
    bool _changed = true;
    while (_changed)
    {
        _changed = false;

        if (_playersCount == 1 || _playersCount == 0) return;

        for (int _index = 0; _index < _playersCount - 2; _index++)
        {
            // > pour l'ordre croissant
            // < pour l'ordre décroissant
            if (playersData[_index].score < playersData[_index + 1].score)
            {
                Swap(_index, _index + 1);
                _changed = true;
            }
        }

        for (int _index = _playersCount - 2; _index > 0; _index--)
        {
            // > pour l'ordre croissant
            // < pour l'ordre décroissant
            if (playersData[_index].score < playersData[_index + 1].score)
            {
                Swap(_index, _index + 1);
                _changed = true;
            }
        }
    }
}

void ULeaderBoardManager::Swap(const int _firstIndex, const int _secondIndex)
{
    FPlayerData _tempElement = playersData[_firstIndex];
    playersData[_firstIndex] = playersData[_secondIndex];
    playersData[_secondIndex] = _tempElement;
}

void ULeaderBoardManager::UpdatePlayersLabel()
{
    Vector2f _windowSize = M_LEVEL.GetCurrentLevel()->GetWindowSize();

    const int _playersLabelCount = static_cast<int>(playersLabel.size());
    for (int _index = 0; _index < _playersLabelCount; _index++)
    {
        if (_index >= playersData.size()) return;

        const string& _text = playersData[_index].name + " : " + to_string(playersData[_index].score) + " points";

        playersLabel[_index]->SetText(_text);

        playersLabel[_index]->SetOriginAtMiddle();
        playersLabel[_index]->SetLocation({ _windowSize.x * 0.5f, _windowSize.y * 0.25f + _windowSize.y * _index / 20 });

    }
}
