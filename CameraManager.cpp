#include "CameraManager.h"

Camera::UCameraManager::UCameraManager()
{
	allRendersData = map<u_int, FRenderData>();
	allCameras = unordered_map<string, UCameraComponent*>();
	current = nullptr;
}


void Camera::UCameraManager::Render(RenderWindow& _window, const bool _isSplitScreen)
{
	int _index = -1;

	for (const pair<int, u_int>& _element : allElements)
	{
		if (_element.first == _index) continue;

		_index = _element.first;
		const AllCameras& _allCameras = !_isSplitScreen ? AllCameras({ make_pair(current->GetOwner()->GetDisplayName(), current) }) : allCameras;
		RenderAllCameras(_window, _index, _allCameras);
	}
}

bool Camera::UCameraManager::SetRenderView(UCameraComponent* _camera, RenderWindow& _window)
{
	if (!_camera->IsActive()) return false;

	// Je définis la vue
	_window.setView(*_camera->GetView());
	return true;
}

void Camera::UCameraManager::RenderAllCameras(RenderWindow& _window, const int _index, const AllCameras& _allCameras)
{
	const pair<Iterator, Iterator>& _results = allElements.equal_range(_index);
	bool _isFirst = true;
	vector<FRenderData> _renderWidgets;

	// Pour chaque caméra
	for (const pair<string, UCameraComponent*>& _pair : _allCameras)
	{
		if (!SetRenderView(_pair.second, _window))
		{
			_pair.second->SetViewport(FloatRect(Vector2f(), Vector2f()));
			continue;
		}

		RenderAllElements(_window, _results, _isFirst, _renderWidgets);
		RenderAllWidgets(_window, _renderWidgets);
	}
}

void Camera::UCameraManager::RenderAllElements(RenderWindow& _window, const pair<Iterator, Iterator>& _results, bool& _isFirst, RenderWidgets& _renderWidgets)
{
	// Je draw tous les éléments
	for (Iterator _it = _results.first; _it != _results.second; ++_it)
	{
		const FRenderData& _data = allRendersData.at(_it->second);

		// Si il s'agit d'un widget
		if (_isFirst && _data.type == Screen)
		{
			// Je l'ajoute comme à afficher plus tard
			_renderWidgets.push_back(_data);
			continue;
		}

		// Je draw l'élément
		_data.callback(_window);
	}

	_isFirst = false;
}

void Camera::UCameraManager::RenderAllWidgets(RenderWindow& _window, const vector<FRenderData>& _renderWidgets)
{
	// Je définis la vue
	_window.setView(_window.getDefaultView());

	for (const FRenderData& _data : _renderWidgets)
	{
		// Je draw l'élément
		_data.callback(_window);
	}
}

void Camera::UCameraManager::UnbindOnRenderWindow(const u_int& _uniqueId)
{
	if (!allRendersData.contains(_uniqueId)) return;

	const int _zOrder = allRendersData.at(_uniqueId).zOrder;
	const pair<Iterator, Iterator>& _results = allElements.equal_range(_zOrder);

	for (Iterator _it = _results.first; _it != _results.second; ++_it)
	{
		if (_it->second != _uniqueId) continue;
		allElements.erase(_it);
		break;
	}

	allRendersData.erase(_uniqueId);
}