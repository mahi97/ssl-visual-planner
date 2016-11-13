#ifndef PLAYON_H
#define PLAYON_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <math.h>
#include <QWidget>
#include <QLineEdit>
#include <QMouseEvent>
#include <QStatusBar>
#include <QRubberBand>
#include <QComboBox>
#include <QPainter>
#include <QTimer>
#include <QDebug>

#include "base.h"
#include "kkagentplanclass.h"
#include "kkplayonplansql.h"
#include "ul.h"

struct kkSelectedAgent {
    int agent = -1;
    int priority = -1;
    int part = -1;
};

struct kkCurrentState {
    int AorB = 0;
    int plan = -1;
    int agent = -1;
    int priority = -1;
    int agentSize = 1;
    int isBall = true;
    PEndPolicy endPolicy = Cycle;
    int endPolicyValue = 1;
};

class playon : public QWidget
{
    Q_OBJECT
public:
    explicit playon(QWidget *parent = 0);
    ~playon();

    void disable();
    void enable();
    void apply(int _id);
    void clean();

    void setLabel(QLabel *tLabel);
    void setWidget(QWidget *tWidget);
    void setStatusBar(QStatusBar *_statusBar);
    void setTabWidget(QTabWidget *_widget);

    void mousePressed(QMouseEvent *event, QPoint tempPos);
    void mouseMoved(QMouseEvent *event, QPoint tempPos);
    void mouseReleased(QMouseEvent *event, QPoint tempPos);

    void initPainting();
    // PLAN CONTROLS

    bool setPlan(PSkills skill);
    bool setPlanPoints();
    bool isInBallMode();
    void setTags(QString str);
    void choosePlan(int _index);
    int getPlanSize();
    void removePlan(int _index);

private:
    QTabWidget *POTabWidget;
    QLabel *fieldLabel;
    QPixmap *fieldPix;
    QWidget *POWidget;
    QStatusBar *statusBar;

    QLabel *playOnEndPolicyLabel[5];
    QLabel *playOnAgentSize[6];
    QLabel *playOnEndPolicyValue[6];
    QLabel *playOnFieldMode[3];
    QLabel *agentLabels[60];
    QLabel *agentLabel[5];
    QLineEdit *playOnEndPolicyCycleValue;
    QLabel *playOnEndPolicyCycleValueLabel;

    void initLabels();

    void setQLabel(QWidget *widget, QLabel **label, QRect rect, int index = 0);
    void setQlabelInTabWidget(QWidget *widget, QLabel **label, QRect rect, int size = 1);
    void setAgentLabel(QWidget *widget, QRect rect);

    kkSelectedAgent getSelectedAgent();
    kkSelectedAgent currentSelected;
    void paintAgentLabels();
    void insertSelectedAgentToState(kkSelectedAgent _selected);

    void getSelectedSettings();
    void paintSettings();
    void setABPointsLabelText();
    void initVarForPainting();
    kkCurrentState currentState;
    kkCurrentState lastState;

    void insertPlanToStruct(kkAgentPlan &plan);

    //migrated vars

    QRect bRect[5];
    bool bAreaSelected;
    int bSelectedArea, bTempArea;

    QRect aRect[5];
    bool aAreaSelected;
    int aSelectedArea[5][2], aTempArea[5][2];

    void drawRobot(QPainter &painter, int x, int y, QString label, int agent, bool selected, bool blink);
    void drawRobots(QPainter &painter, int id);
    int getArea(QRect *rect, int size, QPoint mPos);
    void showArea(int id, QRect *rect, int size);
    void showBallArea(int id);
    void showAgentArea(int id);

    QTimer *timer;
    int timerCounter;
    bool blinkCurrentAgent;

    kkAgentPlanClass *currentPlan;

    void setSkillTexts();
    void emptySkill(int agent, int priority);

    bool rightClickEmpty;

    //
    QString getSkillTextByEnum(PSkills skill);
    //sql side
    playOnPlanSQL *myPlan;
public:
    void disableSQL();
    void enableSQL();

    void savePlan(QString directory);
    int loadPlan(QString directory);
    void reset();
    void clearPlan();

private slots:
    void timerSlot();
    void activeA();
    void activeB();

signals:
    void updateTags(QString str);

};

#endif // PLAYON_H