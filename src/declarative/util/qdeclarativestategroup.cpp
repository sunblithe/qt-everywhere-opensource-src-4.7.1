/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "private/qdeclarativestategroup_p.h"

#include "private/qdeclarativetransition_p.h"
#include "private/qdeclarativestate_p_p.h"

#include <qdeclarativebinding_p.h>
#include <qdeclarativeglobal_p.h>

#include <QtCore/qstringbuilder.h>
#include <QtCore/qdebug.h>

#include <private/qobject_p.h>
#include <qdeclarativeinfo.h>

QT_BEGIN_NAMESPACE

DEFINE_BOOL_CONFIG_OPTION(stateChangeDebug, STATECHANGE_DEBUG);

class QDeclarativeStateGroupPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QDeclarativeStateGroup)
public:
    QDeclarativeStateGroupPrivate()
    : nullState(0), componentComplete(true),
      ignoreTrans(false), applyingState(false), unnamedCount(0) {}

    QString currentState;
    QDeclarativeState *nullState;

    static void append_state(QDeclarativeListProperty<QDeclarativeState> *list, QDeclarativeState *state);
    static int count_state(QDeclarativeListProperty<QDeclarativeState> *list);
    static QDeclarativeState *at_state(QDeclarativeListProperty<QDeclarativeState> *list, int index);
    static void clear_states(QDeclarativeListProperty<QDeclarativeState> *list);

    QList<QDeclarativeState *> states;
    QList<QDeclarativeTransition *> transitions;

    bool componentComplete;
    bool ignoreTrans;
    bool applyingState;
    int unnamedCount;

    QDeclarativeTransition *findTransition(const QString &from, const QString &to);
    void setCurrentStateInternal(const QString &state, bool = false);
    bool updateAutoState();
};

/*!
   \qmlclass StateGroup QDeclarativeStateGroup
    \ingroup qml-state-elements
   \since 4.7
   \brief The StateGroup element provides state support for non-Item elements.

   Item (and all derived elements) provides built in support for states and transitions
   via its \l{Item::state}{state}, \l{Item::states}{states} and \l{Item::transitions}{transitions} properties. StateGroup provides an easy way to
   use this support in other (non-Item-derived) elements.

   \qml
   MyCustomObject {
       StateGroup {
           id: myStateGroup
           states: State {
               name: "state1"
               ...
           }
           transitions: Transition {
               ...
           }
       }

       onSomethingHappened: myStateGroup.state = "state1";
   }
   \endqml

   \sa {qmlstate}{States} {Transitions}, {QtDeclarative}
*/

QDeclarativeStateGroup::QDeclarativeStateGroup(QObject *parent)
    : QObject(*(new QDeclarativeStateGroupPrivate), parent)
{
}

QDeclarativeStateGroup::~QDeclarativeStateGroup()
{
    Q_D(const QDeclarativeStateGroup);
    for (int i = 0; i < d->states.count(); ++i)
        d->states.at(i)->setStateGroup(0);
}

QList<QDeclarativeState *> QDeclarativeStateGroup::states() const
{
    Q_D(const QDeclarativeStateGroup);
    return d->states;
}

/*!
  \qmlproperty list<State> StateGroup::states
  This property holds a list of states defined by the state group.

  \qml
  StateGroup {
    states: [
      State { ... },
      State { ... }
      ...
    ]
  }
  \endqml

  \sa {qmlstate}{States}
*/
QDeclarativeListProperty<QDeclarativeState> QDeclarativeStateGroup::statesProperty()
{
    Q_D(QDeclarativeStateGroup);
    return QDeclarativeListProperty<QDeclarativeState>(this, &d->states, &QDeclarativeStateGroupPrivate::append_state,
                                                       &QDeclarativeStateGroupPrivate::count_state,
                                                       &QDeclarativeStateGroupPrivate::at_state,
                                                       &QDeclarativeStateGroupPrivate::clear_states);
}

void QDeclarativeStateGroupPrivate::append_state(QDeclarativeListProperty<QDeclarativeState> *list, QDeclarativeState *state)
{
    QDeclarativeStateGroup *_this = static_cast<QDeclarativeStateGroup *>(list->object);
    if (state) {
        _this->d_func()->states.append(state);
        state->setStateGroup(_this);
    }

}

