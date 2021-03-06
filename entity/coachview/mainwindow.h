/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <const/constants.h>
#include <entity/entity.h>
#include <entity/contromodule/mrcteam.h>
#include <QMainWindow>
#include <QGroupBox>
#include <QProgressBar>
#include <QLabel>
#include <QMutex>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // general
    void resetRobots();
    void setRobotVisionStatus(quint8 id, bool status);

    // utils
    QString transformIntToString(int value);
    void setupTeams(MRCTeam *our, MRCTeam *their, QString opTeam = "");

    // setters
    void setPlayerRole(quint8 id, QString role);
    void setPlayerBattery(quint8 id, int qt);
    void setPlayerKickCharge(quint8 id, int qt);
    void setRadioConnect(quint8 id, bool isOnline);
    void setDribble(quint8 id, bool isActive);
    void setAgressivity(QString agressivity);

    // updaters
    void updateScores(int score_yellow, int yellowcards_yellow, int redcards_yellow, int tout_yellow,
                      int score_blue, int yellowcards_blue, int redcards_blue, int tout_blue);
    void updateGameStage(QString stage);
    void updateRefereeCommand(QString command);
    void updateTimeLeft(QString timeleft);
    void updateGUI(MRCTeam *ourTeam, MRCTeam *theirTeam, Locations *loc);

    // getters
    bool enableAllieVelocityVector();
    bool enableEnemyVelocityVector();
    bool enableBallVelocityVector();
    bool enablePlayerConfidency();

    // tree
    void addRoot();
    void resetTree(QString strat, QList<QString> playbookList, QMap<QString, QList<QString>> rolesList,
                   QMap<std::pair<QString, QString>, QList<std::pair<QString, quint8>>> playersList,
                   QMap<QString, QString> behavioursList);
    bool isContained(QTreeWidgetItem *parent, QString text);
    void removeOld(QTreeWidgetItem *parent, QList<QString> stringList);
    QTreeWidgetItem* addChild(QTreeWidgetItem* parent, QString text);

private:
    Ui::MainWindow *ui;
    std::vector<QGroupBox*> playerBoxes;
    std::vector<QProgressBar*> playerBatteries;
    std::vector<QProgressBar*> playerKickCharges;
    std::vector<std::pair<QLabel*, QLabel*>> playerRoles;
    std::vector<QLabel*> playerConnections;
    std::vector<QLabel*> playerVisionStatus;
    std::vector<QLabel*> playerDribbles;

    MRCTeam* _ourTeam;
    MRCTeam* _theirTeam;

    // tree
    QTreeWidget *treeWidget;
    QTreeWidgetItem* root;
    QMap<QTreeWidgetItem*, QList<QTreeWidgetItem*>> roles;
    QList<QTreeWidgetItem*> robots;


    // aux functions
    QPixmap getRolePixmap(QString role);
    QPixmap getPlaybookPixmap(QString playbook);
    QList<QPixmap> robotsPixmaps;
};
#endif // MAINWINDOW_H
