////////////////////////////////////////////////////////////////////////////////
//
/// IView.h содержит интерфейс для взаимодействия контроллера с представлением
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

struct ISceneProvider;
struct IViewObserver;
struct VisibleRect;


////////////////////////////////////////////////////////////////////////
//
/// Интерфейс взаимодействия контроллера с представлением
/**
*/
////////////////////////////////////////////////////////////////////////
struct IView
{
  virtual ~IView() = default;

  /// Установить подписчика на события представления
  virtual void SetViewObserver(IViewObserver * observer) = 0;
  /// Установить проводника модели
  virtual void SetSceneProvider(ISceneProvider * sceneProvider) = 0;
  /// Отрисовать сцену
  virtual void RenderScene() = 0;
  /// Получить размер видимой области
  virtual const VisibleRect & GetVisibleRect() const = 0;
};
