#pragma once
#include "../../panel.hpp"

class Details : public PanelEditor {
private:
    bool isWindowActive;
public:
    Details() : PanelEditor("Details") {}
    void onUpdate();
    
    bool getiswindowActive() const;
};