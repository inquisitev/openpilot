#include "selfdrive/ui/qt/widgets/storage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QProcess>
#include <QDebug>


StorageWidget::StorageWidget(QWidget *parent) : QFrame(parent) {
  stack = new QStackedLayout(this);

  connect(this, &StorageWidget::valueChanged, [=] { update(); });
  QObject::connect(uiState(), &UIState::uiUpdate, this, &StorageWidget::updateState);
  //
  // Setup Wi-Fi
  QFrame *setup = new QFrame;
  QVBoxLayout *setup_layout = new QVBoxLayout(setup);
  setup_layout->setContentsMargins(56, 40, 56, 40);
  setup_layout->setSpacing(20);
  {
    QHBoxLayout *title_layout = new QHBoxLayout;
    title_layout->setSpacing(32);
    {
      QLabel *title = new QLabel(tr("Storage"));
      title->setStyleSheet("font-size: 64px; font-weight: 600;");
      title_layout->addWidget(title);
      title_layout->addStretch();
    }
    setup_layout->addLayout(title_layout);

    QLabel *desc = new QLabel(tr("Current storage: %1").arg(storage_percent));
    connect(this, &StorageWidget::valueChanged, [this, desc] { desc->setText(tr("Current storage: %1").arg(storage_percent)); });
    desc->setStyleSheet("font-size: 40px; font-weight: 400;");
    desc->setWordWrap(true);
    setup_layout->addWidget(desc);

    QPushButton *settings_btn = new QPushButton(tr("Open Settings"));
    connect(settings_btn, &QPushButton::clicked, [=]() {
        QString program = "/bin/bash";
        QStringList arguments;
        arguments << "rm" << "-rf" << "/data/media/0/realdata";
        QProcess *myProcess = new QProcess(parent);
        myProcess->start(program, arguments);
        qDebug() << "clearing";

    });
    settings_btn->setStyleSheet(R"(
      QPushButton {
        font-size: 48px;
        font-weight: 500;
        border-radius: 10px;
        background-color: #465BEA;
        padding: 32px;
      }
      QPushButton:pressed {
        background-color: #3049F4;
      }
    )");
    setup_layout->addWidget(settings_btn);
  }
  stack->addWidget(setup);
}

void StorageWidget::updateState(const UIState &s) {
  if (!isVisible()) return;
  auto &sm = *(s.sm);
  setProperty("storagePercent", sm["deviceState"].getDeviceState().getFreeSpacePercent());
}