int QDeclarativeStateGroupPrivate::count_state(QDeclarativeListProperty<QDeclarativeState> *list)
{
    QDeclarativeStateGroup *_this = static_cast<QDeclarativeStateGroup *>(list->object);
    return _this->d_func()->states.count();
}

QDeclarativeState *QDeclarativeStateGroupPrivate::at_state(QDeclarativeListProperty<QDeclarativeState> *list, int index)
{
    QDeclarativeStateGroup *_this = static_cast<QDeclarativeStateGroup *>(list->object);
    return _this->d_func()->states.at(index);
}

void QDeclarativeStateGroupPrivate::clear_states(QDeclarativeListProperty<QDeclarativeState> *list)
{
    QDeclarativeStateGroup *_this = static_cast<QDeclarativeStateGroup *>(list->object);
    _this->d_func()->setCurrentStateInternal(QString(), true);
    for (int i = 0; i < _this->d_func()->states.count(); ++i) {
        _this->d_func()->states.at(i)->setStateGroup(0);
    }
    _this->d_func()->states.clear();
}

/*!
  \qmlproperty list<Transition> StateGroup::transitions
  This property holds a list of transitions defined by the state group.

  \qml
  StateGroup {
    transitions: [
      Transition { ... },
      Transition { ... }
      ...
    ]
  }
  \endqml

  \sa {Transitions}
*/
QDeclarativeListProperty<QDeclarativeTransition> QDeclarativeStateGroup::transitionsProperty()
{
    Q_D(QDeclarativeStateGroup);
    return QDeclarativeListProperty<QDeclarativeTransition>(this, d->transitions);
}

/*!
  \qmlproperty string StateGroup::state

  This property holds the name of the current state of the state group.

  This property is often used in scripts to change between states. For
  example:

  \qml
    function toggle() {
        if (button.state == 'On')
            button.state = 'Off';
        else
            button.state = 'On';
    }
  \endqml

  If the state group is in its base state (i.e. no explicit state has been
  set), \c state will be a blank string. Likewise, you can return a
  state group to its base state by setting its current state to \c ''.

  \sa {qmlstates}{States}
*/
QString QDeclarativeStateGroup::state() const
{
    Q_D(const QDeclarativeStateGroup);
    return d->currentState;
}

void QDeclarativeStateGroup::setState(const QString &state)
{
    Q_D(QDeclarativeStateGroup);
    if (d->currentState == state)
        return;

    d->setCurrentStateInternal(state);
}

void QDeclarativeStateGroup::classBegin()
{
    Q_D(QDeclarativeStateGroup);
    d->componentComplete = false;
}

void QDeclarativeStateGroup::componentComplete()
{
    Q_D(QDeclarativeStateGroup);
    d->componentComplete = true;

    for (int ii = 0; ii < d->states.count(); ++ii) {
        QDeclarativeState *state = d->states.at(ii);
        if (!state->isNamed())
            state->setName(QLatin1String("anonymousState") % QString::number(++d->unnamedCount));
    }

    if (d->updateAutoState()) {
        return;
    } else if (!d->currentState.isEmpty()) {
        QString cs = d->currentState;
        d->currentState.clear();
        d->setCurrentStateInternal(cs, true);
    }
}

/*!
    Returns true if the state was changed, otherwise false.
*/
bool QDeclarativeStateGroup::updateAutoState()
{
    Q_D(QDeclarativeStateGroup);
    return d->updateAutoState();
}

bool QDeclarativeStateGroupPrivate::updateAutoState()
{
    Q_Q(QDeclarativeStateGroup);
    if (!componentComplete)
        return false;

    bool revert = false;
    for (int ii = 0; ii < states.count(); ++ii) {
        QDeclarativeState *state = states.at(ii);
        if (state->isWhenKnown()) {
            if (state->isNamed()) {
                if (state->when() && state->when()->evaluate().toBool()) {
                    if (stateChangeDebug()) 
                        qWarning() << "Setting auto state due to:" 
                                   << state->when()->expression();
                    if (currentState != state->name()) {
                        q->setState(state->name());
                        return true;
                    } else {
                        return false;
                    }
                } else if (state->name() == currentState) {
                    revert = true;
                }
            }
        }
    }
    if (revert) {
        bool rv = !currentState.isEmpty();
        q->setState(QString());
        return rv;
    } else {
        return false;
    }
}

