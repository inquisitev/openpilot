#pragma once

#include <QFrame>
#include <QStackedLayout>
#include <QWidget>
#include "common/params.h"

#include "selfdrive/ui/ui.h"

class StorageWidget : public QFrame {
  Q_OBJECT
  Q_PROPERTY(float storagePercent MEMBER storage_percent NOTIFY valueChanged);

public:
  explicit StorageWidget(QWidget* parent = 0);

signals:
  void valueChanged();

public slots:
  void updateState(const UIState &s);
  /*void clearStorage(int index = 0, const QString &param = "");*/

protected:
  float storage_percent{100};
  QStackedLayout *stack;
};
