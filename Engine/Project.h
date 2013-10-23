//  Powiter
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
/*
 *Created by Alexandre GAUTHIER-FOICHAT on 6/1/2012.
 *contact: immarespond at gmail dot com
 *
 */

#ifndef PROJECT_H
#define PROJECT_H

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <QString>
#include <QDateTime>

#include "Global/GlobalDefines.h"

#include "Engine/Format.h"

class Node;
class TimeLine;
class AppInstance;
class ComboBox_Knob;
class Button_Knob;
class Knob;



namespace Powiter{

class Project : public QObject{
    
    Q_OBJECT
        
    QString _projectName;
    QString _projectPath;
    bool _hasProjectBeenSavedByUser;
    QDateTime _ageSinceLastSave;
    QDateTime _lastAutoSave;
    ComboBox_Knob* _formatKnob;
    Button_Knob* _addFormatKnob;
    boost::shared_ptr<TimeLine> _timeline; // global timeline
    
    std::map<std::string,int> _nodeCounters;
    bool _autoSetProjectFormat;
    std::vector<Node*> _currentNodes;
    
    std::vector<Format> _availableFormats;
    
    std::vector<Knob*> _projectKnobs;
    AppInstance* _appInstance;//ptr to the appInstance
public:
    
    Project(AppInstance* appInstance);
    
    ~Project();
    
    const std::vector<Node*>& getCurrentNodes() const{return _currentNodes;}
    
    const QString& getProjectName() const WARN_UNUSED_RETURN {return _projectName;}
    
    void setProjectName(const QString& name) {_projectName = name;}
    
    const QString& getProjectPath() const WARN_UNUSED_RETURN {return _projectPath;}
    
    void setProjectPath(const QString& path) {_projectPath = path;}
    
    bool hasProjectBeenSavedByUser() const WARN_UNUSED_RETURN {return _hasProjectBeenSavedByUser;}
    
    void setHasProjectBeenSavedByUser(bool s) {_hasProjectBeenSavedByUser = s;}
    
    const QDateTime& projectAgeSinceLastSave() const WARN_UNUSED_RETURN {return _ageSinceLastSave;}
    
    void setProjectAgeSinceLastSave(const QDateTime& t) {_ageSinceLastSave = t;}
    
    const QDateTime& projectAgeSinceLastAutosave() const WARN_UNUSED_RETURN {return _lastAutoSave;}
    
    void setProjectAgeSinceLastAutosaveSave(const QDateTime& t) {_lastAutoSave = t;}
    
    const Format& getProjectDefaultFormat() const WARN_UNUSED_RETURN ;
    
    void setProjectDefaultFormat(const Format& f);
    
    /*Returns the index of the format*/
    int tryAddProjectFormat(const Format& f);
    
    bool shouldAutoSetProjectFormat() const {return _autoSetProjectFormat;}
    
    void setAutoSetProjectFormat(bool b){_autoSetProjectFormat = b;}
    
    const std::vector<Knob*>& getProjectKnobs() const;
    
    boost::shared_ptr<TimeLine> getTimeLine() const WARN_UNUSED_RETURN {return _timeline;}
    
    // TimeLine operations (to avoid duplicating the shared_ptr when possible)
    void setFrameRange(int first, int last);
    
    void seekFrame(int frame);
    
    void incrementCurrentFrame();
    
    void decrementCurrentFrame();
    
    int currentFrame() const WARN_UNUSED_RETURN;
    
    int firstFrame() const WARN_UNUSED_RETURN;
    
    int lastFrame() const WARN_UNUSED_RETURN;
    
    void initNodeCountersAndSetName(Node* n);
    
    void clearNodes();
    
    void loadProject(const QString& path,const QString& name);
    
    void saveProject(const QString& path,const QString& filename,bool autoSave = false);
    
public slots:
    
    void onProjectFormatChanged();
    
    void createNewFormat();
    
signals:
    
    void projectFormatChanged(Format);

private:
    
    
   };
}

#endif // PROJECT_H