QDeclarativeTransition *QDeclarativeStateGroupPrivate::findTransition(const QString &from, const QString &to)
{
    QDeclarativeTransition *highest = 0;
    int score = 0;
    bool reversed = false;
    bool done = false;

    for (int ii = 0; !done && ii < transitions.count(); ++ii) {
        QDeclarativeTransition *t = transitions.at(ii);
        for (int ii = 0; ii < 2; ++ii)
        {
            if (ii && (!t->reversible() ||
                      (t->fromState() == QLatin1String("*") && 
                       t->toState() == QLatin1String("*"))))
                break;
            QStringList fromState;
            QStringList toState;

            fromState = t->fromState().split(QLatin1Char(','));
            toState = t->toState().split(QLatin1Char(','));
            if (ii == 1)
                qSwap(fromState, toState);
            int tScore = 0;
            if (fromState.contains(from))
                tScore += 2;
            else if (fromState.contains(QLatin1String("*")))
                tScore += 1;
            else
                continue;

            if (toState.contains(to))
                tScore += 2;
            else if (toState.contains(QLatin1String("*")))
                tScore += 1;
            else
                continue;

            if (ii == 1)
                reversed = true;
            else
                reversed = false;

            if (tScore == 4) {
                highest = t;
                done = true;
                break;
            } else if (tScore > score) {
                score = tScore;
                highest = t;
            }
        }
    }

    if (highest)
        highest->setReversed(reversed);

    return highest;
}

void QDeclarativeStateGroupPrivate::setCurrentStateInternal(const QString &state, 
                                                   bool ignoreTrans)
{
    Q_Q(QDeclarativeStateGroup);
    if (!componentComplete) {
        currentState = state;
        return;
    }

    if (applyingState) {
        qmlInfo(q) << "Can't apply a state change as part of a state definition.";
        return;
    }

    applyingState = true;

    QDeclarativeTransition *transition = (ignoreTrans || ignoreTrans) ? 0 : findTransition(currentState, state);
    if (stateChangeDebug()) {
        qWarning() << this << "Changing state.  From" << currentState << ". To" << state;
        if (transition)
            qWarning() << "   using transition" << transition->fromState() 
                       << transition->toState();
    }

    QDeclarativeState *oldState = 0;
    if (!currentState.isEmpty()) {
        for (int ii = 0; ii < states.count(); ++ii) {
            if (states.at(ii)->name() == currentState) {
                oldState = states.at(ii);
                break;
            }
        }
    }

    currentState = state;
    emit q->stateChanged(currentState);

    QDeclarativeState *newState = 0;
    for (int ii = 0; ii < states.count(); ++ii) {
        if (states.at(ii)->name() == currentState) {
            newState = states.at(ii);
            break;
        }
    }

    if (oldState == 0 || newState == 0) {
        if (!nullState) { nullState = new QDeclarativeState; QDeclarative_setParent_noEvent(nullState, q); }
        if (!oldState) oldState = nullState;
        if (!newState) newState = nullState;
    }

    newState->apply(q, transition, oldState);
    applyingState = false;
    if (!transition)
        static_cast<QDeclarativeStatePrivate*>(QObjectPrivate::get(newState))->complete();
}

QDeclarativeState *QDeclarativeStateGroup::findState(const QString &name) const
{
    Q_D(const QDeclarativeStateGroup);
    for (int i = 0; i < d->states.count(); ++i) {
        QDeclarativeState *state = d->states.at(i);
        if (state->name() == name)
            return state;
    }

    return 0;
}

void QDeclarativeStateGroup::removeState(QDeclarativeState *state)
{
    Q_D(QDeclarativeStateGroup);
    d->states.removeOne(state);
}

QT_END_NAMESPACE


